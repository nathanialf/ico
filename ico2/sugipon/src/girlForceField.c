#include "typedef.h"
#include "sugiCommon.h"
#include "memory.h"
#include "geometryManager.h"
#include "matrixDrive.h"

/* Per-object force-field state, hung off the actor's sub-object by the caller
   (GirlForceFieldDL reads it back at sub+0x830). */
typedef struct GirlForceFieldWork {
    float radius;
    float invRadius;
    int frame;
} GirlForceFieldWork;

#include "girlForceField.h"
#include "ios.h"
#include "main.h"
#include "StageAnimation.h"

/* The TU's .data (VMA 0x4EB430, 16 B = MAIN.MAP girlForceField.o .data): the
   girl's blue, the colour boy.c's position-sync marker draws her sphere in.
   RECONSTRUCTION: nothing references it in the retail ELF or in the January
   listing, so its use (most likely a debug sphere at the field's radius) is
   compiled out.  What the bytes pin: the four words and the owner (MAIN.MAP
   and the Aug-2001 prototype both put this colour first of the two 16-byte
   members between girl.o and item.o, and retail keeps only it).  What they
   cannot pin: the name or the display it fed. */
static int forceFieldColor[4] = {64, 96, 128, 128}; /* derived name */

inline GirlForceFieldWork *InitGirlForceFieldGeo(char *self, char *param)
{
    GirlForceFieldWork *w =
        (GirlForceFieldWork *)iosMallocDebug(ios_partition_sugipon, 12, "src/girlForceField.c", 23);
    struct DObjNode *c;
    w->radius = *(float *)(param + 0x28);
    w->invRadius = 1.0f / w->radius;
    w->frame = 0;
    c = ((SubHandle *)(self + 0x15C))->sub->nodes;
    c->scale[0] = c->scale[1] = c->scale[2] = 1.0f;
    return w;
}

inline void GirlForceFieldGeo(void) {}

/* The girl's GObj, or NULL before she is spawned. */

/* The per-object-kind action record table (0x4C bytes/entry, indexed by the
   GObj's kind id at +8) and the animation-record table it selects into. */

extern OaRecA objLayout[];
extern OaRecB D_002BC6E0[];

void GirlForceFieldDL(char *self)
{
    float pos[4];
    float quat[4];
    float gpos[4];
    GirlForceFieldWork *w = GOBJ_SUB(self)->work;
    float d2;
    float ratio;

    UpdateRootMatrix(self);
    GetRootPosition(pos, self);

    if (girlGObj != 0) {
        GetRootPosition(gpos, girlGObj);
        d2 = distance_squared(gpos, pos);
        if (d2 < w->radius * w->radius) {
            ratio = 1.0f - FSqrt(d2) * w->invRadius;
            ratio = ratio < 0.0f ? 0.0f : ratio;

            GetRootQuaternion(quat, self);
            w->frame = (int)stage_PlayBgAnimationDissolve(
                D_002BC6E0[objLayout[*(int *)(self + 8)].action].baseMode, pos, quat,
                (float)w->frame, ratio);
            return;
        }
    }
    w->frame = 0;
}
