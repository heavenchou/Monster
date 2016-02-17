
#include "IntList.h"
//---------------------------------------------------------------------------
// �غc�禡
CIntList::CIntList(int iFileCount)
{
	FileCount = iFileCount;
	Total = 0;
	Ints = 0;
	Ints = new int[FileCount];
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CIntList::~CIntList(void)
{
	if(Ints) delete[] Ints;
}
//---------------------------------------------------------------------------
// �����M��
void CIntList::ClearAll(void)
{
	for(int i=0; i<FileCount; i++)
	{
		Ints[i] = 0;
	}
	Total = 0;
}
//---------------------------------------------------------------------------
// �B��l�h��
void CIntList::operator=(CIntList * ilTarget)
{
	Copy(ilTarget);
}
//---------------------------------------------------------------------------
// �B��l�h��
void CIntList::Copy(CIntList * ilTarget)
{
	for (int i=0; i<FileCount; i++)
	{
		Ints[i] = ilTarget->Ints[i];
	}
	Total = ilTarget->Total;
}
//---------------------------------------------------------------------------
// �B��l�h��
void CIntList::operator&=(CIntList * ilTarget)
{
	AndIt(ilTarget);
}
//---------------------------------------------------------------------------
// �B��l�h��
void CIntList::AndIt(CIntList * ilTarget)
{
	Total = 0;
	for (int i=0; i<FileCount; i++)
	{
		if((Ints[i] > 0) && (ilTarget->Ints[i] > 0))	// �o�ˤ~�� and �B��
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
// �B��l�h��
void CIntList::operator|=(CIntList * ilTarget)
{
	OrIt(ilTarget);
}
//---------------------------------------------------------------------------
// �B��l�h��
void CIntList::OrIt(CIntList * ilTarget)
{
	for (int i=0; i<FileCount; i++)
	{
		Ints[i] += ilTarget->Ints[i];
	}
	Total += ilTarget->Total;
}
//---------------------------------------------------------------------------
