/* 
 * File:   system.h
 * Author: topseten
 *
 * Created on December 28, 2014, 11:41 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include "base.h"
#include "main.h"
            
    int InitSystem();
    void InitSystemPrint();
    void InitConfigSystem();
    void InitSystemVar();
    void  InitSystemThread(int threadnumber,int queuenumber);
    void  InitSystemNetwork();
    void InitLogSystem();
    extern pthread_t CreateThread(void *ThreadFunction);
    
    void DestorySystem();
    void SetupSignal();

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

