#include "common.h"
#include "ico/types.h"

/* act-game 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; char _pad34[0x54]; int f_88, f_8C, f_90; char _pad94[0xEC]; int f_180; } AGState;

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

extern void *subCommonIdle(void *a0);
extern int Draw2DLineSeg_Start(int a0);
extern void ReleaseItem(int a0, void *a1);
extern void func_00240038(void *a0, void *a1, float a2);
extern int D_00271240[];
extern float D_0028E614;
extern char D_0062C3C8[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand_WithMail);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCheckView);

extern int *ContinueCorrectPosition(int *a0);
extern void GetRootMatrixByDObj(char *a0, char *a1);
extern float HandyCamera_TargetMoveType(int *a0, int a1);
extern float before_DrawLine(void *a0, void *a1);
extern void func_0018A1D8(float *a0, float *a1, int a2);
extern void *func_0018A370(void);
extern float D_0028E618[];
extern float D_00628DEC;
extern void *D_00629DE4;
extern void *D_00629DE8;

void ACTGameView_Loop(void)
{
    float buf0[4];
    float buf1[4];
    int buf2[4];
    float neg1;
    void *p;
    int q;
    float e;

    if (D_00629DE4 != 0 && D_00629DE8 != 0) {
        GetRootMatrixByDObj((char *)buf0, (char *)D_00629DE4);
        GetRootMatrixByDObj((char *)buf1, (char *)D_00629DE8);
        if (!(HandyCamera_TargetMoveType((int *)buf0, (int)buf1) < D_00628DEC)) {
            if (!(0.0f < before_DrawLine(buf2, ContinueCorrectPosition((int *)D_00629DE8)))) {
                neg1 = -1.0f;
                func_00240038(buf0, func_0018A370(), neg1);
                func_00240038(buf1, ContinueCorrectPosition((int *)D_00629DE8), neg1);
                e = D_0028E618[0];
                q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
                func_0018A1D8(buf0, buf1,
                              (int)(e * (float)q / 60.0f));
            }
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_LwsEffectProcess);

extern void ACTGame_LwsEffectProcess(void *ctx);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern char D_00552200[];
extern char D_0062C3C0[];

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

int GetSkeltonOrient(void *a0, void *a1) {
    int i0 = (*(int **)((char *)a0 + 0x15C))[0x490 / 4];
    int i1 = (*(int **)((char *)a1 + 0x15C))[0x490 / 4];
    ACTCharStat *e0 = &D_0055DA10[i0];
    ACTCharStat *e1 = &D_0055DA10[i1];
    int b0 = (*(unsigned int *)((char *)e0 + 0x188) >> 15) & 1;
    int b1 = (*(unsigned int *)((char *)e1 + 0x188) >> 15) & 1;
    return b0 & b1;
}

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

extern void func_00260568(void *a0, int a1, int a2);
extern float D_00628DF0;
extern void func_00240038(void *a0, void *a1, float a2);

void ACTGame_BeforeFunc(int *a0, int a1, void *a2, int a3) {
    char buf0[0x10];
    char buf1[0x10];
    func_00260568(buf1, 0, 0x10);
    *(float *)(buf1 + 4) = (float)a3 * D_00628DF0 / 180.0f;
    func_00240038(buf0, a2, -1.0f);
    disp_memory_partition_bar((char *)a0[2], (char *)a0[3], a1, buf0, buf1);
}

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

extern float MatrixDrive_GetTurnYAngleXZ(float a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void func_0023FE98(void *a0, void *a1);
extern void func_0023FFF0(void *a0, void *a1, void *a2);
extern void SetRootMatrixWithTransOffsetByDObj(void *a0, void *a1, void *a2, float a3);

void GetGirlHandlinkClInfo(void *a0, void *a1, void *a2, float farg0, float farg1) {
    float buf0[4];
    float buf18[4];
    float buf16[4];

    ActOrientTest(buf0, a0, a1);
    func_00240008(buf16, a2, buf0);
    if (farg1 < MatrixDrive_GetTurnYAngleXZ(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        func_0023FE98(buf16, buf16);
        func_00240038(buf16, buf16, farg1);
        func_0023FFF0(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *) ((char *) a2 + 4)) {
            buf18[1] = *(float *) ((char *) a2 + 4);
        }
        SetRootMatrixWithTransOffsetByDObj(a0, a1, buf18, 1.0f);
        return;
    }
    SetRootMatrixWithTransOffsetByDObj(a0, a1, a2, farg0);
}


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

/* per-action-state attribute table (stride 0x50), indexed by AGState.f_30 */
typedef struct { char _pad0[0x4C]; unsigned int f_4C; } ActStateAttr;
extern ActStateAttr D_00557188[];

int ACTGameCollisionOn(void *a0)
{
    AGState *s = *(AGState **)((char *)a0 + 0x164);
    if (a0 == D_00629DE4) {
        unsigned int off = s->f_30 * 0x50;
        off += (unsigned int)D_00557188;
        if ((((ActStateAttr *)off)->f_4C >> 6) & 1) {
            return s->f_180;
        }
    }
    return 0;
}

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

extern void func_00260568(void *dst, int val, int len);
extern void func_00240080(void *buf, int x);
extern void ClipWallBoxStop(void *buf);
extern void fzMagnitudefv(void *out, int n, void *vec);

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

int ACTGame_CheckHandMotion(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget, int *flagout) {
    HandWork work;
    int flag;
    int rv;
    int cnt;

    func_00260568(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    func_00240080(&work, (int) hand0);
    func_00240080((char *) &work + 0x10, (int) hand1);
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

extern void ChangeFieldCollisionDebugMode(void *buf);
extern int D_0062A558;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObjDirect);


extern int ClipWallFieldCheckCB(void *buf);
extern int func_001668B0(int a0, int a1);
extern int D_0062A55C;

typedef struct { char _pad[0x15C]; char *unk15C; } FlagObj;

int ACTGame_FLAG_LIFEPINCH(int a0, int a1, FlagObj *a2, float *a3, float f) {
    int flag;
    char buf[0xC0];

    func_00260568(buf, 0, 0xC0);
    if (a2 != 0) {
        flag = *(int *)(a2->unk15C + 0x74);
    } else {
        flag = 0;
    }
    *(float *)(buf + 0x70) = f;
    D_0062A55C = 0;
    func_00240080(buf, a0);
    func_00240080(buf + 0x10, a1);
    if (flag) { *(int *)(a2->unk15C + 0x74) = 0; ClipWallBoxStop(buf); }
    if (flag) { *(int *)(a2->unk15C + 0x74) = 1; }
    if (*(int *)(buf + 0x88) == 0) {
        if (flag) { *(int *)(a2->unk15C + 0x74) = 0; ClipWallFieldCheckCB(buf); }
        if (flag) { *(int *)(a2->unk15C + 0x74) = 1; }
    }
    if (*(int *)(buf + 0x88) != 0) {
        D_0062A55C = *(int *)(buf + 0x80);
        a0 = *(int *)(buf + 0x98);
        if (func_001668B0(a0, 0x30000) != 0) {
            return 0;
        }
    }
    if (a3 != 0) {
        a3[0] = *(float *)(buf + 0x20);
        a3[1] = *(float *)(buf + 0x24);
        a3[2] = *(float *)(buf + 0x28);
    }
    return 1;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", SetDirectRootPositionWithNodePointLimit);

int ACTGameView_Init(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006A3F70[0x4B0 / 4]; i++) {
        if (D_006A3F70[i] == a1) {
            return *((unsigned char *)&D_006A3F70[i] + 0x190);
        }
    }
    return 0;
}

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
