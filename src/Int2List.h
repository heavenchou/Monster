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

    // 這個物件是二組 Int 的列表所組合出來的, 每一組表示某一字的範圍

    private:	// User declarations
    public:		// User declarations

        //int FileCount;					// 檔案數目
        //int * Ints;						// 開頭的指標
        //TList * Int2s;
        vector <pair <int,int> > Int2s;     // 裡面放 pair 物件, 每一個 pari 表示某一詞的範圍
        //int Total;
        int NearNum;				// Near 運算的範圍
        int BeforeNum;				// Before 運算的範圍
        string SearchString;        // 搜尋的字串, 一開始可能是 "佛陀" 這種詞, 在運算後可能變成 "(佛陀+羅漢)" 這種運算結果. 這其實是為 ! 運算設計的


        void ClearAll(void);			// 全部清掉
        void operator=(CInt2List * ilTarget);		// 運算子多載
        void operator&=(CInt2List * ilTarget);		// 運算子多載
        void operator|=(CInt2List * ilTarget);		// 運算子多載
        void Copy(CInt2List * ilTarget);		// 將資料 copy 過來
        void AndIt(CInt2List * ilTarget);		// 若二者都有資料, 就二者合併
        void OrIt(CInt2List * ilTarget);		// 二者合併
        void NearIt(CInt2List * ilTarget);		// 若二者靠近至某一個程度, 則變成一個範圍
        void BeforeIt(CInt2List * ilTarget);		// 同 Near , 不過只能在其後面, 也就是有順序的

        void ExcludeIt(CInt2List * ilTarget);		// 排除某一個詞, 例如  舍利!舍利弗 表示只要找舍利, 但不要找到舍利弗

        void Add(pair <int, int> p);	// 加入一筆資料
        void Add(int x, int y);		// 加入一筆資料
        void Delete(int iNum);		// 刪除某一筆資料

        int MyAnsiPos(string sStr1, string sStr2);

        CInt2List();					// 建構函式
        ~CInt2List();					// 解構函式
};
//---------------------------------------------------------------------------
//extern CInt2List *Int2List;
//---------------------------------------------------------------------------
#endif
