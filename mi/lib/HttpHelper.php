<?php
/**
 * HTTP 请求辅助类
 */
class HttpHelper {
  
    const METHOD_GET = 'GET';
    const METHOD_POST = 'POST';

    private $_connectTimeout = 60;
    private $_timeout = 60;
    
    /**
     * Http post请求
     * @param type $url  http url address
     * @param type $data post params name => value 
     */
    public function post($url, $data = array()){
        
        $queryString = $this->buildHttpQueryString($data,  self::METHOD_POST);
        
        $response = $this->makeHttpRequest($url, self::METHOD_POST,$queryString);
        return $response;
    }
    
    /**
     * http get 请求
     * @param type $url  http url address
     * @param type $data get params name => value
     */
    public function get($url,$data = array()) {
        if(!empty($data)){
            $url .= "?" . $this->buildHttpQueryString($data,  self::METHOD_GET);
        }
        $response = $this->makeHttpRequest($url,  self::METHOD_GET);
        return $response;
    }
    
    /**
     * 构造并发送一个http请求
     * @param type $url
     * @param type $method
     * @param type $postFields
     * @return type
     */
    public function makeHttpRequest($url,$method,$postFields = null) {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        if(self::METHOD_POST == $method){
            curl_setopt($ch, CURLOPT_POST, 1);
            if(!empty($postFields)){
                curl_setopt($ch, CURLOPT_POSTFIELDS, $postFields);
            }
        }
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $this->_connectTimeout);
        curl_setopt($ch, CURLOPT_TIMEOUT, $this->_timeout);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
        
        $result = curl_exec($ch);
        curl_close($ch);
        return $result;
    }
    
    /**
     * 构造http请求的查询字符串
     * @param array $params
     * @param type $method
     * @return string
     */
    public function buildHttpQueryString(array $params, $method = self::METHOD_GET) {
        if(empty($params)){
            return '';
        }
        if(self::METHOD_GET == $method){
            $keys = array_keys($params);
            $values = $this->urlEncode(array_values($params));
            $params = array_combine($keys, $values);
        }
        
        $fields = array();
        
        foreach ($params as $key => $value) {
            $fields[] = $key . '=' . $value;
        }
        return implode('&',$fields);
    }
    
    /**
     * url encode 函数
     * @param type $item  数组或者字符串类型
     * @return type
     */
    public function urlEncode($item) {
        if(is_array($item)){
            return array_map(array(&$this,'urlEncode'), $item);
        }
        return rawurlencode($item);
    }
    
    /**
     * url decode 函数
     * @param type $item 数组或者字符串类型
     * @return type
     */
    public function urlDecode($item){
        if(is_array($item)){
            return array_map(array(&$this,'urlDecode'), $item);
        }
        return rawurldecode($item);
    }
}
