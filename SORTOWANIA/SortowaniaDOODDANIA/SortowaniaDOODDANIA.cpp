// SortowaniaDOODDANIA.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "Tab.h"
#include <iostream>
#define _DEBUG_

void aQuickSort( int *tab, int nSize ); // funkcja wywołująca qs
void aMergeSort( int *tab, int nSize ); // funkcja wywołująca mergsort
void amMergeSort( int *tab, int nSize ); // funkcja wywołująca mergsort na jednej tablicy

int main( int argc, char* argv[] )
{
	if( argc!=2 )
	{
		printf( "Brak rozmiaru!" );
		return 1;
	}
	int nSize = atoi( argv[1] );

	pointer_to_sorts tab[] = { BubbleSort, MixedBubbleSort, HeapSort, aQuickSort, SelectionSort, InsertionSort, HalfInsertionSort, aMergeSort, amMergeSort };
	const char* sorty[] = { "BubbleSort", "MixedBubbleSort", "HeapSort", "QuickSort", "SelectionSort", "InsertionSort", "HalfInsertionSort", "MergeSort", "MergeSortOnOneTab" };

	int* m = NULL; // glowna tablica
	int* c = NULL; // kopia

	m = createTab( nSize ); // tworzymy tablice główną
	c = createTab( nSize ); // tworzymy tablice pomocniczą
	if( !( m && c ) )
	{
		printf( "Blad w alokacji pamieci dla tablic" );
	}
	randInit( m, nSize, nSize ); // inicjujemy randomowymi liczbami tablice
	copyTab( c, m, nSize ); // kopiujemy zawartość do tablicy pomocniczej
#ifdef _DEBUG_ // sprawdzam czy dobrze się zainicjowało
	printTab( m, nSize );
#endif
	printf( "\n\n" );
#ifdef _DEBUG_ // sprawdzam czy dobrze sie skopiowało
	printTab( c, nSize ); 
#endif
	printf( "\n\n" );
	clock_t start;
	clock_t stop;
	double time = 0;
	int size = sizeof( tab )/sizeof( pointer_to_sorts );
	for( int i = 0; i<size-1; i++ )
	{
		start = clock(); // rozpoczynamy liczenie czasu
		tab[i]( m, nSize );
		stop = clock(); // kończymy liczenie czasu
		time = ( double ) ( stop-start )/CLOCKS_PER_SEC;
	#ifdef _DEBUG_ // żeby sprawdzić czy dobrze tablica sortuje
		printTab( m, nSize );
	#endif
		printf( "Czas dzialania %s wynosi: %f \n\n", sorty[i], time ); // wyświetlamy nazwę sortowania i czas
		copyTab( m, c, nSize ); // kopiujemy z tablicy pomocniczej do głownej aby znów wykonać sortowania
	}
	//--------------------------------
	int* merge = createTab( 2*nSize ); // tworzymy tablice o dwa razy większym rozmiarze
	memset( merge, 0, 2*nSize * sizeof( int ) ); // ustawiamy w niej zera
	copyTab( merge, m, nSize ); // kopiujemy do niej tablice o rozmiarze nSize z naszymi sortowanymi wartościami
#ifdef _DEBUG_ // sprawdzam czy się dobrze przekopiowało
	printTab( merge, 2*nSize );
	printf( "\n\n" );
#endif
	start = clock();
	tab[8]( merge, nSize ); // sprawdzam szybkość sortowania merg sorta bez tablicy pomocniczej
	stop = clock();
	time = ( double ) ( stop-start )/CLOCKS_PER_SEC;
#ifdef _DEBUG_
	printTab( merge, nSize );
	printf( "\n\n" );
#endif
	printf( "Czas dzialania %s wynosi: %f \n\n", sorty[8], time );
	freeTab( &m ); // zwalniam pamięć użytych tablic
	freeTab( &c );
	freeTab( &merge );

	return 0;
}


void aQuickSort( int *tab, int nSize ) // funkcja wywołująca quicksort
{
	QuickSort( tab, 0, nSize-1 );
}
void aMergeSort( int *tab, int nSize ) // funkcja wywołująca zwykły mergsort z jedną tablicą pomocniczą
{
	int* arr = ( int* ) malloc( sizeof( int )*nSize );
	memset( arr, 0, nSize );
	MergeSort( tab, 0, nSize-1, nSize, arr );
	free( arr );
}
void amMergeSort( int *tab, int nSize ) // funkcja wywołująca mergesort na jednej tablicy
{
	mMergeSort( tab, 0, nSize-1, nSize );
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
