#include "ArrayDeque.h"

int main() {
    ArrayDeque dq;
    dq.addRear(10);
    dq.addRear(20);
    dq.addRear(30);
    dq.display();
    dq.addFront(5);
    dq.display();
    printf("deleteFront: %d\n", dq.deleteFront());
    printf("deleteRear:  %d\n", dq.deleteRear());
    dq.display();
    return 0;
}
