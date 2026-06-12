#include "common.h"
#include "ico/types.h"

/* act-game 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; char _pad34[0x54]; int f_88, f_8C, f_90; } AGState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_SaveActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DeleteActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", EXITDATA_GetNextPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObj);

extern int InitIcoMisc(void *a0);
extern int D_00629C90;
extern void func_0019A4B8(void *a0, int a1, int a2);

void ACTGame_SetActors_Debug(void *a0) {
    int r = InitIcoMisc(a0);
    func_0019A4B8(a0, D_00629C90, r);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryConnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryDisconnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand_WithMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCheckView);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameView_Loop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_LwsEffectProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", _ACTGame_SearchGObj);

extern void *D_00629DE4;

int ACTLookTarget_Exec(char *a0) {
    long long v;
    if (a0 == 0) {
        goto ret0;
    }
    if (a0 != D_00629DE4) {
        goto ret0;
    }
    a0 = *(char **)(a0 + 0x164);
    if (a0 == 0) {
        goto ret0;
    }
    v = *(long long *)(a0 + 0x20);
    v = v << 15;
    return (int)(v >> 32) & 1;
ret0:
    return 0;
}

void ACTParaStatus_Clear(int a0) {
    GOBJ_SUB(a0)->f_534 = 1;
    GOBJ_SUB(a0)->f_53C = 1;
    GOBJ_SUB(a0)->f_538 = 1;
    GOBJ_SUB(a0)->f_7C = 1;
}

void ACTParaStatus_Exec(void *a0) {
    GOBJ_SUB(a0)->f_534 = 0;
    GOBJ_SUB(a0)->f_53C = 0;
    GOBJ_SUB(a0)->f_538 = 0;
    GOBJ_SUB(a0)->f_7C = 0;
}

typedef struct { char _[0x186]; unsigned short f186; char _pad[8]; } ACTCharStat;
extern ACTCharStat D_0055DA10[];

int _ACTCharStatus_Clear(void *a0) {
    ACTCharStat *t = D_0055DA10;
    int idx = GOBJ_SUB(a0)->f_490;
    return t[idx].f186 & 7;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonOrient);

extern int D_0055A2D8[][10];
extern void func_001433F0(int idx, char *tmp_a, char *tmp_b);
extern void disp_memory_partition_bar(char *self, char *other, int v, char *tmp_a, char *tmp_b);

void ACTGame_InnerVelocityUpdate(char *self, char *other, int idx)
{
    char tmp_a[0x10];
    char tmp_b[0x10];
    func_001433F0(idx, tmp_a, tmp_b);
    disp_memory_partition_bar(self, other, D_0055A2D8[idx][9], tmp_a, tmp_b);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_BeforeFunc);

int FunctionAboutClingedStatus(void *a0) {
    float f = *(float *)(*(char **)((char *)a0 + 0x164) + 0x1D0);
    if (f <= 20.0f) {
        return 1;
    }
    return 0;
}

extern void *D_00629DE8;
int ACTEnvGetTest(void) {
    void *q;
    if (D_00629DE8 == 0) return 0;
    q = *(void **)((char *)D_00629DE8 + 0x164);
    return (int)(*(unsigned long long *)((char *)q + 0x18) >> 36) & 1;
}

extern int DebugDisp1CollisionWithColor(void *a0, void *a1);

/* The engine stores component floats through an int/float union so the
 * float stores may-alias the surrounding int traffic (single swc1, no
 * -fno-strict-aliasing override). */
typedef union { int i; float f; } IntFloat;

void ActOrientTest(float *dst, char *obj, void *a2)
{
    int idx = DebugDisp1CollisionWithColor(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetGirlHandlinkClInfo);

extern int D_006A3F70[];

void hand_able_connect(void) {
    D_006A3F70[0x12C] = 0;
    D_006A3F70[0x12D] = 0;
}

void ACTGame_CommonLoop(char *a0)
{
    long long mask1 = ~((long long)0x800 << 32);
    long long mask2 = ~((long long)0x1000 << 32);
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p = *p & mask1 & mask2;
}

void GetOtherStageGirlOrient(void *a0) {
    long long *p = (long long *)((char *)*(void **)((char *)a0 + 0x164) + 0x18);
    *p |= (long long)0x8000 << 28;
    *p |= (long long)0x8000 << 29;
}

extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void GetTarget(void)
{
    char *s = *(char **)((char *)D_00629DE8 + 0x164);
    _ACTGame_SearchGObj(D_00629DE8, 0, 4, 6, D_00629DE4, 0, 0);
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 5, D_00629DE8, 0, 0);
    *(long long *)(s + 0x18) |= (long long)0x8000 << 21;
}

void ACTLookTargetSystem_Exec(void)
{
    char *s = *(char **)((char *)D_00629DE8 + 0x164);
    _ACTGame_SearchGObj(D_00629DE8, 0, 4, 0, 0, 0, 0);
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 0, 0, 0, 0);
    *(long long *)(s + 0x18) &= ~((long long)0x8000 << 21);
}

void ACTItemThrow(float *a0, float *a1)
{
    float *q = (float *)((int *)D_00629DE4)[0x59];
    a0[0] = q[0x4F0/4];
    a0[1] = q[0x4F4/4];
    a0[2] = q[0x4F8/4];
    a1[0] = q[0x4B0/4];
    a1[1] = q[0x4B4/4];
    a1[2] = q[0x4B8/4];
}

int ACTItemWatchMotion(void)
{
    int *player = D_00629DE4;
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
    o = D_00629DE8;
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
    void *g = D_00629DE8;
    AGState *a = *(AGState **)((char *)g + 0x164);
    unsigned int type = a->f_30;
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
    bit = (*(unsigned long *)((char *)a + 0x18) >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
    return rv;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", updateHMC);

void RequestChangeHandMode(float *a0, float *a1)
{
    float *q = (float *)((int *)D_00629DE4)[0x59];
    a0[0] = q[0x500/4];
    a0[1] = q[0x504/4];
    a0[2] = q[0x508/4];
    a1[0] = q[0x510/4];
    a1[1] = q[0x514/4];
    a1[2] = q[0x518/4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTNotNeedCameraOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameCollisionOn);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CheckItemMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CheckHandMotion);

extern void func_00260568(void *dst, int val, int n);
extern void func_00240080(void *buf, int x);
extern void ClipWallBoxStop(void *buf);

/* unaligned 64-bit copy via packed struct (ldl/ldr + sdl/sdr) */
typedef struct { long long w; } __attribute__((packed)) U64ag;

int ACTGame_StageChangeGObjID(int a0, int a1, int *a2, char *a3)
{
    char buf[0xC0];
    func_00260568(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    func_00240080(buf, a0);
    func_00240080(buf + 0x10, a1);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObjDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_LIFEPINCH);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", SetDirectRootPositionWithNodePointLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameView_Init);

int ACTCharctrl_Lock(int a0, int a1) {
    int i;
    for (i = 0; i < D_006A3F70[0x12C]; i++) {
        if (D_006A3F70[i] == a1) {
            return *(unsigned char *)((char *)D_006A3F70 + i * 4 + 0x320);
        }
    }
    return 0;
}

extern char D_0060AF70[];

int ACTCharctrl_Unlock(int a0)
{
    char *base;
    int rv;
    if (a0 != 0) {
        base = D_0060AF70;
        base = base - (-(checkHit(a0) * 0x24));
        rv = *(int *)(base + 0x1C);
    } else {
        rv = 0;
    }
    return rv;
}

int ACTGame_ConnectHand(char *a0) {
    int r = 0;
    void *next = *(void **)(*(char **)(a0 + 0x164) + 0x130);
    if (next == 0 || checkHit(next) == 0) {
        r = 1;
    }
    return r;
}

extern int checkHit(void);
int ACTGame_DisconnectHand(void) {
    return checkHit() == 1;
}

extern const float D_0063226C_flt[] __asm__("D_0062C3D4");
extern int *isysGObjSearchFromObjLayoutID(int);
extern int *ContinueCorrectPosition(int *);
extern float HandyCamera_TargetMoveType(int *, int);
extern int *isysGObjSearchFromObjKindID_begin(int *);

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

void PAIR_IsStatus_BOY_PULL(void *a0) {
    AGState *p = *(AGState **)((char *)a0 + 0x164);
    p->f_88 = 0;
    p->f_90 = 0;
    p->f_8C = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_190;  /* 0x190 */
    unsigned int       f_320;  /* 0x320 */
    unsigned int       f_4B0;  /* 0x4B0 */
    unsigned int       f_4B4;  /* 0x4B4 */
} S_006A3F70;  /* stride 0x4 */

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0027DED0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005523F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552430;  /* stride 0x4 */

/* end struct shapes */
