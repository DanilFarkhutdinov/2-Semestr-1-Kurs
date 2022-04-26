#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include "Second.h"
using namespace std;
void enqueue(queue*& q, string n, string g, int a, string w, int s, string p);
void Show(queue*& q, string filename, string purp);
bool dequeue(queue*& q, man& human);
void clear(queue*& q);
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
		cout << "<p>Kredit:</p>";
		Show(kredit, "Кредит.txt", purp);
		cout << "<p>Vklad:</p>";
		Show(vklad, "Вклад.txt", purp);
		fin.close();
	}
	else {
		cout << "Файл не открыт!";
	}
}
void show_content() {
	cout << "<h2>"
		"<form  method = 'get' action = 'second.cgi'>"
		"<p>"
		"<font color = 'white'>Прикрепите файл: <input type = 'file' name = 'queue' accept = '*/txt'><input type = 'submit' value = 'Отправить'>"
		"</p>"
		"</form>"
		"</h2>";
	char* data = nullptr;
	queue* kredit = new queue;
	queue* vklad = new queue;
	get_form_data(data);
	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "queue", data);
		reading_queue(kredit, vklad);
	}
}
void show_menu() {
	ifstream fin_m("menu.txt");
	if (fin_m.is_open()) {
		auto sz = 1024;
		auto buff_m = new char[sz];
		while (!fin_m.eof()) {
			fin_m.getline(buff_m, sz);
			char* name;
			char* addrr = strtok_s(buff_m, " ", &name);
			cout << "<p>"
				"<a href='" << addrr << "'>" << "<font color = 'white''>" <<
				name << "</a>"
				"</p>";
		}
	}
	else {
		cout << "Файл не открыт";
	}
	fin_m.close();
}
void show_header() {
	cout << "<h1 align = 'center'>Очередь клиентов";
}
void reading_file(ifstream& fin) {
	auto sz = 1024;
	char* buff = new char[sz];
	while (!fin.eof()) {
		fin.getline(buff, sz);
		cout << buff << endl;
		if (!strcmp(buff, "<!--Content-->")) {
			show_content();
		}
		else {
			if (!strcmp(buff, "<!--Menu-->")) {
				show_menu();
			}
			else {
				if (!strcmp(buff, "<!--Header-->")) {
					show_header();
				}
			}
		}
	}
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Content-type: text/html; charset-1251\n\n";
	ifstream fin("file.txt");
	if (!fin.is_open()) {
		cout << "Файл не открыт";
	}
	else {
		reading_file(fin);
	}
	fin.close();
	return 0;
}