//---------------------------------------------------------------------------
#ifndef BitListH
#define BitListH
//---------------------------------------------------------------------------
// ??? 可以考慮用 bitset 物件
class CBitList
{
    private:	// User declarations

        int iByte;		// 計算用的, 某一個 byte
        int iBit;		// 計算用的, 某一個 bit
        unsigned int Mask;		// 用來遮罩某一個 bit 的工具

        void GetByteBit(int iNum);		// 計算出 byte 及 bit

    public:		// User declarations

        int FileCount;					// 檔案數目
        int FileCountBit;				// 檔案數目 / 32 之後的整數
        int * Head;						// 開頭的指標
        bool HasMemory;					// 是否有自己 new 一個空間?

        void Initial(int iFileCount);		// 設定初值
        void Initial(int iFileCount, int iFileCountBit);		// 設定初值

        void SetBit(int iIndex);		// 將某一個 bit 設定為 1
        void ClearBit(int iIndex);	// 將某一個 bit 設定為 0
        int GetBit(int iIndex);		// 取得某一個 bit 的資料

        CBitList();		// 建構函式
        ~CBitList();		// 解構函式
};
//---------------------------------------------------------------------------
//extern TmyBitList *BitList;
//---------------------------------------------------------------------------
#endif
