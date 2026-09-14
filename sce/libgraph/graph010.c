/* libgraph.a member graph010.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern int sceGsPutDispEnv();
extern int sceGsPutDrawEnv();

int sceGsSwapDBuff(void *a0, int a1)
{
    int s0 = a1 & 1;
    int ret;
    sceGsPutDispEnv((char *)a0 + s0 * 0x28);
    if (!s0)
        goto zero_path;
    ret = sceGsPutDrawEnv((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = sceGsPutDrawEnv((char *)a0 + 0x50);
done:
    return ret;
}
