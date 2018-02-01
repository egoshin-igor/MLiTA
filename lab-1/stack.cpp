#include "stdafx.h"
#include "stack.h"


void Stack::add(int i, int j, Stack *&myList)
{
	Stack *temp = new Stack;
	temp->value[0] = i;
	temp->value[1] = j;
	temp->next = myList->head;
	myList->head = temp;
}

void Stack::pop(int &i, int &j, Stack *&myList)
{
	Stack *temp;
	temp = myList->head;
	myList->head = myList->head->next;
	i = temp->value[0];
	j = temp->value[1];
	delete temp;
}