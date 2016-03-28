/* 使用方法

    CTinyIni * myIni = new CTinyIni("D:\\Data\\c\\_CodeBlocks\\tinyini\\bin\\Debug\\test.ini");

    string s = myIni->ReadString("string", "123");
    bool b = myIni->ReadBool("bool", true);
    int i = myIni->ReadInt("int", 123);

    cout << "string : " << s << endl;
    cout << "bool : " << b << endl;
    cout << "int : " << i << endl;
*/

#ifndef TINYINI_H
#define TINYINI_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class CTinyIni
{
    public:
    	string FileName;	// 檔名
    	map <string, string> Result;

        bool ReadBool(string sKey, bool bDefault);          // 讀取布林值
        int ReadInt(string sKey, int iDefault);             // 讀取整數
        string ReadString(string sKey, string sDefault);    // 讀取字串

    	CTinyIni(string sFileName);
    	~CTinyIni();

    protected:
    private:
        string Trim(string);    // 清掉頭尾的空白
};

#endif // TINYINI_H
