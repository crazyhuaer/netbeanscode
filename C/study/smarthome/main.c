/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on December 28, 2014, 11:17 PM
 */

#include "main.h"

#define MAX_LINE    256

void vfree(const void*,void **,void *);
void test(Ring_T data);

int main(int argc, char** argv) {
    
    // test
    //////////////////////////////////////////////////////////////////////////////
    Stack_T names = Stack_new();
    
    int testst = 5;
    int testtest2 = 6;
    Stack_push(names,&testst);
    
    Stack_push(names,&testtest2);
    
    int *getdata = Stack_pop(names);
    
    if (getdata) {
        printf("getdata:%d\n",*getdata);
    }else{
        printf("Stack is empty\n");
    }
    
    getdata = Stack_pop(names);
    if (getdata) {
        printf("getdata:%d\n",*getdata);
    }else{
        printf("Stack is empty\n");
    }
    Stack_free(&names);
    //////////////////////////////////////////////////////////////////////////////
    struct config_t *config_test;
    NEW(config_test);
    
    config_test->server.serverip = newString("192.168.2.1301");
    
    printf("%s\n",config_test->server.serverip);
    freeData(config_test->server.serverip);
    FREE(config_test);
    //////////////////////////////////////////////////////////////////////////////
    List_T p1 = List_list(NULL);
    p1 = List_push(NULL,"China");
    p1 = List_push(p1,"American");
    p1 = List_push(p1,"Cananda");
    
    p1 = List_append(p1,List_list("hello",NULL));

    List_free(&p1);
    //////////////////////////////////////////////////////////////////////////////
//    const char *str; 
//    str = Atom_string("This is my test.");
//    printf("%s\n",str);
    
    //////////////////////////////////////////////////////////////////////////////
    Table_T table = Table_new(0,NULL,NULL);
    
    int fd = 15;
     
    int counts = 23;
    
    Table_put(table,&fd,&counts);
    
    int *values = (int *)Table_get(table,&fd);
    if (values) {
        printf("key:%d,value:%d\n",fd,*values);
        int count = 30;
        Table_put(table,&fd,&count);
        
        values = (int *)Table_get(table,&fd);
        if (values) {
            printf("key:%d,value:%d\n",fd,*values);
        }   
    } else {
        printf("can't get value by key:%d\n",fd);
    }

    int table_length = Table_length(table);
    printf("table length:%d\n",table_length);
    
    Table_remove(table,&fd);

    values = (int *) Table_get(table, &fd);
    if (!values) {
        printf("can't get value by key:%d\n",fd);
    }   
    
    table_length = Table_length(table);
    printf("table remove fd:%d length:%d\n", fd,table_length);
    
    Table_map(table,vfree,NULL);
    Table_free(&table);
    //////////////////////////////////////////////////////////////////////////////
//    Array_T array;
//    array = Array_new(1, 3);
    //////////////////////////////////////////////////////////////////////////////
    Ring_T ring = Ring_ring("List","Sets","Array","String",NULL);
    int sizeofring = Ring_length(ring);
  
    char *data = (sizeofring > 3) ? Ring_get(ring,3) : NULL ;
    printf("sizeofring:%d,3:%s\n",sizeofring,data);
    
    char *first = Ring_put(ring,0,"ring");
    char *adds = Ring_add(ring,1,"adddata");
    data = Ring_get(ring,0);
    sizeofring = Ring_length(ring);
    printf("sizeofring:%d,first:%s,0:%s,adds:%s\n",sizeofring,first,data,adds);
    
    Ring_free(&ring);
    //////////////////////////////////////////////////////////////////////////////
    Ring_T ring2 = Ring_new();
    
    Ring_add(ring2,0,"I ");
    Ring_add(ring2,0,"Love ");
    Ring_addhi(ring2,"U!");
    sizeofring = Ring_length(ring2);
    printf("sizeofring:%d %s %s %s\n",sizeofring,(char *)Ring_get(ring2,0),\
                         (char *)Ring_get(ring2,1),(char *)Ring_get(ring2,2));
    
    Ring_free(&ring2);
    //////////////////////////////////////////////////////////////////////////////
    Ring_T ring3 = (Ring_new());
    test(ring3);
    sizeofring = Ring_length(ring3);
    printf("sizeofring:%d %s %s %s\n",sizeofring,(char *)Ring_get(ring3,0),\
                         (char *)Ring_get(ring3,1),(char *)Ring_get(ring3,2));
    
    Ring_free(&ring3);
    //////////////////////////////////////////////////////////////////////////////
    //assert(ring3);
//    TRY 
//    a[2] = 5;
//    EXCEPT(e)
//            
//    END_TRY;
    
    //////////////////////////////////////////////////////////////////////////////
    //return 0; 
    // end
    //////////////////////////////////////////////////////////////////////////////
    // init var
    int ret = 0;
    int i;
    
    // system init
    ret = InitSystem();
    if(ret < 0){
        return -1;
    }
    
    // test log system
//    INFO("%s%s","This is an error of log file.","do you have a list for this?\n");
//    ERROR("%s%s","This is an error of log file.","do you have a list for this?\n");

    // setup server socket
//    int SmartPort = 1249;
//    int fd = lib_create_server_socket("*",SmartPort);
//    if (fd < 0) {
//        return -1;
//    }
    
//    int connect_prot = 3338;
//    int cfd = lib_connect_server_socket("192.168.2.249", connect_prot);
//    if (cfd < 0) {
//        INFO("%s%s%d", "can\t connect the server","192.168.2.249:",connect_prot);
//        return -1;
//    }
//    CreateThread(TestThread);
//    CreateThread(TestThread2);
    //////////////////////////////////////////////////////////////////////////////
    // test thread.
//    for(i = 0; i < 8192; i++) {
//        if (i%2 == 1) {
//            threadpool_add(config->server.threadpool, TestThread, &i, 0);
//        } else {
//            threadpool_add(config->server.threadpool, TestThread2, NULL, 0);
//        }
//    }
//    
//    sleep(1);
    //////////////////////////////////////////////////////////////////////////////
    // libevent.

    // evhttp

    
    // libmemcached
    memcached_server_st *servers = NULL;
    memcached_st *memc;
    memcached_return rc;
    char *key= "keystring";
    char *value= "keyvalue";

    //memcached_server_st *memcached_servers_parse (char *server_strings);
    memc= memcached_create(NULL);

    servers= memcached_server_list_append(servers, "localhost", 11211, &rc);
    rc= memcached_server_push(memc, servers);

    if (rc == MEMCACHED_SUCCESS)
      fprintf(stderr,"Added server successfully\n");
    else
      fprintf(stderr,"Couldn't add server: %s\n",memcached_strerror(memc, rc));

    rc= memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);

    if (rc == MEMCACHED_SUCCESS)
      fprintf(stderr,"Key stored successfully\n");
    else
      fprintf(stderr,"Couldn't store key: %s\n",memcached_strerror(memc, rc));

//
//    rc = memcached_mget(memc, keys, key_length, 1);
//
//    if (rc == MEMCACHED_SUCCESS) {
//        while ((return_value = memcached_fetch(memc, return_key, &return_key_length,
//                &return_value_length, &flags, &rc)) != NULL) {
//            if (rc == MEMCACHED_SUCCESS) {
//                fprintf(stderr, "Key %s returned %s\n", return_key, return_value);
//            }
//        }
//    }

    
    
    
    // start event loop.
    event_base_dispatch(config->server.base);
    
    //////////////////////////////////////////////////////////////////////////////
    DestorySystem();
    return (EXIT_SUCCESS);
}

void vfree(const void* key,void **count,void *c1){
    FREE(count);
}

void TestThread(void *p) {
    int *pData = (int*)p;
    //printf("test thread:%d\n",*pData);
    //DEBUG("test thread\n");
}

void TestThread2(void *p) {
    //printf("test thread2\n");
    //DEBUG("test thread2\n");
}
void test(Ring_T data){
    Ring_add(data,0,"I ");
    Ring_add(data,0,"Love ");
    Ring_addhi(data,"U!");
}

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param listener
 * @param event
 * @param arg
 */
void do_accept(evutil_socket_t listener, short event, void *arg){
    struct event_base *base = (struct event_base *)arg;
    evutil_socket_t fd;
    struct sockaddr_in sin;
    socklen_t slen = sizeof(sin);
    fd = accept(listener, (struct sockaddr *)&sin, &slen);
    if (fd < 0) {
        perror("accept");
        return;
    }
    
    char *cip= inet_ntoa(sin.sin_addr);
    
//    if (fd > FD_SETSIZE) { //这个if是参考了那个ROT13的例子，貌似是官方的疏漏，从select-based例子里抄过来忘了改
//        perror("fd > FD_SETSIZE\n");
//        return;
//    }

    printf("ACCEPT: fd = %u,ip = %s\n", fd,cip);

    evutil_make_socket_nonblocking(fd);
    config->server.bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(config->server.bev, read_cb, write_cb, error_cb, arg);
    bufferevent_enable(config->server.bev, EV_READ|EV_PERSIST);
}

void read_cb(struct bufferevent *bev, void *arg){
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
        line[n] = '\0';
        printf("fd=%u, read line: %s\n", fd, line);

        bufferevent_write(bev, line, n);
    }
    
    // 这里处理收到的命令信号
    int length = strlen("hello");
    int ret = strncmp(line,"hello",length);
    if(ret == 0 && (line[length] == '\r') || (line[length] == '\n') ){
        printf("get hello!\n");
    }
    
    bufferevent_enable(bev, EV_WRITE | EV_PERSIST);
}

void write_cb(struct bufferevent *bev, void *arg) {
    evutil_socket_t fd = bufferevent_getfd(bev);
    char *buf = "hello world!\n";
    int length = strlen(buf);
    int size = 0,send_size=0;
    while(size < length){
        send_size = send(fd,buf+size,length-size,0);
        if(send_size < 0){
            if(errno == EAGAIN){
                return;
            }
        }
        size += send_size;
    }
    printf(" fd : %d,write %s size:%d\n",fd,buf,size);
}

void error_cb(struct bufferevent *bev, short event, void *arg){
    evutil_socket_t fd = bufferevent_getfd(bev);
    printf("fd = %u, ", fd);
    if (event & BEV_EVENT_TIMEOUT) {
        printf("Timed out\n"); //if bufferevent_set_timeouts() called
    }
    else if (event & BEV_EVENT_EOF) {
        printf("connection closed\n");
    }
    else if (event & BEV_EVENT_ERROR) {
        printf("some other error\n");
    }
    bufferevent_free(bev);
}

//////////////////////////////////////////////////////////////////////////////
void http_request_handle(struct evhttp_request *req,void *arg){
    char output[2048] = "\0";
    char tmp[1024];

    //获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
    const char *uri;
    uri = evhttp_request_uri(req);
    sprintf(tmp, "uri=%s\n", uri);
    strcat(output, tmp);

    sprintf(tmp, "uri=%s\n", req->uri);
    strcat(output, tmp);
    
    //decoded uri
    char *decoded_uri;
    decoded_uri = evhttp_decode_uri(uri);
    sprintf(tmp, "decoded_uri=%s\n", decoded_uri);
    strcat(output, tmp);

    //解析URI的参数(即GET方法的参数)
    struct evkeyvalq params;
    evhttp_parse_query(decoded_uri, &params);
    sprintf(tmp, "q=%s\n", evhttp_find_header(&params, "q"));
    const char *params_q = evhttp_find_header(&params, "q");
    strcat(output, tmp);
    sprintf(tmp, "s=%s\n", evhttp_find_header(&params, "s"));
    const char *params_s = evhttp_find_header(&params, "s");
    strcat(output, tmp);
    free(decoded_uri);

    //获取POST方法的数据
    char *post_data = (char *) EVBUFFER_DATA(req->input_buffer);
    sprintf(tmp, "post_data=%s\n", post_data);
    strcat(output, tmp);

    /*
    具体的：可以根据GET/POST的参数执行相应操作，然后将结果输出
    ...
    */

    /* 输出到客户端 */

    //HTTP header
    evhttp_add_header(req->output_headers, "Server", "my httpd v0.01");
    evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");
    
    //输出的内容
    struct evbuffer *buf;
    buf = evbuffer_new();
    evbuffer_add_printf(buf, "It works!\n%s\nparams_q=%s,params_s=%s\n", output,params_q,params_s);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}

void http_request_special_example(struct evhttp_request *req,void *arg){
    char output[2048] = "\0";
    char tmp[1024];

    //获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
    const char *uri;
    uri = evhttp_request_uri(req);
//    sprintf(tmp, "uri=%s\n", uri);
//    strcat(output, tmp);

//    sprintf(tmp, "uri=%s\n", req->uri);
//    strcat(output, tmp);
    //decoded uri
    char *decoded_uri;
    decoded_uri = evhttp_decode_uri(uri);
//    sprintf(tmp, "decoded_uri=%s\n", decoded_uri);
//    strcat(output, tmp);

    //解析URI的参数(即GET方法的参数)
    struct evkeyvalq params;
    evhttp_parse_query(decoded_uri, &params);
    sprintf(tmp, "q=%s\n", evhttp_find_header(&params, "q"));
    const char *params_q = evhttp_find_header(&params, "q");
    strcat(output, tmp);
    sprintf(tmp, "s=%s\n", evhttp_find_header(&params, "s"));
    const char *params_s = evhttp_find_header(&params, "s");
    strcat(output, tmp);
    free(decoded_uri);

//    //获取POST方法的数据
    char *post_data = (char *) EVBUFFER_DATA(req->input_buffer);
    sprintf(tmp, "post_data=%s\n", post_data);
    strcat(output, tmp);

    //HTTP header
    evhttp_add_header(req->output_headers, "Server", "my httpd v0.01");
    evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");
    
    struct evbuffer *databuf = evbuffer_new();
    evbuffer_add_printf(databuf,output,"%s");
    
    evhttp_send_reply(req, HTTP_OK, "OK", databuf);
    evbuffer_free(databuf);
    
    // kill the base loop
    // 这其实是不应该使用的，不是特别情况，不用关闭
//    if (params_q) {
//        int ret = atoi(params_q);
//        if (ret == 15) {
//            event_base_loopbreak(config->server.base);
//        }
//    }
}