#include <iostream>
#include <stack>
#include <deque>
#include "Location2D.h"

using namespace std;

const int MAZE_SIZE = 6;

//  원본 미로 데이터
char original_map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

//  탐색에 사용할 복사본 미로
char map_data[MAZE_SIZE][MAZE_SIZE];

//  미로 초기 상태로 리셋
void initMap() {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            map_data[i][j] = original_map[i][j];
        }
    }
}

//  (r, c)가 미로 내에 있고 갈 수 있는 위치인지 검사
bool isValidLoc(int r, int c) {
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
    else return map_data[r][c] == '0' || map_data[r][c] == 'x';
}

// [실습 1] STL stack을 써서 DFS로 탐색

void practice01_DFS_stack() {
    initMap(); // 미로 초기화
    stack<Location2D> locStack;
    locStack.push(Location2D(1, 0));

    while (!locStack.empty()) {
        Location2D here = locStack.top();
        locStack.pop();
        int r = here.row; int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map_data[r][c] == 'x') {
            printf("\n=> 미로 탐색 성공\n");
            return;
        }
        else {
            map_data[r][c] = '.';
            if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
        }
    }
    printf("\n=> 미로 탐색 실패\n");
}

// [실습 2] STL deque를 써서 DFS로 탐색 (스택처럼 활용)

void practice02_DFS_deque() {
    initMap(); // 미로 초기화
    deque<Location2D> locDeque;
    locDeque.push_front(Location2D(1, 0));

    while (!locDeque.empty()) {
        Location2D here = locDeque.front();
        locDeque.pop_front();
        int r = here.row; int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map_data[r][c] == 'x') {
            printf("\n=> 미로 탐색 성공\n");
            return;
        }
        else {
            map_data[r][c] = '.';
            // 스택과 동일한 순서를 유지하기 위해 front에 넣음
            if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
        }
    }
    printf("\n=> 미로 탐색 실패\n");
}

// [실습 3] STL deque를 써서 BFS로 탐색 (큐처럼 활용)

void practice03_BFS_deque() {
    initMap(); // 미로 초기화
    deque<Location2D> locDeque;
    locDeque.push_back(Location2D(1, 0)); // 큐는 뒤에서(back) 삽입

    while (!locDeque.empty()) {
        Location2D here = locDeque.front();
        locDeque.pop_front(); // 큐는 앞에서(front) 삭제
        int r = here.row; int c = here.col;

        printf("(%d,%d) ", r, c);

        if (map_data[r][c] == 'x') {
            printf("\n=> 미로 탐색 성공\n");
            return;
        }
        else {
            map_data[r][c] = '.';
            // Queue처럼 작동하도록 뒤로 밀어넣음 (push_back)
            if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
        }
    }
    printf("\n=> 미로 탐색 실패\n");
}

// 메인 함수

int main() {
    cout << "[실습 1] STL stack을 써서 DFS로 탐색\n" << endl;
    practice01_DFS_stack();
    cout << endl;

    cout << "[실습 2] STL deque를 써서 DFS로 탐색\n" << endl;
    practice02_DFS_deque();
    cout << endl;

    cout << "[실습 3] STL deque를 써서 BFS로 탐색\n" << endl;
    practice03_BFS_deque();
    cout << endl;

    return 0;
}