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
    Test_Int2List();

    // 呈現結果
    ShowTestResult();

}
// ----------------------------------------------------------------------------
void TestUnit::Test_Int2List()
{
    cout << "測試 Int2List ..." << endl;

    CInt2List * i2l = new CInt2List;
    i2l->Add(1,2);
    pair<int, int> *a = new pair<int, int>(3,4);
    i2l->Add(*a);

    AreEqual(i2l->Int2s[0].first, 1, "Int2List.first");
    AreEqual(i2l->Int2s[1].second, 4, "Int2List.second");

    CInt2List * i2l2 = new CInt2List;
    int is = i2l2->Int2s.size();
    AreEqual(is , 0, "Int2List 新增的 size 是 0");

    i2l->SearchString = "hahaha";
    i2l2->Copy(i2l);
    //i2l2 = i2l;
    cout << "i2l : " << i2l->SearchString << endl;
    cout << "i2l2 : " << i2l2->SearchString << endl;

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
