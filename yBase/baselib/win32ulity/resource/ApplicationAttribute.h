
#pragma once
#include "tchar.h"
#include <string>
#pragma  comment(lib, "Version.lib")

typedef struct _ATTINFO
{
	std::wstring wsFilePath;		//待修改的文件路径
	std::wstring swCompanyName;		//公司名
	std::wstring swVersion;			//文件版本，产品版本
	std::wstring wsComments;		//描述
	std::wstring wsOriginalFilename;//原始名
	std::wstring wsLegalCopyright;	//版权信息
}ATTINFO, *PATTINFO;

// these macros help to align on r-byte boundaries (thanks Ted Peck)
#define roundoffs(a,b,r) (((BYTE *) (b) - (BYTE *) (a) + ((r) - 1)) & ~((r) - 1))
#define roundpos(a,b,r) (((BYTE *) (a)) + roundoffs(a,b,r))


struct VS_VERSIONINFO
{
	WORD                wLength;
	WORD                wValueLength;
	WORD                wType;
	WCHAR               szKey[1];
	WORD                wPadding1[1];
	VS_FIXEDFILEINFO    Value;
	WORD                wPadding2[1];
	WORD                wChildren[1];
};

struct
{
	WORD wLanguage;
	WORD wCodePage;
} *lpTranslate;

//1.0.3.7
typedef struct _Version
{
	DWORD dwVersionMS;  //high version 1.0
	DWORD dwVersionLS;  //low version  3.7
}VERSION_NUM;

//Get version number from string
void GetVersionFromString(std::wstring wsVersion, VERSION_NUM& varVersion)
{
	int iTmp = 0;
	int iStart = 0;
	int iEnd = wsVersion.find(_T('.'));
	std::wstring wsNum = wsVersion.substr(0, iEnd - iStart);
	int iOne = _wtoi(wsNum.c_str());
	iStart = iEnd + 1;

	iEnd = wsVersion.find(_T('.'), iStart);
	wsNum = wsVersion.substr(iStart, iEnd- iStart);
	int iTwo = _wtoi(wsNum.c_str());
	iStart = iEnd + 1;

	iEnd = wsVersion.find(_T('.'), iStart);
	wsNum = wsVersion.substr(iStart, iEnd- iStart);
	int iThree = _wtoi(wsNum.c_str());
	iStart = iEnd + 1;

	wsNum = wsVersion.substr(iStart, wsVersion.length() - iStart);
	int iFour = _wtoi(wsNum.c_str());

	iOne = iOne << 16;
	varVersion.dwVersionMS = iOne | iTwo;

	iThree = iThree << 16;
	varVersion.dwVersionLS = iThree | iFour;
}

void ChangeBuffer(LPTSTR lpBuf, std::wstring& strValue)
{
	if (!strValue.empty())
	{
		_tcscpy_s(lpBuf, strValue.length()+1, strValue.c_str());
	}
}

void ModifyPEAttribute(ATTINFO& attinfo)
{
	VS_VERSIONINFO      *pVerInfo = NULL;
	LPBYTE              pOffsetBytes = NULL;
	VS_FIXEDFILEINFO    *pFixedInfo = NULL;
	LPCTSTR             lpszFile = attinfo.wsFilePath.c_str();  
	DWORD               dwHandle = 0;
	DWORD				dwSize = 0;
	DWORD				dwResult = 0;

	VERSION_NUM tmp;
	GetVersionFromString(attinfo.swVersion, tmp);
	dwSize = GetFileVersionInfoSize(lpszFile, &dwHandle);

	if (0 < dwSize)
	{
		LPBYTE lpBuffer = new BYTE[dwSize];

		if (GetFileVersionInfo(lpszFile, 0, dwSize, lpBuffer) != FALSE)
		{

			// 'point to' the start of the version information block
			pVerInfo = (VS_VERSIONINFO *) lpBuffer;

			// the fixed section starts right after the 'VS_VERSION_INFO' string
			pOffsetBytes = (BYTE *) &pVerInfo->szKey[_tcslen(pVerInfo->szKey) + 1];

			pFixedInfo = (VS_FIXEDFILEINFO *) roundpos(pVerInfo, pOffsetBytes, 4);

			// increment the numbers!
			pFixedInfo->dwFileVersionMS    = tmp.dwVersionMS; //pFixedInfo->dwFileVersionMS + 0x00010001;
			pFixedInfo->dwFileVersionLS    = tmp.dwVersionLS; //pFixedInfo->dwFileVersionLS + 0x00010001;
			pFixedInfo->dwProductVersionMS = tmp.dwVersionMS; //pFixedInfo->dwProductVersionMS + 0x00010001;  //internal version num
			pFixedInfo->dwProductVersionLS = tmp.dwVersionLS; //pFixedInfo->dwProductVersionLS + 0x00010001;

			HANDLE hResource = BeginUpdateResource(lpszFile, FALSE);
			if (NULL != hResource)
			{
				UINT uTemp;

				// get the language information
				if (VerQueryValue(lpBuffer, _T("\\VarFileInfo\\Translation"), (LPVOID *) &lpTranslate, &uTemp) != FALSE)
				{
					TCHAR strSubBlock[MAX_PATH] = {0};
					LPTSTR  pValueBuffer;


					//名称
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\InternalName"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					BOOL bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						//pValueBuffer[0] = _T('a');
					}

					//文件描述
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\FileDescription"),lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.wsComments);
					}

					//产品名
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\ProductName"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.wsOriginalFilename);
					}

					//版权说明
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\LegalCopyright"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.wsLegalCopyright);
					}

					//原始名
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\OriginalFilename"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.wsOriginalFilename);
					}

					//产品版本
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\ProductVersion"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.swVersion);
					}

					//文件版本
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\FileVersion"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.swVersion);
					}

					//PrivateBuild版本
					_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\SpecialBuild"), lpTranslate->wLanguage, lpTranslate->wCodePage);
					bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
					if (bRet == TRUE)
					{
						ChangeBuffer(pValueBuffer, attinfo.swVersion);
					}

					// could probably just use LANG_NEUTRAL/SUBLANG_NEUTRAL
					if (UpdateResource(hResource, RT_VERSION, MAKEINTRESOURCE(VS_VERSION_INFO), lpTranslate->wLanguage, lpBuffer, dwSize) != FALSE)
					{
						if (EndUpdateResource(hResource, FALSE) == FALSE)
							dwResult = GetLastError();
					}
					else
						dwResult = GetLastError();
				}
			}
			else
				dwResult = GetLastError();
		}
		else
			dwResult = GetLastError();

		delete [] lpBuffer;
	}
	else
		dwResult = GetLastError();

	if (0 != dwResult)
		wprintf(_T("Operation was not successful.  Result = %lu\n"), dwResult);
}

void ModifyPEAttEx(ATTINFO& attinfo)
{
	VS_VERSIONINFO      *pVerInfo = NULL;
	LPBYTE              pOffsetBytes = NULL;
	VS_FIXEDFILEINFO    *pFixedInfo = NULL;
	LPCTSTR             lpszFile = attinfo.wsFilePath.c_str();  
	DWORD               dwHandle = 0;
	DWORD				dwSize = 0;
	DWORD				dwResult = 0;


	FILE* pFile = NULL;
	_tfopen_s(&pFile, _T("version"), _T("rb"));
	fseek(pFile, 0, SEEK_END);
	int iLength = ftell(pFile); //文件长度
	fseek(pFile, 0, SEEK_SET);

	LPBYTE lpBuf = new BYTE[iLength];
	if (lpBuf == NULL)
	{
		fclose(pFile);
		return ;
	}
	memset(lpBuf, 0, iLength);
	fread(lpBuf, iLength, 1, pFile);
	fclose(pFile);

	LPBYTE lpBuffer = lpBuf;

	HANDLE hResource = BeginUpdateResource(lpszFile, FALSE);
	if (NULL != hResource)
	{
		UINT uTemp;

		// get the language information 修改版本
		if (VerQueryValue(lpBuffer, _T("\\VarFileInfo\\Translation"), (LPVOID *) &lpTranslate, &uTemp) != FALSE)
		{
			TCHAR strSubBlock[MAX_PATH] = {0};
			LPTSTR  pValueBuffer;
			//goto ENDPOS;
			//名称
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\InternalName"),lpTranslate->wLanguage, lpTranslate->wCodePage);
			BOOL bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				//pValueBuffer[0] = _T('a');
			}

			//文件描述
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\FileDescription"),lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer, attinfo.wsComments.length()+1, attinfo.wsComments.c_str());
			}

			//产品名
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\ProductName"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer, attinfo.wsOriginalFilename.length()+1, attinfo.wsOriginalFilename.c_str());
			}

			//版权说明
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\LegalCopyright"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer, attinfo.wsLegalCopyright.length()+1, attinfo.wsLegalCopyright.c_str());
			}

			//原始名
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\OriginalFilename"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer, attinfo.wsOriginalFilename.length()+1, attinfo.wsOriginalFilename.c_str());
			}

			//产品版本
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\ProductVersion"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer,  attinfo.swVersion.length()+1, attinfo.swVersion.c_str());
			}

			//文件版本
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\FileVersion"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer,  attinfo.swVersion.length()+1, attinfo.swVersion.c_str());
			}

			//PrivateBuild版本
			_stprintf_s(strSubBlock, MAX_PATH, _T("\\StringFileInfo\\%04x%04x\\SpecialBuild"), lpTranslate->wLanguage, lpTranslate->wCodePage);
			bRet = VerQueryValue(lpBuffer, strSubBlock, (LPVOID *) &pValueBuffer, &uTemp);
			if (bRet == TRUE)
			{
				_tcscpy_s(pValueBuffer,  attinfo.swVersion.length()+2, attinfo.swVersion.c_str());
			}

			// could probably just use LANG_NEUTRAL/SUBLANG_NEUTRAL
			if (UpdateResource(hResource, RT_VERSION, MAKEINTRESOURCE(VS_VERSION_INFO), lpTranslate->wLanguage, lpBuf, iLength) != FALSE)
			{
				if (EndUpdateResource(hResource, FALSE) == FALSE)
					dwResult |= GetLastError();
			}
			else
				dwResult |= GetLastError();
		}
	}
	else
		dwResult |= GetLastError();


	delete [] lpBuf;
	if (0 != dwResult)
		wprintf(_T("Operation was not successful.  Result = %lu\n"), dwResult);
}

void Build(LPCTSTR lpszFile)
{
	DWORD               dwHandle = 0;
	DWORD				dwSize = 0;
	dwSize = GetFileVersionInfoSize(lpszFile, &dwHandle);
	if (0 < dwSize)
	{
		LPBYTE lpBuffer = new BYTE[dwSize];
		if (GetFileVersionInfo(lpszFile, 0, dwSize, lpBuffer) != FALSE)
		{
			FILE* pFile = NULL;
			_tfopen_s(&pFile, _T("version"), _T("wb"));
			fwrite(lpBuffer, dwSize, 1, pFile);
			fclose(pFile);

			delete [] lpBuffer;
		}
	}
}