#include "common.h"

extern int *D_0027DDF0[];

int soundInit(int a0, int val5, int val6)
{
    int *node = D_0027DDF0[a0];
    int ret = 0;
    if (node != 0) {
        do {
            int full;
            int *p = (int *)((char *)node + 0x54);
            int count = p[1];

            if (count == 0x20) {
                full = -1;
            } else {
                register int idx = count * 8;
                char *addr = (char *)node + idx;
                full = 0;
                *(int *)(addr + 0x5C) = val5;
                {
                    int c2 = p[1];
                    register int idx2;
                    char *addr2;
                    p[1] = c2 + 1;
                    idx2 = c2 * 8;
                    addr2 = (char *)node + idx2;
                    *(int *)(addr2 + 0x60) = val6;
                }
            }
            node = (int *)node[0x10 / 4];
            if (full != 0) ret = -1;
        } while (node != 0);
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundOutputModeSet);

extern int AdpcmPlay();
extern void func_00258948(void);
extern void func_002589F8(int a0);
extern void func_00259040(int a0, int a1);
extern void func_00259058(int a0, int a1);
extern void func_002590E0(int a0);
extern char D_00551FA0[];
extern char D_00551FB0[];
extern int D_0062A260;
extern int D_0062A4F8;
extern unsigned long long D_0062BFC8;
extern unsigned long long D_0062BFD0;
extern char D_006A3070[];
extern char D_006A3370[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundReverbDepthSet);


extern int D_0062A4FC;
extern void func_002590B8(int a0);

void soundAllocIopHeap(int a0) {
    D_0062A4FC = a0;
    func_002590B8(a0);
}

extern int D_0062A4F0;
extern int func_00259070(int a, int b, int c);
extern int func_00259208(int a, int b, int c);

void soundAllocIopFree(int a0)
{
    int val;
    D_0062A4F0 = a0;
    val = (a0 * 32767) / 100;
    func_00259070(0, val, val);
    func_00259070(1, val, val);
    func_00259208(0, 0x3FFF, 0x3FFF);
    func_00259208(1, 0x3FFF, 0x3FFF);
}

extern int new_mblock_node(int a, void *b, int c);
extern void debug_assertMessage();
extern int D_0062A528;
extern char D_00551FC8[];
extern char D_00551FD8[];
extern char D_00551FF0[];
void soundDataOpenChk(void) {
    int r = new_mblock_node(0x78000, D_00551FC8, 0xE6);
    D_0062A528 = r;
    if (r < 0) {
        debug_assertMessage(D_00551FD8);
    } else {
        debug_assertMessage(D_00551FF0, r, 0x78000);
    }
}

extern void func_00246700(int a0);
extern int D_0062A528;

void soundBufAlloc(void) {
    func_00246700(D_0062A528);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBufSegFree);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBDDataSet);

/* soundDataOpen */
extern char D_00551FC8[];
extern char D_0062C388[];
extern int D_0062A4E8;
extern int D_0062A4EC;
extern int D_0062BFC0;
extern int D_0062BFC4;
extern void func_001AAD00(char *file, int line);
extern void func_00260380(char *file, int line, char *msg);

void soundDataOpen(int a0, int a1) {
    switch (a0) {
        case 1:
            switch (a1) {
                case 1:
                    D_0062BFC0 = D_0062A4E8;
                    return;
                case 0:
                    D_0062A4EC = 0x1D9020;
                    return;
                case 2:
                    return;
            }
            func_001AAD00(D_00551FC8, 0x1CC);
            func_00260380(D_00551FC8, 0x1CC, D_0062C388);
            return;
        case 2:
            if (a1 == 0) {
                D_0062BFC4 = D_0062A4E8;
                return;
            }
            func_001AAD00(D_00551FC8, 0x1D6);
            func_00260380(D_00551FC8, 0x1D6, D_0062C388);
            return;
    }
    func_001AAD00(D_00551FC8, 0x1DB);
    func_00260380(D_00551FC8, 0x1DB, D_0062C388);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataOpenSync);

extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern void AdpcmInterLeaveVolumeSet(int *a0, int a1, int a2, int a3);
extern char D_00551FC8[];
extern char D_0062C388[];

void soundDataClose(int *a0, int a1, int a2, int a3, int a4) {
    *a0 = a1;
    switch (a1) {
    case 0:
        func_001AAD00(D_00551FC8, 0x254);
        func_00260380(D_00551FC8, 0x254, D_0062C388);
        return;
    case 1:
        func_001AAD00(D_00551FC8, 0x257);
        func_00260380(D_00551FC8, 0x257, D_0062C388);
        return;
    case 2:
        AdpcmInterLeaveVolumeSet(a0, a2, a3, a4);
        return;
    default:
        func_001AAD00(D_00551FC8, 0x25D);
        func_00260380(D_00551FC8, 0x25D, D_0062C388);
        return;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataSegAllClose);

extern void AdpcmVolumeSet(char *a0);
extern void func_00258CF0(int a0);
extern void func_00258FB8(int a0);
extern void func_002593F8(int a0, int a1);
extern void iosMallocCheckLeak2(int a0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeVolSet);



extern char D_006A3070[];
extern void soundSeVolSet(char *p);
extern void soundDataOpen(int a0, int a1);

void debug_DispSEInfo(int a0, int a1)
{
    char *p = D_006A3070;
    char *end = D_006A3070 + 0x300;
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", sound3DParamSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", _soundSeDefPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", _soundSeDefStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefStopNoRelease);

extern void soundSeDefStopNoRelease(int a0, int a1);

void soundSeDefPitchSet(int a0) {
    soundSeDefStopNoRelease(a0, 0);
}

void soundReqTickProc(int a0) {
    soundSeDefStopNoRelease(a0, 1);
}

extern char D_006A3370[];
extern int func_00259DF8(int a0);

void soundSeEnvPlay(int a0)
{
    char *entry;
    short id;
    entry = &D_006A3370[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    func_00259DF8(id);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeEnvNotUseClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataSegNextStageNotUseClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", Ee2Iop);

extern void debug_assertMessage();
extern void func_001007A0(int a);
extern int func_001008E0(int p, int a);
extern int func_001008C0(int h);

extern char D_00551F50[];
extern char D_00551F68[];
extern char D_00551F80[];

int soundOutputModeGet(int a0, int a1, int a2)
{
    int buf[4];
    int x;
    debug_assertMessage(D_00551F50);
    debug_assertMessage(D_00551F68, a0, a1, a2);
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = 0;
    func_001007A0(0);
    x = func_001008E0((int)buf, 1);
    while (func_001008C0(x) >= 0) ;
    debug_assertMessage(D_00551F80);
    func_001007A0(0);
    return (x >= 0) ? 0 : -1;
}

extern int D_0062A4FC;
extern int D_0062A4F0;

int soundReverbDepthGet(void) {
    return D_0062A4FC;
}

int soundBufAdpcmChAlloc(void) {
    return D_0062A4F0;
}

extern unsigned long long D_0062BFC8;
extern char D_00552060[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBufAdpcmFree);


extern unsigned long long D_0062BFC8;

void soundDataAreaSearch(void *a0) {
    unsigned long long *p = (unsigned long long *)((char *)a0 + 0x18);
    D_0062BFC8 &= ~*p;
    *p = 0;
}

char *soundDataAreaGet(int *a0) {
    int key = *a0;
    char *p = D_006A3070;
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

extern int func_00260568(void *dst, int val, int size);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundHDDataSet);


extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern void soundBufSegFree(char *e);
extern char D_00551FC8[];
extern char D_0062C388[];
extern char D_006A3070_b[] __asm__("D_006A3070");

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

char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4) {
    int hi = a2 << 0x10;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = (SqEntry *)hd_search(D_006A3070, &key);
    if (e == 0) {
        key = 0;
        e = (SqEntry *)hd_search(D_006A3070_b, &key);
        if (e == 0) {
            func_001AAD00(D_00551FC8, 0x142);
            func_00260380(D_00551FC8, 0x142, D_0062C388);
        }
        func_00260568(e, 0, 0x30);
        e->num = a1;
        e->bank = a2;
        e->unk6 = a4;
        e->unk4 = a3;
        e->unk28 = -1;
    }
    e->unkC = a0;
    soundBufSegFree((char *)e);
    return (char *)e;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefPlay);

extern int soundSeDefStop(int a0, int a1, int a2, int a3, float f, int t0, int t1);
extern void _soundSeDefStop(int *p);

int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3)
{
    int idx = soundSeDefStop(a0, a1, a2, a3, -1.0f, 0, 0);
    if (idx >= 0) {
        _soundSeDefStop((int *)((char *)D_006A3370 + (idx & 0xFF) * 64));
    }
    return idx;
}

int soundSeDefVolumeRateGet(int a0, int a1, int a2, int a3)
{
    int idx = ((int (*)(int, int, int, int, int, int))soundSeDefStop)(a0, a1, a2, a3, 0, 0);
    if (idx >= 0) {
        _soundSeDefStop((int *)((char *)D_006A3370 + (idx & 0xFF) * 64));
    }
    return idx;
}

float soundSeDefVolumeRateSet(int a0)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A3370 + off;
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
    return *(float *)(D_006A3370 + off + 0x18);
}

void soundSeGroupStop(int a0, float f)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A3370 + off;
    if (*(short *)(e + 0x10) >= 0) {
        a0 = a0 >> 8;
        if (a0 == *(unsigned short *)e) {
            *(float *)(D_006A3370 + off + 0x18) = f;
        }
    }
}

void soundSeGroupGet(int arg)
{
    char *p = D_006A3370;
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

extern int D_0062A524;

int soundSePlayModeStop(void) {
    return D_0062A524 = ((D_0062A524 + 1) & 0x0FFFFFFF) | 0x10000000;
}

void soundVBlank(int arg)
{
    char *p = D_006A3370;
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

extern int func_00259108(int a0, int a1);
extern int D_0062AF94;
extern int D_00271240[];

void soundSeKindBuild(void)
{
    char *p = D_006A3370;
    int i = 0;
    do {
        if (*(int *)(p + 0x30) != 0) {
            int r = func_00259108(1, *(short *)(p + 0x10));
            if (r == 0) {
                soundSeDefPitchSet(((int)*(unsigned short *)p << 8) | i);
            } else if (r & 2) {
                if (D_0062AF94 == 0) {
                    if (D_00271240[5] != 0 &&
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


extern void AdpcmStop(char *p);

void soundSeSemiCommonLoadChk(void)
{
    int i;
    for (i = 0; i < 0x300; i += 0x30) {
        char *p = D_006A3070 + i;
        if (*(unsigned short *)(p + 2) == 0x11) {
            AdpcmStop(p);
        }
    }
}

extern char D_002E2A10[];
extern char D_005E44A0[];

void soundSeEnvDefaultSet(int idx)
{
    char *base = (char *)D_002E2A10;
    short *q = (short *)(base + 0xAD8);
    int i;
    for (i = 0x56C; i >= 0; i--) {
        *q = 0;
        q--;
    }
    for (i = 0; i < 0x10; i++) {
        char *entry = (char *)D_006A3070 + i * 0x30;
        if (*(unsigned short *)(entry + 2) == 0xB) {
            unsigned short target = *(unsigned short *)entry;
            int j;
            for (j = 0; j < 0xEDE; j++) {
                short *e2 = (short *)((char *)D_005E44A0 + j * 8);
                if (e2[0] == target) {
                    *(short *)(D_002E2A10 + e2[3] * 2) = j;
                }
            }
        }
    }
}

extern int D_0062A500;

int debug_req(void) {
    return D_0062A500;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    short              f_10;  /* 0x10 */
    unsigned int       f_30;  /* 0x30 */
} S_006A3370;  /* stride 0x40 */

typedef struct {
    unsigned int       f_60;  /* 0x60 */
} S_005E1C00;  /* stride 0x64 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned short     f_2;  /* 0x02 */
} S_006A3070;

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_002E2A10;  /* stride 0x2 */

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_005E44A0;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00551F30;  /* stride 0x4 */

/* end struct shapes */
