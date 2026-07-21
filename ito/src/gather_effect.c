#include "common.h"
#include "ico/types.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_SetGoal);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_Proc);

struct GEl { int f0; char _4[0x6C]; };
struct GGeo { char _0[0x24]; struct GEl *f24; char _28[8]; int f30; };
extern void *InitParticleLayoutGeo(void *a0);

int GatherEffect_Set(int a0) {
    int acc = 0;
    if (a0 >= 0) {
        struct GGeo *geo = (struct GGeo *)InitParticleLayoutGeo((void *)a0);
        if (geo == 0) {
            return 1;
        }
        {
            int n = geo->f30;
            int i;
            for (i = 0; i < n; i++) {
                acc |= geo->f24[i].f0;
            }
        }
    }
    return acc == 0;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *InitParticleLayoutGeo(void *a0);
extern char D_006CCE60[];
extern void ico_m33_to_quat(int *a0, int a1);
extern void mc_TransMicroCode(int a0, int a1);
extern void GetInverseQuaternion(int a0, int a1);
extern void playSEConditionID(int a0, int a1);

void GatherEffect_InqEnd(void *self) {
    void *o = isysGObjSearchFromObjLayoutID(0x3F);
    if (o != 0) {
        void *g = InitParticleLayoutGeo(self);
        int index = *(int *)((char *)g + 0x60);
        char *entry = D_006CCE60 + index * 0x40;
        ico_m33_to_quat((int *)entry, 0x1E0);
        mc_TransMicroCode(*(int *)entry + 0x20, (int)(entry + 0x20));
        GetInverseQuaternion(*(int *)entry + 0x30, (int)(entry + 0x10));
        entry[4] = 2;
        playSEConditionID(0, 0x60);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", func_00195020);

extern signed char D_006CCE50[];
extern int D_00629C90;
extern float D_00629340;
extern void func_00149CC8(void *a0, float a1);
extern void func_00149CD8(void *a0, int a1, float a2);

void func_001951A8(GObj *obj) {
    int flag;

    if (D_006CCE50[0] == 0) {
        return;
    }
    flag = 0;
    if (D_00629C90 == 0x54 || D_00629C90 == 3 || D_00629C90 == 0x2E) {
        flag = 1;
    }
    if (flag == 0) {
        return;
    }
    func_00149CC8(obj, 6.0f);
    switch (GOBJ_SUB(obj)->f_490) {
    case 0x35D:
        return func_00149CD8(obj, 0, 2.0f);
    case 0x38C:
    case 0x38D:
    case 0x38E:
        return func_00149CD8(obj, 0, 2.0f);
    case 0x373:
    case 0x374:
    case 0x375:
        return func_00149CD8(obj, 0, D_00629340);
    default:
        return;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", func_001952A0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", func_00195714);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_4;  /* 0x04 */
} S_006CCE60;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00556250;  /* stride 0x4 */

/* end struct shapes */
