一,2013-08-05
二,2013-08-06
//写入广播,19:00
//成功注册,18:00
//失败注册
//失败登录,17:30
//成功登录,17:00
//登录请求处理,deal_cmd,17:00
//请求结构
//响应结构
//请求环境,16:30
//处理消息框架,14:00-16:00
//旧有登录流程,14:00-15:00
//框架整理
//粘包处理
//bytes==-1处理
//git工作机
//登录流程


三,2013-08-07
//压入环境,10:30
//打包压入广播表,11:00
//push_bc函数,11:00
//get_yemore,11:40
//push_wirte,12:00
//取广播表写入,12:00
//检查广播流程,12:00
//广播系统,流程检查,14:00
//注册登录
//注册
//登录测试,15:30
//登录失败,15:30
//文件框架,测试环境,16:00
//订阅配对请求,16:30
//定义配对消息
//处理配对请求,17:00
//配对
//安装配对对象,17:30
//定义消息　
//定义消息
//提交参数,18:00
//处理消息
//订阅消息
//调用函数
//列表函数
//游戏逻辑实现
//广播战斗列表,19:00
//列表排错

四,2013-08-08
工作机环境
git:配置,ci,up
安装cvs
安装ssh
mysql
安装gcc套件
测试全部逻辑


老高  13:50:28
 279323376

五,2013-08-09
内网服务器环境安装



2013-09
record服务器
login/dispatch服务器



注册登录请求:
id(4),用户名(32)
注册登录响应:
id(4),返回码(4)

IP Address. . . . . . . . . . . . : 192.168.16.174
MDEF["port"] = 8091;

包格式:包头(1),父命令(1),子命令(2),包长(4),包体
