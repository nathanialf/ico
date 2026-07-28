#include "common.h"




extern unsigned int D_00633150;
typedef struct {
    int _0;
    int flags;
    char _8[0x50];
} R58;
extern R58 D_00275250[];
extern int D_00275254[];
extern int D_0063304C;
extern int D_00274ED4[];
extern void initSceneGObj(int val);
int display_texture_fade_cancel_chk(int a0) {
    if (a0) {
        D_00274ED4[0] = 1;
    }
    if ((D_00275254[0] & 0x800) == 0) {
        return -1;
    }
    initSceneGObj(0);
    D_0063304C = 0;
    return 0x33;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_analog2Pad);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", default_item_select);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", texture_fading);

int func_001B59D0(int idx)
{
    int v = D_00275250[idx].flags;
    if ((v & 0x40) != 0) goto one;
    if ((v & 0x10) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", display_primary_texture_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", exec_layout_texture);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B5C38);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", init_layout_texture);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_switch_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_current_property_item);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_link_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_prev_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_next_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_mask_property);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_default_mask_property);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_fade_status);

int lt_set_item_select_func(void) {
    return D_00633150;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_set_fade_mode);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B7100);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B7190);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B7218);

