#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", InitAttackCheckBoundaryManagerGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryManagerGeo);

void AttackCheckBoundaryManagerDL(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", InitAttackCheckBoundaryGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", actAttackCheckBoundaryStart);

void GetAttackCheckBoundaryRadius(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", CreateAttackCheckBoundary);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", GetAttackCheckBoundaryManagerStatus);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_40;  /* 0x40 */
    unsigned int       f_44;  /* 0x44 */
} S_00617FA0;  /* stride 0x50 */

/* end struct shapes */
