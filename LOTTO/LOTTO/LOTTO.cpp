// LOTTO.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "defs.h"
#include "Print.h"
#include "Data.h"


void HeapCheck();
void CalcStat( int* pNums49, Player** pPlayers, int nPlayersNo );
int compare( char* l, char* p );
void Sort( Player** pPlayers, int nPlayersNo );

int main( int argc, char** argv )
{
	if( argc!=2 )
	{
		printf( "Podaj jako parametr plik z danymi!@!@!" );
		return 2;
	}

	Player** arr_of_players = NULL;
	int number_of_players = ReadData( &arr_of_players, argv[1] );

	if( !number_of_players )
	{
		printf( "Blad w czytaniu, nie ma graczy!@!@" );
		return 2;
	}
	
	int results[NUMS] = { 0 };
	CalcStat( results, arr_of_players, number_of_players );
	Sort( arr_of_players, number_of_players );
	PrintResults( results, arr_of_players, number_of_players );
	FreeMem( &arr_of_players, number_of_players );
	HeapCheck();
	return 0;
}

/*void toLower( char* s, char* modstring )
{
	while( s )
	{
		if( *s>='A' && *s<='Z' )
		{
			*modstring++ = *s+32;
		}
		else *modstring++ = *s;
		s++;
	}
}*/

void Sort( Player** pPlayers, int nPlayersNo ) // insertion sort
{
	for( int i = 1; i<nPlayersNo; i++ )
	{
		Player* helper = pPlayers[i];
		int j = i-1;
		while( j>=0 && ( compare(pPlayers[j]->surrname,helper->surrname)>0 || ( compare( pPlayers[j]->surrname, helper->surrname )==0 && compare(pPlayers[j]->name, helper->name)>0 ) ) )
			pPlayers[j+1] = pPlayers[j--];
		pPlayers[j+1] = helper;
	}
	
}

int compare( char* l,char* p )
{
	char* modstr1 = ( char* ) calloc( strlen( l )+1, sizeof( char ) ); // strlen nie wlicza zera!@!@!@!@!@!
	char* modstr2 = ( char* ) calloc( strlen( p )+1, sizeof( char ) );
	memcpy( modstr1, l, strlen( l )+1 );
	memcpy( modstr2, p, strlen( p )+1 );
	_strlwr( modstr1 );
	_strlwr( modstr2 );
	int temp = strcmp( modstr1, modstr2 ); // strcmp zwraca wartosc wieksza od 0 jak modstr1 > modstr2, 0 jak rowne i  
	free( modstr1 );
	free( modstr2 );
	return temp;
}

void CalcStat( int* pNums49, Player** pPlayers, int nPlayersNo )
{
	
	for( int i = 0; i<nPlayersNo; i++ )
	{
		Player* helper = *pPlayers++;
		int** arr = helper->bets;
		for( int j = 0; j<helper->currentbets; j++ )
		{
			if( !*arr ) break;
			int* number = *arr++;
			for( int k = 0; k<MAXBETS; k++ )
			{
				if( *number<0 && *number > 49 )
				{
					printf( "Bledne liczby!@!@!@!@! w CALCSTAT" );
					break;
				}
				pNums49[ *number++  -1]++; // robie -- bo jak tablice sa numerowane od 0 wiec np jak wpiszemy 1 to inkremetuje indeks od 0
			}
	
		}
	}
}
// na wskaznikach
void HeapCheck()
{
	int  heapstatus;
	heapstatus = _heapchk();
	switch( heapstatus )
	{
		case _HEAPOK:
			printf( " OK - heap is fine\n" );
			break;
		case _HEAPEMPTY:
			printf( " OK - heap is empty\n" );
			break;
		case _HEAPBADBEGIN:
			printf( "ERROR - bad start of heap\n" );
			break;
		case _HEAPBADNODE:
			printf( "ERROR - bad node in heap\n" );
			break;
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
