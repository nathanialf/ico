#include "common.h"

extern int D_00271254[];
extern int D_002715D4[];
extern int D_0062B30C;
extern void initSceneGObj(int a0);

int display_texture_fade_cancel_chk(int a0) {
    if (a0) {
        D_00271254[0] = 1;
    }
    if (D_002715D4[0] & 0x800) {
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x33;
    }
    return -1;
}

extern int InitStageLight(void);
extern int lt_set_item_select_func(void);
extern void kanbanBootMcCheck(int a0);
extern void AdpcmFadeCloseAll(int a0);
extern void initSceneGObj(int a0);
extern int D_002715D0_a[] __asm__("D_002715D0");

int lt_analog2Pad(int a0) {
    int v;
    if (a0 != 0) {
        D_00271254[0] = 1;
    }
    if (InitStageLight() != 2) {
        return -1;
    }
    v = D_002715D0_a[1];
    if (v & 0x40) {
        if (lt_set_item_select_func() != 0x108) {
            v = D_002715D0_a[1];
            if ((v & 0x810) == 0) {
                return -1;
            }
        }
    } else {
        if ((v & 0x810) == 0) {
            return -1;
        }
    }
    kanbanBootMcCheck(0);
    AdpcmFadeCloseAll(0);
    initSceneGObj(0);
    D_0062B30C = 0;
    return 0x32;
}

extern int fightSoundClose(void);
extern void StageManager(float a0, float a1, int a2);
extern float D_00629404;
extern int D_0062B304;

int default_item_select(void) {
    if (fightSoundClose() == 0) {
        StageManager(D_00629404, 4.0f, D_0062B304);
    }
    return -1;
}

extern int D_002715D4[];
extern int lt_set_item_select_func(void);

int texture_fading(void)
{
    if (D_002715D4[0] & 0x10) {
        return lt_set_item_select_func();
    }
    return -1;
}

typedef struct { int _0; int f4; char pad[0x50]; } LTItem_B2EF8;
extern LTItem_B2EF8 D_002715D0[];

int func_001B2EF8(int a0){int v=D_002715D0[a0].f4;if(v&0x40)goto ret1;if(v&0x10)goto ret1;goto ret0;ret1:return 1;ret0:return 0;}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", display_primary_texture_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", exec_layout_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", func_001B3160);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", init_layout_texture);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_switch_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_current_property_item);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_link_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_prev_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_next_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_mask_property);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_default_mask_property);

extern int D_0062B418;
extern int D_0062B40C;
extern int D_0062B41C;
extern int D_0062C1B0;
extern void func_001B3160(int, int);

void lt_fade_status(int a0) {
    if ((D_0062B418 == 2 && a0 != D_0062B40C) || a0 == 0x3A) {
        D_0062C1B0 = a0;
        func_001B3160(D_0062B40C, a0);
        if (D_0062B41C == 1) {
            D_0062B418 = 5;
        } else {
            D_0062B418 = 3;
        }
    }
}

extern int D_0062B410;

int lt_set_item_select_func(void) {
    return D_0062B410;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_set_fade_mode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", func_001B4628);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", func_001B46B8);

typedef struct { char _0[0x68]; int f_68; } RealModel;
extern RealModel D_002E34F0[];

void func_001B4740(int a0, int a1) {
    RealModel *e = &D_002E34F0[a0];
    e->f_68 = (e->f_68 & ~2) | ((a1 & 1) << 1);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_64;  /* 0x64 */
    unsigned int       f_68;  /* 0x68 */
    unsigned int       f_2140;  /* 0x2140 */
    unsigned int       f_21AC;  /* 0x21AC */
} S_002E34F0;  /* stride 0x6C */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_2C;  /* 0x2C */
} S_00536530;  /* stride 0x38 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FBE0;  /* stride 0x4 */

/* end struct shapes */
