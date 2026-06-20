#pragma once
#include <QString>
#include <vector>
#include <map>
#include <utility>

// =============================================
//  Airport: 공항(노드) 정보 구조체
// =============================================
struct Airport {
    QString code;   // IATA 코드 (예: ICN)
    QString name;   // 공항명 (예: 인천국제공항)
    float   mapX;   // 세계지도 상 상대 X 좌표 (0.0~1.0)
    float   mapY;   // 세계지도 상 상대 Y 좌표 (0.0~1.0)
};

// =============================================
//  Flight: 항공편(간선) 정보 구조체
// =============================================
struct Flight {
    QString flightNo;  // 항공편 번호 (예: KE001)
    QString airline;   // 항공사명
    int     from;      // 출발 공항 인덱스
    int     to;        // 도착 공항 인덱스
    int     price;     // 가격 (원)
    int     duration;  // 소요 시간 (분)
};

// =============================================
//  AirportGraph: 방향 그래프 (인접 행렬 기반)
//  - 노드: 공항 (Airport)
//  - 간선: 항공편 (Flight), 방향 있음 (출발→도착)
// =============================================
class AirportGraph {
public:
    std::vector<Airport> airports;
    std::vector<Flight>  flights;
    int nodeCount;

    AirportGraph() : nodeCount(0) {}

    int addAirport(const QString& code, const QString& name, float x, float y) {
        int id = (int)airports.size();
        airports.push_back({code, name, x, y});
        nodeCount++;
        for (auto& row : adjMatrix) row.push_back(-1);
        adjMatrix.push_back(std::vector<int>(nodeCount, -1));
        return id;
    }

    void addFlight(const QString& no, const QString& airline,
                   int from, int to, int price, int duration) {
        int idx = (int)flights.size();
        flights.push_back({no, airline, from, to, price, duration});
        // 방향 그래프: from→to 방향만 등록
        // 동일 구간 복수 항공편을 지원하기 위해 리스트 기반으로 저장
        flightList[{from, to}].push_back(idx);
    }

    // 특정 공항에서 출발하는 항공편 인덱스 목록
    std::vector<int> getDepartures(int airportIdx) const {
        std::vector<int> result;
        for (int v = 0; v < nodeCount; v++) {
            auto key = std::make_pair(airportIdx, v);
            auto it = flightList.find(key);
            if (it != flightList.end())
                for (int idx : it->second) result.push_back(idx);
        }
        return result;
    }

    // 특정 공항에 도착하는 항공편 인덱스 목록
    std::vector<int> getArrivals(int airportIdx) const {
        std::vector<int> result;
        for (int v = 0; v < nodeCount; v++) {
            auto key = std::make_pair(v, airportIdx);
            auto it = flightList.find(key);
            if (it != flightList.end())
                for (int idx : it->second) result.push_back(idx);
        }
        return result;
    }

    bool hasRoute(int from, int to) const {
        return flightList.find({from, to}) != flightList.end();
    }

private:
    std::vector<std::vector<int>> adjMatrix;
    std::map<std::pair<int,int>, std::vector<int>> flightList;
};
