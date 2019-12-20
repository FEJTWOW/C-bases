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
	a->nKey = x; // przypisanie warto�ci do nowego elementu
	q->pTail->pNext = a; // podpinamy nowy element przed ostatni element naszej kolejki
	q->pTail = a; // ustawiamy wska�nik pTail na ostatni element kolejki kt�ry jest naszym nowym elementem
	//a->pNext = NULL; // ustawiamy wska�nik pNext nowego elementu na nulla
}

int FQDequeue( FQueue* q )
{
	if( !FQEmpty( q ) )
	{
		//FQItem* remove = q->pHead->pNext; // wska�nik pomocniczy kt�ry wskazuje na pierwszy element po wartowniku
		//q->pHead->pNext = remove->pNext; // przepinamy wska�nik pNext wartownika na kolejny element po tym kt�ry usuwamy
		//int x = remove->nKey; // przypisujemy warto�� do zmiennej �eby�my mogli zwolni� pami��
		int x = q->pHead->pNext->nKey;
		FQDel( q );
		//free( remove ); // zwalniamy pami��

		if( FQEmpty( q ) ) q->pTail = q->pHead; // je�li usun�li�my ostatni element to pTail musi mie� warto�� pHead
		return x; // zwracamy warto��
	}
	perror( "Kolejka jest pusta!!! Nie mozesz niczego usunac" );
	//!! komunikat w else i wywo�a� FQDel
	return 0;
}

void FQDel( FQueue* q ) // funkcja usuwa pierwszy element
{
	if( !FQEmpty( q ) ) // to w sumie jest niepotrzebne bo funkcje FQDel wywo�ujemy w FQDequeue ju� po sprawdzeniu warunku czy kolejka jest pusta
	{
		FQItem* remove = q->pHead->pNext; // wska�nik pomocniczy kt�ry wskazuje na pierwszy element po wartowniku
		q->pHead->pNext = remove->pNext; // przepinamy wska�nik pNext wartownika na kolejny element po tym kt�ry usuwamy
		free( remove ); // zwalniamy pami��
		if( FQEmpty( q ) ) q->pTail = q->pHead; // je�li usun�li�my ostatni element to pTail musi mie� warto�� pHead
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
	//FQItem* helper = q->pHead->pNext; // wska�nik pomocniczy na pierwszy element
	while( !FQEmpty( q ) )
		FQDel( q );
	//{
	/*FQItem* remover = helper;  // podczepiam pierwszy element dodatkowym wska�nikiem
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
	*q = NULL; // ustawiamy wska�nik na NULLA
}

