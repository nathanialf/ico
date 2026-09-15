/* libgraph.a member graph006.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef long long s_long128;

/* Eight (register-address, data) pairs: FRAME_1, ZBUF_1, XYOFFSET_1, SCISSOR_1,
   PRMODECONT, COLCLAMP, DTHE, TEST_1.  Same pair convention as graph007. */
typedef struct {
    s_long128 frame;           /* 0x00 */
    s_long128 frame_addr;      /* 0x08 */
    s_long128 zbuf;            /* 0x10 */
    s_long128 zbuf_addr;       /* 0x18 */
    s_long128 xyoffset;        /* 0x20 */
    s_long128 xyoffset_addr;   /* 0x28 */
    s_long128 scissor;         /* 0x30 */
    s_long128 scissor_addr;    /* 0x38 */
    s_long128 prmodecont;      /* 0x40 */
    s_long128 prmodecont_addr; /* 0x48 */
    s_long128 colclamp;        /* 0x50 */
    s_long128 colclamp_addr;   /* 0x58 */
    s_long128 dthe;            /* 0x60 */
    s_long128 dthe_addr;       /* 0x68 */
    s_long128 test;            /* 0x70 */
    s_long128 test_addr;       /* 0x78 */
} sceGsDrawEnv;

extern int sceGszbufaddr(short psm, short w, short h);

int sceGsSetDefDrawEnv(sceGsDrawEnv *env, short psm, short w, short h, short ztst, short zpsm)
{
    env->frame_addr = 0x4C;
    env->frame = ((s_long128)(((w + 0x3F) >> 6) & 0x3F) << 16) | ((s_long128)(psm & 0xF) << 24);
    env->zbuf_addr = 0x4E;
    if (ztst == 0) {
        env->zbuf = (s_long128)(short)sceGszbufaddr(psm, w, h) | ((s_long128)(zpsm & 0xF) << 24) |
                    ((s_long128)1 << 32);
    } else {
        env->zbuf = (s_long128)(short)sceGszbufaddr(psm, w, h) | ((s_long128)(zpsm & 0xF) << 24);
    }
    env->xyoffset_addr = 0x18;
    env->xyoffset =
        (((s_long128)0x800 - (short)(w >> 1)) << 4) | (((s_long128)0x800 - (short)(h >> 1)) << 36);
    env->scissor_addr = 0x40;
    env->scissor = ((s_long128)(w - 1) << 16) | ((s_long128)(h - 1) << 48);
    env->prmodecont_addr = 0x1A;
    env->prmodecont |= 1;
    env->colclamp_addr = 0x46;
    env->colclamp |= 1;
    env->dthe_addr = 0x45;
    if (psm & 2) {
        env->dthe |= 1;
    } else {
        env->dthe &= ~1;
    }
    env->test_addr = 0x47;
    if (ztst) {
        env->test = ((s_long128)(ztst & 3) << 17) | 0x00010000;
    } else {
        env->test = 0x00030000;
    }
    __asm__ __volatile__("sync");
    return 8;
}
