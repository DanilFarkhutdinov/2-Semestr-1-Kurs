#pragma once
#include <iostream>
using namespace std;
bool is_get();

void get_form_data(char*& data);

void get_param_value(char*& value, const char* param_name, const char* data);

void str_decode(char*& dec_str, const char* enc_str);

struct List {
    int a;
    string word;
    List* next = nullptr;
};
void add_by_order(List*& head, string new_word);