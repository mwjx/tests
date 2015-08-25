#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#include <gsasl.h>


using namespace std;

bool chunk_split(string &key,int len)
{
	int nPublicKeyLen = key.size();      //strPublicKey为base64编码的公钥字符串
	for(int i = len; i < nPublicKeyLen; i+=len){
		if(key[i] != '\n'){
			key.insert(i, "\n");
		}
		i++;
	}
	return true;
}
//static int base64_encode(char *str,int str_len,char *encode,int encode_len){
//     BIO *bmem,*b64;
//     BUF_MEM *bptr;
//     b64=BIO_new(BIO_f_base64());
//     bmem=BIO_new(BIO_s_mem());
//     b64=BIO_push(b64,bmem);
//     BIO_write(b64,str,str_len); //encode
//     BIO_flush(b64);
//     BIO_get_mem_ptr(b64,&bptr);
//     if(bptr->length>encode_len){
//         //DPRINTF("encode_len too small\n");
//         return -1; 
//     }   
//     encode_len=bptr->length;
//     memcpy(encode,bptr->data,bptr->length);
// //  write(1,encode,bptr->length);
//     BIO_free_all(b64);
//     return encode_len;
// }
 
static int base64_decode(char *str,int str_len,char *decode,int decode_buffer_len)
{
	int len=0;
	BIO *b64,*bmem;
	b64=BIO_new(BIO_f_base64());
	bmem=BIO_new_mem_buf(str,str_len);
	bmem=BIO_push(b64,bmem);
	len=BIO_read(bmem,decode,str_len);
	decode[len]=0;
	BIO_free_all(bmem);
	return 0;
}
char * Base64Decode(char * input, int length, bool with_new_line)  
{  
    BIO * b64 = NULL;  
    BIO * bmem = NULL;  
    char * buffer = (char *)malloc(length);  
    memset(buffer, 0, length);  
  
    b64 = BIO_new(BIO_f_base64());  
    if(!with_new_line) {  
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  
    }  
    bmem = BIO_new_mem_buf(input, length);  
    bmem = BIO_push(b64, bmem);  
    BIO_read(bmem, buffer, length);  
  
    BIO_free_all(bmem);  
  
    return buffer;  
}  

bool b64_decode(string &src,string &out)
{
	int lendata = src.length()*3;
	char strbase[lendata];
	char *p = strbase;
//	char chbuf[src.length()+1];
//	memset(chbuf,0,sizeof(chbuf));
//	strcpy(chbuf,src.c_str());
	//int lenbase = base64_decode(chbuf,src.length(),p,lendata);
	//cout << "b64_decode,lenbase=" << lenbase << ",lendata=" << lendata << ",len=" << src.length() << endl;
	int lenbase = gsasl_base64_from(src.c_str(),src.length(),&p,(size_t *)&lendata);
	lenbase = lendata;
	if(lenbase<0){return false;}
	//p = Base64Decode(chbuf,src.length(),false);
	out = string(p,lenbase);	
	return true;
}
bool gg_verify(const string &path,const string &data,const string &sign)
{
	cout << "验签,key=" << path << endl <<",data=" << data << endl << ",sign=" << sign << endl;
	unsigned char *hash = SHA1((const unsigned char *)data.c_str(),data.length(),NULL);
	string hashdata = string((char *)hash);
	cout << "签名hash:" << hashdata << endl;

	string strkey = path;
	if(!chunk_split(strkey,64)){
		cout << "失败111" << endl;
		return false;
	}
	strkey.insert(0,"-----BEGIN PUBLIC KEY-----\n");
	strkey.append("\n-----END PUBLIC KEY-----");
	
	cout << "公钥:" << strkey << endl;
	BIO *bio = NULL;
	RSA *pkey = NULL;
	char *chkey = const_cast<char *>(strkey.c_str());
	if(NULL==(bio=BIO_new_mem_buf(chkey,-1))){
		cout << "失败222" << endl;
		return false;
	}
	if(NULL==(pkey=PEM_read_bio_RSA_PUBKEY(bio,NULL,NULL,NULL))){
		cout << "失败333" << endl;
		return false;
	}

	bool ret = true;
	string tmpS = string();
	string signtmp = sign;
	//chunk_split(signtmp,64);
	//signtmp.append("\n");
	cout << "signtmp=" << signtmp << endl;
	if(!b64_decode(signtmp,tmpS)){
		cout << "失败444" << endl;
		return false;
	}
	//tmpS.append("\n");
	cout << "------------" << endl;
	cout << "tmpS=" << tmpS << endl;
	cout << "------------" << endl;
//	for(int i=0;i<tmpS.length();++i){
//		if(' '==tmpS[i]){
//			cout << "len=" << tmpS.length() << ",i=" << i << ",val=" << (int)tmpS[i] << endl;
//		}
//	}
	char filename[] = "sign.sha1"; // 此处写入文件名 
	ofstream fout(filename,std::ios::out | std::ios::binary);
	fout << tmpS; // fout用法和cout一致, 不过是写到文件里面去
	cout << "ERR_get_error()=" << ERR_get_error() << endl;
	if(1!=RSA_verify(NID_sha1,(const unsigned char *)hashdata.c_str(),(unsigned int)hashdata.length(),(unsigned char *)tmpS.c_str(),(unsigned int)tmpS.length(),pkey)){
		ret = false;
		long errcode = ERR_get_error();
		char buferr[1024];
		memset(buferr,0,sizeof(buferr));
		ERR_error_string(errcode,buferr);
		cout << "失败555,code=" << errcode << ",errstr=" << buferr << endl;
	}
	RSA_free(pkey);
	return ret;
}
/*
*/
int main(int argc, char *argv[])
{
	printf("Hello, world\n");
	string pubkey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAgRNdVrI0PnfI4SHERW9IWP6/gtYF1MCYuwC6h6FSFh/ja7H4hcNFfgKgNp7JsLkm414VRddGVuaNTLSvY1CKHkhH4pAWCiaAn9ASJanrLzKvx6ScTiZSn+4mx0VwjoG62ESawCCyNAzmHydW+DZFWS7PiyqT4bk33tmcnY96/Jmbsenw7ExYWITmqGaEdlVyFPbGXDC0bEQSNFPNFnlkv0xK0eYdmQLOXiEwZpzLvmaFRw9rgMgYLZoDHcAvsLw/5okVoJTzd/WkWSkTiEKKEmWlSq+CZ7Inmf5pkjB4f1Pdbb6CiwJh1dfPIh6AJTYLjMY/g8iecSbJtrUsKkMLYwIDAQAB";
	string data="{\"orderId\":\"12999763169054705758.1389810966900993\",\"packageName\":\"com.ENP.myongjiang.kr.googleplay\",\"productId\":\"com.zhsj.gold0001\",\"purchaseTime\":1428056813610,\"purchaseState\":0,\"purchaseToken\":\"edckdgalaonbfmjghaifgagc.AO-J1OyQALws1UWsoHLP66twBvMMTF5qDyR8aeKAy9rGYw2JTMVnZzmDSEjyD8rmnsI11kILOfqprBr0jZBvYqThdGb5DfnT4t9vrM-tzVp_VLsI4k-PhmmUhJJi7z7mPudKN8e65s_59a6aCyR2WXeEVOIBuwU2eA\"}";
	string sign="NISm29p4PRZaQ+1pJspYziG6w0Ag6cLrvKpiPu+bH62JB97+79ntyhcoZb47lDB9vjSEkOWomf9koFwKWvCdo6nrrdpc0GlPInsYzBzoZVoF75nHaMXJoaCQ9kJ2gxZC4mznAEKVb5iyw/Ool1pAFLCevpQSzU0KTWYryLAOteTeATlub8YCYCY4vZyNUM7XigKAjS8weR7aQPrahOC3QDw68OIDKVIejiXIcWdkG+5fwddodpGfUbTqUIZuPFV/m058t7dtF5FBE7Mamw0sHL9/ccmzzGoNFfBOXKL0r3zepHqK6SuebGzbxGnQfmjWHq1+6wgAG470SRrwd8F8zQ==";
	bool ret = gg_verify(pubkey,data,sign);
	cout << "验签" << (ret?"成功":"失败") << endl;
	
	return 0;
}
