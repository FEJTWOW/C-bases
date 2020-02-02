// Backtracking.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "HORSE.h"

int main( int argc, char** argv )
{
	if( argc!=3 )
	{
		printf( "Podaj jako parametry wspolrzedna x > 0 i y > 0!@!@!@!" );
		return 1;
	}
	int x = atoi( argv[1] );
	int y = atoi( argv[2] );
	//printf( "%d %d", x, y );
	//printf( "\n\n" );
	if( x<0 || y<0 )
	{
		printf( "Podaj dodatnie wartosci x i y !@!@!@!@" );
		return 1;
	}
	int** chest_array = createChessboard( CHEESBOARD_SIZE );
	if( !chest_array )
	{
		printf( "Blad przy tworzeniu tablicy szachow!@!@!" );
		return 1;
	}
	//printChessBoard( chest_array, 5 );
	Point Horse_moves[HORSE_MOVES] = { { -2, 1 }, { -1, 2 }, { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 }, { -1, -2 }, { -2, -1 } };
	//chest_array[x][y] = 1;
	//printChessBoard( chest_array, CHEESBOARD_SIZE );
	//int v = root( chest_array, CHEESBOARD_SIZE, 1, x, y, Horse_moves );
	//printf( "%d ", v );
	if( !root( chest_array, CHEESBOARD_SIZE, 1, x, y, Horse_moves ) )
	{
		//printChessBoard( chest_array, CHEESBOARD_SIZE );
		printf( "Nie ma takiej sciezki!@!@!@" );
	}
	else
		printChessBoard( chest_array, CHEESBOARD_SIZE );
	
	
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
