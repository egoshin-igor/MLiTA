#pragma once

struct Stack {
	int value[2];
	Stack *next, *head;
	void add(int i, int j, Stack *&myList);
	void pop(int &i, int &j, Stack *&myList);
};
