#include "Stack.h"


void makeEmptyStack( StackItem  **pStack )
{
	while( !isEmpty(*pStack) ) del(pStack);
	( *pStack ) = NULL;
}
void push( StackItem **pStack ,char c )
{
	StackItem* p = ( StackItem* )malloc( sizeof( StackItem ) ); // malloc rezerwuje nam nowy obszar
	if( p )   													// w pamiêci na który zwraca nam adres 
	{
		p->cKey=c;
		p->pNext = *pStack; // przypisujemy wskaŸnikowi pNext wskaŸnik pHead który wskazuje na wczeœniejszy element
		*pStack = p; // teraz przypisujemy wskaŸnikowi pHead wskaŸnik p który wskazuje na nowo utowrzony element
	}

}
char pop( StackItem **pStack )
{
	char c = top( *pStack ); // do funkcji przekazujemy orygina³ pHead zatem bierzemy to na co wskazuje pHead
	if( c )
		del( pStack ); // usuwamy orygina³, czyli pHead
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
		StackItem *p=*pStack; // najpierw podpinamy ten co chcemy usun¹æ
		*pStack =p->pNext; // przypisujemy wskaŸnik pHead który wskazuje na g³owe stosu na element wczeœniejszy
		free( p ); // zwalniamy pamiêæ
	}
	else
		cout <<"\n *!* Stack underflow!! ( DEL )\n\n";
}
int isEmpty( StackItem *pStack )
{
	return !pStack;
}



