#include "WordData.h"
#include "FileList.h"
#include "MainIndex.h"
//---------------------------------------------------------------------------
CWordData::CWordData(void)	// �غc�禡
{
	FileCount = BuildFileList->FileCount;
	FileListBit = new CBitList;
	WordCount = 0;
	WordPos = 0;
	Buffer = 0;
	Buffer1 = 0;
}
//---------------------------------------------------------------------------
CWordData::~CWordData(void)	// �Ѻc�禡
{
	if(WordCount) delete[] WordCount;
	if(FileListBit) delete FileListBit;
	if(WordPos) delete[] WordPos;
	if(Buffer) delete[] Buffer;
	//if(Buffer1) delete[] Buffer1;
}
//---------------------------------------------------------------------------
// ��Ȥ�
void CWordData::Initial(int iOffset, int iBufferSize)
{
	int iTotalDataCount = 0;			// ���ɦ��X�ӳo�Ӧr

	WordCount = new int [FileCount];	// �x�s�C�@���ɮשҥ]�t���r���ƶq
	WordPos = new int* [FileCount]; 	// ��ڸ�ƪ��}�C

    //���U�|���� (�b BCB �i�H)
	// (char *) Buffer = new char[iBufferSize];
	// �ҥH�令�p�U:
	char * cBuffer = new char[iBufferSize];
	Buffer = (int *)cBuffer;
	// �o�˦n���]�i�H
	// Buffer =  (int *) new char[iBufferSize];

	MainIndex->FileStream.seekg(iOffset);
	MainIndex->FileStream.read((char *)Buffer, iBufferSize);

/*
�C�@�Ӧr�b taisho.ndx ������Ƶ��c

���]�u���v�o�Ӧr�b�����ɮפ�, �u��125�ɥX�{.

FileCount = 5; (�����ɮ�)
Word = �� (�Y�@�Ӧr)

3,3,0,0,5 (9300) (�o�Ӥ�k�Ӧ��Ŷ��F, 10000 �Ӧr, 10000 ����, �j���� 200 M)
or
1,1,0,0,1 (1162) (�C�@�� bit �N��@���ɮ�, 0 ��ܦ��ɮרS���o�Ӧr, 1 ��ܳo���ɮצ����r)
3,3,5

WordCount[0] = 3     �o�O�B�~���ͪ��Ŷ�
WordCount[1] = 3
WordCount[2] = 0
WordCount[3] = 0
WordCount[4] = 5

10,20,30             (�Ĥ@���ɥX�{ 3 ��)
100,200,300          (�ĤG���ɥX�{ 3 ��)
111,222,333,444,555  (�Ĥ����ɥX�{ 5 ��)

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
			WordCount[i] = *ipTmp;				// ���ɦ����r, �hŪ�����
			iTotalDataCount += WordCount[i];    // ���ɦ��X�ӳo�Ӧr
			ipTmp++;
		}
		else
		{
			WordCount[i] = 0;
		}
	}

	/* --------------- �ª��}�l ---------------

	WordPos[0] = ipTmp;

	for(int i=1; i<FileCount; i++)
		WordPos[i] = WordPos[i-1] + WordCount[i-1];

	//--------------- �ª����� --------------- */

	///* ----------- �s�� ----------------

	Buffer1 = new int[iTotalDataCount];
	unsigned char * cpNewTmp = (unsigned char *) Buffer1;	// ���o�ӫ��е���s���Ŷ����}�Y
	unsigned char * cpOldTmp = (unsigned char *) ipTmp;		// ���o�ӫ��е����ª��Ŷ����}�Y

	unsigned char ucTmp1, ucTmp2, ucTmp3, ucTmp4;

	WordPos[0] = Buffer1;

	for(int i=0; i<FileCount; i++)		// �ɮ׼ƥ�
	{
		if(i>0)	WordPos[i] = WordPos[i-1] + WordCount[i-1];		// �]�w WordPos ����m

		for(int j=0; j<WordCount[i]; j++)			// �ǳƸ����Y�C�@���ɦ��r���C��
		{
			ucTmp1 = *cpOldTmp;		// ���X�@�� byte

			if(ucTmp1 == 0)			// �o�O�|���, �]���Ĥ@�� byte �O 0
			{
				ucTmp1 = cpOldTmp[1];
				ucTmp2 = cpOldTmp[2];
				ucTmp3 = cpOldTmp[3];
				ucTmp4 = cpOldTmp[4];

				WordPos[i][j] = (unsigned int) ucTmp1 * 16777216;					// 0x 01 00 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2 * 65536; 		// 0x 01 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp3 * 256; 		// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp4; 				// 0x 01

				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// �]�����Y����ƬO�C�@�Ӹ�ƪ��t��.

				cpOldTmp += 5;		// ����U�@��
			}
			else if(ucTmp1 >= 192)		// �T��� 0x 11000000
			{
				ucTmp1 -= 192;
				ucTmp2 = cpOldTmp[1];
				ucTmp3 = cpOldTmp[2];

				WordPos[i][j] = (unsigned int) ucTmp1 * 65536;						// 0x 01 00 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2 * 256; 		// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp3; 				// 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// �]�����Y����ƬO�C�@�Ӹ�ƪ��t��.

				cpOldTmp += 3;		// ����U�@��
			}
			else if(ucTmp1 >= 128)		// �G��� 0x 10000000
			{
				ucTmp1 -= 128;
				ucTmp2 = cpOldTmp[1];

				WordPos[i][j] = (unsigned int) ucTmp1 * 256;				// 0x 01 00
				WordPos[i][j] = WordPos[i][j] + (unsigned int) ucTmp2;		// 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// �]�����Y����ƬO�C�@�Ӹ�ƪ��t��.

				cpOldTmp += 2;		// ����U�@��
			}
			else 					// �@��� \x 01000000
			{
				ucTmp1 -= 64;
				WordPos[i][j] = (unsigned int) ucTmp1;	   // 0x 01
				if(j!=0) WordPos[i][j] += WordPos[i][j-1];			// �]�����Y����ƬO�C�@�Ӹ�ƪ��t��.
				cpOldTmp += 1;		// ����U�@��
			}
		}
	}

	if(Buffer) delete[] Buffer;
	Buffer = Buffer1;		// �]���̫�n delete ���O Buffer

	//------------- �s������ --------------- */
}
//---------------------------------------------------------------------------
// ��Ȥ�, ������ 0
void CWordData::ZeroIt(void)
{
	WordCount = new int [FileCount];	// �x�s�C�@���ɮשҥ]�t���r���ƶq
	WordPos = new int* [FileCount]; 	// ��ڸ�ƪ��}�C

	int iSize = BuildFileList->FileCountBit + 5;	// �h 5 ��, ���F�a!

	//���U�|���� (�b BCB �i�H)
	//(char *)Buffer = new char[iSize*4];		// �@�� int ���Ŷ� 4 byte
	// �ҥH�令�p�U:
	char * cBuffer = new char[iSize*4];		// �@�� int ���Ŷ� 4 byte
	Buffer = (int *)cBuffer;

	for(int i=0; i<iSize; i++)
	{
		Buffer[i] = 0;              		// buffer ���M�� 0
	}

/*
�C�@�Ӧr�b taisho.ndx ������Ƶ��c

���]�u���v�o�Ӧr�b�����ɮפ�, �u��125�ɥX�{.

FileCount = 5; (�����ɮ�)
Word = �� (�Y�@�Ӧr)

3,3,0,0,5 (9300) (�o�Ӥ�k�Ӧ��Ŷ��F, 10000 �Ӧr, 10000 ����, �j���� 200 M)
or
1,1,0,0,1 (1162) (�C�@�� bit �N��@���ɮ�, 0 ��ܦ��ɮרS���o�Ӧr, 1 ��ܳo���ɮצ����r)
3,3,5

WordCount[0] = 3     �o�O�B�~���ͪ��Ŷ�
WordCount[1] = 3
WordCount[2] = 0
WordCount[3] = 0
WordCount[4] = 5

10,20,30             (�Ĥ@���ɥX�{ 3 ��)
100,200,300          (�ĤG���ɥX�{ 3 ��)
111,222,333,444,555  (�Ĥ����ɥX�{ 5 ��)

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
		WordCount[i] = 0;           // �C�@�ɥX�{�r��, �M�� 0
		WordPos[i] = ipTmp;			// �ҥH�C�@�r����m�]�O 0
	}
}
//---------------------------------------------------------------------------
