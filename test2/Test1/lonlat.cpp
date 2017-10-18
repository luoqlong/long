#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

//#define M_PI       3.14159265358979323846
//const double EARTH_RADIUS = 6371.004;//地球半径
//
//
//double rad(double d)
//{
//	return d * M_PI / 180.0;
//}
//
//
//double GetDistance(double lat1, double lng1, double lat2, double lng2)
//{
//	double radLat1 = rad(lat1);
//	double radLat2 = rad(lat2);
//	double a = radLat1 - radLat2;
//	double b = rad(lng1) - rad(lng2);
//
//
//	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
//		cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
//	s = s * EARTH_RADIUS;
//	return s;
//}
//
//bool ReturnTest(bool ret)
//{
//	bool bISf = ~ret;
//	return bISf;
//}
struct UserLonLatInfo
{
	UserLonLatInfo()
	{
		lon = 0.0;
		lat = 0.0;
	}
	double lon;
	double lat;
	std::string userName;
};
//
////距离计算
//#define M_PI       3.14159265358979323846
//const double EARTH_RADIUS = 6371.004;//地球半径
//double rad(double d)
//{
//	return d * M_PI / 180.0;
//}
//double GetDistance(double lat1, double lng1, double lat2, double lng2)
//{
//	double radLat1 = rad(lat1);
//	double radLat2 = rad(lat2);
//	double a = radLat1 - radLat2;
//	double b = rad(lng1) - rad(lng2);
//
//
//	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
//		cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
//	s = s * EARTH_RADIUS * 1000;
//	return s;
//}

//距离计算
#define M_PI       3.14159265358979323846
const double EARTH_RADIUS = 6371.004;//地球半径
double rad(double d)
{
	return d * M_PI / 180.0;
}
double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double a = radLat1 - radLat2;
	double b = rad(lng1) - rad(lng2);


	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
		cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
	s = s * EARTH_RADIUS * 1000;
	return s;
}

double CalUserDistance(UserLonLatInfo& myuserStru, UserLonLatInfo& userStru)
{
	CString strrr;
	//strrr.Format(("uid %s 经纬度是 %f, %f"), myuserStru.userName, myuserStru.lat, myuserStru.lon);
	//CTraceService::TraceString(TEXT(strrr), TraceLevel_Info);
	// 	strrr.Format(("uid %s 经纬度是 %lf, %lf"), userStru.userName, userStru.lat, userStru.lon);
	// 	CTraceService::TraceString(TEXT(strrr), TraceLevel_Info);
	return GetDistance(myuserStru.lat, myuserStru.lon, userStru.lat, userStru.lon);
	//TCHAR disInfo[255] = { '0/' };
	//sprintf_s(disInfo, "玩家: %s, %s相距%ld米", myuserStru.userName.c_str(), userStru.userName.c_str());
	//std::string str(disInfo);
	//repRep.cmd_value.disStrVec.push_back(str);
}
int _tmain(int argc, _TCHAR* argv[])
{
	//std::string str1 = "颉压力最顺咖";
	//TCHAR chStr[256];
	//sprintf_s(chStr, "这个 : %s", str1.c_str());
	//printf("%s/n", chStr);
	//double dist = GetDistance(39.97274, 116.38649, 39.99274, 116.39649);
	////double dist = GetDistance(30.12030029296875, 109.2036972045898, 30.12030029296875,109.2036972045899);
	//cout << dist * 1000 << endl;
	////getchar();
	//int x = 4;
	//int y = 3;
	//int xx = 1 << 3;
	//int z = x & (1 << 3);
	//bool ret = ReturnTest(false);
	//bool ret1 = ReturnTest(true);
	double lon1 = 104.386047363281;
	double lat1 = 30.8506927490234;
	double lon2 = 115.924026489258;
	double lat2 = 25.7717056274414;
	double ret = GetDistance(lat1, lon1, lat2, lon2);
	std::cout << (unsigned long)ret << std::endl;
	LONGLONG ret1 = GetDistance((unsigned long)lat1, (unsigned long)lon1, (unsigned long)lat2, (unsigned long)lon2);
	std::cout << ret1 << std::endl;
	//std::map<std::string, int> userLonlatMap;
	//userLonlatMap["aaa"] = 1;
	//userLonlatMap["bbb"] = 2;
	//userLonlatMap["ccc"] = 3;
	//userLonlatMap["ddd"] = 4;
	//for (auto ptr = userLonlatMap.begin(); ptr != userLonlatMap.end(); ++ptr)
	//{
	//	auto ptr1 = ptr;
	//	for (++ptr1; ptr1 != userLonlatMap.end(); ++ptr1)
	//	{
	//		LONGLONG dis = ptr->second;
	//		std::cout << ptr->first << " + " << ptr1->first << endl;
	//	}
	//}
	std::vector<int> userVec;
	std::map<int, UserLonLatInfo> userLonlatMap;
	UserLonLatInfo myuserStru;
	myuserStru.lat = 30.8506927490234;
	myuserStru.lon = 104.386047363281;
	myuserStru.userName = "my";

	UserLonLatInfo userStru;
	userStru.lat = 0;
	userStru.lon = 0;
	userStru.userName = "aa";
	userLonlatMap[1] = userStru;

	UserLonLatInfo userStru1;
	userStru1.lat = 25.7717056274414;
	userStru1.lon = 115.924026489258;
	userStru1.userName = "bb";
	userLonlatMap[2] = userStru1;

	UserLonLatInfo userStru2;
	userStru2.lat = 30.6289157867432;
	userStru2.lon = 104.013084411621;
	userStru2.userName = "cc";
	userLonlatMap[3] = userStru2;
	
	for (auto ptrM = userLonlatMap.begin(); ptrM != userLonlatMap.end(); ++ptrM)
	{
		LONGLONG dis = CalUserDistance(myuserStru, ptrM->second);
		// 		CString strrr;
		// 		strrr.Format(("11111dis is %d"), dis);
		// 		CTraceService::TraceString(TEXT(strrr), TraceLevel_Info);
		TCHAR disInfo[255] = { '0/' };
		sprintf(disInfo, "玩家: %s, %s相距%ld米", myuserStru.userName.c_str(), ptrM->second.userName.c_str(), dis);
		std::string str(disInfo);
		std::cout << str << endl;
	}
	for (auto ptr = userLonlatMap.begin(); ptr != userLonlatMap.end(); ++ptr)
	{
		auto ptr1 = ptr;
		for (++ptr1; ptr1 != userLonlatMap.end(); ++ptr1)
		{
			LONGLONG dis = CalUserDistance(ptr->second, ptr1->second);
			// 			CString strrr;
			// 			strrr.Format(("222222dis is %d"), dis);
			// 			CTraceService::TraceString(TEXT(strrr), TraceLevel_Info);
			TCHAR disInfo[255] = { '0/' };
			sprintf(disInfo, "玩家: %s, %s相距%ld米", ptr->second.userName.c_str(), ptr1->second.userName.c_str(), dis);
			std::string str(disInfo);
			std::cout << str << endl;
		}
	}
	return 0;
}
