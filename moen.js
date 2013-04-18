//------------------------------
//create time:2013-3-30
//creater:zll,liang_0735@21cn.com,www.mwjx.com
//purpose:英语逻辑
//------------------------------
xinclude("model/moen.js",[],"m_moen.init");
var m_moen = function(){
var wordlist;
var game_status=0; //当前状态:0结束/1开始
var allno = 80,optnum=4; //词条数,选项数
var total_items=5,item_no,p_answerno=-1,p_score;
var p_wordno = -1; //词号:0-?
var itemlist=[];
for(var i=0;i<total_items;i++){
	itemlist[i]=[];
}
var pname1 = ["c1", "c2", "c3", "c4"]; //答对的反馈图案
var pname2 = ["w1", "w2", "w3", "w4"]; //答错的反馈图案
var clist=[],wlist=[];


function init()
{
	g_trace("moen.js,初始");
	init_wordlist();

	//log_trace();
}
function tests(){}
function get_state()
{
	//全部状态
	//输入:无
	//输出:[状态,题号,分数,未结束]
	return [game_status,item_no,p_score,item_no<total_items];
}
function start_game()
{
	//游戏开始
	var i;
	switch(game_status){
	case 0: //start  开始游戏   
		//glog("start_game,start");
		p_score=0; //分数
		item_no=0; //题号
		game_status=1; //状态
		gene_items();
		g_ce().notify(547,0); //开始界面
		break;
	case 1: //stop  停止游戏
		game_status=0;
		g_ce().notify(548,0); //结束界面
		break;
	}
}
function gene_items()
{
	// 随机产生题组编号
	//glog("gene_items");
	var i, j, x, xlist=[];
	for(i=0;i<allno;i++){
		xlist[i] = i;
	}
	//随机排列数组数据
	for(i=0;i<allno;i++){
		j = parseInt(Math.random() * 80);
		x = xlist[i];
		xlist[i] = xlist[j];
		xlist[j] = x;
	}
	//产生题目数组
	for(i=0;i<total_items;i++){
		itemlist[i][0] = xlist[i * 4];
		itemlist[i][1] = xlist[i * 4 + 1];
		itemlist[i][2] = xlist[i * 4 + 2];
		itemlist[i][3] = xlist[i * 4 + 3];
	}
}
function titlebyno(no)
{
	//根据词号取题目
	//输入:no词号
	//输出:题目
	return wordlist[no][0];
}
function chbyno(no)
{
	//根据词号取中文
	//输入:no词号
	//输出:中文
	return ((no>=0)?wordlist[no][2]:"");
}
function new_item()
{
	//新组
	//输入:无
	//输出:[题号,问题,[选项表,...]]
	p_answerno = parseInt(Math.random() * optnum);
	p_wordno = itemlist[item_no][p_answerno]; //词号
	var ret = [item_no+1,wordlist[p_wordno][0],[]];
	for(var i=0;i<optnum;i++){
		ret[2].push(wordlist[itemlist[item_no][i]][2]);
	}
	return ret;
}
function item_click(index)
{
	//处理答案的程序
	//输入:index:0-3
	//输出:true正确/false错误
	if(item_no>=total_items){return false;}
	var ret = (index == p_answerno);
	if(ret){ //正确答案
		p_score = p_score + 10;
		if(p_wordno>=0){g_ce().notify(549,[0,p_wordno]);}
	} 
	item_no = item_no + 1;
	return ret;
}
function had_click()
{
	//能否选中
	//输入:无
	//输出:true/false
	if(!is_ing()){return false;}
	if(item_no>=total_items){return false;}
	return true;
}
function help()
{
	//正确答案
	//输入:无
	//输出:-1失败,0-3
	if(!had_click()){return -1;}
	if(p_answerno<0){return -1;}
	p_wordno = -1; //去掉词号,保证不能进度存档
	return p_answerno;
}
function init_wordlist()
{
	// 设置题目数组
	var word0 = new Array("abase", "lower; humiliate", "降低；屈辱");
	var word1 = new Array("abash", "embarrass", "使困窘");
	var word2 = new Array("abbreviate", "shorten", "缩短");
	var word3 = new Array("abdicate", "renounce; give up", "弃绝；放弃");
	var word4 = new Array("aberration", "wandering or straying; in optics, fa", "偏差；差错");
	var word5 = new Array("abettor", "encourager", "教唆者");
	var word6 = new Array("abeyance", "suspended action", "暂缓");
	var word7 = new Array("abhor", "detest; hate", "憎恨");
	var word8 = new Array("abjure", "renounce upon oath", "誓言放弃");
	var word9 = new Array("ablution", "washing", "沐浴");
	var word10 = new Array("abnegation", "repudiation; self-sacrifice", "自我克制；放弃");
	var word11 = new Array("abolish", "cancel; put an end to", "废除");
	var word12 = new Array("abominate", "loathe; hate", "憎恶");
	var word13 = new Array("aboriginal", "being the first of its kind in a reg", "原始的；本土的");
	var word14 = new Array("abortive", "unsuccessful; fruitless", "未成功的；发育不全的");
	var word15 = new Array("abrade", "wear away by friction; erode", "磨损");
	var word16 = new Array("abridge", "condense or shorten", "缩短；删节");
	var word17 = new Array("abrogate", "abolish", "废止；废除");
	var word18 = new Array("abscond", "depart secretly and hide", "秘密潜逃；藏匿");
	var word19 = new Array("absolve", "pardon (an offense);", "赦免");
	var word20 = new Array("abstemious", "sparing in eating and drinking; temp", "戒酒；节制");
	var word21 = new Array("abstinence", "restrain from eating or drinking", "饮食有度的；适度的");
	var word22 = new Array("abstract", "theoretical; not concrete; nonrepres", "抽象的；难了解的");
	var word23 = new Array("abstruse", "obscure; profound; difficult to unde", "深奥的；难解的");
	var word24 = new Array("abusive", "coarsely insulting; physically harmf", "虐待的；辱骂的");
	var word25 = new Array("abut", "border upon; adjoin", "接界；毗连");
	var word26 = new Array("abysmal", "bottomless", "无底的；地狱的");
	var word27 = new Array("accede", "agree", "同意");
	var word28 = new Array("accelerate", "move faster", "加速");
	var word29 = new Array("accessible", "easy to approach; obtainable", "易达到的；可获得的");
	var word30 = new Array("accessory", "additional object; useful but not es", "附属品；配件；从犯");
	var word31 = new Array("acclimate", "adjust to climate", "使适应於");
	var word32 = new Array("acclivity", "sharp upslope of a hill", "向上的斜坡");
	var word33 = new Array("babble", "chatter idly", "多嘴；说话模糊不清");
	var word34 = new Array("bacchanalian", "drunken", "发酒疯的");
	var word35 = new Array("badger", "pester; annoy", "困扰");
	var word36 = new Array("badinage", "teasing conversation", "嘲弄；开玩笑");
	var word37 = new Array("baffle", "frustrate; perplex", "使困惑；阻碍");
	var word38 = new Array("bagatelle", "trifle", "琐事");
	var word39 = new Array("baleful", "deadly; destructive", "致命的");
	var word40 = new Array("bait", "harass;tease", "迫之使怒；逗弄");
	var word41 = new Array("balk", "foil", "阻碍；错过");
	var word42 = new Array("balm", "something that relieves pain", "止痛的东西；慰藉");
	var word43 = new Array("balmy", "mild; fragrant", "温和的；芳香的");
	var word44 = new Array("banal", "hackneyed; commonplace; trite", "平凡的；琐屑的");
	var word45 = new Array("bandanna", "large, bright-colored handkerchief", "大手帕；大　巾");
	var word46 = new Array("cabal", "small group of persons secretly unit", "阴谋；派系");
	var word47 = new Array("cache", "hiding place", "地窖");
	var word48 = new Array("cacophony", "discord", "刺耳的声音");
	var word49 = new Array("cadaver", "corpse", "尸体");
	var word50 = new Array("cadaverous", "like a corpse; pale", "似尸的；憔悴的");
	var word51 = new Array("cajole", "coax; wheedle", "甘言诱惑");
	var word52 = new Array("calamity", "disaster; misery", "灾难");
	var word53 = new Array("caliber", "ability; capacity", "口径；才干");
	var word54 = new Array("calligraphy", "beautiful writing; excellent penmans", "书法");
	var word55 = new Array("callous", "hardened; unfeeling", "无情的");
	var word56 = new Array("callow", "youthful; immature", "无经验的；未生羽毛的");
	var word57 = new Array("calorific", "heat-producing", "生熟的；发热的");
	var word58 = new Array("calumniate", "slander", "诽谤");
	var word59 = new Array("camaraderie", "good-fellowship", "同志爱；友谊");
	var word60 = new Array("cameo", "shell or jewel carved in relief", "刻有浮雕之宝石");
	var word61 = new Array("canard", "unfounded rumor; exaggerated report", "虚报");
	var word62 = new Array("candor", "frankness", "坦率；爽直；诚恳");
	var word63 = new Array("canine", "related to dogs; dog-like", "犬科动物");
	var word64 = new Array("canker", "any ulcerous sore; any evil", "积病");
	var word65 = new Array("canny", "shrewd; thrifty", "灵敏的；小心的");
	var word66 = new Array("cant", "jargon of thieves; pious phraseology", "伪善之言；隐语");
	var word67 = new Array("cantankerous", "ill humored; irritable", "难处的");
	var word68 = new Array("cantata", "story set to music, to be sung by a", "清唱剧");
	var word69 = new Array("canter", "slow gallop", "慢跑");
	var word70 = new Array("canto", "division of a long poem", "长诗中的篇");
	var word71 = new Array("canvass", "determine votes, etc", "讨论；拉票");
	var word72 = new Array("capacious", "spacious", "宽广的");
	var word73 = new Array("caparison", "showy harness or ornamentation for a", "打扮；马的装饰物");
	var word74 = new Array("capillary", "having a very fine bore", "毛细管的；毛状的");
	var word75 = new Array("capitulate", "surrender", "有条件的投降");
	var word76 = new Array("caprice", "whim", "反覆无常；幻想");
	var word77 = new Array("capricious", "fickle; incalculable", "多变的");
	var word78 = new Array("caption", "title; chapter heading; text under i", "标题；插图的说明");
	var word79 = new Array("captious", "faultfinding", "爱找岔子的，强词夺理的");
	//将题目数据转换到wordlist数组中
	var str1="wordlist=[";
	//var i;
	for(var i=0;i<79;i++){
		str1=str1+"word"+i+",";
	}
	str1=str1+"word79]";
	eval(str1);
}
function is_ing(){return (1==game_status);}
return {
	init:init,
	start_game:start_game, //开始
	get_state:get_state, //全部状态
	new_item:new_item, //新组
	is_ing:is_ing, //是否开始
	item_click:item_click, //处理选中
	help:help, //正确答案
	titlebyno:titlebyno, //根据词号取题目
	chbyno:chbyno, //根据词号取中文
	tests:tests
};
}();
function exists_moen(){return true;} //确认函数
