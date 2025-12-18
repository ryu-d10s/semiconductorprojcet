# Semiconductor Project - ANN & SNN Implementation

반도체 프로젝트 - ANN 및 SNN 구현

## 프로젝트 개요
손동작 인식을 위한 인공신경망(ANN) 및 스파이킹 신경망(SNN) 구현 프로젝트

## 팀원 파일 업로드 가이드

### 1. Git 설치
- [Git 다운로드](https://git-scm.com/downloads)

### 2. 저장소 클론
```bash
git clone https://github.com/ryu-d10s/semiconductorprojcet.git
cd semiconductorprojcet
```

### 3. 파일 추가
```bash
# 자신의 파일을 프로젝트 폴더에 복사 후
git add 파일이름
# 또는 모든 파일 추가
git add .
```

### 4. 커밋
```bash
git commit -m "본인이름: 파일설명"
# 예: git commit -m "홍길동: VGG SNN 모델 구현"
```

### 5. 푸시
```bash
git pull origin main  # 최신 변경사항 가져오기
git push origin main  # 업로드
```

## 프로젝트 구조

### ANN 관련 파일 (현재 업로드됨)
- `project/ann.py` - ANN 모델 메인 구현
- `project/ann_k-fold.py` - K-fold 교차 검증 구현
- `project/ann_script.py` - ANN 실행 스크립트
- `project/logs/` - 학습 로그
- `GOOGLE_DRIVE_SETUP.md` - 구글 드라이브 설정 가이드

### SNN 관련 파일 (추가해야함. 파일 이름 다를 수 있음)
- `snn.py` - SNN 모델 구현
- `snn_ip.cpp` - SNN IP 구현 (C++)
- `SNN_IP.h` - SNN IP 헤더 파일
- `vgg_spiking.py` - VGG 기반 SNN 모델
- `SNN_Training_Colab.ipynb` - SNN Colab 학습 노트북
- `project/snn.py` - Project 폴더의 SNN 구현
- `project/snn_script.py` - SNN 실행 스크립트
- Vivado 및 Vitis 관련 문서

### Vivado Project
- [Vivado 2019.2] open project -> 'snn_1206.xpr' 
								IP는 
									snn_ip\
										solution1\
												impl\
													ip\ 를추가함

- [Vivado HLS 2019.2] -> Open Project -> 'snn_1206\snn_ip\'
- [Vitis IDE 2019.2] -> Vivado에서 Launch Vitis -> 'snn_1206\' Browse

## 주의사항
- 푸시하기 전에 항상 `git pull` 먼저 실행
- 충돌(conflict) 발생 시 문의
- SNN 파일 추가 시 `.gitignore`에서 해당 파일 제거 후 커밋
