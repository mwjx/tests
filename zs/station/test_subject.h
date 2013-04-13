//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:测试类头文件
//------------------------------
#include "observer.h"
class c_station;
class c_observer;
class c_ref :public c_observer
{
public:
	c_ref(void);
	~c_ref(void);
	void update(int,int);
	void run(void);
private:
	int a;
	c_station *p_st;
//	c_observer *p_ob;
};
class c_res :public c_observer
{
public:
	c_res();
	~c_res(void);
	void update(int,int);
private:
	int a;
	c_station *p_st;
//	c_observer *p_ob;
};

