#include "common.h"

#include "ico/types.h"

extern int D_0063C1CC;
extern void sceSifFreeIopHeap();

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStreamFree);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmTickProc2);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmDataSet);
extern char D_00552118[];
extern void SgStAdpcmPlay(long long a0);
extern extern void debug_StdPrintfDummy();

void AdpcmPlay(void *a0) {
    debug_StdPrintfDummy(D_00552118);
    SgStAdpcmPlay(*(long long *)((char *)a0 + 0x30));
}
extern int SgStAdpcmStop(unsigned long long a0);

void AdpcmStop(int a0)
{
    SgStAdpcmStop(*(long long *)(a0 + 0x30));
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmOpen);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmClose);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmInterStereoVolumeSet);
extern void AdpcmInterStereoVolumeSet(void *a0, int a1, int a2);

void AdpcmInterLeaveVolumeSet(int a0, int a1, int a2) {
    char *b = *(char **)(a0 + 0x2C);
    short *q = (short *)(b + (a1 * 2 + 1) * 2);
    short *r = (short *)(b + a1 * 4);
    q[0x20] = a2;
    r[0x1E] = a2;
    AdpcmInterStereoVolumeSet(b, a1 * 2, a2);
}
void AdpcmVolumeSet(int a0, int a1) {
    AdpcmInterLeaveVolumeSet(a0, 0, a1);
}
extern int D_0063C1C8;

void adpcmPauseRequest(int val) {
    D_0063C1C8 = val;
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStreamHeap);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStreamInit);
extern char D_005520B0[];
extern int D_0063C1B8;
extern int D_0063C1C0[2];

int AdpcmIopBuffAlloc(void) {
    int i;
    for (i = 0; i < 2; i++) {
        if (D_0063C1C0[i] == 0) {
            goto found;
        }
    }
    debug_StdPrintfDummy(D_005520B0);
    return 0;
found:
    D_0063C1C0[i] = 1;
    return D_0063C1B8 + i * 0x5C000;
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmNotUseIopAreaFree);
extern char D_00552140[];
extern char D_00552150[];
extern int *adpcmDataSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void iosCdvdBackGroundMgrDelete(int x);
extern void iosCdvdBackGroundMgrSeek(int a, int b);

int *AdpcmOpenSync(int *self)
{
    int *r;
    debug_StdPrintfDummy((int *)D_00552140);
    if (self[5] != 0) goto body;
    return 0;
body:
    if (((int *)self[5])[0x40] != 0) {
        return (int *)-1;
    }
    debug_StdPrintfDummy((int *)D_00552150);
    iosCdvdBackGroundMgrDelete(self[5]);
    r = adpcmDataSet(0, self[1], 0x11, self[2], 0, self[3], self[4]);
    iosCdvdBackGroundMgrSeek(((int *)r[11])[10], 0x5C000);
    return r;
}
extern int D_006BF498[];

void AdpcmFadeCloseAll(short a0)
{
    int *p = D_006BF498;
    int *end = (int *)((char *)p + 0xB0);
    do {
        if (*p != 0) {
            *(short *)((char *)p + 0x44) = a0;
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);
}
int AdpcmUseAreaGet(void)
{
    int count = 0;
    int *p = D_0063C1C0;
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
int AdpcmFreeAreaGet(void)
{
    int count = 0;
    int *p = D_0063C1C0;
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
extern void adpcmPauseRequest__p4(short *p, int doubled_idx) __asm__("AdpcmInterStereoVolumeSet");

void AdpcmInterStereoVolumeSetAll(void)
{
    int i;
    for (i = 0; i < 0xB0; i += 0x58) {
        int *p = (int *)((char *)D_006BF498 + i);
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
short AdpcmInterLeaveVolumeGet(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}
short AdpcmVolumeGet(char *self) {
    return *(short *)(*(char **)(self + 0x2C) + 0x3C);
}
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmTickProc);
void adpcmDiskNotReady(void) {}
void adpcmDiskReturnReady(void) {}
extern void iosCdvdBackGroundReadIOPm();

int adpcmOpenProc(int a0, int a1)
{
    iosCdvdBackGroundReadIOPm(a0, *(int *)(a1 + 0xC), 0x5C000);
    return 1;
}
void adpcmOpenDiskNotReady(void) {}
