#include "common.h"

#include "ico/types.h"

extern char D_0061F9E0[];   /* "...sugipon/src/girlForceField.c": this TU's __FILE__ */
extern int D_0063A438;      /* game heap handle */
extern void *iosMallocDebug(int heap, int size, char *file, int line);
/* Per-object force-field state, hung off the actor's sub-object by the caller
   (GirlForceFieldDL reads it back at sub+0x830). */
typedef struct GirlForceFieldWork {
    float radius;
    float invRadius;
    int   frame;
} GirlForceFieldWork;
/* The 0x15C sub-object slot is a word the engine reads either as an int handle
   or as a pointer (see include/ico/types.h GOBJ_SUB). */
typedef union GObjSubSlot { int handle; void *p; } GObjSubSlot;
/* prototypes: their order is the inline tail's emission order */
GirlForceFieldWork *InitGirlForceFieldGeo(char *self, char *param);
void GirlForceFieldGeo(void);
inline GirlForceFieldWork *InitGirlForceFieldGeo(char *self, char *param)
{
    GirlForceFieldWork *w =
        (GirlForceFieldWork *)iosMallocDebug(D_0063A438, 12, D_0061F9E0, 0x17);
    float *c;
    w->radius = *(float *)(param + 0x28);
    w->invRadius = 1.0f / w->radius;
    w->frame = 0;
    c = *(float **)(((GObjSubSlot *)(self + 0x15C))->handle + 0x870);
    c[8] = c[9] = c[10] = 1.0f;
    return w;
}
inline void GirlForceFieldGeo(void) {}
INCLUDE_ASM("asm/nonmatchings/src/girlForceField", GirlForceFieldDL);
