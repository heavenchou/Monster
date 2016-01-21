//---------------------------------------------------------------------------
#ifndef WordIndexH
#define WordIndexH
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------

class CWordIndex
{
    private:	// User declarations
    public:		// User declarations

        string FileName;				// 檔名
        int WordCount;						// 檔案數目
        vector <string> StringList;     // 檔名陣列的指標   //TStringList * StringList;
        int * WordOffset;					// 每一個字的位移資料

        int GetOffset(string sToken);	// 傳入一個 token , 傳回其在 last index 的 offset
        bool Initial(void);		// 讀入資料

        CWordIndex(string sFileName);		// 建構函式
        ~CWordIndex();							// 解構函式
};
//---------------------------------------------------------------------------
extern CWordIndex * WordIndex;
//---------------------------------------------------------------------------
#endif
