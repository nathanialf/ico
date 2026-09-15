/* libgraph.a member graph013.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef long long s_long128;

/* Four (register-address, data) pairs: TEXFLUSH-or-NOP, TEX1_1, TEX0_1, CLAMP_1. */
typedef struct {
    s_long128 texflush;      /* 0x00 */
    s_long128 texflush_addr; /* 0x08 */
    s_long128 tex1;          /* 0x10 */
    s_long128 tex1_addr;     /* 0x18 */
    s_long128 tex0;          /* 0x20 */
    s_long128 tex0_addr;     /* 0x28 */
    s_long128 clamp;         /* 0x30 */
    s_long128 clamp_addr;    /* 0x38 */
} sceGsTexEnv;

int sceGsSetDefTexEnv(sceGsTexEnv *env, short flush, short tbp, short tbw, short psm, short tw,
                      short th, short tfx, short cbp, short cpsm, short cld, short flt)
{
    if (flush) {
        env->texflush_addr = 0x3F;
    } else {
        env->texflush_addr = 0x7F;
    }
    env->texflush = 0;
    env->tex0_addr = 6;
    env->tex0 = (s_long128)tbp | ((s_long128)tbw << 14) | ((s_long128)psm << 20) |
                ((s_long128)tw << 26) | ((s_long128)th << 30) | ((s_long128)1 << 34) |
                ((s_long128)tfx << 35) | ((s_long128)cbp << 37) | ((s_long128)cpsm << 51) |
                ((s_long128)cld << 61);
    env->tex1_addr = 0x14;
    env->tex1 = ((s_long128)(flt & 1) << 5) | ((s_long128)flt << 6);
    env->clamp_addr = 8;
    env->clamp = 5;
    __asm__ __volatile__("sync");
    return 4;
}
