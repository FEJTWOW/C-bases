#ifndef LIST_H
#define LIST_H

#include <memory.h>
#include "global.h"


typedef int( *pointer_to_compare )( const void*, const void * ); //wska�nik na funkcje typu int przyjmuj�cy dwa wska�niki sta�e const void

typedef struct tagListItem
{
	LISTINFO* m_pInfo; // int nKey;
	tagListItem* m_pNext;
} ListItem;


ListItem* CreateList(); // funkcja tworz�ca liste
int isEmpty( ListItem* p ); // funckja sprawdza czy lista jest pusta
ListItem* Front( ListItem* p ); // funckja zwraca pierwszy element listy
void RemoveFront( ListItem* p ); // funkcja usuwa pierwszy element
void Remove( ListItem* pAfter ); // funkcja usuwa element po wybranym
void Insert( ListItem* pAfter, LISTINFO* pInfo ); // funkcja wstawia element po wybranym
void FreeList( ListItem* p ); // funkcja czy�ci liste ( po za g�ow� )
void DelList( ListItem** p ); // funckja czy�ci liste wraz z g�ow�
void InsertFront( ListItem* p, LISTINFO* pInfo ); // funkcja wstawia element na pocz�tek listy
ListItem* Find( ListItem *p, const void* value, ListItem** previous, pointer_to_compare compare ); // funkcja znajduje element oraz zwraca wska�nik na element kt�ry go poprzedza
int compare( const void* p, const void *v ); // funkcja por�wnuje dwie warto�ci
void SortList( ListItem* p, pointer_to_compare compare ); // funkcja sortuj�ca listy
#endif