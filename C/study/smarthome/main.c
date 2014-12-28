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
    SetupSignal();
    
    // setup server socket
    int SmartPort = 8087;
    int fd = lib_create_server_socket("*",SmartPort);
    if (fd < 0) {
        return -1;
    }
    
    
    
    return (EXIT_SUCCESS);
}

