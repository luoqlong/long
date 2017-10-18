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

// �����ƴ�����
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
	//��ȡ��������
	void GetEspeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVec);
	BYTE userNum; //�����û���
private:
	//��ȡ����·��
	void GetProjectDirectory(TCHAR *workPath, WORD arrCnt);
	//�ָ��ַ���
	void SeparateStr(std::string &str);
	//�����������л�ȡ��Ӧ�û����Ŀ���������
	void Combine(/*BYTE_VECTOR &srcVec, */int n, int m, std::vector<std::vector<BYTE>>& idexVec);
	//������Ч���ж�
	bool MatchCards(BYTE_VECTOR& cardsVec);
	//��ȡvector���ظ������������ĸ���
	BYTE GetRepatNum(BYTE_VECTOR cardsVec);
	//�ж����������û��������Ƿ���Ч
	void IsValidCards(BYTE_VECTOR_VECTOR& cardsVec);
	//�ַ�����
	void DistSpeciallyCards(BYTE* des, BYTE baseNumTem, std::vector<SpeciallyCardStru>& cardsVec);
	//��ԭʼ��������ϴ��
	void ChangeCards(BYTE* des, BYTE baseNumTem, BYTE_VECTOR& cardsVec);
private:
	//��Ŵ�ini�ļ��ж�ȡ����������
	std::vector<SpeciallyCardStru> cardsVec;
	BYTE cardsNum; //�����������
	BYTE cardsIndex; //�ַ�������û�����
};
