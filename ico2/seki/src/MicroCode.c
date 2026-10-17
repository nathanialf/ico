#include "MicroCode.h"
#include "DisplayList.h"
#include "typedef.h"
#include "debug.h"
#include "DmaPacket.h"
#include "include_asm.h"

/* The five VU1 microprograms this table hands to the DMA, from cluster.o,
   mesh.o, normal_c.o, normal_l.o and particle.o. */
extern void ClusterMicroProgram();
extern void MeshMicroProgram();
extern void NormalCMicroProgram();
extern void NormalLMicroProgram();
extern void ParticleMicroProgram();

/* Indexed by the microprogram id the mesh and shadow paths pass around;
   slots 0 and 6 are unused. */
int MicroCodeAddress[7] = {
    0,
    (int)NormalCMicroProgram,
    (int)NormalLMicroProgram,
    (int)ClusterMicroProgram,
    (int)MeshMicroProgram,
    (int)ParticleMicroProgram,
    0,
};

/* The count of microprogram uploads
   this frame, and the program currently resident in each of the 13 VU1
   priority banks. */
static int mcUploadCount; /* derived name */

static int mcResident[16]; /* derived name */

/* The display-list packet builder state and one 64-bit packet slot; same
   objects src/GifPacket.c builds its packets in. */

static void mc_setBaseOffset(int base, int pri);

INCLUDE_ASM(mc_setBaseOffset);

inline void mc_TransMicroCode(int id, int mask)
{
    int *q = &MicroCodeAddress[id];
    int i;
    for (i = 0; i < 13; i++) {
        if ((mask >> i) & 1) {
            if (id != mcResident[i]) {
                mcUploadCount++;
                mc_setBaseOffset(id, i);
                dl_SetDLPriority(i);
                dl_OpenDma(5, (void *)*q, 0);
                dl_CloseDma();
                mcResident[i] = id;
            }
        }
    }
}

/* The DEBUG build's trace of the microcode residency on the mode 1, light == 0
   path, switched by seki's debug-display bit; retail builds the switch as 0,
   jimaku.c's form.  It takes no argument: it reads the module's own state. */
#ifdef DEBUG
#define MC_DEBUG_TRACE (debug_font_flag & 1) /* derived name */
#else
#define MC_DEBUG_TRACE 0 /* derived name */
#endif

extern void mcTracePut(int uploads, int r0, int r1, int r2, int r3, int r4, int r5, int r6, int r7);

static inline void mcTrace(void) /* derived name */
{
    if (MC_DEBUG_TRACE) {
        mcTracePut(mcUploadCount, mcResident[0], mcResident[1], mcResident[2], mcResident[3],
                   mcResident[4], mcResident[5], mcResident[6], mcResident[7]);
    }
}

/* Every level of the selection is a switch except the light tests, and the
   three conditional codes are if/else pairs. */
INCLUDE_ASM(mc_SetMicroCode);

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
