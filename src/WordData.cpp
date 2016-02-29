#include "WordData.h"
#include "FileList.h"
#include "MainIndex.h"
//---------------------------------------------------------------------------
CWordData::CWordData(void)	// 建構函式
{
	FileCount = BuildFileList->FileCount;
	FileListBit = new CBitList;
	WordCount = 0;
	WordPos = 0;
	Buffer = 0;
	Buffer1 = 0;
}
//---------------------------------------------------------------------------
CWordData::~CWordData(void)	// 解構函式
{
	if(WordCount) delete[] WordCount;
	if(FileListBit) delete FileListBit;
	if(WordPos) delete[] WordPos;
	if(Buffer) delete[] Buffer;
	//if(Buffer1) delete[] Buffer1;
}
//---------------------------------------------------------------------------
// 初值化
void CWordData::Initial(int iOffset, int iBufferSize)
{
	int iTotalDataCount = 0;			// 此檔有幾個這個字

	WordCount = new int [FileCount];	// 儲存每一個檔案所包含此字的數量
	WordPos = new int* [FileCount]; 	// 實際資料的陣列

    //底下會有錯 (在 BCB 可以)
	// (char *) Buffer = new char[iBufferSize];
	// 所以改成如下:
	char * cBuffer = new char[iBufferSize];
	Buffer = (int *)cBuffer;
	// 這樣好像也可以
	// Buffer =  (int *) new char[iBufferSize];

	MainIndex->FileStream.seekg(iOffset);
	MainIndex->FileStream.read((char *)Buffer, iBufferSize);

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

iTotalDataCount = 5+3+3 = 11

WordPos[0][0],WordPos[0][1],WordPos[0][2]......
WordPos[1][0],WordPos[1][1],WordPos[1][2]......
WordPos[2][0]
WordPos[3][0]
WordPos[4][0],WordPos[4][1],WordPos[4][2],WordPos[4][3],WordPos[4][4]......

*/
	FileListBit->Initial(FileCount, BuildFileList->FileCountBit);
	FileListBit->Head = Buffer;

	int * ipTmp = Buffer + BuildFileList->FileCountBit;
	for(int i=0; i<FileCount; i++)
	{
		if(FileListBit->GetBit(i))
		{
			WordCount[i] = *ipTmp;				// 該檔有此字, 則讀取資料
			iTotalDataCount += WordCount[i];    // 此檔有幾個這個字
			ipTmp++;
		}
		else
		{
			WordCount[i] = 0;
		}
	}

	/* --------------- 舊版開始 ---------------

	WordPos[0] = ipTmp;

	for(int i=1; i<FileCount; i++)
		WordPos[i] = WordPos[i-1] + WordCount[i-1];

	//--------------- 舊版結束 --------------- */

	///* ----------- 新版 ----------------

	Buffer1 = new int[iTotalDataCount];
	unsigned char * cpNewTmp = (unsigned char *) Buffer1;	// 讓這個指標等於新的空間的開頭
	unsigned char * cpOldTmp = (unsigned char *) ipTmp;		// 讓這個指標等於舊的空間的開頭

	unsigned char ucTmp1, ucTmp2, ucTmp3, ucTmp4;

	WordPos[0] = Buffer1;

	for(int i=0; i<FileCount; i++)		// 檔案數目
	{
		if(i>0)	WordPos[i] = WordPos[i-1] + WordCount[i-1];		// 設定 WordPos 的位置

		for(int j=0; j<WordCount[i]; j++)			// 準備解壓縮每一個檔此字的列表
		{
			ucTmp1 = *cpOldTmp;		// 取出一個 byte

			if(ucTmp1 == 0)			// 這是四位數, 因為第一個 byte 是 0
			{
				ucTmp1 = cpOldTmp[1];
				ucTmp2 = cpOldTmp[2];
				ucTmp3 = cpOldTmp[3];
				ucTmp4 = cpOldTmp[4];

				WordPos[i][j] = (unsigned int) ucTmp1 * 16777216;					// 0x 01 00 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2 * 65536; 		// 0x 01 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp3 * 256; 		// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp4; 				// 0x 01

				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// 因為壓縮的資料是每一個資料的差數.

				cpOldTmp += 5;		// 移到下一個
			}
			else if(ucTmp1 >= 192)		// 三位數 0x 11000000
			{
				ucTmp1 -= 192;
				ucTmp2 = cpOldTmp[1];
				ucTmp3 = cpOldTmp[2];

				WordPos[i][j] = (unsigned int) ucTmp1 * 65536;						// 0x 01 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2 * 256; 		// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp3; 				// 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// 因為壓縮的資料是每一個資料的差數.

				cpOldTmp += 3;		// 移到下一個
			}
			else if(ucTmp1 >= 128)		// 二位數 0x 10000000
			{
				ucTmp1 -= 128;
				ucTmp2 = cpOldTmp[1];

				WordPos[i][j] = (unsigned int) ucTmp1 * 256;				// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2;		// 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// 因為壓縮的資料是每一個資料的差數.

				cpOldTmp += 2;		// 移到下一個
			}
			else 					// 一位數 \x 01000000
			{
				ucTmp1 -= 64;
				WordPos[i][j] = (unsigned int) ucTmp1;	   // 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// 因為壓縮的資料是每一個資料的差數.
				cpOldTmp += 1;		// 移到下一個
			}
		}
	}

	if(Buffer) delete[] Buffer;
	Buffer = Buffer1;		// 因為最後要 delete 的是 Buffer

	//------------- 新版結束 --------------- */
}
//---------------------------------------------------------------------------
// 初值化, 全部填 0
void CWordData::ZeroIt(void)
{
	WordCount = new int [FileCount];	// 儲存每一個檔案所包含此字的數量
	WordPos = new int* [FileCount]; 	// 實際資料的陣列

	int iSize = BuildFileList->FileCountBit + 5;	// 多 5 個, 夠了吧!

	//底下會有錯 (在 BCB 可以)
	//(char *)Buffer = new char[iSize*4];		// 一個 int 的空間 4 byte
	// 所以改成如下:
	char * cBuffer = new char[iSize*4];		// 一個 int 的空間 4 byte
	Buffer = (int *)cBuffer;

	for(int i=0; i<iSize; i++)
	{
		Buffer[i] = 0;              		// buffer 全清為 0
	}

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
	FileListBit->Initial(FileCount, BuildFileList->FileCountBit);
	FileListBit->Head = Buffer;

	int * ipTmp = Buffer + BuildFileList->FileCountBit;
	ipTmp++;
	for(int i=0; i<FileCount; i++)
	{
		WordCount[i] = 0;           // 每一檔出現字數, 清為 0
		WordPos[i] = ipTmp;			// 所以每一字的位置也是 0
	}
}
//---------------------------------------------------------------------------
