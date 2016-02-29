//---------------------------------------------------------------------------
#include "FileList.h"
CFileList * BuildFileList;
//---------------------------------------------------------------------------
CFileList::CFileList(string sFileName)		// �غc�禡
{
	FileName = sFileName;
	Strings = 0;		// ��ȫŧi�� NULL
	Book = 0;           // ��ȫŧi�� NULL
	VolNum = 0;			// ��ȫŧi�� NULL
	SutraNum = 0;		// ��ȫŧi�� NULL
	JuanNum = 0;		// ��ȫŧi�� NULL
	SearchMe = 0;		// ��ȫŧi�� NULL
}
//---------------------------------------------------------------------------
CFileList::~CFileList(void)	// �Ѻc�禡
{
	if(Strings) delete[] Strings;
	if(Book   ) delete[] Book;
	if(VolNum ) delete[] VolNum;
	if(SutraNum) delete[] SutraNum;
	if(JuanNum) delete[] JuanNum;
	if(SearchMe) delete[] SearchMe;
}
//---------------------------------------------------------------------------
bool CFileList::Initial(void)	// ��Ȥ�
{
	ifstream fsIn;
	char buff[1024];
	string sLine;

	fsIn.open(FileName.c_str());
	if(!fsIn) return false;

	// �Ĥ@��, Ū�J buffer �ƶq

	fsIn.getline(buff,sizeof(buff));
	sLine = buff;
	FileCount = atoi(sLine.c_str())   ; // sLine.ToInt();		// ???? error check

	FileCountBit = FileCount / 32;
	if(FileCount % 32) FileCountBit++;

	// �}�Ҥ@�ӪŶ�

	Strings = new string[FileCount];
	Book = new string[FileCount];
	VolNum = new int[FileCount];
	SutraNum = new string[FileCount];
	JuanNum = new int[FileCount];
	SearchMe = new bool[FileCount];

	// �v�@Ū�J

	for(int i=0; i<FileCount; i++)   	// ???? error check
	{
		fsIn.getline(buff,sizeof(buff));
		Strings[i] = buff;

        // �]�� Book �i�঳�G��� (�转 SL), �ҥH���q�{������, ���U�����W���B�z

		// C:\cbeta\Normal\T01\T0001_001.txt
        // C:\cbeta\Normal\C001\C0001_001.txt  // �U�Ʀ��T�X��
        // C:\cbeta\Normal\DA01\DA0001_001.txt  // �ѦW���G�X��

		size_t iPos =  Strings[i].rfind("\\");
        string sFileName = Strings[i].substr(iPos+1);   // ���o�ɦW T0001_001.txt

		string sDirName = Strings[i].substr(0,iPos);      // �ѤU�ؿ��W C:\cbeta\Normal\T01

		size_t iPos2 =  sDirName.rfind("\\");
		string sVol = sDirName.substr(iPos2+1);    // sVol = T01 , C001, DA01 ... (�U�Ƹ��)

        Book[i] = GetAlphaFromHead(sVol);                       // ���o T
        string sVolNum = sVol.substr(Book[i].length());         // ���o "01"
        VolNum[i] = atoi(sVolNum.c_str());                      // ���o 1

		SutraNum[i] = sFileName.substr(Book[i].length(),5);
		JuanNum[i] = atoi(sFileName.substr(Book[i].length()+5,3).c_str());

/*
        // �o�@�q�O�� Delphi �� TRegExpr ����g��, �u��Φb BCB

    	TRegExpr * regex = new TRegExpr;
        regex->InputString = Strings[i];

        // �ɦW�O C:\cbeta\Normal\T01\T0001_001.txt
        // �ɦW�O C:\cbeta\Normal\C001\C0001_001.txt
        // �ɦW�O C:\cbeta\Normal\SL01\SL0001_001.txt
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
			SutraNum[i] = SutraNum[i].substr(0,4);		// �S���O��
		}
	}

	fsIn.close();
	return true;
}
//---------------------------------------------------------------------------
void CFileList::NoneSearch(void)	// ��Ȥ�
{
	for(int i=0; i<FileCount; i++)
	{
		SearchMe[i] = false;
	}
}
//---------------------------------------------------------------------------
// �˯��o�@�g���o�@�Ǩ�
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
// �˯��o�@�U���o�@�Ǹg
void CFileList::SearchThisVol(string sBook, int iVolNum, int iStartSutra, int iEndSutra)
{
	if(iEndSutra == 0)	iEndSutra = iStartSutra;
	if(iStartSutra == 0)	iEndSutra = 99999;

	for(int i=0; i<FileCount; i++)
	{
		int iSutraTmp;					// ���X�g��
        string sSutraTmp = SutraNum[i];

        if(sSutraTmp[1] == 'A' || sSutraTmp[1] == 'B') sSutraTmp[0] = '0';	// �Ȯɬ��ſ��øѮM, ������Q�˯� ????

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

