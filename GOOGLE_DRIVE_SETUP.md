# Google Drive 설정 가이드

## 🎯 왜 Google Drive를 사용하나요?

✅ **한 번만 업로드** - 파일을 Drive에 한 번만 올리면 됩니다
✅ **영구 저장** - Colab 연결이 끊겨도 파일이 사라지지 않습니다
✅ **학습 재개** - 중단된 학습을 언제든 이어서 할 수 있습니다
✅ **자동 백업** - 모든 학습 결과가 Drive에 자동 저장됩니다

---

## 📁 1단계: Google Drive 폴더 구조 만들기

Google Drive (https://drive.google.com)에 접속해서 다음과 같이 폴더를 만드세요:

```
MyDrive/
└── SNN_Project/                    👈 이 폴더를 만드세요
    ├── code/                       👈 코드 파일 폴더
    │   ├── snn.py
    │   └── vgg_spiking.py
    ├── models/                     👈 ANN 모델 폴더
    │   └── ann_vgg16_hand_gesture.pth
    ├── datasets/                   👈 데이터셋 폴더
    │   └── hand_gesture/
    │       ├── train/
    │       │   ├── class1/
    │       │   ├── class2/
    │       │   └── ...
    │       └── test/
    │           ├── class1/
    │           ├── class2/
    │           └── ...
    ├── trained_models/             👈 (자동 생성됨)
    │   ├── ann/
    │   └── snn/
    └── logs/                       👈 (자동 생성됨)
        └── snn/
```

---

## 📤 2단계: 파일 업로드하기

### 방법 1: 웹 브라우저로 업로드 (추천)

1. **Google Drive (drive.google.com) 접속**

2. **SNN_Project 폴더 생성**
   - 우클릭 > 새 폴더 > 이름: `SNN_Project`

3. **SNN_Project 폴더 안에 하위 폴더 생성**
   - `code` 폴더 생성
   - `models` 폴더 생성
   - `datasets` 폴더 생성

4. **파일 업로드**

   **code 폴더에 업로드:**
   - `snn.py` (수정된 버전)
   - `vgg_spiking.py` (수정된 버전)

   **models 폴더에 업로드:**
   - `ann_vgg16_hand_gesture.pth` (약 500MB)

   **datasets 폴더에 업로드:**
   - Option A: `hand_gesture.zip` 업로드 후 Drive에서 압축 해제
   - Option B: `hand_gesture` 폴더를 통째로 업로드 (시간이 오래 걸릴 수 있음)

---

### 방법 2: Google Drive 데스크톱 앱 사용

1. **Google Drive 데스크톱 설치**
   - https://www.google.com/drive/download/

2. **로컬 폴더를 Drive와 동기화**
   - 현재 프로젝트 폴더를 Drive의 `SNN_Project`로 복사
   - 자동으로 동기화됨

---

## 🗂️ 3단계: 데이터셋 압축 해제 (zip 파일을 업로드한 경우)

### Colab에서 압축 해제하기

Colab 노트북에서 다음 셀을 실행:

```python
from google.colab import drive
import zipfile

# Drive 마운트
drive.mount('/content/drive')

# 압축 파일 경로
zip_path = '/content/drive/MyDrive/SNN_Project/datasets/hand_gesture.zip'
extract_to = '/content/drive/MyDrive/SNN_Project/datasets/'

# 압축 해제
with zipfile.ZipFile(zip_path, 'r') as zip_ref:
    zip_ref.extractall(extract_to)

print("✅ 압축 해제 완료!")

# 확인
!ls /content/drive/MyDrive/SNN_Project/datasets/hand_gesture/
```

---

## ✅ 4단계: 파일 구조 확인

모든 파일이 제대로 업로드되었는지 확인하세요:

### 체크리스트

- [ ] `SNN_Project/code/snn.py` 존재
- [ ] `SNN_Project/code/vgg_spiking.py` 존재
- [ ] `SNN_Project/models/ann_vgg16_hand_gesture.pth` 존재 (약 500MB)
- [ ] `SNN_Project/datasets/hand_gesture/train/` 폴더 존재
- [ ] `SNN_Project/datasets/hand_gesture/test/` 폴더 존재
- [ ] `train` 폴더 안에 클래스별 폴더들이 있음
- [ ] `test` 폴더 안에 클래스별 폴더들이 있음

### Colab에서 확인하기

```python
from google.colab import drive
drive.mount('/content/drive')

PROJECT_DIR = '/content/drive/MyDrive/SNN_Project'

# 파일 구조 확인
!ls -R {PROJECT_DIR} | head -50
```

---

## 🚀 5단계: Colab에서 학습 실행

1. **Colab 노트북 열기**
   - `SNN_Training_Colab_Drive.ipynb` 사용

2. **GPU 활성화**
   - 런타임 > 런타임 유형 변경 > GPU (T4) 선택

3. **노트북 실행**
   - 셀을 순서대로 실행
   - Drive 마운트 허용 (팝업에서 승인)

---

## 💾 학습 결과 저장 위치

학습이 완료되면 다음 위치에 자동 저장됩니다:

- **학습된 SNN 모델**: `SNN_Project/trained_models/snn/snn_vgg16_hand_gesture_30.pth`
- **학습 로그**: `SNN_Project/logs/snn/snn_vgg16_hand_gesture_30.log`

**Colab 연결이 끊겨도 이 파일들은 Google Drive에 영구 저장됩니다!**

---

## 🔄 학습 재개하기

Colab 연결이 끊기거나 학습을 중단했을 때:

```python
# 이전 SNN 모델에서 이어서 학습
!python snn.py \
    --dataset HAND_GESTURE \
    --architecture VGG16 \
    --pretrained_snn {PROJECT_DIR}/trained_models/snn/snn_vgg16_hand_gesture_30.pth \
    --epochs 100 \
    --timesteps 30 \
    --batch_size 64 \
    --learning_rate 1e-5 \
    --gpu True \
    --log
```

---

## 📊 Drive 용량 확인

### 필요한 용량

- **코드 파일**: ~50KB
- **ANN 모델**: ~500MB
- **데이터셋**: ~1-2GB (데이터셋 크기에 따라 다름)
- **학습된 SNN 모델**: ~500MB
- **로그 파일**: ~1-10MB

**총 필요 용량: 약 2-3GB**

Google Drive 무료 용량은 15GB이므로 충분합니다!

---

## 🔧 트러블슈팅

### 문제 1: Drive 마운트 실패
**해결**:
```python
from google.colab import drive
drive.flush_and_unmount()  # 기존 마운트 해제
drive.mount('/content/drive', force_remount=True)  # 다시 마운트
```

### 문제 2: 파일을 찾을 수 없음
**해결**:
- Drive 웹에서 파일이 실제로 업로드되었는지 확인
- 경로가 정확한지 확인 (대소문자 구분!)
```python
!ls -R /content/drive/MyDrive/SNN_Project/
```

### 문제 3: 데이터셋 경로 오류
**해결**:
- 데이터셋 폴더 구조 확인:
```python
!ls /content/drive/MyDrive/SNN_Project/datasets/hand_gesture/train/ | head -10
!ls /content/drive/MyDrive/SNN_Project/datasets/hand_gesture/test/ | head -10
```

### 문제 4: Drive 용량 부족
**해결**:
- 불필요한 파일 삭제
- Google One 구독 (100GB: 월 2,400원)
- 또는 학습 후 모델만 남기고 데이터셋은 로컬에 보관

---

## 💡 팁

### 1. 빠른 업로드
- 큰 파일(데이터셋)은 zip으로 압축해서 업로드하면 더 빠릅니다
- 압축 해제는 Colab에서 하면 됩니다

### 2. 폴더 공유
- 팀원과 작업 시 `SNN_Project` 폴더를 공유하면 협업 가능

### 3. 버전 관리
- 학습 결과를 날짜별로 폴더를 만들어 보관하면 좋습니다
```
SNN_Project/
└── trained_models/
    └── snn/
        ├── 2024-12-03/
        │   └── snn_vgg16_hand_gesture_30.pth
        └── 2024-12-04/
            └── snn_vgg16_hand_gesture_50.pth
```

### 4. 로그 확인
- Drive에서 직접 로그 파일을 열어서 확인 가능
- Google Colab에서 실시간으로 확인도 가능

---

## 🎉 완료!

이제 Google Drive에 모든 파일이 준비되었습니다!

다음 단계:
1. [SNN_Training_Colab_Drive.ipynb](SNN_Training_Colab_Drive.ipynb) 노트북 열기
2. Colab에서 실행
3. 학습 결과는 자동으로 Drive에 저장됩니다!

**Colab 연결이 끊겨도 걱정하지 마세요!**
모든 파일은 Google Drive에 안전하게 보관됩니다. 🚀
