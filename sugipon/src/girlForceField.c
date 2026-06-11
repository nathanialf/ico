#include "common.h"
#include "ico/types.h"

void GirlForceFieldGeo(void) {
}

void InitGirlForceFieldGeo(void *a0, int a1, int a2) {
    Obj7F0 *o = GOBJ_SUB(a0)->p_7F0;
    switch (a1) {
    case 0:
        o->f_4 = a2;
        break;
    case 1:
        o->f_C = a2;
        break;
    case 2:
        o->f_18 = a2;
        break;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girlForceField", GirlForceFieldDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girlForceField", func_001CF010);

void func_001CF090(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girlForceField", func_001CF098);
