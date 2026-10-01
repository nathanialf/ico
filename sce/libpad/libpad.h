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

int scePadEnterPressMode(int a0, int a1);                  /* definition in sce/ */
int scePadGetButtonMask(int a0, int a1);                   /* definition in sce/ */
int scePadGetModVersion(void);                             /* definition in sce/ */
int scePadGetReqState(int a0, int a1);                     /* definition in sce/ */
int scePadGetState(int a0, int a1);                        /* definition in sce/ */
int scePadInfoAct(int a0, int a1, int a2, int a3);         /* definition in sce/ */
int scePadInfoMode(int a0, int a1, int a2, int a3);        /* definition in sce/ */
int scePadInfoPressMode(int a0, int a1);                   /* definition in sce/ */
int scePadInit(int a0);                                    /* definition in sce/ */
int scePadInit2(int a0);                                   /* definition in sce/ */
int scePadPortOpen(int a0, int a1, void *a2);              /* definition in sce/ */
int scePadRead(int a0, int a1, int a2);                    /* definition in sce/ */
int scePadSetActDirect(int a0, int a1, unsigned char *a2); /* definition in sce/ */
int scePadSetMainMode(int a0, int a1, int a2, int a3);     /* definition in sce/ */

#endif /* SCE_LIBPAD_LIBPAD_H */
