

#include "log.h"

void LogPrintfInfo(const char* msg, ...) {
    char buf[PRINTF_MAX_LINE_LEN + 1];
    va_list argp;
    va_start(argp, msg);
    vsnprintf(buf, PRINTF_MAX_LINE_LEN, msg, argp);
    va_end(argp);
    systemTime = getCurrentTime();
    printf("%s%s%s\n", systemTime, "[INFO]", buf);
    LogPrintf("%s%s%s", systemTime, "[INFO]", buf);
}

void LogPrintfDebug(const char* msg, ...) {
    char buf[PRINTF_MAX_LINE_LEN + 1];
    va_list argp;
    va_start(argp, msg);
    vsnprintf(buf, PRINTF_MAX_LINE_LEN, msg, argp);
    va_end(argp);
    systemTime = getCurrentTime();
    LogPrintf("%s%s%s", systemTime, "[Debug]", buf);
}

void LogPrintfError(const char* msg, ...) {
    char buf[PRINTF_MAX_LINE_LEN + 1];
    va_list argp;
    va_start(argp, msg);
    vsnprintf(buf, PRINTF_MAX_LINE_LEN, msg, argp);
    va_end(argp);
    systemTime = getCurrentTime();
    LogPrintf("%s%s%s", systemTime, "[Error]", buf);
}

void LogPrintf(const char* msg, ...)
{
    if (msg)
    {
        char buf[PRINTF_MAX_LINE_LEN + 1];
        va_list argp;
        va_start(argp, msg);
        vsnprintf(buf, PRINTF_MAX_LINE_LEN, msg, argp);
        va_end(argp);
        fputs(buf,config->system.logfile);
    }
}

void OpenLogFile(char *logpath) {
    
    config->system.logfile = fopen(logpath, "a+");
    //logfile = fopen(logpath, "a+");

    if (config->system.logfile == NULL) {
        printf("can't open file %s:%s\n",logpath,strerror(errno));
        exit(-1);
    }
}

void CloseLogFile(){
    if (config->system.logfile) {
        fclose(config->system.logfile);
        config->system.logfile = NULL;
    }    
}