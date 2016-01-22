//---------------------------------------------------------------------------

#include "Monster.h"
//---------------------------------------------------------------------------
// 建構函式
CMonster::CMonster(string sFileListFileName,
					string sWordIndexFileName,
					string sMainIndexFileName)
{
	// 初值歸零
	BuildFileList = 0;
	///WordIndex = 0;
	OpPatten = "()&,+*-";		// 算運用的 Patten

	FileListFileName = sFileListFileName;
	WordIndexFileName = sWordIndexFileName;
	MainIndexFileName = sMainIndexFileName;

	///SearchWordList = new TStringList;	// 存放每一個檢索的詞, 日後塗色會用到
	MaxSearchWordNum = 20;				// 檢索詞中最多可出現的字串數,   "佛陀 & 阿羅漢" 就算 2 個
	///swWord = new TmySearchWord*[MaxSearchWordNum];

	for(int i=0; i<MaxSearchWordNum; i++)
	{
	///	swWord[i] = 0;		// 設定初值, 指標歸 0
	}

	// 先處理 build file list
	OpenBuildList();
	OpenWordIndex();
	OpenMainIndex();

	///PostfixStack = new TmyPostfixStack;
	///FileFound = new TmyIntList(BuildFileList->FileCount);	// 存放每一檔找到的結果
}
//---------------------------------------------------------------------------
// 解構函式
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
