#include "common.h"









extern int D_00632218;
extern void AdpcmStop();
extern char D_006A95B0[];
extern int D_0063223C;
extern long long D_00633CD8;
extern char D_006A98B0[];
extern void func_0025DA68();
extern void func_0024A1E0();
extern int D_00632240;
extern void func_0025CCE0(int a0, int a1, int a2);
extern void func_0025CE78(int a0, int a1, int a2);
extern int D_00632208;
extern void func_0025CD28();
extern int  D_00632214;
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundReverbDepthSet);

void soundAllocIopHeap(int a0)
{
    D_00632214 = a0;
    func_0025CD28(a0);
}

void soundAllocIopFree(int a0)
{
    int val;
    D_00632208 = a0;
    val = (a0 * 32767) / 100;
    func_0025CCE0(0, val, val);
    func_0025CCE0(1, val, val);
    func_0025CE78(0, 0x3FFF, 0x3FFF);
    func_0025CE78(1, 0x3FFF, 0x3FFF);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenChk);

void soundBufAlloc(void)
{
    func_0024A1E0(D_00632240);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBufSegFree);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBDDataSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpen);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenSync);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataClose);

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

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefPitchSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundReqTickProc);

void soundSeEnvPlay(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    func_0025DA68(id);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegNextStageNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", Ee2Iop);

extern char D_00557C50[];
extern char D_00557C68[];
extern char D_00557C80[];
extern extern void debug_assertMessage();
extern void func_001007A0(int a);
extern int func_001008C0(int h);
extern int func_001008E0(int p, int a);

int soundOutputModeGet(int a0, int a1, int a2)
{
    int buf[4];
    int x;
    debug_assertMessage(D_00557C50);
    debug_assertMessage(D_00557C68, a0, a1, a2);
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = 0;
    func_001007A0(0);
    x = func_001008E0((int)buf, 1);
    while (func_001008C0(x) >= 0) ;
    debug_assertMessage(D_00557C80);
    func_001007A0(0);
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

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSQDataSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefPlay);

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
extern int func_0025CD78(int a0, int a1);

void soundSeKindBuild(void)
{
    char *p = D_006A98B0;
    int i = 0;
    do {
        if (*(int *)(p + 0x30) != 0) {
            int r = func_0025CD78(1, *(short *)(p + 0x10));
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
            AdpcmStop(p);
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

