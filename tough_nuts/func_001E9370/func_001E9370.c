#include "common.h"

extern char *stage_SetLocalizeGeometry(void *a0);
extern void mc_TransMicroCode(void *a0, void *a1);
extern void GetInverseQuaternion(void *a0, void *a1);
extern void EntryMultiBgaManagerSensitive(void *a0, int a1, void *a2, void *a3, void *a4, void *a5);
extern int D_0062B8FC;
extern char *D_00706D00[];
extern char D_007063A0[];

void InitStageMultiBgaManager(void *a0, void *a1, void *a2, void *a3) {
    char *r = stage_SetLocalizeGeometry(a0);
    D_00706D00[D_0062B8FC] = r;
    mc_TransMicroCode(r + 0x20, a1);
    GetInverseQuaternion(D_00706D00[D_0062B8FC] + 0x30, a2);
    EntryMultiBgaManagerSensitive(D_007063A0, D_0062B8FC++, a0, a1, a2, a3);
    if (D_0062B8FC >= 30) {
        D_0062B8FC = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", EntryStageMultiBgaManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", EntryStageMultiBgaManagerSensitive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", auraInspireBefore);

extern void gif_SetGsReg(int a0, long long a1);
extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_MakeLine2DOffset(void *a0, int a1, void *a2, void *a3, int a4);
extern int D_00271240[];
extern int D_004C2220[];
extern int D_00629F5C;
extern int D_00629F60;
extern int D_00706D78[];
extern int D_0062B948;

typedef struct { char b[16]; } Q16;

typedef struct {
    int f_0;
    int f_4;
    int f_8;
    int f_C;
    int f_10;
    int f_14;
} S78;

void func_001E9370(void) {
    Q16 q;
    Q16 pt[3];
    int *bi = (int *)&pt[1];
    int uninit;
    int t7 = (D_00271240[0] == 0) ? 0x700 : 0x800;

    *(volatile int *)&q = uninit;
    bi[1] = D_00706D78[1] + 0x10;
    bi[0] = D_00706D78[0] + 0x10;
    bi[3] = (D_00629F60 << 4) + D_00706D78[3];
    bi[2] = (D_00629F5C << 4) + D_00706D78[2];
    pt[0] = pt[1];
    bi[7] = t7;
    bi[5] = D_00706D78[5] - 0x400;
    bi[4] = D_00706D78[4] - 0x800;
    bi[6] = 0x1000;
    pt[1] = pt[2];
    gif_SetGsReg(6, D_004C2220[1] | ((long long)(D_00629F5C / 64) << 14) | ((long long)0xCC80 << 19));
    gif_MakeSprite(D_004C2220[0], 0, 0x100, 0x80, 0, 0);
    gif_SetAlpha(1, 5, 0);
    gif_MakeLine2DOffset(&pt[1], 0, &pt[0], &D_0062B948, 1);
}


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E94E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9618);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", blendWork0ToWork1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", parallelAddFeedBackAreaToWork0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", blurBlendFeedBackAreaToWork1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9BD0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9D28);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9E30);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", cleanUpFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA488);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", dispSun);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA658);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA798);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
    unsigned int       f_2C;  /* 0x2C */
} S_00706D78;

/* end struct shapes */
