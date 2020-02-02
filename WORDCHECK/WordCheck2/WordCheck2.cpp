// WordCheck2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "WORD.h"
#include <iostream>

int main(int args, char** argv)
{
	TreeElem* root = NULL; // tworzymy naszego roota
	if( args!=3 )
	{
		printf( "Podaj poprawna liczbe parametrow ( plik we i wy )!@!@!" );
		return 1;
	}
	if( ReadData( &root, argv[1] ) )
	{
		printf( "Blad w czytaniu danych!@!@!@!@" );
		return 1;
	}
	FILE* output = fopen( argv[2], "w" ); // otwieramy plik do odczytu
	if( !output )
	{
		printf( "Nie mozna otworzyc pliku do wypisywania!@!@!" );
		return 1;
	}
	inOrder( root, output );
	FreeMemory( &root );
	fclose( output );
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
