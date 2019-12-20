#include "DStack.h"
#include <stdlib.h>
using namespace std;

void dmakeEmptyStack ( DStackItem **pStack )
{
	while( !isDEmpty(*pStack) ) ddel( pStack );
	*pStack = NULL;

}
void dpush ( DStackItem **pStack,  double x )
{
	DStackItem* p = ( DStackItem* ) malloc ( sizeof ( DStackItem ) ); // malloc rezerwuje nam nowy obszar
	if( p )   													// w pami�ci na kt�ry zwraca nam adres 
	{
		p->fKey = x;
		p->pNext = *pStack; // przypisujemy wska�nikowi pNext wska�nik pHead kt�ry wskazuje na wcze�niejszy element
		*pStack = p; // teraz przypisujemy wska�nikowi pHead wska�nik p kt�ry wskazuje na nowo utowrzony element
	}
}
double dpop ( DStackItem **pStack ) // parametr we/wy
{
	double x = dtop ( *pStack ); // do funkcji przekazujemy orygina� pHead zatem bierzemy to na co wskazuje pHead
	if( !isDEmpty( *pStack ) )
		ddel ( pStack ); // usuwamy orygina�, czyli pHead
	else
		cout << "\n\n *!* Stack underflow!! (dpop) \n\n";
	return x;
}
double dtop ( DStackItem *pStack ) // parametr we
{
	if( !isDEmpty ( pStack ) )
		return pStack->fKey;
	cout << "\n\n *!* Stack underflow!! (dtop) \n\n";
	return 0;
}
void ddel ( DStackItem **pStack )
{
	if( !isDEmpty ( *pStack ) )
	{
		DStackItem *p = *pStack; // najpierw podpinamy ten co chcemy usun��
		*pStack = p->pNext; // przypisujemy wska�nik pHead kt�ry wskazuje na g�owe stosu na element wcze�niejszy
		free ( p ); // zwalniamy pami��
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";
}
int isDEmpty ( DStackItem *pStack )
{
	return !pStack;
}