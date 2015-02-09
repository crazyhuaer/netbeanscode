/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on December 28, 2014, 11:17 PM
 */

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
    CreateThread(TestThread);
    CreateThread(TestThread2);
    while(1){
//        char *datas = "hello world\n";
//        int size = send(cfd,datas,sizeof(datas),0);
        usleep(100000);
    }
    
    DestorySystem();
    return (EXIT_SUCCESS);
}

void vfree(const void* key,void **count,void *c1){
    FREE(count);
}

void *TestThread(void *p) {
    printf("test thread\n");
    DEBUG("test thread\n");
}

void *TestThread2(void *p) {
    printf("test thread2\n");
    DEBUG("test thread2\n");
}
void test(Ring_T data){
    Ring_add(data,0,"I ");
    Ring_add(data,0,"Love ");
    Ring_addhi(data,"U! ");
}