//------------------------------
//create time:2012-7-23
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:时钟
//------------------------------
#include <iostream>
#include <cassert>
#include "tm.h"
#include <cerrno>
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib" )
#else
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif
#include "mutex.h"
using namespace std;

c_tm* c_tm::_instance = NULL;
c_tm* c_tm::instance(void)
{
	if(NULL == _instance){_instance = new c_tm;}
	_instance->add_ref();
	return _instance;
}
void c_tm::release(void)
{
	sub_ref();
	if(get_ref() > 0){return;}
	delete _instance;
	_instance = NULL;
}
c_tm::c_tm(void):tm_ct(0),_fd(-1),blnrun(false),pmf(NULL),pf_arg(NULL)
{
	//cout << "c_tm::c_tm" << endl;
	ref_count = 0;
#ifdef _WIN32
	WSADATA wsd;
	if(WSAStartup(MAKEWORD(2,2),&wsd) != 0){assert(0);return;}
	_fd = empty_sock();
#endif	
	mt_tm = new c_mutex();
}
c_tm::~c_tm(void)
{
	//cout << "c_tm::~c_tm" << endl;
	delete mt_tm;
#ifdef _WIN32
	WSACleanup();
#endif
}
void c_tm::tests(void)
{
	//测试
	//输入:无
	//输出:无
	cout << "时钟测试" << endl;
	run(30);
}
void c_tm::run(int val)
{
	//运行时钟
	//输入:val秒数
	//输出:无
	if(blnrun){return;}
	blnrun = true;
#ifdef _WIN32
	assert(_fd>0);
#endif
	int re = -1;
	fd_set efds;
	static struct timeval TimeOut;
	for(;;){
		//select(0,NULL,NULL,NULL,&TimeOut);
		TimeOut.tv_sec = val;
		TimeOut.tv_usec = 0;  //1秒
#ifdef _WIN32
		FD_ZERO(&efds);
		FD_SET(_fd,&efds);
		re = select(0,NULL,NULL,&efds, &TimeOut);
#else
		re = select(0,NULL,NULL,NULL, &TimeOut);
#endif
		assert(-1!=re);
		//cout << "runtime:" << time(NULL) << endl;
		//if(NULL!=pmf){(*pmf)(pf_arg);}
		run_task();
		//mt_tm->bc();
//		cout << "tm_ct=" << (++tm_ct) << ",re=" << re << ",errno=" << errno << endl;
//		//if(-1==re){
//		fprintf(stderr, "error!%s\n", strerror(errno));
//		cout << "no=" << WSAGetLastError() << endl;
//		break;
	}
}
void c_tm::run_task(void)
{
	//运行任务表
	//输入:无
	//输出:无
	int len = vc_task.size();
	for(int i=0;i<len;++i){
		if(NULL==vc_task[i].p){continue;}
		(*(vc_task[i].p))(vc_task[i].arg);
	}
}
void c_tm::cancel_cb(int no)
{
	//取消任务
	//输入:no下标
	//输出:无
	int len = vc_task.size();
	if(no<0 || no>=len){return;}
	vc_task[no].p = NULL;
	vc_task[no].arg = NULL;
}
int c_tm::reg_cb(void (*func)(void *),void *ptr)
{
	//注册返回响应
	//输入：
	//输出:下标
	int no = no_empty();
	assert(-1!=no);
	vc_task[no].p = func;
	vc_task[no].arg = ptr;
//	pmf = func;
//	pf_arg = ptr;
}
int c_tm::no_empty(void)
{
	//任务表空下标
	//输入:无
	//输出:下标:0-?
	int no = -1;
	int len = vc_task.size();
	for(int i=0;i<len;++i){
		if(NULL==vc_task[i].p){return i;}
	}
	//新增记录
	tm_task_t tmp = {NULL,NULL};
	vc_task.push_back(tmp);
	return len;
}
int c_tm::empty_sock(void)
{
	//创建空白套接字
	//输入:无
	//输出:socket的ID,异常返回-１
	int sockfd; //portnumber=80,
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) { 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		return -1; 
	} 
	return sockfd;
}



