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
#include <sys/socket.h>

//#define NDEBUG
#include <assert.h>
    
#include "log.h"
#include "lib_network.h"
#include "lib_system.h"
#include "uthash.h"
    
#include "cii/stack.h"
#include "cii/atom.h"
#include "cii/mem.h"
#include "cii/list.h"
#include "cii/table.h"
#include "cii/array.h"
#include "cii/ring.h"
#include "cii/arrayrep.h"
#include "cii/except.h"
 
    #define true 1
    #define false 0
    
    char *systemTime;
    
    char *log_path;
    char *confPath;
    struct config_t *config;

    struct config_t {
        struct {
            char *basename;
            FILE *logfile;
        } system;

        struct {
            char *serverip;
            int serverport;
        } server;
    };
    
    void *TestThread(void *p);
    void *TestThread2(void *p);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

