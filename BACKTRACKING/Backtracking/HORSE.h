#pragma once


#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define CHEESBOARD_SIZE 6
#define HORSE_MOVES 8

typedef enum { FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH, EIGHTH } moves;


typedef struct Point
{
	int x;
	int y;
} Point;

int move( int** pChessBoard, int nDim, int move2, int x, int y,
		  int* px, int* py, Point* pHorseMoves );
int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves );
int** createChessboard( int nDim );
void freeChessboard( int*** pChessBoard );
void printChessBoard( int** pChessBoard, int nDim );


