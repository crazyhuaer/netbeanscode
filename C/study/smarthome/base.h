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
    
    char *newString(char *s);
    char * getCurrentTime();

#ifdef	__cplusplus
}
#endif

#endif	/* BASE_H */

