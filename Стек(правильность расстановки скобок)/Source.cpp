#include <iostream>
#include <string.h>
#include "Stack.h"
using namespace std;
void fill_stack(elem*& stack, string str, int a);
void show_stack(elem* stack);
void mistakes(elem*& stack, string str) {
	int size = 0;
	int a = 0;
	for (int j = 0; j < str.length(); j++) {
		if (str[j] == '(' || str[j] == '[' || str[j] == '{' || str[j] == '<' || str[j] == ')' || str[j] == ']' || str[j] == '}' || str[j] == '>') {
			size++;
		}
	}
	for (int i = 0; i < str.length(); i++) {
		if (str[0] == ')' || str[0] == ']' || str[0] == '}' || str[0] == '>') {
			cout << "Неправильно введена первая скобка" << endl;
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
							cout << "Скобка под номером " << i + 1 << " является ошибочной" << endl;
							break;
						}
					}
					else {
						if (str[i] == ']') {
							if (*peek(stack) == '[') {
								pop(stack, str[i]);
							}
							else {
								cout << "Скобка под номером " << i + 1 << " является ошибочной" << endl;
								break;
							}
						}
						else {
							if (str[i] == '}') {
								if (*peek(stack) == '{') {
									pop(stack, str[i]);
								}
								else {
									cout << "Скобка под номером " << i + 1 << " является ошибочной" << endl;
									break;
								}
							}
							else {
								if (str[i] == '>') {
									if (*peek(stack) == '<') {
										pop(stack, str[i]);
									}
									else {
										cout << "Скобка под номером " << i + 1 << " является ошибочной" << endl;
										break;
									}
								}
							}
						}
					}
				}
				else {
					cout << "Скобка под номером " << i + 1 << " является ошибочной" << endl;
				}
			}
		}
	}
	if (size % 2 != 0) {
		cout << "Не хватает скобок" << endl;
	}
	if (!stack) {
		cout << "Скобки расставлены правильно" << endl;
	}
	else {
		cout << "Скобки расставлены неправильно" << endl;
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	elem* stack = nullptr;
	string str;
	cout << "Введите выражение: ";
	cin >> str;
	int length = str.length();
	mistakes(stack, str);
	clear(stack);
	return 0;
}