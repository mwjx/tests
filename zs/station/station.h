//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:广播站，通知中心
//------------------------------
#ifndef C_STATION_H
#define C_STATION_H
#include <map>
#include <set>
#include "observer.h"
using namespace std;
typedef set<c_observer *> tp_obs;
typedef map<int,tp_obs> tp_io;

class c_station
{
	//电台
public:
	static c_station* instance(void); //取惟一实例(取代构造)
	void release(void); //取代析构函数
	void attach(int,c_observer *); //订阅
	void detach(int,c_observer *); //退订
	void notify(int,int); //通知接口:类型,值(-1默认)
protected:
	c_station();
	~c_station();
private:
	static c_station* _instance;
	int ref_count; //被引用计数
	tp_io ls; //订阅列表

	inline int get_ref(void) const { return ref_count;}
	inline void add_ref(void){ ++ ref_count;}
	inline void sub_ref(void){ -- ref_count;}
};


#endif


