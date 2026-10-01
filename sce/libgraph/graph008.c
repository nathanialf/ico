/* libgraph.a member graph008.o */
#include <stdio.h>
#include <libgraph.h>
#include <eeregs.h>

int sceGsPutDrawEnv(void *a0)
{
    unsigned int count;
    int qwc;

    count = 0;
    while (*D2_CHCR & 0x100) {
        if (count++ > 0x1000000) {
            printf("sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n");
            return -1;
        }
    }
    qwc = *(long long *)a0 & 0x7FFF;
    *D2_QWC = qwc + 1;
    if (((unsigned int)a0 & 0x70000000) == 0x70000000)
        *D2_MADR = ((unsigned int)a0 & 0xFFFFFFF) | 0x80000000;
    else
        *D2_MADR = (unsigned int)a0 & 0xFFFFFFF;
    *D2_CHCR = 0x101;
    return 0;
}
