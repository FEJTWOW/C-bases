#include "List.h"

#include <memory.h>
#include <stdlib.h>

ListItem* CreateList()
{
	ListItem* p = ( ListItem* ) malloc( sizeof( ListItem ) );
	if( !p )
	{
		perror( "Memory allocation error! ( CREATE LIST )" );
		return NULL;
	}
	memset( p, 0, sizeof( ListItem ) );
	return p;
}

int isEmpty( ListItem* p )
{
	return !( p->m_pNext );
}

ListItem* Front( ListItem* p )
{
	if( isEmpty( p ) )
	{
		perror( "Lista jest pusta" );
	}
	return p->m_pNext;
}

void RemoveFront( ListItem* p )
{
	Remove( p );
}

void Remove( ListItem* pAfter )
{
	if( pAfter->m_pNext )
	{
		ListItem* remove = pAfter->m_pNext;  // tworzymy wska�nik pomocniczy do kt�rego przypisujemy wska�nik na element kt�ry chcemy usun��
		pAfter->m_pNext = remove->m_pNext; // przeczepiamy "obok" danego elementu wska�niki �eby m�c go spokojnie usun��
		free( remove->m_pInfo ); // usuwanie informacjii
		free( remove );  // usuwamy element
	}
}

void Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	ListItem* h = ( ListItem* ) malloc( sizeof( ListItem ) );
	if( !h )
	{
		perror( "Memory allocation error ( INSERT )" );
		return;
	}
	memset( h, 0, sizeof( ListItem ) );
	h->m_pInfo = pInfo; // przypsuje wska�nik do warto�ci do nowego elementu
	h->m_pNext = pAfter->m_pNext; // ustawiam wska�nik na element za pAfter
	pAfter->m_pNext = h; // przepinam wska�nik pAfter na nasz nowy element
}

void InsertFront( ListItem* p, LISTINFO* pInfo )
{
	Insert( p, pInfo );
}

void FreeList( ListItem *p )
{
	while( !isEmpty( p ) )
		RemoveFront( p );
}

void DelList( ListItem** p )
{
	FreeList( *p );
	free( *p );
	*p = NULL;
}


ListItem* Find( ListItem *p, const void* value, ListItem** previous, pointer_to_compare compare )
{
	ListItem* helper = p->m_pNext; // ustawiamy wska�nik na pierwszym elemencie do rozpatrzenia bo p wskazuje na wartownika
	*previous = p; // previous jest wy/we wi�c mo�e by� sytuacja �e szukany element b�dzie pierwszy
	while( helper ) // nie mo�emy helper->m_pNext bo pominiemy ostatni element
	{
		if( compare( (const void*)helper->m_pInfo, value ) == 0 ) // podaje wska�niki bo do warto�ci odwo�uje si� w compare!!!
			return helper; // je�li helper wskazuje na element listy kt�ry zawiera strukture w kt�rej jest nasza szukana warto�� to go zwracamy
		*previous = helper; // wska�nikiem previous przechodzimy dalej w razie gdy nie znajdziemy naszego elementu
		helper = helper->m_pNext; // przechodzimy do kolejnego elementu listy
	}
	return *previous = NULL; // je�li nie znajdziemy naszej warto�ci to zwracamy previous kt�ry wskazuje na NULLA;
}

void SortList( ListItem* p, pointer_to_compare compare )
{
	ListItem* helper = p;
	while( helper->m_pNext )
	{
		ListItem* pMin = helper;
		ListItem* pNext = pMin->m_pNext;
		while( pNext->m_pNext )
		{
			if( compare( ( const void* ) ( pMin->m_pNext->m_pInfo ), ( const void* ) ( pNext->m_pNext->m_pInfo ) )==1 ) // por�wnujemy kolejne elementy
				pMin = pNext; // pMin wskazuje na element o jeden wcze�niej ni� minimalny
			pNext = pNext->m_pNext;	// przechodzimy dalej w li�cie
		}
		if( helper!=pMin )
		{
			pNext = pMin->m_pNext->m_pNext; // podczepiam ko�c�wk�
			pMin->m_pNext->m_pNext = helper->m_pNext; // podpinam m_pNext mojego najmniejszego elementu przed najmniejszy element ( na pocz�tku przed wartownika ) do kolejnego elementu kt�ry b�dzie przed nim
			helper->m_pNext = pMin->m_pNext; // nast�pnie podpinam wska�nik m_pNext od najmniejszego elementu ( na pocz�tku od wartownika ) do znalezionego minimum
			pMin->m_pNext = pNext; // podpinam wska�nik kt�ry wskazywa� na znalezione minimum do reszty listy ( tej kt�r� �apa�em wska�nikiem na samym pocz�tku )
		}
		helper = helper->m_pNext; // przechodze dalej i szukam kolejnego minimum
	}
}







