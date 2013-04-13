//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:通知模式测试
//------------------------------
#include "observer.h"
#include "station.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "test_subject.h"
using namespace std;
int main(int argc, char *argv[])
{
	//通知模式
	cerr << "通知模式" << endl;
//	c_station *p_st = c_station::instance();
	c_ref o_ref = c_ref();
	c_res o_res = c_res();
	o_ref.run();
//	p_st->release();
	return 0;
}

c_ref::c_ref(void) //:ref(r)
{
	//cerr << "c_ref" << endl;
//	p_st = NULL;
	p_st = c_station::instance();
	//p_ob = new c_observer(this);
	p_st->attach(1,this);
}
c_ref::~c_ref(void)
{
	//cerr << "~c_ref" << endl;
	p_st->detach(1,this);
//	delete p_ob;
	p_st->release();
}
void c_ref::run(void)
{
	p_st->notify(1,-1);
	p_st->notify(2,123);
}
void c_ref::update(int t,int val)
{
	cerr << "c_ref update,t=" << t << ",val=" << val << endl;
}


c_res::c_res()
{
	//cerr << "c_res" << endl;
	p_st = c_station::instance();
//	p_ob = new c_observer(this);
	p_st->attach(1,this);
	p_st->attach(2,this);

	//p_ob = new c_observer(this);	
	//delete p_ob;
}
c_res::~c_res(void)
{
	//cerr << "~c_res" << endl;
	p_st->detach(2,this);
	p_st->detach(1,this);
//	delete p_ob;
	p_st->release();

}
void c_res::update(int t,int val)
{
	cerr << "c_res update,t=" << t << ",val=" << val << endl;
}


