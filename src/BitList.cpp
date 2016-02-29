
#include "BitList.h"
//---------------------------------------------------------------------------
// �غc�禡
CBitList::CBitList()
{
	HasMemory = false;
	Head = 0;
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CBitList::~CBitList(void)
{
	if(HasMemory && Head) delete[] Head;
}
//---------------------------------------------------------------------------
// �]�w���
void CBitList::Initial(int iFileCount)
{
	FileCount = iFileCount;

	FileCountBit = FileCount / 32;
	if(FileCount % 32) FileCountBit++;
}
//---------------------------------------------------------------------------
// �]�w���
void CBitList::Initial(int iFileCount, int iFileCountBit)
{
	FileCount = iFileCount;
	FileCountBit = iFileCountBit;
}
//---------------------------------------------------------------------------
// �N�Y�@�� bit �]�w�� 1
void CBitList::SetBit(int iIndex)
{
	GetByteBit(iIndex);
	Mask = 1;
	Mask <<= iBit;
	Head[iByte] |= (int) Mask;
}
//---------------------------------------------------------------------------
// �N�Y�@�� bit �]�w�� 0
void CBitList::ClearBit(int iIndex)
{
	GetByteBit(iIndex);
	Mask = 1;
	Mask <<= iBit;
	Mask = ~Mask;
	Head[iByte] &= (int) Mask;
}
//---------------------------------------------------------------------------
// ���o�Y�@�� bit �����
int CBitList::GetBit(int iIndex)
{
	GetByteBit(iIndex);
	Mask = 1;
	Mask <<= iBit;

	if (Head[iByte] & (int) Mask)
		return 1;
	else
		return 0;
}
//---------------------------------------------------------------------------
// �p��X byte �� bit
void CBitList::GetByteBit(int iNum)
{
	iByte = iNum / 32;
	iBit = iNum % 32;
}
//---------------------------------------------------------------------------
