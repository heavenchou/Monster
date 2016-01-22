//---------------------------------------------------------------------------
#ifndef MainIndexH
#define MainIndexH
//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
class CMainIndex
{
    private:	// User declarations
    public:		// User declarations

        ifstream FileStream;			// 主索引檔
        string FileName;
        long Size;

        CMainIndex(string sFileName);	// 建構函式
        ~CMainIndex();						// 解構函式
};
//---------------------------------------------------------------------------
extern CMainIndex *MainIndex;
//---------------------------------------------------------------------------
#endif
