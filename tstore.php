<?php
function https_get($url, $data_string)
{
	// create a new cURL resource
	$ch = curl_init();

	// set URL and other appropriate options
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_HEADER, 0);

	// grab URL and pass it to the browser
	$ret = curl_exec($ch);
	$errorNo = curl_errno ( $ch );

	// Check if any error occured
	$info = "";
	if(!$errorNo)
	{
		$info = curl_getinfo($ch);
	}

	// close cURL resource, and free up system resources
	curl_close($ch);
	return array($ret,$errorNo,$info);
}

function https_post($url, $data_string)
{
	$ch = curl_init ($url);
	curl_setopt ( $ch, CURLOPT_CUSTOMREQUEST, "POST" );
	curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, true );
	curl_setopt ( $ch, CURLOPT_POSTFIELDS, $data_string );
	curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, false );
	curl_setopt ( $ch, CURLOPT_SSL_VERIFYHOST, false );
	curl_setopt ( $ch, CURLOPT_HTTPHEADER, array (
			'Content-Type:application/json',
			'Content-Length: ' . strlen ( $data_string ) 
	) );
//	$result = curl_exec ( $ch );
//	$errorNo = curl_errno ( $ch );
//	curl_close ( $ch );

	//ob_start();  
	$return_content = curl_exec($ch);  
	//$return_content = ob_get_contents();  
	//ob_end_clean();  

	$return_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);  
	return array($return_code, $return_content); 
}

function http_post_data($url, $data_string) 
{    
	$ch = curl_init();  
	curl_setopt($ch, CURLOPT_POST, true);  
	curl_setopt($ch, CURLOPT_URL, $url);  
	curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);  
	curl_setopt($ch, CURLOPT_HTTPHEADER, array(  
		'Content-Type: application/json; charset=utf-8',  
		'Content-Length: ' . strlen($data_string))  
	);  
	ob_start();  
	curl_exec($ch);  
	$return_content = ob_get_contents();  
	ob_end_clean();  

	$return_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);  
	return array($return_code, $return_content);  
}  
  
$url  = "https://iapdev.tstore.co.kr/digitalsignconfirm.iap";  
//$data = json_encode(array('a'=>1, 'b'=>2));   
  
//$data = "{\"txid\":\"TX_0000000658\", \"appid\":\"OA12345678\",\"signdata\":\"MIIH7QYJKoZIhvcNAQcCoIIH3jCCB9oCAQExDzANBglghkgBZQMEAMIIH7QYJKdDFDFFEFEFEFoZIhvcNAQcCoIIH3jCCB9oCAQExDzANBglghkgBZQMEA\"}";
$data = file_get_contents("php://input");
$ret = https_post($url, $data);  
//var_dump($ret);
echo ($ret[1]);
ob_flush();
flush();
?>

