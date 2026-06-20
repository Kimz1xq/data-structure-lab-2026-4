#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QPoint>
#include "AirportGraph.h"

// =============================================
//  MapWidget: 세계지도 위에 공항(노드)과 노선(간선)을
//  렌더링하는 커스텀 위젯
//
//  - 배경: world_map.jpg 로드, 없으면 단색으로 대체
//  - 노선: QPainter 선으로 표시
//  - 공항: QPushButton을 지도 위에 배치
//  - 창 크기 변경 시 resizeEvent()로 버튼 좌표 재계산
// =============================================
class MapWidget : public QWidget {
    Q_OBJECT
public:
    explicit MapWidget(AirportGraph* graph, QWidget* parent = nullptr);

signals:
    void airportClicked(int airportId);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

private:
    AirportGraph*             graph;
    QPixmap                   mapImage;
    std::vector<QPushButton*> airportButtons;

    QPoint getScreenPos(float relX, float relY) const;
    void   updateButtonPositions();
};
