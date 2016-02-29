
#include "PostfixStack.h"
//---------------------------------------------------------------------------
// 建構函式
CPostfixStack::CPostfixStack()
{
	Initial();
	QueryStackSize = 0;
	for(int i=0; i<100; i++)
		QueryStack[i] = 0;
}
//---------------------------------------------------------------------------
CPostfixStack::~CPostfixStack(void)	// 解構函式
{
	for(int i=0; i<QueryStackSize; i++)
		if(QueryStack[i]) delete QueryStack[i];
}
//---------------------------------------------------------------------------
void CPostfixStack::Initial()
{
	// QueryStack = 0;
	Level = 0;
	OpStackPoint = 0;
	QueryStackPoint = 0;
}
//---------------------------------------------------------------------------
// 傳入一個運算符號
void CPostfixStack::PushOp(string sOp)
{
	if(sOp == "(")
	{
		PushLeftBracket();
	}
	else if(sOp == ")")
	{
		PushRightBracket();
	}
	else
	{
		PushOpStack(sOp);
	}
}
//---------------------------------------------------------------------------
// 傳入一個分析好的
void CPostfixStack::PushQuery(CInt2List * FoundPos, string sSearchString)
{
	//  如果是數字, 如果有運算符號, 且層數都一樣, 就運算, 結果推入 query stack
	//  如果是數字, 如果有運算符號, 如果層數不一樣, 推入 query stack
	//  如果是數字, 沒有運算符號, 推入 query stack

	// 先檢查有沒有空間可以用

	if(QueryStackSize == QueryStackPoint)	// 空間不夠, 要 creat 一個新的
	{
		QueryStack[QueryStackPoint] = new CInt2List();
		QueryStackSize++;
	}

	QueryStack[QueryStackPoint]->Copy(FoundPos);
	QueryStack[QueryStackPoint]->SearchString = sSearchString;
	QueryStackPoint++;
	Run();
}
//---------------------------------------------------------------------------
// 處理左括號
inline void CPostfixStack::PushLeftBracket(void)
{
	// 如果是左括號, 目前層數 + 1
	Level++;
}
//---------------------------------------------------------------------------
// 處理右括號
inline void CPostfixStack::PushRightBracket(void)
{
	// 如果是右括號, 層數 - 1 , 並且運算
	Level--;
	Run();
}
//---------------------------------------------------------------------------
// 推入運算符號
inline void CPostfixStack::PushOpStack(string sOp)
{
	// 如果是運算符號, 推入 op stack , 且記錄目前層數
	OpStack[OpStackPoint] = sOp[0];
	LevelStack[OpStackPoint] = Level;
	OpStackPoint++;
}
//---------------------------------------------------------------------------
// 執行運算
void CPostfixStack::Run(void)
{
	if(OpStackPoint <= 0) return;						// 沒有任何運算符號, 所以離開
	if(QueryStackPoint < 2) return;						// 有問題, 不可能小於2
	if(Level != LevelStack[OpStackPoint-1]) return;		// 層級不對, 不能運算

	// 取出運算符號

	OpStackPoint--;
	char cNowOp = OpStack[OpStackPoint];

	switch (cNowOp)
	{
		case '&':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->AndIt(QueryStack[QueryStackPoint]);
			break;
		case ',':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->OrIt(QueryStack[QueryStackPoint]);
			break;
		case '+':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->NearIt(QueryStack[QueryStackPoint]);
			break;
		case '*':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->BeforeIt(QueryStack[QueryStackPoint]);
			break;
		case '-':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->ExcludeIt(QueryStack[QueryStackPoint]);
			break;
	}
}
//---------------------------------------------------------------------------
// 傳回資料的筆數, 不是傳回結果, 若失敗傳回 -1
// 因為程式要傳回筆數, 但有時計算會失敗, 因為使用者用了不適當的運算字串,
// 所以在檢查後若不合格, 就傳回 -1
int CPostfixStack::GetResult(void)
{
    // 檢查的標準如下:
    //
    // 1.運算符號堆疊 op stack 必須為 0
    // 2.運算堆疊 query stack 只有一組
    // 3.層數必須為 0

    // 1.
    if(OpStackPoint !=0) return -1;
    // 2.
    if(QueryStackPoint !=1) return -1;
    // 3.
    if(Level !=0) return -1;

    // 傳回標準的結果
    return (QueryStack[0]->Int2s.size());
}
//---------------------------------------------------------------------------
