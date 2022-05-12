#include <iostream>
#include "List2.h"
using namespace std;

void add(list2& list, int data)
{
    elem* newel = new elem;
    newel->x = data;
    list.count++;
    if (!list.first)
    {
        list.first = list.last = newel;
    }
    else
    {
        newel->next = list.first;
        list.first->prev = newel;
        list.first = newel;
    }
}

const int* get(list2 list, int pos)
{
    if (!list.first || pos < 0 || pos >= list.count)
        return nullptr; 
    if (!pos)return &list.first->x; 
    if (pos == list.count - 1)
        return &list.last->x; 
    int p = 1;
    bool fwd = pos <= list.count / 2;
    elem* curr;
    if (fwd)
        curr = list.first->next;
    else {
        curr = list.last->prev;
        pos = list.count - pos - 1;
    }
    while (curr && p < pos)
    {
        p++;
        curr = fwd ? curr->next : curr->prev;
    }
    return &curr->x;
}

void clear(list2& list)
{
    elem* rem;
    while (list.first)
    {
        rem = list.first;
        list.first = list.first->next;
        delete rem;
    }
    list.last = nullptr;
    list.count = 0; 
}

void show_list(const list2& list, bool reversed = false)
{
    elem* curr = reversed ? list.last : list.first;
    if (!curr) cout << "Список пуст\n";
    else while (curr)
    {
        elem* cmp = reversed ? list.first : list.last;
        cout << curr->x << ((curr == cmp) ? "\n" : " ");
        curr = reversed ? curr->prev : curr->next;
    }
}