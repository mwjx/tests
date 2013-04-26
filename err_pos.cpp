void c_cmd_buf::_recv_bc(void)
{
        //活动触发器,目前主要管理广播
        //输入:无
        //输出:无
        //cout << "c_cmd_buf::_recv_bc start" << endl;
        for(;;){
                mt_bc->lock();
                while(p_bl->bc_empty()){
                        mt_bc->wait();
                }
                mt_bc->unlock();
                p_bl->get_ul(obj_bc); //有，取新广播到本地
                if(!obj_bc.to.empty()){start_bc();}
        }
}
void c_cmd_buf::start_bc(void)
{
        //开始广播
        //输入:无
        //输出:无
        //cout << "c_cmd_buf::start_bc" << endl;
        //查找广播uid的socket
        //加入写监听
        set<int>::iterator it;
        int cli,no;
        for(it = obj_bc.to.begin();it != obj_bc.to.end();++it){
                cli = *it; //用户ID
                //cerr << "*it=" << *it << endl;
                no = p_us->nobyuid(cli);
                if(no<0){continue;} //客户端不存在
//              if(p_gms->get_more(cli,buf_))
//                      p_bufio->push_write(fd,buf_,strlen(buf_)+1);
                if(p_bl->get_more(cli,buf_))
                        p_sockls->push_write(no,buf_,strlen(buf_)+1);
                //p_bufio->(buf_,strlen(buf_)+1,fd);
        }
        init_bc();
        /**/
}

int c_usersock::nobyuid(int u)
{
        //根据用户取连接
        if(mp_cs.end()==mp_cs.find(u)){return -1;}
        return mp_cs[u];
}