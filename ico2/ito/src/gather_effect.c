#include "particleEffect.h"
#include <libvu0.h>
#include "Matrix.h"
#include <math.h>
#include "gather_effect.h"
#include "debug.h"
#include "include_asm.h"

INCLUDE_ASM(GatherEffect_SetGoal);

INCLUDE_ASM(GatherEffect_Proc);

inline int GatherEffect_InqEnd(int id)
{
    int acc = 0;
    if (id >= 0) {
        PEGeo *geo = GetParticleEffectData(id);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->n;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->parts[i].alive;
            }
        }
    }
    return acc == 0;
}

INCLUDE_ASM(GatherEffect_Set);
