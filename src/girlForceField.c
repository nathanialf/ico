#include "common.h"
#include "ico/types.h"
#include "vu0.h"
#include "sugiCommon.h"

extern char D_0061F9E0[]; /* "...sugipon/src/girlForceField.c": this TU's __FILE__ */
extern int D_0063A438;    /* game heap handle */
extern void *iosMallocDebug(int heap, int size, char *file, int line);

/* Per-object force-field state, hung off the actor's sub-object by the caller
   (GirlForceFieldDL reads it back at sub+0x830). */
typedef struct GirlForceFieldWork {
    float radius;
    float invRadius;
    int frame;
} GirlForceFieldWork;

/* The 0x15C sub-object slot is a word the engine reads either as an int handle
   or as a pointer (see include/ico/types.h GOBJ_SUB). */
typedef union GObjSubSlot {
    int handle;
    void *p;
} GObjSubSlot;

/* prototypes: their order is the inline tail's emission order */
GirlForceFieldWork *InitGirlForceFieldGeo(char *self, char *param);
void GirlForceFieldGeo(void);

inline GirlForceFieldWork *InitGirlForceFieldGeo(char *self, char *param)
{
    GirlForceFieldWork *w = (GirlForceFieldWork *)iosMallocDebug(D_0063A438, 12, D_0061F9E0, 0x17);
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
extern void *D_00639EA8;

/* The per-object-kind action record table (0x4C bytes/entry, indexed by the
   GObj's kind id at +8) and the animation-record table it selects into. */
typedef struct OaRecA {
    char pad[0x34];
    int x34;
    char pad2[0x4C - 0x38];
} OaRecA;

typedef struct OaRecB {
    void *x0;
    int x4;
    int x8;
    int xC;
    int x10;
} OaRecB;

extern OaRecA D_002C2DC8[];
extern OaRecB D_002BC6E0[];
extern void UpdateRootMatrix(void *gobj);
extern void GetRootPosition(void *dst, void *gobj);
extern void GetRootQuaternion(void *dst, void *gobj);
extern float FSqrt(float x);
extern float stage_PlayBgAnimationDissolve(void *anim, float *pos, float *quat, float frame,
                                           float ratio);

void GirlForceFieldDL(char *self)
{
    float pos[4];
    float quat[4];
    float gpos[4];
    GirlForceFieldWork *w = *(GirlForceFieldWork **)(*(char **)(self + 0x15C) + 0x830);
    float d2;
    float ratio;

    UpdateRootMatrix(self);
    GetRootPosition(pos, self);

    if (D_00639EA8 != 0) {
        GetRootPosition(gpos, D_00639EA8);
        d2 = distance_squared(gpos, pos);
        if (d2 < w->radius * w->radius) {
            ratio = 1.0f - FSqrt(d2) * w->invRadius;
            ratio = ratio < 0.0f ? 0.0f : ratio;

            GetRootQuaternion(quat, self);
            w->frame = (int)stage_PlayBgAnimationDissolve(
                D_002BC6E0[D_002C2DC8[*(int *)(self + 8)].x34].x0, pos, quat, (float)w->frame,
                ratio);
            return;
        }
    }
    w->frame = 0;
}
