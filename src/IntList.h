//---------------------------------------------------------------------------
#ifndef IntListH
#define IntListH
//---------------------------------------------------------------------------
//#include <>
//---------------------------------------------------------------------------
class CIntList
{
private:	// User declarations
public:		// User declarations

	int FileCount;					// �ɮ׼ƥ�
	int * Ints;						// �}�Y������
	int Total;

	void ClearAll(void);			// �����M��

	void operator=(CIntList * ilTarget);		// �B��l�h��
	void operator&=(CIntList * ilTarget);		// �B��l�h��
	void operator|=(CIntList * ilTarget);		// �B��l�h��
	void Copy(CIntList * ilTarget);		// �B��l�h��
	void AndIt(CIntList * ilTarget);		// �B��l�h��
	void OrIt(CIntList * ilTarget);		// �B��l�h��
    CIntList(int iFileCount);		// �غc�禡
	~CIntList();					// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern TmyIntList *IntList;
//---------------------------------------------------------------------------
#endif
