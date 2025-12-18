# Semiconductor Project - ANN & SNN Implementation

반도체 프로젝트 - ANN 및 SNN 구현

## 프로젝트 개요
손동작 인식을 위한 인공신경망(ANN) 및 스파이킹 신경망(SNN) 구현 프로젝트

## 프로젝트 구조

### ANN 관련 파일
- `project/ann.py` - ANN 모델 메인 구현
- `project/ann_k-fold.py` - K-fold 교차 검증 구현
- `project/ann_script.py` - ANN 실행 스크립트
- `project/logs/` - 학습 로그

### SNN 관련 파일
- `snn.py` - SNN 모델 구현
- `snn_ip.cpp` - SNN IP 구현 (C++)
- `SNN_IP.h` - SNN IP 헤더 파일
- `vgg_spiking.py` - VGG 기반 SNN 모델
- `SNN_Training_Colab.ipynb` - SNN Colab 학습 노트북
- `project/snn.py` - Project 폴더의 SNN 구현
- `project/snn_script.py` - SNN 실행 스크립트
- Vivado 및 Vitis 관련 문서

### Vivado Project
- [Vivado 2019.2] -> Open Project -> `snn_1206.xpr` 
								IP는 `snn_ip` -> `solution1\` -> `impl\` -> `ip\` 
- [Vivado HLS 2019.2] -> Open Project -> `snn_1206\snn_ip\`
- [Vitis IDE 2019.2] -> Vivado에서 Launch Vitis -> `snn_1206\` Browse
- `test_pc.py` : Teraterm 연결 -> Vitis로 Run -> Teraterm 연결 해제 -> PC에서 `test_pc.py` run -> PC에서 결과 확인

