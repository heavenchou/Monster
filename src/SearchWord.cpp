
#include "SearchWord.h"
//---------------------------------------------------------------------------
// 建構函式
CSearchWord::CSearchWord(string sWord)
{
	Word = sWord;
	WordData = 0;		// 初值宣告為 0
	FoundPos = 0;		// 各檔找到的數量
	FoundPos = new CInt2List();

	ParseToken();	  	// 先將要搜尋的字串拆成一個一個的 token
	CreatTokenSpace();	// 配置每一個 token 的空間
}
//---------------------------------------------------------------------------
// 解構函式
CSearchWord::~CSearchWord(void)
{
	if(WordData) delete[] WordData;
	if(FoundPos) delete FoundPos;
}
//---------------------------------------------------------------------------
// 分析程式
void CSearchWord::ParseToken(void)
{
	// 先拆解出 Token
	string sTmp = Word;
	while(sTmp.length()>0)
	{
		if((sTmp[0] == '&') && (sTmp.find(';')))			// ???? 暫時當成組字式
		{
			size_t iPos = sTmp.find(';');
			Tokens.push_back(sTmp.substr(0,iPos+1));
			sTmp = sTmp.substr(iPos+1);
		}
		else if(sTmp[0] == '[')			// ???? 暫時當成組字式
		{
			size_t iPos = sTmp.find("]");
			Tokens.push_back(sTmp.substr(0,iPos+1));
			sTmp = sTmp.substr(iPos+1);
		}
		/* 這是在 big5 用的, 在 utf8 會失效

		else if((unsigned char)sTmp[0] >= 128)		// 中文字, 不能用 IsLeadByte(1) , 在英文版會失效
		{
			Tokens.push_back(sTmp.substr(0,2));
			sTmp = sTmp.substr(2);
		}
		else
		{
			Tokens.push_back(sTmp.substr(0,1));
			sTmp = sTmp.substr(1);
		}
		*/

		// utf8 版, 若某字前 5 個 bit 是 11110 表示此字有 4 個字, 若前 4 個 bit 是 1110 , 表示此字有 3 個字...

		else if(((unsigned char)sTmp[0] & 0xFE) == 0xFC) // 0xFE = 1111 1110
		{
		    Tokens.push_back(sTmp.substr(0,6));
		    sTmp = sTmp.substr(6);
		}
		else if(((unsigned char)sTmp[0] & 0xFC) == 0xF8) // 0xFC = 1111 1100
		{
		    Tokens.push_back(sTmp.substr(0,5));
		    sTmp = sTmp.substr(5);
		}
		else if(((unsigned char)sTmp[0] & 0xF8) == 0xF0) // 0xF8 = 1111 1000
		{
		    Tokens.push_back(sTmp.substr(0,4));
		    sTmp = sTmp.substr(4);
		}
		else if(((unsigned char)sTmp[0] & 0xF0) == 0xE0) // 0xE0 = 1111 0000
		{
		    Tokens.push_back(sTmp.substr(0,3));
		    sTmp = sTmp.substr(3);
		}
		else if(((unsigned char)sTmp[0] & 0xE0) == 0xC0) // 0xE0 = 1110 0000
		{
		    Tokens.push_back(sTmp.substr(0,2));
		    sTmp = sTmp.substr(2);
		}
		else
		{
		    Tokens.push_back(sTmp.substr(0,1));
		    sTmp = sTmp.substr(1);
		}

	}
}

//---------------------------------------------------------------------------
// 配置每一個 token 的空間
void CSearchWord::CreatTokenSpace(void)
{
	int iCount = Tokens.size();
	int iBufferSize;

	if(WordData) delete[] WordData;
	WordData = new CWordData[iCount];   // 每一個字都開出空間來

	for (int i=0; i<iCount; i++)
	{
		int iIndex = WordIndex->GetOffset(Tokens[i]);

		if(iIndex >= 0)		// 此字有在索引檔中
		{
			int iOffset = WordIndex->WordOffset[iIndex];
			if(iIndex == WordIndex->WordCount - 1)					// 最後一筆
				iBufferSize = MainIndex->Size - iOffset;
			else
				iBufferSize = WordIndex->WordOffset[iIndex+1]-iOffset;	// ???? 有待檢查最後一筆
			(WordData+i)->Initial(iOffset, iBufferSize);
		}
		else 			// 此字不在索引檔中
		{
			(WordData+i)->ZeroIt();		// 建一個全部都是 0 的 worddata
		}
	}
}
//---------------------------------------------------------------------------
// 搜尋某個檔案檔案
void CSearchWord::Search(int iFileNum)
{
	int iFound = 0;						// 判斷有沒有找到資料
	FoundPos->ClearAll();
	lastK1 = new int[Tokens.size()];
	int iHead;	// 第一個的位置
	int iLastHead;

	/*
	# 由主索引檔讀入資料
	# 找第一個字
	# 找第二個字
	# ...全找到了
	# 檢查合不合格?
	# 繼續.....
	*/

	for(int i=0; i<Tokens.size(); i++)
	{
		lastK1[i] = 0;	// 初值化
	}

	// ???? 如果第一個字就沒有, 如何表示?
	for(int i=0; i<WordData[0].WordCount[iFileNum]; i++)	// 先用最笨的方法, 由第一個 token 的串列, 每一個都去試
	{
		iHead =  WordData->WordPos[iFileNum][i];	// 第一個的位置
		iLastHead = iHead;

		int iFound = 1; 		// 如果只找一個字, 就是找到了.
		for(int j=1; j<Tokens.size(); j++)
		{
			if(Tokens[j] == "?")	// 萬用字元
			{
				iLastHead++;
				continue;
			}

			iFound = 0;
			for(int k=lastK1[j]; k<WordData[j].WordCount[iFileNum]; k++)
			{
				if(WordData[j].WordPos[iFileNum][k] <= iLastHead)
				{
				}
				else if(WordData[j].WordPos[iFileNum][k] > iLastHead+1)        // 超過了
				{
					iFound = -1;        // 提前出局
					lastK1[j] = k;
					break;
				}
				else if(WordData[j].WordPos[iFileNum][k] == iLastHead+1)
				{
					iLastHead += 1;
					iFound = 1;
					lastK1[j] = k;            // 先暫存至 lastK1
					break;
				}
			}
			if (iFound == 0)   	// 沒找到
			{
				return;
			}
			else if (iFound < 0)   // 提前出局
			{
				break;
			}
		}

		if(iFound == 1)	// 找到一組了	???? 這個長度以後若有用到萬用字元, 可能會變
		{
			FoundPos->Add(iHead,iLastHead);		// 找到一組
		}
	}

	delete[] lastK1;
}
//---------------------------------------------------------------------------
