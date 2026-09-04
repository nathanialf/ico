#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", setBattleStatus);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", boss_effect_start);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", boss_effect_check_parts);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", boss_effect_process);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _DoAwait);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _DoAwaitGirl);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _MustChase);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164600);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", PairSetGeometry);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyForceSwitchToCarry);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165670);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165FD0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001661B8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001666E8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", BrainMode_Requset);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00166B70);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", enemy_dodge_to_boy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", Battle_isCurrentStatus);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetFlyPosition);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", NakaBoss);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ChangeBrain_ToAttack);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001680B8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001687C8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00168888);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00168A78);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", flyMailCore);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget_Way);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169498);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169978);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169CD8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169E58);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169EA0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169EE8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169F30);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyCarry);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00169FC0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", funcEnemyCarryFail);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemyHyde);
extern char D_002C2DC8[];

void actEnemyFlagOnFree(int *a0)
{
    char *base = D_002C2DC8 + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", afterCommonCarry);
void actEnemyFlagOnDead(int *a0)
{
    char *base = D_002C2DC8 + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", EnemyBrainStatus_Boy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", EnemyBrainStatus_Girl);
int actEnemyFlagCheckDead(int *a0)
{
    int *p = (int *)(D_002C2DC8 + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}
int actEnemyFlagCheckActive(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002C2DC8 + a0[2] * 0x4C);
    unsigned int field = p[0x48 / 4];
    unsigned int v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", ACTEnemyForceSwitchToCarry);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_GetClingTarget);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isNormalEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isLargeEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", actEnemy_isSmallEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", IsEnemyBrainToGenerator);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", IsEnemyBrainToBoy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetEnemyTypeFromGObj);
int GetEnemyType(void) {
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", isEnemyKidnapEnable);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", isEnemyActive);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetMotherGeneratorLabelAskEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", GetMotherGeneratorGObjAskEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016A568);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016A818);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016AB60);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", EnemyUtil_TurnToBoy);
extern int flyMailCore(void *a0);

int FlyMail(void *a0) {
    int x = *(int *)(*(char **)((char *)a0 + 0x164) + 0x10);
    if (x < 0xC) {
        return -1;
    }
    return flyMailCore(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", boss_effect_callback);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016ADD0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016AE70);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016AEC8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", EnemyUtil_isOtherStatus);
int isEnemyHyde(int *a0)
{
    int *p = (int *)(D_002C2DC8 + a0[2] * 0x4C);
    return (((unsigned int)p[0x48 / 4] >> 21) & 1) ^ 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", _ApproachTarget);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", afterEnemyBodylift);
