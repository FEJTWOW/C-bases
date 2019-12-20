// PRIORQUEUE.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include <iostream>
#include "PQUEUE.h"
//#define _DEBUG1_
//#define _DEBUG2_

int main()
{
	PQueue* p = PQInit( 7 );
	PQueue* helper = p;
	for( int i = 0; i<2; ++i )
	{
		QPRIORINFO* elem = ( QPRIORINFO* ) calloc( 1, sizeof( QPRIORINFO ) );
		elem->nKey = i;
		PQEnqueue( p, elem, i );
		//printf( "\n%d", p->PQCurrSize );

	}
	//printf( "\n\n" );
	//PQPrint( p );
	for( int i = 5; i>2; --i )
	{
		QPRIORINFO* elem = ( QPRIORINFO* ) calloc( 1, sizeof( QPRIORINFO ) );
		elem->nKey = i; 
		PQEnqueue( p, elem, i+2 );
		//printf( "\n\n" );
		//PQPrint( p );
		//printf( "\n %d", p->PQCurrSize );
	}
	for( int i = 2; i<4; ++i )
	{
		QPRIORINFO* elem = ( QPRIORINFO* ) calloc( 1, sizeof( QPRIORINFO ) );
		elem->nKey = i;
		PQEnqueue( p, elem, i+2 );
		//printf( "\n\n" );
		//PQPrint( p );
	}
	//printf( "\n\n" );
#ifdef _DEBUG1_
	printf( "Max Heap: \n" );
	PQPrint( p );
	printf( "\n\n" );
#endif
#ifdef _DEBUG2_
	printf( "Inorder: \n" );
	inorder( p, 0 );
	printf( "\n\n" );
#endif
	IncreaseKey( p, 1, 12 );
	DecreaseKey( p, 3, 0 );
	PQRealease( &p );
	return 0;
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
