
#include "base.h"
#include "main.h"

// string
char *newData(int size){
    char *d = malloc(size);
    if (d == NULL) return NULL;
    memset(d,0,size);
    return d;
}


char *newString(char* s){
    char *d = malloc(strlen(s) +1);
    if (d == NULL) return NULL;
    memset(d,0,(strlen(s)+1));
    strcpy(d,s);
    return d;
}

char* newMultiString(const char *msg, ...) {
    char buf[2*4096];
    va_list argp;
    va_start(argp, msg);
    vsnprintf(buf, 2*4096, msg, argp);
    va_end(argp); 

    char *data = newString(buf);
    return data;
}

void freeData(char *p){
    if(p != NULL){
        free(p);
        p = NULL;
    }
}

char* getCurrentTime(){
    
    time_t time_raw_format;
    time(&time_raw_format);
    struct tm *curtime = localtime(&time_raw_format);
    
    if (systemTime) {
        sprintf(systemTime,"%d-%02d-%02d:%02d:%02d:%02d",curtime->tm_year+1900,curtime->tm_mon+1,curtime->tm_mday,\
                                            curtime->tm_hour,curtime->tm_min,curtime->tm_sec);
    } else {
        ERROR("%s\n",strerror(errno));
        systemTime = NULL;
    }
    return systemTime;
}


char *ReadConfigfile(char *fileName, char *item) {
    FILE *fp;
    char *locate = NULL;
    char *pmove = NULL;
    char confLine[ CONLINELENGTH] = {};
    char context[CONLINELENGTH] = {};
    int result = 1;
    char *pline;
    int itl;


    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("打开文件 : %s 失败!!\n", fileName);
        return NULL;
    }

    while (fgets(confLine, CONLINELENGTH, fp) != NULL) {
        pline = confLine;
        if (*pline == '#'||*pline == '/'||*pline == '*') {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
        while (isspace(*pline) != 0)pline++;
        locate = strchr(pline, '=');
        if (locate == NULL) {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
        pmove = locate;
        pmove--;
        while (isspace(*pmove) != 0)pmove--;
        itl = pmove - pline + 1;
        if (itl == strlen(item)) {
            result = strncasecmp(pline, item, itl);
            if (result == 0) {
                locate++;
                while (isspace(*locate) != 0)locate++;
                pmove = locate;
                while (isspace(*pmove) == 0)pmove++;
                if (pmove - locate + 1 > 0) {
                    strncpy(context, locate, pmove - locate + 1);
                    break;
                } else {
                    fclose(fp);
                    return NULL;
                }
            } else {
                memset(confLine, '0', CONLINELENGTH);
                continue;
            }
        } else {
            memset(confLine, '0', CONLINELENGTH);
            continue;
        }
    }
    fclose(fp);
    char * rtn=(char *)malloc(strlen(context)+1);
    memset(rtn,0,strlen(context)+1);
    strcpy(rtn,context);

    char *tmp=rtn;
    while(*tmp!=';')           //去掉字符串结束符'\0'前的'\n'    
        tmp++;  
     *tmp   =   '\0';
    return rtn;
}


int GetConfInt(char * confPath,char *name)
{
    int rtn=0;
    char *readname=ReadConfigfile(confPath,name);
    if(readname!=NULL)
    {
        rtn=atol(readname);
        int len=strlen(readname);
        char * ls=readname;
        ls+=len-1;
        *ls=tolower(*ls);
        //内存单位换算，结果为byte
        if(*ls=='m')//M
            rtn=rtn*1024*1024;
        if(*ls=='k')//K
            rtn=rtn*1024;
        if(*ls=='g')//G
            rtn=rtn*1024*1024*1024;
        //时间单位换算，结果为秒
        if(*ls=='s')//分
            rtn=rtn*60;
        if(*ls=='h')//小时
            rtn=rtn*60*60;
        if(*ls=='d')//天
            rtn=rtn*60*60*24;
    }
    else
    {
        printf("配置文件中找不到叫:%s的项!",name);
    }
    free(readname);
    return rtn;
}