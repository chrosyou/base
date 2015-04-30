// yBase.cpp : 定义控制台应用程序的入口点。
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

	// TODO: 在此放置代码。
	OldDress* test = new OldDress;
	DecorateA* a = new DecorateA;
	DecorateB* b = new DecorateB;

	a->SetDecorate(test);
	b->SetDecorate(a);

	b->Show();

//	CConcreteCreator<CWindowsProduct> test(_T("test"));
//	COsProduct* windows = test.Create();
//	windows->Start();


	//system("pause");
	return 0;
}

