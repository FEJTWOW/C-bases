#ifndef TAB_H
#define TAB_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

typedef void( *pointer_to_sorts )( int*, int );

int *createTab( int nSize );
void freeTab( int **pTab );
void initTab( int *pTab, int nSize, int nVal );
void randInit( int *pTab, int nSize, int modulo );
void copyTab( int* pTabTo, int* pTabFrom, int nSize );
void printTab( int *pTab, int nSize );


void SelectionSort( int *tab, int nSize );
void InsertionSort( int *tab, int nSize );
void HalfInsertionSort( int *tab, int nSize );
void BubbleSort( int *tab, int nSize );
void MixedBubbleSort( int *tab, int nSize );
void HeapSort( int *tab, int nSize );
void QuickSort( int *tab, int l, int p );
void MergeSort( int* tab, int l, int p, int nSize, int* arr );

void mMergeSort( int *tab, int l, int r, int nSize );

#endif