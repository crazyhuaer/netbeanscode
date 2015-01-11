/* 
 * File:   log.h
 * Author: topseten
 *
 * Created on December 30, 2014, 9:40 PM
 */

#ifndef LOG_H
#define	LOG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>  
#include "main.h"
   
#define DEBUG_PRINT_ENABLED 1  // uncomment to enable DEBUG statements 
#define DEBUG_LOG_ENABLED 1  // uncomment to enable DEBUG statements
#define ERROR_LOG_ENABLED 1  // uncomment to enable DEBUG statements

#define PRINTF_MAX_LINE_LEN 4096

#define LOGFILE "smarthome.log"

FILE *logfile;
char LogCreated;

void LogPrintfInfo(const char *msg, ...);

void LogPrintfDebug(const char *msg, ...);

void LogPrintfError(const char *msg, ...);

void LogPrintf(const char* msg,...);
extern void OpenLogFile(char *logpath);

#if DEBUG_PRINT_ENABLED
    #define INFO LogPrintfInfo
#else
    #define INFO(format, args...) ((void)0)
#endif


#if DEBUG_LOG_ENABLED
    #define DEBUG LogPrintfDebug
#else
    #define DEBUG(format, args...) ((void)0)
#endif


#if ERROR_LOG_ENABLED
    #define ERROR LogPrintfError
#else
    #define ERROR(format, args...) ((void)0)
#endif    

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

