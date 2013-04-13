//------------------------------
//create time:2012-7-23
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:定时器
//------------------------------
#ifndef _TM_H
#define _TM_H
//#include "../netdef.h"
//#include <string>
//#include <sstream>
#include <vector>
//产生秒表
//通知
class c_mutex;
typedef void (*pf)(void *); //函数指针
struct tm_task_t{
	pf p; //函数指针
	void *arg; //参数
};
//typedef std::vector<tm_task_t> tp_vt; 
class c_tm
{
public:
	static c_tm* instance(void); //取惟一实例(取代构造)
	void release(void); //取代析构函数
	void run(int); //运行时钟
	inline c_mutex *get_mt_tm(void){return mt_tm;} //定时锁
	int reg_cb(void (*func)(void *),void* ptr); //注册回调函数，注意结束清除
	void cancel_cb(int no); //取消任务
	
	void tests(void);
protected:
	c_tm(void);
	~c_tm(void);
private:
	static c_tm* _instance;
	int ref_count; //被引用计数
	int tm_ct;
	int _fd; //空白套接字
	c_mutex *mt_tm;
	bool blnrun;
	pf pmf;
	void *pf_arg;
	typedef std::vector<tm_task_t> tp_vt; 
	tp_vt vc_task; //任务表

	int empty_sock(void); //创建sock连接
	int no_empty(void); //任务表空下标
	void run_task(void); //运行任务表

	inline int get_ref(void) const { return ref_count;}
	inline void add_ref(void){ ++ ref_count;}
	inline void sub_ref(void){ -- ref_count;}

};
#endif
