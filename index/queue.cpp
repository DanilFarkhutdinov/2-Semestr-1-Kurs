#include "Queue.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

void enqueue(queue*& q, string n, string g, int a, string w, int s, string p) {
	man human = create_elem(n, g, a, w, s, p);
	element* newel = new element;
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
	element* rem = q->head;
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
void Show(queue*& q, string filename, string purp) {
	man human;
	while (dequeue(q, human)) {
		cout << "<font color = 'white'><p>" << human.name << " " << human.age << " " << human.gender << " " << human.workplace << " " << human.salary << " " << human.purpose << "</p>" << endl;
	}
}
void reading_queue(queue*& kredit, queue*& vklad) {
	fstream fin("input.txt");
	if (fin.is_open()) {
		string purp;
		while (!fin.eof()) {
			char* man = new char[100];
			fin.getline(man, 100);
			char* name = new char[50];
			char* gender = new char[10];
			int age;
			char* workplace = new char[50];
			int salary;
			char* purpose = new char[10];
			sscanf_s(man, "%s%s%d%s%d%s", name, 50, gender, 10, &age, workplace, 50, &salary, purpose, 10);
			purp = purpose;
			if (purp == "Kredit") {
				enqueue(kredit, name, gender, age, workplace, salary, purpose);
			}
			else {
				enqueue(vklad, name, gender, age, workplace, salary, purpose);
			}
		}
		cout << "<font color = 'white'><p>Kredit:</p>";
		Show(kredit, " редит.txt", purp);
		cout << "<font color = 'white'><p>Vklad:</p>";
		Show(vklad, "¬клад.txt", purp);
		fin.close();
	}
	else {
		cout << "‘айл не открыт!";
	}
}
void clear(queue*& q) {
	while (q->size > 0) {
		element* rem = q->head;
		q->head = q->head->next;
		q->size--;
		delete rem;
	}
}