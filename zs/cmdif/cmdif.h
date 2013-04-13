//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:广播站，通知中心
//------------------------------
#ifndef _CMDIF_H
#define _CMDIF_H
#include <map>
//#include <set>
#include "basecmd.h"
//using namespace std;
typedef std::map<int,c_basecmd *> tp_ic;

class c_cmdif
{
	//电台
public:
	static c_cmdif* instance(void); //取惟一实例(取代构造)
	void release(void); //取代析构函数
	void attach(int,c_basecmd *); //订阅
	void detach(int); //退订
	int notify(int,int,int,const char *); //通知接口:类型,值(-1默认)
protected:
	c_cmdif();
	~c_cmdif();
private:
	static c_cmdif* _instance;
	int ref_count; //被引用计数
	tp_ic mp; //订阅列表

	inline int get_ref(void) const { return ref_count;}
	inline void add_ref(void){ ++ ref_count;}
	inline void sub_ref(void){ -- ref_count;}
};


#endif


