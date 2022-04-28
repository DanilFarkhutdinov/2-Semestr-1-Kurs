#include <iostream> 
#include <fstream> 
#include <string> 
#include "List.h"
using namespace std;
void add_by_order(List*& head, string new_word) {
    List* new_elem = new List;
    new_elem->word = new_word;
    if (!head) {
        head = new_elem;
        return;
    }
    List* prev = head;
    if (strcmp(new_word.c_str(), prev->word.c_str()) == -1) {
        new_elem->next = prev;
        head = new_elem;
        return;
    }
    while (prev->next) {
        if ((strcmp(new_word.c_str(), prev->next->word.c_str()) == -1) &&
            (strcmp(new_word.c_str(), prev->word.c_str()) == 1)) {
            new_elem->next = prev->next;
            prev->next = new_elem;
            return;
        }
        prev = prev->next;
    }
    prev->next = new_elem;
}

void show(List* head) {
    List* cur = head;
    while (cur) {
        cout << cur->word << " ";
        cur = cur->next;
    }
    cout << endl;
}