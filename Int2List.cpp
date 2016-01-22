//---------------------------------------------------------------------------
#include "Int2List.h"
//#include "Option.h"
//---------------------------------------------------------------------------
// 建構函式
CInt2List::CInt2List()
{
	//FileCount = iFileCount;
	//Total = 0;
	//Ints = 0;
	//Ints = new int[FileCount];

    SearchString = "";        // 搜尋的字串, 一開始可能是 "佛陀" 這種詞, 在運算後可能變成 "(佛陀+羅漢)" 這種運算結果. 這其實是為 ! 運算設計的

	///Int2s = new TList;
}
//---------------------------------------------------------------------------
// 解構函式
CInt2List::~CInt2List(void)
{
	ClearAll();

	///if(Int2s) delete Int2s;
}
//---------------------------------------------------------------------------
// 全部清掉
inline void CInt2List::ClearAll(void)
{
	Int2s.clear();
}
//---------------------------------------------------------------------------
// 加入某一筆
void CInt2List::Add(pair <int, int> p)
{
	//TPoint * tpNew = new TPoint(tpPtr->x, tpPtr->y);
	Int2s.push_back(p);
}
//---------------------------------------------------------------------------
// 加入某一筆
void CInt2List::Add(int x, int y)
{
	Int2s.push_back(pair<int,int>(x,y));
}
//---------------------------------------------------------------------------
// 刪除某一筆
void CInt2List::Delete(int iNum)
{
	Int2s.erase(Int2s.begin()+iNum-1);
}
//---------------------------------------------------------------------------
// 運算子多載
void CInt2List::operator=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// 將資料 copy 過來
void CInt2List::Copy(CInt2List * ilTarget)
{
    Int2s = ilTarget->Int2s;

	//ClearAll();
	//for (int i=0; i<ilTarget->Int2s->Count; i++)
	//{
	//	Add((TPoint *)ilTarget->Int2s->Items[i]);
	//}

    // SearchString = ilTarget->SearchString;  copy 還是不要去改搜尋字串比較好
}
//---------------------------------------------------------------------------
// 運算子多載
void CInt2List::operator&=(CInt2List * ilTarget)
{
}
/*
//---------------------------------------------------------------------------
// 若二者都有資料, 就二者合併
void CInt2List::AndIt(CInt2List * ilTarget)
{
	// 只要有一個人是 0 , 就玩不下去了

    string sSearchString = "(" + SearchString + "&" + ilTarget->SearchString + ")";     // 變成 "(word1&word2)"
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
	}
	else	//接下來就要將二人合併了
	{
		OrIt(ilTarget);
    }
    SearchString = sSearchString;     // 變成 "(word1&word2)"
}
//---------------------------------------------------------------------------
// 運算子多載
void CInt2List::operator|=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// 二者合併
void CInt2List::OrIt(CInt2List * ilTarget)
{
	int iIndex = 0;		// 移動中的指標
	TPoint * tpPtr1, *tpPtr2;

    string sSearchString = "(" + SearchString + "," + ilTarget->SearchString + ")";     // 變成 "(word1,word2)"
	if(Int2s->Count == 0)	// 我自己沒有資料
	{
		Copy(ilTarget);
        SearchString = sSearchString;
		return;
	}

	if(ilTarget->Int2s->Count == 0)		// 對方沒有資料
    {
        SearchString = sSearchString;
		return;
    }

	for(int i=0; i<ilTarget->Int2s->Count; i++)
	{
		tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[i];
		while(tpPtr2->x >= tpPtr1->x)
		{
			iIndex++;
			if(iIndex == Int2s->Count) break;
			tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		}
		TPoint * tpNew = new TPoint(tpPtr2->x, tpPtr2->y);	// 這裡花了一天半去捉 bug 10/19 '03
		Int2s->Insert(iIndex,tpNew);
	}
    SearchString = sSearchString;
}
//---------------------------------------------------------------------------
// 若二者靠近至某一個程度, 則變成一個範圍
void CInt2List::NearIt(CInt2List * ilTarget)
{
	NearNum = fmOption->Setting->NearNum;			// Near 運算的範圍     ???? 要用使用者輸入
    string sSearchString = "(" + SearchString + "+" + ilTarget->SearchString + ")";     // 變成 "(word1+word2)"

	// 沒資料就結束
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	TList * tlResult = new TList;		// 放結果用的
	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr1 =  (TPoint *) Int2s->Items[i];
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// 找到一組
			//if(!((tpPtr2->x - tpPtr1->y > NearRange) || (tpPtr1->x - tpPtr2->y > NearRange)))
			if((tpPtr2->x - tpPtr1->y <= NearNum) && (tpPtr1->x - tpPtr2->y <= NearNum))
			{
				TPoint * tpNew = new TPoint(min(tpPtr1->x, tpPtr2->x), max(tpPtr1->y, tpPtr2->y));
				tlResult->Add(tpNew);
			}
			else
				if (tpPtr2->x - tpPtr1->y > NearNum) break;	// 找不到了, 換下一組
		}
	}

	ClearAll();
	if(Int2s) delete Int2s;
	Int2s = tlResult;			// 換成成果
    SearchString = sSearchString;

}
//---------------------------------------------------------------------------
// 同 Near , 不過只能在其後面, 也就是有順序的
void CInt2List::BeforeIt(CInt2List * ilTarget)
{
	BeforeNum = fmOption->Setting->BeforeNum;		// Before 運算的範圍   ???? 要用使用者輸入
    string sSearchString = "(" + SearchString + "*" + ilTarget->SearchString + ")";     // 變成 "(word1*word2)"

	// 沒資料就結束
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	TList * tlResult = new TList;		// 放結果用的
	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr1 =  (TPoint *) Int2s->Items[i];
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// 找到一組
			if((tpPtr2->x - tpPtr1->x > 0) && (tpPtr2->x - tpPtr1->y <= BeforeNum))
			{
				TPoint * tpNew = new TPoint(tpPtr1->x, max(tpPtr1->y, tpPtr2->y));
				tlResult->Add(tpNew);
			}
			else
				if (tpPtr2->x - tpPtr1->y > BeforeNum) break;	// 找不到了, 換下一組
		}
	}

	ClearAll();
	if(Int2s) delete Int2s;
	Int2s = tlResult;			// 換成成果
    SearchString = sSearchString;
}
//---------------------------------------------------------------------------
// 排除某一個詞, 例如  舍利!舍利弗 表示只要找舍利, 但不要找到舍利弗
void CInt2List::ExcludeIt(CInt2List * ilTarget)
{
    // 做法 :
    // 先找這個詞的詞距 , 例如 舍利!舍利弗 詞距為 0 , 而 羅漢!阿羅漢 則詞距為 1 (第一個詞在第二個詞的位置)
    // 再分別搜尋這二個詞 , 搜尋後再處理,
    // 例如舍利 找到  1, 10, 20, 30 , 而舍利弗找到 1, 20 , 表示這二組要移除

    //int iExcludeNum = (ilTarget->SearchString.AnsiPos(SearchString) - 1)/2; // 詞距

    // 可惜這一段也沒用了
    //int iExcludeNum = MyAnsiPos(SearchString , ilTarget->SearchString) - 1; // 詞距, 減一是希望由 0 算起

    string sSearchString = "(" + SearchString + "-" + ilTarget->SearchString + ")";     // 變成 "(word1!word2)"

	if(Int2s->Count == 0)	// 我自己沒有資料
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	if(ilTarget->Int2s->Count == 0)		// 對方沒有資料, 或二個詞根本沒有相同處
    {
        SearchString = sSearchString;
		return;
    }

	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
        tpPtr1 =  (TPoint *) Int2s->Items[i];

		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// 找到重複的 , 這一組要刪除
			// if((tpPtr1->x - tpPtr2->x == iExcludeNum)) // 這是舊的方法, 要換成 tpPtr1 與 tpPtr2 不在彼此範圍中
            if(((tpPtr1->x >= tpPtr2->x) && (tpPtr1->y <= tpPtr2->y))||((tpPtr1->x <= tpPtr2->x) && (tpPtr1->y >= tpPtr2->y)))
			{
                Delete(i);
                i--;
                //ilTarget->Delete(j);
                break;
            }
            if(tpPtr2->x > tpPtr1->y) // 不用再找了, 找不到的.
			{
                break;
            }
		}
	}

    SearchString = sSearchString;
}
//---------------------------------------------------------------------------
// 找出第二個字串在第一個字串的距離, 但這是以中文來算的
// 例如 阿難,佛告阿難 , 則傳回 3 , 因為 "阿" 在 "佛告阿難" 第三個字
// 又如 阿難, &#X1234;[金*本]阿難, 也傳回 3 , 因為 "&#X1234;[金*本]" 只是二個字
int CInt2List::MyAnsiPos(string sStr1, string sStr2)
{
    int iResult = 0;
    for(int i=1; i<=sStr2.Length(); i++)
    {
        if(!sStr2.IsTrailByte(i))
        {
            if(sStr2.Length()-i+1 >= sStr1.Length())    // 第二組剩下的長度一定要比第一組長
            {
                bool bFound = true;      // 先假設找到了
                int k = i - 1;

                for(int j = 1 ; j<=sStr1.Length(); j++)
                {
                    if(sStr2[k+j] != sStr1[j] && sStr1[j] != '?') // 問號另外處理
                    {
                        bFound = false;
                        break;
                    }
                    if(sStr2[k+j] != sStr1[j] && sStr1[j] == '?') // 這種情況  妙?菩薩!妙音菩薩
                    {
                        if(sStr2.IsLeadByte(k+j) && sStr2.IsTrailByte(k+j+1))
                        {
                            k++;    // 一個問號對上一個中文字, 所以要向後移一個字
                            if(sStr2.Length()-k < sStr1.Length())
                            {
                                bFound = false;
                                break;
                            }
                        }
                    }
                }
                if(bFound)
                {
                    iResult = i;
                    break;
                }
            }
        }
    }
    if(iResult <= 1)
        return iResult;     // 0 或 1 , 就直接傳回
    else
    {
        // 若輸入是 阿難, &#X1234;[金*本]阿難 , 則底下的 sStr = "&#X1234;[金*本]" , 現在則要找此字串的長度
        string sStr = sStr2.SubString(1,iResult-1);

        int iCount = 0;
        while(sStr.Length()>0)
        {
            if(sStr[1] == '&' && sStr[2] == '#')
            {
                int tmp = sStr.AnsiPos(";");
                if(tmp > 0)
                {
                    // 找到 &#....;
                    iCount++;
                    sStr = sStr.Delete(1,tmp);
                }
                else
                {
                    iCount++;
                    sStr = sStr.Delete(1,1);
                }
            }
            else if(sStr[1] == '[')
            {
                int tmp = sStr.AnsiPos("]");
                if(tmp > 0)
                {
                    // 找到 [金*本]
                    iCount++;
                    sStr = sStr.Delete(1,tmp);
                }
                else
                {
                    iCount++;
                    sStr = sStr.Delete(1,1);
                }
            }
            else if(sStr.Length() == 1) // 剩一個字元
            {
                iCount++;
                sStr = sStr.Delete(1,1);
            }
            else if(sStr.IsLeadByte(1) && sStr.IsTrailByte(2))  // 這是中文字
            {
                iCount++;
                sStr = sStr.Delete(1,2);
            }
            else
            {
                iCount++;
                sStr = sStr.Delete(1,1);
            }
        }
        return iCount+1;
    }
}
*/
