import time
import re
import os
import glob
import numpy as np
import serial
import torch
import torch.nn as nn
from PIL import Image
from typing import Optional, List

# ==========================
# Config
# ==========================
PORT = "COM13"     
BAUD = 115200

T = 10             # NUM_TIMESTEPS 
N_INPUT = 256      # FC-last 입력 크기
N_OUTPUT = 10


DECAY = 0.9
THRESHOLD = 1.0
RESET_POTENTIAL = 0.0

MODEL_PATH = r"C:\Users\blanc\OneDrive\바탕 화면\model\lightweight_snn.pth"


#   - 한 클래스만 보고 싶으면: ...\01_palm
#   - 여러 클래스 섞고 싶으면: ...\model (상위 폴더)
IMG_DIR   = r"C:\Users\blanc\OneDrive\바탕 화면\model\10_down"

CLASS_NAMES: List[str] = [
    "01_palm",
    "02_l",
    "03_fist",
    "04_fist_moved",
    "05_thumb",
    "06_index",
    "07_ok",
    "08_palm_moved",
    "09_c",
    "10_down",
]

# ==========================
# 1) Model 정의
# ==========================

class LightweightSNN(nn.Module):
    """
    lightweight_snn.pth 구조와 맞춘 CNN + FC-last SNN용 feature 추출 모델.

    state_dict 키 예시:
      features.0.weight : (16,1,3,3)
      features.4.weight : (32,16,3,3)
      features.8.weight : (64,32,3,3)
      classifier.0.weight : (256,4096)
      classifier.3.weight : (10,256)
    """
    def __init__(self):
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(1, 16, 3, padding=1, bias=False),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Identity(),
            nn.Conv2d(16, 32, 3, padding=1, bias=False),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Identity(),
            nn.Conv2d(32, 64, 3, padding=1, bias=False),
            nn.MaxPool2d(2),
        )
        # 입력: (1,1,64,64)
        # 64x64 → pool → 32 → pool → 16 → pool → 8  → 64*8*8 = 4096
        self.classifier = nn.Sequential(
            nn.Linear(4096, 256, bias=False),
            nn.ReLU(),
            nn.Identity(),
            nn.Linear(256, 10, bias=False),
        )

    def extract_fc1(self, x: torch.Tensor) -> torch.Tensor:
        """마지막 FC 이전의 256차원 feature (fc1 output) 추출."""
        # x: (1,1,64,64)
        z = self.features(x)          # (1,64,8,8)
        z = z.view(z.size(0), -1)     # (1,4096)
        fc1_out = self.classifier[0](z)  # (1,256)
        return fc1_out.squeeze(0)     # (256,)

    def get_fc2_weight_bias(self):
        """마지막 FC 레이어의 weight, bias 반환."""
        fc2 = self.classifier[3]
        return fc2.weight, fc2.bias   # (10,256), (10,) 또는 bias=None


def load_snn_model(path: str) -> nn.Module:
    """저장된 lightweight_snn.pth 로드."""
    ckpt = torch.load(path, map_location="cpu")
    state = ckpt["model_state_dict"] if isinstance(ckpt, dict) and "model_state_dict" in ckpt else ckpt
    model = LightweightSNN()
    model.load_state_dict(state, strict=False)
    model.eval()
    return model

# ==========================
# 2) fc1 feature → spikes (T,256)
# ==========================

def features_to_spikes(fc1_feat: torch.Tensor, T: int = T) -> np.ndarray:
    """
    256차원 fc1 feature → (T, 256) spike train (0/1)로 변환.
    간단한 threshold-based rate coding.
    """
    v = fc1_feat.detach().cpu().numpy().astype(np.float32)  # (256,)
    max_val = np.max(np.abs(v)) + 1e-8
    v = v / max_val
    v = np.clip(v, 0.0, 1.0)

    spikes = np.zeros((T, N_INPUT), dtype=np.uint8)
    for t in range(T):
        thr = t / float(T)   # 0.0, 0.1, ..., 0.9
        spikes[t] = (v > thr).astype(np.uint8)
    return spikes

# ==========================
# 3) FC-last + LIF (SW sim, HLS-mirror)
# ==========================

def snn_fc_last_hw_style(spikes: np.ndarray,
                         fc_weight: torch.Tensor,
                         fc_bias: Optional[torch.Tensor] = None) -> int:
    """
    HLS / FPGA와 같은 알고리즘으로 마지막 FC + LIF를 SW에서 시뮬레이션.
    spikes: (T,256) uint8
    fc_weight: (10,256)
    fc_bias: (10,) 또는 None
    """
    w = fc_weight.detach().cpu().numpy().astype(np.float32)  # (10,256)
    if fc_bias is not None:
        b = fc_bias.detach().cpu().numpy().astype(np.float32)
    else:
        b = np.zeros((N_OUTPUT,), dtype=np.float32)

    mem = np.zeros((N_OUTPUT,), dtype=np.float32)
    spike_count = np.zeros((N_OUTPUT,), dtype=np.float32)

    for t in range(spikes.shape[0]):
        x_t = spikes[t].astype(np.float32)  # (256,)
        # 출력 뉴런별로 FC + LIF 업데이트
        for o in range(N_OUTPUT):
            s = np.dot(x_t, w[o]) + b[o]
            mem[o] = DECAY * mem[o] + s
            if mem[o] >= THRESHOLD:
                spike_count[o] += 1.0
                mem[o] = RESET_POTENTIAL

    cls = int(np.argmax(spike_count))
    return cls

# ==========================
# 4) Image loading
# ==========================

def load_image_to_tensor(path: str) -> torch.Tensor:
    """
    경로의 이미지를 64x64 grayscale tensor로 로드: (1,1,64,64)
    """
    img = Image.open(path).convert("L")
    img = img.resize((64, 64))
    arr = np.array(img, dtype=np.float32) / 255.0
    tensor = torch.from_numpy(arr).unsqueeze(0).unsqueeze(0)  # (1,1,64,64)
    return tensor

# ==========================
# 5) UART <-> FPGA
# ==========================

def send_spikes_and_get_fpga_class(spikes: np.ndarray,
                                   port: str = PORT,
                                   baud: int = BAUD) -> int:
    """
    spikes: (T,256) uint8
    Protocol:
      - 'S','N','N' header
      - 2560 bytes: spikes.flatten()
    FPGA 쪽 UART 로그에서 "Predicted class = X" 패턴을 찾아 class 반환.
    찾지 못하면 -1 반환.
    """
    flat = spikes.reshape(-1).astype(np.uint8)  # len = T*256 = 2560

    print(f"[PC] Opening serial port {port} @ {baud}...")
    with serial.Serial(port, baud, timeout=1) as ser:
        # 보드 리셋 직후 약간 기다리기
        time.sleep(0.2)
        ser.reset_input_buffer()

        print("[PC] Sending header 'SNN'...")
        ser.write(b"SNN")
        ser.flush()
        time.sleep(0.05)

        print(f"[PC] Sending {len(flat)} spike bytes...")
        ser.write(flat.tobytes())
        ser.flush()

        print("[PC] Waiting for FPGA logs...")
        fpga_class: Optional[int] = None
        t_start = time.time()

        # 디버깅을 위해 RAW 로그 모두 출력
        while time.time() - t_start < 8.0:  # 8초 동안 대기
            line = ser.readline()
            if not line:
                continue
            try:
                text = line.decode(errors="ignore").strip()
            except Exception:
                text = repr(line)

            if text:
                print("[FPGA]", text)
                m = re.search(r"Predicted class\s*=\s*(\d+)", text)
                if m:
                    fpga_class = int(m.group(1))
                    break

    if fpga_class is None:
        print("[PC] FPGA class not found in logs!")
        return -1

    print(f"[PC] Parsed FPGA class = {fpga_class}")
    return fpga_class

# ==========================
# 6) GT 추론 (폴더명 기준)
# ==========================

def infer_gt_from_path(img_path: str) -> Optional[int]:
    """
    폴더 이름으로 GT class index 추론.
    예) .../01_palm/frame_xxx.png  ->  class 0
    """
    dir_name = os.path.basename(os.path.dirname(img_path))
    if dir_name in CLASS_NAMES:
        return CLASS_NAMES.index(dir_name)
    return None

# ==========================
# 7) Main: loop over many images
# ==========================

def main():
    # 1) 모델 로드
    print("[PC] Loading model...")
    model = load_snn_model(MODEL_PATH)
    print("[PC] Model loaded from", MODEL_PATH)

    fc2_w, fc2_b = model.get_fc2_weight_bias()   # (10,256), (10,) 또는 None

    # 2) IMG_DIR 내 모든 이미지 수집
    img_paths = sorted(
        glob.glob(os.path.join(IMG_DIR, "*.png")) +
        glob.glob(os.path.join(IMG_DIR, "*.jpg")) +
        glob.glob(os.path.join(IMG_DIR, "*.jpeg"))
    )
    print(f"[PC] Found {len(img_paths)} images in {IMG_DIR}")

    if not img_paths:
        print("[PC] No images found. Check IMG_DIR.")
        return

    total = 0
    match_sw_hw = 0

    per_class_sw = [0] * N_OUTPUT
    per_class_hw = [0] * N_OUTPUT

    sw_correct_gt = 0
    hw_correct_gt = 0

    for img_path in img_paths:
        total += 1
        basename = os.path.basename(img_path)
        gt_idx = infer_gt_from_path(img_path)

        print("\n==============================")
        print(f"[PC] Image {total}: {basename}")
        if gt_idx is not None:
            print(f"  (GT folder label: class {gt_idx} = {CLASS_NAMES[gt_idx]})")

        # 3) 이미지 로드
        x = load_image_to_tensor(img_path)

        # 4) fc1 feature → spikes
        with torch.no_grad():
            fc1_feat = model.extract_fc1(x)      # (256,)
        spikes = features_to_spikes(fc1_feat, T=T)
        print("[PC] Spikes generated.")

        # 5) SW SNN (FC-last + LIF 시뮬)
        sw_class = snn_fc_last_hw_style(spikes, fc2_w, fc2_b)
        per_class_sw[sw_class] += 1
        print(f"[PC] SW class = {sw_class} ({CLASS_NAMES[sw_class]})")

        # 6) HW SNN (FPGA)
        hw_class = send_spikes_and_get_fpga_class(spikes, PORT, BAUD)
        if 0 <= hw_class < N_OUTPUT:
            per_class_hw[hw_class] += 1
            print(f"[PC] HW class = {hw_class} ({CLASS_NAMES[hw_class]})")
        else:
            print(f"[PC] HW class = {hw_class} (INVALID)")

        # 7) SW vs HW 비교
        same = (sw_class == hw_class)
        if same:
            match_sw_hw += 1
        print(f"[RESULT] {basename} -> SW: {sw_class}, HW: {hw_class}, "
              f"{'MATCH' if same else 'MISMATCH'}")

        # 8) GT 기준 정확도 (폴더명 기반)
        if gt_idx is not None:
            if sw_class == gt_idx:
                sw_correct_gt += 1
            if hw_class == gt_idx:
                hw_correct_gt += 1

    # ==========================
    # Summary
    # ==========================
    print("\n========== SUMMARY ==========")
    print(f"Total images: {total}")
    print(f"SW vs HW MATCH: {match_sw_hw} / {total} ({match_sw_hw / total * 100:.1f}%)")

    print("\nSW predicted count per class (0~9):")
    for i in range(N_OUTPUT):
        print(f"  class {i} ({CLASS_NAMES[i]}): {per_class_sw[i]}")

    print("\nHW predicted count per class (0~9):")
    for i in range(N_OUTPUT):
        print(f"  class {i} ({CLASS_NAMES[i]}): {per_class_hw[i]}")

    if total > 0:
        print("\nAssuming GT from folder names (01_palm, 02_l, ...)")
        print(f"SW correct vs GT: {sw_correct_gt} / {total} "
              f"({sw_correct_gt / total * 100:.1f}%)")
        print(f"HW correct vs GT: {hw_correct_gt} / {total} "
              f"({hw_correct_gt / total * 100:.1f}%)")


if __name__ == "__main__":
    main()
