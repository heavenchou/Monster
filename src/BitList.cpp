
#include "BitList.h"
//---------------------------------------------------------------------------
// 建構函式
CBitList::CBitList()
{
	HasMemory = false;
	Head = 0;
}
//---------------------------------------------------------------------------
// 解構函式
CBitList::~CBitList(void)
{
	if(HasMemory && Head) delete[] Head;
}
//---------------------------------------------------------------------------
// 設定初值
void CBitList::Initial(int iFileCount)
{
	FileCount = iFileCount;

	FileCountBit = FileCount / 32;
	if(FileCount % 32) FileCountBit++;
}
//---------------------------------------------------------------------------
// 設定初值
void CBitList::Initial(int iFileCount, int iFileCountBit)
{
	FileCount = iFileCount;
	FileCountBit = iFileCountBit;
}
//---------------------------------------------------------------------------
// 將某一個 bit 設定為 1
void CBitList::SetBit(int iIndex)
{
	GetByteBit(iIndex);
	Mask = 1;
	Mask <<= iBit;
	Head[iByte] |= (int) Mask;
}
//---------------------------------------------------------------------------
// 將某一個 bit 設定為 0
void CBitList::ClearBit(int iIndex)
{
	GetByteBit(iIndex);
	Mask = 1;
	Mask <<= iBit;
	Mask = ~Mask;
	Head[iByte] &= (int) Mask;
}
//---------------------------------------------------------------------------
// 取得某一個 bit 的資料
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
// 計算出 byte 及 bit
void CBitList::GetByteBit(int iNum)
{
	iByte = iNum / 32;
	iBit = iNum % 32;
}
//---------------------------------------------------------------------------
