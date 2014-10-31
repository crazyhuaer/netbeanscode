/* 
 * File:   testistr.h
 * Author: topseten
 *
 * Created on October 31, 2014, 2:10 PM
 */

#ifndef TESTISTR_H
#define	TESTISTR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
    
//////////////////////////////////////////////////////////////////////////////
// struct define
typedef struct _key_int_value_str_ {
    int id;
    char sUsername[20];
    UT_hash_handle hh;
}stExampleIStr;

typedef struct _key_str_value_int_ {
    const char *sUsername;
    int id;
    UT_hash_handle hh;
}stExampleStrI;


//////////////////////////////////////////////////////////////////////////////
// function
    stExampleIStr * fIStrFindItemById(stExampleIStr *users, int iUserid);
    int             fIStrAddItemToHashTable(stExampleIStr **users, int iUserId, char *sUsername, stExampleIStr **st);
    int             fIStrDelItemById(stExampleIStr *pUsers, int iUserId);
    void            fIStrDelAllItem(stExampleIStr *pUsers);
    void            fIStrPrintHashTable(stExampleIStr *pUsers);
    int             IStrId_sort(stExampleIStr *a, stExampleIStr *b);
    int             IStrName_sort(stExampleIStr *a, stExampleIStr *b);


#ifdef	__cplusplus
}
#endif

#endif	/* TESTISTR_H */

