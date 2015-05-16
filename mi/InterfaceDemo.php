<?php

include_once 'lib/HttpHelper.php';
include_once 'lib/SignatureHelper.php';
include_once 'lib/Configuration.php';

/**
 * 验证登陆信息接口
 * @param type $userId
 * @param type $session
 */
function verifySession($userId,$session) {
    
    $params = array('appId' => Configuration::APP_ID,'uid' => $userId, 'session' => $session);
    
    $signObj = new SignatureHelper();
    
    $signature = $signObj->sign($params, Configuration::SECRET_KEY);
    
    $params['signature'] = $signature;
    
    $request = new HttpHelper();
    $response = $request->get(Configuration::VERIFY_SESSION_URL, $params);
    
    //TODO: 后续业务逻辑处理
    echo $response;
}

/**
 * 查询订单接口
 * @param type $userId
 * @param type $cpOrderId
 */
function queryOrder($userId,$cpOrderId) {
    
    $params = array('appId' => Configuration::APP_ID,'uid' => $userId, 'cpOrderId' => $cpOrderId);
    $signObj = new SignatureHelper();
    
    $signature = $signObj->sign($params, Configuration::SECRET_KEY);
    
    $params['signature'] = $signature;
    
    $request = new HttpHelper();
    $response = $request->get(Configuration::QUERY_ORDER_URL, $params);
    
    //TODO: 后续业务逻辑处理
    echo $response;
}

/**
 * 接收订单通知接口
 */
function notify(){
    $reqparams = $_REQUEST;
    $params = array();
    $httpHelper = new HttpHelper();
    foreach ($reqparams as $key => $value) {
        if($key != 'signature'){
            $params[$key] = $httpHelper->urlDecode($value);
        }
    }
    $signature = $reqparams['signature'];
    
    $signObj = new SignatureHelper();
    
    if($signObj->verifySignature($params, $signature, Configuration::SECRET_KEY)){
        //TODO:后续业务逻辑处理
        echo '{"errcode":200}';
    }else{
       echo '{"errcode":1525}';
    }
}