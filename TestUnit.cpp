#include "TestUnit.h"

TestUnit::TestUnit()
{
}

TestUnit::~TestUnit()
{
}

void TestUnit::RunAllTest()
{
    // ���� Int2List
    cout << "���� Int2List ..." << endl;
    Test_Int2List();

    // ���� Monster
    cout << "���� Monster ..." << endl;
    Test_Monster();

    // ���� SearchWord
    cout << "���� SearchWord ..." << endl;
    // �L�k��, �]���Ψ� worddata, ���Ψ� buildfilelist, ���ݧ�i ???
    //Test_SearchWord();

    // �e�{���G
    ShowTestResult();

}
// ----------------------------------------------------------------------------
void TestUnit::Test_Int2List()
{
    CInt2List * i2l = new CInt2List;
    i2l->Add(1,2);
    pair<int, int> *a = new pair<int, int>(3,4);
    i2l->Add(*a);

    AreEqual(i2l->Int2s[0].first, 1, "Int2List.first");
    AreEqual(i2l->Int2s[1].second, 4, "Int2List.second");

    CInt2List * i2l2 = new CInt2List;
    int is = i2l2->Int2s.size();
    AreEqual(is , 0, "Int2List �s�W�� size �O 0");

    i2l2->Copy(i2l);

    AreEqual(i2l2->Int2s[0].second, 2, "Copy �᪺ Int2List.first");
    AreEqual(i2l2->Int2s[1].first, 3, "Copy �᪺ Int2List.second");
    AreEqual((int)i2l2->Int2s.size(), 2, "Copy �᪺ Int2List size");

    i2l->Delete(0);
    AreEqual((int)i2l->Int2s.size(), 1, "Int2List �R���@���᪺ size");
    AreEqual(i2l->Int2s[0].first, 3, "�R���@���᪺ Int2List.first");
    i2l->Delete(1);
    AreEqual((int)i2l->Int2s.size(), 0, "Int2List �R���G���᪺ size");
    AreEqual((int)i2l->Int2s.size() , 0, "Int2List Delete �᪺ size �O 0");

    // ���� OrIt
    CInt2List * i2l3 = new CInt2List;
    i2l3->Add(1,2);
    i2l3->Add(15,16);
    i2l3->Add(35,36);

    CInt2List * i2l4 = new CInt2List;
    i2l4->Add(5,6);
    i2l4->Add(25,26);

    i2l3->OrIt(i2l4);

    AreEqual((int)i2l3->Int2s.size() , 5, "Int2List OrIt �᪺ size �O 5");
    AreEqual((int)i2l3->Int2s[1].first , 5, "Int2List OrIt �᪺�ĤG�� .first �O 5");
    AreEqual((int)i2l3->Int2s[4].second , 36, "Int2List OrIt �᪺�Ĥ��� .second �O 36");

    // ���� NearIT
    //             (50,52) , (100,102) ,                     (200,202)
    // (1,3)(45, 48),                  (110,113) , (140, 143)
    // ���G (45, 52)         (100,113)

    CInt2List * i2l5 = new CInt2List;
    i2l5->Add(50,52);
    i2l5->Add(100,102);
    i2l5->Add(200,202);

    CInt2List * i2l6 = new CInt2List;
    i2l6->Add(1,3);
    i2l6->Add(45, 48);
    i2l6->Add(110,113);
    i2l6->Add(140, 143);

    i2l5->NearIt(i2l6);

    AreEqual((int)i2l5->Int2s.size() , 2, "Int2List NearIT �᪺ size �O 2");
    AreEqual((int)i2l5->Int2s[0].first , 45, "Int2List NearIT �᪺�Ĥ@�� .first �O 45");
    AreEqual((int)i2l5->Int2s[1].second , 113, "Int2List NearIT �᪺�ĤG�� .second �O 113");


    // ���� BeforeIt
    //         (50,52) ,       (100,102)             (200,202)
    // (45, 48),      (60, 63)        (110,113) ,            (210, 213)
    // ���G (50, 63)           (100,113) ,           (200, 213)

    CInt2List * i2l7 = new CInt2List;
    i2l7->Add(50,52);
    i2l7->Add(100,102);
    i2l7->Add(200,202);

    CInt2List * i2l8 = new CInt2List;
    i2l8->Add(45, 48);
    i2l8->Add(60, 63);
    i2l8->Add(110,113);
    i2l8->Add(210, 213);

    i2l7->BeforeIt(i2l8);

    AreEqual((int)i2l7->Int2s.size() , 3, "Int2List BeforeIt �᪺ size �O 3");
    AreEqual((int)i2l7->Int2s[0].first , 50, "Int2List BeforeIt �᪺�Ĥ@�� .first �O 50");
    AreEqual((int)i2l7->Int2s[2].second , 213, "Int2List BeforeIt �᪺�ĤT�� .second �O 213");

    // ���� ExcludeIt
    //   (50,52) , (100,102)          (200,202),      (300, 303)
    // (49, 52),   (100, 104)   (198,201) , (201,203)
    // ���G (200,202), (300, 303)

    CInt2List * i2l9 = new CInt2List;
    i2l9->Add(50,52);
    i2l9->Add(100,102);
    i2l9->Add(200,202);
    i2l9->Add(300,303);

    CInt2List * i2la = new CInt2List;
    i2la->Add(49, 52);
    i2la->Add(100, 104);
    i2la->Add(198,201);
    i2la->Add(201,203);

    i2l9->ExcludeIt(i2la);

    AreEqual((int)i2l9->Int2s.size() , 2, "Int2List ExcludeIt �᪺ size �O 2");
    AreEqual((int)i2l9->Int2s[0].first , 200, "Int2List ExcludeIt �᪺�Ĥ@�� .first �O 200");
    AreEqual((int)i2l9->Int2s[1].second , 303, "Int2List ExcludeIt �᪺�ĤG�� .second �O 303");

    /*
    for(int i=0; i<i2l9->Int2s.size(); i++)
    {
        auto j = i2l9->Int2s[i];
        cout << j.first << "," << j.second << endl;
    }
    */


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
// �e�{�Ҧ����~������
void TestUnit::ShowTestResult()
{
    cout << "======================================" << endl;
    cout << "= ���\\������                         =" << endl;
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
    cout << "�����@�� " << iCount << " �����զ��\\!" << endl << endl;

    cout << "======================================" << endl;
    cout << "= ���Ѫ�����                         =" << endl;
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
    cout << "�����@�� " << iCount << " �����տ��~!" << endl;
}
// ----------------------------------------------------------------------------
void TestUnit::Test_Monster()
{
    /*
    // �n���Ť~���, ����·�, �ҥH���O��

    string sSentence = "( ��� * ( ��[��*��] ) + ( �� , �@�L ) )";
    string sPatten;

    string sSentence = "��� * ( ��[��*��] ) + ( �� , �@�L ) & �ؼ�";
    string sPatten;

    while (sSentence.length())
	{
		sPatten = SearchEngine->CutPatten(sSentence);
		cout << "\"" << sPatten << "\" : ";
		cout << "\"" << sSentence << "\"" << endl;
	}

    sSentence = "��� * ( ��[��*��] ) + ( �� , �@�L ) & �ؼ�";
    sPatten;

    while (sSentence.length())
	{
		sPatten = SearchEngine->CutPatten(sSentence);
		cout << "\"" << sPatten << "\" : ";
		cout << "\"" << sSentence << "\"" << endl;
	}

	sSentence = "( ��� * ( ��[��*��] ) + ( �� , �@�L ) & �ؼ� )";
    SearchEngine->AnalysisSentence(sSentence);
    cout << "OKSentence : " << SearchEngine->OKSentence << endl;
    for(int i=0; i<SearchEngine->SearchWordList.size(); i++)
    {
        cout << i << " : " << SearchEngine->SearchWordList[i] << endl;
    }

	*/
}
// ----------------------------------------------------------------------------
void TestUnit::Test_SearchWord()
{
    CSearchWord * Word = new CSearchWord("�����[��*��]��&CB01234;");

    AreEqual((int)Word->Tokens.size() , 6, "SearchWord Tokens �� size �O 6");
    AreEqual((string)Word->Tokens[3] , (string)"[��*��]", "SearchWord Tokens[3] �O [��*��]");
    AreEqual((string)Word->Tokens[5] , (string)"&CB01234;", "SearchWord Tokens[5] �O &CB01234;");
}
