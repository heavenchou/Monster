/*
    �����˯�
*/

#include "main.h"
using namespace std;

int main()
{

#ifdef DEBUG
    cout << "DEBUGing... DEBUGing... DEBUGing..." << endl;
#endif // DEBUG

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
    string sBuildList = "./buildlist.txt";
    string sWordIndex = "./wordindex.ndx";
    string sMainIndex = "./main.ndx";

    CMonster * SearchEngine = new CMonster(sBuildList, sWordIndex, sMainIndex);	// �ŧi�����˯�

    SearchEngine->SearchWordList.clear();                              // Search Engine �@�_��s
    ShowTestResult(SearchEngine, "�@�L", 3645);
    ShowTestResult(SearchEngine, "���� + ù�~", 374);
    ShowTestResult(SearchEngine, "�p�� & �@�L", 10850);
    ShowTestResult(SearchEngine, "�p�� * �@�L", 488);
    ShowTestResult(SearchEngine, "�٧Q�� , ����", 3998);
    ShowTestResult(SearchEngine, "�P����", 0);
    ShowTestResult(SearchEngine, "ı?�k�v", 123);
    ShowTestResult(SearchEngine, "ı?�k�v - ı���k�v", 4);
    ShowTestResult(SearchEngine, "( �٧Q�� & ���� ) + ����", 459);
}

// ���յ��G
void ShowTestResult(CMonster * SearchEngine, string sSearchStr, int iResult)
{
    bool bHasRange = false;         // �����˯�
    bool bFindOK = SearchEngine->Find(sSearchStr,bHasRange);        // �}�l�j�M
    cout << "find " << sSearchStr << " : " << SearchEngine->FileFound->Total;
    if(SearchEngine->FileFound->Total == iResult)
        cout << " (OK)" << endl;
    else
        cout << " (XXXXXXXXXXXX)" << endl;
}

