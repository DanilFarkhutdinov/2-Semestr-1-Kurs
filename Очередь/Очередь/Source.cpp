#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "Queuer.h"
using namespace std;
void enqueue(queue*& q, string n, string g, int a, string w, int s, string p);
void Show(queue*& q, string filename);
bool dequeue(queue*& q, man& human);
void reading_file(queue*&kredit, queue*& vklad) {
	fstream fin("input.txt");
	if (fin.is_open()) {
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
			string purp = purpose;
			if (purp == "Kredit") {
				enqueue(kredit, name, gender, age, workplace, salary, purpose);
			}
			else {
				enqueue(vklad, name, gender, age, workplace, salary, purpose);
			}
		}
		fin.close();
	}
	else {
		cout << "‘айл не открыт!";
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	man human;
	queue* kredit = new queue;
	queue* vklad = new queue;
	reading_file(kredit, vklad);
	Show(kredit, " редит.txt");
	Show(vklad, "¬клад.txt");
	return 0;
}