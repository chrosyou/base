// yBase.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "baselib.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣
	Operator* add = FactoryOperator::CreateOperator(_T("/"));
	add->SetOpeA(1.5);
	add->SetOpeB(2.5);
	double dRet = add->GetResult();
	//test.CreateOperator(_T("+"));



	return 0;
}

