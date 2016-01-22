//---------------------------------------------------------------------------

#include "Monster.h"
//---------------------------------------------------------------------------
// �غc�禡
CMonster::CMonster(string sFileListFileName,
					string sWordIndexFileName,
					string sMainIndexFileName)
{
	// ����k�s
	BuildFileList = 0;
	///WordIndex = 0;
	OpPatten = "()&,+*-";		// ��B�Ϊ� Patten

	FileListFileName = sFileListFileName;
	WordIndexFileName = sWordIndexFileName;
	MainIndexFileName = sMainIndexFileName;

	///SearchWordList = new TStringList;	// �s��C�@���˯�����, �����|�Ψ�
	MaxSearchWordNum = 20;				// �˯������̦h�i�X�{���r���,   "��� & ��ù�~" �N�� 2 ��
	///swWord = new TmySearchWord*[MaxSearchWordNum];

	for(int i=0; i<MaxSearchWordNum; i++)
	{
	///	swWord[i] = 0;		// �]�w���, �����k 0
	}

	// ���B�z build file list
	OpenBuildList();
	OpenWordIndex();
	OpenMainIndex();

	///PostfixStack = new TmyPostfixStack;
	///FileFound = new TmyIntList(BuildFileList->FileCount);	// �s��C�@�ɧ�쪺���G
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CMonster::~CMonster(void)
{
    /*
	if(BuildFileList) delete BuildFileList;
	if(WordIndex) delete WordIndex;
	if(PostfixStack) delete PostfixStack;
	if(SearchWordList) delete SearchWordList;
	if(FileFound) delete FileFound;
	if(swWord) delete[] swWord;
    */
}
//---------------------------------------------------------------------------
void CMonster::OpenBuildList(void)
{
	BuildFileList = new CFileList(FileListFileName);
	if(!BuildFileList->Initial())
    {	// ???? error check
        cout << "Open BuildList error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenWordIndex(void)
{
	WordIndex = new CWordIndex(WordIndexFileName);

	if(!WordIndex->Initial())
    {	// ???? error check
        cout << "Open WordIndex error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenMainIndex(void)
{
	MainIndex = new CMainIndex(MainIndexFileName);	// ???? error check
}
//---------------------------------------------------------------------------
