#include "common.h"

/* soundManager 0x164 actor-state view (local) */
typedef struct { char _0[0x80]; int f_80; } SndState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndBgmReadyNextStage);

extern void debug_StdPrintfDummy();
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
            debug_StdPrintfDummy((int)D_00552178, *(short *)(e + 0x10),
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
extern void soundReverbDepthSet(int x);

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
    soundReverbDepthSet(*(unsigned short *)(p + 0x188));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001432E0);

extern void gamesysObjInfoCls(int a0, int a1);

void func_001433E0(int *a0) {
    gamesysObjInfoCls(a0[3], a0[2]);
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
extern void memset(void *dst, int val, int size);
extern void func_00191DB8(void *a0, float f);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern int disp_memory_partition_bar(int a0, int a1, int a2, void *a3, void *a4);
extern St55 D_0055A2D8[];
extern void *D_00629DE8;

void func_001434C0(St1434 *arg0, int arg1) {
    int buf0[4];
    float buf10[4];
    float t1[4];
    long long t2[2];
    long long e[2];

    func_001433F0(arg1, buf0, buf10);
    if (arg0->unkC == 0x11) {
        memset(t1, 0, 0x10);
        t1[2] = 250.0f;
        func_00191DB8(t1, -buf10[1]);
        sceVu0AddVector(buf0, buf0, t1);
    }
    if (arg0 == (St1434 *) D_00629DE8) {
        if (0.0f <= arg0->unk164->unk678->unk330) {
            memset(e, 0, 0x10);
            *(float *) ((char *) e + 8) = -((St1434 *) D_00629DE8)->unk164->unk678->unk330;
            *(V16 *) t2 = *(V16 *) e;
            func_00191DB8(t2, -buf10[1]);
            sceVu0AddVector(buf0, buf0, t2);
        }
    }
    disp_memory_partition_bar(arg0->unk8, arg0->unkC,
                              D_0055A2D8[arg1].unk24,
                              buf0, buf10);
}


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
    debug_StdPrintfDummy(D_005521D0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143910);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143B00);

extern void DispMultiBgaManagerWithKind(int a0, int a1, int a2);

void func_00143DB8(void *a0) {
    int x = *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0x1B8);
    if (x) {
        DispMultiBgaManagerWithKind(0x1B0, x, 1);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144260);

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
