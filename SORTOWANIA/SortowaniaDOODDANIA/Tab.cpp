#include "Tab.h"


int partition( int *tab, int l, int p );
void przesiewanie( int *tab, int l, int p );
void merge( int *tab, int l, int m, int p );
void mmerge( int *tab, int l, int m, int p, int nSize );
void mmmerge( int *tab, int l, int m, int r, int nSize, int* arr );

int *createTab( int nSize )
{
	int *creator = ( int* ) malloc( sizeof( int ) * nSize );
	if( !creator )
	{
		printf( "Blad w alokacji pamieci!!\n\n" );
		return 0;
	}
	memset( creator, 0, nSize );
	return creator;

}
void freeTab( int **pTab )
{
	free( *pTab );
}
void initTab( int *pTab, int nSize, int nVal )
{
	for( int i = 0; i<nSize; i++ )
		*pTab++ = nVal;
}
void randInit( int *pTab, int nSize, int modulo )
{
	srand( ( unsigned int ) time( NULL ) );
	for( int i = 0; i<nSize; i++ )
		*pTab++ = rand()%modulo;
}

void copyTab( int* pTabTo, int* pTabFrom, int nSize )
{
		memcpy( pTabTo, pTabFrom, nSize*sizeof( int ) );
}

void SelectionSort( int *tab, int nSize )
{
	for( int i = 0; i<nSize-1; i++ )
	{
		int min = tab[i];
		int temp = i;
		for( int j = i+1; j<nSize; j++ )
			if( tab[j]<min )
			{
				min = tab[j];
				temp = j;
			}
		tab[temp] = tab[i];
		tab[i] = min;

	}
}

void InsertionSort( int *tab, int nSize )
{
	for( int i = 1; i<nSize; i++ )
	{
		int x = tab[i];
		int j = i-1;
		while( j>=0&&tab[j]>x )
			tab[j+1] = tab[j--];
		tab[j+1] = x;
	}
}

void HalfInsertionSort( int *tab, int nSize ) // wirth strona 79
{
	for( int i = 1; i<nSize; i++ )
	{
		int x = tab[i];
		int l = 0;
		int p = i-1;
		int m = 0;
		while( l<=p )
		{
			m = l+( p-l )/2; // to jest to samo co (l+p)/2 ale unikamy overflowa przy du¿ym p i m 
			if( x<tab[m] ) p = m-1;
			else l = m+1; // w wirthie jest blad bo tam jest m-1 a wtedy ta petla moze byc nieskonczona
		}
		for( int j = i-1; j>=l; j-- ) tab[j+1] = tab[j];
		tab[l] = x;
	}
}

void BubbleSort( int *tab, int nSize )
{
	int temp = 0;
	for( int i = 0; i<nSize-1; i++ )
		for( int j = nSize-1; j>i; j-- )
			if( tab[j]<tab[j-1] )
			{
				temp = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = temp;
			}
}

void MixedBubbleSort( int *tab, int nSize )
{
	int l = 1;
	int p = nSize-1;
	int k = nSize;
	int x = 0;
	while( l<=p )
	{
		for( int j = p; j>=l; j-- )
		{
			if( tab[j-1]>tab[j] )
			{
				x = tab[j-1];
				tab[j-1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		l = k+1;
		for( int j = l; j<=p; j++ )
		{
			if( tab[j-1]>tab[j] )
			{
				x = tab[j-1];
				tab[j-1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		p = k-1;

	}

}

void printTab( int *pTab, int nSize )
{
	for( int i = 0; i<nSize; i++ )
		printf( "%d ", pTab[i] );
}

void HeapSort( int *tab, int nSize ) // wirth str 91
{
	int l = (nSize-2)/2; // indeks ostatniego rodzica
	int p = nSize-1; // ostatni indeks
	for( ; l>=0; l-- )
		przesiewanie( tab, l, nSize-1 );
	for( ; p>0; p-- )
	{
		int x = tab[0]; // zamiana pierwszego elementu z ostatnim
		tab[0] = tab[p];
		tab[p] = x;
		przesiewanie( tab, 0, p-1 ); // wywolanie przesiewania bez ostatniego elementu czyli budujemy maks stug
	}
}

void przesiewanie( int *tab, int l, int p )
{
	if( l==p ) return;
	int i = l; // indeks ostatniego rodzica
	int j = 2*i+1; // indeks lewego dziecka ostatniego rodzica
	int x = tab[i]; // zapamietujemy wartosc rodzica
	while( j<=p )
	{
		if( j<p ) // sprawdzamy czy jest prawe dziecko
			if( tab[j]<tab[j+1] ) j++; // jesli prawe dziecko jest wieksze to je bedziemy zamieniac
		if( x>tab[j] ) break; // jesli rodzic jest wiekszy niz jedno z jego dzieci to jest dobrze i wychodzimy
		tab[i] = tab[j]; // w miejsce rodzica wpisujemy dziecko ( UWAGA TUTAJ MAMY DWIE WARTOSCI TE SAME W TABLICY )
		i = j; // w indeks rodzica dajemy indeks dziecka bo on tez moze byc rodzicem
		j = 2*i+1; // w j przypisujemy indeks lewego dziecka dziecka naszego rodzica ( o ile jest on rodzicem )

	}
	tab[i] = x; // tutaj dopiero zamienianemu rodzicu przypisujemy wartosc
}

void QuickSort( int* tab, int p, int k )
{
	int q = 0;
	if( p<k )
	{
		q = partition( tab, p, k );
		QuickSort( tab, p, q );
		QuickSort( tab, q+1, k );
	}
}

int partition( int *tab, int p, int k )
{
	int x = tab[( p+k )/2];
	int i = p;
	int j = k;
	int w = 0;
	while( true )
	{
		while( tab[j]>x ) j--; // szukamy miejsca dla wartownika
		while( tab[i]<x ) i++; 
		if( i<j ) // mo¿liwe ¿e pivot jest w odpowiednim wiêc ¿eby nie zamieniaæ go z samym sob¹ sprawdzam warunek
		{
			w = tab[i];
			tab[i] = tab[j];
			tab[j] = w;
			i++;
			j--;
		}
		else return j;
	}
}

void MergeSort( int* tab, int l, int r, int nSize, int* temp )
{
	if( l<r )
	{
		int m = ( l+r )/2; // m = l + ( r - l ) /2;


		MergeSort( tab, l, m, nSize, temp );
		MergeSort( tab, m+1, r, nSize, temp );

		mmmerge( tab, l, m, r, nSize, temp );
	}
}

/*void merge( int *tab, int l, int m, int p )
{
	int n1 = m-l+1;
	int n2 = p-m;
	int *left = ( int* ) malloc( sizeof( int ) * n1 );
	int *right = ( int* ) malloc( sizeof( int ) * n2 );
	for( int i = 0; i<n1; i++ )
		left[i] = tab[l+i];
	for( int j = 0; j<n2; j++ )
		right[j] = tab[m+1+j];
	int	i = 0;
	int j = 0;
	int k = l;
	while( i<n1 && j<n2 )
	{
		if( left[i]<=right[j] )
		{
			tab[k] = left[i++];
		}
		else
		{
			tab[k] = right[j++];
		}
		k++;
	}
	memcpy( tab+k, left+i, ( n1-i ) * sizeof(int) );
	free( left );
	free( right );
}*/

void mMergeSort( int *tab, int l, int r, int nSize )
{
	if( l<r )
	{
		int m = ( l+r )/2;


		mMergeSort( tab, l, m, nSize );
		mMergeSort( tab, m+1, r, nSize );

		mmerge( tab, l, m, r, nSize );
	}
}
void mmerge( int *tab, int l, int m, int p, int nSize )
{
	int* left = tab+nSize; // wskaznik na 2 polowe tablicy
	memcpy( left+l, tab+l, sizeof( int ) * (p-l+1) ); // kopiowanie danych
	int i = l; // pocz¹tek pierwszego posortowanego ci¹gu
	int j = m+1; // pocz¹tek drugiego posortowanego ci¹gu
	int k = l; // indeks tablicy do którego bêdziemy wczytywaæ posortowane rosn¹co dwa podci¹gi

	while( i<=m && j<=p ) // laczenie dwoch posortowanych ciagow
	{
		if( left[i]<=left[j] )
		{
			tab[k++] = left[i++];
		}
		else
		{
			tab[k++] = left[j++];
		}
	}
	memcpy( tab+k, left+i, ( m-i+1 )*sizeof( int ) ); // dokopiowywanie reszty
}

void mmmerge( int *tab, int l, int m, int r, int nSize, int* arr )
{
	memcpy( arr+l, tab+l, sizeof( int ) * (r-l+1) ); // kopiujemy zawartoœæ
	int i = l; // pocz¹tek pierwszego posortowanego ci¹gu
	int j = m+1; // pocz¹tek drugiego posortowanego ci¹gu
	int k = l; // indeks tablicy do którego bedziemy wczytywaæ posrtowane rosn¹co dwa podci¹gu

	while( i<=m && j<=r ) // ³¹czenie dwóch posortowanych podci¹gów
	{
		if( arr[i]<=arr[j] )
		{
			tab[k] = arr[i++];
		}
		else
		{
			tab[k] = arr[j++];
		}
		k++;
	}
	memcpy( tab+k, arr+i, ( m-i+1 )*sizeof( int ) ); // dokopiowywanie reszty
}
