/*
    全文檢索
*/

#include "main.h"
using namespace std;

int main(int argc, char* argv[])
{

#ifdef DEBUG
    cout << "DEBUGing... DEBUGing... DEBUGing..." << endl;
#endif // DEBUG

    char cInput;

    cout << "1.執行程式測試 2.執行全文檢索 : ";
    cin >> cInput;

    if(cInput == '1')
    {
        cout << "執行程式測試中..." << endl;
        TestUnit myTest;
        myTest.RunAllTest();
    }
    else if(cInput =='2')
    {
        cout << "執行全文檢索中..." << endl;
        string sProgramPath = argv[0];  // 程式目錄
        sProgramPath = sProgramPath.substr(0,sProgramPath.find_last_of("\\/")+1);
        string sIniFile = sProgramPath + "Monster.ini";

        RunFullTextSearch(sIniFile);
    }
    return 0;
}

// 執行全文檢索
void RunFullTextSearch(string sIniFile)
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

