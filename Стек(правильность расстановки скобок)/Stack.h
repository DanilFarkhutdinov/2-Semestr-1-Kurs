#pragma once
struct elem {
	char exp;
	elem* next = nullptr;
};
void push(elem*& stack, char exp);

const char* peek(const elem* stack);

void clear(elem*& stack);

bool pop(elem*& stack, char& exp);