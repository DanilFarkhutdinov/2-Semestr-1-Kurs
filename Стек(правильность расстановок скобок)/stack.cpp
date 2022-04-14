#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;
void push(elem*& stack, char exp) {
	auto* newel = new elem;
	newel->exp = exp;
	if (stack) newel->next = stack;
	stack = newel;
}
const char* peek(const elem* stack) {
	if (!stack) return nullptr;
	return &stack -> exp;
}
bool pop(elem*& stack, char& exp) {
	if (!stack) return false;
	exp = stack->exp;
	auto* rem = stack;
	stack = stack->next;
	delete rem; 
	return true;
}
void clear(elem*& top) {
	while (top) {
		auto* rem = top;
		top = top->next;
		delete rem;
	}
}
void fill_stack(elem*& stack, string str, int a) {
		push(stack, str[a]);
}
void show_stack(elem* stack) {
	if (!stack) cout << "Стек пуст";
	else {
		auto* curr = stack;
		while (curr) {
			auto val = peek(curr);
			cout << *val << (curr->next ? ' ' : '\n');
			curr = curr->next;
		}
	}
}