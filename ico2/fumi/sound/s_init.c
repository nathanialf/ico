#include "common.h"
#include "typedef.h"
#include "s_init.h"
#include "debug.h"
#include "ios.h"
#include "memory.h"
#include "pad.h"
#include "adpcm_init.h"
#include "camera-root.h"
#include <sifrpc.h>
#include <libvu0.h>
#include <eekernel.h>

typedef struct SqEntry {
    unsigned short num;        /* 0x0 */
    short bank;                /* 0x2 */
    unsigned short unk4;       /* 0x4 */
    unsigned short unk6;       /* 0x6 */
    int unk8;                  /* 0x8 */
    int unkC;                  /* 0xC */
    int unk10[2];              /* 0x10 */
    long long chMask;          /* 0x18 */
    unsigned long long seMask; /* 0x20 */
    int unk28;                 /* 0x28 */
} SqEntry;

typedef struct SeEnvDef {
    float unk0;          /* 0x00 */
    int (*unk4)();       /* 0x04 */
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

/* The SE source definition record (0x3C bytes) a slot plays from: the same
   record `_soundSeDefStop` reaches through the slot's 0x38 pointer. */
typedef struct SeSrcDef {
    int unk0[8];          /* 0x00 */
    int unk20;            /* 0x20 */
    float unk24;          /* 0x24 */
    int unk28[3];         /* 0x28 */
    short unk34;          /* 0x34 */
    unsigned short unk36; /* 0x36 */
    unsigned int b0 : 4;  /* 0x38 bits 0..3 */
    unsigned int b4 : 2;
    unsigned int b6 : 1;
    unsigned int b7 : 1;
    unsigned int b8 : 1;
    unsigned int b9 : 23;
} SeSrcDef;

/* The slot's 0x04 status word, written both as a whole and bit by bit. */
typedef union SeFlag {
    unsigned int all;

    struct {
        short f0;
        unsigned int f16 : 8;
        unsigned int f24 : 1;
        unsigned int f25 : 1;
        unsigned int f26 : 1;
        unsigned int f27 : 1;
        unsigned int f28 : 1;
        unsigned int f29 : 1;
        unsigned int f30 : 1;
        unsigned int f31 : 1;
    } bit;
} SeFlag;

typedef struct SeSlot {
    unsigned short num; /* 0x00 */
    short unk2;         /* 0x02 */
    SeFlag flag;        /* 0x04 */
    unsigned int unk8;  /* 0x08 */
    int unkC;           /* 0x0C */
    short unk10;        /* 0x10 */
    short unk12;        /* 0x12 */
    short unk14;        /* 0x14 */
    short unk16;        /* 0x16 */
    float unk18;        /* 0x18 */
    float unk1C;        /* 0x1C */
    float unk20;        /* 0x20 */
    float unk24;        /* 0x24 */
    float unk28;        /* 0x28 */
    int (*unk2C)();     /* 0x2C */
    SqEntry *unk30;     /* 0x30 */
    int unk34;          /* 0x34 */
    SeSrcDef *unk38;    /* 0x38 */
    SeEnvDef *unk3C;    /* 0x3C */
} SeSlot;

extern char D_006BF570[];

/* INTERIM stand-in for soundDataAreaSearch (defined out of line further down,
   where the compiler emits the inline's own body): the tail still carries asm
   members, so the ROM-slot definition cannot be marked `inline` yet. */
static inline SqEntry *hd_search(int *pk)
{
    int i;
    SqEntry *r;
    for (i = 0; i < 16; i++) {
        r = (SqEntry *)&D_006BF570[i * 0x30];
        if (*(int *)&D_006BF570[i * 0x30] == *pk)
            goto found;
    }
    return 0;
found:
    return r;
}

extern char D_005521C0[];
extern char D_005521D0[];
extern char D_006BF870[];
extern int D_0063A370;
extern int D_0063A650;
extern long long D_0063C1E0;
extern long long D_0063C1E8;
extern void SgInit(void);
extern void SgSetDigitalOutputMode(int a0);
extern void SgSetTickMode(int a0);
extern void SgSetReverbEndAddr(int a0, int a1);
extern void SgSetReverbType(int a0, int a1);
extern void SgSetReverbDepth(int a0, int a1, int a2);
extern void SgSetMasterVol(int a0, int a1, int a2);

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
extern char D_005F5EB8[];
extern int D_0063A684;

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

void soundAllocIopFree(void)
{
    sceSifFreeIopHeap(D_0063A680);
}

extern char D_00552238[];
extern char D_00552248[];
extern char D_00552260[];
extern char D_00552270[];
extern char D_0063A660[];
extern void __assert(char *file, int line, char *msg);
extern void debug_assert(char *file, int line);
extern int SgVabOpenFakeBody(int a0, int a1);
extern void SgSetSeMasterVol(int vab, int vol);
extern int SgBgmOpen(int vab, int a1);
extern void SgSetBgmVol(int h, int vol, int pan);
extern void SgBgmPlay(int h);

/* A slot's request release, which the listing gives to lines 291 to 306 in all
   three of its users (soundDataOpenChk, soundDataClose, _soundSeDefStop): two
   helpers defined there and never emitted out of line, so static inlines (the
   names are ours).  seReqRelease takes the channel, not the slot, because
   _soundSeDefStop's copy recomputes the request word's address from it. */
static inline void seReqChClear(SqEntry *req, int ch, char **rp)
{
    long long bit = (long long)1 << ch;

    if ((req->seMask & bit) != 0) {
        req->seMask &= ~bit;
        D_0063C1E8 &= ~bit;
        *(unsigned short *)&D_006BF870[ch * 64] = *(unsigned short *)&D_006BF870[ch * 64] + 1;
        *rp = 0;
    }
}

static inline void seReqRelease(int ch)
{
    char **rp = (char **)&D_006BF870[ch * 64 + 0x30];
    SqEntry *req = *(SqEntry **)rp;

    if (req != 0)
        seReqChClear(req, ch, rp);
}

void soundDataOpenChk(char *self)
{
    int ok = 0;
    int vab;
    int ch;
    int i;
    int off;
    char *slot;
    char *sl;
    short h;
    int hr;
    long long one;
    long long bit;

    switch (*(unsigned short *)(self + 4)) {
    case 0:
        if (*(int *)(self + 8) != 0) {
            ok = (*(int *)(self + 0xC) != 0);
        }
        break;
    case 1:
        if (*(int *)(self + 8) != 0 && *(int *)(self + 0xC) != 0) {
            ok = (*(int *)(self + 0x10) != 0) ? *(unsigned short *)(self + 4) : 0;
        }
        break;
    default:
        debug_assert(D_005521E8, 358);
        __assert(D_005521E8, 358, D_0063A660);
        break;
    }
    if (ok == 0) {
        return;
    }
    vab = SgVabOpenFakeBody(*(int *)(self + 0xC), *(int *)(self + 0x18));
    *(int *)(self + 0x28) = vab;
    switch (*(unsigned short *)(self + 4)) {
    case 0:
        SgSetSeMasterVol(vab, 127);
        debug_StdPrintfDummy(D_00552238);
        return;
    case 1:
        one = 1;
        for (i = 0; i < 48; i++) {
            bit = one << i;
            if ((D_0063C1E8 & bit) == 0) {
                goto found;
            }
        }
        ch = -1;
        goto chk;
    found:
        D_0063C1E8 |= bit;
        ((SqEntry *)self)->seMask |= bit;
        sl = &D_006BF870[i * 64];
        ((SeSlot *)sl)->flag.all &= 0xFDFFFFFF;
        ch = i;
    chk:
        if (ch < 0) {
            debug_StdPrintfDummy(D_00552248);
            return;
        }
        off = ch * 64;
        hr = SgBgmOpen(*(int *)(self + 0x28), *(int *)(self + 0x10));
        slot = &D_006BF870[off];
        *(short *)(slot + 0x10) = hr;
        h = hr;
        if (h < 0) {
            seReqRelease(ch);
            debug_StdPrintfDummy(D_00552260);
            return;
        }
        SgSetBgmVol(h, 64, 0xFFFF);
        SgBgmPlay(h);
        *(char **)&D_006BF870[off + 0x30] = self;
        *(int *)&D_006BF870[off + 8] = 0;
        debug_StdPrintfDummy(D_00552270);
        return;
    default:
        return;
    }
}

extern int D_0063A640;
extern int D_0063A644;
extern int D_0063C1D8;
extern int D_0063C1DC;

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

extern char D_00552170[];
extern char D_00552188[];
extern char D_005521A0[];
extern void FlushCache(int a);
extern int sceSifDmaStat(int h);
extern int sceSifSetDma(int p, int a);
extern int memset(void *dst, int val, int size);
extern void SgDmaWrite(int heap, int addr, int size);
extern void SgGetDmaTransferStatus(int a0);

char *soundBDDataSet(int a0, int a1, int a2, int a3, int a4, int a5)
{
    SqEntry *e;
    int buf[4];
    int off;
    int chunk;
    int src;
    int heap;
    int h;
    int hi;
    int key;

    off = 0;
    hi = a2 << 16;
    key = (a1 & 0xFFFF) | hi;
    e = hd_search(&key);
    if (e == 0) {
        key = 0;
        e = hd_search(&key);
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
    e->unk8 = a0;
    a5 = (((a5 - 1) / 64) + 1) * 64;
    soundBufAlloc((SoundBufReq *)e, a5);
    while (a5 > 0) {
        chunk = (a5 > 0x78000) ? 0x78000 : a5;
        src = a0 + off;
        SgGetDmaTransferStatus(1);
        heap = D_0063A680;
        debug_StdPrintfDummy(D_00552170);
        debug_StdPrintfDummy(D_00552188, src, heap, chunk);
        buf[0] = src;
        buf[1] = heap;
        buf[2] = chunk;
        buf[3] = 0;
        FlushCache(0);
        h = sceSifSetDma((int)buf, 1);
        while (sceSifDmaStat(h) >= 0)
            ;
        debug_StdPrintfDummy(D_005521A0);
        FlushCache(0);
        if (chunk >= 65) {
            SgDmaWrite(D_0063A680, ((SoundBufReq *)e)->addr + off, chunk);
        } else {
            SgDmaWrite(D_0063A680, ((SoundBufReq *)e)->addr + off, 0x50);
        }
        if (e->unk4 == 1) {
            SgGetDmaTransferStatus(1);
        }
        a5 = a5 - chunk;
        off = off + chunk;
    }
    soundDataOpenChk((char *)e);
    return (char *)e;
}

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

extern int SgVabClose(int vab);
extern void SgBgmStop(unsigned int h, int mode);
extern int SgBgmClose(int h);
extern void AdpcmClose(char *self);

void soundDataClose(int *obj)
{
    SqEntry *self = (SqEntry *)obj;
    int i;
    char *slot;
    short h;

    switch (self->unk4) {
    case 0:
        SgVabClose(self->unk28);
        break;
    case 1:
        i = 0;
        while (self->seMask != 0) {
            if ((int)((self->seMask >> i) & 1)) {
                slot = &D_006BF870[i * 64];
                h = *(short *)(slot + 0x10);
                SgBgmStop(h, 1);
                SgBgmClose(h);
                seReqRelease(i);
            }
            i++;
        }
        SgVabClose(self->unk28);
        iosFree((void *)self->unkC);
        if (self->unk10[0] != 0) {
            iosFree((void *)self->unk10[0]);
        }
        break;
    case 2:
        AdpcmClose((char *)self);
        break;
    }
    *(int *)self = 0;
}

void soundDataSegAllClose(int a0, int a1)
{
    int i;
    char *tbl;
    /* base in the loop header, not in a declaration of its own: the same
       index for its sibling soundDataSegNextStageNotUseClose carries, and
       the form the listing's line rows for this function show */
    for (i = 0, tbl = D_006BF570; i < 768; i += 0x30) {
        char *p = tbl + i;
        if (*(int *)p != 0 && *(unsigned short *)(p + 6) == a0 &&
            *(unsigned short *)(p + 4) == a1) {
            soundDataClose(p);
        }
    }
    if (a1 == 2)
        return;
    soundBufSegFree(a0, a1);
}

extern float D_0063A64C;
extern void SgSetSeVolDirect(int id, int l, int r);

void soundSeVolSet(SeSlot *self)
{
    int l;
    int r;
    int cur;
    int d;
    int vol;

    if (self->flag.all & 0x20000000) {
        r = 0;
        l = 0;
    } else {
        l = (int)((float)self->unk12 * self->unk18);
        r = (int)((float)self->unk14 * self->unk18);
    }
    if (self->unk8 == 0xFFFFFFFF && self->unk3C != 0) {
        l = (int)((float)l * D_0063A64C);
        r = (int)((float)r * D_0063A64C);
    }
    if (l < 0) {
        l = 0;
    } else {
        l = (l < 4097) ? l : 4096;
    }
    if (r < 0) {
        r = 0;
    } else {
        r = (r < 4097) ? r : 4096;
    }
    cur = *(unsigned short *)&self->unk2;
    d = (short)(l - cur);
    if (((d < 0) ? -d : d) < 256 || (short)cur == -1) {
        self->unk2 = l;
    } else {
        self->unk2 = (d > 0) ? cur + 256 : cur - 256;
    }
    cur = *(unsigned short *)&self->flag;
    d = (short)(r - cur);
    if (((d < 0) ? -d : d) < 256 || (short)cur == -1) {
        *(short *)&self->flag = r;
    } else {
        *(short *)&self->flag = (d > 0) ? cur + 256 : cur - 256;
    }
    SgSetSeVolDirect(self->unk10, self->unk2, *(short *)&self->flag);
    if (self->unkC != 0) {
        vol = (r < l) ? l : r;
        vol = (int)((float)vol * (1.0f / 4096.0f) * 255.0f);
        iosPadActVolumeSet(self->unkC, vol & 0xFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/sound/s_init", debug_DispSEInfo);

extern void soundSeVolSet(SeSlot *self);

void sound3DParamSet(SeSlot *self)
{
    float v[4];
    float dist;
    int ang;
    float *cam;
    float *obj;
    float vol;
    float rate;
    float range;
    float front;
    float volL;
    float volR;
    int n;
    int a;
    int pan;
    int ret;

    self->unk14 = 0x1000;
    self->unk12 = 0x1000;
    if (self->unk2C != 0) {
        ret = self->unk2C();
        if (ret > 0) {
            self->flag.bit.f24 = 1;
            self->flag.bit.f25 = 0;
        } else if (ret < 0) {
            self->flag.bit.f24 = 0;
        } else {
            self->unk12 = 0;
            self->unk14 = 0;
            self->flag.bit.f24 = 0;
        }
        self->unk38->b8 = 1;
    }
    if ((self->flag.all & 0x02000000) && self->unk38->b8 == 0) {
        if (self->flag.all & 0x20000000) {
            SgSetSeVolDirect(self->unk10, 0, 0);
        }
        return;
    }
    if ((self->flag.all & 0x01000000) == 0 || (obj = (float *)self->unk34) == 0) {
        soundSeVolSet(self);
        return;
    }
    self->flag.all |= 0x02000000;
    if (self->flag.bit.f26 == 1) {
        cam = GetCameraPos();
        sceVu0CopyVector(v, (float *)self->unk34);
        v[1] = cam[1];
        CameraGetOtherObjOffset(v, &dist, &ang);
    } else {
        CameraGetOtherObjOffset(obj, &dist, &ang);
    }
    if (dist > self->unk28) {
        vol = 0.0f;
    } else if (dist < self->unk24) {
        vol = 1.0f;
    } else {
        dist = dist - self->unk24;
        range = self->unk20 - self->unk24;
        if (self->flag.bit.f30 == 0) {
            rate = dist / range;
            vol = 1.0f / (rate + 1.0f);
        } else {
            if (dist < range) {
                rate = dist / range;
                vol = 1.0f / (rate + 1.0f);
            } else {
                dist = dist - range;
                vol = 1.0f / (dist / ((self->unk28 - self->unk24) - range) + 1.0f) - 0.5f;
            }
        }
    }
    if (self->flag.bit.f27 == 1) {
        a = ang;
        pan = a;
        if (self->flag.bit.f28 == 1) {
            a = (a <= -1) ? -a : a;
            front = (float)a * -0.0027777778f + 1.0f;
        } else {
            front = 1.0f;
        }
        if (pan >= 0) {
            volL = 1.0f;
            a = pan;
            if (a >= 91) {
                a = 180 - a;
            }
            volR = -(1.0f - self->unk1C) / 90.0f * (float)a + 1.0f;
        } else {
            volR = 1.0f;
            a = -pan;
            if (a >= 91) {
                a = 180 - a;
            }
            volL = -(1.0f - self->unk1C) / 90.0f * (float)a + 1.0f;
        }
    } else {
        volR = 1.0f;
        front = 1.0f;
        volL = 1.0f;
    }
    n = (int)(vol * 4096.0f * front);
    self->unk12 = (float)n * volR;
    self->unk14 = (float)n * volL;
    soundSeVolSet(self);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/sound/s_init", _soundSeDefPlay);

extern void SgSeStop(int a0);

typedef struct SeInfo {
    short unk0; /* 0x0 */
    short unk2; /* 0x2 */
    short unk4; /* 0x4 */
    short unk6; /* 0x6 */
} SeInfo;

extern SeInfo D_005F5C70[];

void _soundSeDefStop(int a0, int a1)
{
    int ch = a0 & 0xFF;
    char *self = &D_006BF870[ch * 64];
    short h;
    SeSrcDef *src;

    h = *(short *)(self + 0x10);
    if (h < 0)
        return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)self)
        return;
    seReqRelease(ch);
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

void soundSeDefStop(int a0)
{
    _soundSeDefStop(a0, 0);
}

void soundSeDefStopNoRelease(int a0)
{
    _soundSeDefStop(a0, 1);
}

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

extern char D_005D3F30[];
extern StgPre D_005F5D50[];
extern int D_0063A458;
extern int stage_no;
extern int _soundSeDefPlay(int kind, unsigned int a1, int a2, int a3, float vol, SeEnvDef *env,
                           SeSlot **out);

/* INTERIM stand-in for soundSeEnvDefaultSet, whose ROM-slot definition sits in
   this TU's inline tail: the tail still carries asm members, so that definition
   cannot be marked `inline` yet. */
static inline void env_default_set(SeSlot *self)
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
    self->flag.bit.f30 = env->b3;
    self->flag.bit.f26 = env->b1;
    self->flag.bit.f27 = env->b2;
    self->unk1C = 0.1f;
}

void soundSeEnvPlay(void)
{
    SeSlot *slot;
    int i;

    for (i = D_005F5D50[stage_no].seEnvFirst; i < D_005F5D50[stage_no].seEnvLast; i++) {
        SeEnvDef *e = (SeEnvDef *)&D_005D3F30[i * 0x1C];
        _soundSeDefPlay(*(int *)e, 0xFFFFFFFF, 0, 0, -1.0f, (SeEnvDef *)e, &slot);
        if (slot != 0) {
            slot->unk3C = e;
            env_default_set(slot);
            if (e->b0 == 1) {
                slot->unk34 = iosMallocDebug(D_0063A458, 0x10, D_005521E8, 0x61D);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/sound/s_init", soundSeEnvNotUseClose);

void soundDataSegNextStageNotUseClose(int a0, int a1)
{
    int i;
    int closed = 0;
    int found = 0;
    char *tbl;
    /* base in the loop header, not in a declaration of its own: that is what
       keeps the walk on the entry pointer and the test against the table end */
    for (i = 0, tbl = D_006BF570; i < 768; i += 0x30) {
        char *p = tbl + i;
        if (*(int *)p != 0 && *(unsigned short *)(p + 6) == 1 && *(unsigned short *)(p + 4) == a0) {
            found = 1;
            switch (a0) {
            case 0:
                break;
            case 1:
                if (*(int *)&D_005F5EB8[a1 * 404] != *(unsigned short *)p) {
                    closed++;
                    soundDataClose(p);
                    soundBufSegFree(1, 1);
                }
                break;
            case 2:
                if (*(int *)&D_005F5EB8[a1 * 404 + 4] != *(unsigned short *)p) {
                    soundDataClose(p);
                }
                break;
            default:
                debug_assert(D_005521E8, 1741);
                __assert(D_005521E8, 1741, D_0063A660);
                break;
            }
        }
    }
    if (a0 == 1) {
        D_0063A684 = 0;
        if (found != 0 && closed == 0) {
            D_0063A684 = a0;
        }
    }
}

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

void soundBufAdpcmFree(char *self)
{
    long long mask = ~*(long long *)(self + 0x18);
    D_0063C1E0 &= mask;
    *(long long *)(self + 0x18) = 0;
}

char *soundDataAreaSearch(int *a0)
{
    return (char *)hd_search(a0);
}

char *soundDataAreaGet(int a0, int a1, int a2, int a3)
{
    SqEntry *e;
    int hi = a1 << 16;
    int key = (a0 & 0xFFFF) | hi;

    e = hd_search(&key);
    if (e == 0) {
        key = 0;
        e = hd_search(&key);
        if (e == 0) {
            debug_assert(D_005521E8, 0x14E);
            __assert(D_005521E8, 0x14E, D_0063A660);
        }
        memset(e, 0, 0x30);
        e->num = a0;
        e->bank = a1;
        e->unk6 = a3;
        e->unk4 = a2;
        e->unk28 = -1;
    }
    return (char *)e;
}

char *soundHDDataSet(int a0, int a1, int a2, int a3, int a4)
{
    int hi = a2 << 16;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = hd_search(&key);
    if (e == 0) {
        key = 0;
        e = hd_search(&key);
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

char *soundSQDataSet(int a0, int a1, int a2, int a3, int a4)
{
    int hi = a2 << 16;
    int key = (a1 & 0xFFFF) | hi;
    SqEntry *e = hd_search(&key);
    if (e == 0) {
        key = 0;
        e = hd_search(&key);
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
    e->unk10[0] = a0;
    soundDataOpenChk((char *)e);
    return (char *)e;
}

extern int _soundSeDefPlay(int kind, unsigned int a1, int a2, int a3, float vol, SeEnvDef *env,
                           SeSlot **out);
extern void sound3DParamSet(SeSlot *self);

int soundSeDefPlay(int a0, int a1, int a2, int a3)
{
    int idx = _soundSeDefPlay(a0, a1, a2, a3, -1.0f, 0, 0);
    if (idx >= 0) {
        sound3DParamSet((SeSlot *)((char *)D_006BF870 + (idx & 0xFF) * 64));
    }
    return idx;
}

int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3)
{
    int idx = ((int (*)(int, int, int, int, int, int))_soundSeDefPlay)(a0, a1, a2, a3, 0, 0);
    if (idx >= 0) {
        sound3DParamSet((SeSlot *)((char *)D_006BF870 + (idx & 0xFF) * 64));
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
                sound3DParamSet((SeSlot *)p);
            }
        }
        i++;
        p += 0x40;
    } while (i < 0x30);
}

void soundVBlank(void)
{
    int i;
    for (i = 0; i < 768; i += 0x30) {
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
    self->flag.bit.f30 = env->b3;
    self->flag.bit.f26 = env->b1;
    self->flag.bit.f27 = env->b2;
    self->unk1C = 0.1f;
}

extern const char D_00552398[];
extern char D_005D6DB0[];
extern SeSrcDef D_005DCEF4[];

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
