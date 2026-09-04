#include "common.h"

#include "ico/types.h"






extern void func_00132DC0();
extern int  D_00633CB8[2];
extern int  D_006A94E0[];
extern int  D_00633CC0;
extern int SgStAdpcmStop(unsigned long long a0);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmTickProc2);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmOpen);

extern char D_00557BF8[];
extern extern void debug_StdPrintfDummy();
extern void SgStAdpcmPlay(long long a0);

void AdpcmPlay(void *a0) {
    debug_StdPrintfDummy(D_00557BF8);
    SgStAdpcmPlay(*(long long *)((char *)a0 + 0x30));
}

void AdpcmStop(int a0)
{
    SgStAdpcmStop(*(long long *)(a0 + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmInterLeaveVolumeSet);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmVolumeSet);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmInterStereoVolumeSet);

extern void AdpcmInterStereoVolumeSet(void *a0, int a1, int a2);

void AdpcmIopBuffAlloc(int a0, int a1, int a2) {
    char *b = *(char **)(a0 + 0x2C);
    short *q = (short *)(b + (a1 * 2 + 1) * 2);
    short *r = (short *)(b + a1 * 4);
    q[0x20] = a2;
    r[0x1E] = a2;
    AdpcmInterStereoVolumeSet(b, a1 * 2, a2);
}

void AdpcmOpenSync(int a0, int a1) {
    AdpcmIopBuffAlloc(a0, 0, a1);
}

void AdpcmFadeCloseAll(int val) {
    D_00633CC0 = val;
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStreamHeap);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStreamInit);

extern char D_00557B90[];
extern int D_00633CB0;

int AdpcmUseAreaGet(void) {
    int i;
    for (i = 0; i < 2; i++) {
        if (D_00633CB8[i] == 0) {
            goto found;
        }
    }
    debug_StdPrintfDummy(D_00557B90);
    return 0;
found:
    D_00633CB8[i] = 1;
    return D_00633CB0 + i * 0x5C000;
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmNotUseIopAreaFree);

extern int *AdpcmOpen(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern char D_00557C20[];
extern char D_00557C30[];
extern void func_00133500(int a, int b);
extern void iosCdvdBackGroundMgrDelete(int x);

int *AdpcmFreeAreaGet(int *self)
{
    int *r;
    debug_StdPrintfDummy((int *)D_00557C20);
    if (self[5] != 0) goto body;
    return 0;
body:
    if (((int *)self[5])[0x40] != 0) {
        return (int *)-1;
    }
    debug_StdPrintfDummy((int *)D_00557C30);
    iosCdvdBackGroundMgrDelete(self[5]);
    r = AdpcmOpen(0, self[1], 0x11, self[2], 0, self[3], self[4]);
    func_00133500(((int *)r[11])[10], 0x5C000);
    return r;
}

void AdpcmInterStereoVolumeSetAll(short a0)
{
    int *p = D_006A94E0;
    int *end = (int *)((char *)p + 0xB0);
    do {
        if (*p != 0) {
            *(short *)((char *)p + 0x44) = a0;
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);
}

int AdpcmInterLeaveVolumeGet(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v != 0) count = next;
    } while (n >= 0);
    return count;
}

int AdpcmVolumeGet(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v == 0) count = next;
    } while (n >= 0);
    return count;
}

/* A 2-parameter declaration of AdpcmInterStereoVolumeSet.  The ROM proves the two
 * declarations really coexisted: AdpcmIopBuffAlloc above sets $4/$5/$6 at its
 * call, while both calls below set only $4/$5.  sound/adpcm_init is a splat
 * blob spanning more than one original file, so both have to live here and
 * the alias is the only way to spell the second one. */
extern void adpcmPauseRequest__p4(short *p, int doubled_idx) __asm__("AdpcmInterStereoVolumeSet");

void GetDitchPosition(void)
{
    int i;
    for (i = 0; i < 0xB0; i += 0x58) {
        int *p = (int *)((char *)D_006A94E0 + i);
        if (*p != 0) {
            int v = *(int *)((char *)p + 0x38);
            if (v == 0x20000) goto call0;
            if (v != 0x40000) goto skip;
            adpcmPauseRequest__p4((short *)p, 2);
        call0:
            adpcmPauseRequest__p4((short *)p, 0);
        skip: ;
        }
    }
}

short DebugActOrientFlag(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}

short ACTGetEnvironment(char *self) {
    return *(short *)(*(char **)(self + 0x2C) + 0x3C);
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmTickProc);

void GetSofaPosition(void) {}

void GetCollisCenterPositionSimple(void) {}

int adpcmOpenProc(int a0, int a1)
{
    func_00132DC0(a0, *(int *)(a1 + 0xC), 0x5C000);
    return 1;
}

void func_00141160(void) {}

