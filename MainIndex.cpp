//---------------------------------------------------------------------------
#include "MainIndex.h"

CMainIndex *MainIndex;
//---------------------------------------------------------------------------
CMainIndex::CMainIndex(string sFileName)
{
	FileName = sFileName;
	FileStream.open(FileName.c_str(),ios::binary);	// ???? check error

	FileStream.seekg(0,ios::end);
	Size = FileStream.tellg();
}
//---------------------------------------------------------------------------
CMainIndex::~CMainIndex(void)
{
	FileStream.close();
}
//---------------------------------------------------------------------------
