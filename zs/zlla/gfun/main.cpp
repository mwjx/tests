//------------------------------
//create time:2006-05-26
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:log_writer
//------------------------------
//#include <stdio.h>
#include "../../inc/gfun.h"
#include <iostream>
#include <string>
#include <vector>
//#include "../class_info/class_info.h"
//#include "../gb_convert/uni_table.h"
typedef std::vector<std::string> tp_vs;
using namespace std;
int main(int argc, char *argv[])
{
	//c_class_info *CI = c_class_info::instance("../conf_gms.ini");	
	//c_uni_table *p_gb = c_uni_table::instance(GP_CI->get_val("dirroot"));

	c_gfun *p = c_gfun::instance();
	//p->tests();
	//²ð·Ö
	string ls = string("200200067_200400232_-1_66480");
	if(4!=p->split_str(ls.c_str(),'_')){return 0;}
	int uid = p->get_val();
	int cid = p->get_val();
	int no = p->get_val();
	cout << "uid=" << uid << ",cid=" << cid << ",no=" << no << endl;
	//¸´·Ö¸ô
	tp_vs out;
	ls = string("1`|2`|");
	p->split_str("`|",ls,out);
	int len = out.size();
	cout << "out.size()=" << len << endl;
	for(int i=0;i<len;++i){
		cout << i << "=" << out[i] << endl;
	}

	p->release();

	//p_gb->release();
	//CI->release();
	return 0;
}

