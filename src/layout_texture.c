#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", display_texture_fade_cancel_chk);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_analog2Pad);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", default_item_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", texture_fading);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001BF960);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", display_primary_texture_layout);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", exec_layout_texture);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001C09A8);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", init_layout_texture);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_switch_layout);
extern unsigned int D_0063B610;

int lt_current_property_item(void) {
    return D_0063B610;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_link_layout);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_prev_layout);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_next_layout);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_mask_property);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_default_mask_property);
extern int D_0063B618;

int lt_fade_status(void) {
    return D_0063B618;
}
extern int D_0063B624;

void lt_set_item_select_func(int val) {
    D_0063B624 = val;
}
extern int D_0063B61C;

void lt_set_fade_mode(int val) {
    D_0063B61C = val;
}
