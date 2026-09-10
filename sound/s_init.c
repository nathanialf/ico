#include "common.h"

typedef struct SqEntry {
    short num;        /* 0x0 */
    short bank;       /* 0x2 */
    short unk4;       /* 0x4 */
    short unk6;       /* 0x6 */
    int unk8;         /* 0x8 */
    int unkC;         /* 0xC */
    int unk10[2];     /* 0x10 */
    long long chMask; /* 0x18 */
    int unk20[2];     /* 0x20 */
    int unk28;        /* 0x28 */
} SqEntry;

typedef struct SeReqRec {
    int unk0[8];      /* 0x00 */
    long long chMask; /* 0x20 */
} SeReqRec;

static inline char *hd_search(char *base, int *pk)
{
    char *p = base;
    char *end = p + 0x300;
    char *r = p;
    do {
        char *snap = r;
        if (*(int *)p == *pk)
            goto found;
        r += 0x30;
        p += 0x30;
        r = snap + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}

extern char D_005521C0[];
extern char D_005521D0[];
extern char D_006BF570[];
extern char D_006BF870[];
extern int D_0063A370;
extern int D_0063A650;
extern long long D_0063C1E0;
extern long long D_0063C1E8;
extern void debug_StdPrintfDummy();
extern void SgInit(void);
extern void SgSetDigitalOutputMode(int a0);
extern void SgSetTickMode(int a0);
extern void SgSetReverbEndAddr(int a0, int a1);
extern void SgSetReverbType(int a0, int a1);
extern void SgSetReverbDepth(int a0, int a1, int a2);
extern void SgSetMasterVol(int a0, int a1, int a2);
extern void AdpcmStreamInit(void);

int soundInit(void)
{
    int i;
    char *p;

    debug_StdPrintfDummy(D_005521C0);
    SgInit();
    if (D_0063A370 == 1) {
        SgSetDigitalOutputMode(0x80);
    } else {
        SgSetDigitalOutputMode(0x880);
    }
    debug_StdPrintfDummy(D_005521D0);
    SgSetTickMode(60);
    SgSetReverbEndAddr(0, 0x1FFFFF);
    SgSetReverbEndAddr(1, 0x1DFFFF);
    SgSetReverbType(0, 4);
    SgSetReverbDepth(0, 0xCCC, 0xCCC);
    SgSetReverbType(1, 4);
    SgSetReverbDepth(0, 0xCCC, 0xCCC);
    SgSetMasterVol(0, 0, 0);
    SgSetMasterVol(1, 0, 0);
    for (i = 15; i >= 0; i--) {
        *(int *)&D_006BF570[i * 48] = 0;
    }
    D_0063C1E0 = 0;
    D_0063C1E8 = 0;
    /* the request slot of every SeSlot, walked through a base pointer: that is
       what keeps the +0x30 out of the symbol's %hi/%lo and in the loop start value */
    p = D_006BF870;
    for (i = 47; i >= 0; i--) {
        *(int *)&p[i * 64 + 0x30] = 0;
    }
    AdpcmStreamInit();
    D_0063A650 = 0;
    return 0;
}

extern int D_0063A654;
extern void SgSetOutputMode();

void soundOutputModeSet(int a0)
{
    D_0063A654 = a0;
    SgSetOutputMode(a0);
}

extern int D_0063A648;
extern void SgSetMasterVol(int a0, int a1, int a2);
extern void SgSetReverbDepth(int a0, int a1, int a2);

void soundReverbDepthSet(int a0)
{
    int val;
    D_0063A648 = a0;
    val = (a0 * 32767) / 100;
    SgSetReverbDepth(0, val, val);
    SgSetReverbDepth(1, val, val);
    SgSetMasterVol(0, 0x3FFF, 0x3FFF);
    SgSetMasterVol(1, 0x3FFF, 0x3FFF);
}

extern char D_005521E8[];
extern char D_005521F8[];
extern char D_00552210[];
extern int D_0063A680;
extern void debug_StdPrintfDummy();
extern int iosSifAllocIopHeapDebug(int a, void *b, int c);

void soundAllocIopHeap(void)
{
    int r = iosSifAllocIopHeapDebug(0x78000, D_005521E8, 0xFE);
    D_0063A680 = r;
    if (r < 0) {
        debug_StdPrintfDummy(D_005521F8);
    } else {
        debug_StdPrintfDummy(D_00552210, r, 0x78000);
    }
}

extern void sceSifFreeIopHeap();

void soundAllocIopFree(void)
{
    sceSifFreeIopHeap(D_0063A680);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenChk);

extern char D_005521E8[];
extern char D_0063A660[];
extern int D_0063A640;
extern int D_0063A644;
extern int D_0063C1D8;
extern int D_0063C1DC;
extern void __assert(char *file, int line, char *msg);
extern void debug_assert(char *file, int line);

/* The SPU-buffer view of a sound data area: at 0x18 the same bytes are the
   adpcm channel mask (long long, see soundBufAdpcmChAlloc) in the SqEntry
   view and an (addr, size) pair here, so this role gets its own record. */
typedef struct SoundBufReq {
    short unk0;          /* 0x00 */
    short unk2;          /* 0x02 */
    unsigned short unk4; /* 0x04 */
    unsigned short unk6; /* 0x06 */
    int unk8;            /* 0x08 */
    int unkC;            /* 0x0C */
    int unk10[2];        /* 0x10 */
    int addr;            /* 0x18 */
    int size;            /* 0x1C */
} SoundBufReq;

void soundBufAlloc(SoundBufReq *self, int size)
{
    switch (self->unk6) {
    case 0:
        self->addr = D_0063A640;
        D_0063A640 = D_0063A640 + size;
        D_0063C1D8 = D_0063A640;
        D_0063C1DC = D_0063A640;
        if (D_0063A640 > 0x1D901F) {
            debug_assert(D_005521E8, 412);
            __assert(D_005521E8, 412, D_0063A660);
        }
        break;
    case 1:
        switch (self->unk4) {
        case 1:
            self->addr = D_0063C1D8;
            D_0063C1D8 = D_0063C1D8 + size;
            if (D_0063C1D8 > D_0063A644) {
                debug_assert(D_005521E8, 420);
                __assert(D_005521E8, 420, D_0063A660);
            }
            break;
        case 0:
            D_0063A644 = D_0063A644 - size;
            self->addr = D_0063A644;
            if (D_0063A644 < D_0063C1D8) {
                debug_assert(D_005521E8, 424);
                __assert(D_005521E8, 424, D_0063A660);
            }
            break;
        default:
            debug_assert(D_005521E8, 428);
            __assert(D_005521E8, 428, D_0063A660);
        }
        break;
    case 2:
        switch (self->unk4) {
        case 0:
            self->addr = D_0063C1DC;
            D_0063C1DC = D_0063C1DC + size;
            break;
        default:
            debug_assert(D_005521E8, 443);
            __assert(D_005521E8, 443, D_0063A660);
        }
        break;
    default:
        debug_assert(D_005521E8, 448);
        __assert(D_005521E8, 448, D_0063A660);
    }
    self->size = size;
}

extern int D_0063A640;
extern int D_0063A644;
extern char D_0063A660[];
extern int D_0063C1D8;
extern int D_0063C1DC;
extern void __assert(char *file, int line, char *msg);
extern void debug_assert(char *file, int line);

void soundBufSegFree(int a0, int a1)
{
    switch (a0) {
    case 1:
        switch (a1) {
        case 1:
            D_0063C1D8 = D_0063A640;
            return;
        case 0:
            D_0063A644 = 0x1D9020;
            return;
        case 2:
            return;
        }
        debug_assert(D_005521E8, 0x1D8);
        __assert(D_005521E8, 0x1D8, D_0063A660);
        return;
    case 2:
        if (a1 == 0) {
            D_0063C1DC = D_0063A640;
            return;
        }
        debug_assert(D_005521E8, 0x1E2);
        __assert(D_005521E8, 0x1E2, D_0063A660);
        return;
    }
    debug_assert(D_005521E8, 0x1E7);
    __assert(D_005521E8, 0x1E7, D_0063A660);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBDDataSet);

extern void AdpcmOpen(int *self, int a1, int a2, int a3);

void soundDataOpen(int *work, int mode, int a2, int a3, int a4)
{
    work[0] = mode;
    switch (mode) {
    case 0:
        debug_assert(D_005521E8, 0x266);
        __assert(D_005521E8, 0x266, D_0063A660);
        break;
    case 1:
        debug_assert(D_005521E8, 0x269);
        __assert(D_005521E8, 0x269, D_0063A660);
        break;
    case 2:
        AdpcmOpen(work, a2, a3, a4);
        break;
    default:
        debug_assert(D_005521E8, 0x26F);
        __assert(D_005521E8, 0x26F, D_0063A660);
    }
}

extern int *AdpcmOpenSync(int *self);

int *soundDataOpenSync(int *work)
{
    switch (work[0]) {
    case 0:
        debug_assert(D_005521E8, 0x277);
        __assert(D_005521E8, 0x277, D_0063A660);
        break;
    case 1:
        debug_assert(D_005521E8, 0x27A);
        __assert(D_005521E8, 0x27A, D_0063A660);
        break;
    case 2:
        return AdpcmOpenSync(work);
    default:
        debug_assert(D_005521E8, 0x280);
        __assert(D_005521E8, 0x280, D_0063A660);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataClose);

extern char D_006BF570[];
extern void soundBufSegFree(int a0, int a1);
extern void soundDataClose(char *p);

void soundDataSegAllClose(int a0, int a1)
{
    char *p = D_006BF570;
    char *end = D_006BF570 + 0x300;
    do {
        if (*(int *)p != 0) {
            if (*(unsigned short *)(p + 6) == a0) {
                if (*(unsigned short *)(p + 4) == a1) {
                    soundDataClose(p);
                }
            }
        }
        p += 0x30;
    } while ((int)p < (int)end);
    if (a1 == 2)
        return;
    soundBufSegFree(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeVolSet);
ASM_LIT4_SLOT(D_00638CA0, 0.1f);
ASM_LIT4_SLOT(D_00638CA4, 0.05f);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", debug_DispSEInfo);
ASM_LIT4_SLOT(D_00638CA8, -0.0027777778f);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", sound3DParamSet);
ASM_LIT4_SLOT(D_00638CAC, 3000.0f);
ASM_LIT4_SLOT(D_00638CB0, 0.1f);
ASM_LIT4_SLOT(D_00638CB4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", _soundSeDefPlay);

extern char D_006BF870[];
extern long long D_0063C1E8;
extern void SgSeStop(int a0);
extern void iosPadActStop(int a0);

typedef struct SeInfo {
    short unk0; /* 0x0 */
    short unk2; /* 0x2 */
    short unk4; /* 0x4 */
    short unk6; /* 0x6 */
} SeInfo;

typedef struct SeSrcDef {
    int unk0[13];         /* 0x00 */
    short unk34;          /* 0x34 */
    unsigned short unk36; /* 0x36 */
    unsigned int b0 : 6;  /* 0x38 bits 0..5 */
    unsigned int b6 : 1;
    unsigned int b7 : 25;
} SeSrcDef;

extern SeInfo D_005F5C70[];

void _soundSeDefStop(int a0, int a1)
{
    int ch = a0 & 0xFF;
    char *self = &D_006BF870[ch * 64];
    short h;
    char **rp;
    SeReqRec *req;
    SeSrcDef *src;

    h = *(short *)(self + 0x10);
    if (h < 0)
        return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)self)
        return;
    rp = (char **)&D_006BF870[ch * 64 + 0x30];
    req = *(SeReqRec **)rp;
    if (req != 0) {
        long long bit = (long long)1 << ch;
        long long m = req->chMask;
        if ((m & bit) != 0) {
            req->chMask = m & ~bit;
            D_0063C1E8 &= ~bit;
            *(unsigned short *)self = *(unsigned short *)self + 1;
            *rp = 0;
        }
    }
    if (a1 == 0) {
        SgSeStop(h);
    } else {
        SgSeStop(h | 0x8000);
    }
    src = *(SeSrcDef **)(self + 0x38);
    if (src->b6 == 1 || (&D_005F5C70[src->unk36])->unk6 == 0) {
        if (*(int *)(self + 0xC) != 0)
            iosPadActStop(*(int *)(self + 0xC));
    }
}

extern void _soundSeDefStop(int a0, int a1);

void soundSeDefStop(int a0)
{
    _soundSeDefStop(a0, 0);
}

void soundSeDefStopNoRelease(int a0)
{
    _soundSeDefStop(a0, 1);
}

extern char D_006BF870[];
extern void SgSetSePitchDirect();

void soundSeDefPitchSet(int a0)
{
    char *entry;
    short id;
    entry = &D_006BF870[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0)
        return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry)
        return;
    SgSetSePitchDirect(id);
}

ASM_LIT4_SLOT(D_00638CB8, 3000.0f);
ASM_LIT4_SLOT(D_00638CBC, 0.1f);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvPlay);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvNotUseClose);
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegNextStageNotUseClose);

extern char D_00552170[];
extern char D_00552188[];
extern char D_005521A0[];
extern void FlushCache(int a);
extern int sceSifDmaStat(int h);
extern int sceSifSetDma(int p, int a);

int Ee2Iop(int a0, int a1, int a2)
{
    int buf[4];
    int x;
    debug_StdPrintfDummy(D_00552170);
    debug_StdPrintfDummy(D_00552188, a0, a1, a2);
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = 0;
    FlushCache(0);
    x = sceSifSetDma((int)buf, 1);
    while (sceSifDmaStat(x) >= 0)
        ;
    debug_StdPrintfDummy(D_005521A0);
    FlushCache(0);
    return (x >= 0) ? 0 : -1;
}

int soundOutputModeGet(void)
{
    return D_0063A654;
}

int soundReverbDepthGet(void)
{
    return D_0063A648;
}

extern long long D_0063C1E0;
extern char D_00552280[];

int soundBufAdpcmChAlloc(SqEntry *self, int *chp)
{
    int ch;
    long long bit = 1;

    for (ch = 0; ch < 64U; ch++) {
        if ((D_0063C1E0 & (bit << ch)) == 0)
            goto found;
    }
    debug_assert(D_005521E8, 500);
    __assert(D_005521E8, 500, D_0063A660);
found:
    self->chMask |= bit << ch;
    D_0063C1E0 |= bit << ch;
    if (ch >= 5) {
        debug_StdPrintfDummy(D_00552280);
        debug_assert(D_005521E8, 504);
        __assert(D_005521E8, 504, D_0063A660);
    }
    *chp = ch;
    if (ch < 0) {
        return (ch << 14) + 0x1D9020;
    } else {
        return (ch << 14) + 0x1E0000;
    }
}

extern long long D_0063C1E0;

void soundBufAdpcmFree(char *self)
{
    long long mask = ~*(long long *)(self + 0x18);
    D_0063C1E0 &= mask;
    *(long long *)(self + 0x18) = 0;
}

char *soundDataAreaSearch(int *a0)
{
    int key = *a0;
    char *p = D_006BF570;
    char *end = p + 0x300;
    char *r = p;
    do {
        char *snap = r;
        if (*(int *)p == key)
            goto found;
        r += 0x30;
        p += 0x30;
        r = snap + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataAreaGet);

extern char D_0063A660[];
extern char D_006A95B0_2[] __asm__("D_006BF570");
extern void __assert(char *file, int line, char *msg);
extern void debug_assert(char *file, int line);
extern int memset(void *dst, int val, int size);
extern void soundDataOpenChk(char *e);

char *soundHDDataSet(int a0, int a1, int a2, int a3, int a4)
{
    int hi = a2 << 0x10;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = (SqEntry *)hd_search(D_006BF570, &key);
    if (e == 0) {
        key = 0;
        e = (SqEntry *)hd_search(D_006A95B0_2, &key);
        if (e == 0) {
            debug_assert(D_005521E8, 0x14E);
            __assert(D_005521E8, 0x14E, D_0063A660);
        }
        memset(e, 0, 0x30);
        e->num = a1;
        e->bank = a2;
        e->unk6 = a4;
        e->unk4 = a3;
        e->unk28 = -1;
    }
    e->unkC = a0;
    soundDataOpenChk((char *)e);
    return (char *)e;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSQDataSet);

extern int _soundSeDefPlay(int a0, int a1, int a2, int a3, float f, int t0, int t1);
extern void sound3DParamSet(int *p);

int soundSeDefPlay(int a0, int a1, int a2, int a3)
{
    int idx = _soundSeDefPlay(a0, a1, a2, a3, -1.0f, 0, 0);
    if (idx >= 0) {
        sound3DParamSet((int *)((char *)D_006BF870 + (idx & 0xFF) * 64));
    }
    return idx;
}

int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3)
{
    int idx = ((int (*)(int, int, int, int, int, int))_soundSeDefPlay)(a0, a1, a2, a3, 0, 0);
    if (idx >= 0) {
        sound3DParamSet((int *)((char *)D_006BF870 + (idx & 0xFF) * 64));
    }
    return idx;
}

float soundSeDefVolumeRateGet(int a0)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006BF870 + off;
    if (*(short *)(e + 0x10) >= 0) {
        goto check;
    }
fail:
    return 0.0f;
check:
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)e) {
        goto fail;
    }
    return *(float *)(D_006BF870 + off + 0x18);
}

void soundSeDefVolumeRateSet(int a0, float f)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006BF870 + off;
    if (*(short *)(e + 0x10) >= 0) {
        a0 = a0 >> 8;
        if (a0 == *(unsigned short *)e) {
            *(float *)(D_006BF870 + off + 0x18) = f;
        }
    }
}

extern void soundSeDefStop(int a0);

void soundSeGroupStop(int arg)
{
    char *p = D_006BF870;
    int i = 0;
    do {
        int *e30 = *(int **)(p + 0x30);
        if (e30 != 0) {
            if (*(int *)(p + 8) == arg) {
                int *e38 = *(int **)(p + 0x38);
                if ((*(unsigned int *)((char *)e38 + 0x38) >> 6) & 1) {
                    if (*(unsigned short *)((char *)e30 + 4) == 0) {
                        soundSeDefStop(((int)*(unsigned short *)p << 8) | i);
                    }
                }
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

extern int D_0063A67C;

int soundSeGroupGet(void)
{
    int next = ((D_0063A67C + 1) & 0x0FFFFFFF) | 0x10000000;
    D_0063A67C = next;
    return next;
}

extern void soundSeDefStopNoRelease(int a0);

void soundSePlayModeStop(int arg)
{
    char *p = D_006BF870;
    int i = 0;
    do {
        int *e30 = *(int **)(p + 0x30);
        if (e30 != 0) {
            if (*(unsigned char *)(p + 6) == arg) {
                if (*(unsigned short *)((char *)e30 + 4) == 0) {
                    soundSeDefStopNoRelease(((int)*(unsigned short *)p << 8) | i);
                }
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

extern int D_0028F4C0[];
extern int D_0063B14C;
extern int SgGetSlotStatus(int a0, int a1);

void soundReqTickProc(void)
{
    char *p = D_006BF870;
    int i = 0;
    do {
        if (*(int *)(p + 0x30) != 0) {
            int r = SgGetSlotStatus(1, *(short *)(p + 0x10));
            if (r == 0) {
                soundSeDefStop(((int)*(unsigned short *)p << 8) | i);
            } else if (r & 2) {
                if (D_0063B14C == 0) {
                    if (D_0028F4C0[5] != 0 && *(unsigned int *)(p + 8) != 0xFFFFFFFF &&
                        *(unsigned int *)(p + 8) != 0xFFFFFFFE) {
                        *(int *)(p + 4) |= 0x20000000;
                    } else {
                        *(int *)(p + 4) &= 0xDFFFFFFF;
                    }
                }
                sound3DParamSet((int *)p);
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

extern void adpcmTickProc2();

void soundVBlank(void)
{
    int i;
    for (i = 0; i < 0x300; i += 0x30) {
        char *p = D_006BF570 + i;
        if (*(unsigned short *)(p + 2) == 0x11) {
            adpcmTickProc2(p);
        }
    }
}

typedef struct SeKind {
    short num;  /* 0x0 */
    short unk2; /* 0x2 */
    short unk4; /* 0x4 */
    short idx;  /* 0x6 */
} SeKind;

extern unsigned short D_0030C4E0[];
extern SeKind D_005EE488[];

void soundSeKindBuild(void)
{
    int i;
    int j;
    unsigned short num;
    char *e;

    for (i = 1419; i >= 0; i--) {
        D_0030C4E0[i] = 0;
    }

    for (i = 0; i < 16; i++) {
        e = &D_006BF570[i * 0x30];
        if (*(unsigned short *)(e + 2) == 11) {
            num = *(unsigned short *)e;
            for (j = 0; j < 3837; j++) {
                SeKind *p = &D_005EE488[j];
                if (p->num == num) {
                    D_0030C4E0[p->idx] = j;
                }
            }
        }
    }
}

extern int D_0063A658;

int soundSeSemiCommonLoadChk(void)
{
    return D_0063A658;
}

typedef struct SeEnvDef {
    float unk0;          /* 0x00 */
    float unk4;          /* 0x04 */
    float volume;        /* 0x08 */
    float unkC;          /* 0x0C */
    float unk10;         /* 0x10 */
    float unk14;         /* 0x14 */
    unsigned int b0 : 1; /* 0x18 bit 0 */
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int b3 : 1;
    unsigned int b4 : 28;
} SeEnvDef;

typedef struct SeSrc {
    int unk0[9]; /* 0x00 */
    float unk24; /* 0x24 */
} SeSrc;

typedef struct SeSlot {
    int unk0;             /* 0x00 */
    unsigned int f0 : 26; /* 0x04 bits 0..25 */
    unsigned int f26 : 1;
    unsigned int f27 : 1;
    unsigned int f28 : 2;
    unsigned int f30 : 1;
    unsigned int f31 : 1;
    int unk8[4];     /* 0x08 */
    float unk18;     /* 0x18 */
    float unk1C;     /* 0x1C */
    float unk20;     /* 0x20 */
    float unk24;     /* 0x24 */
    float unk28;     /* 0x28 */
    int unk2C[3];    /* 0x2C */
    SeSrc *unk38;    /* 0x38 */
    SeEnvDef *unk3C; /* 0x3C */
} SeSlot;

void soundSeEnvDefaultSet(SeSlot *self)
{
    SeEnvDef *env = self->unk3C;

    if (env->volume != 0.0f) {
        self->unk18 = env->volume;
    } else {
        self->unk18 = self->unk38->unk24;
    }
    if (env->unkC != 0.0f) {
        self->unk24 = env->unkC;
    } else {
        self->unk24 = 500.0f;
    }
    if (env->unk10 != 0.0f) {
        self->unk20 = env->unk10;
    } else {
        self->unk20 = 1000.0f;
    }
    if (env->unk14 != 0.0f) {
        self->unk28 = env->unk14;
    } else {
        self->unk28 = 3000.0f;
    }
    self->f30 = env->b3;
    self->f26 = env->b1;
    self->f27 = env->b2;
    self->unk1C = 0.1f;
}

extern const char D_00552398[];
extern char D_005D6DB0[];

int debug_req(void)
{
    char *e = D_006BF870;
    int sz = 0x3C;
    int i = 0x2F;
    do {
        if (*(int *)(e + 0x30) != 0) {
            debug_StdPrintfDummy((int)D_00552398, *(short *)(e + 0x10),
                                 (unsigned int)(*(int *)(e + 0x38) - (int)D_005D6DB0) / sz);
        }
        e += 0x40;
        i--;
    } while (i >= 0);
    __asm__ __volatile__("break");
}
