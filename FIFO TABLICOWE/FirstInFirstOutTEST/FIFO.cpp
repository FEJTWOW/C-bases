#include "FIFO.h"

FQueue* FQCreate( int nSize )
{
	FQueue* p = ( FQueue* ) calloc( 1, sizeof( FQueue ) );
	if( !p )
	{
		perror( "Memory allocation error in FQueue!" );
	}
	p->arr = ( FQInfo** ) calloc( nSize, sizeof( FQInfo* ) );
	if( !( p->arr ) )
	{
		perror( "Memory allocation error in p->arr!" );
	}
	p->max = nSize;

	return p;
}


int FQEmpty( FQueue* q )
{
	return !(q->howmanynow);
}

void FQEnqueue( FQueue* q, FQInfo* pInfo )
{
	if( q->howmanynow == q->max )
	{
		perror( "Reached maximum elements in que!" );
		return;
	}
	q->arr[q->nTail] = pInfo; // w tablicy wskaŸników wstawiamy do pierwszego wolnego miejsca wskaŸnik do wstawianej wartoœci
	//q->nTail = q->nTail+1 ;  // przechodzimy dalej w tablicy
	q->nTail = ( q->nTail+1 )%q->max;
	//if( q->nTail==q->max ) q->nTail = 0; // uzyskujemy dzieki temu cyklicznoœæ kolejki!!
	q->howmanynow++; // zwiêkszamy liczbê elementów w tablicy

}
FQInfo* FQDequeue( FQueue* q )
{
	if( FQEmpty( q ) )
	{
		perror( "Que is empty! You can't remove anything!" );
		return NULL;
	}
	FQInfo* pointer_to_value = q->arr[q->nHead];
	//free( q->arr[q->nHead] );
	q->arr[q->nHead] = NULL;
	q->nHead = ( q->nHead+1 )%q->max;
	//if( q->nHead==q->max ) q->nHead = 0;
	q->howmanynow--;

	return pointer_to_value;
}

void FQClear( FQueue* q )
{
	free( q->arr );
	memset( q, 0, sizeof( FQueue ) );
}

void FQRemove( FQueue** q )
{
	FQClear( *q );
	free( *q );
	*q = NULL;
}



