#include "common.h"

extern void soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, int a2, int a3);

void kanbanBootMcCheck(void) {
    soundSeDefPlayWithVolumeRate(0x191, 0xFFFFFFFE, 0, 0);
}

void kanbanBootMain(void) {
    soundSeDefPlayWithVolumeRate(0x18F, 0xFFFFFFFE, 0, 0);
}

extern int D_0060F6E0[];
extern void debug_StdPrintfDummy(void *a0, ...);

void kanbanBootInit(void) {
    debug_StdPrintfDummy(D_0060F6E0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", kanbanBootStart);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE148);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE4A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE800);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE9C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AEB80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AED90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AEF78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF478);

extern void func_001ADFF8(void);
extern void func_001B4740(int a0, int a1);
extern void initSceneGObj(int a0);
extern void kanbanBootMcCheck(void);
extern int lt_set_item_select_func(void);
extern int D_002715D0[];
extern char D_00700700[];
extern int *D_0062B2F0;
extern int D_0062B2F4;
extern int D_0062B2F8;
extern int D_0062B30C;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF648);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF778);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFAE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFCB8);

extern int func_001AE800(void *a0, int a1);
extern void initSceneGObj(int a0);
extern int D_004B8240[];
extern int *D_0062B2F0;
extern int D_0062B2F8;
extern int D_0062B300;
extern int D_0062B308;
extern int D_0062B30C;
extern int D_0062B368;
extern int D_0062C1A4;

int func_001AFE88(int a0) {
    int temp_3;
    int temp_g;

    temp_3 = func_001AE800(D_004B8240, a0);
    if (temp_3 != 0) {
        if (temp_3 <= 0) {
            if (temp_3 == -1) {
                goto block_10;
            }
            goto ret_neg1;
        }
        if (temp_3 == 1) {
            goto block_r1;
        }
        goto ret_neg1;
    }
    D_0062B308 = 0x3FF;
    temp_g = D_0062C1A4;
    if (temp_g == 0) {
        goto ret_neg1;
    }
    if (temp_g == -0xE) {
        goto ret_neg1;
    }
    goto block_10;

block_r1:
    if (D_0062B368 == D_0062B2F8) {
        goto block_pp;
    }
block_10:
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x2A;

block_pp:
    if ((D_0062B2F0[0] & 3) == 3) {
        goto block_shift;
    }
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x13;

block_shift:
    if ((D_0062B2F0[1] >> D_0062B300) & 1) {
        D_0062B308 = 0x3FF;
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x16;
    }
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x14;

ret_neg1:
    return -1;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFF98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0388);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0898);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0A90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0D70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0EF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B1098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B1230);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B14B8);

extern int InitStageLight(void);
extern void stgmgrForceSwitchWithFade(int a0, float a1, float a2);
extern void func_00178C90(void);
extern void func_001ADFF8(void);
extern void kanbanBootMcCheck(void);
extern int lt_set_item_select_func(void);
extern float D_00629400;
extern int D_0062B304;
extern char D_0062D258[];

int func_001B1760(void) {
    int v;
    int v2;

    if (InitStageLight() != 2) {
        goto andi40;
    }
    if ((D_002715D0[1] & 0x10) == 0) {
        goto andi40;
    }
    kanbanBootMcCheck();
    v = lt_set_item_select_func();
    if (v < 0xEF) {
        goto andi40;
    }
    if (v < 0xF1) {
        goto ret25_body;
    }
    if (v >= 0x177) {
        goto andi40;
    }
    if (v < 0x175) {
        goto andi40;
    }
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x35;

andi40:
    if ((D_002715D0[1] & 0x40) == 0) {
        goto ret_neg1;
    }
    debug_StdPrintfDummy(D_0062D258, lt_set_item_select_func());
    v2 = lt_set_item_select_func();
    if (v2 == 0xF0) {
        goto ret25_mccheck;
    }
    if (v2 >= 0xF1) {
        goto high;
    }
    if (v2 != 0xEF) {
        return -1;
    }
    goto stagemgr;
high:
    if (v2 == 0x175) {
        goto stagemgr;
    }
    if (v2 != 0x176) {
        return -1;
    }
    goto ret35_mccheck;
stagemgr:
    func_001ADFF8();
    func_00178C90();
    D_0062B304 = 1;
    stgmgrForceSwitchWithFade(1, D_00629400, 4.0f);
ret25_mccheck:
    kanbanBootMcCheck();
ret25_body:
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x25;

ret35_mccheck:
    kanbanBootMcCheck();
ret35_body:
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x35;

ret_neg1:
    return -1;
}



/* recovered struct shapes */
typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_40;  /* 0x40 */
    unsigned long long f_9C0;  /* 0x9C0 */
} S_004B8240;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_140;  /* 0x140 */
    unsigned int       f_144;  /* 0x144 */
    unsigned int       f_148;  /* 0x148 */
} S_0027CFE0;  /* stride 0x18C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    short              f_4;  /* 0x04 */
    char               f_5;  /* 0x05 */
} S_0062D1A8;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_0027D2F8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_00700700;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_bl_0060F860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060F7D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060F8C0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060F9D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FB00;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FB40;  /* stride 0x4 */

/* end struct shapes */
