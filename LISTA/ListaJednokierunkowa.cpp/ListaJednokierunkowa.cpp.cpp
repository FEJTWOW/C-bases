// ListaJednokierunkowa.cpp.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "List.h"

void PrintList( ListItem* p );


int main()
{
/*	ListItem* list = CreateList();
	LISTINFO* val = ( LISTINFO* ) malloc( sizeof( LISTINFO )*10 );
	memset( val, 0, sizeof( LISTINFO )*10 );
	for( int i = 0; i<10; i++ )
	{
		val->nKey = i;
		InsertFront( list, val++ );
	}*/
	//ListInfo *tab = (ListInfo *)calloc( 20, sizeof( ListInfo ) );
	//ListInfo *f = tab;
	ListItem* lista = CreateList(); // towrzymy listę z wartownikiem na początku
	for ( int i = 0; i < 10; i++ )
	{
		LISTINFO* f =(LISTINFO*)malloc( sizeof( LISTINFO ) ); // alokujemy pamięć dla elementu listy ktorym jest struktura zawierająca liczbę całkowitą
		f->nKey = i; // przypisanie wartości
		InsertFront( lista, f ); // wrzucenie do listy
	}
	for( int i = 20; i>10; i-- )
	{
		LISTINFO* f = ( LISTINFO* ) malloc( sizeof( LISTINFO ) );
		f->nKey = i;
		InsertFront( lista, f ); // robię drugi raz pętle for żeby sprawdzić czy na pewno sortuje po liczbach nie po adresach pamięci
	}
	PrintList( lista ); // wyświetlanie listy
	SortList( lista, compare ); // sortowanie listy
	printf( "\n\n" );
	PrintList( lista ); // sprawdzenie czy dobrze sortuje
	printf( "\n\n" );
	printf( "%d ", lista->m_pNext->m_pInfo->nKey ); // sprawdzam czy dobrze zrozumiałem temat
	ListItem* prev = NULL;
	LISTINFO* elem = ( LISTINFO* ) malloc( sizeof( LISTINFO ) ); // alokujemy pamięć dla wartości do wyszukania
	elem->nKey = 3; // przypisujemy wartość którą chcemy wyszukać
	printf( "\n\n" );
	ListItem* look = Find( lista, elem, &prev, compare );
	printf( "%d\n", look->m_pInfo->nKey );
	printf( "%d\n", prev->m_pInfo->nKey );
	LISTINFO* ins = ( LISTINFO* ) malloc( sizeof( LISTINFO ) );
	ins->nKey = 19;
	Insert( lista->m_pNext->m_pNext->m_pNext, ins ); // w tym przypadku wstawiamy element za trzeci element listy
	printf( "\n\n" );
	PrintList( lista );
	printf( "\n\n" );
	Remove( lista->m_pNext->m_pNext->m_pNext );
	PrintList( lista );
	DelList( &lista );


    return 0;
}

void PrintList( ListItem* p )
{
	ListItem* iterator = p;
	while( iterator->m_pNext )
	{
		printf( "%d ", iterator->m_pNext->m_pInfo->nKey );
		iterator = iterator->m_pNext;
	}
}

int compare( const void* p, const void *v )
{
	if( ( ( LISTINFO* ) p )->nKey>( ( LISTINFO* ) v )->nKey ) // p i v jest typu void więc musimy zrobić rzutowanie
		return 1;
	if( ( ( LISTINFO* ) p )->nKey<( ( LISTINFO* ) v )->nKey )
		return -1;
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
