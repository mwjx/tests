//------------------------------
//create time:2012-1-20
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:常用函数集
//------------------------------
#include <iostream>
#include <cassert>
#include "gfun.h"
#include <ctime>
#include <math.h>
using namespace std;

c_gfun* c_gfun::_instance = NULL;
c_gfun* c_gfun::instance(void)
{
	if(NULL == _instance)
		_instance = new c_gfun;
	_instance->add_ref();
	return _instance;
}
void c_gfun::release(void)
{
	sub_ref();
	if(get_ref() > 0)
		return;
	delete _instance;
	_instance = NULL;
}
c_gfun::c_gfun(void)
{
	ref_count = 0;
	
	lsre.clear();
	nore = -1;
	
}
c_gfun::~c_gfun(void)
{
}
void c_gfun::tests(void)
{
	//测试
	//输入:无
	//输出:无
	cerr << "通用函数集合测试" << endl;
//	//随机
//	cout << "随机数=" << get_rand() << endl;
//	//组合
//	tp_si ols;
//	for(int i=0;i<10;++i)
//		ols.insert(i);
//	cout << join(ols,',') << endl;
//	//拆分
	string ls = string("200200067_200400232_-1_66480");
//	//,66716,66789,66826,67249,67252,67263,67312,67318,67340,67341,67649,67868,68389,68461,69045,69093,69101,69118,69245,69320,69377,70402,70448,70449,70452,70455,70479,70482,70486,70488,70489
	if(4!=split_str(ls.c_str(),'_'))
		return;
	int uid = get_val();
	int cid = get_val();
	int no = get_val();
	cout << "uid=" << uid << ",cid=" << cid << ",no=" << no << endl;
//	const char *sp = get_str();
//	assert(NULL!=sp);
//	string idls = string(sp);
//	cout << "idls:" << idls << endl;
//	int len = split_str(idls.c_str(),',');
//	cout << "len=" << len << endl;
//	int oid;
//	for(;;){
//		if((oid=get_val())<1)
//			break;
//		cout << "oid=" << oid << endl;
//	}
}
const char * c_gfun::get_str(void)
{
	//取列表值字符串
	//输入:无
	//输出:值,异常返回NULL
	if(nore<0||nore>=lsre.size())
		return NULL;
	return (lsre[nore++].c_str());
}
int c_gfun::get_val(void)
{
	//取列表值
	//输入:无
	//输出:值,异常返回-1
	//cout << "get_val,nore=" << nore << endl;
	if(nore<0||nore>=lsre.size())
		return -1;
	//cout << "lsre[nore]:" << lsre[nore] << ",val=" << atoi(lsre[nore].c_str()) << endl;
	return atoi(lsre[nore++].c_str());
}
int c_gfun::split_str(const char * const ls,char k)
{
	//拆分字符串
	//输入:ls要拆分的字符串,k分隔符
	//输出:字段数,异常返回-1
	lsre.clear(); //清空结果列表
	nore = 0; //下标初始
	string s;
	ss.clear();
	ss.str(ls);
	while(getline(ss,s,k)){
		//cout << "s:" << s << endl;
		lsre.push_back(s);
	}
	//cout << "lsre.size()=" << lsre.size() << endl; 
	return lsre.size();
}
const char * c_gfun::join(tp_si &ls,char k)
{
	//组合连结列表
	//输入:ls列表,k分隔符
	//输出:字符串
	ss.str("");
	ss.clear();
	tp_si::iterator it;
	for(it=ls.begin();it!=ls.end();++it){
		if(!ss.str().empty())
			ss << k;
		ss << *it;
	}
	return ss.str().c_str();
}
const char * c_gfun::join(tp_vi &ls,char k)
{
	//组合连结列表
	//输入:ls列表,k分隔符
	//输出:字符串
	ss.str("");
	ss.clear();
	tp_vi::iterator it;
	for(it=ls.begin();it!=ls.end();++it){
		if(!ss.str().empty())
			ss << k;
		ss << *it;
	}
	return ss.str().c_str();
}
void c_gfun::split_str(const char *str,string &ls,tp_vs &out)
{
	//拆分字符串
	//输入:str分隔符,ls源字符串，out输出列表，前置保证清空
	//输出:无
	//ls = string("327:4127,1163;328:417,163;");
	//cerr << "ls:" << ls << endl;
	size_t pos=0;
	size_t end=0;
	int ss = strlen(str);
	for(;;){
		if(string::npos == end){break;}
		//end = ls.find_first_of(str,pos);
		end = ls.find(str,pos);
		if(string::npos == end){ //last
			if((ls.length()-pos)>=0){out.push_back(ls.substr(pos));}
			pos = end;
		}
		else{
			if((end-pos) < 0){assert(0);}
			//if((end-pos)>0) //会有空的情况，不要加这个
			out.push_back(ls.substr(pos,(end-pos)));
			pos = end+ss;
		}
	}
}





