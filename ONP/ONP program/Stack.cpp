#include "Stack.h"


void makeEmptyStack( StackItem  **pStack )
{
	while( !isEmpty(*pStack) ) del(pStack);
	( *pStack ) = NULL;
}
void push( StackItem **pStack ,char c )
{
	StackItem* p = ( StackItem* )malloc( sizeof( StackItem ) ); // malloc rezerwuje nam nowy obszar
	if( p )   													// w pami�ci na kt�ry zwraca nam adres 
	{
		p->cKey=c;
		p->pNext = *pStack; // przypisujemy wska�nikowi pNext wska�nik pHead kt�ry wskazuje na wcze�niejszy element
		*pStack = p; // teraz przypisujemy wska�nikowi pHead wska�nik p kt�ry wskazuje na nowo utowrzony element
	}

}
char pop( StackItem **pStack )
{
	char c = top( *pStack ); // do funkcji przekazujemy orygina� pHead zatem bierzemy to na co wskazuje pHead
	if( c )
		del( pStack ); // usuwamy orygina�, czyli pHead
	else
		cout<<"\n\n *!* Stack underflow!! (POP) \n\n";
	return c;
}
char top( StackItem *pStack )
{
	if( !isEmpty( pStack ) )
		return pStack->cKey;
	return 0;
}
void del( StackItem **pStack )
{
	if( !isEmpty( *pStack ) )
	{
		StackItem *p=*pStack; // najpierw podpinamy ten co chcemy usun��
		*pStack =p->pNext; // przypisujemy wska�nik pHead kt�ry wskazuje na g�owe stosu na element wcze�niejszy
		free( p ); // zwalniamy pami��
	}
	else
		cout <<"\n *!* Stack underflow!! ( DEL )\n\n";
}
int isEmpty( StackItem *pStack )
{
	return !pStack;
}



