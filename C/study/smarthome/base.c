
#include "base.h"

char *newString(char* s){
    char *d = malloc(strlen(s) +1);
    if (d == NULL) return NULL;
    strcpy(d,s);
    return d;
}


char* getCurrentTime(){
    time_t time_raw_format;
    time(&time_raw_format);
    time_t curTime = time_raw_format;
    return (ctime(&curTime));
     
}