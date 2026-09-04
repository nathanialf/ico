#include "common.h"

static inline char *hd_search(char *base, int *pk) {
    char *p = base;
    char *end = p + 0x300;
    char *r = p;
    do {
        char *snap = r;
        if (*(int *)p == *pk) goto found;
        r += 0x30;
        p += 0x30;
        r = snap + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}

typedef struct SqEntry {
    short num;      /* 0x0 */
    short bank;     /* 0x2 */
    short unk4;     /* 0x4 */
    short unk6;     /* 0x6 */
    int unk8;       /* 0x8 */
    int unkC;       /* 0xC */
    int unk10[6];   /* 0x10 */
    int unk28;      /* 0x28 */
} SqEntry;









extern int D_00632218;
extern void adpcmTickProc2();
extern char D_006A95B0[];
extern int D_0063223C;
extern long long D_00633CD8;
extern char D_006A98B0[];
extern void SgSetSePitchDirect();
extern void sceSifFreeIopHeap();
extern int D_00632240;
extern void SgSetReverbDepth(int a0, int a1, int a2);
extern void SgSetMasterVol(int a0, int a1, int a2);
extern int D_00632208;
extern void SgSetOutputMode();
extern int  D_00632214;
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundInit);

void soundOutputModeSet(int a0)
{
    D_00632214 = a0;
    SgSetOutputMode(a0);
}

void soundReverbDepthSet(int a0)
{
    int val;
    D_00632208 = a0;
    val = (a0 * 32767) / 100;
    SgSetReverbDepth(0, val, val);
    SgSetReverbDepth(1, val, val);
    SgSetMasterVol(0, 0x3FFF, 0x3FFF);
    SgSetMasterVol(1, 0x3FFF, 0x3FFF);
}

extern char D_00557CC8[];
extern char D_00557CD8[];
extern char D_00557CF0[];
extern void debug_StdPrintfDummy();
extern int new_mblock_node(int a, void *b, int c);

void soundAllocIopHeap(void) {
    int r = new_mblock_node(0x78000, D_00557CC8, 0xFE);
    D_00632240 = r;
    if (r < 0) {
        debug_StdPrintfDummy(D_00557CD8);
    } else {
        debug_StdPrintfDummy(D_00557CF0, r, 0x78000);
    }
}

void soundBufAlloc(void)
{
    sceSifFreeIopHeap(D_00632240);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenChk);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBDDataSet);

extern int D_00632200;
extern int D_00632204;
extern char D_00632220[];
extern int D_00633CD0;
extern int D_00633CD4;
extern void func_001AD768(char *file, int line);
extern void __assert(char *file, int line, char *msg);

void soundDataOpen(int a0, int a1) {
    switch (a0) {
        case 1:
            switch (a1) {
                case 1:
                    D_00633CD0 = D_00632200;
                    return;
                case 0:
                    D_00632204 = 0x1D9020;
                    return;
                case 2:
                    return;
            }
            func_001AD768(D_00557CC8, 0x1D8);
            __assert(D_00557CC8, 0x1D8, D_00632220);
            return;
        case 2:
            if (a1 == 0) {
                D_00633CD4 = D_00632200;
                return;
            }
            func_001AD768(D_00557CC8, 0x1E2);
            __assert(D_00557CC8, 0x1E2, D_00632220);
            return;
    }
    func_001AD768(D_00557CC8, 0x1E7);
    __assert(D_00557CC8, 0x1E7, D_00632220);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenSync);

extern void AdpcmInterLeaveVolumeSet(int *a0, int a1, int a2, int a3);
extern char D_00632220[];
extern void func_001AD768(char *file, int line);
extern void __assert(char *file, int line, char *msg);

void soundDataClose(int *a0, int a1, int a2, int a3, int a4) {
    *a0 = a1;
    switch (a1) {
    case 0:
        func_001AD768(D_00557CC8, 0x261);
        __assert(D_00557CC8, 0x261, D_00632220);
        return;
    case 1:
        func_001AD768(D_00557CC8, 0x264);
        __assert(D_00557CC8, 0x264, D_00632220);
        return;
    case 2:
        AdpcmInterLeaveVolumeSet(a0, a2, a3, a4);
        return;
    default:
        func_001AD768(D_00557CC8, 0x26A);
        __assert(D_00557CC8, 0x26A, D_00632220);
        return;
    }
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegAllClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeVolSet);

extern void soundDataOpen(int a0, int a1);
extern void soundSeVolSet(char *p);

void debug_DispSEInfo(int a0, int a1)
{
    char *p = D_006A95B0;
    char *end = D_006A95B0 + 0x300;
    do {
        if (*(int *)p != 0) {
            if (*(unsigned short *)(p + 6) == a0) {
                if (*(unsigned short *)(p + 4) == a1) {
                    soundSeVolSet(p);
                }
            }
        }
        p += 0x30;
    } while ((int)p < (int)end);
    if (a1 == 2) return;
    soundDataOpen(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", sound3DParamSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", _soundSeDefPlay);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", _soundSeDefStop);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefStop);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefStopNoRelease);

extern void soundSeDefStopNoRelease(int a0, int a1);

void soundSeDefPitchSet(int a0) {
    soundSeDefStopNoRelease(a0, 0);
}

void soundReqTickProc(int a0) {
    soundSeDefStopNoRelease(a0, 1);
}

void soundSeEnvPlay(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    SgSetSePitchDirect(id);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegNextStageNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", Ee2Iop);

extern char D_00557C50[];
extern char D_00557C68[];
extern char D_00557C80[];
extern extern void debug_StdPrintfDummy();
extern void FlushCache(int a);
extern int sceSifDmaStat(int h);
extern int sceSifSetDma(int p, int a);

int soundOutputModeGet(int a0, int a1, int a2)
{
    int buf[4];
    int x;
    debug_StdPrintfDummy(D_00557C50);
    debug_StdPrintfDummy(D_00557C68, a0, a1, a2);
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = 0;
    FlushCache(0);
    x = sceSifSetDma((int)buf, 1);
    while (sceSifDmaStat(x) >= 0) ;
    debug_StdPrintfDummy(D_00557C80);
    FlushCache(0);
    return (x >= 0) ? 0 : -1;
}

int soundReverbDepthGet(void) {
    return D_00632214;
}

int soundBufAdpcmChAlloc(void) {
    return D_00632208;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBufAdpcmFree);

void soundDataAreaSearch(char *self) {
    long long mask = ~*(long long *)(self + 0x18);
    D_00633CD8 &= mask;
    *(long long *)(self + 0x18) = 0;
}

char *soundDataAreaGet(int *a0) {
    int key = *a0;
    char *p = D_006A95B0;
    char *end = p + 0x300;
    char *r = p;
    do {
        char *snap = r;
        if (*(int *)p == key) goto found;
        r += 0x30;
        p += 0x30;
        r = snap + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundHDDataSet);

/* A second declaration of the sound-header table root.  gcse hashes a
 * SYMBOL_REF by the address of its name string, so the two declarations put
 * the two `hd_search` table arguments in different expression buckets and
 * each call materialises its own lui/addiu pair, as the ROM does.  Folding
 * them into one declaration costs 21 diffs in soundSQDataSet alone. */
extern char D_006A95B0_2[] __asm__("D_006A95B0");
extern int memset(void *dst, int val, int size);
extern void soundDataOpenChk(char *e);

char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4) {
    int hi = a2 << 0x10;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = (SqEntry *)hd_search(D_006A95B0, &key);
    if (e == 0) {
        key = 0;
        e = (SqEntry *)hd_search(D_006A95B0_2, &key);
        if (e == 0) {
            func_001AD768(D_00557CC8, 0x14E);
            __assert(D_00557CC8, 0x14E, D_00632220);
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

char *soundSeDefPlay(int a0, int a1, int a2, int a3, int a4) {
    int hi = a2 << 0x10;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = (SqEntry *)hd_search(D_006A95B0, &key);
    if (e == 0) {
        key = 0;
        e = (SqEntry *)hd_search(D_006A95B0_2, &key);
        if (e == 0) {
            func_001AD768(D_00557CC8, 0x14E);
            __assert(D_00557CC8, 0x14E, D_00632220);
        }
        memset(e, 0, 0x30);
        e->num = a1;
        e->bank = a2;
        e->unk6 = a4;
        e->unk4 = a3;
        e->unk28 = -1;
    }
    e->unk10[0] = a0;
    soundDataOpenChk((char *)e);
    return (char *)e;
}

extern void _soundSeDefStop(int *p);
extern int soundSeDefStop(int a0, int a1, int a2, int a3, float f, int t0, int t1);

int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3)
{
    int idx = soundSeDefStop(a0, a1, a2, a3, -1.0f, 0, 0);
    if (idx >= 0) {
        _soundSeDefStop((int *)((char *)D_006A98B0 + (idx & 0xFF) * 64));
    }
    return idx;
}

int soundSeDefVolumeRateGet(int a0, int a1, int a2, int a3)
{
    int idx = ((int (*)(int, int, int, int, int, int))soundSeDefStop)(a0, a1, a2, a3, 0, 0);
    if (idx >= 0) {
        _soundSeDefStop((int *)((char *)D_006A98B0 + (idx & 0xFF) * 64));
    }
    return idx;
}

float soundSeDefVolumeRateSet(int a0)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A98B0 + off;
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
    return *(float *)(D_006A98B0 + off + 0x18);
}

void soundSeGroupStop(int a0, float f)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A98B0 + off;
    if (*(short *)(e + 0x10) >= 0) {
        a0 = a0 >> 8;
        if (a0 == *(unsigned short *)e) {
            *(float *)(D_006A98B0 + off + 0x18) = f;
        }
    }
}

extern void soundSeDefPitchSet(int a0);

void soundSeGroupGet(int arg)
{
    char *p = D_006A98B0;
    int i = 0;
    do {
        int *e30 = *(int **)(p + 0x30);
        if (e30 != 0) {
            if (*(int *)(p + 8) == arg) {
                int *e38 = *(int **)(p + 0x38);
                if ((*(unsigned int *)((char *)e38 + 0x38) >> 6) & 1) {
                    if (*(unsigned short *)((char *)e30 + 4) == 0) {
                        soundSeDefPitchSet(((int)*(unsigned short *)p << 8) | i);
                    }
                }
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

int soundSePlayModeStop(void)
{
    int next = ((D_0063223C + 1) & 0x0FFFFFFF) | 0x10000000;
    D_0063223C = next;
    return next;
}

extern void soundReqTickProc(int a0);

void soundVBlank(int arg)
{
    char *p = D_006A98B0;
    int i = 0;
    do {
        int *e30 = *(int **)(p + 0x30);
        if (e30 != 0) {
            if (*(unsigned char *)(p + 6) == arg) {
                if (*(unsigned short *)((char *)e30 + 4) == 0) {
                    soundReqTickProc(((int)*(unsigned short *)p << 8) | i);
                }
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

extern int D_00274EC0[];
extern int D_00632CCC;
extern int SgGetSlotStatus(int a0, int a1);

void soundSeKindBuild(void)
{
    char *p = D_006A98B0;
    int i = 0;
    do {
        if (*(int *)(p + 0x30) != 0) {
            int r = SgGetSlotStatus(1, *(short *)(p + 0x10));
            if (r == 0) {
                soundSeDefPitchSet(((int)*(unsigned short *)p << 8) | i);
            } else if (r & 2) {
                if (D_00632CCC == 0) {
                    if (D_00274EC0[5] != 0 &&
                        *(unsigned int *)(p + 8) != 0xFFFFFFFF &&
                        *(unsigned int *)(p + 8) != 0xFFFFFFFE) {
                        *(int *)(p + 4) |= 0x20000000;
                    } else {
                        *(int *)(p + 4) &= 0xDFFFFFFF;
                    }
                }
                _soundSeDefStop((int *)p);
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

void soundSeSemiCommonLoadChk(void)
{
    int i;
    for (i = 0; i < 0x300; i += 0x30) {
        char *p = D_006A95B0 + i;
        if (*(unsigned short *)(p + 2) == 0x11) {
            adpcmTickProc2(p);
        }
    }
}

extern char D_002E7710[];
extern char D_005EB810[];

void soundSeEnvDefaultSet(int idx)
{
    char *base = (char *)D_002E7710;
    short *q = (short *)(base + 0xAD8);
    int i;
    for (i = 0x56C; i >= 0; i--) {
        *q = 0;
        q--;
    }
    for (i = 0; i < 0x10; i++) {
        char *entry = (char *)D_006A95B0 + i * 0x30;
        if (*(unsigned short *)(entry + 2) == 0xB) {
            unsigned short target = *(unsigned short *)entry;
            int j;
            for (j = 0; j < 0xEDE; j++) {
                short *e2 = (short *)((char *)D_005EB810 + j * 8);
                if (e2[0] == target) {
                    *(short *)(D_002E7710 + e2[3] * 2) = j;
                }
            }
        }
    }
}

int debug_req(void) {
    return D_00632218;
}

