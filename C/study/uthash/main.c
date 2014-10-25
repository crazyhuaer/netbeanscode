/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on October 25, 2014, 7:01 PM
 */
//////////////////////////////////////////////////////////////////////////////
// header file.
#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

//////////////////////////////////////////////////////////////////////////////
// struct define
typedef struct _example {
    int id;
    char sUsername[20];
    UT_hash_handle hh;
}stExample;

typedef struct _examples {
    int id;
    stExample *node;
    UT_hash_handle hh;
}stExamples;

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param users
 * @param iUserid
 * @return 
 */
stExample *  fFindItemById(stExample *users,int iUserid){
      
    stExample *pFind;
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
int fAddItemToHashTable(stExample **users,int iUserId,char *sUsername,stExample **st){
    int ret = 0;

    HASH_FIND_INT(*users,&iUserId,*st);
    if (!*st) {
        *st =  malloc(sizeof(stExample));
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
int fDelItemById(stExample *pUsers,int iUserId){
    
    int ret = 0;
    
    stExample *tmp = fFindItemById(pUsers,iUserId);
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
void fPrintHashTable(stExample *pUsers){
    stExample *stFirst;
    for(stFirst=pUsers; stFirst != NULL; stFirst=(stExample*)(stFirst->hh.next)) {
        printf("key %d, username %s\n", stFirst->id, stFirst->sUsername);
    }
}


//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    
    stExample *pUsers = NULL;
    stExample *stFirst;
    int iUserid = 1,ret;
    char sUsername[] = "Neo";
    
    struct timeval tv;
    gettimeofday(&tv,NULL);
    
    long timestamp = (long)time(NULL)*1000 + tv.tv_usec;

    
    printf("%ld\n",timestamp);
    //stFirst = (stExample*)malloc(sizeof(stExample));
    //int ret = fAddItemToHashTable(pUsers,iUserid,sUsername,stFirst);
    
    printf("Program start:\n");
    
    //////////////////////////////////////////////////////////////////////////////
    // add item
    int i;
    for (i = 1; i < 20; i++) {
        ret = fAddItemToHashTable(&pUsers, i, sUsername, &stFirst);
        if (ret > 0) {
            printf("use %d find:%s\n", stFirst->id, stFirst->sUsername);
        } else if (ret == 0) {
            printf("the key:%d is Not Uniqueness!\n", iUserid);
        } else {
            printf("can't create any more memory!\n");
        }
    }

    


    //////////////////////////////////////////////////////////////////////////////
    // find item
    stExample * tmp = fFindItemById(pUsers,iUserid);
    if(tmp){
        printf("use key %d find %s\n",tmp->id,tmp->sUsername);
    }else{
        printf("use key %d can't find any item!\n",iUserid);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // print all
    fPrintHashTable(pUsers);
    
    //////////////////////////////////////////////////////////////////////////////
    // delete a item
    ret = fDelItemById(pUsers,iUserid);
    if (ret > 0) {
        printf("use key %d delete a item.\n",iUserid);
    } else {
        printf("use key %d can't find any item.\n",iUserid);
    }
    
    fPrintHashTable(pUsers);

    
    
    
//    stExamples *pExamples;
//    stExample *test = malloc(sizeof(stExample));
//    int ids = 1;
//    
//    test->id = 5;
//    strcpy(test->sUsername,"hello");
//    HASH_ADD_INT(pExamples,id,test);
//    
//    HASH_FIND_INT(pExamples,&ids,test);
//    
    return (EXIT_SUCCESS);
}

