from torchvision import datasets, transforms

# HAND_GESTURE 데이터셋과 동일한 transform 사용
normalize_gray = transforms.Normalize(mean=[0.5], std=[0.5])
transform_test = transforms.Compose([
    transforms.Grayscale(num_output_channels=1),
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
    normalize_gray
])

# 데이터셋 경로 (실제 경로로 변경해주세요)
dataset_path = '/content/Datasets/hand_gesture/train'

try:
    trainset = datasets.ImageFolder(
        root=dataset_path,
        transform=transform_test
    )

    print("=" * 50)
    print("클래스 매핑 정보")
    print("=" * 50)
    print(f"총 클래스 수: {len(trainset.classes)}\n")

    # class_to_idx는 폴더명 -> 클래스 번호 매핑
    print("폴더명 -> 클래스 번호:")
    for folder_name, class_idx in sorted(trainset.class_to_idx.items(), key=lambda x: x[1]):
        print(f"  클래스 {class_idx}: {folder_name}")

    print("\n" + "=" * 50)
    print(f"class 3 = {trainset.classes[3]}")
    print("=" * 50)

except Exception as e:
    print(f"오류 발생: {e}")
    print("\n해결 방법:")
    print("1. dataset_path 변수를 실제 데이터셋 경로로 변경하세요")
    print("2. 예: dataset_path = './hand_gesture/train'")
