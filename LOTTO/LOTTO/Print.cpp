#include "Print.h"
#include "defs.h"

void PrintSex( FILE* fout, Player* p )
{
	switch( p->sex )
	{
		case FEMALE: fprintf( fout, "Woman " ); break;
		case MALE: fprintf( fout, "Man " ); break;
	}
}

void PrintDate( FILE* fout, Player* p )
{
	//printf( "\n\n %d", p->betdate.weekDay );
	switch( p->betdate.weekDay )
	{
		case Mon:fprintf( fout, "Mon " ); break;
		case Tue:fprintf( fout, "Tue " ); break;
		case Wen:fprintf( fout, "Wen " ); break;
		case Thu:fprintf( fout, "Thu " ); break;
		case Fri:fprintf( fout, "Fri " ); break;
		case Sat:fprintf( fout, "Sat " ); break;
		case Sun:fprintf( fout, "Sun " ); break;
	}
	fprintf( fout, "%d ", p->betdate.nDay );

	switch( p->betdate.name_of_month )
	{
		case Jan: fprintf( fout, "Jan " ); break;
		case Feb: fprintf( fout, "Feb " ); break;
		case Mar: fprintf( fout, "Mar " ); break;
		case Apr: fprintf( fout, "Apr " ); break;
		case May: fprintf( fout, "May " ); break;
		case Jun: fprintf( fout, "Jun " ); break;
		case Jul: fprintf( fout, "Jul " ); break;
		case Aug: fprintf( fout, "Aug " ); break;
		case Sep: fprintf( fout, "Sep " ); break;
		case Oct: fprintf( fout, "Oct " ); break;
		case Nov: fprintf( fout, "Nov " ); break;
		case Dec: fprintf( fout, "Dec " ); break;
	}
	fprintf( fout, "%d ", p->betdate.nYear );
}
void PrintHour( FILE* fout, Player* p )
{
	fprintf( fout, "%02d:%02d ", p->hour, p->minutes );
}
void PrintBets( FILE* fout, Player* pPlayers ) // jak w macierzach 
{
	int** helper = pPlayers->bets;
	for( int i = 0; i<pPlayers->currentbets; i++ )
	{
		int* printer = *helper++;
		for( int j = 0; j<MAXBETS; j++ )
			fprintf( fout, "%d ", *printer++ );
		fprintf( fout, "\n" );
	}
}

void PrintResults( int* pNums49, Player** pPlayers, int nPlayersNo ) 
{
	FILE* p = fopen( "res.txt", "w" );
	if( !p )
	{
		printf( "Nie mozna zrobic pliku do zapisu@!@!@!" );
		return;
	}
	//printf( "resultsprint %d\n", nPlayersNo );
	Player** helper = pPlayers;
	for( int i = 0; i<nPlayersNo; ++i ) // przechodzimy po wszystkich graczach
	{
		Player* printer = *helper++;
		fprintf( p, "%s %s ", printer->surrname, printer->name );
		PrintSex( p, printer );
		PrintDate( p, printer );
		PrintHour( p, printer );
		fprintf( p, "\n" );
		PrintBets( p, printer );
	}
	fprintf( p, "\n" );
	for( int i = 0; i<NUMS; i++ )
	{
		//int* helper = pNums49[i];
		fprintf( p, " %2d:%2d | ", i+1, *pNums49++ ); // dajemy i+1 bo w tablicy przy indeksie 0 mamy wartosc dla 1
		if( !((i+1)%6) ) fprintf( p, "\n" );
	}
	fclose( p );
}