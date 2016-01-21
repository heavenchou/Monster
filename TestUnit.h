#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <iostream>
#include <regex>

class TestUnit
{
    public:
        static void RunAllTest();
        TestUnit();
        virtual ~TestUnit();
    protected:
    private:
};

#endif // TESTUNIT_H
