
#include "main.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    TestUnit *myTest = new TestUnit;

    myTest->RunAllTest();

    return 0;
}
