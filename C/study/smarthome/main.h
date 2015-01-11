/* 
 * File:   main.h
 * Author: topseten
 *
 * Created on December 28, 2014, 11:43 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include <stdio.h>
    #include <stdlib.h>
    #include "log.h"
    #include "lib_network.h"
    #include "lib_system.h"
    #include "uthash.h"

    #define true 1
    #define false 0
    
    char *systemTime;
    char *log_path;
    char *confPath;
    struct config_t *config;

    struct config_t {
        struct {
            FILE *logfile;
        } system;

        struct {
            char *serverip;
            int serverport;
        } server;
    };
    

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

