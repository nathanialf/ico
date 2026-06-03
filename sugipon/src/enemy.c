#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", setEnemyParticleObject);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", setEnemyObject);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", dispEnemyObject);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyCheckHit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", CheckEnemyHit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", InitEnemyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", DisplayEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", DemoMotionGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyFootPrintSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemySetfAppearAll);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemySetfDisappearAll);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemySetfDisappear);

void enemySetParticleDie(void) {
}

void ReviveEnemyParticle(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0xB] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", isExistEnemyParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyGetNSafeParts);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyDeleteParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyHitGeometryAction);

void InitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *base = *(int **)((char *)q + 0x14);
    base[a1] = 0;
}

int HotInitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *r = *(int **)((char *)q + 0x14);
    return r[a1] == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", GetEnemyHitNodeFlag);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_00617DA8;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00617E50;  /* stride 0x4 */

/* end struct shapes */
