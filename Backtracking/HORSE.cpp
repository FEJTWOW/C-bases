#include "HORSE.h"

int move( int** pChessBoard, int nDim, int move, int x, int y,
		  int* px, int* py, Point* pHorseMoves )
{
	*px = x + pHorseMoves->x; // jesli jednak wykorzystujemy parametr move to trzeba to zmienic na *px = x + pHorseMoves[move].x
	*py = y + pHorseMoves->y; // *py = y + pHorseMoves[move].y 
	if( ( *px<0 )||( *py<0 )||( *px>=nDim )||( *py>=nDim )||( pChessBoard[*px][*py]!=0 ) )
		return 0;
	return 1;
	
}
int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves )
{
	static int move_numbers = 0;
	pChessBoard[x][y] = moveNo;
	++move_numbers;

	if( moveNo==nDim*nDim )
	{
		printf( "Liczba prob %d\n", move_numbers );
		return 1;
	}
	int px;
	int py;
	Point* helper = pHorseMoves; // mozna na dwa sposoby kiedy robimy sobie pomocniczy wskaznik na pHorseMoves to nie musimy wykorzystawac parametru move z funkcji move 
	for( int i = FIRST; i<=EIGHTH; i++ )
	{
	
		if( move( pChessBoard, nDim, i, x, y, &px, &py, helper ) ) // tego "i" wtedy kiedy mamy pomocniczy wskaznik helper nie musimy nawet przekazywac ale jak nie mamy to tutaj zmienic z helper na pHorseMoves
		{			
			if( root( pChessBoard, nDim, moveNo+1, px, py, pHorseMoves ) )
				return 1;
		}
		helper++;
	}
	pChessBoard[x][y] = 0;
	return 0;
}
int** createChessboard( int nDim )
{
	int** rows = ( int** )calloc( nDim, sizeof( int* ) );
	int* cols = ( int* ) calloc( nDim*nDim, sizeof( int ) );
	int** helper = rows;
	for( int i = 0; i<nDim; i++ )
	{
		*helper++ = cols;
		cols += nDim;
		
	}
	return rows;
}
void freeChessboard( int*** pChessBoard )
{
	free( **pChessBoard );
	free( *pChessBoard );
	*pChessBoard = NULL;
}
void printChessBoard( int** pChessBoard, int nDim )
{
	int* k = *pChessBoard;
	for( int i = 0; i<nDim; i++ )
	{
		//int* helper = *pChessBoard++;
		for( int j = 0; j<nDim; j++ )
			printf( "%2d ", *k++ );
		printf( "\n" );
	}
}