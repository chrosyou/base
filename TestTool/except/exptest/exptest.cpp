// exptest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

double divtest(double a, double b)
{
	if (b - 0 < 0.000000001)
	{
		throw "argument is not right";
	}


	return a / b;
}


int _tmain(int argc, _TCHAR* argv[])
{

	try
	{
		char *a = NULL;
		*a = 'c';
		//divtest(1, 0);
	}
	catch (...)
	{
		std::cout<<"except occur"<<std::endl;
	}

	return 0;
}

