//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:广播站，通知中心
//------------------------------
#include "cmdif.h"
#include <iostream>
#include <ctime>
#include "log_writer.h"
//#include <fstream>
using namespace std;
//-------------------c_cmdif------------
c_cmdif* c_cmdif::_instance = NULL;
c_cmdif* c_cmdif::instance(void)
{
	//取惟一实例(取代构造)
	//cerr << "c_cmdif::instance" << endl;
	if(NULL == _instance)
		_instance = new c_cmdif();
	_instance->add_ref();
	return _instance;
}
void c_cmdif::release(void)
{
	//取代析构函数
	//cerr << "c_cmdif::release,ref_count=" << ref_count << endl;
	sub_ref();
	//cerr << "sub_ref=" << ref_count << endl;
	if(get_ref() > 0)
		return;
	//cerr << "delete _instance" << endl;
	delete _instance;
	_instance = NULL;
}
c_cmdif::c_cmdif()
{
	//cerr << "c_cmdif" << endl;
	ref_count = 0;
	mp.clear();
}
c_cmdif::~c_cmdif()
{
	//cerr << "~c_cmdif" << endl;
}
void c_cmdif::attach(int t,c_basecmd *p)
{
	//订阅
	if(mp.end()==mp.find(t)){
		mp.insert(tp_ic::value_type(t,p));
	}
	else{
		mp[t] = p;
	}
}
void c_cmdif::detach(int t)
{
	//退订
	assert(mp.end()!=mp.find(t));
	mp.erase(t);
}
int c_cmdif::notify(int room,int cli,int cmd,const char *arg)
{
	//通知
	//输入:room房间,cli用户,cmd指令,arg参数
	//输出:>=0成功,<0失败
	if(mp.end()==mp.find(cmd)){return -1;}
	return mp[cmd]->cmd(room,cli,cmd,arg);
	//mp[cmd]->update(room,cli);
	//return 0;
}

