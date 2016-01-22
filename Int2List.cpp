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
// �B��l�h��
void CInt2List::operator=(CInt2List * ilTarget)
{
}
//---------------------------------------------------------------------------
// �N��� copy �L��
void CInt2List::Copy(CInt2List * ilTarget)
{
    Int2s = ilTarget->Int2s;

	//ClearAll();
	//for (int i=0; i<ilTarget->Int2s->Count; i++)
	//{
	//	Add((TPoint *)ilTarget->Int2s->Items[i]);
	//}

    // SearchString = ilTarget->SearchString;  copy �٬O���n�h��j�M�r�����n
}
//---------------------------------------------------------------------------
// �B��l�h��
void CInt2List::operator&=(CInt2List * ilTarget)
{
}
/*
//---------------------------------------------------------------------------
// �Y�G�̳������, �N�G�̦X��
void CInt2List::AndIt(CInt2List * ilTarget)
{
	// �u�n���@�ӤH�O 0 , �N�����U�h�F

    string sSearchString = "(" + SearchString + "&" + ilTarget->SearchString + ")";     // �ܦ� "(word1&word2)"
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
	}
	else	//���U�ӴN�n�N�G�H�X�֤F
	{
		OrIt(ilTarget);
    }
    SearchString = sSearchString;     // �ܦ� "(word1&word2)"
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
	TPoint * tpPtr1, *tpPtr2;

    string sSearchString = "(" + SearchString + "," + ilTarget->SearchString + ")";     // �ܦ� "(word1,word2)"
	if(Int2s->Count == 0)	// �ڦۤv�S�����
	{
		Copy(ilTarget);
        SearchString = sSearchString;
		return;
	}

	if(ilTarget->Int2s->Count == 0)		// ���S�����
    {
        SearchString = sSearchString;
		return;
    }

	for(int i=0; i<ilTarget->Int2s->Count; i++)
	{
		tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[i];
		while(tpPtr2->x >= tpPtr1->x)
		{
			iIndex++;
			if(iIndex == Int2s->Count) break;
			tpPtr1 =  (TPoint *) Int2s->Items[iIndex];
		}
		TPoint * tpNew = new TPoint(tpPtr2->x, tpPtr2->y);	// �o�̪�F�@�ѥb�h�� bug 10/19 '03
		Int2s->Insert(iIndex,tpNew);
	}
    SearchString = sSearchString;
}
//---------------------------------------------------------------------------
// �Y�G�̾a��ܬY�@�ӵ{��, �h�ܦ��@�ӽd��
void CInt2List::NearIt(CInt2List * ilTarget)
{
	NearNum = fmOption->Setting->NearNum;			// Near �B�⪺�d��     ???? �n�ΨϥΪ̿�J
    string sSearchString = "(" + SearchString + "+" + ilTarget->SearchString + ")";     // �ܦ� "(word1+word2)"

	// �S��ƴN����
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	TList * tlResult = new TList;		// �񵲪G�Ϊ�
	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr1 =  (TPoint *) Int2s->Items[i];
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// ���@��
			//if(!((tpPtr2->x - tpPtr1->y > NearRange) || (tpPtr1->x - tpPtr2->y > NearRange)))
			if((tpPtr2->x - tpPtr1->y <= NearNum) && (tpPtr1->x - tpPtr2->y <= NearNum))
			{
				TPoint * tpNew = new TPoint(min(tpPtr1->x, tpPtr2->x), max(tpPtr1->y, tpPtr2->y));
				tlResult->Add(tpNew);
			}
			else
				if (tpPtr2->x - tpPtr1->y > NearNum) break;	// �䤣��F, ���U�@��
		}
	}

	ClearAll();
	if(Int2s) delete Int2s;
	Int2s = tlResult;			// �������G
    SearchString = sSearchString;

}
//---------------------------------------------------------------------------
// �P Near , ���L�u��b��᭱, �]�N�O�����Ǫ�
void CInt2List::BeforeIt(CInt2List * ilTarget)
{
	BeforeNum = fmOption->Setting->BeforeNum;		// Before �B�⪺�d��   ???? �n�ΨϥΪ̿�J
    string sSearchString = "(" + SearchString + "*" + ilTarget->SearchString + ")";     // �ܦ� "(word1*word2)"

	// �S��ƴN����
	if(Int2s->Count ==0 || ilTarget->Int2s->Count == 0)
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	TList * tlResult = new TList;		// �񵲪G�Ϊ�
	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr1 =  (TPoint *) Int2s->Items[i];
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// ���@��
			if((tpPtr2->x - tpPtr1->x > 0) && (tpPtr2->x - tpPtr1->y <= BeforeNum))
			{
				TPoint * tpNew = new TPoint(tpPtr1->x, max(tpPtr1->y, tpPtr2->y));
				tlResult->Add(tpNew);
			}
			else
				if (tpPtr2->x - tpPtr1->y > BeforeNum) break;	// �䤣��F, ���U�@��
		}
	}

	ClearAll();
	if(Int2s) delete Int2s;
	Int2s = tlResult;			// �������G
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

    string sSearchString = "(" + SearchString + "-" + ilTarget->SearchString + ")";     // �ܦ� "(word1!word2)"

	if(Int2s->Count == 0)	// �ڦۤv�S�����
	{
		ClearAll();
        SearchString = sSearchString;
		return;
	}

	if(ilTarget->Int2s->Count == 0)		// ���S�����, �ΤG�ӵ��ڥ��S���ۦP�B
    {
        SearchString = sSearchString;
		return;
    }

	TPoint * tpPtr1, *tpPtr2;

	for(int i=0; i<Int2s->Count; i++)
	{
        tpPtr1 =  (TPoint *) Int2s->Items[i];

		for(int j=0; j<ilTarget->Int2s->Count; j++)
		{
			tpPtr2 =  (TPoint *) ilTarget->Int2s->Items[j];

			// ��쭫�ƪ� , �o�@�խn�R��
			// if((tpPtr1->x - tpPtr2->x == iExcludeNum)) // �o�O�ª���k, �n���� tpPtr1 �P tpPtr2 ���b�����d��
            if(((tpPtr1->x >= tpPtr2->x) && (tpPtr1->y <= tpPtr2->y))||((tpPtr1->x <= tpPtr2->x) && (tpPtr1->y >= tpPtr2->y)))
			{
                Delete(i);
                i--;
                //ilTarget->Delete(j);
                break;
            }
            if(tpPtr2->x > tpPtr1->y) // ���ΦA��F, �䤣�쪺.
			{
                break;
            }
		}
	}

    SearchString = sSearchString;
}
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
