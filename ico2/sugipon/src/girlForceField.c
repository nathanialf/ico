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

/* The 0x15C sub-object slot is a word the engine reads either as an int handle
   or as a pointer (see GOBJ_SUB in ../common/include/typedef.h). */
typedef union GObjSubSlot {
    int handle;
    void *p;
} GObjSubSlot;

#include "girlForceField.h"
#include "ios.h"

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
    float *c;
    w->radius = *(float *)(param + 0x28);
    w->invRadius = 1.0f / w->radius;
    w->frame = 0;
    c = *(float **)(((GObjSubSlot *)(self + 0x15C))->handle + 0x870);
    c[8] = c[9] = c[10] = 1.0f;
    return w;
}

inline void GirlForceFieldGeo(void) {}

/* The girl's GObj, or NULL before she is spawned. */
/* kept local: main.c's global; this TU does not include main.h */
extern void *girlGObj;

/* The per-object-kind action record table (0x4C bytes/entry, indexed by the
   GObj's kind id at +8) and the animation-record table it selects into. */

extern OaRecA objLayout[];
extern OaRecB D_002BC6E0[];
/* kept local: float (void *, float *, float *, float, float) here, float (int, void *, void *, float, float) in StageAnimation.h */
extern float stage_PlayBgAnimationDissolve(void *anim, float *pos, float *quat, float frame,
                                           float ratio);

void GirlForceFieldDL(char *self)
{
    float pos[4];
    float quat[4];
    float gpos[4];
    GirlForceFieldWork *w = *(GirlForceFieldWork **)((char *)GOBJ_SUB(self) + 0x830);
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
            w->frame =
                (int)stage_PlayBgAnimationDissolve(D_002BC6E0[objLayout[*(int *)(self + 8)].x34].x0,
                                                   pos, quat, (float)w->frame, ratio);
            return;
        }
    }
    w->frame = 0;
}
