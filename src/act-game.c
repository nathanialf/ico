#include "common.h"






extern char D_006124F8[];
extern int checkHit(char *self);
extern int D_006AA4B0[];
extern void *D_00631AE8;
extern unsigned short D_00565060[];
extern int *D_00631AE4;
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_Loop);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_LwsEffectProcess);

INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTGame_SearchGObj);

int ACTLookTarget_Exec(int *a0)
{
    int *inner;
    long long val;
    register int ret;
    if (a0 == 0) goto fail;
    if (a0 != D_00631AE4) goto fail;
    inner = (int *)a0[0x164 / 4];
    if (inner == 0) goto fail;
    val = *(long long *)((char *)inner + 0x20);
    ret = (int)((val << 8) >> 32) & 1;
    return ret;
fail:
    ret = 0;
    return ret;
}

void ACTParaStatus_Clear(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 1;
    ((int *)self[0x57])[0x153] = 1;
    ((int *)self[0x57])[0x152] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTParaStatus_Exec);

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_00149EF4);

int func_00149EF8(void *a0)
{
    void *p = *((void **) (((char *) a0) + 0x15C));
    int idx = *((int *) (((char *) p) + 0x4A0));
    unsigned short *new_var;
    new_var = D_00565060;
    return ((unsigned short *) (((char *) new_var) + (idx * 0x190)))[0x186 / 2] & 7;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetSkeltonOrient);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_InnerVelocityUpdate);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_BeforeFunc);

int FunctionAboutClingedStatus(char *self)
{
    char *sub = *(char **)(self + 0x164);
    if (*(float *)(sub + 0x1D0) <= 20.0f) {
        return 1;
    }
    return 0;
}

long ACTEnvGetTest(void)
{
    void *a = D_00631AE8;
    if (a == 0) {
        return 0;
    }
    {
        unsigned long *b = *(unsigned long **)((char *)a + 0x164);
        return (b[3] >> 36) & 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ActOrientTest);

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetGirlHandlinkClInfo);

void hand_able_connect(void) {
    int *p = D_006AA4B0;
    *(int *)((char *)p + 0x4B0) = 0;
    *(int *)((char *)p + 0x4B4) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A2C4);

void func_0014A2C8(char *a0)
{
    long long mask1 = ~((long long)0x800 << 32);
    long long mask2 = ~((long long)0x1000 << 32);
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p = *p & mask1 & mask2;
}

void GetOtherStageGirlOrient(char *a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    long long v1 = (long long)0x8000 << 28;
    long long v2 = (long long)0x8000 << 29;
    *p = *p | v1 | v2;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetTarget);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTLookTargetSystem_Exec);

void ACTItemThrow(float *a0, float *a1)
{
    float *q = (float *)D_00631AE4[0x59];
    a0[0] = q[0x4F0/4];
    a0[1] = q[0x4F4/4];
    a0[2] = q[0x4F8/4];
    a1[0] = q[0x4B0/4];
    a1[1] = q[0x4B4/4];
    a1[2] = q[0x4B8/4];
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A46C);

int func_0014A470(void)
{
    int *player = D_00631AE4;
    unsigned int state = *(int *)(*(char **)((char *)player + 0x164) + 0x30);
    void *o;
    unsigned long *b;
    unsigned long bit;
    int rv;
    if (state == 0) {
        goto ret0;
    }
    if (state < 4) {
        goto lt4;
    }
    if (state >= 0x4D) {
        goto ret0;
    }
    if (state < 0x4B) {
        rv = 0;
        goto end;
    }
    return 1;
lt4:
    o = D_00631AE8;
    if (o != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
bittest:
    b = *(unsigned long **)((char *)o + 0x164);
    bit = (b[3] >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
end:
    return rv;
}

int ACTGame_InsertCamera_GirlIsPinch(void)
{
    void *g = D_00631AE8;
    char *a = *(char **)((char *)g + 0x164);
    unsigned int type = *(int *)(a + 0x30);
    unsigned long bit;
    int rv;
    if (type == 0x45) {
        return 1;
    }
    if (type >= 0x46) {
        goto upper;
    }
    if (type >= 4) {
        goto ret0;
    }
    if (type == 0) {
        goto ret0;
    }
    if (g != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
upper:
    if (type >= 0x4F) {
        goto ret0;
    }
    if (type < 0x4D) {
        goto ret0;
    }
    return 1;
bittest:
    bit = (*(unsigned long *)(a + 0x18) >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", updateHMC);

void RequestChangeHandMode(float *a0, float *a1)
{
    float *q = (float *)D_00631AE4[0x59];
    a0[0] = q[0x500/4];
    a0[1] = q[0x504/4];
    a0[2] = q[0x508/4];
    a1[0] = q[0x510/4];
    a1[1] = q[0x514/4];
    a1[2] = q[0x518/4];
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A5FC);

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A600);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameCollisionOn);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameCollisionOff);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckItemMotion);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckHandMotion);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_StageChangeGObjID);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_StageChangeGObjDirect);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_LIFEPINCH);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/nonmatchings/src/act-game", SetDirectRootPositionWithNodePointLimit);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_Init);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCharctrl_Lock);

int ACTCharctrl_Unlock(int a0)
{
    char *base;
    int rv;
    if (a0 != 0) {
        base = D_006124F8;
        base = base - (-(checkHit(a0) * 0x24));
        rv = *(int *)(base + 0x1C);
    } else {
        rv = 0;
    }
    return rv;
}

int ACTGame_ConnectHand(int *a0)
{
    int *q;
    int ret = 0;
    q = (int *)((int *)a0[0x164 / 4])[0x140 / 4];
    if (q == 0 || checkHit(q) == 0) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_DisconnectHand);

INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_GetPosition_BOY);

void PAIR_IsStatus_BOY_PULL(char *self)
{
    char *sub = *(char **)(self + 0x164);
    *(int *)(sub + 0x98) = 0;
    *(int *)(sub + 0xA0) = 0;
    *(int *)(sub + 0x9C) = 0;
}

