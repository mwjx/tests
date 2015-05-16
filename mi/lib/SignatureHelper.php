<?php
/**
 * 签名辅助类
 *
 */
class SignatureHelper {
    
    /**
     * 计算hmac-sha1签名
     * @param array $params
     * @param type $secretKey
     * @return type
     */
    public function sign(array $params, $secretKey){
        $sortString = $this->buildSortString($params);
        $signature = hash_hmac('sha1', $sortString, $secretKey,FALSE);
        
        return $signature;
    }
    
    /**
     * 验证签名
     * @param array $params
     * @param type $signature
     * @param type $secretKey
     * @return type
     */
    public function verifySignature(array $params, $signature, $secretKey) {
        $tmpSign = $this->sign($params, $secretKey);
        return $signature == $tmpSign ? TRUE : FALSE;
    }
    
    /**
     * 构造排序字符串
     * @param array $params
     * @return string
     */
    public function buildSortString(array $params) {
        if(empty($params)){
            return '';
        }
        
        ksort($params);
        
        $fields = array();
        
        foreach ($params as $key => $value) {
            $fields[] = $key . '=' . $value;
        }
        
        return implode('&',$fields);
    }
}


