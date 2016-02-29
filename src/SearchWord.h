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

	void ParseToken(void);	  // 先將要搜尋的字串拆成一個一個的 token
	void CreatTokenSpace(void);	// 配置每一個 token 的空間

public:		// User declarations
	int *lastK1 ;
	//int *lastK2 ;
	string Word;					// 要分析的字
	vector <string>	Tokens;				// 拆解開來的 token, 例如傳入 "佛陀持[金*本]", 則拆成四組 "佛", "陀", "持", "[金*本]"
	CWordData * WordData;				// 每一個 token 的資料
	CInt2List * FoundPos;				// 儲存找到的位置

	void Search(int iFileNum);		// 進行分析

	CSearchWord(string sWord);		// 建構函式
	~CSearchWord();					// 解構函式
};
//---------------------------------------------------------------------------
//extern CSearchWord *SearchWord;
//---------------------------------------------------------------------------
#endif
