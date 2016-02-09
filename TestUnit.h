#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <iostream>
#include <vector>
//---------------------
#include "Int2List.h"
//---------------------
using namespace std;

class TestUnit
{
    public:
        void RunAllTest();

        void Test_Int2List();

        TestUnit();
        ~TestUnit();

        // 傳入測試及預測結果, 用來判斷是否成功, sTestName 是測試名稱
        template <class T>
        void AreEqual(T x, T y, string sTestName);
        void ShowTestResult();      // 呈現測試結果

    protected:
    private:
        vector <pair <string, bool>> Result;    // 儲存每一個測試的結果

};

#endif // TESTUNIT_H
