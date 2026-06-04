#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", POSITIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", NEGATIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", CUR_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_TESTFUNCTION);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_mcard_error_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_memory_card_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_set_current_port_2);

extern void debug_assertMessage(void *a0);
extern char D_0060F8D8[];
extern char D_0060F8E8[];

int _la_set_current_port_lock_2(void *a0, int a1) {
    debug_assertMessage(D_0060F8D8);
    return a1;
}

int _la_set_current_port_new(void *a0, int a1) {
    debug_assertMessage(D_0060F8E8);
    return a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_vibe_select);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_title_continue_or_new);

int la_title_new_game_only(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_set_preview_info);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_game_memory_card_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_mc_load_current_slot_select);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_mc_load_file_select);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_confirm_no_memory_card);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_confirm_no_data);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_start_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_processing);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_mc_confirm_save_file);

int la_save_game_memory_card_check(void) {
    return -1;
}

int progressive_bar(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_mc_save_file_select);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_save_start_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_save_confirm_overwrite);

int la_format_confirm(void) {
    return -1;
}

extern int D_00271258[];

int la_system_save_processing(int a0) {
    if (a0) {
        D_00271258[0] = 1;
    }
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_save_processing);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FBB0;  /* stride 0x4 */

/* end struct shapes */
