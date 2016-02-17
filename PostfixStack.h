//---------------------------------------------------------------------------
#ifndef PostfixStackH
#define PostfixStackH
//---------------------------------------------------------------------------
#include "Int2List.h"
#include "FileList.h"
//---------------------------------------------------------------------------
/*
	###################################
	# �m�߭p����B��
	#
	# ��h
	#
	#  �p�G�O�Ʀr, �p�G���B��Ÿ�, �B�h�Ƴ��@��, �N�B��, ���G���J query stack
	#  �p�G�O�Ʀr, �p�G���B��Ÿ�, �p�G�h�Ƥ��@��, ���J query stack
	#  �p�G�O�Ʀr, �S���B��Ÿ�, ���J query stack
	#
	#  �p�G�O�B��Ÿ�, ���J op stack , �B�O���ثe�h��
	#
	#  �p�G�O���A��, �ثe�h�� + 1
	#  �p�G�O�k�A��, �h�� - 1 , �åB�B��
	###################################
*/

class CPostfixStack
{
private:	// User declarations

	char OpStack[100];
	int LevelStack[100];
	int Level;
	int OpStackPoint;

	int QueryStackSize;		// query stack ���j�p, �]�N�O���X��, �]���Y pop �X��, �Ȯɤ��|�h delete ��.
	int QueryStackPoint;	// �ثe�i�H�ϥΨ쪺����

	void PushLeftBracket(void);
	void PushRightBracket(void);
	void PushOpStack(string sOp);
	void Run(void);						// �i����R

public:		// User declarations

	CInt2List * QueryStack[100];				// ???? �W�L 100 �ӫ���? �i�Ҽ{�� vector �ʺA���� ???
	void PushOp(string sOp);		// �ǤJ�@�����d�ߵ��G
	void PushQuery(CInt2List * FileFoundCount, string sSearchString);		// �ǤJ�@�����d�ߵ��G
    int GetResult(void);     // �Ǧ^��ƪ�����, ���O�Ǧ^���G, �Y���ѶǦ^ -1

	void Initial(void);		// ��Ȥ�
    CPostfixStack();		// �غc�禡
    ~CPostfixStack();		// �Ѻc�禡
};
//---------------------------------------------------------------------------
//extern TmyPostfixStack *PostfixStack;
//---------------------------------------------------------------------------
#endif
