//------------------------------
//create time:2012-12-26
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:升级属性技能
//------------------------------
#ifndef _EN_H
#define _EN_H
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <ctime>
#include "../cmdif/basecmd.h"
typedef std::vector<int> tp_vi;
/*
using namespace std;
//typedef list<top_score> tp_lt;
typedef set<int> tp_si;

//class c_global_sql;
//class c_mysql;
class c_gas; //集气
class c_bc; //变动广播
class c_conf; //配置
class c_gfun; //通用函数集
class c_cinfo; //类信息
*/
class c_level;
class c_userlist; //在线
class c_broadcastlist;
class c_cmdif; //指令接口
class c_en :public c_basecmd //: public c_observer
{
public:
	static c_en* instance(void); //取惟一实例(取代构造)
	void release(void); //取代析构函数
	int cmd(int room,int cli,int cmd,const char *arg); //指令	

	void tests(void);
protected:
	c_en(void);
	~c_en(void);
private:
	static  c_en* _instance;
	int ref_count; //被引用计数
	int roomen; //房间号
	std::stringstream ss;  //临时字符串格式流
	int pool; //彩池
	int nowno; //当前题目词号
	tp_vi vi_opt; //选项
	struct tp_sit{
		int u; //用户ID
		int money; //积分
	}; //座位
	const static int NUM_SIT = 5; //座位数
	typedef std::vector<tp_sit> tp_vs;
	tp_vs vs_sits; //座位表
	/*
	int max_userlv; //用户等级上限
	tp_si si_att; //可升级属性代码
	c_gas *p_gas; //集气
	c_bc *p_bc; //变动广播对象
	c_conf *p_conf; //配置
	c_gfun *p_gfun; //通用函数
	c_cinfo *p_cinfo; //类信息
	*/
	c_level *p_level; //信息存取
	c_userlist *p_ul; //在线用户列表
	c_broadcastlist *p_bl; //广播
	c_cmdif *p_if; //指令接口

	void inroom(int cli); //进房
	void outroom(int cli); //出房
	void bc_init(int cli); //广播初始房间信息

	inline int get_ref(void) const { return ref_count;}
	inline void add_ref(void){ ++ ref_count;}
	inline void sub_ref(void){ -- ref_count;}

};
#endif
