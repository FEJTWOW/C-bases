#ifndef _FIFO_H
#define _FIFO_H

#include "global.h"
#include <memory.h>
#include <cstdlib>

typedef struct
{
	FQInfo** arr; // potrzebujemy tablicy wskaŸników do naszej struktury w global.h
	int nHead; // indeks pierwszego elementu
	int nTail; // indeks pierwszego wolnego elementu
	int howmanynow; // dodatkowa informacja, ile elementów znajduje siê w kolejce
	int max; // maksymalna liczba elementów

} FQueue;

FQueue* FQCreate( int nSize ); // return NULL ( fail ) 
int FQEmpty( FQueue *q ); // sprawdza czy kolejka nie jest pusta
void FQEnqueue( FQueue* q, FQInfo* pInfo ); // wstawia nowy element do kolejki
FQInfo* FQDequeue( FQueue* q ); // zwraca wskaznik
void FQClear( FQueue* q ); // funkcja czyszczaca kolejke, zwalniamy pamiec
void FQRemove( FQueue** q );

#endif


