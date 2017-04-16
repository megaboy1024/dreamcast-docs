/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                        Hello Example

    FILE:       hellop.c

    PURPOSE:    Remote procedures that are linked with the server
                side of RPC distributed application

    FUNCTIONS:  HelloProc() - prints "hello, world" or other string
                sent by client to server

    COMMENTS:   This version of the distributed application that prints
                "hello, world" (or other string) on the server features
                a client that manages its connection to the server.
                It uses the binding handle hello_IfHandle, defined in
                the file hello.h.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "hello.h"    // header file generated by MIDL compiler

void HelloProc(unsigned char * pszString)
{
    printf("%s\n", pszString);
}

void Shutdown(void)
{
    RPC_STATUS status;

    printf("Calling RpcMgmtStopServerListening\n");
    status = RpcMgmtStopServerListening(NULL);
    printf("RpcMgmtStopServerListening returned: 0x%x\n", status);
    if (status) {
       exit(status);
    }

    printf("Calling RpcServerUnregisterIf\n");
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    printf("RpcServerUnregisterIf returned 0x%x\n", status);
    if (status) {
       exit(status);
    }
}

/* end file hellop.c */