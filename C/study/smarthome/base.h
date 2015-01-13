/* 
 * File:   base.h
 * Author: topseten
 *
 * Created on December 29, 2014, 2:51 PM
 */

#ifndef BASE_H
#define	BASE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #include <time.h>
    #include <stdlib.h>
    #include <string.h>
    
    #define CONLINELENGTH 1024

    char *newData(unsigned int size);
    char *newString(char *s);
    char *newMultiString(const char* msg, ...);
    char * getCurrentTime();
    
    char *ReadConfigfile(char *fileName, char *item);
    int GetConfInt(char * confPath,char *name);

#ifdef	__cplusplus
}
#endif

#endif	/* BASE_H */

