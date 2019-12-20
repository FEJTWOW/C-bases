// MatrixEquation.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdio.h>
#include "Matrix.h"

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );

int main( int argc, char* argv[] )
{

	if( argc != 2 ) // pierwszy argument to nazwa programu a skoro mamy plik jeszcze to muszą być dwa argumenty
	{
		printf("Brak pliku do odczytu!\n\n");
		return 1;
	}
	FILE* p = fopen( argv[1], "r" ); // otwieramy nasz plik tekstowy w trybie czytania i ustawiamy wskaźnik na początek pliku
	if( !p ) 
	{
		printf("Bład odczytu pliku!\n\n");
		return 1;
	}

	int nSize = 0;
	fscanf( p, "%d", &nSize ); // zczytujemy pierwsza liczbe z pliku ktora jest rozmiar macierzy

	double** ReadTab = NULL; // do tej tablicy bedziemy wczytywac macierz
	double* fwvector = NULL; // do tej tablicy bedziemy wczytywac wektor wyrazow wolnych
	if( !CreateMatrix( &ReadTab, nSize ) )
	{
		perror( "Blad alokacji pamieci \n\n" ); // alokujemy dynamicznie pamiec dla naszej macierzy
		return 2;
	}
	fwvector = ( double* )malloc( sizeof( double ) * nSize ); // alokujemy dynamicznie pamiec dla wektora wyrazow wolnych
	if( !fwvector ) return 0; // sprawdzam czy alokacja sie powiodla
	memset( fwvector, 0, sizeof( double ) * nSize ); // ustawiamy zerowe wartosci
	ReadData( p, ReadTab, fwvector, nSize ); // czytamy z pliku
	fclose( p );
	double* solution = NULL;
	solution = ( double* )malloc( sizeof( double ) * nSize );
	if( !solution ) return 0; // sprawdzam czy alokacja sie powiodla
	memset( solution, 0, sizeof( double ) * nSize );
	double** InvMat = NULL; 
	CreateMatrix( &InvMat, nSize ); // tworzymy pamiec na pamiec odwrotna
	double x = Det ( ReadTab, nSize );
	if( !x )//!!!!!!!!!!!
	{
		printf("Wyznacznik wynosi zero, nie mozemy obliczyc macierzy odwrotnej\n\n");
		return 0;
	}
	InverseMatrix( InvMat, ReadTab, nSize, x ); // obliczamy macierz odwrotna
	DeleteMatrix( &ReadTab, nSize );
	LayoutEqu( InvMat, fwvector, solution, nSize ); // obliczamy wektor ktory jest rozwiazaniem
	free(fwvector);
	DeleteMatrix( &InvMat, nSize );
	double* v = solution;
	while( nSize-- ) printf("%f\n", *v++ ); // wyswietlamy rozwiazanie
	free( solution );

	return 0;

}


void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
	 // deklaracja wskaźnika który będzie odpowiadać za przypisywania do kolumn
	for( int i = 0; i < nDim ; i++ )
	{
		double* cols = *pMatrix++; // ustawienie wskaźnika na bierzącej kolumnie
		for( int j=0; j<nDim; j++ )
		{
			fscanf( fin, "%lf", cols++ ); // bo w cols znajduje sie adres komorki na ktorą wskazuje cols
			//cols++; // przejscie do kolejnej kolumny
		}
		fscanf( fin, "%lf", b++ ); // jak już przeczytamy cały wiersz macierzy to zostaje nam wyraz wolny
		
								   //b++; // przejscie na kolejny element wektora wyrazów wolnych
		//pMatrix++; // przejscie do kolejnego wiersza
	}
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowa
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
