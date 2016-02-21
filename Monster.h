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

        void OpenBuildList(void);       // �}�� build file list ��
        void OpenWordIndex(void);		// �}�� word index ��
        void OpenMainIndex(void);		// �}�� last index ��

    public:		// User declarations

        string MainIndexFileName;		    // �D�n�� index ���ɦW
        string WordIndexFileName;		    // word index �ɦW
        string FileListFileName;		    // file list �ɦW
        string OpPatten;       			    // �B��Ϊ� Patten
        vector <string> SearchWordList;		// �s��C�@���˯�����, �����|�Ψ�
        CIntList * FileFound;				// �s��C�@�ɧ�쪺�ƶq
        CPostfixStack * PostfixStack;		// �B��Ϊ�
        string OKSentence;				    // �w�g���R�L��, �Ҧp ��� & ���� �ܦ� S&S
        int MaxSearchWordNum;				// �˯������̦h�i�X�{���r���,   "��� & ��ù�~" �N�� 2 ��
        CSearchWord ** swWord;			// �C�@���˯��r�ꪺ����, �̦h 20 ��, �Ҧp "��� & ��ù�~" �N�� 2 ��

        // ���U�T�ӳ��令��~���}��
        //TmyFileList * BuildFileList;		// build file list;
        //TmyWordIndex * WordIndex;		// build file list;
        //TmyMainIndex * MainIndex;		// Last index file

        // �۶ǤJ���ѼƤ����X Patten , ��r��]�|�Q��h��
        string CutPatten(string & sString);

        // �M��@�Ӧr��, ���ӭn�Ǧ^�@���ɮצ�, ��ܭ����ɮצ�
        //void __fastcall Find_old(AnsiString sSearchWord);
        bool Find(string sSearchWord,bool bHasSearchRange);  // �Y�B�⥢��, �Ǧ^ false
        void AnalysisSentence(string sSentence); // ���R��J�r��, ���� OKSentence
        int FindOneFile(int iFileNum);				// �Ǧ^��쪺�ռ�

        CMonster(string sFileListFileName, string sWordIndexFileName, string sMainIndexFileName);	// �غc�禡
        ~CMonster();		// �Ѻc�禡
};

#endif

