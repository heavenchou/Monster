/*
    Monster 全文檢索  by Heaven Chou
    使用方法:

      Monster [字串] [起始數字] [列出筆數]

      字串 :
        無字串 或為 ? 或為 help ： 列出本說明
        test1 : 列出單元測試結果 (隱藏版)
        test2 : 列出全文檢索結果 (隱藏版)
        其他字串 : 當成是搜尋字串

      起始數字 : 搜尋的起始 , 預設為 1
      列出筆數 : 每次列出筆數, 預設為 10 , 最大值為 100

    ps.索引檔的位置請在 Monster.ini 中設定
*/

#include "main.h"
using namespace std;

int main(int argc, char* argv[])
{
    // 分析參數
    string sProgramPath = argv[0];  // 程式目錄
    sProgramPath = sProgramPath.substr(0,sProgramPath.find_last_of("\\/")+1);
    string sIniFile = sProgramPath + "Monster.ini";

	string sSearchStr = "";
	int iStartNum = 1;     // 起始筆數
	int iListCount = 10;   // 列出的筆數

	if(argc > 1) sSearchStr = argv[1];	    // 傳入的參數
	if(argc > 2) iStartNum = atoi(argv[2]);	    // 傳入的參數
	if(argc > 3) iListCount = atoi(argv[3]);	// 傳入的參數

	if(iStartNum > 0) iStartNum = iStartNum - 1;    // 因為實際基底是 0 , 所以要減 1
	if(iListCount <= 0) iListCount = 10;            // 預設是 10
	if(iListCount > 100) iListCount = 100;          // 最大只能 100

    if(sSearchStr == "" || sSearchStr == "?" || sSearchStr == "help")
    {
		// 無參數, 列出說明
		cout << "Monster 全文檢索 (Beta)" << endl;
		cout << "使用方法:" << endl << endl;

		cout << "  Monster [字串] [起始數字] [列出筆數]" << endl << endl;

		cout << "  字串 : " << endl;
		cout << "    無字串 或為 ? 或為 help ： 列出本說明" << endl;
		cout << "    其他字串 : 當成是搜尋字串" << endl << endl;

		cout << "  起始數字 : 搜尋的起始 , 預設為 1" << endl;
		cout << "  列出筆數 : 每次列出筆數, 預設為 10 , 最大值為 100" << endl << endl;

		cout << "ps.索引檔的位置請在 Monster.ini 中設定" << endl;
    }
    else if(sSearchStr == "test1")
    {
        cout << "執行程式測試中..." << endl;
        TestUnit myTest;
        myTest.RunAllTest();
    }
    else if(sSearchStr == "test2")
    {
        cout << "測試全文檢索中..." << endl;
        TestFullTextSearch(sIniFile);
    }
    else
    {
        cout << "執行全文檢索中..." << endl;
        RunFullTextSearch(sIniFile, sSearchStr, iStartNum, iListCount);
    }
    return 0;
}

// 測試全文檢索
void TestFullTextSearch(string sIniFile)
{
/*
    string sBuildList = "D:\\Data\\c\\_CodeBlocks\\Monster\\src\\bin\\Debug\\buildlist.txt";
    string sWordIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\src\\bin\\Debug\\wordindex.ndx";
    string sMainIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\src\\bin\\Debug\\main.ndx";
*/
    CTinyIni * TinyIni = new CTinyIni(sIniFile);
    string sBuildList = TinyIni->ReadString("BuildList", "buildlist.txt");
    string sWordIndex = TinyIni->ReadString("WordIndex", "wordindex.ndx");
    string sMainIndex = TinyIni->ReadString("MainIndex", "main.ndx");

    CMonster * SearchEngine = new CMonster(sBuildList, sWordIndex, sMainIndex);	// 宣告全文檢索

    SearchEngine->SearchWordList.clear();                              // Search Engine 一起更新
    ShowTestResult(SearchEngine, "世尊", 3645);
    ShowTestResult(SearchEngine, "菩薩 + 羅漢", 374);
    ShowTestResult(SearchEngine, "如來 & 世尊", 10850);
    ShowTestResult(SearchEngine, "如來 * 世尊", 488);
    ShowTestResult(SearchEngine, "舍利弗 , 阿難", 3998);
    ShowTestResult(SearchEngine, "周海文", 0);
    ShowTestResult(SearchEngine, "覺?法師", 123);
    ShowTestResult(SearchEngine, "覺?法師 - 覺光法師", 4);
    ShowTestResult(SearchEngine, "( 舍利弗 & 阿難 ) + 菩薩", 459);
}

// 執行全文檢索
void RunFullTextSearch(string sIniFile, string sSearchStr, int iStartNum, int iListCount)
{
    CTinyIni * TinyIni = new CTinyIni(sIniFile);
    string sBuildList = TinyIni->ReadString("BuildList", "buildlist.txt");
    string sWordIndex = TinyIni->ReadString("WordIndex", "wordindex.ndx");
    string sMainIndex = TinyIni->ReadString("MainIndex", "main.ndx");

    CMonster * SearchEngine = new CMonster(sBuildList, sWordIndex, sMainIndex);	// 宣告全文檢索

    SearchEngine->SearchWordList.clear();                              // Search Engine 一起更新
    bool bHasRange = false;         // 全部檢索
    //sSearchStr = "阿羅漢";
    bool bFindOK = SearchEngine->Find(sSearchStr, bHasRange);        // 開始搜尋

    SearchEngine->ShowResult(iStartNum , iListCount); // 呈現結果

}

// 測試結果
void ShowTestResult(CMonster * SearchEngine, string sSearchStr, int iResult)
{
    bool bHasRange = false;         // 全部檢索
    bool bFindOK = SearchEngine->Find(sSearchStr,bHasRange);        // 開始搜尋
    cout << "find " << sSearchStr << " : " << SearchEngine->FileFound->Total;
    if(SearchEngine->FileFound->Total == iResult)
        cout << " (OK)" << endl;
    else
        cout << " (XXXXXXXXXXXX)" << endl;
}

