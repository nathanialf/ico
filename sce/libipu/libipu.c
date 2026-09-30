/* Vendor SCE library member: libipu.a(libipu.o).  MAIN.MAP's member spans tile this
 * run at retail addresses (0xE8, 0x150, 0x68), VMA 0x272338..0x2725D8, 3 functions. */
#include <eeregs.h>

extern void setD3_CHCR(int *a0);
extern void setD4_CHCR(int *a0);

void sceIpuStopDMA(void *a0)
{
    setD4_CHCR((int *)1);
    ((int *)a0)[0] = *D4_MADR;
    ((int *)a0)[1] = *D4_TADR;
    ((int *)a0)[2] = *D4_QWC;
    ((int *)a0)[3] = *D4_CHCR;
    while (*IPU_CTRL & 0xF0) {}
    setD3_CHCR((int *)0);
    ((int *)a0)[4] = *D3_MADR;
    ((int *)a0)[5] = *D3_QWC;
    ((int *)a0)[6] = *D3_CHCR;
    ((int *)a0)[7] = *IPU_BP;
    ((int *)a0)[8] = *IPU_CTRL;
}

void sceIpuRestartDMA(void *a0)
{
    int *p = (int *)a0;
    unsigned int bp = p[7];
    int cmd = bp & 0x7F;
    int n = ((bp >> 16) & 3) + ((bp >> 8) & 0xF);
    int madr = p[0] - (n << 4);
    int qwc = p[2] + n;

    if (p[4] != 0 && p[5] != 0) {
        *D3_MADR = p[4];
        *D3_QWC = p[5];
        setD3_CHCR((int *)(p[6] | 0x100));
    }
    while (*IPU_CTRL < 0) {}
    *IPU_CMD = cmd;
    while (*IPU_CTRL < 0) {}
    if (madr != 0 && qwc != 0) {
        *D4_MADR = madr;
        *D4_TADR = p[1];
        *D4_QWC = qwc;
        setD4_CHCR((int *)(p[3] | 0x100));
    }
}

int sceIpuSync(int a0)
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
