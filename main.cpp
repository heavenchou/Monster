/*
    全文檢索
*/

#include "main.h"
using namespace std;

int main()
{
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
        RunFullTextSearch();
    }
    return 0;
}

// 執行全文檢索
void RunFullTextSearch()
{
    string sBuildList = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\buildlist.txt";
    string sWordIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\wordindex.ndx";
    string sMainIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\main.ndx";

    CMonster * SearchEngine = new CMonster(sBuildList, sWordIndex, sMainIndex);	// 宣告全文檢索

    SearchEngine->SearchWordList.clear();                              // Search Engine 一起更新

    string SearchSentence = "湖南 , 民前";   // 要檢索的句子

    bool bHasRange = false;         // 全部檢索

    bool bFindOK = SearchEngine->Find(SearchSentence,bHasRange);        // 開始搜尋
    int iFoundCount = SearchEngine->FileFound->Total;
    cout << "find : " << iFoundCount << endl;
}


