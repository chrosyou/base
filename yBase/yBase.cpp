// yBase.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AnalyseCmdLine.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	base::strings::CCmdLine cmd(lpCmdLine);

	return 0;
}

