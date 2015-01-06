

#include "lib_system.h"


// Init the system,such as log signal
int InitSystem(){
    InitSystemVar();
    InitLogSystem();
    SetupSignal();
}

void InitSystemVar(){

}

// open the log file
int InitLogSystem(){ 
    
    if (DEBUG_LOG_ENABLED || ERROR_LOG_ENABLED) {
        OpenLogFile(log_path);
    }

    // test log system
    INFO(2,"%s%s\n","This is an error of log file.","do you have a list for this?");
}

// process the system signals
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

void DestorySystem(){
    if (log_path) {
        free(log_path);
        log_path = NULL;
    }
    CloseLogFile();
}