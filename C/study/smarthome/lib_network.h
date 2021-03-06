/* 
 * File:   network.h
 * Author: topseten
 *
 * Created on December 28, 2014, 11:37 PM
 */

#ifndef NETWORK_H
#define	NETWORK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include "log.h"
#include "include.x86/event2/bufferevent.h"

    int lib_create_server_socket(const char* pIp, int nPort);
    int create_libevent_connect_client();
    
    static void buff_input_cb(struct bufferevent *bev, void *ctx);
    static void buff_ev_cb(struct bufferevent *bev, short events, void *ctx);

#ifdef	__cplusplus
}
#endif

#endif	/* NETWORK_H */

