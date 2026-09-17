#include "common.h"
#include "MicroCode.h"
#include "DisplayList.h"
#include "typedef.h"

/* The five VU1 microprograms this table hands to the DMA; MAIN.MAP pulls
   cluster.o, mesh.o, normal_c.o, normal_l.o and particle.o into the link
   for exactly these names (map lines 42-46). */
extern void ClusterMicroProgram();
extern void MeshMicroProgram();
extern void NormalCMicroProgram();
extern void NormalLMicroProgram();
extern void ParticleMicroProgram();

/* .data, the whole of MicroCode.o's run (MAIN.MAP line 5804 names it at the
   run base and sizes the member 0x1C).  Indexed by the microprogram id the
   mesh and shadow paths pass around; slots 0 and 6 are unused. */
int MicroCodeAddress[7] = {
    0,
    (int)NormalCMicroProgram,
    (int)NormalLMicroProgram,
    (int)ClusterMicroProgram,
    (int)MeshMicroProgram,
    (int)ParticleMicroProgram,
    0,
};

/* .sbss and .bss, owned by MicroCode.o and reached only from this file
   (MAIN.MAP names no symbol in either run): the count of microprogram uploads
   this frame, and the program currently resident in each of the 13 VU1
   priority banks. */
static int mcUploadCount;

static int mcResident[16];

/* The display-list packet builder state and one 64-bit packet slot; same
   objects src/GifPacket.c builds its packets in. */

extern GifDpk D_004EE6F0;

void mc_setBaseOffset(int base, int pri)
{
    char *c;
    char *q;

    c = (char *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.dma = c;
    D_004EE6F0.end = 0;
    D_004EE6F0.tail = c;
    ((GifPkWord *)c)->d = 0x10000000;
    D_004EE6F0.ptr = (unsigned long long *)(c + 8);

    switch (base) {
    case 1:
    case 2: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 3: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 4: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x020001F8;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    case 5: {
        char *p = (char *)D_004EE6F0.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        D_004EE6F0.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x0200016A;
        D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    } break;
    }

    q = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = q;
    ((GifPkWord *)q)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0x10);
    dl_SetDLPriority(pri);
    dl_OpenDma(5, (int)D_004EE6F0.dma, 0);
    dl_CloseDma();
}

inline void mc_TransMicroCode(int a0, int a1)
{
    int *q = &MicroCodeAddress[a0];
    int i;
    for (i = 0; i < 13; i++) {
        if ((a1 >> i) & 1) {
            if (a0 != mcResident[i]) {
                mcUploadCount++;
                mc_setBaseOffset(a0, i);
                dl_SetDLPriority(i);
                dl_OpenDma(5, *q, 0);
                dl_CloseDma();
                mcResident[i] = a0;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/MicroCode", mc_SetMicroCode);

inline void mc_Init(void)
{
    int *p = mcResident;
    int i = 0xC;
    mcUploadCount = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

inline void mc_Reset(void)
{
    int *p = mcResident;
    int i = 0xC;
    mcUploadCount = 0;
    p += 0xC;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}
