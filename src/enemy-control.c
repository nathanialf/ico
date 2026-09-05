#include "common.h"
#include "sugiCommon.h"

/* prototypes: their order is the inline tail's emission order */
int InitEnemyCtrlGeo(void);
int IsSelectID_EnemyCtrl(int a0);
extern int D_0063C2D4;
extern int D_0063C2D8;
extern int D_0063C2DC;
extern int D_006E6BD0[];
inline int InitEnemyCtrlGeo(void)
{
    D_0063C2D4 = 0;
    D_0063C2D8 = -1;
    D_0063C2DC = 0;
    return 0;
}
void EnemyCtrlBeforeFunc(void) {
    if (D_0063C2D4 > 0) {
        D_0063C2D8 = D_006E6BD0[(int)(random_unit() * 10.0f) % D_0063C2D4];
    } else {
        D_0063C2D8 = -1;
    }
    D_0063C2DC++;
    D_0063C2D4 = 0;
}
inline int IsSelectID_EnemyCtrl(int a0)
{
    if (D_0063C2D8 < 0) goto init;
    if (a0 != D_0063C2D8) goto append;
    return 1;
init:
    D_0063C2D8 = a0;
    return 1;
append:
    D_006E6BD0[D_0063C2D4] = a0;
    D_0063C2D4++;
    return 0;
}
