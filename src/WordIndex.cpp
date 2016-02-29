//---------------------------------------------------------------------------
#include "WordIndex.h"

CWordIndex * WordIndex;
//---------------------------------------------------------------------------
CWordIndex::CWordIndex(string sFileName)		// �غc�禡
{
	FileName = sFileName;
    WordOffset = 0;
}
//---------------------------------------------------------------------------
CWordIndex::~CWordIndex(void)	// �Ѻc�禡
{
	if(WordOffset) delete[] WordOffset;
}
//---------------------------------------------------------------------------
bool CWordIndex::Initial(void)	// ��Ȥ�
{
	ifstream fsIn;
	char buff[1024];
	string sLine;
	fsIn.open(FileName.c_str());
	if(!fsIn) return false;

	// �Ĥ@��, Ū�J buffer �ƶq

	fsIn.getline(buff,sizeof(buff));
	sLine = buff;
	WordCount = atoi(sLine.c_str());		// ???? error check

	// �}�Ҥ@�ӪŶ�

	//StringList = new TStringList();
	WordOffset = new int[WordCount];

	// �v�@Ū�J

	for(int i=0; i<WordCount; i++)   	// ???? error check
	{
		fsIn.getline(buff,sizeof(buff));
		//StringList->Add(buff);
		StringList.push_back(buff);
	}

	// StringList->Sort();
	for(int i=0; i<WordCount; i++)
	{
		sLine = StringList[i];
		int iPos = sLine.find("=");
        if(iPos == 0) iPos = 3;         // �b��媩�|�䤣�� = �Ÿ�.
		StringList[i] = sLine.substr(0,iPos);			// ���e�����r
		WordOffset[i] = atoi(sLine.substr(iPos+1).c_str());	// ���᭱�� Offset
	}
	fsIn.close();
	return true;
}
//---------------------------------------------------------------------------
int CWordIndex::GetOffset(string sToken)
{
    int iResult=-1;

    for(int i=0; i<StringList.size(); i++)
    {
        if(sToken == StringList[i])
            return i;
    }
	return -1;


    // return StringList->IndexOf(sToken);
	// ???? �o�̦��[�t���Ŷ�
	/*
	int iIndex;
	if (StringList->Find(sToken, iIndex))
		return iIndex;
	else
		return -1;
	*/
}
//---------------------------------------------------------------------------
