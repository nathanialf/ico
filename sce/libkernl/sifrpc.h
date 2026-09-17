/*
 * sce/libkernl/sifrpc.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called sifrpc.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_SIFRPC_H
#define SCE_LIBKERNL_SIFRPC_H

int _sceSifLoadElfPart(void *a0, int a1, int a2, int a3);              /* dominant spelling at 1 sites */
void _sceSifLoadModule(void *a0, int a1, int a2, int a3, int a4);      /* dominant spelling at 1 sites */
int _sceSifLoadModuleBuffer(void *a0, int a1, int a2, void *a3);       /* dominant spelling at 1 sites */
int _sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1, int t2); /* dominant spelling at 1 sites */
int sceSifAllocIopHeap(int a0);                                        /* definition in sce/ */
int sceSifBindRpc(void *cd, unsigned int sid, int mode);               /* dominant spelling at 3 sites */
int sceSifCallRpc();                                                   /* dominant spelling at 6 sites */
int sceSifCheckStatRpc(char *a0);                                      /* definition in sce/ */
int sceSifDmaStat(int h);                                              /* dominant spelling at 3 sites */
void sceSifExecRequest(int *item);                                     /* dominant spelling at 1 sites */
void sceSifExitCmd(void);                                              /* definition in sce/ */
int sceSifFreeIopHeap(int a0);                                         /* definition in sce/ */
unsigned int sceSifGetReg(unsigned int a0);                             /* dominant spelling at 1 sites; the argument's
                                                                          unsignedness is ROM-proven, see sceSifResetIop */
int sceSifInitIopHeap(void);                                           /* definition in sce/ */
int sceSifInitRpc(int mode);                                           /* dominant spelling at 2 sites */
int sceSifLoadFileReset(void);                                         /* definition in sce/ */
void sceSifLoadModule(void *a0, int a1, int a2);                       /* definition in sce/ */
int sceSifRebootIop(const char *img);                                  /* dominant spelling at 1 sites */
int sceSifSetDma(int p, int a);                                        /* dominant spelling at 3 sites */
void sceSifSetReg(int a0, int a1);                                     /* dominant spelling at 1 sites */
int sceSifSyncIop(void);                                               /* definition in sce/ */
void sceSifWriteBackDCache(void *addr, int len);                       /* dominant spelling at 2 sites */

#endif /* SCE_LIBKERNL_SIFRPC_H */
