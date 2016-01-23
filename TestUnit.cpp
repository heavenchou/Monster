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

    AreEqual<int>(3, 4, "3=4?");
    AreEqual<float>(3.1, 4.1, "3.1=4.1?");
    AreEqual<int>(3.1, 3.2, "(int)3.1=3.2?");
    AreEqual<string>("test", "test", "test=test");
    AreEqual<string>("test1", "test2", "test1=test2");

    ShowTestResult();

}

void TestUnit::Test_Int2List()
{
    cout << "測試 Int2List" << endl;
}

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
// -------------------------------------------------------
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
