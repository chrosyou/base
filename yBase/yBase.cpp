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

	IUnknow* pI = CreateInstance();

	IX* pIX = NULL;
	HRESULT hr = pI->QueryInterface(2, (void**)&pIX);
	if (SUCCEEDED(hr))
	{
		pIX->PrintX();
		pIX->Release();
		pIX->PrintX();
	}


	pI->Release();

	//system("pause");
	return 0;
}

