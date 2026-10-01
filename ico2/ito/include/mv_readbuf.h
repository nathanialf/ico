/*
 * ico2/ito/include/mv_readbuf.h
 *
 * The declarations of what mv_readbuf.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_READBUF_H
#define MV_READBUF_H

/* The ring the stream file is read into and the demuxer drains. */
typedef struct ReadBuf { /* field names derived */
    unsigned char *data; /* 0x00 */
    int size;            /* 0x04 */
    int put;             /* 0x08, where the next read lands */
    int count;           /* 0x0C, the bytes read and not yet demuxed */
} ReadBuf; /* derived name */

/* What a demux callback is handed with each packet: the read ring the
   packet sits in and the decoder it feeds. */
typedef struct MvCbArg { /* field names derived */
    ReadBuf *rb;
    void *dec;
} MvCbArg; /* derived name */

/* libmpeg's stream callback data: one demuxed packet's payload in the read
   ring and its time stamps. */
typedef struct MvCbStr { /* field names derived */
    int type;            /* 0x00 */
    char pad4[4];        /* 0x04 */
    unsigned char *data; /* 0x08 */
    unsigned int len;    /* 0x0C */
    long long pts;       /* 0x10 */
    long long dts;       /* 0x18 */
} MvCbStr; /* derived name */

int readBufBeginGet(ReadBuf *self, void **p);
int readBufBeginPut(ReadBuf *self, void **p);
int readBufCreate(ReadBuf *self);
void readBufDelete(ReadBuf *self);
int readBufEndGet(ReadBuf *self, int n);
void readBufEndPut(ReadBuf *self, int n);

#endif /* MV_READBUF_H */
