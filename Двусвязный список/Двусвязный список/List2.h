#pragma once
struct elem
{
    int x;
    elem* next = nullptr;
    elem* prev = nullptr;
};

struct list2
{
    elem* first = nullptr;
    elem* last = nullptr;
    int count = 0;
};

void add(list2& list, int data);

const int* get(list2 list, int pos);

void clear(list2& list);