#include "common.h"

#include "ico/types.h"

extern int D_0063C1CC;
extern void sceSifFreeIopHeap();

void AdpcmStreamFree(void)
{
    sceSifFreeIopHeap(D_0063C1CC);
}
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

inline void adpcmPauseRequest(int val) {
    D_0063C1C8 = val;
}
extern char D_00552098[];
extern int D_0063C1B8;
extern int iosSifAllocIopHeapDebug(int a, void *b, int c);

inline void AdpcmStreamHeap(void)
{
    int r = iosSifAllocIopHeapDebug(0xB8800, D_00552098, 68);
    D_0063C1CC = r;
    if (r & 0x7FF) {
        D_0063C1B8 = (r / 0x800 + 1) * 0x800;
    } else {
        D_0063C1B8 = r;
    }
}
extern int D_006BF548[];
extern int D_006BF498[];
extern int D_0063C1C0[2];
extern int SgGetSpuSlotMalloc(int a);
extern void SgStAdpcmInit(void);

inline void AdpcmStreamInit(void)
{
    int i;
    int *p;

    for (i = 0, p = D_006BF548; i < 4; i++, p++) {
        *p = SgGetSpuSlotMalloc(1);
    }
    AdpcmStreamHeap();
    SgStAdpcmInit();
    for (i = 0; i < 2; i++) {
        *(int *)((char *)D_006BF498 + i * 0x58) = 0;
    }
    for (i = 0; i < 2; i++) {
        D_0063C1C0[i] = 0;
    }
    D_0063C1C8 = 0;
}
extern char D_005520B0[];
extern int D_0063C1B8;
extern int D_0063C1C0[2];

inline int AdpcmIopBuffAlloc(void) {
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
extern char D_005520D0[];
extern int D_006BF498[];

inline int AdpcmNotUseIopAreaFree(void)
{
    int cnt = 0;
    int i;
    unsigned char buf[2];
    int *p = D_006BF498;
    int *end = (int *)((char *)p + 0xB0);

    *(short *)buf = 0;

    do {
        if (*p != 0) {
            int no = (*(int *)((char *)p + 0x18) - D_0063C1B8) / 0x5C000;
            if (no < 3) {
                buf[no] = 1;
            }
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);

    i = 0;
    do {
        if (buf[i] == 0) {
            if (D_0063C1C0[i] != 0) {
                debug_StdPrintfDummy(D_005520D0);
                cnt++;
                D_0063C1C0[i] = 0;
            }
        }
        i++;
    } while (i < 2);
    return cnt;
}
extern char D_00552140[];
extern char D_00552150[];
extern int *adpcmDataSet(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void iosCdvdBackGroundMgrDelete(int x);
extern void iosCdvdBackGroundMgrSeek(int a, int b);

inline int *AdpcmOpenSync(int *self)
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

inline void AdpcmFadeCloseAll(short a0)
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
inline int AdpcmUseAreaGet(void)
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
inline int AdpcmFreeAreaGet(void)
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

inline void AdpcmInterStereoVolumeSetAll(void)
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
inline short AdpcmInterLeaveVolumeGet(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}
inline short AdpcmVolumeGet(char *self) {
    return *(short *)(*(char **)(self + 0x2C) + 0x3C);
}
extern int SgStAdpcmIopReadAddr(int a);
extern void iosCdvdBackGroundReadIOPm(int a0, int a1, int a2);
extern void iosCdvdBackGroundMgrSeek(int a, int b);

inline int adpcmTickProc(int self, int obj)
{
    int *st = *(int **)(obj + 0x2C);
    int size;
    int cur = SgStAdpcmIopReadAddr(st[2]);

    if (cur != st[4]) {
        if (cur > st[4]) {
            size = cur - st[4];
        } else {
            size = st[7] - st[4];
        }
        if (size > 0x1EAAA || cur < st[4]) {
            iosCdvdBackGroundReadIOPm(self, st[6] + st[4], size);
        } else {
            size = 0;
        }
        if (*(int *)(self + 0x110) >= st[9]) {
            iosCdvdBackGroundMgrSeek(self, st[8] + (*(int *)(self + 0x110) - st[9]));
        }
        st[4] = st[4] + size;
        if (st[4] >= st[7]) {
            st[4] = 0;
        }
    }
    return 0;
}
inline void adpcmDiskNotReady(void) {}
inline void adpcmDiskReturnReady(void) {}
extern void iosCdvdBackGroundReadIOPm();

inline int adpcmOpenProc(int a0, int a1)
{
    iosCdvdBackGroundReadIOPm(a0, *(int *)(a1 + 0xC), 0x5C000);
    return 1;
}
inline void adpcmOpenDiskNotReady(void) {}
