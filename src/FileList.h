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

        string FileName;				// �ɦW
        int FileCount;						// �ɮ׼ƥ�
        int FileCountBit;					// �ɮ׼ƥ� / 32 ���᪺���

        string * Strings;				// �ɦW�}�C������
        string * Book;					// ��X�øg 'T'(�j��), 'X'(����)
        int * VolNum;						// ��X�U��
        string * SutraNum;              // ��X�g��
        int * JuanNum;                      // ��X����
        bool * SearchMe;					// �P�_�n���n�˯�

        bool Initial(void);		// Ū�J���

        string GetAlphaFromHead(string sInput);     // ���o�r��e���D�Ʀr������
        void NoneSearch(void);	// �����������˯�
        void SearchThisSutra(string sBook, string sSutraNum, int iStartJuan = 0, int iEndJuan = 0);   // �˯��o�@�g���o�Ǩ�
        void SearchThisVol(string sBook, int iVolNum, int iStartSutra = 0, int iEndSutra = 0);   // �˯��o�@�U���o�Ǹg

        CFileList(string sFileName);		// �غc�禡
        ~CFileList();							// �Ѻc�禡
};
//---------------------------------------------------------------------------
extern CFileList * BuildFileList;
//---------------------------------------------------------------------------
#endif
