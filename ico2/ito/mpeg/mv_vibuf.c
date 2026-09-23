#define MV_DEFS_WANT_ALLOC

#include "common.h"
#include "mv_defs.h"
#include "memory.h"
#include <eekernel.h>
#include "typedef.h"

/* One entry of the timestamp ring: the PTS/DTS pair the demuxer read out of a
   pack header, and the run of ring bytes it applies to. */

/* The video-input ring: a run of 2048-byte sectors that the CD DMA fills and
   the MPEG demuxer drains.  Byte counts are (sector << 11) + a partial
   offset into the sector the writer is part way through. */
typedef struct ViBuf {
    char *data;      /* 0x00 ring buffer, 2048 bytes per sector */
    char *dmaTag;    /* 0x04 uncached-accel DMA tag list over the ring */
    int nSector;     /* 0x08 ring size in sectors */
    int rdSector;    /* 0x0C sector the reader is on */
    int nReady;      /* 0x10 whole sectors written but not yet read */
    int wOffset;     /* 0x14 bytes written into the sector after those */
    int size;        /* 0x18 ring size in bytes (nSector << 11) */
    int unk1C[7];    /* 0x1C */
    int bitPos;      /* 0x38 IPU bit pointer at the head of the ring */
    int unk3C;       /* 0x3C */
    int sema;        /* 0x40 */
    int running;     /* 0x44 the ring's DMA chain is armed */
    long long total; /* 0x48 bytes handed to the ring since the last reset */
    ViTs *ts;        /* 0x50 timestamp ring */
    int tsMax;       /* 0x54 timestamp ring capacity */
    int tsCount;     /* 0x58 timestamps live in it */
    int tsWr;        /* 0x5C index the next timestamp goes to */
    char created;    /* 0x60 */
} ViBuf;

static void Free();
extern int DIntr(void);

/* Write the IPU input channel's CHCR (0x1000B400) with the DMA controller
   held (D_ENABLER/D_ENABLEW bit 16) and interrupts off: listing rows 66-71,
   inlined into every caller, the shape libmpeg's setD4_CHCR has with the
   SYNC/EI pair where that one calls EIntr. Our name. */
static __inline__ void setIpuInChcr(int chcr)
{
    DIntr();
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = chcr;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    SYNC();
    EI();
}

/* RECONSTRUCTION: one quadword of the DMA tag list, written through a union
   member. The ROM reloads self->data, self->nSector and self->dmaTag after
   every tag store and does not strength-reduce the tag loop, which is what
   an alias-set-0 store gives (gcc 2.9's c_get_alias_set returns 0 for an
   access directly through a union member); a plain `unsigned long` store
   lets loop.c hoist all three. Our names. */
typedef union {
    unsigned long ul[2];
    int w[4];
} QWord;

/* One 16-byte DMA source-chain tag: the data address in the upper word, the
   tag id and quadword count below. Listing rows 80-81. Our name. */
static __inline__ void setDmaTag(char *tag, int i, int addr, int qwc, int id)
{
    ((QWord *)tag)[i].ul[0] = ((unsigned long)addr << 32) | ((unsigned long)id << 28) | qwc;
}

/* census free_buf, a file static, `static` keeps its ELF symbol local so it cannot
   collide with the ico2/ito/mpeg/mv_videodec global of the same name */
static void free_buf(int *a0)
{
    Free(a0[0]);
    Free(a0[1]);
    Free(a0[20]);
}

/* kept local: this TU's uses of viBufReset do not fit the prototype in mv_vibuf.h */
extern int viBufReset(ViBuf *self);

int viBufCreate(ViBuf *self)
{
    int sem[8];
    int data;
    int tag;
    int ts;
    /* The ring geometry is held in locals: 256 sectors of 2048 bytes, and a
       512-entry timestamp ring.  Keep them as locals - each is set here and
       read exactly once at the bottom, so local-alloc's update_equiv_regs
       moves the constant load down next to its store and all three share $v0
       (writing the literals at the store sites instead costs 17 insns). */
    int nSector = 0x100;
    int tsMax = 0x200;

    self->created = 0;

    data = alloc_zeroed(0x80000, 0x40);
    if (data == 0) {
        return -1;
    }
    tag = alloc_zeroed(0x1010, 0x40);
    if (tag == 0) {
        return -1;
    }
    ts = alloc_zeroed(0x3000, 4);
    if (ts == 0) {
        return -1;
    }

    self->data = (char *)data;
    self->dmaTag = (char *)uncached_accel_addr(tag);
    self->nSector = nSector;
    self->size = nSector << 11;

    self->ts = (ViTs *)ts;
    self->tsMax = tsMax;

    sem[2] = 1;
    sem[1] = 1;

    self->sema = CreateSema(sem);

    self->created = 1;

    viBufReset(self);

    self->total = 0;

    return 0;
}

int viBufReset(ViBuf *self)
{
    int i;

    self->rdSector = 0;
    self->nReady = 0;
    self->wOffset = 0;
    self->running = 1;

    self->tsCount = 0;
    self->tsWr = 0;
    for (i = 0; i < self->tsMax; i++) {
        self->ts[i].pts = -1;
        self->ts[i].dts = -1;
        self->ts[i].pos = 0;
        self->ts[i].len = 0;
    }

    for (i = 0; i < self->nSector; i++) {
        setDmaTag(self->dmaTag, i, phys_addr((int)(self->data + i * 2048)), 128, 3);
    }
    setDmaTag(self->dmaTag, i, phys_addr((int)self->dmaTag), 0, 2);

    *(volatile int *)0x1000B420 = 0;
    *(volatile int *)0x1000B410 = phys_addr((int)self->data);
    *(volatile int *)0x1000B430 = phys_addr((int)self->dmaTag);
    setIpuInChcr(5);

    return 1;
}

/* Hand out the region the caller may write next, as up to two runs: the one
   that ends at the top of the ring and, if it wraps, the one that starts at
   the bottom.  Two sectors are held back so the writer never overruns the
   reader. */
void viBufBeginPut(ViBuf *self, void **addr1, int *size1, void **addr2, int *size2)
{
    int keep;
    int pos;
    int room;
    int len;

    WaitSema(self->sema);

    keep = self->nReady + 2;
    pos = (self->rdSector + self->nReady) << 11;
    room = (self->nSector - keep) << 11;

    pos = (pos + self->wOffset) % self->size;
    len = room - self->wOffset;

    if (self->size - pos >= len) {
        *addr1 = self->data + pos;
        *size1 = len;

        *size2 = 0;
        *addr2 = 0;
    } else {
        *addr1 = self->data + pos;
        *size1 = self->size - pos;
        *addr2 = self->data;
        *size2 = len - (self->size - pos);
    }
    SignalSema(self->sema);
}

void viBufEndPut(int *self, int a1)
{
    WaitSema(self[0x40 / 4]);
    self[0x14 / 4] = self[0x14 / 4] + a1;
    *((long long *)(((char *)self) + 0x48)) =
        ((long long)a1) + (*((long long *)(((char *)self) + 0x48)));
    SignalSema(self[0x40 / 4]);
}

INCLUDE_ASM("asm/nonmatchings/ico2/ito/mpeg/mv_vibuf", viBufAddDMA);
INCLUDE_ASM("asm/nonmatchings/ico2/ito/mpeg/mv_vibuf", viBufStopDMA);
INCLUDE_ASM("asm/nonmatchings/ico2/ito/mpeg/mv_vibuf", viBufRestartDMA);

void viBufFlush(int *self)
{
    WaitSema(self[0x40 / 4]);
    self[0x14 / 4] = (self[0x14 / 4] + 0x7FF) / 0x800 * 0x800;
    SignalSema(self[0x40 / 4]);
}

/* Does the entry's byte position still lie inside the run of ts->len bytes
   the reader just consumed at ts->pos, measured around a size-byte ring? */
static __inline__ int tsRunCovers(int pos, ViTs *t, int size)
{
    return (pos + size - t->pos) % size < t->len;
}

/* Walk the live timestamps oldest first and charge the run described by `ts`
   against them, retiring any entry the run swallows whole. */
int viBufModifyPts(ViBuf *self, ViTs *ts)
{
    ViTs *e;
    int idx;
    int size;
    int ok;
    int n;
    int m;

    idx = (self->tsWr - self->tsCount + self->tsMax) % self->tsMax;
    size = self->nSector << 11;
    ok = 1;

    if (self->tsCount > 0) {
        for (;;) {
            e = &self->ts[idx];

            if (e->len == 0 || ts->len == 0)
                break;

            if (tsRunCovers(e->pos, ts, size)) {
                n = ts->pos + ts->len - e->pos;
                n = e->len < n ? e->len : n;

                e->pos = (e->pos + n) % size;
                e->len -= n;

                if (e->len == 0) {
                    if (e->pts >= 0) {
                        e->pts = -1;
                        e->dts = -1;
                        e->pos = 0;
                        e->len = 0;
                    }
                    m = self->tsCount - 1;
                    if (m < 0)
                        m = 0;
                    self->tsCount = m;
                }
            } else {
                ok = 0;
            }

            idx = (idx + 1) % self->tsMax;
            if (!ok)
                break;
        }
    }
    return 0;
}

/* Hand back the PTS/DTS pair covering the byte the IPU is reading right now,
   and retire it.  The read position is the DMA address the IPU_TO channel has
   reached, less what is still sitting in the IPU's input FIFO. */
int viBufGetTs(ViBuf *self, ViTs *out)
{
    unsigned int madr;
    unsigned int bp;
    int bitPos;
    int fp;
    int ifc;
    int size;
    unsigned int pos;
    int n;
    int i;
    int j;
    int wr;
    int found;
    int d;
    ViTs *e;

    madr = *(volatile unsigned int *)0x1000B410;
    bp = *(volatile unsigned int *)0x10002020;
    bitPos = self->bitPos & 0x7F;
    fp = (bp >> 16) & 3;
    ifc = (bp >> 8) & 0xF;
    madr -= (fp + ifc) << 4;

    size = self->nSector << 11;

    found = 0;

    WaitSema(self->sema);

    out->pts = -1;
    out->dts = -1;

    pos = (madr + (bitPos >> 3) + size - (unsigned int)self->data) % size;

    n = self->tsCount;
    wr = self->tsWr;

    for (i = 0; i < n && !found; i++) {
        j = (wr - n + self->tsMax + i) % self->tsMax;

        e = &self->ts[j];

        if (tsRunCovers(pos, e, size)) {
            out->pts = e->pts;
            out->dts = e->dts;
            e->pts = -1;
            e->dts = -1;

            found = 1;
            d = self->tsCount;
            if (d >= 2)
                d = 1;
            self->tsCount -= d;
        }
    }

    SignalSema(self->sema);

    return 1;
}

/* census Free, this TU's own copy of the mv_defs.h file static, `static` keeps its
   ELF symbol local so it cannot collide with the mv_videodec global of that name */
static void Free(int a0)
{
    iosFree(phys_addr(a0));
}

INCLUDE_ASM("asm/nonmatchings/ico2/ito/mpeg/mv_vibuf", viBufDelete);

int viBufCount(int *self)
{
    int ret;
    WaitSema(self[0x40 / 4]);
    ret = (self[0x10 / 4] << 11) + self[0x14 / 4];
    SignalSema(self[0x40 / 4]);
    return ret;
}

extern int viBufModifyPts(ViBuf *self, ViTs *ts);

/* Record one PTS/DTS pair against the bytes the caller just wrote.  Returns 0
   only when the timestamp ring is full. */
int viBufPutTs(ViBuf *self, ViTs *ts)
{
    int ret = 0;

    WaitSema(self->sema);

    if (self->tsCount < self->tsMax) {
        viBufModifyPts(self, ts);

        if (ts->pts >= 0 || ts->dts >= 0) {
            self->ts[self->tsWr].pts = ts->pts;
            self->ts[self->tsWr].dts = ts->dts;
            self->ts[self->tsWr].pos = ts->pos;
            self->ts[self->tsWr].len = ts->len;

            self->tsCount++;
            self->tsWr = (self->tsWr + 1) % self->tsMax;
        }
        ret = 1;
    }
    SignalSema(self->sema);

    return ret;
}
