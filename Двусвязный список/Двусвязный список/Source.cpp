#include <iostream>
#include <string>
#include "List2.h"

using namespace std;

void show_list(const list2& list, bool reversed = false);

void Sum(list2 sum, list2 list1, list2 list2, string str1, string str2) {
	int x1 = str1.length();
	int x2 = str2.length();
	int size1 = str1.length();
	int count1 = 0;
	int count2 = 0;
	string buff1;
	while (size1 > 9) {
		for (int i = size1 - 9; i <= size1; i++) {
			buff1 += str1[i];
		}
		int rez = stoi(buff1);
		add(list1, rez);
		str1.erase(size1 - 9);
		size1 -= 9;
		buff1.clear();
		count1++;
	}
	int s1 = stoi(str1);
	add(list1, s1);
	count1++;
	int size2 = str2.length();
	string buff2;
	while (size2 > 9) {
		for (int i = size2 - 9; i <= size2; i++) {
			buff2 += str2[i];
		}
		int rez = stoi(buff2);
		add(list2, rez);
		str2.erase(size2 - 9);
		size2 -= 9;
		buff2.clear();
		count2++;
	}
	int s2 = stoi(str2);
	add(list2, s2);
	count2++;
	if (count1 > count2) {
		while (count1 > count2) {
			add(list2, 0);
			count2++;
		}
	}
	else {
		if (count1 < count2) {
			while (count1 < count2) {
				add(list1, 0);
				count1++;
			}
		}
	}
	int length = list1.count;
	int c = 0;
	for (int j = length - 1; j >= 0; j--) {
		auto val1 = get(list1, j);
		auto val2 = get(list2, j);
		auto product = *val1 + *val2 + c;
		if (product / 1000000000 != 0) {
			c = 1;
			product = product % 1000000000;
		}
		else {
			c = 0;
		}
		add(sum, product);
	}
	cout << "—умма: ";
	for (int j = 0; j <= sum.count - 1; j++) {
		auto val3 = get(sum, j);
		if (*val3 < 10 && j>0 && x1 >=9 && x2>=9) {
			cout << "00000000" << *val3;
		}
		else {
			if (*val3 < 100 && j>0 && x1 >= 9 && x2 >= 9) {
				cout << "0000000" << *val3;
			}
			else {
				if (*val3 < 1000 && j>0 && x1 >= 9 && x2 >= 9) {
					cout << "000000" << *val3;
				}
				else {
					if (*val3 < 10000 && j>0 && x1 >= 9 && x2 >= 9) {
						cout << "00000" << *val3;
					}
					else {
						if (*val3 < 100000 && j>0 && x1 >= 9 && x2 >= 9) {
							cout << "0000" << *val3;
						}
						else {
							if (*val3 < 1000000 && j>0 && x1 >= 9 && x2 >= 9) {
								cout << "000" << *val3;
							}
							else {
								if (*val3 < 10000000 && j>0 && x1 >= 9 && x2 >= 9) {
									cout << "00" << *val3;
								}
								else {
									if (*val3 < 100000000 && j>0 && x1 >= 9 && x2 >= 9) {
										cout << "0" << *val3;
									}
									else {
										cout << *val3;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	clear(list1);
	clear(list2);
}

int main() {
	setlocale(LC_ALL, "Russian");
	string str1, str2;
	list2 number1;
	list2 number2;
	list2 sum;
	cout << "¬ведите первое число: ";
	cin >> str1;
	cout << "¬ведите второе число: ";
	cin >> str2;
	Sum(sum, number1, number2, str1, str2);
	return 0;
}