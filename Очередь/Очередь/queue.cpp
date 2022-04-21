#include <iostream>
#include <fstream>
#include "Queuer.h"
using namespace std;
void enqueue(queue*& q, string n, string g, int a, string w, int s, string p) {
	man human = create_elem(n, g, a, w, s, p);
	elem* newel = new elem;
	newel->m = human;
	if (q->size == 0) {
		q->head = q->tail = newel;
	}
	else {
		q->tail->next = newel;
		q->tail = newel;
	}
	q->size++;
}
bool dequeue(queue*& q, man& human) {
	if (q->size == 0) {
		return false;
	}
	elem* rem = q->head;
	human = q->head->m;
	q->head = q->head->next;
	delete rem;
	q->size--;
	return true;
}
man create_elem(string n, string g, int a, string w, int s, string p) {
	man m;
	m.name = n;
	m.age = a;
	m.gender = g;
	m.workplace = w;
	m.salary = s;
	m.purpose = p;
	return m;
}
void Show(queue*& q, string filename) {
	man human;
	ofstream fout(filename);
	while (dequeue(q, human)) {
		fout << human.name << " " << human.age << " " << human.gender << " " << human.workplace << " " << human.salary << " " << human.purpose << endl;
	}
	fout.close();
}
void clear(queue*& q) {
	while (q->size > 0) {
		elem* rem = q->head;
		q->head = q->head->next;
		q->size--;
		delete rem;
	}
}