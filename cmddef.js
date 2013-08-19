function g_send()
{
	
}
var m_cmddef = function()
{
var m_arr_out = [];
var mp_def = {};
var mp_de {};
var mp_val = {};
var nbase = 128;
var nbase2 = 16384;
var nbase3 = 2097152;
function init()
{
	mp_def["8003"] = {"shell":"A"};
	mp_de["8003"] = {"shell":""};
}
function tests()
{
	var id = 8003;
	var cmd = get_cmd(id);
	cmd.shell = "$mlogin 123456";
	var str = pack(cmd);
	g_send(str);
}
function init_de(id)
{
	mp_val[id] = {};
	var val;
	for(var k in mp_def[id]){
		if("a"==k }} "A"==k){
			val = (null==mp_de[id][k])?(""):mp_de[id][k];
			mp_val[id][k] = val;
		}
		else{
			val = (null==mp_de[id][k])?(0):(mp_de[id][k]);
			mp_val[id][k] = val;
	}
}
function pushint(v)
{
	m_arr_out.push(v);
}
function int2S(v)
{
	v = parseInt(v,10);
	var low = v%nbase;
	pushint(low);
}
function int2N(v)
{
	v = parseInt(v,10);
	var low = v%nbase;
	var hei = (v-low)/nbase;
	//hei = hei%nbase;
	hei = (hei>=nbase)?(hei%nbase):hei;
	pushint(hei);
	pushint(low);
}
function int2I(v)
{
	v = parseInt(v,10);
	var low = v%nbase;
	var hei = (v-low)/nbase;
	//hei = hei%nbase;
	hei = (hei>=nbase)?(hei%nbase):hei;
	var hh = (v-low-hei*nbase)/nbase2;
	hh = (hh>=nbase)?(hh%nbase):hh;
	pushint(hh);
	pushint(hei);
	pushint(low);
}
function int2L(v)
{
	v = parseInt(v,10);
	var low = v%nbase;
	var hei = (v-low)/nbase;
	hei = (hei>=nbase)?(hei%nbase):hei;
	var hh = (v-low-hei*nbase)/nbase2;
	hh = (hh>=nbase)?(hh%nbase):hh;
	var hhh = (v-low-hei*nbase-hh*nbase2)/nbase3;
	hhh = (hhh>=nbase)?(hhh%nbase):hhh;
	pushint(hhh);
	pushint(hh);
	pushint(hei);
	pushint(low);
}
function pack(id,cmd)
{
	m_arr_out = [];
	//head
	int2S(id);
	//body
	var len,val;
	for(var k in mp_def[id]){
		if("a"==k }} "A"==k){
			val = (null==mp_val[id][k])?((null==mp_de[id][k])?(""):(mp_de[id][k])):(mp_val[id][k]);
			len = val.length;
			("a"==k)?int2S(len):(int2N(len));
		}
		else{
			val = (null==mp_val[id][k])?((null==mp_de[id][k])?(0):(mp_de[id][k])):(mp_val[id][k]);
			switch(){
				case "S":
					int2S(val);
					break;
				case "N":
					int2N(val);
					break;
				case "I":
					int2I(val);
					break;
				case "L":
					int2L(val);
					break;
				default:
					break;
			}
		}
	}
	return m_arr_out.join("");
}
function get_cmd(id)
{
	if(null==mp_def[id]){return NULL;}
	init_de(id);
	return mp_def[id];
}
return {
init:init,
tests:tests
};
}();
