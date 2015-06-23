// glog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <glog/logging.h>  

int _tmain(int argc, _TCHAR* argv[])
{

	FLAGS_log_dir = "D:\\glog";
	google::InitGoogleLogging("abc.exe");
	LOG(INFO) << "我在InitInstance()";   // 记录一个INFO等级的日志"我在InitInstance()"
	google::ShutdownGoogleLogging(); 

	return 0;
}

