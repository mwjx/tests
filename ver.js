var m_ver = function()
{
var boxroot = "E://src/tmp/";
var serroot = "E://src/";
function init()
{
}
function tests()
{
	up_dir("ftmp/");
}
function up_dir(d)
{
	var file = "CVS/Entries";
	//取本地列表
	var dloc = boxroot+d;
	var pathloc = dloc+file;
	var txtloc = get_loc(pathloc);
	//取远程列表
	var dser = serroot+d;
	var pathser = dser+file;
	var txtser = get_ser(pathser);
	//比较出新文件列表
	var arr = diff(txtloc,txtser);
	var down = arr[0];
	var arrdir = arr[1];
	//下载新文件
	var from,to,f;
	for(var i =0;i<down.length;++i){
		f = down[i][1];
		from = dser+f;
		to = dloc+f;
		copyfile(to,from);
	}
	//更新本地列表文件
	if(down.length>0){
		copyfile(pathloc,pathser);
	}
	//目录递归
	for(var i=0;i<arrdir.length;++i){
		up_dir(d+arrdir[i]+"/");
	}
}
function diff(loc,ser)
{
	var arrloc = loc.split("\n");
	var arrser = ser.split("\n");
	var mp_loc = {}; //file=>[ver,time]
	var row;
	for(var i=0;i<arrloc.length;++i){
		row = arrloc[i].split("/");
		if(6!=row.length){continue;}
		mp_loc[row[1]] = [row[2],row[3]];
	}
	var tmp,vtmp,vloc;
	var down = [];
	var arrdir = [];
	for(var i=0;i<arrser.length;++i){
		row = arrser[i].split("/");
		if(6!=row.length){continue;}
		if("D"==row[0]){
			arrdir.push(row[1]);
			continue;
		}
		tmp = row[1];
		if(null!=mp_loc[tmp] && mp_loc[tmp][0]==row[2]){
			continue;
		}
		down.push(row);
	}

	return [down,arrdir];
}
function copyfile(to,from)
{
	//复制文件
	//略
	var fso = new ActiveXObject("Scripting.FileSystemObject");   
	//f = fso.CreateTextFile("c://testfile.txt", true);   
	//f.WriteLine("This is a test.");   
	//f.Close();   
	var f = fso.GetFile(frin);   
	var f.Copy(to);   
}
function readfiles(path)
{
	//读取文件
	var fso=new ActiveXObject("Scripting.FileSystemObject");
	var file = fso.GetFile(path);
	var ts = file.OpenAsTextStream(ForReading,TristateUseDefault);  
	//var mynote = ts.ReadLine(); 读取一行
	var s=ts.ReadAll(); //读取全部
	ts.Close();
	return s;
}
function get_loc(path)
{
	//取本地列表
	return readfiles(path);
}
function get_ser(path)
{
	//取远程列表
	return readfiles(path);
}
return {
init:init,
tests:tests
};
}();