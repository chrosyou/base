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
	ATTINFO test;
	test.swCompanyName = _T("company");
	test.swVersion = _T("1.2.3.4");
	test.wsComments = _T("comment");
	test.wsLegalCopyright = _T("copyright");
	test.wsOriginalFilename = _T("setup");
	test.wsFilePath = _T("E:\\work\\base\\base\\Release\\testmfc.exe");

	ModifyPEAttribute(test);

	return 0;
}

