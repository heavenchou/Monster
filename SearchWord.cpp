
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

	// ???? 如果第一個字就沒有, 如何表示?
	for(int i=0; i<WordData[0].WordCount[iFileNum]; i++)	// 先用最笨的方法, 由第一個 token 的串列, 每一個都去試
	{
		iHead =  WordData->WordPos[iFileNum][i];	// 第一個的位置
		iLastHead = iHead;

		for(int i=0; i<Tokens.size(); i++)
		{
			lastK1[i] = 0;	// 初值化
	   //		lastK2[i] = 0;	// 初值化
		}

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
				// /* 第一種方法, 彈性較大的
				if(WordData[j].WordPos[iFileNum][k]>iLastHead)
				{
					iLastHead = WordData[j].WordPos[iFileNum][k];
					lastK1[j] = k;			// 先暫存至 lastK2;
					if(iLastHead - iHead + 1 > Tokens.size())		// 提前出局
                    {
						iFound = -1;
                    }
					else
					{
						iFound = 1;
					}
					break;
				}
				//--------  第一種方法, 彈性較大的 ---------- */

				/* 第二種方法, 較嚴格的
				if(WordData[j].WordPos[iFileNum][k]>iLastHead+1)		// 超過了
				{
					iFound = -1;		// 提前出局
					break;
				}
				else if(WordData[j].WordPos[iFileNum][k] == iLastHead+1)
				{
						iLastHead++;
 						iFound = 1;
						//lastK2[j] = k;			// 先暫存至 lastK2;
						break;
				}
				//--------  第二種方法, 較嚴格的 ---------- */
			}
			if (iFound <= 0)   	// 沒找到或提前出局
			{
				break;
			}
		}

		if (iFound == 0)   	// 沒找到
		{
			break;
		}

		if(iLastHead - iHead + 1 == Tokens.size())	// 找到一組了	???? 這個長度以後若有用到萬用字元, 可能會變
		{
			//FoundPos->Ints[iFileNum]++;		// 各檔案找到目標的筆數
			//FoundPos->Total++;				// 全部找到的字數
			FoundPos->Add(iHead,iLastHead);		// 找到一組
			//for(int i=0; i<Tokens->Count; i++)
			//	{
			//		lastK1[i] = lastK2[i];	// 加速下次找的速度
			//	}
		}
	}

	delete[] lastK1;
}
//---------------------------------------------------------------------------
