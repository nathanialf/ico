/* libgraph.a member graph015.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdio.h>

/* R5900 opcodes with no C spelling.  This member's uses stand for a
   Sony-internal header this tree cannot name: MAIN.MAP attests archives and
   their members, never a header, so the definition is kept per member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct {
    unsigned long long nloop : 15;
    unsigned long long eop : 1;
    unsigned long long pad1 : 30;
    unsigned long long pre : 1;
    unsigned long long prim : 11;
    unsigned long long flg : 2;
    unsigned long long nreg : 4;
    unsigned long long regs0 : 4;
    unsigned long long regs1 : 60;
} GifTag;

typedef struct {
    GifTag gif;           /* 0x00 */
    long long bitbltbuf;  /* 0x10 */
    long long abitbltbuf; /* 0x18 */
    long long trxpos;     /* 0x20 */
    long long atrxpos;    /* 0x28 */
    long long trxreg;     /* 0x30 */
    long long atrxreg;    /* 0x38 */
    long long trxdir;     /* 0x40 */
    long long atrxdir;    /* 0x48 */
    GifTag gif2;          /* 0x50 */
} LoadImage;

int sceGsSetDefLoadImage(LoadImage *di, short dbp, short dbw, short dpsm, short dsax, short dsay,
                         short rrw, short rrh)
{
    int size = 0;

    switch (dpsm) {
    case 0:
    case 48:
        size = (rrw * rrh) >> 2;
        break;
    case 1:
    case 49:
        size = (rrw * rrh * 3) >> 4;
        break;
    case 2:
    case 10:
    case 50:
    case 58:
        size = (rrw * rrh) >> 3;
        break;
    case 19:
    case 27:
        size = (rrw * rrh) >> 4;
        break;
    case 20:
    case 36:
    case 44:
        size = (rrw * rrh) >> 5;
        break;
    }
    if (size > 0x7FFF) {
        printf("sceGsSetDefLoadImage: too big size\r\n");
        return 0;
    }
    *(u128 *)&di->gif = 0;
    di->gif.nloop = 4;
    di->gif.nreg = 1;
    di->gif.regs0 = 0xE;
    di->bitbltbuf = ((long long)dbp << 32) | ((long long)dbw << 48) | ((long long)dpsm << 56);
    di->abitbltbuf = 0x50;
    di->trxpos = ((long long)dsax << 32) | ((long long)dsay << 48);
    di->atrxpos = 0x51;
    di->trxreg = (long long)rrw | ((long long)rrh << 32);
    di->atrxreg = 0x52;
    di->trxdir = 0;
    di->atrxdir = 0x53;
    *(u128 *)&di->gif2 = 0;
    di->gif2.nloop = size;
    di->gif2.eop = 1;
    di->gif2.flg = 2;
    SYNC();
    return 6;
}
