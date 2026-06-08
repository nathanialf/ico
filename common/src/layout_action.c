#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", POSITIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", NEGATIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", CUR_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_TESTFUNCTION);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_mcard_error_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_memory_card_check);

extern int D_0062B2E8;
extern int D_0062B31C;
extern int D_0027126C[];
extern int D_0062B30C;
extern int initSceneGObj(int a0);

int _la_set_current_port_2(void)
{
  if (D_0062B2E8 == 0)
  {
    return -1;
  }
  D_0027126C[0] = 7;
  D_0062B31C = 1;
  initSceneGObj(0);
  D_0062B30C = (float) 0;
  return 0x33;
}

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

extern int D_002715D4[];
extern int lt_set_fade_mode(int a0);

int la_vibe_select(void)
{
    if (D_002715D4[0] & 0x40) {
        return lt_set_fade_mode(0);
    }
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_title_continue_or_new);

int la_title_new_game_only(void) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_set_preview_info);

extern int D_0062B308;
extern int D_0062B2FC;
extern void func_001AF120(void);

int la_load_game_memory_card_check(void) {
    if (D_0062B308 == 0) {
        if ((1 >> D_0062B2FC) & 1) {
            return -1;
        }
    }
    func_001AF120();
    return -1;
}

extern int D_0062B2F8;
extern void func_001B4740(int a0, int a1);

int la_mc_load_current_slot_select(void) {
    func_001B4740(0x8C, D_0062B2F8);
    func_001B4740(0x8D, D_0062B2F8 ^ 1);
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_mc_load_file_select);

extern int lt_set_item_select_func(void);

int la_load_confirm_no_memory_card(void) {
    if (D_002715D4[0] & 0x40) {
        return lt_set_item_select_func();
    }
    return -1;
}

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

extern int D_0062B30C;

int la_save_start_check(int a0, int a1)
{
    int ret;
    if (a1 == 0xB7) goto path_b7;
    if (a1 == 0xB8) goto path_b8;
    return -1;
path_b7:
    initSceneGObj(0);
    D_0062B30C = 0;
    ret = 0x2E;
    goto out;
path_b8:
    initSceneGObj(0);
    D_0062B30C = 0;
    ret = 0x1A;
out:
    return ret;
}

extern int D_002715D4[];

int la_save_confirm_overwrite(void)
{
    int ret;
    if ((D_002715D4[0] & 0x10) == 0) goto fail;
    initSceneGObj(0);
    D_0062B30C = 0;
    ret = 0x1A;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}

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
