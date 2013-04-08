//------------------------------
//create time:2012-8-21
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:通用配置
//------------------------------
#include <iostream>
#include <cassert>
#include "en.h"
//#include "../include/class_mysql.h"
//#include "../global_sql/global_sql.h"
#include "log_writer.h"
#include "../level/level.h"
#include "../gas/gas.h"
#include "../bc/bc.h"
#include "../class_userlist.h"
#include "../conf/conf.h"
#include "gfun.h"
#include "../map/cinfo.h"
#include "../class_broadcastlist.h"
#include "../cmdif/cmdif.h"
#include <algorithm>
using namespace std;
const int NUM_OPT = 4; //选项数
//const int TM_TOP = 3600; //每小时更新排行
//const int NUM_TOP = 10; //前n名有奖
//bool is_eque(top_score a,int u){return (a.u==u);}
//bool is_lit(top_score a,top_score b){return (a.v<b.v && a.u!=b.u);}
c_en* c_en::_instance = NULL;
c_en* c_en::instance(void)
{
	if(NULL == _instance){_instance = new c_en;}
	_instance->add_ref();
	return _instance;
}
void c_en::release(void)
{
	sub_ref();
	if(get_ref() > 0){return;}
	delete _instance;
	_instance = NULL;
}
c_en::c_en(void):ref_count(0),roomen(534),pool(0),nowno(0)
{
	vi_opt.resize(NUM_OPT,-1);
	vs_sits.resize(NUM_SIT);
	/*
//	p_gsql = c_global_sql::instance();
//	p_sql = p_gsql->get_sql();
	p_gas = c_gas::instance();
	p_bc = c_bc::instance();
	p_conf = c_conf::instance();
	p_gfun = c_gfun::instance();
	p_cinfo = c_cinfo::instance();
	*/
	p_level = c_level::instance();
	p_ul = c_userlist::instance();
	p_bl = c_broadcastlist::instance();
	p_if = c_cmdif::instance();
	p_if->attach(2063,this); //进房
	p_if->attach(2065,this); //退房
	//tests();
}
c_en::~c_en(void)
{
	p_if->detach(2065);
	p_if->detach(2063);
	p_if->release();
	p_bl->release();
	p_ul->release();
	p_level->release();
	/*
	p_cinfo->release();
	p_gfun->release();
	p_conf->release();
	p_bc->release();
	p_gas->release();
//	p_sql = NULL;
//	p_gsql->release();
	*/
}
void c_en::tests(void)
{
	//测试
	//输入:无
	//输出:无
	cerr << "英语多人房测试" << endl;
}
void c_en::inroom(int cli)
{
	//进房
	//输入:cli客户
	//输出:无
	p_ul->set_room(cli,roomen);
	bc_init(cli);
}
void c_en::outroom(int cli)
{
	//出房
	//输入:cli客户
	//输出:无
	p_ul->set_room(cli,0);
	//cout << "c_en::outroom,cli=" << cli << endl;
}
void c_en::bc_init(int cli)
{
	//广播初始房间信息
	//输入:cli客户
	//输出:无
	ss.str("");
	ss.clear();
	//彩池
	ss << pool << "`|" << nowno;
	//题目
	for(int i=0;i<NUM_OPT;++i){
		ss << "," << vi_opt[i];
	}
	//座位表
	ss << "`|";
	string tmp;
	for(int i=0;i<NUM_SIT;++i){
		if(0!=i){ss << ";";}
		tmp = string();
		p_level->get_name(vs_sits[i].u,tmp);
		ss << i << "," << vs_sits[i].money << "," << tmp;
	}
	//ss << u << "," << k << "," << next;
	p_bl->add_bc(1,cli,2064,ss.str().c_str(),0); //私人

}
int c_en::cmd(int room,int cli,int cmd,const char *arg)
{
	//指令
	//输入:room房间,cli客户,cmd指令,arg参数
	//输出:0成功/-1失败
	//cout << "c_reg::cmd,room=" << room << ",cli=" << cli << ",cmd=" << cmd << ",arg=" << arg << endl;
	switch(cmd){
	case 2063: //进房
		inroom(cli);
		break;
	case 2065: //出房
		outroom(cli);
		break;
	default:
		break;
	}
	return 0;
}





