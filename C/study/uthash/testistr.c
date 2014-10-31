/* 
 * File:   main.c
 * Author: topseten
 *
 * Created on October 25, 2014, 7:01 PM
 */
//////////////////////////////////////////////////////////////////////////////
// header file.
#include "testistr.h"
#include "hashtable.h"

//////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param argc
 * @param argv
 * @return 
 */
int testistr() {

    stExampleIStr *pUsers = NULL;
    stExampleIStr *stFirst;
    int iUserid = 0, ret;
    char sUsername[15] = "Neo";
    int iRunning = 1;
    char in[10];
    
    int i;
    
    //////////////////////////////////////////////////////////////////////////////
    // get timestamp
    //    struct timeval tv;
    //    gettimeofday(&tv,NULL);
    //    long timestamp = (long)time(NULL)*1000 + tv.tv_usec; 
    //    printf("%ld\n",timestamp);
    //////////////////////////////////////////////////////////////////////////////
    // start
    printf("Program start:\n");
    while (iRunning) {
        printf(" 1. add user\n");
        printf(" 2. add/rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. .\n");
        printf("11. test key:str\n");
        printf("99. quit\n");
        //gets(in);
        fgets(in, sizeof(in), stdin);
        switch (atoi(in)) {

            case 1:
            {
               //////////////////////////////////////////////////////////////////////////////
                // add item
                int i;
                for (i = 20; i > 0; i--) {
                    sprintf(sUsername, "Neo_%d", i);
                    ret = fIStrAddItemToHashTable(&pUsers, i, sUsername, &stFirst);
                    if (ret > 0) {
                        printf("use %d find:%s\n", stFirst->id, stFirst->sUsername);
                    } else if (ret == 0) {
                        printf("the key:%d is Not Uniqueness!\n", iUserid);
                    } else {
                        printf("can't create any more memory!\n");
                    }
                }
                break;
            }

            case 2:
            {
                sprintf(sUsername, "Neo_%d", 1);
                ret = fIStrAddItemToHashTable(&pUsers,1, sUsername, &stFirst);
                if (ret > 0) {
                    printf("use %d find:%s\n", stFirst->id, stFirst->sUsername);
                } else if (ret == 0) {
                    printf("the key:%d is Not Uniqueness!\n", iUserid);
                } else {
                    printf("can't create any more memory!\n");
                }
                break;
            }

            case 3:
            {
                //////////////////////////////////////////////////////////////////////////////
                // find item
                stExampleIStr * tmp = NULL;
                tmp = fIStrFindItemById(pUsers, iUserid);
                if (tmp) {
                    printf("use key %d find %s\n", tmp->id, tmp->sUsername);
                } else {
                    printf("use key %d can't find any item!\n", iUserid);
                }
                break;
            }

            case 4:
            {
                //////////////////////////////////////////////////////////////////////////////
                // delete a item
                printf("Delete a item\n");
                i = fIStrDelItemById(pUsers, iUserid);
                if (i) {
                    printf("use key %d delete a item.\n", iUserid);
                } else {
                    printf("use key %d can't find any item.\n", iUserid);
                }
                break;
            }

            case 5:
            {
                //////////////////////////////////////////////////////////////////////////////
                // delete all
                printf("Delete all\n");
                fIStrDelAllItem(pUsers);
                pUsers = NULL;
                fIStrPrintHashTable(pUsers);
                break;
            }

            case 6:
            {
                HASH_SORT(pUsers, IStrName_sort);
                fIStrPrintHashTable(pUsers);
                break;
            }

            case 7:
            {
                //////////////////////////////////////////////////////////////////////////////
                // sort the item
                HASH_SORT(pUsers, IStrId_sort);
                fIStrPrintHashTable(pUsers);
                break;
            }

            case 8:
            {
                //////////////////////////////////////////////////////////////////////////////
                //fgets(temp, sizeof(temp), stdin); print all
                fIStrPrintHashTable(pUsers);
                break;
            }


            case 9:
            {
                //////////////////////////////////////////////////////////////////////////////
                // count the item
                printf("pUsers has %u items.\n", HASH_COUNT(pUsers));
                break;
            }
            
            case 10:
            {

                break;
            }
            
            case 11:
            {
                //////////////////////////////////////////////////////////////////////////////
                const char **n, *names[] = {"joe", "bob", "betty", NULL};
                stExampleStrI *s, *tmp, *users = NULL;
                int i = 0;

                for (n = names; *n != NULL; n++) {
                    s = (stExampleStrI*) malloc(sizeof (stExampleStrI));
                    s->sUsername = *n;
                    s->id = i++;
                    HASH_ADD_KEYPTR(hh, users, s->sUsername, strlen(s->sUsername), s);
                }

                HASH_FIND_STR(users, "betty", s);
                if (s) printf("betty's id is %d\n", s->id);

                /* free the hash table contents */
                HASH_ITER(hh, users, s, tmp) {
                    HASH_DEL(users, s);
                    free(s);
                }
                //////////////////////////////////////////////////////////////////////////////
                break;
            }

            case 99:
            {
                iRunning = 0;
                fIStrDelAllItem(pUsers);
                break;
            }
            
            default:
            {
                fIStrPrintHashTable(pUsers);
            }

        }

    }

    fIStrDelAllItem(pUsers);
    pUsers = NULL;
    return (EXIT_SUCCESS);
}

