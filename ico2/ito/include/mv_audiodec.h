/*
 * ico2/ito/include/mv_audiodec.h
 *
 * The declarations of what mv_audiodec.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_AUDIODEC_H
#define MV_AUDIODEC_H

#include <libmpeg.h>
#include "mv_readbuf.h"

/* The audio decoder's record, 0x68 bytes.  The first 40 bytes after the state
 * word are the two stream-file chunk headers the IOP callback copies in
 * verbatim, which is why they are laid out field by field and printed as one
 * block when the last of them arrives. */
typedef struct AudioDec { /* field names derived */
    int state;           /* 0x00, 0 collecting the header, 1 preset, 2 playing, 3 paused */
    char id[4];          /* 0x04, the stream file's chunk tag */
    int headerSize;      /* 0x08 */
    int type;            /* 0x0C, 0 PCM big endian, 1 PCM little endian, 2 ADPCM */
    int sampleRate;      /* 0x10 */
    int channels;        /* 0x14 */
    int interleaveSize;  /* 0x18 */
    int interleaveStart; /* 0x1C, first interleave block */
    int interleaveEnd;   /* 0x20, last interleave block */
    char dataId[4];      /* 0x24, the data chunk's tag */
    int dataSize;        /* 0x28 */
    int headerBytes;     /* 0x2C, how many of the 40 header bytes have arrived */
    int ring;            /* 0x30, the EE side ring buffer */
    int writePos;        /* 0x34 */
    int filled;          /* 0x38 */
    int ringSize;        /* 0x3C */
    int putTotal;        /* 0x40 */
    int iopBuf;          /* 0x44, the IOP heap block the two PCM channels read */
    int iopSize;         /* 0x48 */
    int iopPos;          /* 0x4C */
    int word50;          /* 0x50, cleared with the others, never read */
    int sentTotal;       /* 0x54 */
    char mono;           /* 0x58 */
    char pad59[3];
    int volume;     /* 0x5C */
    char pcmInited; /* 0x60 */
    char ch0Open;   /* 0x61 */
    char ch1Open;   /* 0x62 */
    char pad63[5];
} AudioDec;

int audioDecDelete(AudioDec *self);
void audioDecReset(AudioDec *self);
int audioDecIsPreset(AudioDec *self);
void audioDecStart(AudioDec *self);
int audioDecPause(AudioDec *self);
void audioDecResume(AudioDec *self);
int audioDecCreate(AudioDec *self, int mono, int volume);
int audioDecSendToIOP(AudioDec *self);
int pcmCallback(sceMpeg *mp, void *cbdata, void *anyData);

#endif /* MV_AUDIODEC_H */
