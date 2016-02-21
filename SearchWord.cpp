
#include "SearchWord.h"
//---------------------------------------------------------------------------
// �غc�禡
CSearchWord::CSearchWord(string sWord)
{
	Word = sWord;
	WordData = 0;		// ��ȫŧi�� 0
	FoundPos = 0;		// �U�ɧ�쪺�ƶq
	FoundPos = new CInt2List();

	ParseToken();	  	// ���N�n�j�M���r���@�Ӥ@�Ӫ� token
	CreatTokenSpace();	// �t�m�C�@�� token ���Ŷ�
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CSearchWord::~CSearchWord(void)
{
	if(WordData) delete[] WordData;
	if(FoundPos) delete FoundPos;
}
//---------------------------------------------------------------------------
// ���R�{��
void CSearchWord::ParseToken(void)
{
	// ����ѥX Token
	string sTmp = Word;
	while(sTmp.length()>0)
	{
		if((sTmp[0] == '&') && (sTmp.find(';')))			// ???? �Ȯɷ��զr��
		{
			size_t iPos = sTmp.find(';');
			Tokens.push_back(sTmp.substr(0,iPos+1));
			sTmp = sTmp.substr(iPos+1);
		}
		else if(sTmp[0] == '[')			// ???? �Ȯɷ��զr��
		{
			size_t iPos = sTmp.find("]");
			Tokens.push_back(sTmp.substr(0,iPos+1));
			sTmp = sTmp.substr(iPos+1);
		}
		else if((unsigned char)sTmp[0] >= 128)		// ����r, ����� IsLeadByte(1) , �b�^�媩�|����
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
// �t�m�C�@�� token ���Ŷ�
void CSearchWord::CreatTokenSpace(void)
{
	int iCount = Tokens.size();
	int iBufferSize;

	if(WordData) delete[] WordData;
	WordData = new CWordData[iCount];   // �C�@�Ӧr���}�X�Ŷ���

	for (int i=0; i<iCount; i++)
	{
		int iIndex = WordIndex->GetOffset(Tokens[i]);

		if(iIndex >= 0)		// ���r���b�����ɤ�
		{
			int iOffset = WordIndex->WordOffset[iIndex];
			if(iIndex == WordIndex->WordCount - 1)					// �̫�@��
				iBufferSize = MainIndex->Size - iOffset;
			else
				iBufferSize = WordIndex->WordOffset[iIndex+1]-iOffset;	// ???? �����ˬd�̫�@��
			(WordData+i)->Initial(iOffset, iBufferSize);
		}
		else 			// ���r���b�����ɤ�
		{
			(WordData+i)->ZeroIt();		// �ؤ@�ӥ������O 0 �� worddata
		}
	}
}
//---------------------------------------------------------------------------
// �j�M�Y���ɮ��ɮ�
void CSearchWord::Search(int iFileNum)
{
	int iFound = 0;						// �P�_���S�������
	FoundPos->ClearAll();
	lastK1 = new int[Tokens.size()];
	int iHead;	// �Ĥ@�Ӫ���m
	int iLastHead;

	/*
	# �ѥD������Ū�J���
	# ��Ĥ@�Ӧr
	# ��ĤG�Ӧr
	# ...�����F
	# �ˬd�X���X��?
	# �~��.....
	*/

	// ???? �p�G�Ĥ@�Ӧr�N�S��, �p����?
	for(int i=0; i<WordData[0].WordCount[iFileNum]; i++)	// ���γ̲ª���k, �ѲĤ@�� token ����C, �C�@�ӳ��h��
	{
		iHead =  WordData->WordPos[iFileNum][i];	// �Ĥ@�Ӫ���m
		iLastHead = iHead;

		for(int i=0; i<Tokens.size(); i++)
		{
			lastK1[i] = 0;	// ��Ȥ�
	   //		lastK2[i] = 0;	// ��Ȥ�
		}

		int iFound = 1; 		// �p�G�u��@�Ӧr, �N�O���F.
		for(int j=1; j<Tokens.size(); j++)
		{
			if(Tokens[j] == "?")	// �U�Φr��
			{
				iLastHead++;
				continue;
			}

			iFound = 0;
			for(int k=lastK1[j]; k<WordData[j].WordCount[iFileNum]; k++)
			{
				// /* �Ĥ@�ؤ�k, �u�ʸ��j��
				if(WordData[j].WordPos[iFileNum][k]>iLastHead)
				{
					iLastHead = WordData[j].WordPos[iFileNum][k];
					lastK1[j] = k;			// ���Ȧs�� lastK2;
					if(iLastHead - iHead + 1 > Tokens.size())		// ���e�X��
                    {
						iFound = -1;
                    }
					else
					{
						iFound = 1;
					}
					break;
				}
				//--------  �Ĥ@�ؤ�k, �u�ʸ��j�� ---------- */

				/* �ĤG�ؤ�k, ���Y�檺
				if(WordData[j].WordPos[iFileNum][k]>iLastHead+1)		// �W�L�F
				{
					iFound = -1;		// ���e�X��
					break;
				}
				else if(WordData[j].WordPos[iFileNum][k] == iLastHead+1)
				{
						iLastHead++;
 						iFound = 1;
						//lastK2[j] = k;			// ���Ȧs�� lastK2;
						break;
				}
				//--------  �ĤG�ؤ�k, ���Y�檺 ---------- */
			}
			if (iFound <= 0)   	// �S���δ��e�X��
			{
				break;
			}
		}

		if (iFound == 0)   	// �S���
		{
			break;
		}

		if(iLastHead - iHead + 1 == Tokens.size())	// ���@�դF	???? �o�Ӫ��ץH��Y���Ψ�U�Φr��, �i��|��
		{
			//FoundPos->Ints[iFileNum]++;		// �U�ɮק��ؼЪ�����
			//FoundPos->Total++;				// ������쪺�r��
			FoundPos->Add(iHead,iLastHead);		// ���@��
			//for(int i=0; i<Tokens->Count; i++)
			//	{
			//		lastK1[i] = lastK2[i];	// �[�t�U���䪺�t��
			//	}
		}
	}

	delete[] lastK1;
}
//---------------------------------------------------------------------------
