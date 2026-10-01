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

/* one of the 8-byte time-stamp slots the decoder handle carries for each
 * field: _getPtsDtsFlags fills the pair as a 64-bit word and the display
 * record takes its low half back as an int */
typedef union {
    long long d;
    int w[2];
} MpegStamp;

/* the decoder handle sceMpegCreate registers: the picture size and count,
 * the two fields' time stamps and flags, and its internal record */
typedef struct {
    int width, height, frameCount, pad0C;
    MpegStamp pts, dts;       /* 0x10, 0x18 */
    long long flags;          /* 0x20 */
    MpegStamp pts2nd, dts2nd; /* 0x28, 0x30 */
    long long flags2nd;       /* 0x38 */
    struct MpegOut *sys;      /* 0x40 */
} sceMpeg;

int sceMpegAddCallback(void *a0, int a1, int a2, int a3); /* definition in sce/ */
int sceMpegAddStrCallback();                              /* definition in sce/ */
int sceMpegClearRefBuff(void *mp);
int sceMpegCreate(void *self, void *buf, int size);
int sceMpegDelete(sceMpeg *m); /* definition in sce/ */
int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3, int p4);
int sceMpegGetPicture(int *a0, unsigned int a1, int a2); /* definition in sce/ */
void sceMpegInit(void);
int sceMpegIsEnd(int **a0);          /* definition in sce/ */
int sceMpegIsRefBuffEmpty(void *a0); /* definition in sce/ */
void sceMpegReset(int *a0);          /* definition in sce/ */

/* The library's internal symbols are in libmpeg_internal.h. */

#endif /* SCE_LIBMPEG_LIBMPEG_H */
