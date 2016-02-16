//---------------------------------------------------------------------------
#include "Int2List.h"
//#include "Option.h"
//---------------------------------------------------------------------------
// �غc�禡
CInt2List::CInt2List()
{
	//FileCount = iFileCount;
	//Total = 0;
	//Ints = 0;
	//Ints = new int[FileCount];

    SearchString = "";        // �j�M���r��, �@�}�l�i��O "���" �o�ص�, �b�B���i���ܦ� "(���+ù�~)" �o�عB�⵲�G. �o���O�� ! �B��]�p��

	///Int2s = new TList;
}
//---------------------------------------------------------------------------
// �Ѻc�禡
CInt2List::~CInt2List(void)
{
	ClearAll();

	///if(Int2s) delete Int2s;
}
//---------------------------------------------------------------------------
// �����M��
inline void CInt2List::ClearAll(void)
{
	Int2s.clear();
}
//---------------------------------------------------------------------------
// �[�J�Y�@��
void CInt2List::Add(pair <int, int> p)
{
	//TPoint * tpNew = new TPoint(tpPtr->x, tpPtr->y);
	Int2s.push_back(p);
}
//---------------------------------------------------------------------------
// �[�J�Y�@��
void CInt2List::Add(int x, int y)
{
	Int2s.push_back(pair<int,int>(x,y));
}
//---------------------------------------------------------------------------
// �R���Y�@��
void CInt2List::Delete(int iNum)
{
	Int2s.erase(Int2s.begin()+iNum-1);
}
//---------------------------------------------------------------------------
// �B��l�h�� =
void CInt2List::operator=(CInt2List * ilTarget)
{
    Copy(ilTarget);
}
//---------------------------------------------------------------------------
// �N��� copy �L��
void CInt2List::Copy(CInt2List * ilTarget)
{
    Int2s = ilTarget->Int2s;
    // SearchString = ilTarget->SearchString;  copy �٬O���n�h��j�M�r�����n
}
//---------------------------------------------------------------------------
// �B��l�h��
void CInt2List::operator&=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// �Y�G�̳������, �N�G�̦X��
void CInt2List::AndIt(CInt2List * ilTarget)
{
	// �u�n���@�ӤH�O 0 , �N�����U�h�F

    SearchString = "(" + SearchString + "&" + ilTarget->SearchString + ")";     // �ܦ� "(word1&word2)"
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
	}
	else	//���U�ӴN�n�N�G�H�X�֤F
	{
		//OrIt(ilTarget);
    }
}
//---------------------------------------------------------------------------
// �B��l�h��
void CInt2List::operator|=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// �G�̦X��
void CInt2List::OrIt(CInt2List * ilTarget)
{
	int iIndex = 0;		// ���ʤ�������
	//TPoint * tpPtr1, *tpPtr2;
	pair<int, int> tpPtr1, tpPtr2;

    SearchString = "(" + SearchString + "," + ilTarget->SearchString + ")";     // �ܦ� "(word1,word2)"

	if(Int2s.size() == 0)	// �ڦۤv�S�����
	{
		Copy(ilTarget);
		return;
	}

	if(ilTarget->Int2s.size() == 0)		// ���S�����
    {
		return;
    }

    /*
    // �o�@�q���I�_��, �����򤣯�令���U����?... ��ӨS���F, �]���̫�O�� Insert, ���O���J�b�̫�
	for(int i=0; i<ilTarget.Int2s.size; i++)
	{
		tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[i];
		while(tpPtr2->x >= tpPtr1->x)
		{
			iIndex++;
			if(iIndex == Int2s.size) break;
			tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		}
		TPoint * tpNew = new TPoint(tpPtr2->x, tpPtr2->y);	// �o�̪�F�@�ѥb�h�� bug 10/19 '03
		Int2s->Insert(iIndex,tpNew);
	}
	*/

    // ���M vector �]�i�H���J, ���Ĳv���n, �ҥH��Ψ�L��k, ��ʱN�G�� vector �X�֦��@��

    vector <pair <int,int> > pairTmp;

	for(int i=0; i<ilTarget->Int2s.size(); i++)
	{
		tpPtr1 = Int2s[iIndex];
		tpPtr2 = ilTarget->Int2s[i];
		if(iIndex < Int2s.size())
        {
            while(tpPtr2.first >= tpPtr1.first)
            {
                pairTmp.push_back(tpPtr1);

                iIndex++;
                tpPtr1 = Int2s[iIndex];
                if(iIndex == Int2s.size()) break;
            }
        }
        pairTmp.push_back(tpPtr2);
	}

    // �i���٦��٨S�B�z����, �n�~��B�z
    while(iIndex < Int2s.size())
    {
        pairTmp.push_back(tpPtr1);
        iIndex++;
        tpPtr1 = Int2s[iIndex];
    }

	Int2s = pairTmp;
}

//---------------------------------------------------------------------------
// �Y�G�̾a��ܬY�@�ӵ{��, �h�ܦ��@�ӽd��
void CInt2List::NearIt(CInt2List * ilTarget)
{

	NearNum = 30; //fmOption->Setting->NearNum;			// Near �B�⪺�d��     ???? �n�ΨϥΪ̿�J
    string sSearchString = "(" + SearchString + "+" + ilTarget->SearchString + ")";     // �ܦ� "(word1+word2)"


	// �S��ƴN����
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];
		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

			// ���@��
			if((tpPtr2.first - tpPtr1.second <= NearNum) && (tpPtr1.first - tpPtr2.second <= NearNum))
			{
				pair <int,int> tpNew = pair <int,int>(min(tpPtr1.first, tpPtr2.first), max(tpPtr1.second, tpPtr2.second));
				pairTmp.push_back(tpNew);
			}
			else
				if (tpPtr2.first - tpPtr1.second > NearNum) break;	// �䤣��F, ���U�@��
		}
	}

	Int2s = pairTmp;
    SearchString = sSearchString;
}

//---------------------------------------------------------------------------
// �P Near , ���L�u��b��᭱, �]�N�O�����Ǫ�
void CInt2List::BeforeIt(CInt2List * ilTarget)
{
	BeforeNum = 30; //fmOption->Setting->BeforeNum;		// Before �B�⪺�d��   ???? �n�ΨϥΪ̿�J
    string sSearchString = "(" + SearchString + "*" + ilTarget->SearchString + ")";     // �ܦ� "(word1*word2)"

	// �S��ƴN����
	if(Int2s.size() ==0 || ilTarget->Int2s.size() == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];
		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

			// ���@��
			if((tpPtr2.first - tpPtr1.first > 0 ) && (tpPtr2.first - tpPtr1.second <= BeforeNum))
			{
				pair <int,int> tpNew = pair <int,int>(tpPtr1.first, max(tpPtr1.second, tpPtr2.second));
				pairTmp.push_back(tpNew);
			}
			else
				if (tpPtr2.first - tpPtr1.second > BeforeNum) break;	// �䤣��F, ���U�@��
		}
	}

	Int2s = pairTmp;
    SearchString = sSearchString;
}
//---------------------------------------------------------------------------
// �ư��Y�@�ӵ�, �Ҧp  �٧Q!�٧Q�� ��ܥu�n��٧Q, �����n���٧Q��

void CInt2List::ExcludeIt(CInt2List * ilTarget)
{
    // ���k :
    // ����o�ӵ������Z , �Ҧp �٧Q!�٧Q�� ���Z�� 0 , �� ù�~!��ù�~ �h���Z�� 1 (�Ĥ@�ӵ��b�ĤG�ӵ�����m)
    // �A���O�j�M�o�G�ӵ� , �j�M��A�B�z,
    // �Ҧp�٧Q ���  1, 10, 20, 30 , �Ӫ٧Q����� 1, 20 , ��ܳo�G�խn����

    //int iExcludeNum = (ilTarget->SearchString.AnsiPos(SearchString) - 1)/2; // ���Z

    // �i���o�@�q�]�S�ΤF
    //int iExcludeNum = MyAnsiPos(SearchString , ilTarget->SearchString) - 1; // ���Z, ��@�O�Ʊ�� 0 ��_

    SearchString = "(" + SearchString + "-" + ilTarget->SearchString + ")";     // �ܦ� "(word1!word2)"

	if(Int2s.size() == 0)	// �ڦۤv�S�����
	{
		ClearAll();
		return;
	}

	if(ilTarget->Int2s.size() == 0)		// ���S�����, �ΤG�ӵ��ڥ��S���ۦP�B
    {
		return;
    }

    vector <pair <int,int> > pairTmp;
	pair<int, int> tpPtr1, tpPtr2;

    // �o�@�q���G�i�H�A�֤@�I, ���ζ]�G�Ӱj��....�p�G���G�q��e�e�i ???
	for(int i=0; i<Int2s.size(); i++)
	{
        tpPtr1 = Int2s[i];

        bool bPush = true;  // �w�]�o�@�լO�i�Ϊ�, ���D�b ilTarget ���Q�ư�����

		for(int j=0; j<ilTarget->Int2s.size(); j++)
		{
            tpPtr2 = ilTarget->Int2s[j];

            if(tpPtr1.first > tpPtr2.second) // �ĤG���٤ӻ�, �����L
			{
                continue;
            }
			// ��쭫�ƪ� , �o�@�խn�R��
            if(((tpPtr1.first >= tpPtr2.first) && (tpPtr1.second <= tpPtr2.second))||((tpPtr1.first <= tpPtr2.first) && (tpPtr1.second >= tpPtr2.second)))
			{
                bPush = false;
                break;
            }
            if(tpPtr2.first > tpPtr1.second) // ���ΦA��F, �䤣�쪺.
			{
                break;
            }
		}

		if(bPush)
        {
            pairTmp.push_back(tpPtr1);
        }

	}

	Int2s = pairTmp;
}
/*
//---------------------------------------------------------------------------
// ��X�ĤG�Ӧr��b�Ĥ@�Ӧr�ꪺ�Z��, ���o�O�H����Ӻ⪺
// �Ҧp ����,��i���� , �h�Ǧ^ 3 , �]�� "��" �b "��i����" �ĤT�Ӧr
// �S�p ����, &#X1234;[��*��]����, �]�Ǧ^ 3 , �]�� "&#X1234;[��*��]" �u�O�G�Ӧr
int CInt2List::MyAnsiPos(string sStr1, string sStr2)
{
    int iResult = 0;
    for(int i=1; i<=sStr2.Length(); i++)
    {
        if(!sStr2.IsTrailByte(i))
        {
            if(sStr2.Length()-i+1 >= sStr1.Length())    // �ĤG�ճѤU�����פ@�w�n��Ĥ@�ժ�
            {
                bool bFound = true;      // �����]���F
                int k = i - 1;

                for(int j = 1 ; j<=sStr1.Length(); j++)
                {
                    if(sStr2[k+j] != sStr1[j] && sStr1[j] != '?') // �ݸ��t�~�B�z
                    {
                        bFound = false;
                        break;
                    }
                    if(sStr2[k+j] != sStr1[j] && sStr1[j] == '?') // �o�ر��p  ��?����!��������
                    {
                        if(sStr2.IsLeadByte(k+j) && sStr2.IsTrailByte(k+j+1))
                        {
                            k++;    // �@�Ӱݸ���W�@�Ӥ���r, �ҥH�n�V�Ჾ�@�Ӧr
                            if(sStr2.Length()-k < sStr1.Length())
                            {
                                bFound = false;
                                break;
                            }
                        }
                    }
                }
                if(bFound)
                {
                    iResult = i;
                    break;
                }
            }
        }
    }
    if(iResult <= 1)
        return iResult;     // 0 �� 1 , �N�����Ǧ^
    else
    {
        // �Y��J�O ����, &#X1234;[��*��]���� , �h���U�� sStr = "&#X1234;[��*��]" , �{�b�h�n�䦹�r�ꪺ����
        string sStr = sStr2.SubString(1,iResult-1);

        int iCount = 0;
        while(sStr.Length()>0)
        {
            if(sStr[1] == '&' && sStr[2] == '#')
            {
                int tmp = sStr.AnsiPos(";");
                if(tmp > 0)
                {
                    // ��� &#....;
                    iCount++;
                    sStr = sStr.Delete(1,tmp);
                }
                else
                {
                    iCount++;
                    sStr = sStr.Delete(1,1);
                }
            }
            else if(sStr[1] == '[')
            {
                int tmp = sStr.AnsiPos("]");
                if(tmp > 0)
                {
                    // ��� [��*��]
                    iCount++;
                    sStr = sStr.Delete(1,tmp);
                }
                else
                {
                    iCount++;
                    sStr = sStr.Delete(1,1);
                }
            }
            else if(sStr.Length() == 1) // �Ѥ@�Ӧr��
            {
                iCount++;
                sStr = sStr.Delete(1,1);
            }
            else if(sStr.IsLeadByte(1) && sStr.IsTrailByte(2))  // �o�O����r
            {
                iCount++;
                sStr = sStr.Delete(1,2);
            }
            else
            {
                iCount++;
                sStr = sStr.Delete(1,1);
            }
        }
        return iCount+1;
    }
}
*/
