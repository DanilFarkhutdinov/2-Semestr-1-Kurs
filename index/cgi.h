#pragma once
bool is_get();

void get_form_data(char*& data);

void get_param_value(char*& value, const char* param_name, const char* data);

void str_decode(char*& dec_str, const char* enc_str);

struct elem {
	char exp;
	elem* next = nullptr;
};
void push(elem*& stack, char exp);

const char* peek(const elem* stack);

void clear(elem*& stack);

bool pop(elem*& stack, char& exp);