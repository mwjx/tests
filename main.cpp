//--------等解决问题--------
/*
划线
IE
FF
*/
//#include <stdio.h>
#include <iostream>  
#include <time.h>  
#include <stdlib.h>  
#include <vector>
using namespace std;  
const int SIZE_CHAR = 32; //生成32 + 1位C Style字符串  
const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";  
typedef vector<int> tp_vi;
void print(tp_vi &tmp);
int main()  
{  
    srand((unsigned)time(NULL));  
    char ch[SIZE_CHAR + 1] = {0};  
    for (int i = 0; i < SIZE_CHAR; ++i)  
    {  
       int x = rand()%sizeof(CCH);     
       ch[i] = CCH[x];  
    }  
    cout <<ch <<"/n";        
    return 0;  
}  
void rash(void)
{
	srand((unsigned int)time(NULL));
	int num = 80;
	tp_vi vi_ls;
	vi_ls.reserve(num);
	for(int i =0;i<num;++i){
		vi_ls.push_back(i);
	}

	//乱序
	int key,val;
	for(int i =0;i<vi_ls.size();++i){
		key = rand()%num;
		val = vi_ls[key];
		vi_ls[key] = vi_ls[i];
		vi_ls[i] = val;
	}
}
void print(tp_vi &tmp)
{
	for(int i=0;i<tmp.size();++i){
		cout << tmp[i] << ",";
	}
	cout << endl;
}
void ques()
{
	//出题
	
	//定时器
	//不在运行中
	//扣所有座位单注
	//扣注失败，踢出
	//注数合计是否为0
	//加注到彩池
	//取题目及选项
	//设题目
	//清空答题标识
	//广播彩池到房间
	//广播题目到房
}
void click()
{
	//选择

	//不在运行中
	//不是座位用户
	//本轮已答
	//设答题标识
	//彩池变动变量
	//是否够选金
	//扣钱
	//是否正确
	//正确获奖移钱
	//广播彩池到房
	//座位钱到房
	//选择和结果到房
}
//数据类
//运行标识
//彩池
//题目，选项
//座位表
//牌堆
//每轮答题标识

//其他
//洗牌
//改变运行状态.遍历座位表
//踢出
/*int main(int argc, char *argv[])
{
	printf("Hello, world\n");
	
	return 0;
}
*/
/*
#include <iostream>  
#include <string>  
#include <vector>  
using namespace std;  
int main()  
{  
    string tmp1,tmp2;  
    tmp1="rusher;lewjan;bill;stan;yx;";  
    tmp2="abcc";  
    vector<string>list;  
    list.push_back(tmp1);  
    list.push_back(tmp2);  
    for (unsigned int i=0;i<list.size();i++)  
    {  
       cout<<list[i]<<endl;  
    }  
    return 0;  
}  
*/	

