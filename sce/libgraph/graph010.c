/* libgraph.a member graph010.o */
#include <libgraph.h>

int sceGsSwapDBuff(void *db, int id)
{
    int s0 = id & 1;
    int ret;
    sceGsPutDispEnv((char *)db + s0 * 0x28);
    if (!s0)
        goto zero_path;
    ret = sceGsPutDrawEnv((char *)db + 0x140);
    goto done;
zero_path:
    ret = sceGsPutDrawEnv((char *)db + 0x50);
done:
    return ret;
}
