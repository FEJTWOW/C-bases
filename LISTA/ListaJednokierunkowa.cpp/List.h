#ifndef LIST_H
#define LIST_H

#include <memory.h>
#include "global.h"


typedef int( *pointer_to_compare )( const void*, const void * ); //wskaünik na funkcje typu int przyjmujπcy dwa wskaüniki sta≥e const void

typedef struct tagListItem
{
	LISTINFO* m_pInfo; // int nKey;
	tagListItem* m_pNext;
} ListItem;


ListItem* CreateList(); // funkcja tworzπca liste
int isEmpty( ListItem* p ); // funckja sprawdza czy lista jest pusta
ListItem* Front( ListItem* p ); // funckja zwraca pierwszy element listy
void RemoveFront( ListItem* p ); // funkcja usuwa pierwszy element
void Remove( ListItem* pAfter ); // funkcja usuwa element po wybranym
void Insert( ListItem* pAfter, LISTINFO* pInfo ); // funkcja wstawia element po wybranym
void FreeList( ListItem* p ); // funkcja czyúci liste ( po za g≥owπ )
void DelList( ListItem** p ); // funckja czyúci liste wraz z g≥owπ
void InsertFront( ListItem* p, LISTINFO* pInfo ); // funkcja wstawia element na poczπtek listy
ListItem* Find( ListItem *p, const void* value, ListItem** previous, pointer_to_compare compare ); // funkcja znajduje element oraz zwraca wskaünik na element ktÛry go poprzedza
int compare( const void* p, const void *v ); // funkcja porÛwnuje dwie wartoúci
void SortList( ListItem* p, pointer_to_compare compare ); // funkcja sortujπca listy
#endif