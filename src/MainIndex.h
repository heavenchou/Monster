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

        ifstream FileStream;			// �D������
        string FileName;
        long Size;

        CMainIndex(string sFileName);	// �غc�禡
        ~CMainIndex();						// �Ѻc�禡
};
//---------------------------------------------------------------------------
extern CMainIndex *MainIndex;
//---------------------------------------------------------------------------
#endif
