#pragma once
#include "defs.h"


int ReadData( Player*** pAllDraws, const char* sfileName );
void FreeMem( Player*** pTab, int nPlayersNo );