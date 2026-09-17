/*
 * sce/libgraph/libgraph.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libgraph.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBGRAPH_LIBGRAPH_H
#define SCE_LIBGRAPH_LIBGRAPH_H

void *sceGsGetGParam(void);                                            /* definition in sce/ */
void sceGsGetIMR(void);                                                /* definition in sce/ */
void sceGsPutDispEnv(void *a0);                                        /* definition in sce/ */
int sceGsPutDrawEnv(void *a0);                                         /* definition in sce/ */
int sceGsPutIMR(void *a0);                                             /* definition in sce/ */
void sceGsResetGraph(short mode, short inter, short omode, short ffmd); /* definition in sce/; the ROM sign-extends all four with sll/sra */
void sceGsResetPath(void);                                             /* dominant spelling at 4 sites */
int sceGsSetDefAlphaEnv(long long *a0, int a1);                        /* definition in sce/ */
void sceGsSetDefDispEnv(int *env, int psm, short w, short h, short dx, short dy); /* dominant spelling at 2 sites */
int sceGsSetDefDrawEnv();                                              /* dominant spelling at 2 sites */
int sceGsSetDefTexEnv();                                               /* dominant spelling at 1 sites */
int sceGsSwapDBuff(void *a0, int a1);                                  /* definition in sce/ */
void sceGsSyncPath(int a, int b);                                      /* dominant spelling at 5 sites */
int sceGsSyncV(void);                                                  /* definition in sce/ */
short sceGszbufaddr(short a0, short a1, short a2);                     /* definition in sce/ */

#endif /* SCE_LIBGRAPH_LIBGRAPH_H */
