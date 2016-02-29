//---------------------------------------------------------------------------
#ifndef BitListH
#define BitListH
//---------------------------------------------------------------------------
// ??? �i�H�Ҽ{�� bitset ����
class CBitList
{
    private:	// User declarations

        int iByte;		// �p��Ϊ�, �Y�@�� byte
        int iBit;		// �p��Ϊ�, �Y�@�� bit
        unsigned int Mask;		// �ΨӾB�n�Y�@�� bit ���u��

        void GetByteBit(int iNum);		// �p��X byte �� bit

    public:		// User declarations

        int FileCount;					// �ɮ׼ƥ�
        int FileCountBit;				// �ɮ׼ƥ� / 32 ���᪺���
        int * Head;						// �}�Y������
        bool HasMemory;					// �O�_���ۤv new �@�ӪŶ�?

        void Initial(int iFileCount);		// �]�w���
        void Initial(int iFileCount, int iFileCountBit);		// �]�w���

        void SetBit(int iIndex);		// �N�Y�@�� bit �]�w�� 1
        void ClearBit(int iIndex);	// �N�Y�@�� bit �]�w�� 0
        int GetBit(int iIndex);		// ���o�Y�@�� bit �����

        CBitList();		// �غc�禡
        ~CBitList();		// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern TmyBitList *BitList;
//---------------------------------------------------------------------------
#endif
