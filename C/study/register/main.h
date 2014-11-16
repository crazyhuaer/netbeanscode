/* 
 * File:   main.h
 * Author: topseten
 *
 * Created on November 11, 2014, 9:02 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "include/uthash.h"

    //////////////////////////////////////////////////////////////////////////////
    typedef struct _student_{
        int id;
        char *username;
        UT_hash_handle hh;
    }stStudent;
    
    //////////////////////////////////////////////////////////////////////////////
    // global var
    stStudent *sTable;
    
    //////////////////////////////////////////////////////////////////////////////
    void fPrintWelcome();


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

