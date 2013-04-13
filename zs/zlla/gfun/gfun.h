//------------------------------
//create time:2012-1-20
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:常用函数集
//------------------------------
#ifndef _GFUN_H
#define _GFUN_H
#include <sstream>
#include <map>
#include <vector>
#include <set>
//#include "../include/frand.h"
typedef std::vector<std::string> tp_vs;
typedef std::set<int> tp_si;
typedef std::map<int,int> tp_ii;
typedef std::vector<int> tp_vi;
class c_gfun
{
public:
	static c_gfun* instance(void); //取惟一实例(取代构造)
	void release(void); //取代析构函数

	int split_str(const char * const,char); //拆分字符串
	int get_val(void); //取列表值
	const char * get_str(void); //取列表值字符串
	const char * join(tp_si &,char); //组合连结列表
	const char * join(tp_vi &,char); //组合连结列表
	//inline int get_rand(void){return ra.rand();} //随机数
	void split_str(const char *,std::string &,tp_vs &); //拆分字符串

	void tests(void);
protected:
	c_gfun(void);
	~c_gfun(void);
private:
	static c_gfun* _instance;
	int ref_count; //被引用计数
	std::stringstream ss;  //临时字符串格式流
	tp_vs lsre; //字符串列表
	int nore; //列表的当前下标
	//随机数对象，线性同余方式的生成器，默认参数为了16807生成器
	//randomizer ra; 

	inline int get_ref(void) const { return ref_count;}
	inline void add_ref(void){ ++ ref_count;}
	inline void sub_ref(void){ -- ref_count;}

};
#endif
