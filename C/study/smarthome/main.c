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
    
    // init var
    int ret = 0;
    int i;
    
    // system init
    ret = InitSystem();
    if(ret < 0){
        return -1;
    }
    
    // setup server socket
//    int SmartPort = 8087;
//    int fd = lib_create_server_socket("*",SmartPort);
//    if (fd < 0) {
//        return -1;
//    }
    
    
    DestorySystem();
    return (EXIT_SUCCESS);
}

