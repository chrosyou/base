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
	Context test(new StrageryA);
	DWORD dwRet = test.Operator();

//	CConcreteCreator<CWindowsProduct> test(_T("test"));
//	COsProduct* windows = test.Create();
//	windows->Start();


	system("pause");
	return 0;
}

