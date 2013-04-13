//------------------------------
//create time:2012-7-23
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:时钟
//------------------------------
#include "tm.h"
#include <iostream>
#include <string>
#include <sstream>
//#include "../smpthread/smpthread.h"
using namespace std;
//void deal_cmd(int cmd,const char * const arg,int r); //处理响应
int main(int argc, char *argv[])
{
	c_tm *p_tm = c_tm::instance();
	p_tm->tests();
	p_tm->release();
	return 0;
}


