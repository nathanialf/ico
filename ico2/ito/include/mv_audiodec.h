/*
 * ico2/ito/include/mv_audiodec.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_audiodec.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MV_AUDIODEC_H
#define MV_AUDIODEC_H


/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the audio decoder's own record,
 * 0x68 bytes, read back from this member's own loads and stores.  The first
 * 40 bytes after the state word are the two stream-file chunk headers the IOP
 * callback copies in verbatim, which is why they are laid out field by field
 * and printed as one block when the last of them arrives. */
typedef struct AudioDec {
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
    int f50;             /* 0x50 */
    int sentTotal;       /* 0x54 */
    char mono;           /* 0x58 */
    char pad59[3];
    int volume;          /* 0x5C */
    char pcmInited;      /* 0x60 */
    char ch0Open;        /* 0x61 */
    char ch1Open;        /* 0x62 */
    char pad63[5];
} AudioDec;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order mv_audiodec.c's inline tail has. */
int audioDecDelete(AudioDec *self);
void audioDecReset(AudioDec *self);
int audioDecIsPreset(AudioDec *self);
void audioDecStart(AudioDec *self);
int audioDecPause(AudioDec *self);
void audioDecResume(AudioDec *self);

int audioDecCreate(AudioDec *self, int a1, int a2);
int audioDecSendToIOP(AudioDec *self);
int pcmCallback(int a0, int *pkt, int *ctx);

#endif /* MV_AUDIODEC_H */
