/*
 * sce/libpad/libpad.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libpad.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBPAD_LIBPAD_H
#define SCE_LIBPAD_LIBPAD_H

int scePadEnterPressMode(int port, int slot);                    /* definition in sce/ */
int scePadGetButtonMask(int port, int slot);                     /* definition in sce/ */
int scePadGetModVersion(void);                                   /* definition in sce/ */
int scePadGetReqState(int port, int slot);                       /* definition in sce/ */
int scePadGetState(int port, int slot);                          /* definition in sce/ */
int scePadInfoAct(int port, int slot, int act, int term);        /* definition in sce/ */
int scePadInfoMode(int port, int slot, int term, int index);     /* definition in sce/ */
int scePadInfoPressMode(int port, int slot);                     /* definition in sce/ */
int scePadInit(int a0);                                          /* definition in sce/ */
int scePadInit2(int a0);                                         /* definition in sce/ */
int scePadPortOpen(int port, int slot, void *addr);              /* definition in sce/ */
int scePadRead(int port, int slot, int data);                    /* definition in sce/ */
int scePadSetActAlign(int port, int slot, char *act);            /* definition in sce/ */
int scePadSetActDirect(int port, int slot, unsigned char *act);  /* definition in sce/ */
int scePadSetMainMode(int port, int slot, int mode, int option); /* definition in sce/ */

#endif /* SCE_LIBPAD_LIBPAD_H */
