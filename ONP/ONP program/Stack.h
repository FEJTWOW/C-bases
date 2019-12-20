#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct tagStackItem
{
	char cKey;
	tagStackItem *pNext;

} StackItem;



void makeEmptyStack( StackItem **pStack );
void push( StackItem **pStack, char c );
char pop( StackItem **pStack ); // parametr we/wy
char top( StackItem *pStack ); // parametr we
void del( StackItem **pStack );
int isEmpty( StackItem *pStack );


#endif