
#include "lib_system.h" 

void SetupSignal() {
    signal(SIGPIPE, SIG_IGN);
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;

    if (sigemptyset(&sa.sa_mask) == -1 ||
            sigaction(SIGPIPE, &sa, 0) == -1) {
        exit(-1);
    }
}