<?php
function https_get($url)
{
	//exit($url);
	$ch = curl_init(); 
	curl_setopt($ch, CURLOPT_URL,$url); 
	//curl_setopt ( $ch, CURLOPT_CUSTOMREQUEST, "GET" );
	//curl_setopt ( $ch, CURLOPT_HEADER, 0);
	
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); 
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false); 

	curl_exec($ch);  
	curl_close($ch); 


//	// grab URL and pass it to the browser
//	$ret = curl_exec($ch);
//	$errorNo = curl_errno ( $ch );
//
//	// Check if any error occured
//	$info = "";
//	if(!$errorNo)
//	{
//		$info = curl_getinfo($ch);
//	}
//
//	// close cURL resource, and free up system resources
//	curl_close($ch);
//	return array($ret,$errorNo,$info);
}

function https_post($url, $data)
{
	$ch = curl_init ();
	curl_setopt ( $ch, CURLOPT_URL, $url); 
	curl_setopt ( $ch, CURLOPT_CUSTOMREQUEST, "POST" );
	curl_setopt ( $ch, CURLOPT_HEADER, 0);
	curl_setopt ( $ch, CURLOPT_POSTFIELDS, $data );
	
	//curl_setopt( $ch, CURLOPT_HTTPHEADER, array("Expect:"));

	//curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, false );
	//curl_setopt ( $ch, CURLOPT_SSL_VERIFYHOST, false );
	curl_setopt ( $ch, CURLOPT_HTTPHEADER, array (	//"Expect:",
			'Content-Type:application/json',
			'Content-Length: ' . strlen ( $data ) 
	) );
	curl_exec($ch);  
	curl_close($ch); 
}

//$path = "me?access_token=";
//$path = "debug_token?input_token=";
$act = isset($_GET["act"])?$_GET["act"]:"me";
$field = isset($_GET["field"])?$_GET["field"]:"access_token";

$url  = "https://graph.facebook.com/v2.3/".$act."?".$field."=";  

//$data = json_encode(array('a'=>1, 'b'=>2));   
  
$data = "CAACEdEose0cBAMSk9urp9zTl1jwH2GuilRq4BWMsUmhIRAGf4A9D1ft3QV6CeqRMSN8VNow1j0M8baofGvlX3OchPI2hgyGwtry09NaLsHojTOaKJjddVhSy9CksR07qHzctNEfYGslyyFCU5DLxpsaFmqkDRmHdC76aT6pPHVkyewC4ZCNPSY2x6osQFPGzMpzvZC3IfDUGsuUe4c";
//$url = "http://localhost/phpinfo.php";
//$url = "http://www.qq.com/";

//$data = file_get_contents("php://input");

$url .= $data;

//$url = "https://developers.facebook.com/docs/apps/changelog";
//$url = "https://www.baidu.com/";
//$url = "https://www.google.com/?gws_rd=ssl";
//set_time_limit(720);
$ret = https_get($url);  
//var_dump($ret);
//echo ($ret[1]);
ob_flush();
flush();
?>

