#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include "AirportGraph.h"
#include "MapWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAirportClicked(int id);
    void onFlightClicked(QListWidgetItem* item);

private:
    void setupGraph();
    void setupUI();

    AirportGraph* graph;
    MapWidget*    mapWidget;

    QLabel*      airportNameLabel;
    QLabel*      airportGuideLabel;
    QLabel*      depCountLabel;    // "♦ 출발 항공편 (N건)"
    QListWidget* departureList;
    QLabel*      arrCountLabel;    // "↓ 도착 항공편 (N건)"
    QListWidget* arrivalList;

    int currentAirportId;
};
