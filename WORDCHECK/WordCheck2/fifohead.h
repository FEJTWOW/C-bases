#pragma once

#include <memory.h>
#include <stdlib.h>

typedef struct tagFQFIFOITEM
{
	int nKey;
	tagFQFIFOITEM* pNext;
} FQItem;

typedef struct
{
	FQItem* pHead;
	FQItem* pTail;
} FQueue;

/*typedef struct
{
	FQueue* q;
	FQItem* em;

} FQAll;*/

FQueue* FQCreate();
void FQRemove( FQueue** q );
int FQEmpty( FQueue* q );
void FQEnqueue( FQueue* q, int x );
int FQDequeue( FQueue* q );
void FQDel( FQueue* q );
void FQClear( FQueue* q );


