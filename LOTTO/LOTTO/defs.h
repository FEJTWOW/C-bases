#pragma once
#include <time.h>
#include <memory.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
typedef enum { MALE, FEMALE } SexType;
typedef enum { Mon, Tue, Wen=9, Thu, Fri, Sat, Sun } DayNames;
typedef enum { Jan, Feb=6, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec } MonthNames;

/*#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)*/

#define MAXBETS 6
#define MAXEXTRABETS 2
#define NUMS 49

#define ALLOCPLAYER 4
#define ALLOCBET 2
#define MAXNAME 31
#define SIZEOFPESEL 11
#define HOUR 5

#define COUNTRYCODE 2
#define CONTROLSUM 2
#define BANKNUM 8
#define CLIENTACCOUNT 16

#define SWIFTID 4
#define SWIFTCOUNTRY 5
#define SWIFTLOCATION 2
#define SWIFTBANKLOCATION 3


typedef struct
{
	DayNames weekDay;
	MonthNames name_of_month;
	int nDay;
	int Month;
	int nYear;
} Date;

typedef struct
{
	char country[COUNTRYCODE];
	char sum[CONTROLSUM];
	char banknumber[BANKNUM];
	char account[CLIENTACCOUNT];
} IBan;

typedef struct
{
	char bankid[SWIFTID];
	char countryid[SWIFTCOUNTRY];
	char location[SWIFTLOCATION];
	char banklocation[SWIFTBANKLOCATION];
} Swift;

typedef struct
{
	Swift AccSwift;
	IBan AccIban;
} Account;

typedef struct
{
	char* name;       //string
	char* surrname;   //string
	Account bankacc;
	Date betdate;
	int DrawMax;
	int** bets;
	int currentbets;
	SexType sex;
	char pesel[SIZEOFPESEL];
	int hour;
	int minutes;

} Player;

