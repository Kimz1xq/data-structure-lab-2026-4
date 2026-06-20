#pragma once
#include <cstdio>
#include <cstdlib>

#define MAX_DEQUE_SIZE 100

inline void dequeError(const char* msg) {
    printf("%s\n", msg);
    exit(1);
}

class ArrayDeque {
    int front, rear;
    int data[MAX_DEQUE_SIZE];
public:
    ArrayDeque() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull()  { return (rear + 1) % MAX_DEQUE_SIZE == front; }
    int  size()    { return (rear - front + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE; }
    void addRear(int val) {
        if (isFull()) dequeError("덱 포화 에러");
        rear = (rear + 1) % MAX_DEQUE_SIZE;
        data[rear] = val;
    }
    int deleteFront() {
        if (isEmpty()) dequeError("덱 공백 에러");
        front = (front + 1) % MAX_DEQUE_SIZE;
        return data[front];
    }
    void addFront(int val) {
        if (isFull()) dequeError("덱 포화 에러");
        data[front] = val;
        front = (front - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
    }
    int deleteRear() {
        if (isEmpty()) dequeError("덱 공백 에러");
        int val = data[rear];
        rear = (rear - 1 + MAX_DEQUE_SIZE) % MAX_DEQUE_SIZE;
        return val;
    }
    int getFront() {
        if (isEmpty()) dequeError("덱 공백 에러");
        return data[(front + 1) % MAX_DEQUE_SIZE];
    }
    int getRear() {
        if (isEmpty()) dequeError("덱 공백 에러");
        return data[rear];
    }
    void display() {
        printf("[덱 항목의 수 = %2d] front->rear: ", size());
        for (int i = (front + 1) % MAX_DEQUE_SIZE; i != (rear + 1) % MAX_DEQUE_SIZE; i = (i + 1) % MAX_DEQUE_SIZE)
            printf("<%2d>", data[i]);
        printf("\n");
    }
};
