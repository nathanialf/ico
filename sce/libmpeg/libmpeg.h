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

/* the decoder handle sceMpegCreate registers: the picture size and count,
 * the two fields' time stamps and flags, and its internal record */
typedef struct {
    int width, height, frameCount, pad0C;
    long long pts, dts;       /* 0x10, 0x18 */
    long long flags;          /* 0x20 */
    long long pts2nd, dts2nd; /* 0x28, 0x30 */
    long long flags2nd;       /* 0x38 */
    struct MpegSys *sys;      /* 0x40 */
} sceMpeg;

/* a callback sceMpegAddCallback registers: called with the handle, the
 * callback's data record (its first word the type) and the registered data */
typedef int (*sceMpegCallback)(sceMpeg *mp, void *cbdata, void *anyData);
sceMpegCallback sceMpegAddCallback(sceMpeg *mp, int type, sceMpegCallback func, void *data);
int sceMpegAddStrCallback(sceMpeg *mp, int type, int ch, sceMpegCallback func, void *data);
int sceMpegClearRefBuff(sceMpeg *mp);
int sceMpegCreate(sceMpeg *mp, void *buf, int size);
int sceMpegDelete(sceMpeg *m); /* definition in sce/ */
int sceMpegDemuxPssRing(sceMpeg *mp, void *buf, int size, int ring, int ringSize);
int sceMpegGetPicture(sceMpeg *mp, unsigned int buf, int size); /* definition in sce/ */
void sceMpegInit(void);
int sceMpegIsEnd(sceMpeg *mp);          /* definition in sce/ */
int sceMpegIsRefBuffEmpty(sceMpeg *mp); /* definition in sce/ */
void sceMpegReset(sceMpeg *mp);         /* definition in sce/ */

/* The library's internal symbols are in libmpeg_internal.h. */

#endif /* SCE_LIBMPEG_LIBMPEG_H */
