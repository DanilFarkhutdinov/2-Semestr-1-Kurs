#include "cgi.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

bool is_get()
{
	size_t realsize;
	char* value = new char[5];
	getenv_s(&realsize, value, 5, "REQUEST_METHOD");
	bool res = !_strcmpi(value, "GET");
	delete[] value;
	return res;
}

size_t get_content_length()
{
	size_t realsize;
	char* value = new char[11];
	getenv_s(&realsize, value, 11, "CONTENT_LENGTH");
	size_t size;
	if (!realsize) size = 0;
	else sscanf_s(value, "%d", &size);
	delete[] value;
	return size;
}

void get_form_data(char*& data)
{
	delete[] data;
	if (is_get())
	{
		size_t realsize;
		char* value = new char[65536];
		getenv_s(&realsize, value, 65536, "QUERY_STRING");
		data = new char[realsize + 1];
		strcpy_s(data, realsize + 1, value);
		delete[] value;
	}
	else
	{
		size_t buf_size = get_content_length();
		data = new char[buf_size + 1];
		fread_s(
			data,
			buf_size + 1,
			sizeof(char),
			buf_size,
			stdin
		);
		data[buf_size] = 0;
	}
}

void get_param_value(char*& value, const char* param_name, const char* data)
{
	delete[] value;
	value = nullptr;
	char* str = _strdup(data);
	char* tmp = str;
	char* cont;
	while (char* part = strtok_s(tmp, "&", &cont))
	{
		tmp = nullptr;
		char* val;
		char* key = strtok_s(part, "=", &val);
		if (!_strcmpi(param_name, key))
		{
			str_decode(value, val);
			//value = _strdup(val);
			delete[] str;
			return;
		}
	}
	delete[] str;
	value = new char[1];
	value[0] = 0;
}

void str_decode(char*& dec_str, const char* enc_str)
{
	char* res = new char[strlen(enc_str) + 1];
	int i = 0, j = 0;
	while (enc_str[i])
	{
		if (enc_str[i] == '+')
		{
			res[j] = ' ';
		}
		else
		{
			if (enc_str[i] == '%')
			{
				char ch[3] = { enc_str[i + 1], enc_str[i + 2], 0 };
				int c;
				sscanf_s(ch, "%X", &c);
				res[j] = c;
				i += 2;
			}
			else
			{
				res[j] = enc_str[i];
			}
		}
		i++;
		j++;
	}
	res[j] = 0;
	size_t len = strlen(res) + 1;
	delete[] dec_str;
	dec_str = new char[len];
	strcpy_s(dec_str, len, res);
	delete[] res;
}

void push(elem*& stack, char exp) {
	auto* newel = new elem;
	newel->exp = exp;
	if (stack) newel->next = stack;
	stack = newel;
}
const char* peek(const elem* stack) {
	if (!stack) return nullptr;
	return &stack->exp;
}
bool pop(elem*& stack, char& exp) {
	if (!stack) return false;
	exp = stack->exp;
	auto* rem = stack;
	stack = stack->next;
	delete rem;
	return true;
}
void clear(elem*& top) {
	while (top) {
		auto* rem = top;
		top = top->next;
		delete rem;
	}
}
void fill_stack(elem*& stack, string str, int a) {
	push(stack, str[a]);
}
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
			cout << "<font color = 'white'><p>Неправильно введена первая скобка</p>" << endl;
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
							cout << "<font color = 'white'><p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
							break;
						}
					}
					else {
						if (str[i] == ']') {
							if (*peek(stack) == '[') {
								pop(stack, str[i]);
							}
							else {
								cout << "<font color = 'white'><p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
								break;
							}
						}
						else {
							if (str[i] == '}') {
								if (*peek(stack) == '{') {
									pop(stack, str[i]);
								}
								else {
									cout << "<font color = 'white'><p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
									break;
								}
							}
							else {
								if (str[i] == '>') {
									if (*peek(stack) == '<') {
										pop(stack, str[i]);
									}
									else {
										cout << "<font color = 'white'><p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
										break;
									}
								}
							}
						}
					}
				}
				else {
					cout << "<font color = 'white'><p>Скобка под номером " << i + 1 << " является ошибочной</p>" << endl;
				}
			}
		}
	}
	if (size % 2 != 0) {
		cout << "<font color = 'white'><p>Не хватает скобок</p>" << endl;
	}
	if (!stack) {
		cout << "<font color = 'white'><p>Скобки расставлены правильно</p>" << endl;
	}
	else {
		cout << "<font color = 'white'><p>Скобки расставлены неправильно</p>" << endl;
	}
}
void show_stack(elem* stack) {
	if (!stack) cout << "Стек пуст";
	else {
		auto* curr = stack;
		while (curr) {
			auto val = peek(curr);
			cout << *val << (curr->next ? ' ' : '\n');
			curr = curr->next;
		}
	}
}