#include "stdafx.h"
#include "IniProc.h"
#include <algorithm>
#define MAX_CARD_COUNT 1

const static char goodCards[][5] =
{
	//8点
	{ 0x01, 0x04, 0x05, 0x02, 0x06 },
	{ 0x12, 0x13, 0x16, 0x22, 0x26 },
	{ 0x03, 0x23, 0x04, 0x21, 0x07 },

	//9点
	{ 0x01, 0x04, 0x05, 0x15, 0x24 },
	{ 0x12, 0x02, 0x06, 0x22, 0x07 },
	{ 0x13, 0x03, 0x04, 0x01, 0x08 },

	//10点
	{ 0x01, 0x04, 0x05, 0x25, 0x15 },
	{ 0x12, 0x02, 0x06, 0x22, 0x08 },
	{ 0x13, 0x03, 0x04, 0x01, 0x09 },

};
void CSpeciallyCard::IsValidCards(BYTE_VECTOR_VECTOR& cardsVecTem)
{
	auto ptrBegin = cardsVecTem.begin();
	for (; ptrBegin != cardsVecTem.end();)
	{
		BYTE_VECTOR allUsrCardsVec;
		for (int idex = 0; idex < userNum; ++idex)
		{
			allUsrCardsVec.insert(allUsrCardsVec.end(), 
				cardsVec[(*ptrBegin)[idex]].cards, 
				cardsVec[(*ptrBegin)[idex]].cards + MAX_COUNT - 1);
		}
		if (GetRepatNum(allUsrCardsVec) > MAX_CARD_COUNT)
		{
			ptrBegin = cardsVecTem.erase(ptrBegin);
		}
		else
		{
			++ptrBegin;
		}
	}
}

bool CSpeciallyCard::MatchCards(BYTE_VECTOR& cardsVec)
{
	RETURN_FALSE_IF(MAX_COUNT - 1 != cardsVec.size());
	for (std::string::size_type idex = 0; idex < cardsVec.size(); ++idex)
	{
		BYTE cardTem = cardsVec[idex];
		if (cardTem >= 0x01 && cardTem <= 0xd
			|| cardTem >= 0x11 && cardTem <= 0x1d
			|| cardTem >= 0x21 && cardTem <= 0x2d)
			{
				continue;
			}
		else
		{
			return false;
		}
	}
	return true;
}

BYTE CSpeciallyCard::GetRepatNum(BYTE_VECTOR cardsVec)
{
	RETURN_ZERO_IF(0 == cardsVec.size());
	std::sort(cardsVec.begin(), cardsVec.end());
	int maxData = 0;
	int valueCnt = 0;
	int maxCnt = 0;
	for (std::string::size_type i = 0; i < cardsVec.size(); ++i)
	{
		if (maxData == cardsVec[i])
		{
			++valueCnt;
		}
		else
		{
			maxData = cardsVec[i];
			valueCnt = 1;
		}
		if (maxCnt < valueCnt)
		{
			maxCnt = valueCnt;
		}
	}
	return maxCnt;
}

void CSpeciallyCard::Combine(/*BYTE_VECTOR &srcVec, */int n, int m, std::vector<std::vector<BYTE>>& idexVec)
{
	if (m > n)
	{
		return;
	}
	std::vector<BYTE> vecTem;
	int* pTable = new int[n];       //定义标记buf并将其前m个置1  
	memset(pTable, 0, sizeof(int)*n);
	for (int i = 0; i < m; ++i)
	{
		pTable[i] = 1;
	}
	bool bFind = false;
	do
	{
		vecTem.clear();
		for (int i = 0; i < n; i++)  //打印当前组合  
		{
			if (pTable[i])
			{
				vecTem.push_back(i);
			}
		}
		if (0 != vecTem.size())
		{
			idexVec.emplace_back(vecTem);
		}

		bFind = false;
		for (int i = 0; i < n - 1; i++)
		{
			if (pTable[i] == 1 && pTable[i + 1] == 0)
			{
				std::swap(pTable[i], pTable[i + 1]);    //调换10为01  
				bFind = true;

				if (pTable[0] == 0)  //如果第一位为0，则将第i位置之前的1移到最左边，如为1则第i位置之前的1就在最左边，无需移动  
				{
					for (int k = 0, j = 0; k < i; k++)   //O(n)复杂度使1在前0在后  
					{
						if (pTable[k])
						{
							std::swap(pTable[k], pTable[j]);
							j++;
						}
					}
				}

				break;
			}
		}
	} while (bFind);

	delete[] pTable;
}

// 特殊牌组处理
void CSpeciallyCard::GetEspeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVec)
{
	//TCHAR iniDirectory[MAX_PATH] = TEXT("");
	//GetProjectDirectory(iniDirectory, MAX_PATH);
	//TCHAR iniPath[MAX_PATH] = TEXT("");
	//_snprintf(iniPath, MAX_PATH, TEXT("%s\\SpeciallyCard.ini"), iniDirectory);
	//CWHIniData IniData;
	//IniData.SetIniFilePath(iniPath);
	//BYTE cardsNum = 0;
	//cardsNum = GetPrivateProfileInt(TEXT("Cards"), TEXT("Num"), 0, iniPath);
	//int arrNum = sizeof(goodCards) / sizeof(goodCards[0]);
	//for (BYTE idex = 0; arrNum; ++idex)
	//{
	//	TCHAR cardsName[MAX_COUNT] = TEXT("");
	//	TCHAR cardsAr[MAX_PATH] = TEXT("");
	//	int num = sizeof(cardsAr) / sizeof(cardsAr[0]);
	//	//_snprintf(cardsName, MAX_COUNT, TEXT("Arr%d"), idex);
	//	//GetPrivateProfileString(TEXT("Cards"), cardsName, NULL, cardsAr, sizeof(cardsAr) / sizeof(cardsAr[0]), iniPath);
		std::string cardSr;
		SeparateStr(cardSr);
	//}
	DistSpeciallyCards(des, baseNumTem, cardsVec);
}

void CSpeciallyCard::DistSpeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVecTem)
{
	BYTE_VECTOR_VECTOR btVec;
	BYTE_VECTOR indexVec;
	Combine(cardsNum, userNum, btVec);
	IsValidCards(btVec);
	BYTE num = btVec.size();
	srand(time(0));
	if (0 != num)
	{
		BYTE idex = rand() % num;
		for (int i = 0; i < userNum; ++i)
		{
			BYTE arrInde = btVec[idex][i];
			SpeciallyCardStru cardStru;
			memcpy_s(cardStru.cards, MAX_COUNT - 1, cardsVec[arrInde].cards, MAX_COUNT - 1);
			cardsVecTem.emplace_back(cardStru);
		}
		BYTE_VECTOR cardsVec;
		for (int idex = 0; idex < cardsVecTem.size(); ++idex)
		{
			cardsVec.insert(cardsVec.end(), cardsVecTem[idex].cards, cardsVecTem[idex].cards + MAX_COUNT - 1);
			for (int i = 0; i < cardsVec.size(); ++i)
			{
				printf("%02x ", cardsVec[i]);
			}
			printf("\n");
		}
		ChangeCards(des, baseNumTem, cardsVec);
	}

}

void CSpeciallyCard::ChangeCards(BYTE* des, BYTE baseNumTem, BYTE_VECTOR& cardsVec)
{
	//从前往后发牌处理
	int baseNum = 0;
	int modefyNum = 0;
	std::vector<BYTE> baseVec(des, des + baseNumTem);
	auto modefyBegin = cardsVec.begin();
	auto modefyEnd = cardsVec.end();
	int idex = 0;
	int modefyIdex = 0;
	auto basePtr = baseVec.begin();
	//获取对应索引，并将对应idex处置为0
	for (; modefyBegin != modefyEnd; ++modefyBegin)
	{
		auto findPtr = find(basePtr++, baseVec.end(), *modefyBegin);
		if (baseVec.end() != findPtr)
		{
			modefyIdex = findPtr - baseVec.begin();
			BYTE dataTem = des[idex];
			des[idex] = *modefyBegin;
			des[modefyIdex] = dataTem;
			baseVec[modefyIdex] = dataTem;
			++idex;
		}
	}
	//从后往前发牌处理
	//int baseNum = 0;
	//int modefyNum = 0;
	//std::vector<BYTE> baseVec(des, des + baseNumTem);
	////std::vector<BYTE> modifyVec(src, src + num);
	////BYTE index[13] = {0xFF};
	//auto modefyBegin = cardsVec.begin();
	//auto modefyEnd = cardsVec.end();
	//int idex = baseNumTem - 1;
	//int modefyIdex = 0;
	//auto basePtr = baseVec.rbegin();
	////获取对应索引，并将对应idex处置为0
	//for (; modefyBegin != modefyEnd; ++modefyBegin)
	//{
	//	auto findPtr = find(basePtr++, baseVec.rend(), *modefyBegin);
	//	if (baseVec.rend() != findPtr)
	//	{
	//		modefyIdex = baseVec.rend() - findPtr - 1;
	//		BYTE dataTem = des[idex];
	//		des[idex] = *modefyBegin;
	//		des[modefyIdex] = dataTem;
	//		baseVec[modefyIdex] = dataTem;
	//		--idex;
	//	}
	//}
}

void CSpeciallyCard::GetProjectDirectory(TCHAR *workPath, WORD arrCnt)
{
	TCHAR cardsTem[MAX_PATH] = TEXT("");
	GetModuleFileName(NULL, cardsTem, CountArray(cardsTem));
	for (int idex = lstrlen(cardsTem); idex >= 0; --idex)
	{
		if (TEXT('\\') == cardsTem[idex])
		{
			cardsTem[idex] = 0;
			break;
		}
	}
	ASSERT(TEXT('0') != cardsTem[0]);
	lstrcpyn(workPath, cardsTem, arrCnt);
}

void CSpeciallyCard::SeparateStr(std::string &str)
{
	SpeciallyCardStru cardStru;
	//std::string::size_type pos = str.find_first_of(',');
	//std::string::size_type posTem = 0;
	//std::string strTem = "";
	//unsigned int idex = 0;
	//while (std::string::npos != pos)
	//{
	//	strTem = str.substr(posTem, pos - posTem);
	//	long data = strtol(strTem.c_str(), NULL, 16);
	//	char chArr[14] = "";
	//	sprintf_s(chArr, "%d\n", data);
	//	cardStru.cards[idex] = atoi(chArr);
	//	++idex;

	//	posTem = pos + 1;
	//	pos = str.find_first_of(',', posTem);
	//}
	//strTem = str.substr(posTem);
	//long data = strtol(strTem.c_str(), NULL, 16);
	//char chArr1[14] = "";
	//sprintf_s(chArr1, "%d\n", data);
	//cardStru.cards[idex] = atoi(chArr1);
	//RETURN_IF(4 != idex);
	for (int idex = 0; idex < sizeof(goodCards) / sizeof(goodCards[0]); ++idex)
	{
		memcpy_s(cardStru.cards, 5, goodCards[idex], 5);

		BYTE_VECTOR vecTem(cardStru.cards, cardStru.cards + MAX_COUNT - 1);
		RETURN_IF(!MatchCards(vecTem) || GetRepatNum(vecTem) > MAX_CARD_COUNT);
		cardsVec.emplace_back(cardStru);
		++cardsNum;
	}
}

