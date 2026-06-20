#pragma once
#include <cstdio>
#include <cstdlib>

#define MAX_QUEUE_SIZE 100

inline void queueError(const char* msg) {
    printf("%s\n", msg);
    exit(1);
}

class CircularQueue {
    int front, rear;
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull()  { return (rear + 1) % MAX_QUEUE_SIZE == front; }
    int  size()    { return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }
    void enqueue(int val) {
        if (isFull()) queueError("큐 포화 에러");
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = val;
    }
    int dequeue() {
        if (isEmpty()) queueError("큐 공백 에러");
        front = (front + 1) % MAX_QUEUE_SIZE;
        return data[front];
    }
    int peek() {
        if (isEmpty()) queueError("큐 공백 에러");
        return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    void display() {
        printf("[큐 항목의 수 = %2d] ==> ", size());
        for (int i = (front + 1) % MAX_QUEUE_SIZE; i != (rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE)
            printf("<%2d>", data[i]);
        printf("\n");
    }
};
