#include "CircularQueue.h"

int main() {
    CircularQueue q;
    for (int i = 1; i <= 5; i++)
        q.enqueue(i * 10);
    q.display();
    printf("dequeue: %d\n", q.dequeue());
    printf("dequeue: %d\n", q.dequeue());
    q.display();
    q.enqueue(60);
    q.enqueue(70);
    q.display();
    return 0;
}
