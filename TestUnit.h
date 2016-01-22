#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <iostream>
#include <vector>
using namespace std;

class TestUnit
{
    public:
        static void RunAllTest();
        bool Test_Int2List();

        TestUnit();
        ~TestUnit();

        template <class T>
        void AreEqual(T x, T y, string sTestName);

    protected:
    private:
        vector <pair <string, bool>> Result;

};

#endif // TESTUNIT_H
