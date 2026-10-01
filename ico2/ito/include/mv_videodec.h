/*
 * ico2/ito/include/mv_videodec.h
 *
 * The declarations of what mv_videodec.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_VIDEODEC_H
#define MV_VIDEODEC_H

#include "mv_vibuf.h"
#include "mv_vobuf.h"
#include "mv_disp.h"
#include "mv_readbuf.h"

/* The video decoder: libmpeg's decoder record, its work area and the
   video-input ring the demuxer fills. */
typedef struct VideoDec { /* field names derived */
    int width;            /* 0x00, libmpeg's decoder record: the picture size */
    int height;           /* 0x04 */
    int frameCount;       /* 0x08, the pictures decoded */
    char pad0C[60];       /* 0x0C, the rest of libmpeg's record */
    int buf;              /* 0x48, the decoder's work area */
    ViBuf vibuf;          /* 0x50 */
    int state;            /* 0xB8: 0 decoding, 1 aborted, 2 flushed, 3 ended */
    char padBC[4];        /* 0xBC */
    int dmacHandler;      /* 0xC0, the image-done DMA handler mv_main installs */
    int intcHandler;      /* 0xC4, the vblank handler mv_main installs */
} VideoDec;

/* libmpeg's error callback data. */
typedef struct MvCbErr { /* field names derived */
    int type;            /* 0x00 */
    char *message;       /* 0x04 */
} MvCbErr;

/* libmpeg's time stamp callback data: the PTS and DTS of the picture about
   to be decoded, filled in by the callback. */
typedef struct MvCbTs { /* field names derived */
    int type;           /* 0x00 */
    char pad4[4];       /* 0x04 */
    long long pts;      /* 0x08 */
    long long dts;      /* 0x10 */
} MvCbTs;

/* The block the decode thread is started with: the decoder, the display it
   draws to and the video-out ring between them. */
typedef struct MvThreadArg { /* field names derived */
    VideoDec *dec;
    MvDispEnv *disp;
    VoBuf *vo;
    /* the block is 64 bytes; only the three above are used */
    char reserved[64 - 12];
} MvThreadArg;

int videoCallback(int mp, MvCbStr *pkt, MvCbArg *arg);
void videoDecAbort(VideoDec *self);
int videoDecCreate(VideoDec *self);
int videoDecDelete(VideoDec *self);
int videoDecFlush(VideoDec *self);
int videoDecGetState(VideoDec *self);
int videoDecIsFlushed(VideoDec *self);
void videoDecMain(void *thArg);
int videoDecSetStream(VideoDec *self, int type, int ch, void *fn, void *data);

#endif /* MV_VIDEODEC_H */
