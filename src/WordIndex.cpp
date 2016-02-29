//---------------------------------------------------------------------------
#include "WordIndex.h"

CWordIndex * WordIndex;
//---------------------------------------------------------------------------
CWordIndex::CWordIndex(string sFileName)		// 建構函式
{
	FileName = sFileName;
    WordOffset = 0;
}
//---------------------------------------------------------------------------
CWordIndex::~CWordIndex(void)	// 解構函式
{
	if(WordOffset) delete[] WordOffset;
}
//---------------------------------------------------------------------------
bool CWordIndex::Initial(void)	// 初值化
{
	ifstream fsIn;
	char buff[1024];
	string sLine;
	fsIn.open(FileName.c_str());
	if(!fsIn) return false;

	// 第一行, 讀入 buffer 數量

	fsIn.getline(buff,sizeof(buff));
	sLine = buff;
	WordCount = atoi(sLine.c_str());		// ???? error check

	// 開啟一個空間

	//StringList = new TStringList();
	WordOffset = new int[WordCount];

	// 逐一讀入

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
        if(iPos == 0) iPos = 3;         // 在日文版會找不到 = 符號.
		StringList[i] = sLine.substr(0,iPos);			// 取前面的字
		WordOffset[i] = atoi(sLine.substr(iPos+1).c_str());	// 取後面的 Offset
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
	// ???? 這裡有加速的空間
	/*
	int iIndex;
	if (StringList->Find(sToken, iIndex))
		return iIndex;
	else
		return -1;
	*/
}
//---------------------------------------------------------------------------
