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
#include "threadpool.h"
#include "include/event2/util.h"
#include "include/event2/event.h"
#include "include/event2/bufferevent.h"
#include "include/evhttp.h"
    
//#ifndef WIN32
//#include <arpa/inet.h>
//#endif  //  !WIN32
//    
//#pragma comment(lib,"ws2_32.lib")
    
    #define true 1
    #define false 0
    
    #define THREADNUMBER 32
    #define QUEUENUMBER  256
    
    
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
            int webport;
            struct event_base *base;
            struct bufferevent *bev;
            struct event *listen_event;
            struct evhttp *httpd;
            evutil_socket_t listener;
            threadpool_t *threadpool;
            pthread_mutex_t lock;
        } server;
    };
    
    void TestThread(void *p);
    void TestThread2(void *p);
    
    void do_accept(evutil_socket_t listener,short event,void *arg);
    void read_cb(struct bufferevent *bev,void *arg);
    void write_cb(struct bufferevent *bev,void *arg);
    void error_cb(struct bufferevent *bev,short event,void *arg);
    
    void http_request_handle(struct evhttp_request *req,void *arg);
    void http_request_special_example(struct evhttp_request *req,void *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

