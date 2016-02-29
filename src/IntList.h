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

	int FileCount;					// 檔案數目
	int * Ints;						// 開頭的指標
	int Total;

	void ClearAll(void);			// 全部清掉

	void operator=(CIntList * ilTarget);		// 運算子多載
	void operator&=(CIntList * ilTarget);		// 運算子多載
	void operator|=(CIntList * ilTarget);		// 運算子多載
	void Copy(CIntList * ilTarget);		// 運算子多載
	void AndIt(CIntList * ilTarget);		// 運算子多載
	void OrIt(CIntList * ilTarget);		// 運算子多載
    CIntList(int iFileCount);		// 建構函式
	~CIntList();					// 解構函式
};
//---------------------------------------------------------------------------
//extern TmyIntList *IntList;
//---------------------------------------------------------------------------
#endif
