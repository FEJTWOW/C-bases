#include "fifohead.h"

FQueue* FQCreate()
{
	FQueue* q = ( FQueue* )calloc( 1, sizeof( FQueue ) );
	if( !q )
	{
		perror( "Memory allocation error ( FQCREATE Q )" );
		return NULL;
	}
	FQItem* i = ( FQItem* )calloc( 1, sizeof( FQItem ) );
	if( !i )
	{
		perror( "Memory allocation error (FQCREATE I )" );
		return NULL;
	}
	q->pHead = q->pTail = i;
	return q;
}

int FQEmpty( FQueue* q )
{
	return !( q->pHead->pNext );
}


void FQEnqueue( FQueue* q, int x )
{
	FQItem* a = ( FQItem* ) calloc( 1, sizeof( FQItem ) );
	if( !a )
	{
		perror( "Memory allocation error ( FQENQUEUE )" );
		return;
	}
	a->nKey = x; // przypisanie wartoúci do nowego elementu
	q->pTail->pNext = a; // podpinamy nowy element przed ostatni element naszej kolejki
	q->pTail = a; // ustawiamy wskaünik pTail na ostatni element kolejki ktÛry jest naszym nowym elementem
	//a->pNext = NULL; // ustawiamy wskaünik pNext nowego elementu na nulla
}

int FQDequeue( FQueue* q )
{
	if( !FQEmpty( q ) )
	{
		//FQItem* remove = q->pHead->pNext; // wskaünik pomocniczy ktÛry wskazuje na pierwszy element po wartowniku
		//q->pHead->pNext = remove->pNext; // przepinamy wskaünik pNext wartownika na kolejny element po tym ktÛry usuwamy
		//int x = remove->nKey; // przypisujemy wartoúÊ do zmiennej øebyúmy mogli zwolniÊ pamiÍÊ
		int x = q->pHead->pNext->nKey;
		FQDel( q );
		//free( remove ); // zwalniamy pamiÍÊ

		if( FQEmpty( q ) ) q->pTail = q->pHead; // jeúli usunÍliúmy ostatni element to pTail musi mieÊ wartoúÊ pHead
		return x; // zwracamy wartoúÊ
	}
	perror( "Kolejka jest pusta!!! Nie mozesz niczego usunac" );
	//!! komunikat w else i wywo≥aÊ FQDel
	return 0;
}

void FQDel( FQueue* q ) // funkcja usuwa pierwszy element
{
	if( !FQEmpty( q ) ) // to w sumie jest niepotrzebne bo funkcje FQDel wywo≥ujemy w FQDequeue juø po sprawdzeniu warunku czy kolejka jest pusta
	{
		FQItem* remove = q->pHead->pNext; // wskaünik pomocniczy ktÛry wskazuje na pierwszy element po wartowniku
		q->pHead->pNext = remove->pNext; // przepinamy wskaünik pNext wartownika na kolejny element po tym ktÛry usuwamy
		free( remove ); // zwalniamy pamiÍÊ
		if( FQEmpty( q ) ) q->pTail = q->pHead; // jeúli usunÍliúmy ostatni element to pTail musi mieÊ wartoúÊ pHead
	}

}

void FQClear( FQueue* q )
{
	/*FQItem* clear = q->pHead->pNext; // wskazujemy pierwszy element
	while( clear )
	{
		FQItem* helper = clear->pNext;
		//helper = clear->pNext;
		memset( clear , 0, sizeof( FQItem ) );
		clear = helper;
	}*/
	//FQItem* helper = q->pHead->pNext; // wskaünik pomocniczy na pierwszy element
	while( !FQEmpty( q ) )
		FQDel( q );
	//{
	/*FQItem* remover = helper;  // podczepiam pierwszy element dodatkowym wskaünikiem
	//helper = remove->pNext;
	helper = helper->pNext; // helperem przechodze na kolejny element
	free( remover ); // usuwam nasz element
}
//!!!!
}*/
}

void FQRemove( FQueue** q )
{
	FQClear( *q );
	/*FQItem* remove = q->pHead->pNext;
	while( remove )
	{
		FQItem* helper = remove;
		helper = remove->pNext;
		free( remove );
		remove = helper;
	}*/
	free( ( *q )->pHead ); // zwalniamy FQItem wartownika
	free( *q ); // zwalniamy wartownika
	*q = NULL; // ustawiamy wskaünik na NULLA
}

