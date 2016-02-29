//---------------------------------------------------------------------------
#ifndef PostfixStackH
#define PostfixStackH
//---------------------------------------------------------------------------
#include "Int2List.h"
#include "FileList.h"
//---------------------------------------------------------------------------
/*
	###################################
	# 練習計算機運算
	#
	# 原則
	#
	#  如果是數字, 如果有運算符號, 且層數都一樣, 就運算, 結果推入 query stack
	#  如果是數字, 如果有運算符號, 如果層數不一樣, 推入 query stack
	#  如果是數字, 沒有運算符號, 推入 query stack
	#
	#  如果是運算符號, 推入 op stack , 且記錄目前層數
	#
	#  如果是左括號, 目前層數 + 1
	#  如果是右括號, 層數 - 1 , 並且運算
	###################################
*/

class CPostfixStack
{
private:	// User declarations

	char OpStack[100];
	int LevelStack[100];
	int Level;
	int OpStackPoint;

	int QueryStackSize;		// query stack 的大小, 也就是有幾個, 因為若 pop 出來, 暫時不會去 delete 它.
	int QueryStackPoint;	// 目前可以使用到的指標

	void PushLeftBracket(void);
	void PushRightBracket(void);
	void PushOpStack(string sOp);
	void Run(void);						// 進行分析

public:		// User declarations

	CInt2List * QueryStack[100];				// ???? 超過 100 個怎麼辦? 可考慮用 vector 動態成長 ???
	void PushOp(string sOp);		// 傳入一詞的查詢結果
	void PushQuery(CInt2List * FileFoundCount, string sSearchString);		// 傳入一詞的查詢結果
    int GetResult(void);     // 傳回資料的筆數, 不是傳回結果, 若失敗傳回 -1

	void Initial(void);		// 初值化
    CPostfixStack();		// 建構函式
    ~CPostfixStack();		// 解構函式
};
//---------------------------------------------------------------------------
//extern TmyPostfixStack *PostfixStack;
//---------------------------------------------------------------------------
#endif
