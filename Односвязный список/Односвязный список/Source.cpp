#include <iostream> 
#include <fstream> 
#include <string> 
#include "List.h"
using namespace std;

void show(List* head);

void fill_list(List*& head) {
    ifstream fin("List.txt");
    char buff[100];
    if (fin.is_open()) {
        while (!fin.eof()) {
            fin.getline(buff, 100);
            add_by_order(head, buff);
        }
    }
    else {
        cout << "‘айл не открыт";
    }
    fin.close();
}

void fout_file(string str) {
    ofstream fout;
    fout.open("List.txt", std::ios::app);
    if (fout.is_open()) {
        fout << endl << str;
    }
    else {
        cout << "‘айл не открыт";
    }
    fout.close();
}

void check(string str) {
    ifstream fin("List.txt");
    char buff[100];
    int count = 0;
    while (!fin.eof()) {
        fin.getline(buff, 100);
        if (buff == str) count++;
    }
    if (count == 0) fout_file(str);
    fin.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    List* head = nullptr;
    string str;
    cout << "¬ведите слово: ";
    cin >> str;
    check(str);
    fill_list(head);
    show(head);
    return 0;
}