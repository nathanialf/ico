/* libgraph.a member graph007.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef unsigned long long u_long128;

/* The (data, address) register pair list sceGsSetDefClear fills: six GS
   register writes, TEST_1 / PRIM / RGBAQ / XYZ2 / XYZ2 / TEST_1. */
typedef struct {
    u_long128 test_1;       /* 0x00 */
    u_long128 test_1_addr;  /* 0x08 */
    u_long128 prim;         /* 0x10 */
    u_long128 prim_addr;    /* 0x18 */
    u_long128 rgbaq;        /* 0x20 */
    u_long128 rgbaq_addr;   /* 0x28 */
    u_long128 xyz2_0;       /* 0x30 */
    u_long128 xyz2_0_addr;  /* 0x38 */
    u_long128 xyz2_1;       /* 0x40 */
    u_long128 xyz2_1_addr;  /* 0x48 */
    u_long128 test_1r;      /* 0x50 */
    u_long128 test_1r_addr; /* 0x58 */
} sceGsClear;

int sceGsSetDefClear(sceGsClear *cl, short ztst, short x, short y, short w, short h,
                     unsigned char r, unsigned char g, unsigned char b, unsigned char a,
                     unsigned int z)
{
    cl->test_1_addr = 0x47;
    cl->test_1 = 0x00030000;
    cl->prim_addr = 0;
    cl->prim = 6;
    cl->rgbaq_addr = 1;
    cl->rgbaq = (u_long128)r | ((u_long128)g << 8) | ((u_long128)b << 16) | ((u_long128)a << 24) |
                ((u_long128)0x3F800000 << 32);
    cl->xyz2_0_addr = 5;
    cl->xyz2_0 = (u_long128)(x << 4) | ((u_long128)(y << 4) << 16) | ((u_long128)z << 32);
    cl->xyz2_1_addr = 5;
    cl->xyz2_1 =
        (u_long128)((x + w) << 4) | ((u_long128)((y + h) << 4) << 16) | ((u_long128)z << 32);
    cl->test_1r_addr = 0x47;
    if (ztst) {
        cl->test_1r = ((u_long128)(ztst & 3) << 17) | 0x00010000;
    } else {
        cl->test_1r = 0x00030000;
    }
    __asm__ __volatile__("sync");
    return 6;
}
