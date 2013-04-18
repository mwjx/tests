//------------------------------
//create time:2013-3-29
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:游戏界面
//------------------------------
xinclude("view/feen.js",["view/fe.js","view/visits.js","view/stline.js","ctrl/taskmg.js"],"m_feen.init");
var m_feen = function(){
var dir = m_cofm.get_dimg();
var warea = 500,harea = 400; //480; //战场宽高
var rtx =0,rty = 0; //右顶点坐标
var wsm = MDEF["wsm"],hsm = MDEF["hsm"]; //640; //300; //小屏宽高
var btnstart = null; //开始按钮 
var mp_che = {}; //数据缓存:{w,h,ltx,lty}
var arropt = []; //选项列表
var pname1 = ["c1", "c2", "c3", "c4"]; //答对的反馈图案
var pname2 = ["w1", "w2", "w3", "w4"]; //答错的反馈图案
//"home/background.jpg"=>{id,w,h,x,y,evt[cmd,arg],sty,big,bigimg}
var mp_img = {}; 
//mp_img["en/bg_480_320.jpg"] = {"w":480,"h":320,"x":0,"y":0,"bigimg":"en/background.jpg","big":{"w":500,"h":400,"x":0,"y":0}}
mp_img["en/start.jpg"] = {"id":"divstart","w":97,"h":33,"x":370,"y":260,"big":{"x":0,"y":0},"evt":[432,0],"sty":"cursor:pointer;"}
mp_img["en/ppt_2.gif"] = {"id":"divhelp","w":24,"h":24,"x":330,"y":265,"evt":[434,0],"big":{"x":0,"y":0},"sty":"cursor:pointer;"}
var mp_div = {}; //id=>{x,y}
mp_div["info1"] = {"x":410,"y":10,"txt":"积分"};
mp_div["info2"] = {"x":430,"y":30,"txt":"0"};
mp_div["info3"] = {"x":410,"y":50,"txt":"题号"};
mp_div["info4"] = {"x":430,"y":70,"txt":"0"};
var mp_sty = {}; //id=>{x,y}
mp_sty["info5"] = {"x":63,"y":117,"txt":""};
mp_sty["item_area"] = {"x":121,"y":63};
mp_sty["opt1"] = {"x":73,"y":156};
mp_sty["opt2"] = {"x":73,"y":192};
mp_sty["opt3"] = {"x":73,"y":229};
mp_sty["opt4"] = {"x":73,"y":265};
mp_sty["feedback"] = {"x":124,"y":125};
mp_sty["end"] = {"x":100,"y":120};

function init()
{
	g_trace("feen.js,初始");
	make_face();
	btnstart = $$("divstart");
	arropt.push($$("opt1").childNodes[0].childNodes[1]);
	arropt.push($$("opt2").childNodes[0].childNodes[1]);
	arropt.push($$("opt3").childNodes[0].childNodes[1]);
	arropt.push($$("opt4").childNodes[0].childNodes[1]);
	m_visits.set_xy(rtx,rty);
	m_stline.load_data(mp_che["w"],mp_che["h"],mp_che["ltx"],mp_che["lty"]);
	//log_trace();
}
function tests(){}
function make_face()
{
	//生成界面
	init_mp();
	var sm = is_sm(); //是否小屏
	var arr = [];	
	var img,path;
	var sm = is_sm(); //是否小屏
	var ww = sm?wsm:warea; //比例
	var hh = sm?hsm:harea;
	var xy = get_xy();
	rtx = xy[0] + ww;
	rty = xy[1];
	mp_che["w"] = ww;
	mp_che["h"] = hh;
	mp_che["ltx"] = xy[0];
	mp_che["lty"] = xy[1];
	path = (dir+(sm?"en/bg_480_320.jpg":"en/background.jpg"));
	arr.push("<DIV id=\"full_en\" style=\"position:absolute;left:"+xy[0]+"px;top:"+xy[1]+"px;width:"+ww+"px;height:"+hh+"px;BACKGROUND: url("+path+") no-repeat;z-index:0;\">");
	arr.push("<div id=\"holder\" style=\"position:relative;left:"+(0)+"px;top:"+(0)+"px;width:"+ww+"px;height:"+hh+"px;\">");
	arr.push("</div>");
	for(var k in mp_img){
		if(!sm && null!=mp_img[k]["bigimg"]){ //大屏
			path = mp_img[k]["bigimg"];
		}
		else{
			path = k;
		}
		arr.push(get_div({"img":k,"path":path,"w":mp_img[k].w,"h":mp_img[k].h,"x":mp_img[k].x,"y":mp_img[k].y}));
	}
	for(var k in mp_div){
		arr.push(html_div(k));
	}
	//arr.push("<div id=info5 style=\"POSITION:absolute;LEFT:63px;TOP:117px;\"><font color=\"#80FF80\" size=\"4\"><span align=\"center\">上面单词的词义，最接近下面哪一个选项?</span></font></div>");
	arr.push("<div id=info5 style=\"POSITION:absolute;LEFT:"+mp_sty["info5"].x+"px;TOP:"+mp_sty["info5"].y+"px;\"><font color=\"#80FF80\" size=\"4\"><span align=\"center\">上面单词的词义，最接近下面哪一个选项?</span></font></div>");
	arr.push("<div id=item_area style=\"POSITION:absolute;LEFT:"+mp_sty["item_area"].x+"px;TOP:"+mp_sty["item_area"].y+"px;width:258px;visibility:hidden;\"><font color=\"#FF0000\" size=\"8\"><span align=\"center\">BADINAGE!</span></font></div>");

	arr.push("<div id=opt1 style=\"POSITION:absolute;LEFT:"+mp_sty["opt1"].x+"px;TOP:"+mp_sty["opt1"].y+"px;width:258;visibility:hidden;\" onclick=\"g_ce().notify(433,0);\"><font color=\"#FFFF00\" size=\"4\">A. <span>开玩笑!</span></font></div>");
	arr.push("<div id=opt2 style=\"POSITION:absolute;LEFT:"+mp_sty["opt2"].x+"px;TOP:"+mp_sty["opt2"].y+"px;width:258;visibility:hidden;\" onclick=\"g_ce().notify(433,1);\"><font color=\"#FFFF00\" size=\"4\">B. <span>开玩笑!</span></font></div>");
	arr.push("<div id=opt3 style=\"POSITION:absolute;LEFT:"+mp_sty["opt3"].x+"px;TOP:"+mp_sty["opt3"].y+"px;width:258;visibility:hidden;\" onclick=\"g_ce().notify(433,2);\"><font color=\"#FFFF00\" size=\"4\">C. <span>开玩笑!</span></font></div>");
	arr.push("<div id=opt4 style=\"POSITION:absolute;LEFT:"+mp_sty["opt4"].x+"px;TOP:"+mp_sty["opt4"].y+"px;width:258;visibility:hidden;\" onclick=\"g_ce().notify(433,3);\"><font color=\"#FFFF00\" size=\"4\">D. <span>开玩笑!</span></font></div>");

	arr.push("<div id=feedback style=\"POSITION:absolute;LEFT:"+mp_sty["feedback"].x+"px;TOP:"+mp_sty["feedback"].y+"px;width:258;visibility:hidden;\"><img src=\"images/en/c1.gif\" width=\"255\" height=\"170\"></div>")
	arr.push("<div id=end style=\"POSITION:ABSOLUTE;LEFT:"+mp_sty["feedback"].x+"PX;TOP:"+mp_sty["feedback"].y+"PX;width:300;visibility:hidden;z-index:5;filter:shadow(color=silver,direction=900,enabled=1)\"><h1><font color=\"#0000FF\" size=\"12\"><p id=s4 align=\"center\">Game Over!</p></font></h1></div>");

	arr.push("</DIV>");
	m_fe.face.insertAdjacentHTML("beforeend",arr.join(""));
}
function show_fb(flag)
{
	//显示结果
	//输入:flag:true对/false错
	//输出:无
	var i = parseInt(Math.random() * 4);
	var path = (dir+"en/"+(flag?pname1[i]:pname2[i])+".gif");
	var o = $$("feedback").childNodes[0];
	o.src = path;
	opendiv("feedback",true);
}
function open_info(flag)
{
	//开关题号项
	//输入:flag:true/false
	//输出:无
	for(var k in mp_div){
		$$(k).style.display = (flag?"block":"none");
	}
}
function html_div(id)
{
	//display:none;
	return ("<div id=\""+id+"\" style=\"POSITION:ABSOLUTE;LEFT:"+mp_div[id].x+"PX;TOP:"+mp_div[id].y+"PX;\"><h3><font color=\"#FFFF00\"><span>"+mp_div[id].txt+"</span></font></h3></div>");
}
function up_end(val)
{
	//更新结束
	//输入:val值
	//输出:无
	var o = $$("end").childNodes[0].childNodes[0].childNodes[0];
	o.innerText = val;
}
function up_title(val)
{
	//更新题目
	//输入:val值
	//输出:无
	//glog("up_title,val="+val);
	var o = $$("item_area").childNodes[0].childNodes[0];
	o.innerText = val;
	//glog("o.innerText="+o.innerText);
	//alert($$("item_area").innerHTML);
}
function light(no,c)
{
	//高亮选项
	//输入:no下标:0-3,c:red,green
	//输出:无
	if(!c){c="red";}
	var o = arropt[no].parentNode;
	o.style.color=c;
}
function up_opt(arr)
{
	//更新选项
	//输入:arr:[选项,...]
	//输出:无
	assert.call(this,arr.length==arropt.length);
	//glog("up_opt="+arr.length+","+arropt.length);
	var o = null;
	for(var i = 0;i<arr.length;++i){
		arropt[i].innerText = arr[i];
		o = arropt[i].parentNode;
		o.style.color="#FFFF00";
	}
}
function up_no(val)
{
	//更新题号
	//输入:val值
	//输出:无
	var o = $$("info4").childNodes[0].childNodes[0].childNodes[0];
	o.innerText = (""+val);
}
function up_score(val)
{
	//更新分数
	//输入:val值
	//输出:无
	var o = $$("info2").childNodes[0].childNodes[0].childNodes[0];
	o.innerText = (""+val);
}
function opendiv(id,flag)
{
	//开始元素
	//输入:id编号,flag:true开/false关
	//输出:无
	$$(id).style.visibility= (flag?"visible":"hidden");
}
function sw_start(flag)
{
	//切换开关图
	//输入:flag:true开/false关
	//输出:无
	var o = btnstart.childNodes[0];
	o.src=(dir+(flag?"en/start.jpg":"en/stop.jpg"));
}
function init_mp()
{
	//初始数据
	var sm = is_sm(); //是否小屏
	var ww = wsm/warea; //比例
	var hh = hsm/harea;
	var xy = get_xy();
	for(var k in mp_img){
		if(!sm && mp_img[k]["big"]){ //大屏
			//wh
			if(mp_img[k]["big"]["w"]){
				mp_img[k].w = mp_img[k]["big"].w;
				mp_img[k].h = mp_img[k]["big"].h;
			}
			//xy
			if(mp_img[k]["big"]["x"]){
				mp_img[k].x = mp_img[k]["big"].x;
				mp_img[k].y = mp_img[k]["big"].y;
			}
		}
//		mp_img[k].x += xy[0];
//		mp_img[k].y += xy[1];
	}
//	for(var k in mp_div){
//		mp_div[k].x += xy[0];
//		mp_div[k].y += xy[1];
//	}
//	for(var k in mp_sty){
//		mp_sty[k].x += xy[0];
//		mp_sty[k].y += xy[1];
//	}
}
function get_div(info)
{
	//图层
	//输入:{img,w,h,x,y,path}
	//输出:字符串
	var evt = "",sty="",id="";
	//return "";
	if(null!=mp_img[info.img]["id"]){
		id = "id=\""+mp_img[info.img]["id"]+"\"";
	}
	if(null!=mp_img[info.img]["evt"]){
		evt = ("onclick=\"javascript:g_ce().notify("+mp_img[info.img]["evt"][0]+","+mp_img[info.img]["evt"][1]+");\"");
	}
	if(null!=mp_img[info.img]["sty"]){
		sty = (mp_img[info.img]["sty"]);
	}
	return ("<div "+id+" style=\"POSITION:ABSOLUTE;TOP:"+info.y+"PX;LEFT:"+info.x+"PX;"+sty+"\" "+evt+"><img border=\"0\" src=\""+dir+info.path+"\" width=\""+info.w+"\" height=\""+info.h+"\"></div>");
}
function is_sm(){return true;return (m_coagent.get_w()<warea || m_coagent.get_h()<harea);}
function get_xy()
{
	//层起始坐标
	//输入:无
	//输出:[x,y]
	var ret = [0,0];
	//return ret;
	//屏幕宽高
	var w = m_coagent.get_w();
	var h = m_coagent.get_h();
	var sm = is_sm(); //是否小屏
	var ww = sm?MDEF["wsm"]:warea; //对应屏宽高
	var hh = sm?MDEF["hsm"]:harea;
	//glog("w="+w+",h="+h);
	var x = parseInt((w-ww)/2,10);
	var y = parseInt((h-hh)/2,10);
	if(x>=0 && y>=0){ret = [x,y];}
	return ret;
}
function tip(txt)
{
	//提示
	//参数:txt内容
	//返回:无
	opendiv("end",true);
	up_end(txt);    
	//弹跳任务
	//关闭任务,3秒后
	m_taskmg.add(new c_tkcloseend());
}
return {
	init:init,
	opendiv:opendiv, //开关元素
	sw_start:sw_start, //开始图
	up_score:up_score, //更新分数
	up_no:up_no, //更新题号
	up_title:up_title, //新新题目
	up_opt:up_opt, //更新选项
	up_end:up_end, //更新结束
	show_fb:show_fb, //显示结果
	light:light, //高亮选项
	open_info:open_info, //开关题号项
	tip:tip, //提示
	tests:tests
};
}();

//弹跳任务
function c_tkcloseend()
{
//关提示任务
//参数:无
//返回:无
var blnover = false; //是否结果
var count = 90; //N帧后关闭
//var sit = v;
//var nodes = arr; //节点表
//var lastx = nodes[0][0];
//var lasty = nodes[0][1];
//var sx,sy,ex,ey;
//var size = 25;
//glog("c_tkline,sit="+sit);
function over(){blnover=true;}
function run()
{
	//画线
	//参数:无
	//返回:true完成/false继续
	//glog("c_tkline,run,len="+nodes.length);
	if(blnover){m_feen.opendiv("end",false);return true;}
	--count;
	if(count<1){m_feen.opendiv("end",false);return true;}
	return false;
}
return {
run:run,
over:over //结束
};
}

//关闭任务
function c_tkcloseend()
{
//关提示任务
//参数:无
//返回:无
var blnover = false; //是否结果
var count = 90; //N帧后关闭
//var sit = v;
//var nodes = arr; //节点表
//var lastx = nodes[0][0];
//var lasty = nodes[0][1];
//var sx,sy,ex,ey;
//var size = 25;
//glog("c_tkline,sit="+sit);
function over(){blnover=true;}
function run()
{
	//画线
	//参数:无
	//返回:true完成/false继续
	//glog("c_tkline,run,len="+nodes.length);
	if(blnover){m_feen.opendiv("end",false);return true;}
	--count;
	if(count<1){m_feen.opendiv("end",false);return true;}
	return false;
	/*
	if(nodes.length<1){return true;}
	//var k = nodes.length-1;
	var nx = nodes[0][0]; //下一个节点
	var ny = nodes[0][1];
	var x = nx,y = ny;
	if(lastx!=nx){
		x = (lastx<nx)?(lastx+size):(lastx-size);
		x = (Math.abs(nx-x)<=size)?nx:x;
	}
	if(lasty!=ny){
		y = (lasty<ny)?(lasty+size):(lasty-size);
		y = (Math.abs(ny-y)<=size)?ny:y;
	}
	//glog(x+","+y+";"+nx+","+ny);
	sx = lastx;
	sy = lasty;
	ex = x;
	ey = y;
	lastx = x;
	lasty = y;
	if(nx==x && ny==y){
		nodes.shift();
		if(nodes.length<1){g_ce().notify(439,[sit,nx,ny]);}
	}
	m_stline.draw(sit,sx,sy,ex,ey);
	return false;
	*/
}
return {
run:run,
over:over //结束
};
}

function exists_feen(){return true;} //确认函数
