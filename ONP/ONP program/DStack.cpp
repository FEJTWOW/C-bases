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
	if( p )   													// w pamiêci na który zwraca nam adres 
	{
		p->fKey = x;
		p->pNext = *pStack; // przypisujemy wskaŸnikowi pNext wskaŸnik pHead który wskazuje na wczeœniejszy element
		*pStack = p; // teraz przypisujemy wskaŸnikowi pHead wskaŸnik p który wskazuje na nowo utowrzony element
	}
}
double dpop ( DStackItem **pStack ) // parametr we/wy
{
	double x = dtop ( *pStack ); // do funkcji przekazujemy orygina³ pHead zatem bierzemy to na co wskazuje pHead
	if( !isDEmpty( *pStack ) )
		ddel ( pStack ); // usuwamy orygina³, czyli pHead
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
		DStackItem *p = *pStack; // najpierw podpinamy ten co chcemy usun¹æ
		*pStack = p->pNext; // przypisujemy wskaŸnik pHead który wskazuje na g³owe stosu na element wczeœniejszy
		free ( p ); // zwalniamy pamiêæ
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";
}
int isDEmpty ( DStackItem *pStack )
{
	return !pStack;
}