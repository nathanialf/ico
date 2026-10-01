/* libipu.a(libipu.o): the IPU DMA stop and restart handlers and sceIpuSync. */
#include <eeregs.h>
#include <libipu.h>
#include <libipu_internal.h>

void sceIpuStopDMA(sceIpuDmaEnv *env)
{
    setD4_CHCR(1);
    env->d4madr = *D4_MADR;
    env->d4tadr = *D4_TADR;
    env->d4qwc = *D4_QWC;
    env->d4chcr = *D4_CHCR;
    while (*IPU_CTRL & 0xF0) {}
    setD3_CHCR(0);
    env->d3madr = *D3_MADR;
    env->d3qwc = *D3_QWC;
    env->d3chcr = *D3_CHCR;
    env->ipubp = *IPU_BP;
    env->ipuctrl = *IPU_CTRL;
}

void sceIpuRestartDMA(sceIpuDmaEnv *env)
{
    unsigned int bp = env->ipubp;
    int cmd = bp & 0x7F;
    int n = ((bp >> 16) & 3) + ((bp >> 8) & 0xF);
    int madr = env->d4madr - (n << 4);
    int qwc = env->d4qwc + n;

    if (env->d3madr != 0 && env->d3qwc != 0) {
        *D3_MADR = env->d3madr;
        *D3_QWC = env->d3qwc;
        setD3_CHCR(env->d3chcr | 0x100);
    }
    while (*IPU_CTRL < 0) {}
    *IPU_CMD = cmd;
    while (*IPU_CTRL < 0) {}
    if (madr != 0 && qwc != 0) {
        *D4_MADR = madr;
        *D4_TADR = env->d4tadr;
        *D4_QWC = qwc;
        setD4_CHCR(env->d4chcr | 0x100);
    }
}

int sceIpuSync(int a0, unsigned short timeout)
{
    int r = 0;
    switch (a0) {
    case 0:
        while (*IPU_CTRL < 0) {}
        r = 0;
        break;
    case 1:
        r = (unsigned)*IPU_CTRL >> 31;
        break;
    }
    return r;
}
