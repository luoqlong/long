#include "stdafx.h"
#include <iostream>

int main(void)
{
	int arr[3] = {};
	memset(arr, 1, sizeof(arr) / sizeof(arr[0]) *sizeof(int));
	//std::cout << arr[2] << std::endl;
	int x, y = 1;

	struct test
	{
		short a;
		double b;
		WORD c;
		short d;
		int e;
	};

	test tt;
	ZeroMemory(&tt, sizeof(tt));
	tt.a = 12;
	int siee = sizeof(test);
	int siee1 = sizeof(tt);
	return 0;
}