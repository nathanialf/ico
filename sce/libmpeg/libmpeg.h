/*
 * sce/libmpeg/libmpeg.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libmpeg.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBMPEG_LIBMPEG_H
#define SCE_LIBMPEG_LIBMPEG_H

int sceMpegAddCallback(void *a0, int a1, int a2, int a3); /* definition in sce/ */
int sceMpegAddStrCallback();                              /* definition in sce/ */
int sceMpegClearRefBuff(void *mp);
int sceMpegCreate(void *self, void *buf, int size);
int sceMpegDelete(void); /* definition in sce/ */
int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3, int p4);
int sceMpegGetPicture(int *a0, unsigned int a1, int a2); /* definition in sce/ */
void sceMpegInit(void);
int sceMpegIsEnd(int **a0);          /* definition in sce/ */
int sceMpegIsRefBuffEmpty(void *a0); /* definition in sce/ */
void sceMpegReset(int *a0);          /* definition in sce/ */

/* The library's internal symbols are in libmpeg_internal.h. */

#endif /* SCE_LIBMPEG_LIBMPEG_H */
