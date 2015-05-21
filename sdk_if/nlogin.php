<?php
function https_get($url="",$da="")
{
	//exit($url);
	$ch = curl_init(); 
	curl_setopt($ch, CURLOPT_URL,$url); 
	curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
	
	//curl_setopt($ch, CURLOPT_HEADER, "Authorization: Bearer ".$da);
	//curl_setopt($ch, CURLOPT_HEADER, "Authorization: ".$da);
	curl_setopt ( $ch, CURLOPT_HTTPHEADER, array (
			'Authorization: Bearer '.$da 
	) );
	//Authorization: Bearer AAAAOLtP40eH6P5S4Z4FpFl77n3FD5I+W3ost3oDZq/nbcS+7MAYXwXbT3Y7Ib3dnvcqHkcK0e5/rw6ajF7S/QlJAgUukpp1OGkG0vzi16hcRNYX6RcQ6kPxB0oAvqfUPJiJw==
	
	//curl_setopt ( $ch, CURLOPT_CUSTOMREQUEST, "GET" );
	//curl_setopt ( $ch, CURLOPT_HEADER, 0);
	
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); 
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false); 

	$ret = curl_exec($ch);  
	curl_close($ch); 

	return $ret;
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
function xml2json($str="")
{
	$xml = simplexml_load_string($str);
	$code = "110";
	$email = "";
	//$tmp = $xml->response->email;
	//var_dump(strval($tmp));
	//var_dump($xml->result[0]->resultcode);
	//exit();

	if(($xml->result)){
		if(($xml->result->resultcode)){
			$code = strval($xml->result->resultcode);
		}
	}
	if(($xml->response)){
		if(($xml->response->email)){
			$email = strval($xml->response->email);
		}
	}
	$ret = array();
	$ret["code"] = $code;
	$ret["email"] = $email;

	echo json_encode($ret);
//	echo "<br><br><br><br><br>";
//	var_dump($xml);	
}

//$act = isset($_GET["act"])?$_GET["act"]:"me";
//$field = isset($_GET["field"])?$_GET["field"]:"access_token";


$url = "https://apis.naver.com/nidlogin/nid/getUserProfile.xml";


  
//$data = "AAAAQCR0QAN2VJzYVchsKA9dZEPM7TLwfusBz9gb4aUFBR/oatAjK8+Ep4k7U+DPsRuVaMtgZoPDqAP8Lg7f976oBKo=";
$data = file_get_contents("php://input");

//set_time_limit(720);
//$ret = $strxml;
$ret = https_get($url,$data);
//var_dump($ret);
//exit();
//echo ($ret[1]);
xml2json($ret);


ob_flush();
flush();
?>

