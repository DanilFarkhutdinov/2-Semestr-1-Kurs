#include <iostream>
#include <fstream>
#include <Windows.h>
#include "cgi.h"
using namespace std;
void fill_stack(elem*& stack, string str, int a);
void show_stack(elem* stack);
void mistakes(string str) {
	elem* stack = nullptr;
	int size = 0;
	int a = 0;
	for (int j = 0; j < str.length(); j++) {
		if (str[j] == '(' || str[j] == '[' || str[j] == '{' || str[j] == '<' || str[j] == ')' || str[j] == ']' || str[j] == '}' || str[j] == '>') {
			size++;
		}
	}
	for (int i = 0; i < str.length(); i++) {
		if (str[0] == ')' || str[0] == ']' || str[0] == '}' || str[0] == '>') {
			cout << "<p>Неправильно введена первая скобка</p>" << endl;
			a = i;
			fill_stack(stack, str, a);
			break;
		}
		else {
			if (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == '<') {
				a = i;
				fill_stack(stack, str, a);
			}
			else {
				if (stack) {
					if (str[i] == ')') {
						if (*peek(stack) == '(') {
							pop(stack, str[i]);
						}
						else {
							cout << "<p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
							break;
						}
					}
					else {
						if (str[i] == ']') {
							if (*peek(stack) == '[') {
								pop(stack, str[i]);
							}
							else {
								cout << "<p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
								break;
							}
						}
						else {
							if (str[i] == '}') {
								if (*peek(stack) == '{') {
									pop(stack, str[i]);
								}
								else {
									cout << "<p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
									break;
								}
							}
							else {
								if (str[i] == '>') {
									if (*peek(stack) == '<') {
										pop(stack, str[i]);
									}
									else {
										cout << "<p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
										break;
									}
								}
							}
						}
					}
				}
				else {
					cout << "<p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
				}
			}
		}
	}
	if (size % 2 != 0) {
		cout << "<p>Не хватает скобок</p>" << endl;
	}
	if (!stack) {
		cout << "<p>Скобки расставлены правильно</p>" << endl;
	}
	else {
		cout << "<p>Скобки расставлены неправильно</p>" << endl;
	}
}
void show_content() {
	cout << "<h2>"
		"<form  method = 'get' action = 'index.cgi'>"
		"<p>"
		"<font color = 'white'><input placeholder = 'Введите выражение' name = 'exp'><input type = 'submit' value = 'Отправить'>"
		"</p>"
		"</form>"
		"</h2>";
	char* data = nullptr;
	get_form_data(data);
	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "exp", data);
		cout << "<p>" << value << "</p>";
		mistakes(value);
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
	cout << "<h1 align = 'center'>Проверка правильности расстановки скобок";
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