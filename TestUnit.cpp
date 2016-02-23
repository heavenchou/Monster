#include "TestUnit.h"

TestUnit::TestUnit()
{
}

TestUnit::~TestUnit()
{
}

void TestUnit::RunAllTest()
{
    // 測試 Int2List
    cout << "測試 Int2List ..." << endl;
    Test_Int2List();

    // 測試 Monster
    cout << "測試 Monster ..." << endl;
    Test_Monster();

    // 測試 SearchWord
    cout << "測試 SearchWord ..." << endl;
    // 無法測, 因為用到 worddata, 它用到 buildfilelist, 有待改進 ???
    //Test_SearchWord();

    // 呈現結果
    ShowTestResult();

}
// ----------------------------------------------------------------------------
void TestUnit::Test_Int2List()
{
    CInt2List * i2l = new CInt2List;
    i2l->Add(1,2);
    pair<int, int> *a = new pair<int, int>(3,4);
    i2l->Add(*a);

    AreEqual(i2l->Int2s[0].first, 1, "Int2List.first");
    AreEqual(i2l->Int2s[1].second, 4, "Int2List.second");

    CInt2List * i2l2 = new CInt2List;
    int is = i2l2->Int2s.size();
    AreEqual(is , 0, "Int2List 新增的 size 是 0");

    i2l2->Copy(i2l);

    AreEqual(i2l2->Int2s[0].second, 2, "Copy 後的 Int2List.first");
    AreEqual(i2l2->Int2s[1].first, 3, "Copy 後的 Int2List.second");
    AreEqual((int)i2l2->Int2s.size(), 2, "Copy 後的 Int2List size");

    i2l->Delete(0);
    AreEqual((int)i2l->Int2s.size(), 1, "Int2List 刪掉一筆後的 size");
    AreEqual(i2l->Int2s[0].first, 3, "刪掉一筆後的 Int2List.first");
    i2l->Delete(1);
    AreEqual((int)i2l->Int2s.size(), 0, "Int2List 刪掉二筆後的 size");
    AreEqual((int)i2l->Int2s.size() , 0, "Int2List Delete 後的 size 是 0");

    // 測試 OrIt
    CInt2List * i2l3 = new CInt2List;
    i2l3->Add(1,2);
    i2l3->Add(15,16);
    i2l3->Add(35,36);

    CInt2List * i2l4 = new CInt2List;
    i2l4->Add(5,6);
    i2l4->Add(25,26);

    i2l3->OrIt(i2l4);

    AreEqual((int)i2l3->Int2s.size() , 5, "Int2List OrIt 後的 size 是 5");
    AreEqual((int)i2l3->Int2s[1].first , 5, "Int2List OrIt 後的第二筆 .first 是 5");
    AreEqual((int)i2l3->Int2s[4].second , 36, "Int2List OrIt 後的第五筆 .second 是 36");

    // 測試 NearIT
    //             (50,52) , (100,102) ,                     (200,202)
    // (1,3)(45, 48),                  (110,113) , (140, 143)
    // 結果 (45, 52)         (100,113)

    CInt2List * i2l5 = new CInt2List;
    i2l5->Add(50,52);
    i2l5->Add(100,102);
    i2l5->Add(200,202);

    CInt2List * i2l6 = new CInt2List;
    i2l6->Add(1,3);
    i2l6->Add(45, 48);
    i2l6->Add(110,113);
    i2l6->Add(140, 143);

    i2l5->NearIt(i2l6);

    AreEqual((int)i2l5->Int2s.size() , 2, "Int2List NearIT 後的 size 是 2");
    AreEqual((int)i2l5->Int2s[0].first , 45, "Int2List NearIT 後的第一筆 .first 是 45");
    AreEqual((int)i2l5->Int2s[1].second , 113, "Int2List NearIT 後的第二筆 .second 是 113");


    // 測試 BeforeIt
    //         (50,52) ,       (100,102)             (200,202)
    // (45, 48),      (60, 63)        (110,113) ,            (210, 213)
    // 結果 (50, 63)           (100,113) ,           (200, 213)

    CInt2List * i2l7 = new CInt2List;
    i2l7->Add(50,52);
    i2l7->Add(100,102);
    i2l7->Add(200,202);

    CInt2List * i2l8 = new CInt2List;
    i2l8->Add(45, 48);
    i2l8->Add(60, 63);
    i2l8->Add(110,113);
    i2l8->Add(210, 213);

    i2l7->BeforeIt(i2l8);

    AreEqual((int)i2l7->Int2s.size() , 3, "Int2List BeforeIt 後的 size 是 3");
    AreEqual((int)i2l7->Int2s[0].first , 50, "Int2List BeforeIt 後的第一筆 .first 是 50");
    AreEqual((int)i2l7->Int2s[2].second , 213, "Int2List BeforeIt 後的第三筆 .second 是 213");

    // 測試 ExcludeIt
    //   (50,52) , (100,102)          (200,202),      (300, 303)
    // (49, 52),   (100, 104)   (198,201) , (201,203)
    // 結果 (200,202), (300, 303)

    CInt2List * i2l9 = new CInt2List;
    i2l9->Add(50,52);
    i2l9->Add(100,102);
    i2l9->Add(200,202);
    i2l9->Add(300,303);

    CInt2List * i2la = new CInt2List;
    i2la->Add(49, 52);
    i2la->Add(100, 104);
    i2la->Add(198,201);
    i2la->Add(201,203);

    i2l9->ExcludeIt(i2la);

    AreEqual((int)i2l9->Int2s.size() , 2, "Int2List ExcludeIt 後的 size 是 2");
    AreEqual((int)i2l9->Int2s[0].first , 200, "Int2List ExcludeIt 後的第一筆 .first 是 200");
    AreEqual((int)i2l9->Int2s[1].second , 303, "Int2List ExcludeIt 後的第二筆 .second 是 303");

    /*
    for(int i=0; i<i2l9->Int2s.size(); i++)
    {
        auto j = i2l9->Int2s[i];
        cout << j.first << "," << j.second << endl;
    }
    */


}
// ----------------------------------------------------------------------------
template <class T>
void TestUnit::AreEqual(T x, T y, string sTestName)
{
    if(x == y)
    {
        pair<string, bool> *a = new pair<string, bool>(sTestName, true);
        Result.push_back(*a);
    }
    else
    {
        pair<string, bool> *a = new pair<string, bool>(sTestName, false);
        Result.push_back(*a);
    }
}
// ----------------------------------------------------------------------------
// 呈現所有錯誤的測試
void TestUnit::ShowTestResult()
{
    cout << "======================================" << endl;
    cout << "= 成功\的測試                         =" << endl;
    cout << "======================================" << endl;

    int iCount = 0;
    for(auto it = Result.begin(); it != Result.end(); it++)
    {
        if(it->second == true)
        {
            iCount++;
            cout << "O " << it->first << endl;
        }
    }
    cout << "======================================" << endl;
    cout << "全部共有 " << iCount << " 項測試成功\!" << endl << endl;

    cout << "======================================" << endl;
    cout << "= 失敗的測試                         =" << endl;
    cout << "======================================" << endl;

    iCount = 0;
    for(auto it = Result.begin(); it != Result.end(); it++)
    {
        if(it->second == false)
        {
            iCount++;
            cout << "X " << it->first << endl;
        }
    }
    cout << "======================================" << endl;
    cout << "全部共有 " << iCount << " 項測試錯誤!" << endl;
}
// ----------------------------------------------------------------------------
void TestUnit::Test_Monster()
{
    /*
    // 要先宣才能測, 比較麻煩, 所以先別測

    string sSentence = "( 佛陀 * ( 持[金*本] ) + ( 佛 , 世尊 ) )";
    string sPatten;

    string sSentence = "佛陀 * ( 持[金*本] ) + ( 佛 , 世尊 ) & 目標";
    string sPatten;

    while (sSentence.length())
	{
		sPatten = SearchEngine->CutPatten(sSentence);
		cout << "\"" << sPatten << "\" : ";
		cout << "\"" << sSentence << "\"" << endl;
	}

    sSentence = "佛陀 * ( 持[金*本] ) + ( 佛 , 世尊 ) & 目標";
    sPatten;

    while (sSentence.length())
	{
		sPatten = SearchEngine->CutPatten(sSentence);
		cout << "\"" << sPatten << "\" : ";
		cout << "\"" << sSentence << "\"" << endl;
	}

	sSentence = "( 佛陀 * ( 持[金*本] ) + ( 佛 , 世尊 ) & 目標 )";
    SearchEngine->AnalysisSentence(sSentence);
    cout << "OKSentence : " << SearchEngine->OKSentence << endl;
    for(int i=0; i<SearchEngine->SearchWordList.size(); i++)
    {
        cout << i << " : " << SearchEngine->SearchWordList[i] << endl;
    }

	*/
}
// ----------------------------------------------------------------------------
void TestUnit::Test_SearchWord()
{
    CSearchWord * Word = new CSearchWord("佛陀持[金*本]及&CB01234;");

    AreEqual((int)Word->Tokens.size() , 6, "SearchWord Tokens 的 size 是 6");
    AreEqual((string)Word->Tokens[3] , (string)"[金*本]", "SearchWord Tokens[3] 是 [金*本]");
    AreEqual((string)Word->Tokens[5] , (string)"&CB01234;", "SearchWord Tokens[5] 是 &CB01234;");
}
