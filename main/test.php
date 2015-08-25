<?php
$inapp_purchase_data = '{"orderId":"12999763169054705758.1389868167179749","packageName":"com.ENP.myongjiang.kr.googleplay","productId":"com.zhsj.gold0001","purchaseTime":1428056867002,"purchaseState":0,"purchaseToken":"hlncjddgfamlhlnpicbmkapc.AO-J1OwWXa5Y4k7R-DGn-Y4jKWGqt_o1lrQoS3ExAdrSyTANk4KXn7DGZZCLim7HwL0RfK56GvdHo-ofVVzaD-VxnPysi6qZsRxN9f3PebHFXFWdSB6a0O75PpAMM7nBvWMXMVRvr-2L0SL08d0HIGzVEJkfNDPO_g"}';
$inapp_data_signature = 'NISm29p4PRZaQ+1pJspYziG6w0Ag6cLrvKpiPu+bH62JB97+79ntyhcoZb47lDB9vjSEkOWomf9koFwKWvCdo6nrrdpc0GlPInsYzBzoZVoF75nHaMXJoaCQ9kJ2gxZC4mznAEKVb5iyw/Ool1pAFLCevpQSzU0KTWYryLAOteTeATlub8YCYCY4vZyNUM7XigKAjS8weR7aQPrahOC3QDw68OIDKVIejiXIcWdkG+5fwddodpGfUbTqUIZuPFV/m058t7dtF5FBE7Mamw0sHL9/ccmzzGoNFfBOXKL0r3zepHqK6SuebGzbxGnQfmjWHq1+6wgAG470SRrwd8F8zQ==';
$google_public_key = 'MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAgRNdVrI0PnfI4SHERW9IWP6/gtYF1MCYuwC6h6FSFh/ja7H4hcNFfgKgNp7JsLkm414VRddGVuaNTLSvY1CKHkhH4pAWCiaAn9ASJanrLzKvx6ScTiZSn+4mx0VwjoG62ESawCCyNAzmHydW+DZFWS7PiyqT4bk33tmcnY96/Jmbsenw7ExYWITmqGaEdlVyFPbGXDC0bEQSNFPNFnlkv0xK0eYdmQLOXiEwZpzLvmaFRw9rgMgYLZoDHcAvsLw/5okVoJTzd/WkWSkTiEKKEmWlSq+CZ7Inmf5pkjB4f1Pdbb6CiwJh1dfPIh6AJTYLjMY/g8iecSbJtrUsKkMLYwIDAQAB';

//$data = "abc\n";
$img = base64_decode($inapp_data_signature);
//var_dump(base64_encode($data));
//file_put_contents('sign.sha1', $img);
var_dump($img);
exit($img);
$public_key = "-----BEGIN PUBLIC KEY-----\n" . chunk_split($google_public_key, 64, "\n") . "-----END PUBLIC KEY-----";

$public_key_handle = openssl_get_publickey($public_key);

//var_dump($public_key_handle);
//exit();
$result = openssl_verify($inapp_purchase_data, base64_decode($inapp_data_signature), $public_key_handle, OPENSSL_ALGO_SHA1);

if (1 === $result) {
	echo "支付验证成功！";
}
else{
	echo "支付验证失败！";
}

?>