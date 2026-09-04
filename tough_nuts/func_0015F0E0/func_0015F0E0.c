#include "common.h"

/* enemy_act 0x164 actor-state view (local) */
typedef struct { char _0[0x1DC]; int f_1DC, f_1E0; char _pad1e4[0x34]; int f_218; } EBrain670;
typedef struct { char _0[0x30]; int f_30; char _pad34[0x10C]; long long f_140; char _pad148[0x2E8]; int f_430; char _pad434[0x23C]; EBrain670 *p_670; } EnemyActState;

typedef struct { int a, b, c; } S_2E9D0;
extern S_2E9D0 D_0027E9D0;
extern char D_0062C458[];
extern void debug_StdPrintfDummy();
extern void actCommonRopeCliff(int a0, int a1);

void setBattleStatus(volatile int a0) {
    debug_StdPrintfDummy(D_0062C458);
    *(S_2E9D0 *)(*(int *)(a0 + 0x15C) + 0x1B0) = D_0027E9D0;
    actCommonRopeCliff(a0, 0);
}


void boss_effect_start(volatile int a0) {
    long long *p = *(long long **)(a0 + 0x164);
    p[4] &= ~0x40000LL;
}

/* m2c scaffold from asm/aug6/nonmatchings/fumi/src/enemy_act/boss_effect_check_parts.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern void ReviveEnemyParticle(void *a0, int a1);

void boss_effect_check_parts(void *a0)
{
    void *volatile self = a0;
    void *p = *(void **)((char *)self + 0x164);
    *(unsigned long long *)((char *)p + 0x18) |= 0x8000000000000000ULL;
    ReviveEnemyParticle(self, 1);
    *(int *)(*(int *)((char *)self + 0x15C) + 0x644) = 0;
}


void boss_effect_process(int a0) {
    int buf[4];
    buf[0] = a0;
}

int _DoAwait(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_30 == 0xF;
}

extern int CanWallLeverPull(int a0, int a1);

int _DoAwaitGirl(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    return CanWallLeverPull(*(int *)(p + 0x5EC), 0);
}

extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_0062C4F8[];

typedef union { long long d; int w[2]; } MustChaseFlag;

void _MustChase(int a0) {
    char *g = *(char **)(*(int *)(a0 + 0x164) + 0x670);
    switch (*(int *)(g + 0x1E4)) {
    case 0:
        ((MustChaseFlag *)(g + 0x208))->d &= ~1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d &= ~2LL;
        break;
    case 1:
        ((MustChaseFlag *)(g + 0x208))->d &= ~1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d |= 2LL;
        break;
    case 2:
        ((MustChaseFlag *)(g + 0x208))->d |= 1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d &= ~2LL;
        break;
    case 3:
        ((MustChaseFlag *)(g + 0x208))->d |= 1LL;
        ((MustChaseFlag *)(*(char **)(*(int *)(a0 + 0x164) + 0x670) + 0x208))->d |= 2LL;
        break;
    default:
        func_001AAD00(D_00553110, 0x312);
        __assert(D_00553110, 0x312, D_0062C4F8);
        break;
    }
}


extern void memset(void *a0, int a1, int a2);
extern void sceVu0CopyVector(void *a0, void *a1);
extern int GatherEffect_Proc(float f, int a0, void *a1, void *a2, void *a3, void *a4);
extern void InitDemoMotionGeo(void *a0, int a1);
extern void GetEnemyTypeFromGObj();
extern int D_00271240[];

typedef struct { float x, y, z, w; } Vec4;
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyControl);


extern void subEnemyControl(int *self, int a1);

void subEnemyCollision(int *self, int a1)
{
    char *p;
    int i;
    p = (char *)((int *)self[0x59])[0x19C] + 0x360;
    i = 0;
    do {
        if (*(signed char *)(p + 0x1D) != 0) {
            if (*(int *)(p + 0x14) == a1) {
                return;
            }
        }
        i++;
        p += 0x20;
    } while (i < 5);
    subEnemyControl(self, a1);
}

extern int HotInitDemoMotionGeo(void *a0, int a1);
extern void sceVu0CopyVector(void *a0, void *a1);
extern void BirdDL(int a0, void *a1);
extern void InitDemoMotionGeo(void *a0, int a1);

void actEnemyAttack(void *self)
{
  int buf[4];
  int k;
  int n;
  int off;
  char *e;
  n = *((int *) (((char *) (*((int **) (((char *) self) + 0x15C)))) + 0x88));
  for (k = 0; k < n; k++)
  {
    if (HotInitDemoMotionGeo(self, k) == 0)
    {
      subEnemyCollision(self, k);
    }
  }

  off = 0;
  k = 4;
  do
  {
    e = ((char *) (off + (*((int *) ((*((int *) (((char *) self) + 0x164))) + 0x670))))) + 0x360;
    if ((*((signed char *) (e + 0x1D))) != 0)
    {
      if ((*((signed char *) (e + 0x1C))) != 0)
      {
        char *g = (((char *) (*((int *) ((*((int *) (((char *) self) + 0x15C))) + 0xC)))) + ((*((int *) (e + 0x14))) << 6)) + 0x30;
        sceVu0CopyVector(buf, g);
        n = off;
        *((float *) (&buf[3])) = 1.0f;
        BirdDL(*((int *) (((char *) (n + (*((int *) ((*((int *) (((char *) self) + 0x164))) + 0x670))))) + 0x370)), buf);
      }
      {
        char *e2 = ((char *) (off + (*((int *) ((*((int *) (((char *) self) + 0x164))) + 0x670))))) + 0x360;
        if ((*((int *) (e2 + 0x18))) == 0)
        {
          InitDemoMotionGeo(self, *((int *) (e2 + 0x14)));
        }
      }
      {
        char *e3 = ((char *) (off + (*((int *) ((*((int *) (((char *) self) + 0x164))) + 0x670))))) + 0x360;
        if (((*((signed char *) (e3 + 0x1C))) == 0) && ((*((int *) (e3 + 0x18))) < 0))
        {
          *((signed char *) (e3 + 0x1D)) = 0;
        }
      }
      {
        char *e4 = ((char *) (off + (*((int *) ((*((int *) (((char *) self) + 0x164))) + 0x670))))) + 0x360;
        *((int *) (e4 + 0x18)) = (*((int *) (e4 + 0x18))) - 1;
      }
    }
    k--;
    off += 0x20;
  }
  while (k >= 0);
}



extern int D_00629DE4;
extern void ActPara_GetDefTbl(void *a0, int a1);
extern int IsEnemyBrainToGenerator(void *a0, int a1, int a2);
extern char D_0055DA10[];

void actEnemyRestart(void *a0) {
    int *p;
    char *e;
    if (D_00629DE4 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_0055DA10 + p[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00629DE4, 5);
        }
    }
}

extern int D_00629DE8;
extern void ActPara_GetDefTbl(void *a0, int a1);
extern int IsEnemyBrainToGenerator(void *a0, int a1, int a2);
extern char D_0055DA10[];

void PairSetGeometry(void *a0) {
    int *p;
    char *e;
    if (D_00629DE8 != 0) {
        ActPara_GetDefTbl(a0, 0x1B);
        p = *(int **)((char *)a0 + 0x15C);
        e = D_0055DA10 + p[0x490 / 4] * 0x190;
        if ((*(unsigned int *)(e + 0x188) >> 1) & 1) {
            IsEnemyBrainToGenerator(a0, D_00629DE8, 5);
        }
    }
}

extern int ContinueCorrectPosition(int a0);
extern float RotateAccordingToStick_PatternThree(float *a0, float *a1);
extern float D_00628FD8;

int actEnemyForceSwitchToCarry(int a0) {
    float v1[4];
    float v2[4];
    float angle;
    float diff;
    int rv;
    if (D_00629DE4 == 0) {
        goto zero;
    }
    v1[0] = ((float *)ContinueCorrectPosition(D_00629DE4))[0];
    v1[1] = ((float *)ContinueCorrectPosition(D_00629DE4))[1];
    v1[2] = ((float *)ContinueCorrectPosition(D_00629DE4))[2];
    v2[0] = ((float *)ContinueCorrectPosition(a0))[0];
    v2[1] = ((float *)ContinueCorrectPosition(a0))[1];
    v2[2] = ((float *)ContinueCorrectPosition(a0))[2];
    angle = RotateAccordingToStick_PatternThree(v1, v2);
    if (angle < D_00628FD8) {
        diff = v1[1] - v2[1];
        if (diff < 0.0f) {
            if (200.0f < -diff) {
                return 1;
            }
            return 0;
        }
        rv = 0;
        if (!(200.0f < diff)) {
            return rv;
        }
    }
    rv = 1;
    goto end;
zero:
    rv = 0;
end:
    return rv;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyKidnapEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015E110);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015E738);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyKidnapBegin);

extern void ACTParaStatus_Exec(void *);
extern int ACTReserveTarget(void *, void *, int);
extern void GetHeightOfFieldPlaneDifference(void *, void *, int, int, void *, float, float, float, float);
extern void actEnemyKidnapBegin(void *, float);
extern void func_0010E4E8(void *, int);
extern void func_0018F2A0(void *, int);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", MoveChestForCatchBoy);




INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyBodylift);

extern int ContinueCorrectPosition(int a0);
extern void _OrientXZGV(float *a0, int a1, int a2);
extern void actCommonStoneDead(void *a0, float *a1, float a2);
extern int func_00143DE0(void *a0, int a1, int a2, float *a3, float a4, float a5);
extern float *subCommonIdle(void *a0);
extern int _RotyGV(float *a0, float *a1);
extern int MoveChestForCatchBoy(void *a0);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void dispPlane(void *a0, float *a1);
extern void ACTGameView_Loop(void);
extern void BoxBarSoundOn(void *a0, int a1);
extern unsigned int _ACTWait(int a0);
extern int D_00629DE8;
extern float D_0062900C;
extern char D_0055DB48[];

void func_0015F0E0(int *volatile self) {
    float buf[8];
    int base = *(int *)((char *)self + 0x164);
    int bp = base + 0x100;
    int status = 0x143;
    int mode, ang, r, r0, r1, idx, q;

    while (1) {
        if (*(int *)(*(int *)((char *)self + 0x15C) + 0x490) != 0x382) goto wait;
        r0 = ContinueCorrectPosition(D_00629DE8);
        r1 = ContinueCorrectPosition((int)self);
        _OrientXZGV((float *)bp, r0, r1);
        if (D_0062900C < *(float *)((char *)base + 0x33C) && *(int *)((char *)base + 0x30) != 0x6F) {
            idx = *(int *)(*(int *)((char *)self + 0x15C) + 0x490);
            actCommonStoneDead((void *)self, (float *)bp, (float)*(int *)(D_0055DB48 + idx * 0x190));
        }
        r = func_00143DE0((void *)self, D_00629DE8, 45, &buf[4], 60.0f, 100.0f);
        if (r == 0) {
            mode = 0;
        } else {
            mode = 2;
            ang = __builtin_abs(_RotyGV(&buf[4], subCommonIdle((void *)D_00629DE8)));
            if (ang <= 89) mode = 1;
        }
        if (mode == 1) goto set144;
        if (mode == 2) goto domove;
        goto do145;
    set144:
        status = 0x144;
    domove:
        if (MoveChestForCatchBoy((void *)self) == 0) goto do145;
        if (mode == 1) {
            q = *(int *)(D_00629DE8 + 0x164) + 0x100;
            sceVu0ScaleVector((void *)q, (void *)q, -1.0f);
            dispPlane((void *)D_00629DE8, (float *)(*(int *)(D_00629DE8 + 0x164) + 0x100));
        }
        ACTGameView_Loop();
        while (1) {
            BoxBarSoundOn((void *)self, status);
            _ACTWait(1);
        }
    do145:
        BoxBarSoundOn((void *)self, 0x145);
    wait:
        _ACTWait(1);
    }
}


extern void GetHeightOfWallFromGObj(void *a0, void *a1);
extern void ActOrientTest(void *a0, void *a1, int a2);
extern float *subCommonIdle(void *a0);
extern void func_00191DB8(void *a0, float a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void debug_Marker(void *a0, int a1, int a2, int a3, float a4);
extern int D_00629DE4;
extern float D_00629010;

void func_0015F2A8(int *self) {
    float a[24];
    float t, ct, f20, f21, f12;
    int r, cr;

    *(int *)((*(int *)((char *)self + 0x15C)) + 0x540) = 1;
    *(int *)((*(int *)((char *)self + 0x15C)) + 0x370) = 2;
    GetHeightOfWallFromGObj(&a[0], self);
    GetHeightOfWallFromGObj(&a[4], (void *)D_00629DE4);
    ActOrientTest(&a[8], self, 1);
    t = (a[1] - a[5]) / 600.0f;
    t = t < 0.0f ? 0.0f : (1.0f < t ? 1.0f : t);
    f20 = t * 1000.0f + -200.0f;
    f21 = t * -400.0f;
    a[12] = subCommonIdle(self)[0];
    a[13] = subCommonIdle(self)[1];
    a[14] = subCommonIdle(self)[2];
    _OrientXZGV(&a[16], &a[4], &a[0]);
    r = _RotyGV(&a[12], &a[16]);
    cr = r;
    cr = cr < -45 ? -45 : (r < 46 ? r : 45);
    f12 = (float)cr * D_00629010 / 180.0f;
    func_00191DB8(&a[12], f12);
    sceVu0ScaleVector(&a[20], &a[12], f20);
    a[21] = f21;
    sceVu0AddVector((void *)((*(int *)((char *)self + 0x15C)) + 0x380), &a[0], &a[20]);
    debug_Marker((void *)((*(int *)((char *)self + 0x15C)) + 0x380), 0xFF, 0, 0, 200.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemyPickupBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015F8A0);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_0015F9C0);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", CheckEnemyBrainMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", BrainMode_Requset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_00160368);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrainMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", enemy_dodge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", Battle_isCurrentStatus);

extern int actBoyDitch3mReady(void);
extern float _GetRandom(void);
extern int D_00629DE4;
extern int D_0062A670;
extern int D_0062BFF0[1];

/* self->f0 (GObj*) -> p_164 -> f_670 (motion obj) */
typedef struct GFP_Mot {
    char _pad0[0x1E0];
    int f1E0;       /* 0x1E0 */
    char _pad1[0x10];
    int f1F4;       /* 0x1F4 */
    char _pad2[0x8];
    int f200;       /* 0x200 */
    char _pad3[0x8];
    int f20C;       /* 0x20C */
} GFP_Mot;
typedef struct GFP_Act { char _pad[0x670]; GFP_Mot *f670; } GFP_Act;
typedef struct GFP_G0  { char _pad[0x164]; GFP_Act *f164; } GFP_G0;
typedef struct GFP_Self { GFP_G0 *f0; } GFP_Self;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", GetFlyPosition);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", NakaBoss);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_001616E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", ChangeBrain_ToAttack);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_00161998);

extern int DispPointBlur(void *a0);
extern void BoxBarSoundOn(void *a0, int a1);
extern int funcEnemyCarryFail(int *a0);
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_00553120[];
extern char D_005532B0[];
extern int D_0062B068;

static inline int subEnemyBrain_ToBoy_chk(void *a0) {
    char *p = *(char **)((char *)a0 + 0x164);
    if (*(int *)(*(char **)(p + 0x670) + 0x1FC) != 5) {
        return 0;
    }
    if (*(int *)(*(char **)(p + 0x678) + 0x400) == 0) {
        func_001AAD00(D_00553110, 0x2E8);
        __assert(D_00553110, 0x2E8, D_00553120);
    }
    return 1;
}

int subEnemyBrain_ToBoy(void *a0) {
    int f18 = 0;
    int f20 = 0;
    int rv = 0;
    int catch;
    int r;
    int a1v;

    r = DispPointBlur(a0);
    switch (r) {
    case 1:
        f18 = 1;
        break;
    case 2:
        f18 = 1;
        f20 = 1;
        break;
    }

    if (a0 == 0 || *(int *)((char *)a0 + 0xC) != 4) {
        func_001AAD00(D_00553110, 0x7C0);
        __assert(D_00553110, 0x7C0, D_005532B0);
    }

    if (funcEnemyCarryFail((int *)a0) == 0) {
        goto done;
    }

    catch = subEnemyBrain_ToBoy_chk(a0);

    if (catch != 0) {
        if (f20 != 0) {
            goto setE;
        }
        if (D_0062B068 == 0) {
            goto done;
        }
    setE:
        BoxBarSoundOn(a0, 0x1E);
        rv = 1;
        goto done;
    } else {
        if (f18 == 0) {
            goto done;
        }
        BoxBarSoundOn(a0, 0x1D);
        rv = 1;
    }
done:
    return rv;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", ChangeBrain_ToKidnap);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", subEnemyBrain_ToGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", _ApproachTarget_Boss);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_00162808);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", flyMailCore);

extern void debug_StdPrintfDummy(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_005531D8[];

void _ApproachTarget_Way(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_005531D8);
    s0 = new_var;
    s0[0x30 / 4] = 0x1;
    _ACTWait(0);
}

extern void debug_StdPrintfDummy(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_00553208[];

void actEnemyStart(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553208);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}

extern void debug_StdPrintfDummy(char *p);
extern unsigned int _ACTWait(int a0);

extern char D_00553238[];

void subEnemyBrain_Irregular(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553238);
    s0[0x30 / 4] = 0x3;
    _ACTWait(0);
}

extern char D_00553280[];

void subEnemyBrain_Attack(volatile unsigned int a0)
{
    int *new_var;
    volatile int local;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553280);
    s0 = new_var;
    s0[0x30 / 4] = 0x1C;
    _ACTWait(0);
}

extern void __assert(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_0062C4F8[];
void subEnemyBrain_Cling(int a0) {
    volatile int local;
    local = a0;
    func_001AAD00(D_00553110, 0xACB);
    __assert(D_00553110, 0xACB, D_0062C4F8);
}

extern void iosOmSendMail();

void funcEnemyAiGetGirl(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    int g = *(int *)(p + 0x670);
    iosOmSendMail(D_00629DE4, *(int *)(g + 0x1F8), (void *)a0, g);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}


extern void iosOmSendMail(void *a0, int a1, void *a2);

void func_00162E98(volatile int a0) {
    iosOmSendMail((void *)D_00629DE4, 0xCF, (void *)a0);
    for (;;) {
        BoxBarSoundOn((void *)a0, 0xB4);
        _ACTWait(1);
    }
}


extern void actChangeActBrain(void *a0, void *a1, void *a2);
extern int actEnemy_isLargeEnemy();
extern int D_0062A4DC;
extern void CylinderCollision(int *self, char *spill);
extern void ResetEnemyEye(int *self);
extern void actEnemyRun(int *self);
extern void gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
extern int D_00629C90;
extern char D_005532A0[];

void func_00162ED8(void *a0) {
    void *volatile self = a0;
    int *p = *(int **)((char *)self + 0x164);
    char spill[16];
    int *s;
    p[0x128 / 4] = 0;
    actChangeActBrain((void *)D_0062A4DC, (void *)actEnemy_isLargeEnemy, (void *)p);
    s = (int *)self;
    *(long long *)(spill + 0) = *(long long *)((char *)D_005532A0 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_005532A0 + 8);
    CylinderCollision(s, spill);
    ResetEnemyEye(s);
    actEnemyRun(s);
    func_0018F2A0((void *)self, 0xA);
    p[0x430 / 4] = 0;
    p[0x434 / 4] = 7;
    gamesysObjInfoPosSetStage((int *)self, 7, 0, D_00629C90);
    _ACTWait(0);
}


void actEnemyStand(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    p->f_140 |= 0x100000000LL;
}

extern void CylinderCollision(int *self, char *spill);
extern void ResetEnemyEye(int *self);
extern void actEnemyRun(int *self);

extern char D_005532A0[];

void actEnemyWalk(int *self)
{
    char spill[16];
    *(long long *)(spill + 0) = *(long long *)((char *)D_005532A0 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_005532A0 + 8);
    CylinderCollision(self, spill);
    ResetEnemyEye(self);
    actEnemyRun(self);
}

typedef struct { char _[0x48]; unsigned int f48; } NestEntry;
extern NestEntry D_002A0A90[];

void actEnemyRun(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    t[idx].f48 &= 0xFFDFFFFF;
}

extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void ACTParaStatus_Clear(void *a0);
extern void func_00178E08(int a0);

void actEnemyHang(volatile int a0) {
    int p = *(int *)(a0 + 0x164);
    void *self2 = (void *)a0;
    void *q;
    *(void **)(p + 0x128) = (void *)D_00629DE8;
    iosOmSendMail((void *)D_00629DE8, 0x2F, self2);
    q = *(void **)(p + 0x128);
    *(int *)(*(int *)((char *)q + 0x15C) + 0x74) = 1;
    ACTParaStatus_Clear(q);
    func_00178E08(0x167);
    *(void **)(p + 0x128) = 0;
    if (*(int *)(p + 0x30) == 5) {
        func_0018F2A0((void *)a0, 4);
    }
}


void actEnemyCarry(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    t[idx].f48 |= 0x40000;
}

int actEnemyBodyslam(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_430 == 2;
}

int actEnemyBodyslamFail(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    return p->f_430 == 1;
}

int actEnemyNest(int *a0) {
    NestEntry *t = D_002A0A90;
    int idx = a0[2];
    return (t[idx].f48 >> 18) & 1;
}

int funcEnemyCarryFail(int *a0)
{
    unsigned int *p = (unsigned int *)((char *)D_002A0A90 + a0[2] * 0x4C);
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

extern int MoveChestForCatchBoy(void *a0);
extern void BoxBarSoundOn(void *a0, int a1);
int actEnemyHyde(void *a0) {
    int r = MoveChestForCatchBoy(a0);
    if (r != 0) {
        func_00163988((int *)a0, 0, 0);
    }
    BoxBarSoundOn(a0, 0xF1);
    return r;
}

int actEnemyFlagOnFree(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    if (q->f_1E0 == 0 && p->f_30 == 0x10) {
        return q->f_218;
    }
    return 0;
}

int afterCommonCarry(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 1;
}

int actEnemyFlagOnDead(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 2;
}

int EnemyBrainStatus_Boy(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1E0 == 0;
}

extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern char D_00553110[];
extern char D_00553120[];
int EnemyBrainStatus_Girl(void *a0, int *a1) {
    void *p = *(char **)((char *)a0 + 0x164);
    int v = *(int *)(*(char **)((char *)p + 0x670) + 0x1FC);
    int w;
    if (v != 5) return 0;
    w = *(int *)(*(char **)((char *)p + 0x678) + 0x400);
    *a1 = w;
    if (w == 0) {
        func_001AAD00(D_00553110, 0x2E8);
        __assert(D_00553110, 0x2E8, D_00553120);
    }
    return 1;
}

extern int D_00629DE8;

int actEnemyFlagCheckDead(char *self)
{
    char *sub;
    char *sub2;
    if (D_00629DE8 != 0) {
        char *sub_d = *(char **)((char *)D_00629DE8 + 0x164);
        if (*(int *)(sub_d + 0x30) != 0x6B) return 0;
    }
    sub = *(char **)((char *)self + 0x164);
    sub2 = *(char **)(sub + 0x670);
    return *(int *)(sub2 + 0x1FC) == 3;
}

int actEnemyFlagCheckActive(void *a0) {
    EnemyActState *p = *(EnemyActState **)((char *)a0 + 0x164);
    EBrain670 *q = p->p_670;
    return q->f_1DC;
}

int ACTEnemyForceSwitchToCarry(void) {
    return 1;
}

int actEnemy_GetClingTarget(int *a0) {
    unsigned int *p;
    unsigned int field;
    unsigned int v0;
    if (*(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0x1DC) == 0)
        return 0;
    p = (unsigned int *)((char *)D_002A0A90 + a0[2] * 0x4C);
    field = p[0x48 / 4];
    v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}

extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern char D_005532B0[];
int actEnemy_isNormalEnemy(void *a0) {
    if (a0 == 0 || *(int *)((char *)a0 + 0xC) != 4) {
        func_001AAD00(D_00553110, 0x7C0);
        __assert(D_00553110, 0x7C0, D_005532B0);
    }
    return funcEnemyCarryFail((int *)a0);
}

int actEnemy_isLargeEnemy(volatile int a0) {
    int *p = *(int **)(a0 + 0x164);
    p[0x33C / 4] = 0;
    p[0x100 / 4] = 0;
    p[0x104 / 4] = 0;
    p[0x108 / 4] = 0;
    for (;;) {
        if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x210) == D_00629DE4) {
            actEnemyRestart((void *)a0);
        }
        _ACTWait(1);
    }
}


extern float _GetRandom(void);
extern int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);

void func_00163448(volatile unsigned int a0)
{
    int *p = *(int **)(a0 + 0x164);
    p[0x33C / 4] = 0;
    p[0x100 / 4] = 0;
    p[0x104 / 4] = 0;
    p[0x108 / 4] = 0;
    if (D_00629DE4 != 0) {
        DispCollisionPC((void *)a0, D_00629DE4, (int)((char *)p + 0x100), 0, 0,
                        (float)((int)(_GetRandom() * 10.0f) % 200 + 300));
    }
    p[0x33C / 4] = 0;
    p[0x100 / 4] = 0;
    p[0x104 / 4] = 0;
    p[0x108 / 4] = 0;
    for (;;) {
        actEnemyRestart((void *)a0);
        _ACTWait(1);
    }
}


extern char D_00553320[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", func_00163500);


extern int D_00271240[];

void func_001635B8(volatile unsigned int a0)
{
    int *p = *(int **)(a0 + 0x164);
    int i, cnt;
    for (i = 0; i < (0x3C - D_00271240[0] * 0xA) / D_00271240[1] / 2; i++) {
        p[0x33C / 4] = 0;
        p[0x100 / 4] = 0;
        p[0x104 / 4] = 0;
        p[0x108 / 4] = 0;
        BoxBarSoundOn((void *)a0, 0xD3);
        if (p[0x30 / 4] == 0x47) {
            break;
        }
        _ACTWait(1);
    }
    for (i = 0; i < (0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 0xFA / 0x3C; i++) {
        actEnemyRestart((void *)a0);
        _ACTWait(1);
    }
    func_0018F2A0((void *)a0, 1);
    _ACTWait(0);

}


extern float ClearHandCameraCorrect(int a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/enemy_act", actEnemy_isSmallEnemy);


extern int ContinueCorrectPosition(int a0);
extern void _OrientXZGV(float *a0, int a1, int a2);
extern void dispPlane(void *a0, float *a1);

void func_00163830(volatile unsigned int a0)
{
    volatile int local;
    char *m;
    int r0, r1;
    m = (char *)(*(int *)(a0 + 0x164)) + 0x100;
    r0 = ContinueCorrectPosition(D_00629DE8);
    r1 = ContinueCorrectPosition(a0);
    _OrientXZGV((float *)m, r0, r1);
    dispPlane((void *)a0, (float *)m);
    BoxBarSoundOn((void *)a0, 0x142);
    for (;;) {
        int s;
        _ACTWait(0x78);
        s = a0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x200) = 0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x20C) = D_0062A670;
    }
}


void func_001638C0(volatile unsigned int a0)
{
    BoxBarSoundOn((void *)a0, 0x14C);
    for (;;) {
        int s;
        _ACTWait(0x78);
        s = a0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x200) = 0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x20C) = D_0062A670;
    }
}


void func_00163910(volatile unsigned int a0)
{
    if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x1DC) == 3) {
        BoxBarSoundOn((void *)a0, 0x155);
    } else {
        BoxBarSoundOn((void *)a0, 0x153);
    }
    for (;;) {
        int s;
        _ACTWait(0x78);
        s = a0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x200) = 0;
        *(int *)(*(int *)(*(int *)(s + 0x164) + 0x670) + 0x20C) = D_0062A670;
    }
}


extern int D_0062A670;

void func_00163988(int *a0, int a1, int *a2) {
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x200) = a1;
    if (a2 == 0) goto elsebr;
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x20C) = a2[0];
    return;
elsebr:
    *(int *)(*(int *)(a0[0x59] + 0x670) + 0x20C) = D_0062A670;
}

extern int ContinueCorrectPosition(int a0);
extern void _OrientXZGV(float *a0, int a1, int a2);
extern void func_00104548(float *a0, void *a1);
extern int _RotyGV(float *a0, float *a1);
extern void dispPlane(void *a0, float *a1);
extern void actCommonStoneDead(void *a0, float *a1, float a2);
extern void BoxBarSoundOn(void *a0, int a1);

int IsEnemyBrainToGenerator(void *a0, int a1, int a2) {
    float posA[4];
    float mtx[4];
    float posB[4];
    char *p;
    char *q;
    float *m;
    int r0;
    int r1;
    int flag;
    int mode;
    int angle;
    int absA;

    p = *(char **)((char *)a0 + 0x164);
    r0 = ContinueCorrectPosition(a1);
    r1 = ContinueCorrectPosition(a0);
    _OrientXZGV(posA, r0, r1);
    q = *(char **)((char *)a0 + 0x164);
    *(float *)(p + 0x100) = posA[0];
    *(float *)(p + 0x104) = posA[1];
    *(float *)(p + 0x108) = posA[2];
    flag = *(int *)(q + 0x30);
    mode = ((flag ^ 3) == 0) ? 0x5A : 0x69;
    posB[0] = *(float *)(q + 0x100);
    posB[1] = *(float *)(q + 0x104);
    posB[2] = *(float *)(q + 0x108);
    m = mtx;
    func_00104548(m, a0);
    m = posB;
    angle = _RotyGV(mtx, m);
    absA = (angle >= 0) ? angle : -angle;
    if (mode < absA) {
        *(float *)(q + 0x5B0) = posB[0];
        *(float *)(q + 0x5B4) = posB[1];
        *(float *)(q + 0x5B8) = posB[2];
        if (angle > 0) {
            BoxBarSoundOn(a0, 0xD5);
        } else {
            BoxBarSoundOn(a0, 0xD4);
        }
    } else if (absA < 0xF) {
        BoxBarSoundOn(a0, 0xDE);
    }
    if (a2 == 0) {
        dispPlane(a0, posA);
    } else {
        actCommonStoneDead(a0, posA, (float)a2);
    }
}


extern int subEnemyBrain_ToBoy(void *a0);

int FlyMail(void *a0) {
    int x = *(int *)(*(char **)((char *)a0 + 0x164) + 0x10);
    if (x < 0xC) {
        return -1;
    }
    return subEnemyBrain_ToBoy(a0);
}

void GetEnemyTypeFromGObj(int a0) {
    void *o = isysGObjSearchFromObjLayoutID(4);
    if (o != 0) {
        do {
            if (*(int *)(*(int *)(*(int *)((char *)o + 0x164) + 0x670) + 0x1DC) == 3) {
                int i;
                for (i = 0; i < 5; i++) {
                    char *e = (char *)((i << 5) + *(int *)(*(int *)((char *)o + 0x164) + 0x670) + 0x360);
                    if (e[0x1D] != 0) {
                        if (*(int *)(e + 0x10) == a0) {
                            e[0x1C] = 0;
                            return;
                        }
                    }
                }
            }
            o = isysGObjSearchFromObjKindID_next(o);
        } while (o != 0);
    }
}



extern void *ExecMotionOrient(void *a0, void *a1, void *a2);
extern char D_005531F0[];

void GetEnemyType(volatile unsigned int a0) {
    int *s0;
    void *r;
    s0 = *((int **)(a0 + 0x164));
    debug_StdPrintfDummy((char *)D_005531F0);
    r = ExecMotionOrient((void *)a0, (void *)1, (char *)s0 + 0x610);
    s0[0x110 / 4] = (int)r;
    for (;;) {
        _ACTWait(1);
    }
}


extern void debug_StdPrintfDummy(char *p);
extern void *ExecMotionOrient(void *a0, void *a1, void *a2);
extern char D_00553220[];

void func_00163C40(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    void *r;
    s0 = *((int **)(a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553220);
    r = ExecMotionOrient((void *)a0, (void *)7, (char *)s0 + 0x610);
    s0[0x110 / 4] = (int)r;
    *(int *)((char *)r + 0x114) = 0;
    _ACTWait(0);
}



/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_58;  /* 0x58 */
    unsigned int       f_74;  /* 0x74 */
    unsigned int       f_90;  /* 0x90 */
    unsigned int       f_AC;  /* 0xAC */
    unsigned int       f_C8;  /* 0xC8 */
    unsigned int       f_170;  /* 0x170 */
} S_0027E770;  /* stride 0x1C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553140;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005532F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553420;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553440;  /* stride 0x4 */

/* end struct shapes */
