//---------------------------------------------------------------------------
#ifndef SearchWordH
#define SearchWordH
//---------------------------------------------------------------------------
#include "WordData.h"
#include "WordIndex.h"
#include "MainIndex.h"
#include "FileList.h"
#include "Int2List.h"
//---------------------------------------------------------------------------
class CSearchWord
{
private:	// User declarations

	void ParseToken(void);	  // ���N�n�j�M���r���@�Ӥ@�Ӫ� token
	void CreatTokenSpace(void);	// �t�m�C�@�� token ���Ŷ�

public:		// User declarations
	int *lastK1 ;
	//int *lastK2 ;
	string Word;					// �n���R���r
	vector <string>	Tokens;				// ��Ѷ}�Ӫ� token, �Ҧp�ǤJ "�����[��*��]", �h��|�� "��", "��", "��", "[��*��]"
	CWordData * WordData;				// �C�@�� token �����
	CInt2List * FoundPos;				// �x�s��쪺��m

	void Search(int iFileNum);		// �i����R

	CSearchWord(string sWord);		// �غc�禡
	~CSearchWord();					// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern CSearchWord *SearchWord;
//---------------------------------------------------------------------------
#endif
