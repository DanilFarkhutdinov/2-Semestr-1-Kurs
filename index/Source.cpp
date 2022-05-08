#include <iostream>
#include <fstream>
#include <Windows.h>
#include "cgi.h"
#include "Queue.h"
using namespace std;
void fill_stack(elem*& stack, string str, int a);
void show_stack(elem* stack);
void mistakes(string str);
void reading_queue(queue*& kredit, queue*& vklad);
void check(string str);
void enter_list();
char* GetValueOfParam(const char* strParam){
	char* value = nullptr;
	char* data = nullptr;
	get_form_data(data);
	if (data && strlen(data) > 0)
	{
		get_param_value(value, strParam, data);
	}
	return value;
}
void show_content(char* nameofFile) {
	ifstream fin(nameofFile);
	auto sz = 1024;
	char* buff = new char[sz];
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin.getline(buff, sz);
			cout << buff << endl;
		}
		fin.close();
		delete[] buff;
	}
	char* content = GetValueOfParam("content");
	if (!strcmp(content, "task_1")) {
		char* value = GetValueOfParam("exp");
		cout << "<font color = 'white'><p>" << value << "</p>";
		mistakes(value);
	}
	if (!strcmp(content, "task_2")) {
		queue* kredit = new queue;
		queue* vklad = new queue;
		char* value = GetValueOfParam("queue");
		reading_queue(kredit, vklad);
	}
	if (!strcmp(content, "task_3")) {
		char* value = GetValueOfParam("list");
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
			cout <<
				"<form method  = 'get'>"
				"<p>" << "<button href = " << addrr <<" value = " << addrr << " name = 'menu' type = 'submit'" <<"<font>" << name <<"</font>" << "</button>" << "</p>"
				"</form>"
				 << endl;
		}
		delete[] buff_m;
	}
	else {
		cout << "Файл не открыт";
	}
	fin_m.close();
}
void show_header() {
	cout << "<h1 align = 'center'>Мой сайт";
}
void reading_file(ifstream& fin) {
	auto sz = 1024;
	char* buff = new char[sz];
	char* name = GetValueOfParam("menu");
	while (!fin.eof()) {
		fin.getline(buff, sz);
		cout << buff << endl;
		if (!strcmp(buff, "<!--Content-->")) {
			show_content(name);
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
	delete[] buff;
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