#pragma once
#include <iostream>
using namespace std;
struct man {
	string name;
	string gender;
	int age;
	string workplace;
	int salary;
	string purpose;
};
struct element {
	man m;
	element* next = nullptr;
};
struct queue {
	element* head = nullptr;
	element* tail = nullptr;
	size_t size = 0;
};
void enqueue(queue*& q, string n, string g, int a, string w, int s, string p);

man create_elem(string n, string g, int a, string w, int s, string p);

bool dequeue(queue*& q, man& m);

void clear(queue*& q);