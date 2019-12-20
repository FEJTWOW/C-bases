#include "Data.h"
#define DEBUG1

int SetSex( Player* p, char c )
{
	switch( c )
	{
		case 'm':
		case 'M': p->sex = MALE; break;
		case 'f':
		case 'F': p->sex = FEMALE; break;
		default: return 0;
	}

	return 1;
}

int SetDate( Player* p, int d, int m, int y )
{
	if( ( d>31 )||( d<1 )||( m<1 )||( m>12 )||( y<1970 ) ) return 0;
	
	p->betdate.nDay = d;
	p->betdate.nYear = y;
	p->betdate.Month = m;
	tm data = { 0, 0, 0, d, m-1, y-1900 };
	mktime( &data ); // konwertuje strukture tm do time_t
	switch( data.tm_wday )
	{
		case 0: p->betdate.weekDay = Sun; break;
		case 1: p->betdate.weekDay = Mon; break;
		case 2: p->betdate.weekDay = Tue; break;
		case 3: p->betdate.weekDay = Wen; break;
		case 4: p->betdate.weekDay = Thu; break;
		case 5: p->betdate.weekDay = Fri; break;
		case 6: p->betdate.weekDay = Sat; break;
		default: return 0;
	}

	switch( m )
	{
		case 1: p->betdate.name_of_month = Jan; break;
		case 2: p->betdate.name_of_month = Feb; break;
		case 3: p->betdate.name_of_month = Mar; break;
		case 4: p->betdate.name_of_month = Apr; break;
		case 5: p->betdate.name_of_month = May; break;
		case 6: p->betdate.name_of_month = Jun; break;
		case 7: p->betdate.name_of_month = Jul; break;
		case 8: p->betdate.name_of_month = Aug; break;
		case 9: p->betdate.name_of_month = Sep; break;
		case 10: p->betdate.name_of_month = Oct; break;
		case 11: p->betdate.name_of_month = Nov; break;
		case 12: p->betdate.name_of_month = Dec; break;
		default: return 0;
		
	}
	return 1;
	
}

int SetHour( Player* p, int hh, int mm )
{
	if( ( hh<0 )||( hh>23 )||( mm<0 )||( mm>59 ) )
	{
		printf( "Zle godziny lub minuty@!@!@!" );
		return 0;
	}
	p->hour=hh;
	p->minutes=mm;
	return 1;
}

int AllocAddMem( Player*** pTab, int nCurrSize )
{
	Player** copy_in_case_of_fail = *pTab;
	*pTab = ( Player** ) realloc( *pTab, ( nCurrSize+ALLOCPLAYER )*sizeof( Player* )  );

	if( pTab )
	{
		memset( *pTab+nCurrSize, 0, ALLOCPLAYER*sizeof( Player* ) );
		return ALLOCPLAYER;
	}

	printf( "Blad w realokacji podczas dodawania gracza!!" );
	*pTab = copy_in_case_of_fail;
	return 0;

	// uzywa funkcji "realloc" i memset
	// przy czym jeœli siê nie powiod³o
	// to nie mo¿na straciæ do tej pory czytanych danych i program ma dzialac dalej
	// z tym ze zwraca wtedy wartosc zero
	// w przypadku powodzenia realokacjii zwraca o ile realokowano!!!\
	// tablice gracyz realokujemy co cztetry element tablice zak³adów co dwa
	// *pTab nie mozemy stracic mozna wczesniej zapamietac albo przywrocic z kopii 
}

int AllocAddBetMem( Player* pTab, int nCurrSizeNormalBets )
{
	int** copy_in_case_of_fail = pTab->bets;
	pTab->bets = ( int** ) realloc( pTab->bets, ( nCurrSizeNormalBets+ALLOCBET )*sizeof( int* ) );
	if( pTab->bets )
	{
		memset( pTab->bets+nCurrSizeNormalBets, 0, ALLOCBET*sizeof( int* ) );
		return ALLOCBET;
	}

	printf( "Blad w realokacji zakladow!!@!!" );
	pTab->bets = copy_in_case_of_fail;
	return 0;
}

void FreeMem( Player*** pTab, int nPlayersNo )
{
	Player** helper = *pTab;
	for( int i = 0; i<nPlayersNo; i++ )
	{
		Player* remove = *helper++; // podpinamy sobie playera i przechodzimy na kolejnego 
		int** hel = remove->bets;
		for( int j = 0; j<remove->currentbets; j++ )
		{
			int* rem = *hel++;
			free( rem ); // usuwamy kolejne kolumny betow
		}
		free( remove->bets ); // usuwamy tablice wskaznikow do zakladow
		free( remove->name ); // usuwamy imie
		free( remove->surrname ); // usuwamy nazwisko 
		free( remove );

	}
	free( *pTab );
}

int ReadData( Player*** pAllDraws, const char* sfileName )
{
	FILE* p = fopen( sfileName, "r" );
	if( !p )
	{
		printf( "Nie mozna przeczytac pliku!@!@!(READDATA)" );
		return 0;
	}

	//Player** Array_of_players = *pAllDraws;
	
	int current_number_of_players = 0; // obecna liczba graczy
	int maximum_allocated_players = 0; // maksymalna zaalokowana
	char c;

	while( !feof( p ) )
	{
		if( ( c = getc( p ) )=='*' )
		{
			if( current_number_of_players==maximum_allocated_players ) // jesli liczba graczy osiagnie maksymalna to musimy zrobic realloca
			{
				maximum_allocated_players += AllocAddMem( pAllDraws, current_number_of_players );
				if( maximum_allocated_players==current_number_of_players ) // jak realokacja sie nie powiedzie to liczba obecnych graczy wynosi maksymalna
				{
					printf( "Realokacja nie powiodla sie!@!@. Nie mozna dodac gracza" );
					break;
				}
			}

			Player* new_player = (*pAllDraws)[current_number_of_players] = ( Player* ) calloc( 1, sizeof( Player ) );
			if( !new_player )
			{
				printf( "Blad w tworzeniu gracza!@!@!@" );
				break;
			}
		 // zwiekszam liczbe graczy bo potem i tak juz nie uzywam tej zmiennej
			int d, m, y, hh, mm;
			char sex;

			new_player->name = ( char* ) calloc( MAXNAME, sizeof( char ) );
			new_player->surrname = ( char* ) calloc( MAXNAME, sizeof( char ) );

			fscanf( p, "%s %s %c %4c %2c %2c %3c %2c %2c %8c %16c %d:%d %d/%d/%d %11c",
					new_player->surrname, new_player->name, &sex, new_player->bankacc.AccSwift.bankid,
					new_player->bankacc.AccSwift.countryid, new_player->bankacc.AccSwift.location, new_player->bankacc.AccSwift.banklocation,
					new_player->bankacc.AccIban.country, new_player->bankacc.AccIban.sum, new_player->bankacc.AccIban.banknumber,
					new_player->bankacc.AccIban.account, &hh, &mm, &d, &m, &y, new_player->pesel );

		#ifdef DEBUG1
			printf( "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" );
			printf( "nazwisko: %s ", new_player->surrname );
			printf( "imie: %s ", new_player->name );
			printf( "plec: %c ", sex );
			printf( "swift: %.4s ", new_player->bankacc.AccSwift.bankid );
			printf( "%.2s ", new_player->bankacc.AccSwift.countryid );
			printf( "%.2s ", new_player->bankacc.AccSwift.location );
			printf( "%.3s ", new_player->bankacc.AccSwift.banklocation );
			printf( "iban: %.2s ", new_player->bankacc.AccIban.country );
			printf( "%.2s ", new_player->bankacc.AccIban.sum );
			printf( "%.8s ", new_player->bankacc.AccIban.banknumber );
			printf( "%.16s ", new_player->bankacc.AccIban.account );
			printf( "data: %d/%d/%d ", d, m, y );
			printf( "pesel: %.11s\n", new_player->pesel );
		#endif

			if( !SetSex( new_player, sex ) )
			{
				printf( "Blad przy ustalaniu plci!@!@!@" );
				break;
			}
			if( !SetDate( new_player, d, m, y ) )
			{
				printf( "Blad przy ustalaniu daty@!@!@" );
				break;
			}
			if( !SetHour( new_player, hh, mm ) )
			{
				printf( "Blad przy ustalaniu godziny!@!@!" );
				break;
			}


			fscanf( p, "\n" );
			
			//int number_of_normal_draws = 0;

			while( ( c = getc( p ) )!= '*' && !feof( p ) )
			{
				ungetc( c, p );

				if( new_player->currentbets==new_player->DrawMax )
				{
					new_player->DrawMax += AllocAddBetMem( new_player, new_player->currentbets );
					if( new_player->currentbets==new_player->DrawMax )
					{
						printf( "Nie powiodla sie realokacja betowania!@!@!@\n\n" );
						break;
					}
				}

				int* helper = new_player->bets[new_player->currentbets++] = ( int* ) calloc( MAXBETS, sizeof( int ) );
				if( !helper )
				{
					printf( "Blad przy alokacji miejsc na zaklady!@!@!" );
					break;
				}
				//int* helper = new_player->bets[new_player->currentbets++];
				for( int i = 0; i<MAXBETS; i++, helper++ )
				{
					fscanf( p, "%d", helper );
		//			printf( "%d ", *helper ); // jak to zakomentujesz to pamietaj zeby zwiekszyc helpera w linijce wyzej bo inaczej sie wysypie
				}
				//printf( "\n" );
				fscanf( p, "\n" );
			}
			if( !feof( p ) ) ungetc( c, p );
			

		}
		else
		{
			printf( "Blad podczas czytania danych !@!@!@" );
			break;
		}
		current_number_of_players++;
	}
	return current_number_of_players;
}