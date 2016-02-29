//---------------------------------------------------------------------------
#ifndef WordDataH
#define WordDataH
//---------------------------------------------------------------------------
#include "BitList.h"
//---------------------------------------------------------------------------
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

class CWordData
{
private:	// User declarations

	int * Buffer;		// �C�@�Ӧr�Ҧ����j�q�Ŷ�, �Ψӥ]�t���U���F�� (�ª��٨S�����Y��)
	int * Buffer1;      // �C�@�Ӧr�Ҧ����j�q�Ŷ�, �Ψӥ]�t���U���F�� (�s���w�����Y��)

public:		// User declarations

	int	FileCount;		// �ɮ׭Ӽ�

	CBitList * FileListBit;		// ���V�@��Ʀr, �C�@�� bit �N��@���ɮת����p
	int * WordCount;	/* �C�@���ɮשҧt�����r���ƶq, �o�Ӥ���ϥ� buffer ���Ŷ�,
						   �]�� buffer �̭��u�����ɦ���Ƥ~�|��
						   �ҥH�o�ӪŶ��n�t�~���� */
	int ** WordPos;		// �o�ӪŶ��n�t�~����

	void Initial(int iOffset, int iBufferSize);	// ��Ȥ�
	void ZeroIt(void);	// ��Ȥ�, ������ 0

	CWordData();		// �غc�禡
	~CWordData();		// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern TmyWordData *WordData;
//---------------------------------------------------------------------------
#endif
