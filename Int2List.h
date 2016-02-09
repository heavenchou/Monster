//---------------------------------------------------------------------------
#ifndef Int2ListH
#define Int2ListH
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CInt2List
{

    // �o�Ӫ���O�G�� Int ���C��ҲզX�X�Ӫ�, �C�@�ժ�ܬY�@�r���d��

    private:	// User declarations
    public:		// User declarations

        //int FileCount;					// �ɮ׼ƥ�
        //int * Ints;						// �}�Y������
        //TList * Int2s;
        vector <pair <int,int> > Int2s;     // �̭��� pair ����, �C�@�� pari ��ܬY�@�����d��
        //int Total;
        int NearNum;				// Near �B�⪺�d��
        int BeforeNum;				// Before �B�⪺�d��
        string SearchString;        // �j�M���r��, �@�}�l�i��O "���" �o�ص�, �b�B���i���ܦ� "(���+ù�~)" �o�عB�⵲�G. �o���O�� ! �B��]�p��


        void ClearAll(void);			// �����M��
        void operator=(CInt2List * ilTarget);		// �B��l�h��
        void operator&=(CInt2List * ilTarget);		// �B��l�h��
        void operator|=(CInt2List * ilTarget);		// �B��l�h��
        void Copy(CInt2List * ilTarget);		// �N��� copy �L��
        void AndIt(CInt2List * ilTarget);		// �Y�G�̳������, �N�G�̦X��
        void OrIt(CInt2List * ilTarget);		// �G�̦X��
        void NearIt(CInt2List * ilTarget);		// �Y�G�̾a��ܬY�@�ӵ{��, �h�ܦ��@�ӽd��
        void BeforeIt(CInt2List * ilTarget);		// �P Near , ���L�u��b��᭱, �]�N�O�����Ǫ�

        void ExcludeIt(CInt2List * ilTarget);		// �ư��Y�@�ӵ�, �Ҧp  �٧Q!�٧Q�� ��ܥu�n��٧Q, �����n���٧Q��

        void Add(pair <int, int> p);	// �[�J�@�����
        void Add(int x, int y);		// �[�J�@�����
        void Delete(int iNum);		// �R���Y�@�����

        int MyAnsiPos(string sStr1, string sStr2);

        CInt2List();					// �غc�禡
        ~CInt2List();					// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern CInt2List *Int2List;
//---------------------------------------------------------------------------
#endif
