
#include <unistd.h>
#include "lib_system.h"

// Init the system,such as log signal network thread etc...
int InitSystem(){  
    InitSystemPrint();
    InitSystemVar();
    InitConfigSystem();
    
    InitSystemThread(THREADNUMBER, QUEUENUMBER);  
    InitSystemNetwork();
    
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
    
    config->system.basename = newString(buf);
    
    config->server.base = event_base_new();
}

void InitConfigSystem(){ 
    config->server.serverip = ReadConfigfile(confPath,"serverip");
    config->server.serverport = GetConfInt(confPath,"serverport");
    config->server.webport = GetConfInt(confPath,"webport");

    printf("\tL__________System params:\n");
    printf("\tL__________Server IP:%s\n",config->server.serverip);
    printf("\tL__________Server Port:%d\n",config->server.serverport);
    printf("\tL__________Web Port:%d\n",config->server.webport);
}

void InitSystemThread(int threadnumber,int queuenumber){
    pthread_mutex_init(&(config->server.lock), NULL);

    if ((config->server.threadpool = threadpool_create(threadnumber, queuenumber, 0)) == NULL) {
        printf("Create thread pool error!\n");
        DEBUG("Create thread pool error!\n");
        exit(-1);
    }
}

void InitSystemNetwork(){

    //////////////////////////////////////////////////////////////////////////////
    // create tcp server
    int listen_backlog = 32;

    int ret = create_libevent_listen(config->server.serverport,listen_backlog,do_accept);
    if(ret <= 0){
        printf("System Can't Running with Network.\n");
        DEBUG("System Can't Running with Network.\n");
        exit(-1);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // create http server
    config->server.httpd = evhttp_new(config->server.base);

    evhttp_bind_socket(config->server.httpd,"0.0.0.0",config->server.webport);
    evhttp_set_timeout(config->server.httpd,10);
    
    evhttp_set_gencb(config->server.httpd,http_request_handle,NULL);
    evhttp_set_cb(config->server.httpd,"/hello",http_request_special_example,NULL);
}

// open the log file
void InitLogSystem(){  
    if (DEBUG_LOG_ENABLED || ERROR_LOG_ENABLED) {
        OpenLogFile(log_path);
    }
}

void sig_handler(int signo) {

    switch (signo) {
        case SIGINT:    // interrupt the programe
        {
            ERROR("%s", "received SIGINT\n");
            DestorySystem();
            break;
        }
        case SIGPIPE:   // the server is out of connect
        {
            INFO("%s", "received SIGPIPE\n");
            ERROR("%s", "received SIGPIPE\n");
            signal(SIGPIPE, SIG_IGN);
            break;
        }
        case SIGTSTP:   // stop the programe
        {
            printf("Ctrl+z,ignore\n");
            signal(SIGTSTP, SIG_DFL);
            break;
        }
        case SIGTERM:   // kill the programe
        {
            printf("SIGTERM,ignore\n");
            signal(SIGTERM, SIG_IGN);
            break;
        }
        case SIGHUP:    // restart the programe.
        {
            printf("get SIGHUP\n");
            sigset_t x;
            sigemptyset(&x);
            sigaddset(&x, SIGHUP);
            sigprocmask(SIG_UNBLOCK, &x, NULL);

//            const char *exepath = newMultiString("%s%s", config->system.basename, "smarthome");
//            execl(exepath, NULL);
  
            exit(1);
      
            break;
        }
        default:
        {

        }
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

    struct sigaction new_action;
    struct sigaction oldaction;
//    
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGINT);
    sigaddset(&new_action.sa_mask, SIGPIPE);
    sigaddset(&new_action.sa_mask, SIGTERM);
    sigaddset(&new_action.sa_mask, SIGTSTP);
    
    new_action.sa_handler = sig_handler;

    new_action.sa_flags = 0;
    
    sigaction(SIGHUP,NULL,&oldaction);
    
    if (oldaction.sa_handler != SIG_IGN) {
        sigaction(SIGHUP,&new_action,NULL);
    }

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

/** 
 创建线程
 */

pthread_t CreateThread(void *ThreadFunction) {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    if (pthread_create(&tid, &attr,ThreadFunction, NULL) != 0) {
            printf("创建主接收事件监听线程失败");
        return 0;
    
    }
    else
        return tid;
}

/**
 * 
 */
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
        if(config->system.basename){
            freeData(config->system.basename);
        }
        
        if(config->server.serverip){
            freeData(config->server.serverip);
        }

        if (config->server.threadpool) {
            threadpool_destroy(config->server.threadpool, 0);
        }

        pthread_mutex_destroy(&(config->server.lock));

        if(config->server.listen_event){
            event_free(config->server.listen_event);
        }
        
        if(config->server.httpd){
            evhttp_free(config->server.httpd);
        }

        if(config->server.bev){
            bufferevent_free(config->server.bev);
        }
        
        if(config->server.base){
            event_base_free(config->server.base);
        }

        freeData(config);
    }
}