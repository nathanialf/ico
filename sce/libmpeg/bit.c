/* Vendor SCE library member: libmpeg.a(bit.o).  MAIN.MAP's member size (0x20C)
 * tiles the retail run, VMA 0x272058..0x272264, the seven _sysbit functions of
 * the demultiplexer's bit reader.  The two DMA channel control helpers after
 * them (setD3_CHCR, setD4_CHCR, VMA 0x272268..0x272338) are libipu.o's own
 * functions in the listing, where libipu.o begins after bit.o's 4 bytes of
 * link fill; they stay in this file until libipu's row is moved to take them. */
#include <eekernel.h>
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <eeregs.h>
#include <libipu_internal.h>

/* the bitstream reader state: the 64 bit accumulator this file shifts bits out
 * of, the ring of bytes the IPU feeds it from, and the bit position */
typedef struct {
    long long buf;       /* 0x00 */
    unsigned char *base; /* 0x08 */
    unsigned char *p;    /* 0x0C */
    unsigned int cnt;    /* 0x10 */
    long long pos;       /* 0x18 */
    unsigned char *wrap; /* 0x20 */
    unsigned char *end;  /* 0x24 */
    int size;            /* 0x28 */
} SysBit;

/* kept local: its record type is this member's own */
extern void _sysbitFlush(SysBit *bs, int n);

void _sysbitInit(int *a0, int a1, int a2, int a3)
{
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    _sysbitFlush((SysBit *)a0, 0);
}

int _sysbitNext(void *a0, int a1)
{
    return *(unsigned long long *)a0 >> (64 - a1);
}

void _sysbitFlush(SysBit *bs, int n)
{
    bs->buf <<= n;
    bs->cnt -= n;
    while (bs->cnt < 57) {
        bs->buf |= (long long)*bs->p++ << (56 - bs->cnt);
        if (bs->p >= bs->end) {
            bs->p = bs->wrap;
        }
        bs->cnt += 8;
    }
    bs->pos += n;
}

int _sysbitGet(int *self, int a1)
{
    int ret = _sysbitNext(self, a1);
    _sysbitFlush((SysBit *)self, a1);
    return ret;
}

int _sysbitMarker(int *self)
{
    int ret = _sysbitNext(self, 1);
    _sysbitFlush((SysBit *)self, 1);
    return ret;
}

void _sysbitJump(int *a0, int a1)
{
    long long x = *(long long *)(a0 + 6) + (a1 << 3);
    int v;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = x;
    v = a0[2] + (int)(x >> 3);
    a0[3] = v;
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        a0[3] = v - a0[10];
    }
    _sysbitFlush((SysBit *)a0, 0);
}

int _sysbitPtr(int *a0, int a1)
{
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

void setD3_CHCR(int *a0)
{
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D3_CHCR = (int)a0;
    *D_ENABLEW = *D_ENABLER & 0xFFFEFFFF;
    EIntr();
}

void setD4_CHCR(int *a0)
{
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D4_CHCR = (int)a0;
    *D_ENABLEW = *D_ENABLER & 0xFFFEFFFF;
    EIntr();
}
