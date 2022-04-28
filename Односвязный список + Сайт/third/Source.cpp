#include <iostream>
#include <fstream>
#include <string> 
#include <Windows.h>
#include "Third.h"
using namespace std;
void show(List* head);

void fill_list(List*& head) {
	ifstream fin("List.txt");
	char buff[100];
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin.getline(buff, 100);
			add_by_order(head, buff);
		}
	}
	else {
		cout << "Файл не открыт";
	}
	fin.close();
}

void fout_file(string str) {
	ofstream fout;
	fout.open("List.txt", std::ios::app);
	if (fout.is_open()) {
		fout << endl << str;
	}
	else {
		cout << "Файл не открыт";
	}
	fout.close();
}

void check(string str) {
	ifstream fin("List.txt");
	char buff[100];
	int count = 0;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin.getline(buff, 100);
			if (buff == str) count++;
		}
		if (count == 0) fout_file(str);
	}
	else {
		cout << "Файл не открыт";
	}
	fin.close();
}

void enter_list() {
	List* head = nullptr;
	fill_list(head);
	show(head);
}

void show_content() {
	cout << "<h2>"
		"<form  method = 'get' action = 'third.cgi'>"
		"<p>"
		"<font color = 'white'><input placeholder = 'Введите слово' name = 'list'><input type = 'submit' value = 'Отправить'>"
		"</p>"
		"</form>"
		"</h2>";
	char* data = nullptr;
	get_form_data(data);
	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "list", data);
		check(value);
		enter_list();
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
	cout << "<h1 align = 'center'>Словарь";
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