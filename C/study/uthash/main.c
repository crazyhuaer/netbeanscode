/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on October 24, 2014, 11:30 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "uthash.h"

typedef struct example_user_t {
    int id;
    int cookie;
    UT_hash_handle hh;
} example_user_t;

int main(int argc,char *argv[]) {
    int i;
    example_user_t *user, *users=NULL;
    
    /* create elements */
    for(i=0;i<10;i++) {
        if ( (user = (example_user_t*)malloc(sizeof(example_user_t))) == NULL) exit(-1);
        user->id = i;
        user->cookie = i*i;
        HASH_ADD_INT(users,id,user);
    }

    for(user=users; user != NULL; user=(example_user_t*)(user->hh.next)) {
        printf("user %d, cookie %d\n", user->id, user->cookie);
    }
    return 0;
}