#pragma once
#include "global.h"
#include <memory.h>
#include <cstdlib>
#include <stdio.h>

typedef struct
{
	QPRIORINFO* pInfo;
	int nPrior;
	//PQItem* pNext; jak bez tego to potrzebujemy PQItem** PQ

} PQItem;

typedef struct
{
	PQItem** item;
	int PQSize;
	int PQCurrSize;

} PQueue;

PQueue* PQInit( int nSize );
int PQisEmpty( PQueue* PQ );
void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior );
PQItem* PQDequeue( PQueue* PQ );
void PQClearQueue( PQueue* PQ );
void PQRealease( PQueue** PQ );
void PQPrint( PQueue* PQ );
void DecreaseKey( PQueue* PQ, int i, int nPrior ); 
void IncreaseKey( PQueue* PQ, int i, int nPrior );
void inorder( PQueue* PQ, int root );

