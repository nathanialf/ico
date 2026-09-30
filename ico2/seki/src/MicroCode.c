#include "MicroCode.h"
#include "DisplayList.h"
#include "typedef.h"
#include "debug.h"

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

/* The DEBUG build's trace of the microcode residency on the mode 1, a1 == 0
   path (names ours), switched by seki's debug-display bit; retail builds the
   switch as 0, jimaku.c's form.  It takes no argument because it reads the
   module's own state, which is also what leaves its retail body empty.  WHAT
   THE BYTES PIN: the listing's rows 212-220 inside that arm carry no code; the
   ROM's 0x30 frame keeps sixteen bytes of outgoing argument space below its
   two saves, the trace of a call with nine or ten integer arguments that is
   expanded and then deleted (inlining carries its argument space into
   mc_SetMicroCode; a declared local would cost the `j dl_CloseDma` sibling
   call); no string reaches MicroCode.o's .rodata (the jump table fills it);
   and the empty body's lone (use (const_int 0)) keeps jump2 from
   cross-jumping this arm's `code = 20` into mode 2's (the ROM keeps both,
   rows 221 and 258).  Measured: the block written in the arm itself, or a
   helper that takes the selection's arguments, has insns at save time, no
   use, and the arms merge.  WHAT THEY CANNOT PIN: the callee and what it
   printed; mcTracePut and its arguments are ours. */
#ifdef DEBUG
#define MC_DEBUG_TRACE (debug_font_flag & 1)
#else
#define MC_DEBUG_TRACE 0
#endif

extern void mcTracePut(int uploads, int r0, int r1, int r2, int r3, int r4, int r5, int r6, int r7);

static inline void mcTrace(void)
{
    if (MC_DEBUG_TRACE) {
        mcTracePut(mcUploadCount, mcResident[0], mcResident[1], mcResident[2], mcResident[3],
                   mcResident[4], mcResident[5], mcResident[6], mcResident[7]);
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
                    if (debug_specular_flag != 1) {
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
                    if (debug_specular_flag != 1) {
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
            if (debug_specular_flag == 0) {
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
