/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on November 11, 2014, 8:51 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

/**
 * 
 */
void fPrintWelcome(){
    printf("//////////////////////////////////////////////////////\n");
    printf("****\tWelcome!\n");
    printf("****\t1.Add a new man.\n");
    printf("****\t2.Find a man.\n");
    printf("****\t3.Modify a man by id.\n");
    printf("****\t4.Delete a man by id.\n");
    printf("****\t5.Delete all man.\n");
    printf("****\t9.Print all members.\n");
    printf("****\t0.Exit\n");
}

void fInitData(){
    sTable = NULL;
}

/*
 * 
 */
int main(int argc, char** argv) {

    int uid;
    stStudent *s;
    char yesOrno;
    char command[3];
    char iIsRunning = 0x01;

    // Init the data
    fInitData();
    
    while (iIsRunning) {

        fPrintWelcome();
  
        fgets(command, sizeof(command), stdin);

        if (command[0] >= '0' && command[0] <= '9') {
            switch (command[0]) {
                // exit.
                case '0':
                {
                    iIsRunning = 0x00;
                    break;
                }
                // add a man
                case '1':
                {
                    printf("Input userid:");
                    scanf("%d",&uid);
                    
                    HASH_FIND_INT(sTable,&uid,s);
                    
                    if (s == NULL) {
                        s = (stStudent *)malloc(sizeof(stStudent));
                        s->id = uid;
                        s->username = malloc(sizeof(char) * 10);
                        
                        printf("Input username:");
                        scanf("%s",s->username);
                        
                        HASH_ADD_INT(sTable,id,s);
                        printf("add uid:%d,username:%s success.\n",s->id,s->username);
                    } else {
                        printf("This id is exist.uid:%d Username is %s.\n",s->id,s->username);
                    } 
                    break;
                }
                // find a man
                case '2':
                {
                    printf("Input userid:");
                    scanf("%d",&uid);
                    
                    HASH_FIND_INT(sTable,&uid,s);
                    
                    if (s == NULL) {
                        printf("This is is not exist.Do you want to add it?\n");
                        
                        // clear the stdin
                        setbuf(stdin, NULL);
                        
                        scanf("%c",&yesOrno);
                        if (yesOrno == 'Y' || yesOrno == 'y') {
                            s = (stStudent *)malloc(sizeof(stStudent));
                            s->id = uid;
                            s->username = malloc(sizeof(char) * 10);

                            printf("Input username:");
                            scanf("%s",s->username);

                            HASH_ADD_INT(sTable,id,s);
                            printf("add uid:%d,username:%s success.\n",s->id,s->username);
                        }
                    } else {
                        printf("This uid:%d Username:%s.\n",s->id,s->username);
                    } 
                    break;
                }
                
                // modify a man.
                case '3':
                {
                    printf("Input modify userid:");
                    scanf("%d",&uid);
                    
                    HASH_FIND_INT(sTable,&uid,s);
                    
                    if (s != NULL) {
                        HASH_DEL(sTable,s);
                        
                        s->id = uid;
                        
                        printf("Input username:");
                        scanf("%s",s->username);
                        
                        HASH_ADD_INT(sTable,id,s);
                        
                        printf("modify uid:%d,username:%s success.\n",s->id,s->username);
                    } else {
                        printf("This id is not exist.\n");
                    } 
                    break;
                }
                
                // delete a man
                case '4':
                {
                    printf("Input delete userid:");
                    scanf("%d",&uid);
                    
                    HASH_FIND_INT(sTable,&uid,s);
                    
                    if (s != NULL) {
                        HASH_DEL(sTable,s);
                        printf("delete uid:%d,username:%s success.\n",s->id,s->username);
                    } else {
                        printf("This id is not exist.\n");
                    } 
                    break;
                }

                // delete all man
                case '5':
                {
                    printf("This is is not exist.Do you want to add it?\n");

                    // clear the stdin
                    setbuf(stdin, NULL);

                    scanf("%c", &yesOrno);
                    if (yesOrno == 'Y' || yesOrno == 'y') {
                        stStudent *tmp;

                        HASH_ITER(hh, sTable, s, tmp) {
                            HASH_DEL(sTable, s);
                            free(s->username);
                            free(s);
                        }
                        printf("delete all success.\n");
                    }
                    break;
                }     
                
                // print all data
                case '9':
                {
                    for(s=sTable; s != NULL; s=(stStudent*)(s->hh.next)){
                        printf("user id:%d,name:%s\n",s->id,s->username);
                    }

                    break;
                }
                
                default:
                {
                    system("clear");
                }
            }
        } else {
            //printf("Please input an enable number.\n");
        }
        
        // clear the stdin.
        setbuf(stdin, NULL);
        command[1] = '\0';
    }
    return (EXIT_SUCCESS);
}