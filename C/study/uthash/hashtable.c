/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on October 25, 2014, 7:01 PM
 */
//////////////////////////////////////////////////////////////////////////////
#include "hashtable.h"
#include "testistr.h"

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param users
 * @param iUserid
 * @return 
 */
stExampleIStr *  fIStrFindItemById(stExampleIStr *users,int iUserid){
    stExampleIStr *pFind;
    HASH_FIND_INT(users,&iUserid,pFind);
    return pFind;
}

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param users
 * @param iUserId
 * @param sUsername
 * @return 
 */
int fIStrAddItemToHashTable(stExampleIStr **users,int iUserId,char *sUsername,stExampleIStr **st){
    
    int ret = 0;

    HASH_FIND_INT(*users,&iUserId,*st);
    if (!*st) {
        *st =  malloc(sizeof(stExampleIStr));
        if (*st == NULL) ret = -1;
        (*st)->id = iUserId;
        HASH_ADD_INT(*users,id,*st);
        strcpy((*st)->sUsername,sUsername);
        printf("Add an item.\n");
        ret = 1;
    } else {
        printf("Not Uniqueness\n");
        ret = 0;
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param pUsers
 * @param iUserId
 * @return 
 */
int fIStrDelItemById(stExampleIStr *pUsers,int iUserId){  
    
    int ret = 0;
    stExampleIStr *tmp = fIStrFindItemById(pUsers,iUserId);
    if (tmp) {
        HASH_DEL(pUsers,tmp);
        free(tmp);
        tmp = NULL;
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param pUsers
 */
void fIStrDelAllItem(stExampleIStr *pUsers) {
    stExampleIStr *current_user, *tmp;

    HASH_ITER(hh, pUsers, current_user, tmp) {
        HASH_DEL(pUsers, current_user); /* delete; users advances to next */
        free(current_user); /* optional- if you want to free  */
    }

    pUsers = NULL;
}

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param pUsers
 */
void fIStrPrintHashTable(stExampleIStr *pUsers){
    stExampleIStr *stFirst;
    for(stFirst=pUsers; stFirst != NULL; stFirst=(stExampleIStr*)(stFirst->hh.next)) {
        printf("key %d, username %s\n", stFirst->id, stFirst->sUsername);
    }
}

int IStrId_sort(stExampleIStr *a, stExampleIStr *b) {
    return (a->id - b->id);
}

int IStrName_sort(stExampleIStr *a, stExampleIStr *b) {
    return strcmp(a->sUsername,b->sUsername);
}