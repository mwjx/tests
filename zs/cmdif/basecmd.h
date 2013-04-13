//------------------------------
//create time:2013-3-25
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:处理命令基类
//------------------------------
#ifndef C_BASECMD_H
#define C_BASECMD_H
class c_basecmd
{

public:
	c_basecmd(){};
	~c_basecmd(){};
	//virtual void update(int,int)=0; //通知接口:类型,值(-1默认)
	virtual int cmd(int,int,int,const char *)=0; //通知接口:类型,值(-1默认)
protected:
private:
};

#endif


