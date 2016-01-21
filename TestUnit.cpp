#include "TestUnit.h"

using namespace std;

TestUnit::TestUnit()
{
    //ctor
}

TestUnit::~TestUnit()
{
    //dtor
}

void TestUnit::RunAllTest()
{
    cout << "Test OK!" << endl;

    string s ("subject");
    regex e ("(sub)(.*)");

    if (regex_match (s,e))
        cout << "string object matched\n";
}
