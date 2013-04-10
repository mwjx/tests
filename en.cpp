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
#include "tm.h"
#include <algorithm>
using namespace std;
const int NUM_OPT = 4; //选项数
//const int NUM_SIT = 5; //座位数
const int MIN_SITMONEY = 20; //最小上桌钱
const int MAX_SITMONEY = 100; //最大上桌钱
const int SIG_MONEY = 1; //单注
const int CLICK_MONEY = 10; //选金上限
const int NUM_CARD = 80; //词数
//const int TM_TOP = 3600; //每小时更新排行
//const int NUM_TOP = 10; //前n名有奖
//bool is_eque(top_score a,int u){return (a.u==u);}
//bool is_lit(top_score a,top_score b){return (a.v<b.v && a.u!=b.u);}
void _tm_en(void* ptr)
{
	AF *pa = static_cast<AF *>(ptr); // 强制转换 p 为 A* 
	c_en *ph = pa->p; // 从A中析取Hack对象地址
	void (c_en::*pmf)(void)=pa->pmf; //析取 ptr 到成员函数
	(ph->*pmf)(); // 调用成员函数
}

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
c_en::c_en(void):ref_count(0),roomen(534),pool(0),nowno(0),blnrun(false)
{
	vi_opt.reserve(NUM_OPT);
	vi_opt.resize(NUM_OPT,-1);
	vs_sits.reserve(NUM_SIT);
	vs_sits.resize(NUM_SIT);
	vi_ls.reserve(NUM_CARD);
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
	p_if->attach(2067,this); //坐下
	p_if->attach(2071,this); //站起
	p_if->attach(2079,this); //答题
	p_tm = c_tm::instance();
	a1.p = this;
	a1.pmf = &c_en::ques;
	no_tm = p_tm->reg_cb(&_tm_en,&a1);
	
	//tests();
}
c_en::~c_en(void)
{
	assert(-1!=no_tm);
	p_tm->cancel_cb(no_tm);
	no_tm = -1;
	p_tm->release();
	p_if->detach(2079);
	p_if->detach(2071);
	p_if->detach(2067);
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
	req_down(123,"0");
	rash();
	print(vi_ls);
	ques();
}
int c_en::tsf_sitbyuid(int u)
{
	//根据uid查座位号
	//参数:u用户
	//返回:座位号,-1无座位
	if(u<1){return -1;}
	for(int i =0;i<NUM_SIT;++i){
		if(u==vs_sits[i].u){return i;}
	}
	return -1;
}
int c_en::tsf_enough(int u)
{
	//用户钱是否够
	//参数:u用户
	//返回:0钱不够,>0上桌钱数
	int v = p_level->get_vals(15,u);
	if(v<MIN_SITMONEY){return 0;}
	return (v>=MAX_SITMONEY)?MAX_SITMONEY:MIN_SITMONEY;
}
int c_en::tsf_sit2user(int no,int u)
{
	//桌子钱到用户
	//参数:no座号,u用户
	//返回:0成功,-1失败
	if(vs_sits[no].money<1){return -1;}
	int v = p_level->get_vals(15,u);
	v += vs_sits[no].money;
	p_level->set_vals(15,u,v);
	vs_sits[no].money = 0;
	return 0;
}
int c_en::tsf_user2sit(int u,int no)
{
	//用户钱到桌子
	//参数:u用户,no座号
	//返回:0成功,-1失败
	p_level->set_vals(15,u,MAX_SITMONEY*100);
	int v = p_level->get_vals(15,u);
	if(v<MIN_SITMONEY){return -1;}
	int sub = (v>=MAX_SITMONEY)?MAX_SITMONEY:MIN_SITMONEY;
	p_level->set_vals(15,u,(v-sub));
	vs_sits[no].money = sub;
	return 0;
}
void c_en::req_up(int cli,const char *arg)
{
	//站起
	//参数:cli客户,arg座位号
	//返回:无
	//cout << "c_en::req_up,cli=" << cli << ",arg=" << arg << endl;
	int ruid = p_ul->uidbycid(cli);
	if(ruid<1){return;}
	//cout << "req_up,111" << endl;
	int no = atoi(arg);
	//位置是否存在
	if(no<0 || no>=NUM_SIT){return;}
	//cout << "req_up,222" << endl;
	//座位是否有人
	//请求者是否在些座位
	if(tsf_sit_uid(no)!=ruid){return;}
	//cout << "req_up,333" << endl;
	//踢人
	clear_sit(no);
}
void c_en::clear_sit(int no)
{
	//踢人
	//参数:no座号
	//返回:无
	//前置保证no有效
	int u = tsf_sit_uid(no);
	//cout << "req_up,clear_sit,no=" << no << ",u=" << u << endl;
	//转钱到身上
	if(0!=tsf_sit2user(no,u)){return;}
	//cout << "req_up,444" << endl;
	//座位清空
	tsf_set_sit(no,1,0);
	tsf_set_sit(no,2,0);
	//cout << "req_up,555" << endl;
	//状态信号
	tsf_up_state();
	//广播座号到个人
	int cli = p_ul->cidbyuid(u);
	//cout << "req_up,666" << endl;
	//rsp_down(cli,no);
	rsp_down(cli,-1);
	//广播座位信息到房间
	bc_sitinfo(no);
}
void c_en::req_down(int cli,const char *arg)
{
	//坐下
	//参数:cli客户,arg座位号:0-4
	//返回:无
	//cout << "req_down,cli=" << cli << endl;
	int ruid = p_ul->uidbycid(cli);
	if(ruid<1){return;}
	//cout << "req_down,111" << endl;
	int no = atoi(arg);
	//位置是否存在
	if(no<0 || no>=NUM_SIT){return;}
	//cout << "req_down,222" << endl;
	//位置已经有人
	if(tsf_sit_uid(no)>0){return;}
	//cout << "req_down,333" << endl;
	//请求者是否在房间,略
	//请求者是否已坐下
	if(-1!=tsf_sitbyuid(ruid)){return;}
	//cout << "req_down,444" << endl;
	//请求者是否有赌资//移赌资
	if(0!=tsf_user2sit(ruid,no)){return;}
	//cout << "req_down,555" << endl;
	//坐下
	tsf_down(no,ruid);
	//状态信号
	tsf_up_state();
	//广播结果消息到请求者
	rsp_down(cli,no);
	//广播座位信息到房间
	bc_sitinfo(no);
}
void c_en::inroom(int cli)
{
	//进房
	//输入:cli客户
	//输出:无
	p_ul->set_room(cli,roomen);
	int ruid = p_ul->uidbycid(cli);
	int mysit = tsf_sitbyuid(ruid);
	rsp_down(cli,mysit);
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
void c_en::bc_sitinfo(int no)
{
	//座位信息
	//参数:no座号
	//返回:无
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	string tmp;
	p_level->get_name(vs_sits[no].u,tmp);
	stmp << no << "," << vs_sits[no].money << "," << tmp;
	p_bl->add_bc(4,roomen,2070,stmp.str().c_str(),roomen); //房间	
}
void c_en::bc_pool(void)
{
	//彩池信息广播
	//参数:无
	//返回:无
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	stmp << pool;
	p_bl->add_bc(4,roomen,2074,stmp.str().c_str(),roomen); //房间	
}
void c_en::bc_sitmoney(int no)
{
	//座位钱广播
	//参数:no座位下标
	//返回:无
	assert((no>=0 && no<vs_sits.size()));
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	stmp << no << "_" << vs_sits[no].money;
	p_bl->add_bc(4,roomen,2078,stmp.str().c_str(),roomen); //房间	
}
void c_en::bc_sitmoney(void)
{
	//座位钱广播
	//参数:无
	//返回:无
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	for(int i = 0;i<vs_sits.size();++i){
		if(vs_sits[i].u<1){continue;}
		if(!stmp.str().empty()){stmp << ",";}
		stmp << i << "_" << vs_sits[i].money;
	}
	p_bl->add_bc(4,roomen,2078,stmp.str().c_str(),roomen); //房间	
}
void c_en::bc_ques(void)
{
	//题目广播
	//参数:无
	//返回:无
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	stmp << nowno;
	for(int i = 0;i<vi_opt.size();++i){
		stmp << "," << vi_opt[i];
	}
	p_bl->add_bc(4,roomen,2076,stmp.str().c_str(),roomen); //房间	
}

void c_en::rsp_down(int cli,int no)
{
	//坐下响应
	//参数:cli客户,no座号
	//返回:无
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	stmp << no;
	p_bl->add_bc(1,cli,2068,stmp.str().c_str(),0); //私人
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
void c_en::ques(void)
{
	//出题//定时器调用
	//参数:无
	//返回:无
	//cout << "c_en::ques" << endl;
	//不在运行中
	if(!blnrun){return;}
	//扣所有座位单注
	//扣注失败，踢出
	int count = 0;
	for(int i=0;i<NUM_SIT;++i){
		if(vs_sits[i].u<1){continue;}
		if(vs_sits[i].money<SIG_MONEY){
			clear_sit(i);
			continue;
		}
		vs_sits[i].money-=SIG_MONEY;		
		count += SIG_MONEY;
	}
	//cout << "count=" << count << endl;
	//注数合计是否为0
	if(count<1){return;}
	//加注到彩池
	pool += count;
	//取题目及选项
	if(vi_ls.size()<NUM_OPT){rash();}
	vi_opt.clear();
	for(int i=0;i<NUM_OPT;++i){
		vi_opt.push_back(vi_ls.back());
		vi_ls.pop_back();
	}
	//设题目
	srand((unsigned int)time(NULL));
	nowno = vi_opt[rand()%NUM_OPT];
	//清空答题标识
	si_ed.clear();
	//广播彩池到房间
	bc_pool();
	//广播题目到房
	bc_ques();
	//广播座位钱到房
	bc_sitmoney();
	//cout << "end,nowno=" << nowno << endl;
}
void c_en::rash(void)
{
	//洗出一副牌
	//参数:无
	//返回:无
	srand((unsigned int)time(NULL));
	for(int i =0;i<NUM_CARD;++i){
		vi_ls.push_back(i);
	}

	//乱序
	int key,val;
	for(int i =0;i<vi_ls.size();++i){
		key = rand()%NUM_CARD;
		val = vi_ls[key];
		vi_ls[key] = vi_ls[i];
		vi_ls[i] = val;
	}
}
void c_en::print(tp_vi &tmp)
{
	for(int i=0;i<tmp.size();++i){
		cout << tmp[i] << ",";
	}
	cout << endl;
}
void c_en::tsf_up_state(void)
{
	//刷新运行状态
	//参数:无
	//返回:无
	for(int i=0;i<NUM_SIT;++i){
		if(vs_sits[i].u>0){
			blnrun = true;
			return;
		}
	}
	blnrun = false;
}
void c_en::click(int cli,int no)
{
	//答题
	//参数:cli客户,no选项下标(0-3)
	//返回:无
	if(no<0 || no>=NUM_OPT){return;}
	//不在运行中
	if(!blnrun){return;}
	//已答对
	if(-1==nowno){return;}
	//用户无效
	int ruid = p_ul->uidbycid(cli);
	if(ruid<1){return;}
	//不是座位用户
	int mysit = tsf_sitbyuid(ruid);
	if(-1==mysit){return;}
	//本轮已答
	if(si_ed.end()!=si_ed.find(ruid)){return;}
	//设答题标识
	si_ed.insert(ruid);
	//彩池变动变量
	bool blnpool = false;
	//是否够选金
	int need = pool>CLICK_MONEY?CLICK_MONEY:pool;
	int v = vs_sits[mysit].money; //p_level->get_vals(15,ruid);
	//扣钱
	if(v>=need){
		blnpool = true;
		pool += need;
		v -= need;
		vs_sits[mysit].money = v; //p_level->set_vals(15,ruid,v);
	}
//	//正确词号
//	int word = vi_opt[no];
	//是否正确
	//正确获奖移钱,答案置-1
	bool blnok = false; //是否答对
	if(blnpool && nowno==vi_opt[no]){
		blnok = true;
		vs_sits[mysit].money += pool;
		pool = 0;
		nowno = -1;
	}
	if(blnpool){
		//广播彩池到房
		bc_pool();
		//座位钱到房
		bc_sitmoney(mysit);
	}
	//选择和结果到房
	bc_click(blnok,mysit,no);
}
void c_en::bc_click(bool bln,int sit,int no)
{
	//广播结果
	//参数:bln结果,sit座位号0-4,no选项0-3
	std::stringstream stmp;  //临时字符串格式流
	stmp.str("");
	stmp.clear();
	stmp << (bln?"Y":"N") << "," << sit << "," << no;
	p_bl->add_bc(4,roomen,2080,stmp.str().c_str(),roomen); //房间	
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
	case 2067: //坐下
		req_down(cli,arg);
		break;
	case 2071: //站起
		req_up(cli,arg);
		break;
	case 2079: //答题
		click(cli,atoi(arg));
		break;
	default:
		break;
	}
	return 0;
}





