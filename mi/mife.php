<?php
require_once("InterfaceDemo.php");
$m_uid = isset($_GET["uid"])?$_GET["uid"]:"0";

  
//$m_data = file_get_contents("php://input");
$m_uid = "73878237";
$m_data = "{\"appId\":\"2882303761517333929\",\"session\":\"0JYkVRwkkbawLlsm\"}";
//$m_data = "{\"appId\":\"aa\",\"session\":\"aa\"}";
$oj = json_decode($m_data);

verifySession($m_uid,$oj->session);

//ob_flush();
//flush();
?>

