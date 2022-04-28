#pragma once
#include <iostream>
using namespace std;
struct List {
    int a;
    string word;
    List* next = nullptr;
};
void add_by_order(List*& head, string new_word);