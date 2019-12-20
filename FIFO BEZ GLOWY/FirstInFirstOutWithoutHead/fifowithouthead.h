#pragma once

#include <memory.h>
#include <cstdlib>

typedef struct tagFQFIFOITEM
{
	int nKey;
	tagFQFIFOITEM* pNext;
} FQItem;

typedef struct
{
	FQItem* pHead; // ptr to the first queue item
	FQItem* pTail; // ptr to the last queue item
} FQueue;

FQueue* FQCreate(); // inicjuje kolejke ( NULL to fail )
int FQEmpty( FQueue* q ); // if FIFO empty returned 1 else 0
void FQEnqueue( FQueue* q, int x ); // insert new item at the end
int FQDequeue( FQueue* q ); // take out the first item
void FQClear( FQueue* q ); // clears the queue
void FQRemove( FQueue** q ); // clears the queue ( =FQClear() ) and removes
void FQDel( FQueue* q ); // removes only first item nie /// nie mamy tutaj wartownika wiêc bez sensu
