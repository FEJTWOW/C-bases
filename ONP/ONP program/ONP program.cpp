// ONP program.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <stdio.h>
#include "Stack.h"
#include <math.h>
#include "DStack.h"

#define DOT '.'

void skipSpaces();
double getNum();
int isDigit( char c );
char getOper();
int isOper( char cOper );
int prior( char cOper );
double Calc( double arg1, double arg2, char cOperator );
double ONP();
void CalcInBrackets(StackItem **pStack, DStackItem **pDStack );


int main( int argc, char *argv[] )
{	
	printf( "Podaj wyrazenie: " );
	printf("\n\n %f", ONP() );
	
	return 0;
}
void skipSpaces()
{
	char c;
	while( ( c=getchar() ) ==' ' );
	ungetc( c,stdin );
}
double getNum()
{
	char c;
	double num=0;
	int sign=0;
	skipSpaces();
//	( c=getchar() == '-' ) ? o=-1 : ungetc( c, stdin );
	if( ( c=getchar() ) == '+' || c == '-' )
	{
		if( c =='-' ) sign = -1;
	}
	else ungetc( c, stdin );
	while( isDigit( c=getchar() ) )
		num=num*10+( c-'0' );
	if( c==DOT )
	{
		double coef=0.1;
		while( isDigit( c=getchar() ) )
		{	
			num+=(c-'0')*coef;
			coef*=0.1;
		}
			
		
	}
	ungetc( c,stdin );
	return ( sign ) ? -num : num ;
}
int isDigit( char c )
{
	return ( c>='0' ) && ( c<='9' );
}
char getOper()
{
	skipSpaces();
	return getchar();
}
int isOper( char cOper )
{
	switch( cOper )
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
	case '(':
	case ')': return 1;
	}
	return 0;
	
}
int prior( char cOper )
{
	switch( cOper )
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}
double ONP()
{
	char c;
	StackItem *pStack = NULL;
	makeEmptyStack( &pStack );
	DStackItem *pDStack = NULL;
	dmakeEmptyStack( &pDStack );
//	if( ( c = getOper() ) == '(' ) push ( &pStack, c );
//	else ungetc ( c, stdin );
	while( ( c=getOper() ) == '-' ) push( &pStack, c );
	ungetc( c, stdin );
	while( ( c=getOper() ) == '(' )
	{
		push( &pStack, c );
		if( ( c = getOper() ) == '-' ) 
		{
			push( &pStack, c );
			dpush( &pDStack, 0 );
		}
		else ungetc( c, stdin );
	}
	ungetc( c, stdin );
	dpush ( &pDStack, getNum () );
	while( isOper( c=getOper() ) )
	{
		if( c == ')' )
		{
			CalcInBrackets( &pStack, &pDStack );
			continue;
		}
		else if( c == '(' )
		{
			push( &pStack, c );
			if( ( c = getOper () ) == '-' )
			{
				push ( &pStack, c );
				dpush( &pDStack, 0 );
			}
			else ungetc ( c, stdin );
			if( ( c = getOper() ) == '(' )
			{
				ungetc( c, stdin );
				continue;
			}
			ungetc( c, stdin );
			dpush( &pDStack, getNum() );
			continue;
		}
	
		while( prior(c) <= prior( top( pStack ) ) )
		{
			double arg2 = dpop( &pDStack );
			dpush( &pDStack , Calc( dpop( &pDStack ), arg2, pop( &pStack ) ) );

		}
		push( &pStack, c );
		if( ( c = getOper () ) != '(' )
		{
			ungetc( c, stdin );
			dpush( &pDStack, getNum() );
		}
		else ungetc( c, stdin );
	}
	while( !isEmpty( pStack ) )
	{
		double arg2 = dpop ( &pDStack );
		dpush ( &pDStack, Calc ( dpop ( &pDStack ), arg2, pop ( &pStack ) ) );
	}

	return dpop( &pDStack );
	
}

double Calc( double arg1, double arg2, char cOperator )
{
	switch( cOperator )
	{
		case '+': return arg1 + arg2;
		case '-': return arg1 - arg2;
		case '*': return arg1 * arg2;
		case '/': if( fabs ( arg2 > 1e-14 ) ) return arg1/arg2;
				cout<< "Error: division by 0!!\n";
				break;
		case '^': return pow( arg1,arg2 ); 	
	}
	return 0;
}
void CalcInBrackets(StackItem **pStack, DStackItem **pDStack )
{
	char c;
	while( ( c = pop( pStack ) ) != '('  )
	{
		double arg2 = dpop ( pDStack );
		dpush ( pDStack, Calc ( dpop ( pDStack ), arg2, c ) );
	}
			
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
