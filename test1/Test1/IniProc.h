#pragma once


#include <vector>
#include <winnt.h>
#define TCHAR char
#define MAX_COUNT 6
#define CountArray(exc) sizeof(exc)/sizeof(exc[0])
#define RETURN_FALSE_IF(exc) if(exc){return false;}
#define RETURN_ZERO_IF(exc) if(exc){return 0;}
#define RETURN_IF(exc) if(exc){return;}
typedef std::vector<BYTE> BYTE_VECTOR;
typedef std::vector<std::vector<BYTE>> BYTE_VECTOR_VECTOR;
struct SpeciallyCardStru
{
	BYTE cards[5];
	SpeciallyCardStru()
	{
		memset(cards, 0, sizeof(cards));
	}
};

// 特殊牌处理类
class CSpeciallyCard
{
public:
	CSpeciallyCard()
	{
		userNum = 0;
		cardsNum = 0;
		cardsIndex = 0;
	}
	~CSpeciallyCard()
	{
		
	}

public:
	//获取特殊牌组
	void GetEspeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVec);
	BYTE userNum; //特殊用户数
private:
	//获取工程路径
	void GetProjectDirectory(TCHAR *workPath, WORD arrCnt);
	//分隔字符串
	void SeparateStr(std::string &str);
	//从所有牌组中获取对应用户数的可能组合序号
	void Combine(/*BYTE_VECTOR &srcVec, */int n, int m, std::vector<std::vector<BYTE>>& idexVec);
	//牌组有效性判断
	bool MatchCards(BYTE_VECTOR& cardsVec);
	//获取vector中重复次数最多的数的个数
	BYTE GetRepatNum(BYTE_VECTOR cardsVec);
	//判断所有特殊用户的牌组是否有效
	void IsValidCards(BYTE_VECTOR_VECTOR& cardsVec);
	//分发牌组
	void DistSpeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVec);
	//将原始牌组重新洗牌
	void ChangeCards(BYTE* des, BYTE baseNumTem, BYTE_VECTOR& cardsVec);
private:
	//存放从ini文件中读取的所有牌组
	std::vector<SpeciallyCardStru> cardsVec;
	BYTE cardsNum; //特殊牌组个数
	BYTE cardsIndex; //分发牌组给用户索引
};
