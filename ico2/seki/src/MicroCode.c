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

extern GifDpk PacketBufferStruct;

void mc_setBaseOffset(int base, int pri)
{
    char *c;
    char *q;

    c = (char *)PacketBufferStruct.ptr;
    PacketBufferStruct.gif = 0;
    PacketBufferStruct.dma = c;
    PacketBufferStruct.end = 0;
    PacketBufferStruct.tail = c;
    ((GifPkWord *)c)->d = 0x10000000;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 8);

    switch (base) {
    case 1:
    case 2: {
        char *p = (char *)PacketBufferStruct.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        PacketBufferStruct.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        PacketBufferStruct.ptr = (unsigned long long *)(p + 4);
    } break;
    case 3: {
        char *p = (char *)PacketBufferStruct.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000100;
        p += 4;
        PacketBufferStruct.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x02000180;
        PacketBufferStruct.ptr = (unsigned long long *)(p + 4);
    } break;
    case 4: {
        char *p = (char *)PacketBufferStruct.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        PacketBufferStruct.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x020001F8;
        PacketBufferStruct.ptr = (unsigned long long *)(p + 4);
    } break;
    case 5: {
        char *p = (char *)PacketBufferStruct.ptr;

        ((GifPkWord *)p)->w[0] = 0x03000010;
        p += 4;
        PacketBufferStruct.ptr = (unsigned long long *)p;
        ((GifPkWord *)p)->w[0] = 0x0200016A;
        PacketBufferStruct.ptr = (unsigned long long *)(p + 4);
    } break;
    }

    q = (char *)PacketBufferStruct.ptr;
    PacketBufferStruct.tail = q;
    ((GifPkWord *)q)->d = 0x60000000;
    PacketBufferStruct.ptr = (unsigned long long *)(q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)(q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)(q + 0x10);
    dl_SetDLPriority(pri);
    dl_OpenDma(5, (int)PacketBufferStruct.dma, 0);
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

extern int D_0063B1AC;
/* A compiled-out trace (our name) in the empty-hook form other TUs carry
   (cdvd.c's stDebugPrint, main.c's mainDebugBar).  WHAT THE BYTES PIN: a
   call with nine or more integer arguments that emits nothing, since the
   ROM's 0x30 frame keeps sixteen bytes of outgoing argument space below its
   two saves (a declared local would cost the `j dl_CloseDma` sibling call),
   inlining carries the callee's argument space into mc_SetMicroCode, and no
   string reaches MicroCode.o's .rodata (the jump table fills it); and a
   zero-code insn left by the inlined body in the mode 1, a1 == 0 arm, which
   keeps jump2 from cross-jumping that arm's `code = 20` into mode 2's (the
   ROM keeps both, rows 221 and 258; the listing's rows 212-220 are
   code-free).  WHAT THEY CANNOT PIN: the callee, its arguments, or how the
   developers switched it off; mcTracePut and its argument list are ours. */
extern void mcTracePut(int mode, int a1, int a2, int a3, int pri, int x, int y, int w, int h);

static inline void mcTrace(void)
{
    if (0) {
        mcTracePut(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

/* MicroCode.c:166-280 in the listing: every level of the selection is a
   switch except the a1 tests, and the three conditional codes are if/else
   pairs (the else value on its own row, the conditional move on the next). */
void mc_SetMicroCode(int mode, int a1, int a2, int a3, int pri)
{
    int code = 0xFFFF;
    char *c;

    switch (mode) {
    case 0:
        switch (a1) {
        case 0:
            switch (a3) {
            case -1:
                code = 34;
                break;
            case 2:
                code = 36;
                break;
            default:
                code = 32;
                break;
            }
            break;
        case 3:
            code = 38;
            break;
        default:
            switch (a2) {
            case 0:
                if (a3 == 2) {
                    code = 36;
                } else {
                    code = 32;
                }
                break;
            case 1:
                code = 34;
                break;
            case 2:
                code = 38;
                break;
            }
            break;
        }
        break;
    case 1:
        if (a1 == 0) {
            mcTrace();
            code = 20;
        } else {
            if (a3 == -1) {
                switch (a2) {
                case 0:
                    if (D_0063B1AC != 1) {
                        code = 20;
                    } else {
                        code = 24;
                    }
                    break;
                case 1:
                    code = 22;
                    break;
                }
            } else {
                switch (a2) {
                case 0:
                    if (D_0063B1AC != 1) {
                        code = 20;
                    } else {
                        code = 24;
                    }
                    break;
                case 1:
                    code = 22;
                    break;
                }
            }
        }
        break;
    case 2:
        if (a1 == 0) {
            code = 20;
        } else {
            if (D_0063B1AC == 0) {
                code = 22;
            } else {
                code = 24;
            }
        }
        break;
    case 3:
        code = 18;
        break;
    }
    if (code == 0xFFFF) {
        return;
    }

    c = (char *)PacketBufferStruct.ptr;
    PacketBufferStruct.gif = 0;
    PacketBufferStruct.tail = c;
    PacketBufferStruct.dma = c;
    PacketBufferStruct.end = 0;
    ((GifPkWord *)c)->d = 0x10000000;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 8);
    ((GifPkWord *)(c + 8))->w[0] = code | 0x15000000;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 0xC);
    ((GifPkWord *)(c + 0xC))->w[0] = 0x13000000;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 0x10);
    PacketBufferStruct.tail = c + 0x10;
    ((GifPkWord *)(c + 0x10))->d = 0x60000000;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 0x18);
    ((GifPkWord *)(c + 0x18))->w[0] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 0x1C);
    ((GifPkWord *)(c + 0x18))->w[1] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)(c + 0x20);
    dl_SetDLPriority(pri);
    dl_OpenDma(5, (int)PacketBufferStruct.dma, 0);
    dl_CloseDma();
}

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
