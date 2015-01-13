

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
        INFO("%s","received SIGPIPE\n");
        ERROR("%s", "received SIGPIPE\n");
        signal(SIGPIPE,SIG_IGN);
    }else if(signo == SIGTSTP){
        printf("Ctrl+z,ignore\n");
        signal(SIGTSTP,SIG_DFL);
    }else if(signo == SIGTERM){
        printf("SIGTERM,ignore\n");
        signal(SIGTERM,SIG_IGN);
    }else{
        ERROR("%s","what?signal?\n");
    }
}

//void handle_pipe(int sig){
//    INFO("%s","received SIGPIPE\n");
//}

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

//    struct sigaction sa;
//    //在linux下写socket的程序的时候，如果尝试send到一个disconnected socket上，就会让底层抛出一个SIGPIPE信号。
//    //这个信号的缺省处理方法是退出进程
//    //重载这个信号的处理方法,如果接收到一个SIGPIPE信号，忽略该信号
//    //sa.sa_handler = handle_pipe;
//    sa.sa_handler = SIG_IGN;
//    sa.sa_flags = 0;
//    //sigemptyset()用来将参数set信号集初始化并清空
//    if (sigemptyset(&sa.sa_mask) == -1 ||
//            sigaction(SIGPIPE, &sa, 0) == -1) {
//        exit(-1);
//    }
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