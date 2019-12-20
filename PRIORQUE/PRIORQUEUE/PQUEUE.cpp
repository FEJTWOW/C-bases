#include "PQUEUE.h"

void UpdateDown( PQueue* PQ, int l, int p );
void UpdateUp( PQueue* PQ, int l, int p );

PQueue* PQInit( int nSize )
{
	PQueue* prio = ( PQueue* ) calloc( 1, sizeof( PQueue ) ); // alokacja pamieci dla naszej g³ównej struktury
	if( !prio )
	{
		perror( "Blad alokacji pamieci!!@!" );
		return NULL;
	}
	prio->item = ( PQItem** ) calloc( nSize, sizeof( PQItem* ) ); // tworzenie tablicy wskaŸników
	/*for( int i = 0; i<nSize; i++ )
	{
		prio->item[i] = ( PQItem* ) calloc( 1, sizeof( PQItem ) );
		if( !prio->item[i] )
		{
			perror( "Blad alokacji w alokowaniu tablicy wskaznikow!!!@!@!" );
			return NULL;
		}
	}*/
	if( !( prio->item ) )
	{
		perror( "Blad alokacji pamieci !@!@! prio->PQ" );
		return NULL;
	}
	prio->PQSize = nSize; // ustawienie rozmiaru kolejki
	return prio;
}
int PQisEmpty( PQueue* PQ )
{
	return !( PQ->PQCurrSize );
}
void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior )
{
	if( PQ->PQCurrSize == PQ->PQSize )
	{
		perror( "Kolejka jest pelna nie mozesz nic dodac" );
		return;
	}
	PQ->item[PQ->PQCurrSize] = ( PQItem* ) calloc( 1, sizeof( PQItem ) ); // alokuje pamiêæ na strukture PQItem
	if( !PQ->item[PQ->PQCurrSize] )
	{
		perror( "Blad alokacji pamieci PQEnqueue@!@!" );
		return;
	}
	PQ->item[PQ->PQCurrSize]->pInfo = pInfo; // wybieram pierwszy wolne miejsce w tablicy przechodzimy wskaŸnikiem do 
	PQ->item[PQ->PQCurrSize]->nPrior = nPrior; // ustawiamy priorytet danemu elementowi
	//PQ->PQCurrSize++;
	UpdateUp( PQ, 0, PQ->PQCurrSize++ );
	//printf( "\n\n" );
	//PQPrint( PQ );

}
PQItem* PQDequeue( PQueue* PQ )
{
	if( PQisEmpty( PQ ) )
	{
		perror( "Kolejka jest pusta, nie mozesz usunac elementu!" );
		return NULL;
	}
	PQItem* returnval = PQ->item[0];
	PQ->item[0] = PQ->item[--PQ->PQCurrSize]; // ostatni przerzucam na sam pocz¹tek i uaktualniam w dól
	UpdateDown( PQ, 0, PQ->PQCurrSize );
	return returnval;
}
void PQClearQueue( PQueue* PQ )
{
	while( !PQisEmpty( PQ ) )
	{
		PQItem* remove = PQDequeue( PQ );
		printf( "%d o prio: %d\n", remove->pInfo->nKey, remove->nPrior );
		free( remove );
	}
}
void PQRealease( PQueue** PQ )
{
	PQClearQueue( *PQ );
	free( (*PQ)->item );
	free( *PQ );
	*PQ = NULL;
}
void PQPrint( PQueue* PQ )
{
	for( int i = 0; i<PQ->PQCurrSize; ++i )
		printf( "%d o prio: %d\n", PQ->item[i]->pInfo->nKey, PQ->item[i]->nPrior );
}

void inorder( PQueue* PQ, int root )
{
	int leftchild = root*2+1;
	int rightchild = root*2+2;

	if( leftchild<PQ->PQCurrSize )
		inorder( PQ, leftchild ); // idziemy maksymalnie w lewo
	printf( "%d o prio %d\n", PQ->item[root]->pInfo->nKey, PQ->item[root]->nPrior ); // kiedy ju¿ nie mo¿emy to wypisujemy wartoœæ
	if( rightchild<PQ->PQCurrSize ) // idziemy w prawo kiedy ju¿ nie mo¿emy w lewo
		inorder( PQ, rightchild );

}
void DecreaseKey( PQueue* PQ, int i, int nPrior )
{
	if( nPrior<PQ->item[i]->nPrior )
	{
		PQ->item[i]->nPrior = nPrior;
		UpdateDown( PQ, i, PQ->PQCurrSize-1);
	}
}
void IncreaseKey( PQueue* PQ, int i, int nPrior )
{
	if( nPrior>PQ->item[i]->nPrior )
	{
		PQ->item[i]->nPrior = nPrior;
		UpdateUp( PQ, 0, i);
	}
}
void UpdateDown( PQueue* PQ, int l, int p )
{
	if( l==p ) return;
	int i = l;
	int j = 2*i+1;
	PQItem* x = PQ->item[l];
	while( j<=p )
	{
		if( j<p )// sprawdzamy czy jest prawe dziecko
			if( PQ->item[j]->nPrior < PQ->item[j+1]->nPrior ) j++; // jeœli priorytet lewego dziecka jest mniejszy ni¿ prawego to przechodzimy na prawe
		
		if( x->nPrior > PQ->item[j]->nPrior ) break;// jeœli priorytet rodzica jest wiêkszy ni¿ wiêkszego z dzieci to jest ok i wychodzimy
		// alternatywnie mo¿na w tym ifie daæ x->nPrior i wtedy nie musimy robiæ tego wpisywania w linijcie 133 tylko musimy zrobiæ to jedno na koñcu co jest w 137 linijce
		PQ->item[i] = PQ->item[j]; // w miejsce rodzica przypisujemy wiêksze z dzieci
		//PQ->item[j] = x;
 		i = j; // przechodzimy na indeks dziecka
		j = 2*i+1; // wyliczamy dzieci tego dziecka
	}
	PQ->item[i] = x;
	//printf( "\n\n" );
	//PQPrint( PQ );
}
void UpdateUp( PQueue* PQ, int l, int p )
{
	if( l==p ) return;
	int i = p; // dziecko
	int j = (i-1)/2; // rodzic
	PQItem* x = PQ->item[i];
	while( i>0 )
	{
		/*if( PQ->item[i]->nPrior > PQ->item[i-1]->nPrior ) // jeœli to prawe dziecko to musimy wiedzieæ czy jego prio jest wiêksze ni¿ lewego dziecka
		{
			PQItem* temp = PQ->item[i];
			PQ->item[i] = PQ->item[i-1];
			PQ->item[i-1] = PQ->item[i];
			--i;
		}*/
		if( x->nPrior < PQ->item[j]->nPrior ) break; // je¿eli prio dziecka jest mniejsze od rodzica to jest ok
		

		PQ->item[i] = PQ->item[j];
		//PQ->item[j] = x;
		i = j;
		j = (i-1)/2;
	}
	PQ->item[i] = x;

}


