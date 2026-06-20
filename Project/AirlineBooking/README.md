# AirlineBooking Project

자료구조 프로젝트용 항공권 예매 시스템입니다.

## 핵심 구조

- `AirportGraph`: 공항을 노드, 항공편을 방향 간선으로 표현한 그래프 자료구조
- `MainWindow`: 공항 선택, 출발/도착 항공편 목록, 예매 완료 메시지 UI
- `MapWidget`: 지도 위 공항 버튼과 항공 노선을 시각화하는 Qt 위젯

## 빌드 방법

Qt Creator에서 `AirlineBooking.pro`를 열고 빌드하면 됩니다.

CLI 환경에서는 Qt가 설치되어 있을 때 아래처럼 빌드할 수 있습니다.

```bash
qmake AirlineBooking.pro
make
./AirlineBooking
```

Windows + Visual Studio/Qt 환경에서는 Qt VS Tools 또는 Qt Creator 사용을 권장합니다.
