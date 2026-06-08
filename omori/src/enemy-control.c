#include "common.h"

extern int D_0062C0A4;
extern int D_0062C0A8;
extern int D_006CA470[];

int EnemyCtrlBeforeFunc(int a0)
{
    if (D_0062C0A8 < 0) goto init;
    if (a0 != D_0062C0A8) goto append;
    return 1;
init:
    D_0062C0A8 = a0;
    return 1;
append:
    D_006CA470[D_0062C0A4] = a0;
    D_0062C0A4++;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/enemy-control", InitEnemyCtrlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/enemy-control", IsSelectID_EnemyCtrl);

extern int D_0062AA58;

void func_0018F940(void) {
    D_0062AA58 = 1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006CA470;  /* stride 0x4 */

/* end struct shapes */
