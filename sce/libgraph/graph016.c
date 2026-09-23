/* libgraph.a member graph016.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

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
    unsigned int h0;      /* 0x0 */
    unsigned int h1;      /* 0x4 */
    unsigned int h2;      /* 0x8 */
    unsigned int h3;      /* 0xC */
    GifTag gif;           /* 0x10 */
    long long bitbltbuf;  /* 0x20 */
    long long abitbltbuf; /* 0x28 */
    long long trxpos;     /* 0x30 */
    long long atrxpos;    /* 0x38 */
    long long trxreg;     /* 0x40 */
    long long atrxreg;    /* 0x48 */
    long long finish;     /* 0x50 */
    long long afinish;    /* 0x58 */
    long long trxdir;     /* 0x60 */
    long long atrxdir;    /* 0x68 */
} StoreImage;

int sceGsSetDefStoreImage(StoreImage *di, short sbp, short sbw, short spsm, short ssax, short ssay,
                          short rrw, short rrh)
{
    di->h0 = 0;
    di->h1 = 0x06008000;
    di->h2 = 0x13000000;
    di->h3 = 0x50000006;
    *(u128 *)&di->gif = 0;
    di->gif.nloop = 5;
    di->gif.eop = 1;
    di->gif.nreg = 1;
    di->gif.regs0 = 0xE;
    di->bitbltbuf = (long long)sbp | ((long long)sbw << 16) | ((long long)spsm << 24);
    di->abitbltbuf = 0x50;
    di->trxpos = (long long)ssax | ((long long)ssay << 16);
    di->atrxpos = 0x51;
    di->trxreg = (long long)rrw | ((long long)rrh << 32);
    di->atrxreg = 0x52;
    di->finish = 0;
    di->afinish = 0x61;
    di->trxdir = 1;
    di->atrxdir = 0x53;
    SYNC();
    return 7;
}
