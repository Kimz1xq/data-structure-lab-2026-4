#include <iostream>
#include "AdjMatGraph.h" 

using namespace std;

int main() {
    AdjMatGraph g;

    // 4개의 정점을 생성하여 삽입 (A, B, C, D)
    for (int i = 0; i < 4; i++) {
        g.insertVertex('A' + i);
    }

    // 무방향 간선 삽입
    g.insertEdge(0, 1);
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    return 0;
}