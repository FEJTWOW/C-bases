#include "fifowithouthead.h"


FQueue* FQCreate() // inicjuje kolejke ( NULL to fail )
{
	FQueue* p = ( FQueue* )calloc( 1, sizeof( FQueue ) );
	if( !p )
	{
		perror( "Memory allocation error! ( FQueue ) " );
		return NULL;
	}
	p->pHead = p->pTail = NULL;
	/*FQItem* item = ( FQItem* ) calloc( 1, sizeof( FQItem ) );
	if( !item )
		perror( "Memory allocation error! ( FQItem )" );
	p->pHead = item;
	p->pTail = item;*/

	return p;
}

int FQEmpty( FQueue* q ) // if FIFO empty returned 1 else 0
{
	return !( q->pHead ); // je�li pHead wskazuje na NULLA to zwr�cimy prawd� w innym pzypadku fa�sz
}

void FQEnqueue( FQueue* q, int x ) // insert new item at the end
{
	FQItem* insert = ( FQItem* ) calloc( 1, sizeof( FQItem ) ); // tworzymy now� struktur� ( kolejny element kolejki )
	if( !insert ) // sprawdzamy czy alokacja pami�ci si� powiod�a
	{
		perror( "Memory allocation error ( FQEnqueue )" );
		return;
	}
	insert->nKey = x; // przypisujemy do nowej struktury warto�� x

	/*q->pHead = insert;

	if( q->pTail ) // je�li to pierwszy element to musimy na niego ustawi� wska�niki pHead i pTail bo to zar�wno pocz�tek jak i koniec
	{
		q->pTail->pNext = insert;
	}
	q->pTail = insert; /// to nie dzia�a co Pan napisa�, ni�ej zmieni�em na jeszcze inn� wersj� ni� Panu pokazywa�em
	if( !( q->pHead ) )
		q->pHead = insert;*/

	if( !q->pHead ) // je�li pHead jest NULLEM to oznacza �e nie ma jeszcze �adnego elementu w kolejce
	{
		q->pHead = insert; // zatem przypisuje wska�nik na g�owe kolejki na dodawany elemenet
		q->pTail = insert; // i koniec kolejki na dodawany element
		return; // oraz wychodz� z funkcjii 
	}
	insert->pNext = q->pHead; // podpinam wska�nik inserta na kolejny element do pocz�tku kolejki fifo
	q->pHead = insert; // przestawiam wska�nik na pierwszy element na nowo wstawiony element




		
}
// nano pico unix ( sprwdzone )

int FQDequeue( FQueue* q ) // take out the first item
{
	FQItem* remover = q->pHead; // wska�nik pomocniczy kt�ry pokazuje na pierwszy element kolejki
	if( !FQEmpty( q ) ); // sprawdzamy czy kolejka nie jest pusta
	{
		//int x = remover->nKey; // przypisujemy do x warto�� pierwszego elementu kolejki 
		//remover = q->pHead; // podczepiamy pierwszy element kolejki
		//q->pHead = remover->pNext; // przesuwamy wska�nik pHead na kolejny element kolejki jeden if �eby na nulla wskazywa� pTail
		//free( remover ); // usuwamy pierwszy element kolejki
		int x = q->pHead->nKey;
		FQDel( q );
		if( FQEmpty( q ) ) q->pHead = q->pTail = NULL; // je�li usun�li�my ostatni element to ustawiamy wska�niki
		return x; // zwracamy pobran� warto��
	}
	perror( "Kolejka jest pusta!!! Nie mozesz usunac zadnego elementu!!!!" );
	//!! komunikat i fqdel
	return 0;
}


void FQClear( FQueue* q ) // clears the queue
{
	/*if( FQEmpty( q ) ) return; // je�li kolejka jest pusta to wracamy
	FQItem* clear = q->pHead; // wska�nik pomocniczy do wyzerowania kolejki
	while( clear ) // przechodzimy po kolejce dop�ki nie wskazuje na NULLA
	{
		memset( clear, 0, sizeof( FQItem ) ); // ustawiamy same zera w strukturze
		clear = clear->pNext; // przechodzimy na kolejny element kolejce
	}*/
	if( FQEmpty( q ) ) return;
	//FQClear( q ); // najpierw czyszcz� kolejke
	//FQItem* helper = q->pHead; // bior� sobie wska�nik pomoniczy kt�ry wskazuje na pierwszy element
	while( q->pHead ) 	// dop�ki nie wskazuje on na nulla to przechodze po kolejce
		FQDel( q );
	
	
	/*{
		FQItem* remover = helper; // podczepiam pierwszy element dodatkowym wska�nikiem
		helper = helper->pNext; // helperem przechodze na kolejny element
		free( remover ); // zwalniam podczepiony element
	}*/
}

void FQRemove( FQueue** q ) // clears the queue ( =FQClear() ) and removes
{
	/*if( FQEmpty( q ) ) return;
	FQClear( q ); // najpierw czyszcz� kolejke
	FQItem* helper = q->pHead; // bior� sobie wska�nik pomoniczy kt�ry wskazuje na pierwszy element
	while( helper ) // dop�ki nie wskazuje on na nulla to przechodze po kolejce
	{
		FQItem* remover = helper; // podczepiam pierwszy element dodatkowym wska�nikiem
		helper = helper->pNext; // helperem przechodze na kolejny element
		free( remover ); // zwalniam podczepiony element
	}*/
	FQClear( *q );
	free( *q );
}

void FQDel( FQueue* q )
{
	FQItem* remover = q->pHead; // wska�nik pomocniczy kt�ry pokazuje na pierwszy element kolejki
//	free( *q ); // zwalniam pami�� przydzielon� na struktur� FQueue
	if( !FQEmpty( q ) )
	{
		remover = q->pHead; // podczepiamy pierwszy element kolejki
		q->pHead = remover->pNext; // przesuwamy wska�nik pHead na kolejny element kolejki
		free( remover ); // usuwamy pierwszy element kolejki
	}
}
