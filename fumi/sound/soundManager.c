#include "common.h"

/* soundManager 0x164 actor-state view (local) */
typedef struct { char _0[0x80]; int f_80; } SndState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndBgmReadyNextStage);

extern void debug_assertMessage();
extern char D_006A3370[];

extern char D_00552178[];

extern char D_005CD670[];

int sndInit(void)
{
    char *e = D_006A3370;
    int sz = 0x3C;
    int i = 0x2F;
    do {
        if (*(int *)(e + 0x30) != 0) {
            debug_assertMessage((int)D_00552178, *(short *)(e + 0x10),
                          (unsigned int)(*(int *)(e + 0x38) - (int)D_005CD670) / sz);
        }
        e += 0x40;
        i--;
    } while (i >= 0);
    __asm__ __volatile__("break");
}

extern void debug_DispSEInfo(int x, int y);
extern void soundDataSegNextStageNotUseClose(int *a, int *b);
extern void Ee2Iop(int x, int *p);
extern void soundVBlank(int x);

void sndManager(int *a, int *b)
{
    Ee2Iop(1, a);
    Ee2Iop(2, a);
    soundVBlank(1);
    debug_DispSEInfo(1, 0);
    soundDataSegNextStageNotUseClose(a, b);
}

extern void soundSeEnvDefaultSet(int id);
extern void AdpcmFadeCloseAll(int x);
extern void soundAllocIopFree(int x);

typedef struct {
    char           _pad[0x188];
    unsigned short f_188;
    char           _pad2[6];
} SndEnt; /* stride 0x190 */
extern SndEnt D_005EBC48[];

void func_00143298(int id)
{
    unsigned int p;
    soundSeEnvDefaultSet(id);
    AdpcmFadeCloseAll(0);
    p = id * 0x190;
    p += (unsigned int)D_005EBC48;
    soundAllocIopFree(*(unsigned short *)(p + 0x188));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001432E0);

extern void ExecIcoMisc(int a0, int a1);

void func_001433E0(int *a0) {
    ExecIcoMisc(a0[3], a0[2]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001433F0);

typedef struct { char pad[0x330]; float unk330; } Sub678;
typedef struct { char pad[0x678]; Sub678 *unk678; } Sub164;
typedef struct {
    char pad8[8];
    int unk8;
    int unkC;
    char pad10[0x164 - 0x10];
    Sub164 *unk164;
} St1434;
typedef struct { char pad24[0x24]; int unk24; } St55;
typedef struct { long long a, b; } V16;
extern void func_001433F0(int a0, void *a1, void *a2);
extern int func_00260568(void *dst, int val, int size);
extern void func_00191DB8(void *a0, float f);
extern void func_0023FFF0(void *dst, void *a, void *b);
extern int disp_memory_partition_bar(int a0, int a1, int a2, void *a3, void *a4);
extern St55 D_0055A2D8[];
extern void *D_00629DE8;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001434C0);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143610);

extern void *D_00629DE4, *D_00629DE8;
extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void func_001438A8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 5, D_00629DE8, 0, 0);
}

void func_001438C8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 0, 0, 0, 0);
}

extern void ACTLookTargetSystem_Exec(void);
extern char D_005521D0[];

void func_001438E8(void) {
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_005521D0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143910);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143B00);

extern void setParticleEffect(int a0, int a1, int a2);

void func_00143DB8(void *a0) {
    int x = *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0x1B8);
    if (x) {
        setParticleEffect(0x1B0, x, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143DE0);

extern void traceLine(int a0, int a1, int a2, void *a3, int a4);
extern int DebugDisp1CollisionWithColor(void *a0, int a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern char D_00552230[];
extern int D_0062AF84;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143FB0);

extern void ActPara_GetDefTbl(void *a0, int a1);

void func_001440F0(void *a0) {
    SndState *p = *(SndState **)((char *)a0 + 0x164);
    p->f_80 = 0;
    ActPara_GetDefTbl(a0, 0);
}

extern float pac_DispQW(void);
extern void func_0014A510(void *a0, int a1, int a2);
extern void *func_0014A6A8(void);
extern void func_001E19A8(void *a0, void *a1, void *a2, int a3, int a4);

typedef struct {
    char _0[0x5C];
    int f_5C;   /* 0x5C */
    int f_60;   /* 0x60 */
} SndBrain670;

typedef struct {
    char _0[0x20];
    long long f_20; /* 0x20 */
    char _28[0x80 - 0x28];
    int f_80;   /* 0x80 */
    int f_84;   /* 0x84 */
} SndActState;

typedef struct {
    char _0[0x80];
    int f_80;   /* 0x80 */
    char _84[0x670 - 0x84];
    SndBrain670 *p_670; /* 0x670 */
    char _674[0x678 - 0x674];
    void *p_678;    /* 0x678 */
} SndActView;

typedef struct {
    char _0[0x470];
    int f_470;  /* 0x470 */
    char _474[0x490 - 0x474];
    int f_490;  /* 0x490 */
    char _494[0x4BC - 0x494];
    int f_4BC;  /* 0x4BC */
} SndDObj;

typedef struct {
    char _0[0x15C];
    int f_15C;  /* 0x15C */
    char _160[0x190 - 0x160];
} SndOrientEntry;

extern SndOrientEntry D_0055DA10[];

void func_00144100(void *self) {
    SndActState *p = (SndActState *)*(int *)((char *)self + 0x164);
    int var_6 = 0;

    if ((int)(p->f_20 << 0x1D >> 0x20) & 1) {
        p->f_80 |= 0x10;
    }
    if (p->f_80 != p->f_84) {
        p->f_84 = p->f_80;
        var_6 = 1;
    }
    if (((SndActView *)*(int *)((char *)self + 0x164))->p_670->f_5C++ >= 0x79) {
        SndDObj *d = *(SndDObj **)((char *)self + 0x15C);
        if (((d->f_470 & 0x16) != 0 || d->f_4BC != 0) &&
            D_0055DA10[d->f_490].f_15C == 1) {
            ((SndActView *)*(int *)((char *)self + 0x164))->p_670->f_5C = 0;
            ((SndActView *)*(int *)((char *)self + 0x164))->p_670->f_60 =
                (int)(pac_DispQW() * 10.0f);
            var_6 = 1;
        }
    }
    ((SndActView *)*(int *)((char *)self + 0x164))->f_80 |= 2;
    if (var_6) {
        SndActView *q2 = (SndActView *)*(int *)((char *)self + 0x164);
        void *r;
        func_0014A510(q2->p_678, p->f_80, q2->p_670->f_60);
        p = *(SndActState **)((char *)self + 0x164);
        r = func_0014A6A8();
        func_001E19A8(self, ((SndActView *)p)->p_678, r, 0, 3);
    }
}


extern float ClearHandCameraCorrect(void *a0, void *a1);
extern void *ContinueCorrectPosition(void *a0);
extern int funcEnemyCarryFail(void *a0);
extern void *isysGObjSearchFromObjKindID_begin(void *obj);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern int D_00271240[];
extern float D_0062C3C4_a[] __asm__("D_0062C3C4");

typedef struct {
    char _0[0x10];
    int  f_10;
    char _14[0x70 - 0x14];
    int  f_70;
    char _74[0xC];
} SndCorr;

void func_00144260(void *a0) {
    SndCorr *snd = *(SndCorr **)((char *)a0 + 0x164);
    int n70 = snd->f_70;

    func_00260568((char *)snd + 0x54, 0, 0x2C);
    if (a0 == D_00629DE4 || a0 == D_00629DE8) {
        float best_d = D_0062C3C4_a[0];
        void *best = 0;
        void *o = isysGObjSearchFromObjLayoutID(4);
        if (o != 0) {
            do {
                void *cp = ContinueCorrectPosition(a0);
                void *cp2 = ContinueCorrectPosition(o);
                float d = ClearHandCameraCorrect(cp, cp2);
                if (funcEnemyCarryFail(o) != 0 && d < best_d) {
                    best_d = d;
                    best = o;
                }
                o = isysGObjSearchFromObjKindID_begin(o);
            } while (o != 0);
        }
        snd->f_70 = (int)best;
        if (a0 == D_00629DE4 && n70 != 0) {
            int q = (0x3C - D_00271240[0] * 10) / D_00271240[1];
            if (snd->f_10 % (q * 2) != 0) {
                snd->f_70 = n70;
            }
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001443B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144440);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001446F8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001449B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144C10);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552210;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552240;  /* stride 0x4 */

/* end struct shapes */
