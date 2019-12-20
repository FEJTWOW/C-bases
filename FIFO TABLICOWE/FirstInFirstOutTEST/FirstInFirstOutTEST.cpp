// FirstInFirstOutTEST.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "FIFO.h"

int main()
{
	FQueue* v = FQCreate( 10 );
	
	printf( "%d\n%d\n%d\n%d\n", v->howmanynow, v->max, v->nHead, v->nTail );
	//FQInfo* p = ( FQInfo* ) calloc( 15, sizeof( FQInfo ) );
	/*FQInfo** p = v->arr;
	FQInfo* insert = *p;*/
	for( int i = 0; i<10; i++ )
	{
		FQInfo* p = ( FQInfo* ) calloc( 1, sizeof( FQInfo ) );
		p->nKey = i;
		FQEnqueue( v, p );
	}
	for( int i = 0; i<5; i++ )
	{
		FQInfo* d = FQDequeue( v );
		printf( "%d ", d->nKey );
		free( d );
	}
	for( int i = 0; i<5; i++ )
	{
		FQInfo* p = ( FQInfo* ) calloc( 1, sizeof( FQInfo ) );
		p->nKey = i;
		FQEnqueue( v, p );
	}

	for( int i = 0; i<10; i++ )
	{
	
		FQInfo* d = FQDequeue( v );
		printf( "%d ", d->nKey );
		free( d );
	}
	FQRemove( &v );
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
