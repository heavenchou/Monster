#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <iostream>
#include <vector>
//---------------------
#include "Int2List.h"
#include "Monster.h"
#include "SearchWord.h"
//---------------------
using namespace std;

class TestUnit
{
    public:
        void RunAllTest();

        void Test_Int2List();
        void Test_Monster();
        void Test_SearchWord();

        TestUnit();
        ~TestUnit();

        // �ǤJ���դιw�����G, �ΨӧP�_�O�_���\, sTestName �O���զW��
        template <class T>
        void AreEqual(T x, T y, string sTestName);
        void ShowTestResult();      // �e�{���յ��G

    protected:
    private:
        vector <pair <string, bool>> Result;    // �x�s�C�@�Ӵ��ժ����G

};

#endif // TESTUNIT_H
