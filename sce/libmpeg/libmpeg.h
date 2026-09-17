/*
 * sce/libmpeg/libmpeg.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libmpeg.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBMPEG_LIBMPEG_H
#define SCE_LIBMPEG_LIBMPEG_H

int sceMpegAddCallback(void *a0, int a1, int a2, int a3); /* definition in sce/ */
int sceMpegAddStrCallback();                              /* definition in sce/ */
int sceMpegCreate(void *self, void *buf, int size);       /* dominant spelling at 1 sites */
int sceMpegDelete(void);                                  /* definition in sce/ */

int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3,
                        int p4);                         /* dominant spelling at 2 sites */

int sceMpegGetPicture(int *a0, unsigned int a1, int a2); /* definition in sce/ */
void sceMpegInit(void);                                  /* dominant spelling at 1 sites */
int sceMpegIsEnd(int **a0);                              /* definition in sce/ */
int sceMpegIsRefBuffEmpty(void *a0);                     /* definition in sce/ */
void sceMpegReset(int *a0);                              /* definition in sce/ */

#endif /* SCE_LIBMPEG_LIBMPEG_H */
