

#include "log.h"

void Print(int level,const char* msg, ...)
{
    if (msg)
    {
        char buf[PRINTF_MAX_LINE_LEN + 1];
        va_list argp;
        va_start(argp, msg);
        vsnprintf(buf, PRINTF_MAX_LINE_LEN, msg, argp);
        va_end(argp);
        
        // TODO write it to the log file or whatever
        char *timeString = getCurrentTime();

        switch(level){
            case 0:
            {   
                printf("%s%s\n",timeString,buf);
                break;
            }
            case 1:
            {
                LogPrintf("%s%s%s",timeString,"[Debug]",buf);
                break;
            }
            case 2:
            {
                LogPrintf("%s%s%s",timeString,"[Error]",buf);
                break;
            }
            default:
            {
                printf("%s%s\n",timeString,buf);
            }
        } 
    }
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
        
        // TODO write it to the log file or whatever
        fputs(buf,logfile);
    }
}

void OpenLogFile(char *logpath) {
    
    logfile = fopen(LOGFILE, "a+");

    if (logfile == NULL) {
        printf("can't open file %s:%s\n",logpath,strerror(errno));
        exit(-1);
    }
}

void CloseLogFile(){
    if (logfile) {
        fclose(logfile);
    }    
}