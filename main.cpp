/*
    �����˯�
*/

#include "main.h"
using namespace std;

int main()
{
    char cInput;

    cout << "1.����{������ 2.��������˯� : ";
    cin >> cInput;

    if(cInput == '1')
    {
        cout << "����{�����դ�..." << endl;
        TestUnit myTest;
        myTest.RunAllTest();
    }
    else if(cInput =='2')
    {
        cout << "��������˯���..." << endl;
        RunFullTextSearch();
    }
    return 0;
}

// ��������˯�
void RunFullTextSearch()
{
    string sBuildList = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\buildlist.txt";
    string sWordIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\wordindex.ndx";
    string sMainIndex = "D:\\Data\\c\\_CodeBlocks\\Monster\\bin\\Debug\\main.ndx";

    CMonster * SearchEngine = new CMonster(sBuildList, sWordIndex, sMainIndex);	// �ŧi�����˯�
    /*
    SearchEngine->SearchWordList->Clear();                              // Search Engine �@�_��s
    bool bFindOK = SearchEngine->Find(SearchSentence,bHasRange);        // �}�l�j�M
    int iFoundCount = SearchEngine->FileFound->Total;
    */
}


