// TestMain.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestMain.h"
#include "baseoperator.h"

typedef HRESULT (__stdcall* MyDllCreateObject)(void **ppv );

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	HMODULE hWnd = LoadLibraryW(L"TestDll.dll");
	if (hWnd == NULL)
	{
		return 1;
	}

	MyDllCreateObject test = (MyDllCreateObject)GetProcAddress(hWnd, "DllCreateObject");

	if (NULL == test)
	{
		return 2;
	}

	BaseOpreator* lpBase = NULL;
	test((void**)(&lpBase));

	POINT pos;
	lpBase->GetMousePos(pos);


	return 0;
}

