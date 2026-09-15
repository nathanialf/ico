#include "common.h"

/* prototypes: their order is the deferred inline tail's emission order */
void adpcmPauseRequest(int val);
void AdpcmStreamHeap(void);
void AdpcmStreamInit(void);
int AdpcmIopBuffAlloc(void);
int AdpcmNotUseIopAreaFree(void);
int *AdpcmOpenSync(int *self);
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
extern int D_0063C1CC;
extern void sceSifFreeIopHeap();

void AdpcmStreamFree(void)
{
    sceSifFreeIopHeap(D_0063C1CC);
}

typedef struct {
    char _0[0x30];
    int f30;
    int f34;
    int pitch; /* 0x38 */
    int f3C;   /* 0x3C */
} AdpcmDataRec;

extern int iosCdvdDiskStatusGet(void);
extern int D_0063C1C8;
extern const AdpcmDataRec D_00559D50[];
extern int SgStAdpcmChannelPitch(long long mask, int pitch);
extern int SgStAdpcmIopReadAddr(int addr);
extern void soundDataClose(int *obj);
extern void AdpcmVolumeSet(int obj, int vol);

void adpcmTickProc2(int *a0)
{
    int *self = (int *)a0[11];
    int i;

    if (iosCdvdDiskStatusGet() == 0 && D_0063C1C8 == 0) {
        for (i = 0; i < self[1]; i++) {
            char *ch = (char *)(self + 2);
            int ofs = i * 4;
            int no = *(unsigned short *)a0;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), D_00559D50[no].pitch);
        }
    } else {
        for (i = 0; i < self[1]; i++) {
            char *ch = (char *)(self + 2);
            int ofs = i * 4;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), 0);
        }
        return;
    }
    if (*(short *)((char *)self + 0x46) != 0) {
        int addr = SgStAdpcmIopReadAddr(self[2]);
        int delta;

        if (addr >= self[19]) {
            delta = addr - self[19];
        } else {
            delta = self[7] - self[19] + addr;
        }
        self[19] = addr;
        if (delta != 0) {
            self[20] -= delta;
            if (self[20] <= 0) {
                *(short *)((char *)self + 0x48) += 1;
                self[20] += self[9] - self[8];
            }
            if (*(short *)((char *)self + 0x46) != 0 &&
                *(short *)((char *)self + 0x48) >= *(short *)((char *)self + 0x46)) {
                soundDataClose(a0);
                return;
            }
        }
    }
    if (*(short *)((char *)self + 0x44) != 0) {
        int d = AdpcmVolumeGet((char *)a0) - *(short *)((char *)self + 0x44);

        if (d < 0) {
            d = 0;
        }
        if (d == 0) {
            soundDataClose(a0);
            return;
        }
        AdpcmVolumeSet((int)a0, d);
    }
}

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

extern int D_006BF498[];
extern int D_006BF548[];
extern char D_00552098[];
extern char D_0063A630[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern AdpcmObj *soundDataAreaGet(int a0, int a1, int a2, int a3);
extern int soundBufAdpcmChAlloc(AdpcmObj *self, int *chp);
extern int SgStAdpcmOpen(AdpcmChReq *req);
extern int SgStAdpcmChannelVolume(long long mask, int l, int r);
extern int Ee2Iop(int a0, int a1, int a2);
extern int iosCdvdBackGroundMgrAdd(char *name, void *proc, void *self, void *notready, int a4,
                                   void *a5, int a6, int a7);
extern void iosCdvdBackGroundMgrSeek(int a, int b);

int *adpcmDataSet(int a0, int no, int bank, int a3, int size, int a5, int a6)
{
    AdpcmChReq req;
    AdpcmObj *obj;
    AdpcmStream *p;
    int i;
    int j;

    if (size > 0x5C000) {
        size = 0x5C000;
    }
    obj = soundDataAreaGet(no, bank, 2, a3);
    for (i = 0; i < 2; i++) {
        int *q = (int *)((char *)D_006BF498 + i * 0x58);
        if (q[0] == 0) {
            goto found;
        }
    }
    debug_assert(D_00552098, 0x16B);
    __assert(D_00552098, 0x16B, D_0063A630);
found:
    p = (AdpcmStream *)((char *)D_006BF498 + i * 0x58);
    p->used = 1;
    obj->stream = p;
    p->n = D_00559D50[no].f3C;
    switch (p->n) {
    case 1:
        p->f38 = 0x10000;
        break;
    case 2:
        p->f38 = 0x20000;
        break;
    case 4:
        p->f38 = 0x40000;
        break;
    default:
        debug_assert(D_00552098, 0x17D);
        __assert(D_00552098, 0x17D, D_0063A630);
    }
    p->mask = 0;
    for (j = 0; j < p->n; j++) {
        req.f10 = soundBufAdpcmChAlloc(obj, &req.ch);
        p->ch[j] = req.ch = D_006BF548[req.ch];
        req.f4 = p->f38 | 2;
        req.f8 = a5 + (0x800 / p->n) * j;
        req.fC = 0x5C000;
        req.f14 = 0x4000;
        SgStAdpcmOpen(&req);
        if (p->f38 == 0x10000) {
            p->f40[j] = 0x3FFF;
            p->f3C[j] = 0x3FFF;
        } else if ((j & 1) == 0) {
            p->f3C[j] = 0x3FFF;
            p->f40[j] = 0;
        } else {
            p->f40[j] = 0x3FFF;
            p->f3C[j] = 0;
        }
        p->f44 = 0;
        SgStAdpcmChannelVolume(1LL << p->ch[j], p->f3C[j], p->f40[j]);
        SgStAdpcmChannelPitch(1LL << p->ch[j], D_00559D50[no].pitch);
        p->mask |= 1LL << p->ch[j];
    }
    if (size < 0x5C000) {
        p->f10 = size;
    } else {
        p->f10 = 0;
    }
    p->f14 = D_00559D50[no].pitch;
    p->f18 = a5;
    p->f1C = 0x5C000;
    p->f24 = D_00559D50[no].f34 << 11;
    p->f20 = D_00559D50[no].f30 << 11;
    p->f4C = 0;
    p->f50 = D_00559D50[no].f34 << 11;
    p->f46 = a6;
    p->f48 = 0;
    if (size != 0) {
        Ee2Iop(a0, a5, size);
    }
    p->f28 = iosCdvdBackGroundMgrAdd((char *)&D_00559D50[no], adpcmTickProc, obj, adpcmDiskNotReady,
                                     (int)adpcmDiskReturnReady, obj, 0, 0);
    iosCdvdBackGroundMgrSeek(p->f28, size);
    return (int *)obj;
}

extern char D_00552118[];
extern void SgStAdpcmPlay(long long a0);
extern extern void debug_StdPrintfDummy();

void AdpcmPlay(void *a0)
{
    debug_StdPrintfDummy(D_00552118);
    SgStAdpcmPlay(*(long long *)((char *)a0 + 0x30));
}

extern int SgStAdpcmStop(unsigned long long a0);

void AdpcmStop(int a0)
{
    SgStAdpcmStop(*(long long *)(a0 + 0x30));
}

extern char D_005520B0[];
extern int D_0063C1B8;
extern int D_0063C1C0[2];

inline int AdpcmIopBuffAlloc(void)
{
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

extern char D_00552128[];
extern char D_0063A638[];
extern int soundDataAreaSearch(int *req);
extern int iosCdvdBackGroundMgrAdd(char *name, void *proc, void *self, void *notready, int a4,
                                   void *a5, int a6, int a7);

void AdpcmOpen(int *self, int no, int a2, int a3)
{
    int req;

    debug_StdPrintfDummy(D_00552128, no);
    req = (no & 0xFFFF) | 0x110000;
    if (soundDataAreaSearch(&req) != 0) {
        self[5] = 0;
        return;
    }
    self[2] = a2;
    self[1] = no;
    self[3] = AdpcmIopBuffAlloc();
    if (self[3] != 0) {
        self[5] = iosCdvdBackGroundMgrAdd((char *)&D_00559D50[no], adpcmOpenProc, self,
                                          adpcmOpenDiskNotReady, 0, self, 0, 0);
    } else {
        self[5] = 0;
        debug_StdPrintfDummy(D_0063A638, (char *)&D_00559D50[no]);
    }
    self[4] = a3;
}

extern char D_00552098[];
extern char D_0063A630[];
extern int D_006BF498[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void iosCdvdBackGroundMgrDelete(int handle);
extern int SgStAdpcmClose(int ch);
extern void soundBufAdpcmFree(int *obj);

static inline void AdpcmIopBuffFree(int *self)
{
    int adr = self[6];
    int no = (adr - D_0063C1B8) / 0x5C000;

    if (no >= 3) {
        debug_assert(D_00552098, 0x8F);
        __assert(D_00552098, 0x8F, D_0063A630);
    }
    D_0063C1C0[no] = 0;
}

void AdpcmClose(int *a0)
{
    int *self = (int *)a0[11];
    int i;
    int j;

    if (self != 0 && self[10] != 0) {
        iosCdvdBackGroundMgrDelete(self[10]);
        self[10] = 0;
        AdpcmStop((int)self);
        for (i = 0; i < self[1]; i++) {
            char *ch = (char *)(self + 2);
            int ofs = i * 4;
            SgStAdpcmClose(*(int *)(ch + ofs));
        }
        AdpcmIopBuffFree(self);
        soundBufAdpcmFree(a0);
        for (j = 0; j < 2; j++) {
            int *p = (int *)((char *)D_006BF498 + j * 0x58);
            if (p[0] != 0 && p == self) {
                goto found;
            }
        }
        debug_assert(D_00552098, 0x25D);
        __assert(D_00552098, 0x25D, D_0063A630);
    found:
        *(int *)((char *)D_006BF498 + j * 0x58) = 0;
        *(long long *)(self + 12) = 0;
    }
}

extern int D_0063A628;
extern int soundOutputModeGet(void);
extern int SgStAdpcmChannelVolume(long long mask, int l, int r);

/* vol is in the ABI (AdpcmInterLeaveVolumeSet passes it) but the ROM never
   reads $6: the levels come back out of the record the caller just wrote. */
/* K&R definition: it declares no prototype, which is what lets
 * AdpcmInterStereoVolumeSetAll below call this function with two arguments,
 * as ROM does. */
void AdpcmInterStereoVolumeSet(a0, ch, vol) char *a0;

int ch;

int vol;

{
    int j = ch + 1;
    short *r = (short *)(a0 + ch * 2);
    short *q = (short *)(a0 + j * 2);
    short lv = r[0x1E];
    short rv = q[0x20];

    if (D_0063A628 == 0) {
        rv = 0;
        lv = 0;
    }
    if (*(int *)(a0 + 0x38) == 0x10000) {
        return;
    }
    if (soundOutputModeGet() == 0) {
        int *p = (int *)(a0 + 8);
        int *c = p + ch;
        SgStAdpcmChannelVolume(1LL << *c, lv, 0);
        p += j;
        SgStAdpcmChannelVolume(1LL << *p, 0, rv);
    } else {
        int *p = (int *)(a0 + 8);
        int *c = p + ch;
        SgStAdpcmChannelVolume(1LL << *c, lv, rv);
        p += j;
        SgStAdpcmChannelVolume(1LL << *p, lv, rv);
    }
}

extern void AdpcmInterStereoVolumeSet();

void AdpcmInterLeaveVolumeSet(int a0, int a1, int a2)
{
    char *b = *(char **)(a0 + 0x2C);
    short *q = (short *)(b + (a1 * 2 + 1) * 2);
    short *r = (short *)(b + a1 * 4);
    q[0x20] = a2;
    r[0x1E] = a2;
    AdpcmInterStereoVolumeSet(b, a1 * 2, a2);
}

void AdpcmVolumeSet(int a0, int a1)
{
    AdpcmInterLeaveVolumeSet(a0, 0, a1);
}

extern int D_0063C1C8;

inline void adpcmPauseRequest(int val)
{
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
    if (self[5] != 0)
        goto body;
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
        if (v != 0)
            count = next;
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
        if (v == 0)
            count = next;
    } while (n >= 0);
    return count;
}

inline void AdpcmInterStereoVolumeSetAll(void)
{
    int i;
    for (i = 0; i < 0xB0; i += 0x58) {
        int *p = (int *)((char *)D_006BF498 + i);
        if (*p != 0) {
            int v = *(int *)((char *)p + 0x38);
            if (v == 0x20000)
                goto call0;
            if (v != 0x40000)
                goto skip;
            AdpcmInterStereoVolumeSet(p, 2);
        call0:
            AdpcmInterStereoVolumeSet(p, 0);
        skip:;
        }
    }
}

inline short AdpcmInterLeaveVolumeGet(char *self, int idx)
{
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}

inline short AdpcmVolumeGet(char *self)
{
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
