
#include "lib_network.h"

/* 
 * function: lib_create_server_socket
 * Author: topseten
 *
 */
int lib_create_server_socket(const char* pIp, int nPort) {
    int nFd;
    struct sockaddr_in sockAddr;
    // 创建TCP socket
    if (-1 == (nFd = socket(AF_INET, SOCK_STREAM, 0))) {
        ERROR("socket create error: %s",strerror(errno));
        return 0;
    }

    // 地址重用
    int nOptVal = 1;
    socklen_t nOptLen = sizeof (int);
    if (-1 == setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR , &nOptVal, nOptLen)) {
        ERROR("setsockopt(...) error,地址重用: %s\n", strerror(errno));
        return 0;
    }
    memset(&sockAddr, 0, sizeof (sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(nPort);

    if (0 == strcmp(pIp, "*")) {
        sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        in_addr_t nNetIP = inet_addr(pIp);
        if (INADDR_NONE == nNetIP) {
            ERROR("inet_addr failed!ipaddr=[%s]!%s\n", pIp, strerror(errno));
            return 0;
        }
        sockAddr.sin_addr.s_addr = nNetIP;
    }
    if (0 != bind(nFd, (struct sockaddr*) &sockAddr, sizeof (sockAddr))) {
        ERROR("bind(...) error: %s\n", strerror(errno));
        return 0;
    }
    // 监听端口
    if (0 != listen(nFd, 100)) {
        ERROR("listen(...) error: %s\n", strerror(errno));
        return 0;
    }

    return nFd;
}

/* 
 * function: lib_connect_server_socket
 * Author: topseten
 *
 */
int lib_connect_server_socket(char *SIP, int port) {
    int fd;
    struct sockaddr_in addr;
    struct timeval timeo = {3, 0};
    socklen_t len = sizeof (timeo);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd <= 0)
        return 0;
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);
    addr.sin_family = AF_INET;

    addr.sin_addr.s_addr = inet_addr(SIP);
    addr.sin_port = htons(port);
    if (connect(fd, (struct sockaddr*) &addr, sizeof (addr)) == -1)
        return -1;
    else
        return fd;
}

int create_libevent_listen(int listen_port,int listen_backlog,void *do_accept){
    config->server.listener = socket(AF_INET,SOCK_STREAM,0);
    assert(config->server.listener > 0);
    evutil_make_listen_socket_reuseable(config->server.listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(listen_port);

#ifndef WIN32
    {
        int one=1;
        setsockopt(config->server.listener,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
    }
#endif
    
    // bind
    if (bind(config->server.listener, (struct sockaddr *) &sin, sizeof (sin)) < 0) {
        perror("bind");
        return -1;
    }

    // listen
    if (listen(config->server.listener, listen_backlog) < 0) {
        perror("listen");
        return -1;
    }

    printf("Listening...\n");

    // set nonblocking
    evutil_make_socket_nonblocking(config->server.listener);
 
    assert(config->server.base != NULL);
    
    // set listen event to add base.
    struct event *listen_event;
    listen_event = event_new(config->server.base, config->server.listener, EV_READ | EV_PERSIST, 
                            do_accept, (void*) (config->server.base));

    /*  或者采用如下方式
     * struct event *listen_event;
     * struct event_base *base = event_base_new();
     * event_set(&listen_event,listener,EV_READ|EV_PERSIST,do_accept,(void*)base);
     */
    
    event_add(listen_event, NULL);
    return config->server.listener;
}
