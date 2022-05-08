#include "List.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

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
	string str;
	while (cur) {
		str += cur->word;
		str += " ";
		cur = cur->next;
	}
	cout << "<font color = 'white'><p>" << str << "</p>";
}

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
		cout << "Файл не открыт";
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
		cout << "Файл не открыт";
	}
	fout.close();
}

void enter_list() {
	List* head = nullptr;
	fill_list(head);
	show(head);
}

void check(string str) {
	ifstream fin("List.txt");
	char buff[100];
	int count = 0;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin.getline(buff, 100);
			if (buff == str) count++;
		}
		if (count == 0) fout_file(str);
	}
	else {
		cout << "Файл не открыт";
	}
	fin.close();
}