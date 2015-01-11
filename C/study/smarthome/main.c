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
int main(int argc, char** argv) {
    
    // test

//    return 0; 
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
    INFO("%s%s","This is an error of log file.","do you have a list for this?\n");
    ERROR("%s%s","This is an error of log file.","do you have a list for this?\n");
 
    // setup server socket
//    int SmartPort = 1249;
//    int fd = lib_create_server_socket("*",SmartPort);
//    if (fd < 0) {
//        return -1;
//    }

//    int connect_prot = 3338;
//    int cfd = lib_connect_server_socket("192.168.2.249", connect_prot);
//    if (cfd < 0) {
//        return -1;
//    }
        
//    while(1){
//        usleep(100000);
//    }
    
    DestorySystem();
    return (EXIT_SUCCESS);
}

