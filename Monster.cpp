//---------------------------------------------------------------------------

#include "Monster.h"
//---------------------------------------------------------------------------
// �غc�禡
CMonster::CMonster(string sFileListFileName,
					string sWordIndexFileName,
					string sMainIndexFileName)
{
	// ����k�s
	BuildFileList = 0;
	///WordIndex = 0;
	OpPatten = "()&,+*-";		// ��B�Ϊ� Patten

	FileListFileName = sFileListFileName;
	WordIndexFileName = sWordIndexFileName;
	MainIndexFileName = sMainIndexFileName;

	MaxSearchWordNum = 20;	// �˯������̦h�i�X�{���r���, "��� & ��ù�~" �N�� 2 �� , ���ӥi�H�Ҽ{�� vector �����ƶq ???
	swWord = new CSearchWord*[MaxSearchWordNum];

	for(int i=0; i<MaxSearchWordNum; i++)
	{
		swWord[i] = 0;		// �]�w���, �����k 0
	}

	// ���B�z build file list
	OpenBuildList();
	OpenWordIndex();
	OpenMainIndex();

	PostfixStack = new CPostfixStack;
	FileFound = new CIntList(BuildFileList->FileCount);	// �s��C�@�ɧ�쪺���G
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CMonster::~CMonster(void)
{
    /*
	if(BuildFileList) delete BuildFileList;
	if(WordIndex) delete WordIndex;
	if(PostfixStack) delete PostfixStack;
	if(SearchWordList) delete SearchWordList;
	if(FileFound) delete FileFound;
	if(swWord) delete[] swWord;
    */
}
//---------------------------------------------------------------------------
void CMonster::OpenBuildList(void)
{
	BuildFileList = new CFileList(FileListFileName);
	if(!BuildFileList->Initial())
    {	// ???? error check
        cout << "Open BuildList error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenWordIndex(void)
{
	WordIndex = new CWordIndex(WordIndexFileName);

	if(!WordIndex->Initial())
    {	// ???? error check
        cout << "Open WordIndex error!";
	}
}
//---------------------------------------------------------------------------
void CMonster::OpenMainIndex(void)
{
	MainIndex = new CMainIndex(MainIndexFileName);	// ???? error check
}
//---------------------------------------------------------------------------
// �M��@�Ӧr��, ���ӭn�Ǧ^�@���ɮצ�, ��ܭ����ɮצ�
bool CMonster::Find(string sSentence, bool bHasSearchRange)
{
    bool bResult = true;
	FileFound->ClearAll();		// �C�@�ɧ�쪺�ƶq�k 0
	SearchWordList.clear();
	OKSentence = "";			// �����k 0

	AnalysisSentence(sSentence);		// ���R, �ò��� OKSentence

	for(int i=0; i<BuildFileList->FileCount; i++)
	{
		int iResult;
		if(!bHasSearchRange || BuildFileList->SearchMe[i])
			iResult = FindOneFile(i);	// �j�M��@�ɮ�, �öǦ^���G
		else iResult = 0;

        if(iResult == -1)
        {
            bResult = false;        // �B�⥢�ѤF
            FileFound->Total = 0;   // ���S���
            break;
        }

		FileFound->Ints[i] = iResult;
		FileFound->Total = FileFound->Total + iResult;
	}

	// ������, �N swWord ����

	for(int i=0; i<MaxSearchWordNum; i++)
	{
		if(swWord[i]) delete swWord[i];
		swWord[i] = 0;
	}
    return bResult;
}

//---------------------------------------------------------------------------
// �����R�@�U�n�j�M���r��
//
// �p�G��J���r��O (��� & ����) | ���I
// �̫�|�ܦ�
// (S&S)|S		S ��ܤ@�Ӧr��, �s�b  SearchWordList ����
void CMonster::AnalysisSentence(string sSentence)
{
	SearchWordList.clear();
	string sPatten;

	// �ثe�ĴX�Ӧr��? �Ҧp (S&S)|S  (���&����)|���I  ����O�� 0 ��
	int iPattenNum = 0;

	while (sSentence.length())
	{
		sPatten = CutPatten(sSentence);
        // �R�����䪺�Ů�
        if(sSentence[0] == ' ') sSentence = sSentence.substr(sSentence.find_first_not_of(' '));

		if((sPatten.find_first_of(OpPatten) == 0) && (sPatten.length()==1))		// �p�G�O�B��Ÿ�����
		{
			//PostfixStack->PushOp(sPatten);
			OKSentence += sPatten;
		}
		else
		{
			// �B�z�@�Ӧr

			SearchWordList.push_back(sPatten);	// ���O���_��
			swWord[iPattenNum] = new CSearchWord(sPatten);	// �N���r�ǳƦn
			OKSentence += "S";
			iPattenNum++;
		}
	}
}

//---------------------------------------------------------------------------
string CMonster::CutPatten(string & sString)
{
	// �R�����䪺�Ů�
	if(sString[0] == ' ')
        sString = sString.substr(sString.find_first_not_of(' '));

	string sTmp = sString;

	/// OpPatten = "&,+*()-";
	if((sString.find_first_of(OpPatten) == 0) && ((sString.length() == 1)||(sString[1] == ' ')))		// �p�G�O�B��Ÿ�, �᭱�����O�Ů�ΨS�r�F
	{
		sString = sString.substr(1);
		return (sTmp.substr(0,1));
	}
	else
	{
		// ��X�U�@�� patten ����m�ε���

		size_t sPos = sString.find_first_of(OpPatten);
		while(sPos != std::string::npos)
        {
            if((sString.length() == sPos + 1)||(sString[sPos+1] == ' '))
            {
                // ���F
 				sString = sString.substr(sPos);
 				sTmp = sTmp.substr(0,sPos);

 				// ���� sTmp �k��Ů�
 				sTmp = sTmp.substr(0,sTmp.find_last_not_of(' ')+1);
				return (sTmp);
            }
            else
            {
                sPos = sString.find_first_of(OpPatten,sPos+1);
            }
        }

		sString = "";
		sTmp = sTmp.substr(0,sTmp.find_last_not_of(' ')+1);
		return (sTmp);
	}
}

//---------------------------------------------------------------------------
// �M��@�Ӧr��, ���ӭn�Ǧ^�@���ɮצ�, ��ܭ����ɮצ�
int CMonster::FindOneFile(int iFileNum)
{
	/*
	###################################
	# �m�߭p����B��
	#
	# ��h
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

	PostfixStack->Initial();
	string sPatten;
	string sOKSentence = OKSentence;	// �Ȧs���r��

	// �ثe�ĴX�Ӧr��? �Ҧp (S&S)|S  (���&����)|���I  ����O�� 0 ��
	int iPattenNum = 0;

	//while (sOKSentence.Length())
	for(int i=0; i<OKSentence.length(); i++)
	{
		sPatten = sOKSentence.substr(i,1);		// ���X patten
		if(sPatten.find_first_of(OpPatten) == 0)		// �p�G�O�B��Ÿ�����
		{
			PostfixStack->PushOp(sPatten);
		}
		else
		{
			// ???? �[�t����k, �p�G�O and �N�u��e�@�Ӧ����G��, �p�G�O or �N�u�d�e�@�ӬO�S��쪺
			// ???? �[�t����k, �p�G���έp����, �����N���, ����t�׷|���

			// �B�z�@�Ӧr

			sPatten = SearchWordList[iPattenNum];	// ���X�Y�@���r��
			swWord[iPattenNum]->Search(iFileNum);			// �u�b�Y���ɷj�M
			PostfixStack->PushQuery(swWord[iPattenNum]->FoundPos, sPatten);
			iPattenNum++;
		}
	}
	// ???? �o�O�ռ�, ���O����, �Ҧp ��� near ���� �i���O 1 ��
	// return (PostfixStack->QueryStack[0]->Int2s->Count);
    return (PostfixStack->GetResult());
}
