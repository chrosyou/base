// CreateDump.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CreateDump.h"
#include <imagehlp.h>

#pragma comment(lib,"Dbghelp.lib")

// 异常处理函数
LONG WINAPI EL_UnhandledExceptionFilterFunc(PEXCEPTION_POINTERS pExceptionInfo)
{
	HANDLE hFile = CreateFile(_T("d:\\test.dmp"), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION eInfo={0};
		eInfo.ThreadId=GetCurrentThreadId();
		eInfo.ExceptionPointers=pExceptionInfo;
		eInfo.ClientPointers=FALSE;

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),

			hFile, MiniDumpNormal, &eInfo, 0, 0);



		CloseHandle(hFile);

	}
	return true;
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	SetUnhandledExceptionFilter(EL_UnhandledExceptionFilterFunc);
	
	int i = 0;
	int j = 1 / i;


	return 0;
}

