// glog.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <glog/logging.h>  

int _tmain(int argc, _TCHAR* argv[])
{

	FLAGS_log_dir = "D:\\glog";
	google::InitGoogleLogging("abc.exe");
	LOG(INFO) << "����InitInstance()";   // ��¼һ��INFO�ȼ�����־"����InitInstance()"
	google::ShutdownGoogleLogging(); 

	return 0;
}

