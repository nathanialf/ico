#include "common.h"

#include "ico/types.h"

typedef struct { long long w; } __attribute__((packed)) U64ag;

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    float _80;
    char _84[0x04];
    int _88;
    char _8c[0x0C];
    int _98;
    char _9c[0x24];
} HandWork;

typedef union { int i; float f; } IntFloat;






extern char D_006124F8[];
extern int checkHit(char *self);
extern int D_006AA4B0[];
extern void *D_00631AE8;
extern unsigned short D_00565060[];
extern int *D_00631AE4;
extern int *ContinueCorrectPosition(int *a0);
extern int D_00274EC0[];
extern float D_002924D8[];
extern float D_00630AEC;
extern void GetRootMatrixByDObj(char *a0, char *a1);
extern float HandyCamera_TargetMoveType(int *a0, int a1);
extern float before_DrawLine(void *a0, void *a1);
extern void func_0018CD00(float *a0, float *a1, int a2);
extern void *func_0018CEC0(void);
extern void func_00243B18(void *a0, void *a1, float a2);

void ACTGameView_Loop(void)
{
    float buf0[4];
    float buf1[4];
    int buf2[4];
    float neg1;
    void *p;
    int q;
    float e;

    if (D_00631AE4 != 0 && D_00631AE8 != 0) {
        GetRootMatrixByDObj((char *)buf0, (char *)D_00631AE4);
        GetRootMatrixByDObj((char *)buf1, (char *)D_00631AE8);
        if (!(HandyCamera_TargetMoveType((int *)buf0, (int)buf1) < D_00630AEC)) {
            if (!(0.0f < before_DrawLine(buf2, ContinueCorrectPosition((int *)D_00631AE8)))) {
                neg1 = -1.0f;
                func_00243B18(buf0, func_0018CEC0(), neg1);
                func_00243B18(buf1, ContinueCorrectPosition((int *)D_00631AE8), neg1);
                e = D_002924D8[0];
                q = (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1];
                func_0018CD00(buf0, buf1,
                              (int)(e * (float)q / 60.0f));
            }
        }
    }
}

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

extern int D_00561928[][10];
extern void disp_memory_partition_bar(char *self, char *other, int v, char *tmp_a, char *tmp_b);
extern void func_00144938(int idx, char *tmp_a, char *tmp_b);

void ACTGame_InnerVelocityUpdate(char *self, char *other, int idx)
{
    char tmp_a[0x10];
    char tmp_b[0x10];
    func_00144938(idx, tmp_a, tmp_b);
    disp_memory_partition_bar(self, other, D_00561928[idx][9], tmp_a, tmp_b);
}

extern float D_00630AF0;
extern void func_002641D8(void *a0, int a1, int a2);

void ACTGame_BeforeFunc(int *a0, int a1, void *a2, int a3) {
    char buf0[0x10];
    char buf1[0x10];
    func_002641D8(buf1, 0, 0x10);
    *(float *)(buf1 + 4) = (float)a3 * D_00630AF0 / 180.0f;
    func_00243B18(buf0, a2, -1.0f);
    disp_memory_partition_bar((char *)a0[2], (char *)a0[3], a1, buf0, buf1);
}

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

extern int DebugDisp1CollisionWithColor(void *a0, void *a1);

void ActOrientTest(float *dst, char *obj, void *a2)
{
    int idx = DebugDisp1CollisionWithColor(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}

extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern void func_00102A40(void *a0, void *a1, void *a2, float a3);
extern void func_00243978(void *a0, void *a1);
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern void func_00243AE8(void *a0, void *a1, void *a2);

void GetGirlHandlinkClInfo(void *a0, void *a1, void *a2, float farg0, float farg1) {
    float buf0[4];
    float buf18[4];
    float buf16[4];

    ActOrientTest(buf0, a0, a1);
    func_00243AE8(buf16, a2, buf0);
    if (farg1 < MatrixDrive_GetTurnYAngleXZ(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        func_00243978(buf16, buf16);
        func_00243B18(buf16, buf16, farg1);
        func_00243AD0(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *) ((char *) a2 + 4)) {
            buf18[1] = *(float *) ((char *) a2 + 4);
        }
        func_00102A40(a0, a1, buf18, 1.0f);
        return;
    }
    func_00102A40(a0, a1, a2, farg0);
}

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

extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void GetTarget(void)
{
    char *s = *(char **)((char *)D_00631AE8 + 0x164);
    _ACTGame_SearchGObj(D_00631AE8, 0, 4, 6, D_00631AE4, 0, 0);
    _ACTGame_SearchGObj(D_00631AE4, 1, 4, 5, D_00631AE8, 0, 0);
    *(long long *)(s + 0x18) |= (long long)0x8000 << 21;
}

void ACTLookTargetSystem_Exec(void)
{
    char *s = *(char **)((char *)D_00631AE8 + 0x164);
    _ACTGame_SearchGObj(D_00631AE8, 0, 4, 0, 0, 0, 0);
    _ACTGame_SearchGObj(D_00631AE4, 1, 4, 0, 0, 0, 0);
    *(long long *)(s + 0x18) &= ~((long long)0x8000 << 21);
}

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

extern int ACTGame_DisconnectHand(void);
extern int dispInsectNet(int *self);

int ACTGameCollisionOff(int *self)
{
    unsigned long new_var;
    int ret = 0;
    new_var = ACTGame_DisconnectHand();
    if (new_var != 0)
    {
        ret = dispInsectNet(self);
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckItemMotion);

extern void ClipWallBoxStop(void *);
extern void func_00243B60(void *buf, int x);
extern void fzMagnitudefv(void *out, int n, void *vec);

int ACTGame_CheckHandMotion(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget, int *flagout) {
    HandWork work;
    int flag;
    int rv;
    int cnt;

    func_002641D8(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    func_00243B60(&work, (int) hand0);
    func_00243B60((char *) &work + 0x10, (int) hand1);
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 0;
    }
    ClipWallBoxStop(&work);
    if (flagout != 0) {
        *flagout = work._98;
    }
    cnt = work._88;
    if (cnt == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *) ((char *) posout + 0) = work._20;
        *(float *) ((char *) posout + 4) = work._24;
        *(float *) ((char *) posout + 8) = work._28;
    }
    if (cnt != 0 && magtarget != 0) {
        fzMagnitudefv(magtarget, cnt, &work._80);
    }
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 1;
    }
    return rv & 0xFF;
}

int ACTGame_StageChangeGObjID(int a0, int a1, int *a2, char *a3)
{
    char buf[0xC0];
    func_002641D8(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    func_00243B60(buf, a0);
    func_00243B60(buf + 0x10, a1);
    ClipWallBoxStop(buf);
    if (a2 != 0) {
        *a2 = *(int *)(buf + 0x98);
    }
    if (a3 != 0) {
        *(U64ag *)a3 = *(U64ag *)(buf + 0x80);
        *(int *)(a3 + 8) = *(int *)(buf + 0x88);
    }
    return *(int *)(buf + 0x88) != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_StageChangeGObjDirect);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_LIFEPINCH);

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/nonmatchings/src/act-game", SetDirectRootPositionWithNodePointLimit);

int ACTGameView_Init(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006AA4B0[0x4B0 / 4]; i++) {
        if (D_006AA4B0[i] == a1) {
            return *((unsigned char *)&D_006AA4B0[i] + 0x190);
        }
    }
    return 0;
}

int ACTCharctrl_Lock(int a0, int a1) {
    int i;
    for (i = 0; i < D_006AA4B0[0x12C]; i++) {
        if (D_006AA4B0[i] == a1) {
            return *(unsigned char *)((char *)D_006AA4B0 + i * 4 + 0x320);
        }
    }
    return 0;
}

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

extern int checkHit__p4() __asm__("checkHit");

int ACTGame_DisconnectHand(void) {
    return checkHit__p4() == 1;
}

extern const float D_0063226C_flt[] __asm__("D_0063226C");
extern int *isysGObjSearchFromObjKindID_begin(int *);
extern int *isysGObjSearchFromObjLayoutID(int);

int *PAIR_GetPosition_BOY(int a0, int a1) {
    float best_val = D_0063226C_flt[0];
    int *best = 0;
    int *node;

    node = isysGObjSearchFromObjLayoutID(a1);
    if (node != 0) {
        do {
            float val = HandyCamera_TargetMoveType(ContinueCorrectPosition(node), a0);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_begin(node);
        } while (node != 0);
    }
    return best;
}

void PAIR_IsStatus_BOY_PULL(char *self)
{
    char *sub = *(char **)(self + 0x164);
    *(int *)(sub + 0x98) = 0;
    *(int *)(sub + 0xA0) = 0;
    *(int *)(sub + 0x9C) = 0;
}

