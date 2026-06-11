#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", display_texture_fade_cancel_chk);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_analog2Pad);

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", func_001B2EF8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_texture", lt_fade_status);

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
