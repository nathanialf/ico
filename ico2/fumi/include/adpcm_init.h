/*
 * ico2/fumi/include/adpcm_init.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what adpcm_init.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ADPCM_INIT_H
#define ADPCM_INIT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order adpcm_init.c's inline tail has. */
void adpcmPauseRequest(int val);
/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the six-word open request
   soundDataOpen fills in and soundDataOpenSync reads back. */
typedef struct AdpcmOpenReq {
    int mode;   /* 0x00, soundDataOpen's mode, 2 for ADPCM */
    int id;     /* 0x04, the sound id */
    int ch;     /* 0x08 */
    int iopBuf; /* 0x0C */
    int f10;    /* 0x10 */
    int bg;     /* 0x14, the background loader handle */
} AdpcmOpenReq;

struct AdpcmStreamTag;

typedef struct {
    char _0[0x2C];
    struct AdpcmStreamTag *stream; /* 0x2C */
} AdpcmObj;

typedef struct {
    int ch;  /* 0x00 */
    int f4;  /* 0x04 */
    int f8;  /* 0x08 */
    int fC;  /* 0x0C */
    int f10; /* 0x10 */
    int f14; /* 0x14 */
} AdpcmChReq;

typedef struct AdpcmStreamTag {
    int used;       /* 0x00 */
    int n;          /* 0x04 */
    int ch[2];      /* 0x08 */
    int f10;        /* 0x10 */
    int f14;        /* 0x14 */
    int f18;        /* 0x18 */
    int f1C;        /* 0x1C */
    int f20;        /* 0x20 */
    int f24;        /* 0x24 */
    int f28;        /* 0x28 */
    int f2C;        /* 0x2C */
    long long mask; /* 0x30 */
    int f38;        /* 0x38 */
    short f3C[2];   /* 0x3C */
    short f40[2];   /* 0x40 */
    short f44;      /* 0x44 */
    short f46;      /* 0x46 */
    short f48;      /* 0x48 */
    short f4A;      /* 0x4A */
    int f4C;        /* 0x4C */
    int f50;        /* 0x50 */
    int f54;        /* 0x54 */
} AdpcmStream;

void AdpcmStreamHeap(void);
void AdpcmStreamInit(void);
int AdpcmIopBuffAlloc(void);
int AdpcmNotUseIopAreaFree(void);
int *AdpcmOpenSync(AdpcmOpenReq *self);
void AdpcmFadeCloseAll(short a0);
int AdpcmUseAreaGet(void);
int AdpcmFreeAreaGet(void);
void AdpcmInterStereoVolumeSetAll(void);
short AdpcmInterLeaveVolumeGet(char *self, int idx);
short AdpcmVolumeGet(char *self);
int adpcmTickProc(int self, int obj);
void adpcmDiskNotReady(void);
void adpcmDiskReturnReady(void);
int adpcmOpenProc(int a0, int a1);
void adpcmOpenDiskNotReady(void);

void AdpcmInterStereoVolumeSet();
void AdpcmOpen(AdpcmOpenReq *self, int no, int a2, int a3);
void AdpcmPlay(void *a0);
void AdpcmVolumeSet(int a0, int a1);
int *adpcmDataSet(int a0, int no, int bank, int a3, int size, int a5, int a6);
void adpcmTickProc2(int *a0);

#endif /* ADPCM_INIT_H */
