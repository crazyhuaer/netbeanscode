
#include "lib_network.h"


int lib_create_server_socket(const char* pIp, int nPort) {
    int nFd;
    struct sockaddr_in sockAddr;
    // 创建TCP socket
    if (-1 == (nFd = socket(AF_INET, SOCK_STREAM, 0))) {
        //Error("socket create error: %s", strerror(errno));
        return 0;
    }

    // 地址重用
    int nOptVal = 1;
    socklen_t nOptLen = sizeof (int);
    if (-1 == setsockopt(nFd, SOL_SOCKET, SO_REUSEADDR , &nOptVal, nOptLen)) {
        //Error("setsockopt(...) error,地址重用: %s\n", strerror(errno));
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
            printf("inet_addr failed!ipaddr=[%s]!%s\n", pIp, strerror(errno));
            return 0;
        }
        sockAddr.sin_addr.s_addr = nNetIP;
    }
    if (0 != bind(nFd, (struct sockaddr*) &sockAddr, sizeof (sockAddr))) {
        printf("bind(...) error: %s\n", strerror(errno));
        return 0;
    }
    // 监听端口
    if (0 != listen(nFd, 100)) {
        printf("listen(...) error: %s\n", strerror(errno));
        return 0;
    }

    return nFd;
}