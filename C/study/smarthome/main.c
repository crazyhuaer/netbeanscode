/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on December 28, 2014, 11:17 PM
 */

#include <unistd.h>
#include <sys/socket.h>
#include "main.h"

/*
 * 
 */
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
    
//    int fd = 15;
//     
//    int counts = 23;
//    
//    Table_put(table,&fd,&counts);
//    
//    int *values = (int *)Table_get(table,&fd);
//    if (values) {
//        printf("key:%d,value:%d\n",fd,*values);
//        int count = 30;
//        Table_put(table,&fd,&count);
//        
//        values = (int *)Table_get(table,&fd);
//        if (values) {
//            printf("key:%d,value:%d\n",fd,*values);
//        }
//        
//        
//    } else {
//        printf("can't get value by key:%d\n",fd);
//    }
//
//    int table_length = Table_length(table);
//    printf("table length:%d\n",table_length);
//    
//    Table_map(table,vfree,NULL);
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
    Ring_addhi(ring2,"U! ");
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
//    // test thread.
//    for(i = 0; i < 8192; i++) {
//        if (i%2 == 1) {
//            threadpool_add(threadpool, TestThread, &i, 0);
//        } else {
//            threadpool_add(threadpool, TestThread2, NULL, 0);
//        }
//    }
//    
//    sleep(1);
    //////////////////////////////////////////////////////////////////////////////
    // test libevent.
    int listen_port = 9999;
    int listen_backlog = 32;
    
    evutil_socket_t listener;
    listener = socket(AF_INET,SOCK_STREAM,0);
    assert(listener > 0);
    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(listen_port);

    if (bind(listener, (struct sockaddr *) &sin, sizeof (sin)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(listener, listen_backlog) < 0) {
        perror("listen");
        return 1;
    }

    printf("Listening...\n");

    evutil_make_socket_nonblocking(listener);

    struct event_base *base = event_base_new();
    assert(base != NULL);
    struct event *listen_event;
    listen_event = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, (void*) base);
    event_add(listen_event, NULL);
    event_base_dispatch(base);

    printf("The End.");
    return 0;
    
    //////////////////////////////////////////////////////////////////////////////
    
//    while(1){
////        char *datas = "hello world\n";
////        int size = send(cfd,datas,sizeof(datas),0);
//        usleep(100000);
//    }
    
    
    
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
    Ring_addhi(data,"U! ");
}

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
    if (fd > FD_SETSIZE) { //这个if是参考了那个ROT13的例子，貌似是官方的疏漏，从select-based例子里抄过来忘了改
        perror("fd > FD_SETSIZE\n");
        return;
    }

    printf("ACCEPT: fd = %u\n", fd);

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

void read_cb(struct bufferevent *bev, void *arg){
#define MAX_LINE    256
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
        line[n] = '\0';
        printf("fd=%u, read line: %s\n", fd, line);

        bufferevent_write(bev, line, n);
    }
}

void write_cb(struct bufferevent *bev, void *arg) {
#define MAX_LINE    256
    char line[MAX_LINE+1];
    int n;
    evutil_socket_t fd = bufferevent_getfd(bev);
    
    
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