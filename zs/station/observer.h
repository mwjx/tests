//------------------------------
//create time:2011-6-8
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:观察者,收音机
//加入一个观察者7步---------------记住要在具体观察者对象中实现update接口
//1.：.h文件加上类声明如class c_ref; //测试类1
//2.：.h文件多态构造函数声明如c_observer(c_ref * const);
//3.：.h文件变量声明如c_ref *p_ref;
//4.：.h文件变量初始为NULL值，init(void)
//5.：.cpp文件包含头文件如#include "../class_gameserver.h";
//6.：.cpp文件多态构造实现如c_observer(c_ref * const p){init();p_ref=p;}
//7.：.cpp文件接口挂载如update(int t,int val)
//------------------------------
#ifndef C_OBSERVER_H
#define C_OBSERVER_H
//#include <stdio.h>

//class c_ref; //测试类1
//class c_res; //测试类2
//class c_gameserver; //游戏服务器
//class c_small_world; //小千世界
//class c_res_mg; //资源管理
//class c_fight; //战斗相关
//class c_uinfo; //用户信息对象
//class c_make; //炼制对象
//class c_skill; //技能对象
class c_observer
{
	//观察者，收音机
	//事件类型定义:
	//1物件从小千世界列表中删除，正式删除前通知/2两秒心跳通知/3心跳通知60秒粗略/
	//4进入房间前请求房间数据7001指令,值为用户ID/
	//5一刻钟心跳/6半小时心跳/7小时心跳/8天心跳/
	//9移动结束/
	//10新建筑完成/
	//11添加物件到内存完成/
	//12移动开始前/
	//13丢弃物品前/
	//14捡拾物品后/
	//15服务器初始完成/
	//16生命值变动/
	//17等级变动/
	//18战斗死亡前，包括玩家假死/
	//19渡劫成功/
	//20变身前/
	//21变身后/
	//22血上限变动/
	//23气上限变动/
	//24海上限变动/
	//25气速变动/
	//26攻增变动/
	//27防增变动/
	//28用户进入房间后/
	//29最小天劫片段心跳/
	//30渡劫失败/
	//31开始渡劫/
	//32使用物品或技能前/
	//33买物品资源后/
	//34卖物品资源后/
	//35玩家杀死了物件/
	//36玩家缴税后/
	//37玩家杀死了玩家/
	//38升大级完成/
	//39玩家创派/
	//40玩家完成任务/
	//41完成全部新手任务/
	//42创盟成功,uid/
	//43夺城成功,uid/
	//44登录成功,uid/
	//45退出游戏,uid/
	//46开启技能,uid/

	//卡牌通知
	//101完成关卡,uid/
	//102增加卡牌,uid/
	//103城战胜利,uid/
	//104开战通知,room/
	//105添加城战记录,city/
	//106领取宠物,uid/
	//107对战胜,uid/
	//108卡牌变动,uid/
	//109首次答对,英语,uid------------/
	//110答对10题,uid/

public:
//	c_observer(c_ref * const);
//	c_observer(c_res * const);
//	c_observer(c_gameserver * const);
//	c_observer(c_small_world * const);
//	c_observer(c_res_mg * const);
//	c_observer(c_fight * const);
//	c_observer(c_uinfo * const);
//	c_observer(c_make * const);
//	c_observer(c_skill * const);
	virtual ~c_observer(){};
	virtual void update(int,int)=0; //通知接口:类型,值(-1默认)
//	void update(int,int); //通知接口:类型,值(-1默认)

//	void tests(void);
protected:
	c_observer(){};
private:
//	c_ref *p_ref;
//	c_res *p_res;
//	c_gameserver *p_gms;
//	c_small_world *p_small;
//	c_res_mg *p_res_mg;
//	c_fight *p_fight;
//	c_uinfo *p_uinfo;
//	c_make *p_make;
//	c_skill *p_skill;

//	inline void init(void){p_ref=NULL;p_res=NULL;p_gms=NULL;p_small=NULL;p_res_mg=NULL;p_fight=NULL;p_uinfo=NULL;p_make=NULL;p_skill=NULL;}
};

#endif


