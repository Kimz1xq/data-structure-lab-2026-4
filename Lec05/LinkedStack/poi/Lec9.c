#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct stackNode {
	int data;
	struct stackNode* link;

}stackNode;

stackNode* top;

void push(int item) {
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));

	temp->data = item;
	temp->link = top;
	top = temp;
}

int pop() {
	int item;
	stackNode* temp = top;

	if (top != NULL) {
		item = temp->data;
		top = temp -> link;
		free(temp);
		return item;
	}
}

void printStack() {
	stackNode* p = top;
	printf("\n STACK[");
}