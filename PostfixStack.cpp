//---------------------------------------------------------------------------
//#include <vcl\vcl.h>
#pragma hdrstop

#include "PostfixStack.h"
//---------------------------------------------------------------------------
// �غc�禡
CPostfixStack::CPostfixStack()
{
	Initial();
	QueryStackSize = 0;
	for(int i=0; i<100; i++)
		QueryStack[i] = 0;
}
//---------------------------------------------------------------------------
CPostfixStack::~CPostfixStack(void)	// �Ѻc�禡
{
	for(int i=0; i<QueryStackSize; i++)
		if(QueryStack[i]) delete QueryStack[i];
}
//---------------------------------------------------------------------------
void CPostfixStack::Initial()
{
	// QueryStack = 0;
	Level = 0;
	OpStackPoint = 0;
	QueryStackPoint = 0;
}
//---------------------------------------------------------------------------
// �ǤJ�@�ӹB��Ÿ�
void CPostfixStack::PushOp(string sOp)
{
	if(sOp == "(")
	{
		PushLeftBracket();
	}
	else if(sOp == ")")
	{
		PushRightBracket();
	}
	else
	{
		PushOpStack(sOp);
	}
}
//---------------------------------------------------------------------------
// �ǤJ�@�Ӥ��R�n��
void CPostfixStack::PushQuery(CInt2List * FoundPos, string sSearchString)
{
	//  �p�G�O�Ʀr, �p�G���B��Ÿ�, �B�h�Ƴ��@��, �N�B��, ���G���J query stack
	//  �p�G�O�Ʀr, �p�G���B��Ÿ�, �p�G�h�Ƥ��@��, ���J query stack
	//  �p�G�O�Ʀr, �S���B��Ÿ�, ���J query stack

	// ���ˬd���S���Ŷ��i�H��

	if(QueryStackSize == QueryStackPoint)	// �Ŷ�����, �n creat �@�ӷs��
	{
		QueryStack[QueryStackPoint] = new CInt2List();
		QueryStackSize++;
	}

	QueryStack[QueryStackPoint]->Copy(FoundPos);
	QueryStack[QueryStackPoint]->SearchString = sSearchString;
	QueryStackPoint++;
	Run();
}
//---------------------------------------------------------------------------
// �B�z���A��
inline void CPostfixStack::PushLeftBracket(void)
{
	// �p�G�O���A��, �ثe�h�� + 1
	Level++;
}
//---------------------------------------------------------------------------
// �B�z�k�A��
inline void CPostfixStack::PushRightBracket(void)
{
	// �p�G�O�k�A��, �h�� - 1 , �åB�B��
	Level--;
	Run();
}
//---------------------------------------------------------------------------
// ���J�B��Ÿ�
inline void CPostfixStack::PushOpStack(string sOp)
{
	// �p�G�O�B��Ÿ�, ���J op stack , �B�O���ثe�h��
	OpStack[OpStackPoint] = sOp[1];
	LevelStack[OpStackPoint] = Level;
	OpStackPoint++;
}
//---------------------------------------------------------------------------
// ����B��
void CPostfixStack::Run(void)
{
	if(OpStackPoint <= 0) return;						// �S������B��Ÿ�, �ҥH���}
	if(QueryStackPoint < 2) return;						// �����D, ���i��p��2
	if(Level != LevelStack[OpStackPoint-1]) return;		// �h�Ť���, ����B��

	// ���X�B��Ÿ�

	OpStackPoint--;
	char cNowOp = OpStack[OpStackPoint];

	switch (cNowOp)
	{
		case '&':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->AndIt(QueryStack[QueryStackPoint]);
			break;
		case ',':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->OrIt(QueryStack[QueryStackPoint]);
			break;
			/**
		case '+':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->NearIt(QueryStack[QueryStackPoint]);
			break;
		case '*':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->BeforeIt(QueryStack[QueryStackPoint]);
			break;
		case '-':
			QueryStackPoint--;
			QueryStack[QueryStackPoint-1]->ExcludeIt(QueryStack[QueryStackPoint]);
			break;
			*/
	}
}
//---------------------------------------------------------------------------
// �Ǧ^��ƪ�����, ���O�Ǧ^���G, �Y���ѶǦ^ -1
// �]���{���n�Ǧ^����, �����ɭp��|����, �]���ϥΪ̥ΤF���A���B��r��,
// �ҥH�b�ˬd��Y���X��, �N�Ǧ^ -1
int CPostfixStack::GetResult(void)
{
    // �ˬd���зǦp�U:
    //
    // 1.�B��Ÿ����| op stack ������ 0
    // 2.�B����| query stack �u���@��
    // 3.�h�ƥ����� 0

    // 1.
    if(OpStackPoint !=0) return -1;
    // 2.
    if(QueryStackPoint !=1) return -1;
    // 3.
    if(Level !=0) return -1;

    // �Ǧ^�зǪ����G
    return (QueryStack[0]->Int2s.size());
}
//---------------------------------------------------------------------------
