
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