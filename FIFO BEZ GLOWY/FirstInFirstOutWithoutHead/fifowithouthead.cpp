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
	return !( q->pHead ); // jeúli pHead wskazuje na NULLA to zwrÛcimy prawdÍ w innym pzypadku fa≥sz
}

void FQEnqueue( FQueue* q, int x ) // insert new item at the end
{
	FQItem* insert = ( FQItem* ) calloc( 1, sizeof( FQItem ) ); // tworzymy nowπ strukturÍ ( kolejny element kolejki )
	if( !insert ) // sprawdzamy czy alokacja pamiÍci siÍ powiod≥a
	{
		perror( "Memory allocation error ( FQEnqueue )" );
		return;
	}
	insert->nKey = x; // przypisujemy do nowej struktury wartoúÊ x

	/*q->pHead = insert;

	if( q->pTail ) // jeúli to pierwszy element to musimy na niego ustawiÊ wskaüniki pHead i pTail bo to zarÛwno poczπtek jak i koniec
	{
		q->pTail->pNext = insert;
	}
	q->pTail = insert; /// to nie dzia≥a co Pan napisa≥, niøej zmieni≥em na jeszcze innπ wersjÍ niø Panu pokazywa≥em
	if( !( q->pHead ) )
		q->pHead = insert;*/

	if( !q->pHead ) // jeúli pHead jest NULLEM to oznacza øe nie ma jeszcze øadnego elementu w kolejce
	{
		q->pHead = insert; // zatem przypisuje wskaünik na g≥owe kolejki na dodawany elemenet
		q->pTail = insert; // i koniec kolejki na dodawany element
		return; // oraz wychodzÍ z funkcjii 
	}
	insert->pNext = q->pHead; // podpinam wskaünik inserta na kolejny element do poczπtku kolejki fifo
	q->pHead = insert; // przestawiam wskaünik na pierwszy element na nowo wstawiony element




		
}
// nano pico unix ( sprwdzone )

int FQDequeue( FQueue* q ) // take out the first item
{
	FQItem* remover = q->pHead; // wskaünik pomocniczy ktÛry pokazuje na pierwszy element kolejki
	if( !FQEmpty( q ) ); // sprawdzamy czy kolejka nie jest pusta
	{
		//int x = remover->nKey; // przypisujemy do x wartoúÊ pierwszego elementu kolejki 
		//remover = q->pHead; // podczepiamy pierwszy element kolejki
		//q->pHead = remover->pNext; // przesuwamy wskaünik pHead na kolejny element kolejki jeden if øeby na nulla wskazywa≥ pTail
		//free( remover ); // usuwamy pierwszy element kolejki
		int x = q->pHead->nKey;
		FQDel( q );
		if( FQEmpty( q ) ) q->pHead = q->pTail = NULL; // jeúli usunÍliúmy ostatni element to ustawiamy wskaüniki
		return x; // zwracamy pobranπ wartoúÊ
	}
	perror( "Kolejka jest pusta!!! Nie mozesz usunac zadnego elementu!!!!" );
	//!! komunikat i fqdel
	return 0;
}


void FQClear( FQueue* q ) // clears the queue
{
	/*if( FQEmpty( q ) ) return; // jeúli kolejka jest pusta to wracamy
	FQItem* clear = q->pHead; // wskaünik pomocniczy do wyzerowania kolejki
	while( clear ) // przechodzimy po kolejce dopÛki nie wskazuje na NULLA
	{
		memset( clear, 0, sizeof( FQItem ) ); // ustawiamy same zera w strukturze
		clear = clear->pNext; // przechodzimy na kolejny element kolejce
	}*/
	if( FQEmpty( q ) ) return;
	//FQClear( q ); // najpierw czyszczÍ kolejke
	//FQItem* helper = q->pHead; // biorÍ sobie wskaünik pomoniczy ktÛry wskazuje na pierwszy element
	while( q->pHead ) 	// dopÛki nie wskazuje on na nulla to przechodze po kolejce
		FQDel( q );
	
	
	/*{
		FQItem* remover = helper; // podczepiam pierwszy element dodatkowym wskaünikiem
		helper = helper->pNext; // helperem przechodze na kolejny element
		free( remover ); // zwalniam podczepiony element
	}*/
}

void FQRemove( FQueue** q ) // clears the queue ( =FQClear() ) and removes
{
	/*if( FQEmpty( q ) ) return;
	FQClear( q ); // najpierw czyszczÍ kolejke
	FQItem* helper = q->pHead; // biorÍ sobie wskaünik pomoniczy ktÛry wskazuje na pierwszy element
	while( helper ) // dopÛki nie wskazuje on na nulla to przechodze po kolejce
	{
		FQItem* remover = helper; // podczepiam pierwszy element dodatkowym wskaünikiem
		helper = helper->pNext; // helperem przechodze na kolejny element
		free( remover ); // zwalniam podczepiony element
	}*/
	FQClear( *q );
	free( *q );
}

void FQDel( FQueue* q )
{
	FQItem* remover = q->pHead; // wskaünik pomocniczy ktÛry pokazuje na pierwszy element kolejki
//	free( *q ); // zwalniam pamiÍÊ przydzielonπ na strukturÍ FQueue
	if( !FQEmpty( q ) )
	{
		remover = q->pHead; // podczepiamy pierwszy element kolejki
		q->pHead = remover->pNext; // przesuwamy wskaünik pHead na kolejny element kolejki
		free( remover ); // usuwamy pierwszy element kolejki
	}
}
