#pragma once
#include <iostream>
using namespace std;
bool is_get();

void get_form_data(char*& data);

void get_param_value(char*& value, const char* param_name, const char* data);

void str_decode(char*& dec_str, const char* enc_str);

struct man {
	string name;
	string gender;
	int age;
	string workplace;
	int salary;
	string purpose;
};
struct elem {
	man m;
	elem* next = nullptr;
};
struct queue {
	elem* head = nullptr;
	elem* tail = nullptr;
	size_t size = 0;
};
void enqueue(queue*& q, string n, string g, int a, string w, int s, string p);

man create_elem(string n, string g, int a, string w, int s, string p);

bool dequeue(queue*& q, man& m);

void clear(queue*& q);
