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
#include <glib-2.0/glib.h>
    //////////////////////////////////////////////////////////////////////////////
    typedef struct _student_{
        int id;
        char *str;
        UT_hash_handle hh;
    }stIntStr;
    
    typedef struct _hashtable_{
        int             nodetype;   // 节点类型 1:int 2:string 3:point 4:struct 
        unsigned int    size;
        unsigned int    current;
        stIntStr        **headNode;
        stIntStr        *NodeSpace[1];
    }stHashTable;
    
    //////////////////////////////////////////////////////////////////////////////
    // global var
    stIntStr *sTable;
    stHashTable *hHashTable;
    
    //////////////////////////////////////////////////////////////////////////////
    void fInitData(int length);
    void fPrintWelcome();

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

