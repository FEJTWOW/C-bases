#include "Matrix.h"



void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim ); // wycina nty wiersz i nta kolumne
void ComplMatrix( double** pTabO, double** pTabI, int nDim ); // liczy macierz dopelnien

int CreateMatrix( double*** pTab, int nSize ) // !!! - error 1 -ok
{
	*pTab = ( double** )malloc( sizeof( double* ) * nSize ); //tworzymy tablice wskaünikÛw
	if( !*pTab ) return 0;
	memset( *pTab, NULL, sizeof( double* ) * nSize );

	double **creator = *pTab;// tworzymy wskaünik pomocniczy øeby nie zmieniac wskaznika pTab
	for( int i=0; i<nSize; i++ )
	{
		*creator = ( double* )malloc( sizeof( double ) * nSize ); // alokujemy pamiec kolejno dla kazdej "komorki" tablicy wskaznikow ADRESY NIE MUSZA BYC PO KOLEI W TYM PRZYPADKU!!!!@!@!@!
		if( !*creator ) return 0; 
		memset( *creator++, 0, sizeof( double ) * nSize );
	}
	return 1;
}
void DeleteMatrix( double*** pTab, int nSize ) // *pTab==NULL;
{
	double** creator = *pTab; // tworzymy wskaznik pomocniczy
	for( int i = 0; i < nSize; i++ ) free( *creator++ ); // zwalniamy kolejno pamiec w "komorkach" tablicy wskaznikow
	free( *pTab ); // zwalniamy pamiec dla tablicy wskaznikow
	*pTab = NULL; // ustawiamy wskaznik ktory wskazywal na tablice wskaznikow na NULLA
}
void TransMatrix( double** pTab, int nDim ) // to juz pisalismy w 1 semestrze
{
	//double temp = 0;
	//double* col = NULL; // pomocny wskaznik do przechodzenia po kolumnach
	double** row = pTab; // jest nam potrzebny bo inaczej podczas inkrementacjii by nam sie sypal kod
	for( int i=0; i < nDim-1; i++ )
	{
		double* col = *row++ +i+1;
		for( int j= i+1; j < nDim; j++ )
		{
			//temp = pTab[i][j];
			double temp = *col;
			//pTab[i][j] = pTab[j][i];
			*col = pTab[j][i]; // o tutaj by nam sie psulo bo pTab[j][i] to jest to samo co *(*(pTab+j)+i)
			pTab[j][i] = temp;
			*col++; //przechodzimy do kolejnej kolumny
		}
		//row++; //przejscie do kolejnego wiersza, sztuka dla sztuki
		// a tak to tutaj zamiast row pisalibysmy pTab++ i wtedy by sie to w 43 linijce sypalo 

	}
}

void InverseMatrix( double** pInv, double** pTab, int nSize, double det )
{
// Macierz odwrotna liczymy tak ze najpierw wyliczamy macierz dopelnien nastepnie ja transponujemy a na koncu kazdy element tej macierzy dzielimy przez wyznacznik
	ComplMatrix( pInv, pTab , nSize ); // wyliczamy macierz dopelnien
	TransMatrix( pInv, nSize ); // transponujemy ja
	double* s = NULL; // tworzymy wskaznik pomocniczy do przechodzenia po kolumnach
	for( int i=0; i< nSize; i++ )
	{
		s = *pInv++; // ustawiamy wskaznik pomocniczy na odpowiedniej kolumnie w odpowiednim wierszu
		for( int j=0; j< nSize; j++ ) *s++ /= det; // kolejno przechodzimy po kolumnie
		//pInv++; // przechodzimy do kolejnego wiersza
	}
}
double Det( double** pTab, int nSize ) // rozw wzg 0 wiersza rekurencyjnie
{
	if( nSize == 2 ) return ( pTab[0][0]*pTab[1][1] ) - ( pTab[0][1]*pTab[1][0] ); // liczmy wyznacznik dla macierzy 2-wymiarowej
	double** I = NULL; // tworzymy wskaznik pomocniczy
	CreateMatrix( &I, nSize - 1 ); // tworzymy pomocnicza macierz o rozmiarze o 1 mniejszym niz wejsciowa bo musimy z niej wycinac 
	double res = 0;
	double* f = *pTab; // ustawiamy wskaznik na elemencie wzgledem ktorego rozpoczniemy rozwiniecie Laplace'a
	int sign = 1; // zmienna odpowiadajaca za znak poniewaz w zaleznosci od numeru wiersza i komorki musimy brac wynik dodatni lub ujemny
	for( int i = 0; i < nSize; i++ )
	{
		Complement( I, pTab, 0, i , nSize ); // wycinamy z macierzy pTab wiersz i kolumne
		res += *f++ * sign * Det( I, nSize -1 ); // rekurencyjnie obliczamy wyznacznik
		//f++; // przechodzimy do kolejnego elementu z pierwszego wiersza
		sign =- sign; // zmieniamy sing na -1 poniewaø teraz suma wiersza i kolumny bedzie nieparzysta
		
	}
	DeleteMatrix( &I, nSize - 1 ); // sprzatamy po sobie
	return res; // zwracamy wynik
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize )
{
	double* s = NULL; // wskaznik do przechodzenia po kolumnach macierzy odwrotnej
	double* x = NULL; // wskaznik do przechodzenia po wektorze wyrazow wolnych, jest on potrzebny poniewaz potrzebujemy pamietac poczatek wektora wyrazow wolnych bo kazdy wiersz macierzy mnozymy przez ten wektor
	for( int i = 0; i < nSize; i++ )
	{
		s = *pInv; // ustawiamy wskaznik pomocniczy na odpowiedniej kolumnie
		x = pB; // ustawiamy wskaznik pomocniczy na poczatku wektora wyrazow wolnych
		for( int j=0; j< nSize; j++ ) *pRes += *s++ *  *x++ ;
		pInv++; // przechodzimy do kolejnego wiersza
		pRes++; // przechodzimy do kolejnej komorki wektora ktory jest rozwiazaniem
	}
}
void PrintMatrix( double **pTab, int nSize )
{
	double* init = NULL; // wskaznik pomocniczy do przechodzenia po kolumnach
	for( int i=0; i<nSize; i++ )
	{
		init = *pTab++;

		for( int j=0; j<nSize; j++, init++ )
		{
			printf("%f ", *init );
		}
		printf("\n");
		//pTab++; // przejcie do kolejnego wiersza

	}
}


void Complement( double **pTabO, double **pTabI, int nRow, int nCol, int nDim )
{
	double* copy = NULL; // wskaznik pomocniczy do przechodzenia po kolumnach macierzy z ktorej wycinamy
	double* to = NULL; // wskaznik pomocniczy do przechodzenia po kolumnach macierzy do ktorej wczytujemy wycieta macierz
	for( int i = 0 ; i < nDim ; i ++ )
	{
		copy = *pTabI; // ustawienie wskaznikow na odpowiednich kolumnach
		to = *pTabO;
		if( i == nRow ) // skoro dany wiersz chcemy wyciac to inkrementujemy wskaznik odpowiadajacy za tablice wejsciowa i pomijamy dany wiersz
		{ 
			pTabI++;
			continue;
			
		}
		for( int j = 0; j < nDim; j ++ )
		{
			if( j == nCol )	 // jesli dana kolumne chcemy wyciac to inkrementujemy wskaznik z tablicy wejsciowej ktory na nia wskazuje dzieki czemu zostaje pominieta
			{	
				copy++;
				continue;
			}

			*to++ = *copy++; // przechodzimy po kolumnach i kopiujemy dane
		}
		pTabO++; // przejscie do kolejnego wiersza tablicy wyjsciowej
		pTabI++; // przejscie do kolejnego wiersza tablice wejsciowej
	}
}
void ComplMatrix ( double **pTabO, double **pTabI, int nDim ) // macierz dopelnien
{
	double* D = NULL; // wskaznik pomocniczy odpowiadajacy za wpisywanie wartosci dopelnien do macierzy wyjsciowej
	double** I = NULL; // macierz pomocnicza z ktorej bedziemy liczyc wyznacznik
	CreateMatrix( &I, nDim - 1 );
	for( int i=0; i<nDim; i++ )
	{
		D = *pTabO++; // ustawienie wskaznika we wlasciwej kolumnie
		double sign = ( i%2 ) ? -1 : 1;
		for( int j=0; j<nDim; j++ )
		{
			Complement ( I, pTabI, i, j, nDim ); // wyciecie odpowiedniego wiersza i kolumny
			*D++ = sign * Det( I , nDim - 1 ); // w zaleznosci od numeru wiersza i kolumny przypisujemy wartosc wyznacznika ze znakiem dodatnim lub ujemnym
			sign=-sign;
			//D++;
		}
		//pTabO++; // przejscie do kolejnego wiersza macierzy wyjsciowej
	}
	DeleteMatrix( &I, nDim - 1 ); // sprzatamy po sobie
}

