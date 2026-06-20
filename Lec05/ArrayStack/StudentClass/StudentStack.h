#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

#define MAX_STRING 100
#define MAX_STACK_SIZE 100

class Student {
	int id;
	char name[MAX_STRING];
	char dept[MAX_STRING];

public:
	Student(int i = 0, const char* n = "", const char* d = "") { set(i, n, d); }
	void set(int i, const char* n, const char* d) {
		id = i;
		strcpy(name, n);
		strcpy(dept, d);
	}
	void display() {
		printf("학번:%-15d 성명:%-10s 학과:%-20s\n", id, name, dept);
	}
};

class StudentStack {
    int top;
    Student data[MAX_STACK_SIZE];
public:
    StudentStack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE - 1; }
    void push(Student e) {
        if (isFull()) return;
        data[++top] = e;
    }
    Student pop() {
        if (isEmpty()) return Student();
        return data[top--];
    }
    void display() {
        printf("[전체 학생수 = %d]\n", top + 1);
        for (int i = 0; i <= top; i++) data[i].display();
    }
};