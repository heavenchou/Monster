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
// 運算子多載 =
void CInt2List::operator=(CInt2List * ilTarget)
{
    Copy(ilTarget);
}
//---------------------------------------------------------------------------
// 將資料 copy 過來
void CInt2List::Copy(CInt2List * ilTarget)
{
    Int2s = ilTarget->Int2s;
    // SearchString = ilTarget->SearchString;  copy 還是不要去改搜尋字串比較好
}
//---------------------------------------------------------------------------
// 運算子多載
void CInt2List::operator&=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// 若二者都有資料, 就二者合併
void CInt2List::AndIt(CInt2List * ilTarget)
{
	// 只要有一個人是 0 , 就玩不下去了

    SearchString = "(" + SearchString + "&" + ilTarget->SearchString + ")";     // 變成 "(word1&word2)"
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
	}
	else	//接下來就要將二人合併了
	{
		//OrIt(ilTarget);
    }
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
	//TPoint * tpPtr1, *tpPtr2;
	pair<int, int> tpPtr1, tpPtr2;

    SearchString = "(" + SearchString + "," + ilTarget->SearchString + ")";     // 變成 "(word1,word2)"

	if(Int2s.size() == 0)	// 我自己沒有資料
	{
		Copy(ilTarget);
		return;
	}

	if(ilTarget->Int2s.size() == 0)		// 對方沒有資料
    {
		return;
    }

    /*
    // 這一段有點奇怪, 為什麼不能改成底下那樣?... 原來沒錯了, 因為最後是用 Insert, 不是插入在最後
	for(int i=0; i<ilTarget.Int2s.size; i++)
	{
		tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[i];
		while(tpPtr2->x >= tpPtr1->x)
		{
			iIndex++;
			if(iIndex == Int2s.size) break;
			tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		}
		TPoint * tpNew = new TPoint(tpPtr2->x, tpPtr2->y);	// 這裡花了一天半去捉 bug 10/19 '03
		Int2s->Insert(iIndex,tpNew);
	}
	*/

    // 雖然 vector 也可以插入, 但效率不好, 所以改用其他方法, 手動將二個 vector 合併成一個

    vector <pair <int,int> > pairTmp;

	for(int i=0; i<ilTarget->Int2s.size(); i++)
	{
		tpPtr1 = Int2s[iIndex];
		tpPtr2 = ilTarget->Int2s[i];
		if(iIndex < Int2s.size())
        {
            while(tpPtr2.first >= tpPtr1.first)
            {
                pairTmp.push_back(tpPtr1);

                iIndex++;
                tpPtr1 = Int2s[iIndex];
                if(iIndex == Int2s.size()) break;
            }
        }
        pairTmp.push_back(tpPtr2);
	}

    // 可能還有還沒處理完的, 要繼續處理
    while(iIndex < Int2s.size())
    {
        pairTmp.push_back(tpPtr1);
        iIndex++;
        tpPtr1 = Int2s[iIndex];
    }

	Int2s = pairTmp;
}

//---------------------------------------------------------------------------
// 若二者靠近至某一個程度, 則變成一個範圍
void CInt2List::NearIt(CInt2List * ilTarget)
{

	NearNum = 30; //fmOption->Setting->NearNum;			// Near 運算的範圍     ???? 要用使用者輸入
    string sSearchString = "(" + SearchString + "+" + ilTarget->SearchString + ")";     // 變成 "(word1+word2)"


	// 沒資料就結束
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];
		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

			// 找到一組
			if((tpPtr2.first - tpPtr1.second <= NearNum) && (tpPtr1.first - tpPtr2.second <= NearNum))
			{
				pair <int,int> tpNew = pair <int,int>(min(tpPtr1.first, tpPtr2.first), max(tpPtr1.second, tpPtr2.second));
				pairTmp.push_back(tpNew);
			}
			else
				if (tpPtr2.first - tpPtr1.second > NearNum) break;	// 找不到了, 換下一組
		}
	}

	Int2s = pairTmp;
    SearchString = sSearchString;
}

//---------------------------------------------------------------------------
// 同 Near , 不過只能在其後面, 也就是有順序的
void CInt2List::BeforeIt(CInt2List * ilTarget)
{
	BeforeNum = 30; //fmOption->Setting->BeforeNum;		// Before 運算的範圍   ???? 要用使用者輸入
    string sSearchString = "(" + SearchString + "*" + ilTarget->SearchString + ")";     // 變成 "(word1*word2)"

	// 沒資料就結束
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];
		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

			// 找到一組
			if((tpPtr2.first - tpPtr1.first > 0 ) && (tpPtr2.first - tpPtr1.second <= BeforeNum))
			{
				pair <int,int> tpNew = pair <int,int>(tpPtr1.first, max(tpPtr1.second, tpPtr2.second));
				pairTmp.push_back(tpNew);
			}
			else
				if (tpPtr2.first - tpPtr1.second > BeforeNum) break;	// 找不到了, 換下一組
		}
	}

	Int2s = pairTmp;
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

    SearchString = "(" + SearchString + "-" + ilTarget->SearchString + ")";     // 變成 "(word1!word2)"

	if(Int2s.size() == 0)	// 我自己沒有資料
	{
		ClearAll();
		return;
	}

	if(ilTarget->Int2s.size() == 0)		// 對方沒有資料, 或二個詞根本沒有相同處
    {
		return;
    }

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

    // 這一段似乎可以再快一點, 不用跑二個迴圈....如果讓二段交叉前進 ???
	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];

        bool bPush = true;  // 預設這一組是可用的, 除非在 ilTarget 找到被排除的詞

		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

            if(tpPtr1.first > tpPtr2.second) // 第二組還太遠, 先跳過
			{
                continue;
            }
			// 找到重複的 , 這一組要刪除
            if(((tpPtr1.first >= tpPtr2.first) && (tpPtr1.second <= tpPtr2.second))||((tpPtr1.first <= tpPtr2.first) && (tpPtr1.second >= tpPtr2.second)))
			{
                bPush = false;
                break;
            }
            if(tpPtr2.first > tpPtr1.second) // 不用再找了, 找不到的.
			{
                break;
            }
		}

		if(bPush)
        {
            pairTmp.push_back(tpPtr1);
        }

	}

	Int2s = pairTmp;
}
/*
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
