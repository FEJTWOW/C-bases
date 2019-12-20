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
		ListItem* remove = pAfter->m_pNext;  // tworzymy wskaŸnik pomocniczy do którego przypisujemy wskaŸnik na element który chcemy usun¹æ
		pAfter->m_pNext = remove->m_pNext; // przeczepiamy "obok" danego elementu wskaŸniki ¿eby móc go spokojnie usun¹æ
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
	h->m_pInfo = pInfo; // przypsuje wskaŸnik do wartoœci do nowego elementu
	h->m_pNext = pAfter->m_pNext; // ustawiam wskaŸnik na element za pAfter
	pAfter->m_pNext = h; // przepinam wskaŸnik pAfter na nasz nowy element
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
	ListItem* helper = p->m_pNext; // ustawiamy wskaŸnik na pierwszym elemencie do rozpatrzenia bo p wskazuje na wartownika
	*previous = p; // previous jest wy/we wiêc mo¿e byæ sytuacja ¿e szukany element bêdzie pierwszy
	while( helper ) // nie mo¿emy helper->m_pNext bo pominiemy ostatni element
	{
		if( compare( (const void*)helper->m_pInfo, value ) == 0 ) // podaje wskaŸniki bo do wartoœci odwo³uje siê w compare!!!
			return helper; // jeœli helper wskazuje na element listy który zawiera strukture w której jest nasza szukana wartoœæ to go zwracamy
		*previous = helper; // wskaŸnikiem previous przechodzimy dalej w razie gdy nie znajdziemy naszego elementu
		helper = helper->m_pNext; // przechodzimy do kolejnego elementu listy
	}
	return *previous = NULL; // jeœli nie znajdziemy naszej wartoœci to zwracamy previous który wskazuje na NULLA;
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
			if( compare( ( const void* ) ( pMin->m_pNext->m_pInfo ), ( const void* ) ( pNext->m_pNext->m_pInfo ) )==1 ) // porównujemy kolejne elementy
				pMin = pNext; // pMin wskazuje na element o jeden wczeœniej ni¿ minimalny
			pNext = pNext->m_pNext;	// przechodzimy dalej w liœcie
		}
		if( helper!=pMin )
		{
			pNext = pMin->m_pNext->m_pNext; // podczepiam koñcówkê
			pMin->m_pNext->m_pNext = helper->m_pNext; // podpinam m_pNext mojego najmniejszego elementu przed najmniejszy element ( na pocz¹tku przed wartownika ) do kolejnego elementu który bêdzie przed nim
			helper->m_pNext = pMin->m_pNext; // nastêpnie podpinam wskaŸnik m_pNext od najmniejszego elementu ( na pocz¹tku od wartownika ) do znalezionego minimum
			pMin->m_pNext = pNext; // podpinam wskaŸnik który wskazywa³ na znalezione minimum do reszty listy ( tej któr¹ ³apa³em wskaŸnikiem na samym pocz¹tku )
		}
		helper = helper->m_pNext; // przechodze dalej i szukam kolejnego minimum
	}
}







