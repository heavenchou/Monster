//---------------------------------------------------------------------------
#ifndef WordDataH
#define WordDataH
//---------------------------------------------------------------------------
#include "BitList.h"
//---------------------------------------------------------------------------
/*
每一個字在 taisho.ndx 中的資料結構

假設「中」這個字在五個檔案中, 只有125檔出現.

FileCount = 5; (五個檔案)
Word = 中 (某一個字)

3,3,0,0,5 (9300) (這個方法太佔空間了, 10000 個字, 10000 個檔, 大概佔 200 M)
or
1,1,0,0,1 (1162) (每一個 bit 代表一個檔案, 0 表示此檔案沒有這個字, 1 表示這個檔案有此字)
3,3,5

WordCount[0] = 3     這是額外產生的空間
WordCount[1] = 3
WordCount[2] = 0
WordCount[3] = 0
WordCount[4] = 5

10,20,30             (第一個檔出現 3 次)
100,200,300          (第二個檔出現 3 次)
111,222,333,444,555  (第五個檔出現 5 次)

WordPos[0][0],WordPos[0][1],WordPos[0][2]......
WordPos[1][0],WordPos[1][1],WordPos[1][2]......
WordPos[2][0]
WordPos[3][0]
WordPos[4][0],WordPos[4][1],WordPos[4][2],WordPos[4][3],WordPos[4][4]......

*/

class CWordData
{
private:	// User declarations

	int * Buffer;		// 每一個字所佔的大量空間, 用來包含底下的東西 (舊版還沒解壓縮的)
	int * Buffer1;      // 每一個字所佔的大量空間, 用來包含底下的東西 (新版已解壓縮的)

public:		// User declarations

	int	FileCount;		// 檔案個數

	CBitList * FileListBit;		// 指向一串數字, 每一個 bit 代表一個檔案的情況
	int * WordCount;	/* 每一個檔案所含有此字的數量, 這個不能使用 buffer 的空間,
						   因為 buffer 裡面只有該檔有資料才會有
						   所以這個空間要另外產生 */
	int ** WordPos;		// 這個空間要另外產生

	void Initial(int iOffset, int iBufferSize);	// 初值化
	void ZeroIt(void);	// 初值化, 全部填 0

	CWordData();		// 建構函式
	~CWordData();		// 解構函式
};
//---------------------------------------------------------------------------
//extern TmyWordData *WordData;
//---------------------------------------------------------------------------
#endif
