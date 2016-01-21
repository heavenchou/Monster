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

        string FileName;				// �ɦW
        int WordCount;						// �ɮ׼ƥ�
        vector <string> StringList;     // �ɦW�}�C������   //TStringList * StringList;
        int * WordOffset;					// �C�@�Ӧr���첾���

        int GetOffset(string sToken);	// �ǤJ�@�� token , �Ǧ^��b last index �� offset
        bool Initial(void);		// Ū�J���

        CWordIndex(string sFileName);		// �غc�禡
        ~CWordIndex();							// �Ѻc�禡
};
//---------------------------------------------------------------------------
extern CWordIndex * WordIndex;
//---------------------------------------------------------------------------
#endif
