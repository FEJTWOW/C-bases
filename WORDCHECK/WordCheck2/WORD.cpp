#include "WORD.h"

void inOrder( TreeElem* root, FILE* output )
{
	if( root->pLeft )
		inOrder( root->pLeft, output ); // idziemy maksymalnie w lewo
	fprintf( output,  "%s | %d | ", root->pWord, root->nNo ); // wypisujemy zawartoœæ noda
	ListItem* helper = root->List->pHead; // pomocniczy wskaznik na poczatek kolejki
	while( helper )
	{
		fprintf( output, "%d ", helper->nLine );
		helper = helper->pNext;
	}
	fprintf( output, "\n" );
	if( root->pRight ) // idziemy w prawo kiedy ju¿ nie mo¿emy w lewo
		inOrder( root->pRight, output );
}



int compare( char* l, char* p )
{
	char* modstr1 = ( char* ) calloc( strlen( l )+1, sizeof( char ) ); // strlen nie wlicza zera!@!@!@!@!@!
	char* modstr2 = ( char* ) calloc( strlen( p )+1, sizeof( char ) );
	memcpy( modstr1, l, strlen( l )+1 );
	memcpy( modstr2, p, strlen( p )+1 );
	_strlwr( modstr1 );
	_strlwr( modstr2 );
	int temp = strcmp( modstr1, modstr2 ); // strcmp zwraca wartosc wieksza od 0 jak modstr1 > modstr2, 0 jak rowne i  
	free( modstr1 );
	free( modstr2 );
	return temp;
}


void FindAndInsert( char* word, TreeElem** root, int line_number )
{
	if( !*root )
	{
		char* strinkhelper = ( char* ) calloc( strlen( word ) +1, sizeof( char ) );
		if( !strinkhelper )
		{
			printf( "Blad w alokacji pamieci!@!@(FINDANDINSERT)" );
			return;
		}
		memcpy( strinkhelper, word, strlen( word ) + 1 ); // kopiujemy to co w word do nowego stringa ( bo bufor jest statyczny )
		*root = ( TreeElem* ) calloc( 1, sizeof( TreeElem ) );
		if( !*root )
		{
			printf( "Blad alokacji pamieci dla *root( FIND AND INSERT )!@!@!" );
			return;
		}
		( *root )->nNo = 1;
		( *root )->List = ( ListHead* ) calloc( 1, sizeof( ListHead ) );
		( *root )->List->pHead = ( *root )->List->pTail = ( ListItem* ) calloc( 1, sizeof( ListItem ) );
		( *root )->List->pTail->nLine = line_number; 
		( *root )->pWord = strinkhelper; // przypisujemy nasze s³owo
	}
	else if( ( compare( word, ( *root )->pWord ) )<0 )
		FindAndInsert( word, &( *root )->pLeft, line_number );
	else if ( ( compare( word, ( *root )->pWord ) )>0 )
		FindAndInsert( word, &( *root )->pRight, line_number );
	else // jak tutaj wchodzimy to znaczy ¿e znaleŸliœmy to samo s³owo
	{
		( *root )->nNo++;
		if( ( *root )->List->pTail->nLine==line_number ) return; // to oznacza ¿e znaleŸliœmy drugie takie samo s³owo w tej samej lini czyli nie musimy tworzyæ nowego elementu listy
		ListItem* nowy_elem = ( ListItem* ) calloc( 1, sizeof( ListItem ) );
		if( !nowy_elem )
		{
			printf( "Blad w alokacji pamieci dla listy(FINDANDINSER)!@!@!" );
			return;
		}
		nowy_elem->nLine = line_number;
		(*root)->List->pTail->pNext = nowy_elem;
		(*root)->List->pTail = nowy_elem;
	}
}


int isWord( char* s ) // funckja z pierwszego sema 
{
	if( s[0]=='_'||( s[0]>='a' && s[0]<='z' )||( s[0]>='A' && s[0]<='Z' ) )
	{
		int i = 1;
		while( s[i] )
		{
			if( !( s[i]=='_'||( s[i]>='a' && s[i]<='z' )||( s[i]>='A' && s[i]<='Z' )||( s[i]>='0' && s[i]<='9' ) ) )
				return 0;
			i++;
		}
		return 1;
	}
	return 0;

}




int ReadData( TreeElem** root, const char* sfileName )
{
    FILE* p = fopen( sfileName, "r" );
	if( !p )
	{
		printf( "Brak pliku do odczytu!@!@!@!(READDATA)" );
		return 0;
	}
	const char* korektor = " >\"*)(#,.-:;\t";
	//char str[MAXCHAR] = { 0 };
	char* str = ( char* ) calloc( MAXCHAR, sizeof( char ) );
	int lnumber = 1;


	while( fgets( str, MAXCHAR, p ) ) // pobieramy linie z tesktu
	{
		char* schowek = strtok( str, korektor ); // do naszego schowka trafia linia która odpowiednio jest zkorektowana
		while( schowek ) // czytamy nasze wyrazy
		{
			if( !isWord( schowek ) ) // sprawdxamy czy nasz wyraz jest identyfikatorem( mo¿na dodaæ dodatkowe znaki do korektora ale wtedy bêdziemy czytaæ wyrazy które nie powinniœmy np char* )
			{
				schowek = strtok( NULL, korektor );
				continue;
			}
			FindAndInsert( schowek, root, lnumber );
			schowek = strtok( NULL, korektor );
		}
		lnumber++;
		memset( str, 0, MAXCHAR*sizeof( char ) );
	}
	free( str );
	fclose( p );
	return 0;

}

void FreeMemory( TreeElem** root )
{
	if( ( *root )->pLeft )
		FreeMemory( &( *root )->pLeft );
	if( ( *root )->pRight )
		FreeMemory( &( *root )->pRight );
	while( ( *root )->List->pHead )
	{
		ListItem* remove = ( *root )->List->pHead;
		( *root )->List->pHead = remove->pNext;
		free( remove );
	}
	free( ( *root )->List );
	free( ( *root )->pWord );
	free( *root );

}
