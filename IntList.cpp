
#include "IntList.h"
//---------------------------------------------------------------------------
// 建構函式
CIntList::CIntList(int iFileCount)
{
	FileCount = iFileCount;
	Total = 0;
	Ints = 0;
	Ints = new int[FileCount];
}
//---------------------------------------------------------------------------
// 解構函式
CIntList::~CIntList(void)
{
	if(Ints) delete[] Ints;
}
//---------------------------------------------------------------------------
// 全部清掉
void CIntList::ClearAll(void)
{
	for(int i=0; i<FileCount; i++)
	{
		Ints[i] = 0;
	}
	Total = 0;
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::operator=(CIntList * ilTarget)
{
	Copy(ilTarget);
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::Copy(CIntList * ilTarget)
{
	for (int i=0; i<FileCount; i++)
	{
		Ints[i] = ilTarget->Ints[i];
	}
	Total = ilTarget->Total;
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::operator&=(CIntList * ilTarget)
{
	AndIt(ilTarget);
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::AndIt(CIntList * ilTarget)
{
	Total = 0;
	for (int i=0; i<FileCount; i++)
	{
		if((Ints[i] > 0) && (ilTarget->Ints[i] > 0))	// 這樣才能 and 運算
		{
			Ints[i] += ilTarget->Ints[i];
			Total += Ints[i];
		}
		else
		{
			Ints[i] = 0;
		}
	}
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::operator|=(CIntList * ilTarget)
{
	OrIt(ilTarget);
}
//---------------------------------------------------------------------------
// 運算子多載
void CIntList::OrIt(CIntList * ilTarget)
{
	for (int i=0; i<FileCount; i++)
	{
		Ints[i] += ilTarget->Ints[i];
	}
	Total += ilTarget->Total;
}
//---------------------------------------------------------------------------
