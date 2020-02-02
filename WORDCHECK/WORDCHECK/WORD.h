#pragma once

#include <stdio.h>
#include <cstdlib>
#include <memory.h>
#include <string.h>
#define MAXCHAR 1000


typedef struct ListItem
{
	ListItem* pNext;
	int nLine;
} ListItem;


typedef struct ListHead
{
	ListItem* pTail;
	ListItem* pHead;

} ListHead;



typedef struct TreeElem
{
	int nNo;	// ilosc wystapien s³owa
	char* pWord;	// slowo
	ListHead* List;	// lista numerow linii w ktorej wystêpuje slowo ( numery ró¿ne ) jak wystêpuje s³owo druga raz w danej lini to zwiêkszamy nNo

	TreeElem* pLeft; // lewe poddrzewo
	TreeElem* pRight; // prawe poddrzewo

} TreeElem;


int ReadData( TreeElem** root, const char* sfileName );
void inOrder( TreeElem* p, FILE* output );
int compare( char* l, char* p );
void FreeMemory( TreeElem** root );