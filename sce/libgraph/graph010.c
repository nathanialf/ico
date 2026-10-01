/* libgraph.a member graph010.o */
#include <libgraph.h>

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
