/*
 * sce/libcdvd/libcdvd.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libcdvd.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBCDVD_LIBCDVD_H
#define SCE_LIBCDVD_LIBCDVD_H

int _sceCd_cd_ncmd[];                                                  /* dominant spelling at 1 sites */
char _sceCd_cd_scmd[];                                                 /* dominant spelling at 1 sites */
int _sceCd_ncmd_prechk(int a0);                                        /* dominant spelling at 1 sites */
int _sceCd_ncmd_semid[];                                               /* dominant spelling at 1 sites */
int _sceCd_ncmdrdata[];                                                /* dominant spelling at 1 sites */
void _sceFsSigSema(void);                                              /* definition in sce/ */
int sceCdBreak(void);                                                  /* dominant spelling at 1 sites */
int sceCdDiskReady(int mode);                                          /* dominant spelling at 3 sites */
int sceCdGetDiskType(void);                                            /* dominant spelling at 2 sites */
int sceCdGetError(void);                                               /* dominant spelling at 2 sites */
int sceCdInit(int mode);                                               /* dominant spelling at 1 sites */
int sceCdMmode(int media);                                             /* dominant spelling at 1 sites */
int sceCdRead(int lsn, int sectors, void *buf, int *mode);             /* dominant spelling at 2 sites */
int sceCdReadIOPm(int lsn, int sectors, void *buf, int *mode);         /* dominant spelling at 1 sites */
int sceCdStRead(int a0, int a1, int a2, void *a3);                     /* dominant spelling at 1 sites */
int sceCdStStat(void);                                                 /* definition in sce/ */
int sceCdStatus(void);                                                 /* dominant spelling at 3 sites */
int sceCdStream(int a0, int a1, int a2, int a3, void *a4);             /* dominant spelling at 1 sites */
int sceCdSync(int mode);                                               /* dominant spelling at 4 sites */
int sceFsReset(void);                                                  /* definition in sce/ */

#endif /* SCE_LIBCDVD_LIBCDVD_H */
