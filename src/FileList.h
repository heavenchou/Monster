//---------------------------------------------------------------------------
#ifndef FileListH
#define FileListH
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdlib.h>
///#include "RegExpr.hpp"

using namespace std;
//---------------------------------------------------------------------------
string GetAlphaFromHead(string sInput);

class CFileList
{
    private:	// User declarations

    public:		// User declarations

        string FileName;				// 檔名
        int FileCount;						// 檔案數目
        int FileCountBit;					// 檔案數目 / 32 之後的整數

        string * Strings;				// 檔名陣列的指標
        string * Book;					// 找出藏經 'T'(大正), 'X'(卍續)
        int * VolNum;						// 算出冊數
        string * SutraNum;              // 算出經號
        int * JuanNum;                      // 算出卷號
        bool * SearchMe;					// 判斷要不要檢索

        bool Initial(void);		// 讀入資料

        string GetAlphaFromHead(string sInput);     // 取得字串前面非數字的部份
        void NoneSearch(void);	// 取消全部的檢索
        void SearchThisSutra(string sBook, string sSutraNum, int iStartJuan = 0, int iEndJuan = 0);   // 檢索這一經的這些卷
        void SearchThisVol(string sBook, int iVolNum, int iStartSutra = 0, int iEndSutra = 0);   // 檢索這一冊的這些經

        CFileList(string sFileName);		// 建構函式
        ~CFileList();							// 解構函式
};
//---------------------------------------------------------------------------
extern CFileList * BuildFileList;
//---------------------------------------------------------------------------
#endif
