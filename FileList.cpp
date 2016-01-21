//---------------------------------------------------------------------------
#include "FileList.h"
CFileList * BuildFileList;
//---------------------------------------------------------------------------
CFileList::CFileList(string sFileName)		// 建構函式
{
	FileName = sFileName;
	Strings = 0;		// 初值宣告為 NULL
	Book = 0;           // 初值宣告為 NULL
	VolNum = 0;			// 初值宣告為 NULL
	SutraNum = 0;		// 初值宣告為 NULL
	JuanNum = 0;		// 初值宣告為 NULL
	SearchMe = 0;		// 初值宣告為 NULL
}
//---------------------------------------------------------------------------
CFileList::~CFileList(void)	// 解構函式
{
	if(Strings) delete[] Strings;
	if(Book   ) delete[] Book;
	if(VolNum ) delete[] VolNum;
	if(SutraNum) delete[] SutraNum;
	if(JuanNum) delete[] JuanNum;
	if(SearchMe) delete[] SearchMe;
}
//---------------------------------------------------------------------------
bool CFileList::Initial(void)	// 初值化
{
	ifstream fsIn;
	char buff[1024];
	string sLine;

	fsIn.open(FileName.c_str());
	if(!fsIn) return false;

	// 第一行, 讀入 buffer 數量

	fsIn.getline(buff,sizeof(buff));
	sLine = buff;
	FileCount = atoi(sLine.c_str())   ; // sLine.ToInt();		// ???? error check

	FileCountBit = FileCount / 32;
	if(FileCount % 32) FileCountBit++;

	// 開啟一個空間

	Strings = new string[FileCount];
	Book = new string[FileCount];
	VolNum = new int[FileCount];
	SutraNum = new string[FileCount];
	JuanNum = new int[FileCount];
	SearchMe = new bool[FileCount];

	// 逐一讀入

	for(int i=0; i<FileCount; i++)   	// ???? error check
	{
		fsIn.getline(buff,sizeof(buff));
		Strings[i] = buff;

        // 因為 Book 可能有二位數 (西蓮 SL), 所以此段程式取消, 底下的正規式處理

		// C:\cbeta\Normal\T01\T0001_001.txt
        // C:\cbeta\Normal\C001\C0001_001.txt  // 冊數有三碼的
        // C:\cbeta\Normal\DA01\DA0001_001.txt  // 書名有二碼的

		size_t iPos =  Strings[i].rfind("\\");
        string sFileName = Strings[i].substr(iPos+1);   // 取得檔名 T0001_001.txt

		string sDirName = Strings[i].substr(0,iPos);      // 剩下目錄名 C:\cbeta\Normal\T01

		size_t iPos2 =  sDirName.rfind("\\");
		string sVol = sDirName.substr(iPos2+1);    // sVol = T01 , C001, DA01 ... (冊數資料)

        Book[i] = GetAlphaFromHead(sVol);                       // 取得 T
        string sVolNum = sVol.substr(Book[i].length());         // 取得 "01"
        VolNum[i] = atoi(sVolNum.c_str());                      // 取得 1

		SutraNum[i] = sFileName.substr(Book[i].length(),5);
		JuanNum[i] = atoi(sFileName.substr(Book[i].length()+5,3).c_str());

/*
        // 這一段是用 Delphi 的 TRegExpr 物件寫的, 只能用在 BCB

    	TRegExpr * regex = new TRegExpr;
        regex->InputString = Strings[i];

        // 檔名是 C:\cbeta\Normal\T01\T0001_001.txt
        // 檔名是 C:\cbeta\Normal\C001\C0001_001.txt
        // 檔名是 C:\cbeta\Normal\SL01\SL0001_001.txt
	    regex->Expression = "[\\/\\\\]([a-zA-Z]+)(\\d+)[\\/\\\\]\\D+(.{5})(\\d{3})\\.";
    	if(regex->Exec())
    	{
            Book[i] = regex->Match[1];
            VolNum[i] = regex->Match[2].ToInt();
            SutraNum[i] = regex->Match[3];
		    JuanNum[i] = regex->Match[4].ToInt();
    	}
*/

		if(SutraNum[i][4] == '_')
		{
			SutraNum[i] = SutraNum[i].substr(0,4);		// 沒有別本
		}
	}

	fsIn.close();
	return true;
}
//---------------------------------------------------------------------------
void CFileList::NoneSearch(void)	// 初值化
{
	for(int i=0; i<FileCount; i++)
	{
		SearchMe[i] = false;
	}
}
//---------------------------------------------------------------------------
// 檢索這一經的這一些卷
void CFileList::SearchThisSutra(string sBook, string sSutraNum, int iStartJuan, int iEndJuan)
{
	if(iEndJuan == 0)	iEndJuan = iStartJuan;
	if(iStartJuan == 0)	iEndJuan = 99999;

	for(int i=0; i<FileCount; i++)
	{
		if(Book[i] == sBook && SutraNum[i] == sSutraNum && JuanNum[i] >= iStartJuan && JuanNum[i] <= iEndJuan)
		{
			SearchMe[i] = true;
		}
	}
}
//---------------------------------------------------------------------------
// 檢索這一冊的這一些經
void CFileList::SearchThisVol(string sBook, int iVolNum, int iStartSutra, int iEndSutra)
{
	if(iEndSutra == 0)	iEndSutra = iStartSutra;
	if(iStartSutra == 0)	iEndSutra = 99999;

	for(int i=0; i<FileCount; i++)
	{
		int iSutraTmp;					// 取出經號
        string sSutraTmp = SutraNum[i];

        if(sSutraTmp[1] == 'A' || sSutraTmp[1] == 'B') sSutraTmp[0] = '0';	// 暫時為嘉興藏解套, 讓它能被檢索 ????

		if(sSutraTmp.length() == 5)
			iSutraTmp = atoi(sSutraTmp.substr(0,4).c_str());
		else
			iSutraTmp = atoi(sSutraTmp.c_str());

		if(Book[i] == sBook && VolNum[i] == iVolNum && iSutraTmp >= iStartSutra && iSutraTmp <= iEndSutra)
		{
			SearchMe[i] = true;
		}
	}
}
//---------------------------------------------------------------------------

string CFileList::GetAlphaFromHead(string sInput)
{
    string sResult = "";
    for(int i=0; i<sInput.length(); i++)
    {
        if(sInput[i] > '9')
            sResult.push_back(sInput[i]);
    }
    return sResult;
}

