#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QMessageBox>
#include <QLocale>
#include <QStatusBar>

// ---- 가격 포맷: 85000 → "₩85,000" ----
static QString fmtPrice(int price) {
    return "₩" + QLocale(QLocale::Korean).toString(price);
}

// ---- 시간 포맷: 90분 → "1시간 30분" ----
static QString fmtTime(int min) {
    return QString("%1시간 %2분").arg(min / 60).arg(min % 60);
}

// ============================================================
//  공항 10개 · 항공편 28개 (노드·간선 하드코딩)
// ============================================================
// 이 지도는 태평양 중심 투영 (중심 경도 약 160°E)
// 공항 좌표: 이미지 상 실제 위치 기준으로 수동 보정
void MainWindow::setupGraph() {
    graph = new AirportGraph();

    //              코드     이름        mapX   mapY
    // 지도 왼쪽: 유럽, 아프리카
    graph->addAirport("LHR", "런던",      0.175f, 0.215f);  // 0  유럽 왼쪽
    // 중앙 상단: 아시아
    graph->addAirport("PEK", "베이징",    0.520f, 0.255f);  // 1
    graph->addAirport("GMP", "김포",      0.555f, 0.248f);  // 2  (ICN 위)
    graph->addAirport("ICN", "인천",      0.555f, 0.272f);  // 3
    graph->addAirport("NRT", "나리타",    0.585f, 0.270f);  // 4
    graph->addAirport("PUS", "부산",      0.568f, 0.298f);  // 5  (ICN 아래)
    graph->addAirport("CJU", "제주",      0.556f, 0.318f);  // 6  (PUS 아래)
    graph->addAirport("HKG", "홍콩",      0.532f, 0.358f);  // 7
    graph->addAirport("SIN", "싱가포르",  0.512f, 0.432f);  // 8
    // 오른쪽: 북미 (태평양 건너편)
    graph->addAirport("LAX", "LA",        0.888f, 0.305f);  // 9
    graph->addAirport("JFK", "뉴욕",      0.940f, 0.262f);  // 10

    // 항공편 (편명, 항공사, 출발, 도착, 가격, 분)
    // ICN(3) 출발 국제선
    graph->addFlight("KE001","대한항공",  3, 4,  280000, 150); // ICN→NRT
    graph->addFlight("OZ201","아시아나",  3, 4,  260000, 150);
    graph->addFlight("KE005","대한항공",  3, 1,  230000, 130); // ICN→PEK
    graph->addFlight("KE011","대한항공",  3, 7,  350000, 230); // ICN→HKG
    graph->addFlight("KE021","대한항공",  3, 8,  480000, 360); // ICN→SIN
    graph->addFlight("KE031","대한항공",  3, 9,  850000, 540); // ICN→LAX
    graph->addFlight("OZ271","아시아나",  3, 9,  820000, 540);
    graph->addFlight("KE041","대한항공",  3, 0,  980000, 720); // ICN→LHR
    // ICN(3) 도착
    graph->addFlight("KE002","대한항공",  4, 3,  280000, 150);
    graph->addFlight("KE006","대한항공",  1, 3,  230000, 130);
    graph->addFlight("KE012","대한항공",  7, 3,  350000, 230);
    graph->addFlight("KE022","대한항공",  8, 3,  480000, 360);
    graph->addFlight("KE032","대한항공",  9, 3,  850000, 540);
    graph->addFlight("KE042","대한항공",  0, 3,  980000, 720);
    // 국내선 GMP(2) ↔ PUS(5) / CJU(6)
    graph->addFlight("KE1201","대한항공", 2, 5,   85000,  55);
    graph->addFlight("KE1202","대한항공", 5, 2,   85000,  55);
    graph->addFlight("KE1211","대한항공", 2, 6,   75000,  60);
    graph->addFlight("KE1212","대한항공", 6, 2,   75000,  60);
    graph->addFlight("BX201","에어부산",  5, 6,   65000,  50);
    graph->addFlight("BX202","에어부산",  6, 5,   65000,  50);
    // NRT(4) 출발
    graph->addFlight("JL031","일본항공",  4, 7,  420000, 250);
    graph->addFlight("JL041","일본항공",  4, 8,  650000, 420);
    // HKG(7) ↔ SIN(8)
    graph->addFlight("CX751","캐세이퍼시픽",7, 8, 280000, 210);
    graph->addFlight("CX752","캐세이퍼시픽",8, 7, 280000, 210);
    // 태평양/대서양
    graph->addFlight("BA269","영국항공",  0, 9,  750000, 660); // LHR→LAX
    graph->addFlight("AA100","아메리칸",  9, 0,  730000, 660);
    graph->addFlight("AA200","아메리칸",  9,10,  270000, 340); // LAX→JFK
    graph->addFlight("AA201","아메리칸", 10, 9,  270000, 340);
}

// ============================================================
//  UI 구성
// ============================================================
void MainWindow::setupUI() {
    setWindowTitle("항공권 예매 시스템");
    resize(1200, 700);

    auto* central = new QWidget(this);
    auto* hLayout = new QHBoxLayout(central);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    setCentralWidget(central);

    // 지도
    mapWidget = new MapWidget(graph, central);
    connect(mapWidget, &MapWidget::airportClicked, this, &MainWindow::onAirportClicked);
    hLayout->addWidget(mapWidget, 2);

    // 정보 패널
    auto* panel = new QFrame(central);
    panel->setFixedWidth(390);
    panel->setStyleSheet("background:#16213E;");
    auto* vLayout = new QVBoxLayout(panel);
    vLayout->setContentsMargins(14, 14, 14, 10);
    vLayout->setSpacing(5);
    hLayout->addWidget(panel);

    // 공항 이름
    airportNameLabel = new QLabel("공항을 클릭하세요", panel);
    airportNameLabel->setStyleSheet(
        "font-size:15px;font-weight:bold;color:#E0E0E0;");
    vLayout->addWidget(airportNameLabel);

    // 안내 문구
    airportGuideLabel = new QLabel("좌측 지도에서 공항(버튼)을 클릭하세요.", panel);
    airportGuideLabel->setStyleSheet("font-size:10px;color:#9E9E9E;");
    vLayout->addWidget(airportGuideLabel);

    auto* sep = new QFrame(panel);
    sep->setFrameShape(QFrame::HLine);
    sep->setStyleSheet("color:#2D3561;margin-top:2px;");
    vLayout->addWidget(sep);

    // 출발 항공편 헤더
    depCountLabel = new QLabel("♦ 출발 항공편", panel);
    depCountLabel->setStyleSheet(
        "font-size:11px;color:#64B5F6;font-weight:bold;margin-top:2px;");
    vLayout->addWidget(depCountLabel);

    departureList = new QListWidget(panel);
    departureList->setStyleSheet(
        "QListWidget{background:#0D1117;border:1px solid #2D3561;"
        "color:#E0E0E0;font-size:11px;border-radius:3px;}"
        "QListWidget::item{padding:4px 6px;border-bottom:1px solid #1A1F36;}"
        "QListWidget::item:hover{background:#1E3A5F;cursor:pointer;}");
    departureList->setMaximumHeight(190);
    connect(departureList, &QListWidget::itemClicked,
            this, &MainWindow::onFlightClicked);
    vLayout->addWidget(departureList);

    // 도착 항공편 헤더
    arrCountLabel = new QLabel("↓ 도착 항공편", panel);
    arrCountLabel->setStyleSheet(
        "font-size:11px;color:#81C784;font-weight:bold;margin-top:4px;");
    vLayout->addWidget(arrCountLabel);

    arrivalList = new QListWidget(panel);
    arrivalList->setStyleSheet(departureList->styleSheet());
    arrivalList->setMaximumHeight(190);
    connect(arrivalList, &QListWidget::itemClicked,
            this, &MainWindow::onFlightClicked);
    vLayout->addWidget(arrivalList);

    vLayout->addStretch();
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), currentAirportId(-1)
{
    setupGraph();
    setupUI();

    // 하단 상태 표시줄
    statusBar()->setStyleSheet("color:#9E9E9E;font-size:9px;");
    statusBar()->showMessage(
        "공항 아이콘을 클릭하면 출발/도착 항공편이 표시됩니다");
}

MainWindow::~MainWindow() { delete graph; }

// ---- 슬롯 -------------------------------------------------------

void MainWindow::onAirportClicked(int id) {
    if (id < 0 || id >= graph->nodeCount) return;
    currentAirportId = id;

    const Airport& ap = graph->airports[id];
    airportNameLabel->setText(
        QString("%1 (%2)").arg(ap.name).arg(ap.code));
    airportGuideLabel->setText("아래 항공편을 클릭하면 예매합니다.");

    // ---- 출발 항공편 ----
    departureList->clear();
    auto deps = graph->getDepartures(id);
    for (int idx : deps) {
        const Flight& f  = graph->flights[idx];
        const Airport& to = graph->airports[f.to];
        // 형식: [편명] 항공사  →  도착코드 (도착명)  ·  ₩가격  ·  시간
        QString txt = QString("[%1] %2  →  %3 (%4)  ·  %5  ·  %6")
            .arg(f.flightNo)
            .arg(f.airline)
            .arg(to.code)
            .arg(to.name)
            .arg(fmtPrice(f.price))
            .arg(fmtTime(f.duration));
        auto* item = new QListWidgetItem(txt, departureList);
        item->setData(Qt::UserRole, idx);
    }
    depCountLabel->setText(
        QString("♦ 출발 항공편 (%1건)").arg(deps.size()));

    // ---- 도착 항공편 ----
    arrivalList->clear();
    auto arrs = graph->getArrivals(id);
    for (int idx : arrs) {
        const Flight& f    = graph->flights[idx];
        const Airport& from = graph->airports[f.from];
        // 형식: [편명] 항공사  →  출발코드 (출발명)  ·  ₩가격  ·  시간
        QString txt = QString("[%1] %2  →  %3 (%4)  ·  %5  ·  %6")
            .arg(f.flightNo)
            .arg(f.airline)
            .arg(from.code)
            .arg(from.name)
            .arg(fmtPrice(f.price))
            .arg(fmtTime(f.duration));
        auto* item = new QListWidgetItem(txt, arrivalList);
        item->setData(Qt::UserRole, idx);
    }
    arrCountLabel->setText(
        QString("↓ 도착 항공편 (%1건)").arg(arrs.size()));
}

void MainWindow::onFlightClicked(QListWidgetItem* item) {
    int idx = item->data(Qt::UserRole).toInt();
    const Flight& f = graph->flights[idx];
    QMessageBox::information(this, "예매 완료",
        QString("예매가 완료되었습니다.\n\n"
                "항공편: %1 (%2)\n"
                "구간: %3 → %4\n"
                "가격: %5\n"
                "소요 시간: %6")
        .arg(f.flightNo)
        .arg(f.airline)
        .arg(graph->airports[f.from].code)
        .arg(graph->airports[f.to].code)
        .arg(fmtPrice(f.price))
        .arg(fmtTime(f.duration)));
}
