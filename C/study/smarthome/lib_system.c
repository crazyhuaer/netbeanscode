

#include "lib_system.h"


// Init the system,such as log signal
int InitSystem(){
    InitSystemPrint();
    InitSystemVar();
    InitConfigSystem();
    InitLogSystem();
    SetupSignal();
}

void InitSystemPrint(){
    printf("----------Smart Home Network Programming--------\n");
}

void InitSystemVar(){
    systemTime = newData(20);
    systemTime = getCurrentTime();
    //log_path = newMultiString("%s%s",systemTime,".log");
    // log_path from config file
    
    char buf[1024];
    int count;
    memset(buf,0,1024);
    
    count = readlink( "/proc/self/exe", buf,1024);
    if ( count < 0 || count >=1024) 
    {
        printf( "获取配置文件基础路径发生错误\n" ); 
    }
    while(buf[ count ]!='/')
        count--;
    count++;
    buf[ count ] = '\0';
    
    log_path = newMultiString("%s%s",buf,LOGFILE);
    confPath = newMultiString("%s%s",buf,"config.conf");
    
    config=(struct config_t*)malloc(sizeof(struct config_t));
    memset(config,0,sizeof(struct config_t));
}

void InitConfigSystem(){ 
    config->server.serverip = ReadConfigfile(confPath,"serverip");
    config->server.serverport = GetConfInt(confPath,"serverport");

    printf("\tL__________System params:\n");
    printf("\tL__________Web IP:%s\n",config->server.serverip);
    printf("\tL__________Web Port:%d\n",config->server.serverport);
}

// open the log file
int InitLogSystem(){  
    if (DEBUG_LOG_ENABLED || ERROR_LOG_ENABLED) {
        OpenLogFile(log_path);
    }
}

void sig_handler(int signo) {
    if (signo == SIGINT){
        //INFO("%s","received SIGINT\n");
        ERROR("%s","received SIGINT\n");
        DestorySystem();
    }else if (signo == SIGPIPE) {
        struct sigaction sa;

        sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;

        if (sigemptyset(&sa.sa_mask) == -1 ||
                sigaction(SIGPIPE, &sa, 0) == -1) {
            ERROR("%s","SIGPIPE Error\n");
            DestorySystem();
        }
    }else if(signo == SIGTSTP){
        printf("Ctrl+z,ignore\n");
    }else if(signo == SIGTERM){
        printf("SIGTERM,ignore\n");
    }else{
        ERROR("%s","what?signal?\n");
    }
}

// process the system signals
void SetupSignal() {
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    if (signal(SIGPIPE, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGPIPE\n");
    if (signal(SIGTERM, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGTERM\n");
    if (signal(SIGTSTP, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGPIPE\n");
}

void DestorySystem(){
    if (log_path) {
        freeData(log_path);
    }
    
    if (confPath) {
        freeData(confPath);
    }
    
    if (systemTime){
        freeData(systemTime);
    }
    
    CloseLogFile();
    
    if (config){
        if(config->server.serverip){
            freeData(config->server.serverip);
        }
        
        freeData(config);
    }
    exit(0);
}