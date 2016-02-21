//---------------------------------------------------------------------------
#ifndef MonsterH
#define MonsterH
//---------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "FileList.h"
#include "WordIndex.h"
#include "MainIndex.h"
#include "IntList.h"
#include "PostfixStack.h"
#include "SearchWord.h"

//---------------------------------------------------------------------------
class CMonster
{
    private:	// User declarations

        void OpenBuildList(void);       // 開啟 build file list 檔
        void OpenWordIndex(void);		// 開啟 word index 檔
        void OpenMainIndex(void);		// 開啟 last index 檔

    public:		// User declarations

        string MainIndexFileName;		    // 主要的 index 的檔名
        string WordIndexFileName;		    // word index 檔名
        string FileListFileName;		    // file list 檔名
        string OpPatten;       			    // 運算用的 Patten
        vector <string> SearchWordList;		// 存放每一個檢索的詞, 日後塗色會用到
        CIntList * FileFound;				// 存放每一檔找到的數量
        CPostfixStack * PostfixStack;		// 運算用的
        string OKSentence;				    // 已經分析過的, 例如 佛陀 & 阿難 變成 S&S
        int MaxSearchWordNum;				// 檢索詞中最多可出現的字串數,   "佛陀 & 阿羅漢" 就算 2 個
        CSearchWord ** swWord;			// 每一個檢索字串的指標, 最多 20 個, 例如 "佛陀 & 阿羅漢" 就算 2 個

        // 底下三個都改成對外公開的
        //TmyFileList * BuildFileList;		// build file list;
        //TmyWordIndex * WordIndex;		// build file list;
        //TmyMainIndex * MainIndex;		// Last index file

        // 自傳入的參數中取出 Patten , 原字串也會被砍去喔
        string CutPatten(string & sString);

        // 尋找一個字串, 應該要傳回一個檔案串, 表示哪些檔案有
        //void __fastcall Find_old(AnsiString sSearchWord);
        bool Find(string sSearchWord,bool bHasSearchRange);  // 若運算失敗, 傳回 false
        void AnalysisSentence(string sSentence); // 分析輸入字串, 產生 OKSentence
        int FindOneFile(int iFileNum);				// 傳回找到的組數

        CMonster(string sFileListFileName, string sWordIndexFileName, string sMainIndexFileName);	// 建構函式
        ~CMonster();		// 解構函式
};

#endif

