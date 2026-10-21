/* libmpeg.a(bit.o): the seven _sysbit functions of the demultiplexer's bit
 * reader.  The two DMA channel control helpers after them (setD3_CHCR,
 * setD4_CHCR) belong to libipu.o, which begins after bit.o's 4 bytes of link
 * fill; they are kept in this file. */
#include <eekernel.h>
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <eeregs.h>
#include <libipu_internal.h>

/* the bitstream reader state: the 64 bit accumulator this file shifts bits out
 * of, the ring of bytes the IPU feeds it from, and the bit position */
typedef struct {         /* field names derived */
    long long buf;       /* 0x00 */
    unsigned char *base; /* 0x08 */
    unsigned char *p;    /* 0x0C */
    unsigned int cnt;    /* 0x10 */
    long long pos;       /* 0x18 */
    unsigned char *wrap; /* 0x20 */
    unsigned char *end;  /* 0x24 */
    int size;            /* 0x28 */
} SysBit;                /* derived name */

/* Its record type is this member's own */
void _sysbitFlush(SysBit *bs, int n);

void _sysbitInit(int *bs, int base, int wrap, int size)
{
    bs[2] = base;
    bs[3] = base;
    *(long long *)bs = 0;
    bs[4] = 0;
    *(long long *)(bs + 6) = 0;
    bs[8] = wrap;
    bs[9] = wrap + size;
    bs[0xA] = size;
    _sysbitFlush((SysBit *)bs, 0);
}

int _sysbitNext(void *bs, int n)
{
    return *(unsigned long long *)bs >> (64 - n);
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

int _sysbitGet(int *self, int n)
{
    int ret = _sysbitNext(self, n);
    _sysbitFlush((SysBit *)self, n);
    return ret;
}

int _sysbitMarker(int *self)
{
    int ret = _sysbitNext(self, 1);
    _sysbitFlush((SysBit *)self, 1);
    return ret;
}

void _sysbitJump(int *bs, int bytes)
{
    long long x = *(long long *)(bs + 6) + (bytes << 3);
    int v;
    *(long long *)bs = 0;
    bs[4] = 0;
    *(long long *)(bs + 6) = x;
    v = bs[2] + (int)(x >> 3);
    bs[3] = v;
    if ((unsigned int)v >= (unsigned int)bs[9]) {
        bs[3] = v - bs[10];
    }
    _sysbitFlush((SysBit *)bs, 0);
}

int _sysbitPtr(int *bs, int bits)
{
    int v = bs[2] + (bits >> 3);
    if ((unsigned int)v >= (unsigned int)bs[9]) {
        v -= bs[10];
    }
    return v;
}

void setD3_CHCR(int chcr)
{
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D3_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & 0xFFFEFFFF;
    EIntr();
}

void setD4_CHCR(int chcr)
{
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D4_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & 0xFFFEFFFF;
    EIntr();
}
