// FirstInFirstOutWithHead.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "fifohead.h"

void printFifo( FQueue* q );

int main()
{
	FQueue* fifo = FQCreate();
	//FQueue* qfifo = fifo.q;
	for( int i=0; i<5; i++ )
		FQEnqueue( fifo, i );
	for( int i = 5; i>0; --i )
		FQEnqueue( fifo, i );
	/*FQClear( fifo );
	FQRemove( fifo );*/
	for( int i = 0; i<10; i++ )
		printf( "%d ", FQDequeue( fifo ));
	for( int i = 0; i<5; i++ )
		FQEnqueue( fifo, i );
	FQDel( fifo ); // usuwamy pierwszy element czyli 0
	printf( "\n\n" );
	printFifo( fifo ); // wyświetlamy kolejke

	FQRemove( &fifo );

	return 0;
}


void printFifo( FQueue* q )
{
	FQItem* printer = q->pHead->pNext;
	while( printer )
	{
		printf( "%d ", printer->nKey );
		printer = printer->pNext;
	}
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
