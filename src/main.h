#ifndef mainH
#define mainH

//---------------------------------------------------------------------------
#include <iostream>
#include <assert.h>
#include "TestUnit.h"
#include "Monster.h"
#include "TinyIni.h"
#include "mydebug.h"
//---------------------------------------------------------------------------

void RunFullTextSearch(string sIniFile, string sSearchStr, int iStartNum, int iListCount);
void TestFullTextSearch(string sIniFile);
void ShowTestResult(CMonster * SearchEngine, string sSearchStr, int iResult);

#endif
