#include "TinyIni.h"

// 建構式
CTinyIni::CTinyIni(string sFileName)
{
	FileName = sFileName;
	ifstream FileStream;

	FileStream.open(FileName.c_str());
	if(!FileStream)
	{
        cout << "Open " << sFileName << " fail!" << endl;
        return;
	}

	char cBuff[256];
	while(FileStream.getline (cBuff,256))
    {
        string sBuff = cBuff;
        if(sBuff.back() == 0x0d) sBuff.pop_back();	// unix 下讀取 dos 格式的資料, 會有個 0x0d 在尾端
        if(sBuff[0] != '#')
        {
            // 非註解才處理

            size_t iPos = sBuff.find_first_of('=');     // key = value
            if(iPos != string::npos)
            {
                string sKey = sBuff.substr(0,iPos);     // key
                string sValue = sBuff.substr(iPos+1);    // value

                sKey = Trim(sKey);
                sValue = Trim(sValue);

                Result.insert ( pair<string,string>(sKey, sValue) );
                //cout << "find : " << sKey << " , " << sValue << endl;
            }
        }
    }
}
//-----------------------------------------------------------------------------
// 讀取布林值
// 空字串,  0 , false, no 會傳回 false ; 反之 1, true, yes 會傳回 true;
bool CTinyIni::ReadBool(string sKey, bool bDefault)
{
    string sValue;
    if(Result.count(sKey))
        sValue = Result[sKey];
    else
        return bDefault;

    string slValue; // 存放小寫的 sValue
    slValue.resize(sValue.size());  // 不能是空的, 不然會有問題.

    transform(sValue.begin(), sValue.end(), slValue.begin(), ::tolower);

    if(slValue == "" || slValue == "0" || slValue == "false" || slValue == "no")
        return false;
    else if(slValue == "1" || slValue == "true" || slValue == "yes")
        return true;
    else
        return bDefault;
}
//-----------------------------------------------------------------------------
// 讀取整數
int CTinyIni::ReadInt(string sKey, int iDefault)
{
    string sValue;
    if(Result.count(sKey))
        sValue = Result[sKey];
    else
        return iDefault;

    const char * p;
    char * e;   // 用來指向第一個無法處理成數字的位置

    p = sValue.c_str();
    int iValue = strtol(p,&e,10);

    if(*e != 0 || sValue == "")  // 表示有些字元無法轉成數字, 就傳回預設值
        return iDefault;
    else
        return iValue;
}
//-----------------------------------------------------------------------------
// 讀取字串
string CTinyIni::ReadString(string sKey, string sDefault)
{
    if(Result.count(sKey))
        return Result[sKey];
    else
        return sDefault;
}
//-----------------------------------------------------------------------------
// 清掉頭尾的空白
string CTinyIni::Trim(string sStr)
{
    if(sStr.empty()) return "";

    if(sStr[0] == ' ')
    {
        size_t startpos = sStr.find_first_not_of(" ");
        if( startpos != string::npos)
        {
            sStr = sStr.substr(startpos);
        }
    }

    if(sStr.back() == ' ')
    {

        size_t endpos = sStr.find_last_not_of(" ");
        if( endpos != string::npos)
        {
            sStr = sStr.substr( 0, endpos+1 );
        }
    }

    return sStr;
}
//-----------------------------------------------------------------------------
