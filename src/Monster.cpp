//---------------------------------------------------------------------------

#include "Monster.h"
//---------------------------------------------------------------------------
// 建構函式
CMonster::CMonster(string sFileListFileName,
					string sWordIndexFileName,
					string sMainIndexFileName)
{
	// 初值歸零
	BuildFileList = 0;
	///WordIndex = 0;
	OpPatten = "()&,+*-";		// 算運用的 Patten

	FileListFileName = sFileListFileName;
	WordIndexFileName = sWordIndexFileName;
	MainIndexFileName = sMainIndexFileName;

	MaxSearchWordNum = 20;	// 檢索詞中最多可出現的字串數, "佛陀 & 阿羅漢" 就算 2 個 , 末來可以考慮用 vector 不限數量 ???
	swWord = new CSearchWord*[MaxSearchWordNum];

	for(int i=0; i<MaxSearchWordNum; i++)
	{
		swWord[i] = 0;		// 設定初值, 指標歸 0
	}

	// 先處理 build file list
	OpenBuildList();
	OpenWordIndex();
	OpenMainIndex();

	PostfixStack = new CPostfixStack;
	FileFound = new CIntList(BuildFileList->FileCount);	// 存放每一檔找到的結果
}
//---------------------------------------------------------------------------
// 解構函式
CMonster::~CMonster(void)
{
    /*
	if(BuildFileList) delete BuildFileList;
	if(WordIndex) delete WordIndex;
	if(PostfixStack) delete PostfixStack;
	if(SearchWordList) delete SearchWordList;
	if(FileFound) delete FileFound;
	if(swWord) delete[] swWord;
    */
}
//---------------------------------------------------------------------------
void CMonster::OpenBuildList(void)
{
	BuildFileList = new CFileList(FileListFileName);
	if(!BuildFileList->Initial())
    {	// ???? error check
        cout << "Open BuildList error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenWordIndex(void)
{
	WordIndex = new CWordIndex(WordIndexFileName);

	if(!WordIndex->Initial())
    {	// ???? error check
        cout << "Open WordIndex error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenMainIndex(void)
{
	MainIndex = new CMainIndex(MainIndexFileName);	// ???? error check
}
//---------------------------------------------------------------------------
// 尋找一個字串, 應該要傳回一個檔案串, 表示哪些檔案有
bool CMonster::Find(string sSentence, bool bHasSearchRange)
{
    bool bResult = true;
	FileFound->ClearAll();		// 每一檔找到的數量歸 0
	SearchWordList.clear();
	OKSentence = "";			// 全部歸 0
	FileHintCount = 0;

	AnalysisSentence(sSentence);		// 分析, 並產生 OKSentence

	for(int i=0; i<BuildFileList->FileCount; i++)
	{
		int iResult;
		if(!bHasSearchRange || BuildFileList->SearchMe[i])
			iResult = FindOneFile(i);	// 搜尋單一檔案, 並傳回結果
		else iResult = 0;

        if(iResult == -1)
        {
            bResult = false;        // 運算失敗了
            FileFound->Total = 0;   // 當成沒找到
            break;
        }
        if(iResult > 0) FileHintCount++;
		FileFound->Ints[i] = iResult;
		FileFound->Total = FileFound->Total + iResult;
	}

	// 結束時, 將 swWord 釋放掉

	for(int i=0; i<MaxSearchWordNum; i++)
	{
		if(swWord[i]) delete swWord[i];
		swWord[i] = 0;
	}
    return bResult;
}

//---------------------------------------------------------------------------
// 先分析一下要搜尋的字串
//
// 如果輸入的字串是 (佛陀 & 阿難) | 布施
// 最後會變成
// (S&S)|S		S 表示一個字串, 存在  SearchWordList 之中
void CMonster::AnalysisSentence(string sSentence)
{
	SearchWordList.clear();
	string sPatten;

	// 目前第幾個字串? 例如 (S&S)|S  (佛陀&阿難)|布施  佛陀是第 0 個
	int iPattenNum = 0;

	while (sSentence.length())
	{
		sPatten = CutPatten(sSentence);
        // 刪除左邊的空格
        if(sSentence[0] == ' ') sSentence = sSentence.substr(sSentence.find_first_not_of(' '));

		if((sPatten.find_first_of(OpPatten) == 0) && (sPatten.length()==1))		// 如果是運算符號的話
		{
			//PostfixStack->PushOp(sPatten);
			OKSentence += sPatten;
		}
		else
		{
			// 處理一個字

			SearchWordList.push_back(sPatten);	// 先記錄起來
			swWord[iPattenNum] = new CSearchWord(sPatten);	// 將此字準備好
			OKSentence += "S";
			iPattenNum++;
		}
	}
}

//---------------------------------------------------------------------------
string CMonster::CutPatten(string & sString)
{
	// 刪除左邊的空格
	if(sString[0] == ' ')
        sString = sString.substr(sString.find_first_not_of(' '));

	string sTmp = sString;

	/// OpPatten = "&,+*()-";
	if((sString.find_first_of(OpPatten) == 0) && ((sString.length() == 1)||(sString[1] == ' ')))		// 如果是運算符號, 後面必須是空格或沒字了
	{
		sString = sString.substr(1);
		return (sTmp.substr(0,1));
	}
	else
	{
		// 找出下一個 patten 的位置或結束

		size_t sPos = sString.find_first_of(OpPatten);
		while(sPos != std::string::npos)
        {
            if((sString.length() == sPos + 1)||(sString[sPos+1] == ' '))
            {
                // 找到了
 				sString = sString.substr(sPos);
 				sTmp = sTmp.substr(0,sPos);

 				// 移除 sTmp 右邊空格
 				sTmp = sTmp.substr(0,sTmp.find_last_not_of(' ')+1);
				return (sTmp);
            }
            else
            {
                sPos = sString.find_first_of(OpPatten,sPos+1);
            }
        }

		sString = "";
		sTmp = sTmp.substr(0,sTmp.find_last_not_of(' ')+1);
		return (sTmp);
	}
}

//---------------------------------------------------------------------------
// 尋找一個字串, 應該要傳回一個檔案串, 表示哪些檔案有
int CMonster::FindOneFile(int iFileNum)
{
	/*
	###################################
	# 練習計算機運算
	#
	# 原則
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

	PostfixStack->Initial();
	string sPatten;
	string sOKSentence = OKSentence;	// 暫存的字串

	// 目前第幾個字串? 例如 (S&S)|S  (佛陀&阿難)|布施  佛陀是第 0 個
	int iPattenNum = 0;

	//while (sOKSentence.Length())
	for(int i=0; i<OKSentence.length(); i++)
	{
		sPatten = sOKSentence.substr(i,1);		// 取出 patten
		if(sPatten.find_first_of(OpPatten) == 0)		// 如果是運算符號的話
		{
			PostfixStack->PushOp(sPatten);
		}
		else
		{
			// ???? 加速的方法, 如果是 and 就只算前一個有結果的, 如果是 or 就只查前一個是沒找到的
			// ???? 加速的方法, 如果不統計次數, 有找到就算數, 那麼速度會更快

			// 處理一個字

			sPatten = SearchWordList[iPattenNum];	// 取出某一筆字串
			swWord[iPattenNum]->Search(iFileNum);			// 只在某個檔搜尋
			PostfixStack->PushQuery(swWord[iPattenNum]->FoundPos, sPatten);
			iPattenNum++;
		}
	}
	// ???? 這是組數, 不是筆數, 例如 佛陀 near 阿難 可能算是 1 組
	// return (PostfixStack->QueryStack[0]->Int2s->Count);
    return (PostfixStack->GetResult());
}
//---------------------------------------------------------------------------
// 秀出成果
/* 傳回範例

{
  "num_found": 2628,
  "total_term_hits": 3860,
  "results": [
    {
      "id": 12298,
      "juan": 1,
      "orig": 1,
      "category": "法華部類",
      "canon": "T",
      "vol": "T09",
      "work": "T0270",
      "edition": "大",
      "term_hits": 31,
      "work": "T0270",
      "category": "法華部",
      "title": "大法鼓經",
      "creators": "求那跋陀羅",
      "file": "T09n0270",
      "juan_start": 1,
      "byline": "劉宋 求那跋陀羅譯",
      "time_dynasty": "劉宋",
      "time_from": 420,
      "time_to": 479
    },
    {
      "id": 12297,
      "juan": 1,
      "orig": 0,
      "category": "法華部類",
      "canon": "T",
      "vol": "T09",
      "work": "T0270",
      "edition": "CBETA",
      "term_hits": 30,
      "work": "T0270",
      "category": "法華部",
      "title": "大法鼓經",
      "creators": "求那跋陀羅",
      "file": "T09n0270",
      "juan_start": 1,
      "byline": "劉宋 求那跋陀羅譯",
      "time_dynasty": "劉宋",
      "time_from": 420,
      "time_to": 479
    },
    {
      "id": 12299,
      "juan": 1,
      "orig": 0,
      "category": "法華部類",
      "canon": "T",
      "vol": "T09",
      "work": "T0270",
      "edition": "大→元",
      "term_hits": 30,
      "work": "T0270",
      "category": "法華部",
      "title": "大法鼓經",
      "creators": "求那跋陀羅",
      "file": "T09n0270",
      "juan_start": 1,
      "byline": "劉宋 求那跋陀羅譯",
      "time_dynasty": "劉宋",
      "time_from": 420,
      "time_to": 479
    },
    ...
  ]
}
*/
// 秀出成果 iStartNnum : 起始筆數, iListCount : 列出筆數
void CMonster::ShowResult(int iStartNum, int iListCount)
{

    string sResult = "{\n";
    sResult = sResult + "\t\"num_found\": " + int_to_string(FileFound->Total) + ",\n";
    sResult = sResult + "\t\"total_term_hits\": " + int_to_string(FileHintCount) + ",\n";
    sResult = sResult + "\t\"results\": [\n";

    int iCount = 0; // 找到的筆數

    for(int i=0; i<FileFound->FileCount; i++)
    {
        // 有搜尋到才處理
        if(FileFound->Ints[i]>0)
        {
            if(iCount >= iStartNum) // 要 >= 指定的筆數才印出來
            {
                sResult = sResult + "\t  {\n";

                // 各卷的資料

                sResult = sResult + "\t\t" + "\"id\": " + int_to_string(iCount) + ",\n";
                sResult = sResult + "\t\t" + "\"juan\": " + int_to_string(BuildFileList->JuanNum[i]) + ",\n";
                sResult = sResult + "\t\t" + "\"canon\": " + BuildFileList->Book[i] + ",\n";
                sResult = sResult + "\t\t" + "\"vol\": " + BuildFileList->Book[i] + BuildFileList->Vol[i] + ",\n";
                sResult = sResult + "\t\t" + "\"work\": " + BuildFileList->Book[i] + BuildFileList->SutraNum[i] + ",\n";
                sResult = sResult + "\t\t" + "\"term_hits\": " + int_to_string(FileFound->Ints[i]) + ",\n";
                sResult = sResult + "\t\t" + "\"file\": " + BuildFileList->Book[i] + BuildFileList->Vol[i] + "n" + BuildFileList->SutraNum[i] + ",\n";

                sResult = sResult + "\t  },\n";
            }

            iCount++;

            if(iCount >= iListCount + iStartNum ) break;    // 若超過列印的筆數, 就中止
        }
    }

    sResult = sResult + "\t]\n";
    sResult = sResult + "}\n";

    cout << sResult;


    /*
    cout <<  "{";
    cout <<  "\t\"num_found\": " << FileFound->Total << "," << endl;
    cout <<  "\t\"total_term_hits\": " << FileHintCount << "," << endl;
    cout <<  "\t\"results\": [" << endl;
    cout <<  "\t]" << endl;
    cout <<  "}" << endl;
    */

}
// int to string
string CMonster::int_to_string(int i)
{
    char c[50];
    sprintf(c, "%d", i);
    string s = c;
    return s;
}
