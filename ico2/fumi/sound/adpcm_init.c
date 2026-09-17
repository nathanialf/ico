#include "common.h"
#include "debug.h"
#include "ios.h"
#include "adpcm_init.h"
#include <sifrpc.h>
#include "s_init.h"

extern int D_0063C1CC;

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

/* kept local: this TU's uses of iosCdvdDiskStatusGet do not fit the prototype in cdvd.h */
extern int iosCdvdDiskStatusGet(void);
extern int D_0063C1C8;
extern const AdpcmDataRec D_00559D50[];
extern int SgStAdpcmChannelPitch(long long mask, int pitch);
extern int SgStAdpcmIopReadAddr(int addr);

void adpcmTickProc2(int *a0)
{
    AdpcmStream *self = (AdpcmStream *)a0[11];
    int i;

    if (iosCdvdDiskStatusGet() == 0 && D_0063C1C8 == 0) {
        for (i = 0; i < self->n; i++) {
            char *ch = (char *)self->ch;
            int ofs = i * 4;
            int no = *(unsigned short *)a0;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), D_00559D50[no].pitch);
        }
    } else {
        for (i = 0; i < self->n; i++) {
            char *ch = (char *)self->ch;
            int ofs = i * 4;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), 0);
        }
        return;
    }
    if (self->f46 != 0) {
        int addr = SgStAdpcmIopReadAddr(self->ch[0]);
        int delta;

        if (addr >= self->f4C) {
            delta = addr - self->f4C;
        } else {
            delta = self->f1C - self->f4C + addr;
        }
        self->f4C = addr;
        if (delta != 0) {
            self->f50 -= delta;
            if (self->f50 <= 0) {
                self->f48 += 1;
                self->f50 += self->f24 - self->f20;
            }
            if (self->f46 != 0 && self->f48 >= self->f46) {
                soundDataClose(a0);
                return;
            }
        }
    }
    if (self->f44 != 0) {
        int d = AdpcmVolumeGet((char *)a0) - self->f44;

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

extern int D_006BF498[];
extern int D_006BF548[];

/* adpcm_init.o's .rodata run opens with these three named objects: the two
   messages are printed further down the file than the strings that follow
   them in the ROM run. */
static const char adpcmFile[] = __FILE__;

static const char adpcmNoAllocMsg[] = "AdpcmIopBuffAlloc not alloc\n";

/* the IOP area is reserved but unused, so it is being freed */
static const char adpcmFreeIopMsg[] =
    "IOP領域が確保されているのにもかかわらず,使われていなので解放します\n";

extern char D_0063A630[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int soundBufAdpcmChAlloc(AdpcmObj *self, int *chp);
extern int SgStAdpcmOpen(AdpcmChReq *req);
extern int SgStAdpcmChannelVolume(long long mask, int l, int r);
/* kept local: this TU's uses of iosCdvdBackGroundMgrAdd do not fit the prototype in cdvd.h */
extern int iosCdvdBackGroundMgrAdd(char *name, void *proc, void *self, void *notready, int a4,
                                   void *a5, int a6, int a7);
/* kept local: this TU's uses of iosCdvdBackGroundMgrSeek do not fit the prototype in cdvd.h */
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
    debug_assert(adpcmFile, 363);
    __assert(adpcmFile, 363, D_0063A630);
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
        debug_assert(adpcmFile, 381);
        __assert(adpcmFile, 381, D_0063A630);
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

extern void SgStAdpcmPlay(long long a0);

void AdpcmPlay(void *a0)
{
    debug_StdPrintfDummy("AdpcmPlay\n");
    SgStAdpcmPlay(*(long long *)((char *)a0 + 0x30));
}

extern int SgStAdpcmStop(unsigned long long a0);

void AdpcmStop(int a0)
{
    SgStAdpcmStop(*(long long *)(a0 + 0x30));
}

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
    debug_StdPrintfDummy(adpcmNoAllocMsg);
    return 0;
found:
    D_0063C1C0[i] = 1;
    return D_0063C1B8 + i * 0x5C000;
}

extern char D_0063A638[];
/* kept local: this TU's uses of iosCdvdBackGroundMgrAdd do not fit the prototype in cdvd.h */
extern int iosCdvdBackGroundMgrAdd(char *name, void *proc, void *self, void *notready, int a4,
                                   void *a5, int a6, int a7);

void AdpcmOpen(AdpcmOpenReq *self, int no, int a2, int a3)
{
    int req;

    debug_StdPrintfDummy("AdpcmOpen id%d \n", no);
    req = (no & 0xFFFF) | 0x110000;
    if (soundDataAreaSearch(&req) != 0) {
        self->bg = 0;
        return;
    }
    self->ch = a2;
    self->id = no;
    self->iopBuf = AdpcmIopBuffAlloc();
    if (self->iopBuf != 0) {
        self->bg = iosCdvdBackGroundMgrAdd((char *)&D_00559D50[no], adpcmOpenProc, self,
                                           adpcmOpenDiskNotReady, 0, self, 0, 0);
    } else {
        self->bg = 0;
        debug_StdPrintfDummy(D_0063A638, (char *)&D_00559D50[no]);
    }
    self->f10 = a3;
}

/* kept local: this TU's uses of iosCdvdBackGroundMgrDelete do not fit the prototype in cdvd.h */
extern void iosCdvdBackGroundMgrDelete(int handle);
extern int SgStAdpcmClose(int ch);

static inline void AdpcmIopBuffFree(AdpcmStream *self)
{
    int adr = self->f18;
    int no = (adr - D_0063C1B8) / 0x5C000;

    if (no >= 3) {
        debug_assert(adpcmFile, 143);
        __assert(adpcmFile, 143, D_0063A630);
    }
    D_0063C1C0[no] = 0;
}

void AdpcmClose(int *a0)
{
    AdpcmStream *self = (AdpcmStream *)a0[11];
    int i;
    int j;

    if (self != 0 && self->f28 != 0) {
        iosCdvdBackGroundMgrDelete(self->f28);
        self->f28 = 0;
        AdpcmStop((int)self);
        for (i = 0; i < self->n; i++) {
            char *ch = (char *)self->ch;
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
        debug_assert(adpcmFile, 605);
        __assert(adpcmFile, 605, D_0063A630);
    found:
        *(int *)((char *)D_006BF498 + j * 0x58) = 0;
        self->mask = 0;
    }
}

extern int D_0063A628;

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

inline void adpcmPauseRequest(int val)
{
    D_0063C1C8 = val;
}

inline void AdpcmStreamHeap(void)
{
    int r = iosSifAllocIopHeapDebug(0xB8800, adpcmFile, 68);
    D_0063C1CC = r;
    if (r & 0x7FF) {
        D_0063C1B8 = (r / 0x800 + 1) * 0x800;
    } else {
        D_0063C1B8 = r;
    }
}

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
                debug_StdPrintfDummy(adpcmFreeIopMsg);
                cnt++;
                D_0063C1C0[i] = 0;
            }
        }
        i++;
    } while (i < 2);
    return cnt;
}

/* kept local: this TU's uses of iosCdvdBackGroundMgrDelete do not fit the prototype in cdvd.h */
extern void iosCdvdBackGroundMgrDelete(int x);

inline int *AdpcmOpenSync(AdpcmOpenReq *self)
{
    int *r;
    debug_StdPrintfDummy("AdpcmOpensync\n");
    if (self->bg != 0)
        goto body;
    return 0;
body:
    if (((int *)self->bg)[0x40] != 0) {
        return (int *)-1;
    }
    debug_StdPrintfDummy("AdpcmOpensync done\n");
    iosCdvdBackGroundMgrDelete(self->bg);
    r = adpcmDataSet(0, self->id, 0x11, self->ch, 0, self->iopBuf, self->f10);
    iosCdvdBackGroundMgrSeek(((int *)r[11])[10], 0x5C000);
    return r;
}

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
    for (i = 0; i < 176; i += 0x58) {
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
/* kept local: this TU's uses of iosCdvdBackGroundReadIOPm do not fit the prototype in cdvd.h */
extern void iosCdvdBackGroundReadIOPm(int a0, int a1, int a2);

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

/* kept local: this TU's uses of iosCdvdBackGroundReadIOPm do not fit the prototype in cdvd.h */
extern void iosCdvdBackGroundReadIOPm();

inline int adpcmOpenProc(int a0, int a1)
{
    iosCdvdBackGroundReadIOPm(a0, *(int *)(a1 + 0xC), 0x5C000);
    return 1;
}

inline void adpcmOpenDiskNotReady(void) {}
