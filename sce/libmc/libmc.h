/*
 * sce/libmc/libmc.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libmc.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBMC_LIBMC_H
#define SCE_LIBMC_LIBMC_H

int sceMcChdir(int a0, int a1, char *name, char *pwd);                 /* definition in sce/ */
int sceMcClose(int arg);                                               /* definition in sce/ */
int sceMcDelete(int a0, int a1, char *name);                           /* definition in sce/ */
int sceMcFlush(int arg);                                               /* definition in sce/ */
int sceMcFormat(int a0, int a1);                                       /* definition in sce/ */
int sceMcGetDir(int a0, int a1, char *name, int a3, int nblk, void *buf); /* definition in sce/ */
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format); /* dominant spelling at 1 sites */
void sceMcInit(void);                                                  /* dominant spelling at 1 sites */
int sceMcMkdir(int a0, int a1, char *name);                            /* definition in sce/ */
int sceMcOpen(int a0, int a1, char *name, int flags);                  /* definition in sce/ */
int sceMcRead(int a0, void *buf, int len);                             /* definition in sce/ */
int sceMcSeek(int a0, int a1, int a2);                                 /* definition in sce/ */
int sceMcSync(int a0, int *a1, int *a2);                               /* definition in sce/ */
int sceMcUnformat(int a0, int a1);                                     /* definition in sce/ */
int sceMcWrite(int fd, void *buf, int len);                            /* dominant spelling at 1 sites */

#endif /* SCE_LIBMC_LIBMC_H */
