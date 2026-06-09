#include "common.h"
#include "ico/types.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_SetGoal);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_Proc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_Set);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/gather_effect", GatherEffect_InqEnd);

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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    char               f_4;  /* 0x04 */
} S_006CCE60;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00556250;  /* stride 0x4 */

/* end struct shapes */
