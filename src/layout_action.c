#include "common.h"











extern int D_00280F78[];
extern int D_00274ED8[];
extern int D_0063304C;
extern void initSceneGObj(int val);
extern int lt_set_item_select_func(void);
extern void func_001B7218();
extern int D_00633038;
extern int D_0063303C;
extern void func_001B1B90();
extern int D_00633048;
extern void iosPadDisable(void);
extern void func_0017B288(int bit_idx);
extern void stgmgrForceSwitchWithFade(int val);
extern int D_0063305C;
extern int D_00633E9C;
extern void func_0013ED40(int bit, int set);
extern int D_00631A00;
extern int D_00274ED4[];
extern int D_00275254[];
extern int lt_set_fade_mode();
extern int D_00616EE8[];
extern int D_00616ED8[];
extern void debug_assertMessage();
INCLUDE_ASM("asm/nonmatchings/src/layout_action", POSITIVE_SE);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", NEGATIVE_SE);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", CUR_SE);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_TESTFUNCTION);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_mcard_error_check);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_memory_card_check);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_current_port_2);

int _la_set_current_port_lock_2(int a0, int a1)
{
    debug_assertMessage(D_00616ED8);
    return a1;
}

int _la_set_current_port_new(int a0, int a1)
{
    debug_assertMessage(D_00616EE8);
    return a1;
}

int la_vibe_select(void)
{
    if (D_00275254[0] & 0x40) {
        return lt_set_fade_mode(0);
    }
    return -1;
}

int la_title_continue_or_new(int a0)
{
    if (a0 != 0) {
        int v;
        stgmgrForceSwitchWithFade(0);
        v = D_00631A00;
        D_00274ED4[0] = 1;
        D_00633E9C = v;
        iosPadDisable();
        func_0013ED40(0, 0);
        func_0017B288(0x161);
        if (D_0063305C == 0) {
            D_0063305C = 1;
        }
    }
    return -1;
}

int la_title_new_game_only(void) {
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_preview_info);

int la_load_game_memory_card_check(void) {
    if (D_00633048 == 0) {
        if ((1 >> D_0063303C) & 1) {
            return -1;
        }
    }
    func_001B1B90();
    return -1;
}

int la_mc_load_current_slot_select(void)
{
    func_001B7218(0x8C, D_00633038);
    func_001B7218(0x8D, D_00633038 ^ 1);
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_load_file_select);

int la_load_confirm_no_memory_card(void)
{
    if (D_00275254[0] & 0x40) {
        return lt_set_item_select_func();
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_confirm_no_data);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_start_check);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_processing);

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_confirm_save_file);

int la_save_game_memory_card_check(void) {
    return -1;
}

int progressive_bar(void)
{
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_save_file_select);

int la_save_start_check(int a0, int a1)
{
    int ret;
    if (a1 == 0xB7) goto path_b7;
    if (a1 == 0xB8) goto path_b8;
    return -1;
path_b7:
    initSceneGObj(0);
    D_0063304C = 0;
    ret = 0x2E;
    goto out;
path_b8:
    initSceneGObj(0);
    D_0063304C = 0;
    ret = 0x1A;
out:
    return ret;
}

int la_save_confirm_overwrite(void)
{
    int ret;
    if ((D_00275254[0] & 0x10) == 0) goto fail;
    initSceneGObj(0);
    D_0063304C = 0;
    ret = 0x1A;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}

int la_format_confirm(void)
{
    return -1;
}

int la_system_save_processing(int a0) {
    if (a0 != 0) {
        D_00274ED8[0] = 1;
    }
    return -1;
}

void func_001B5788(void)
{
    if (D_00274ED4[0] != 0) {
        return;
    }
    D_00280F78[1]++;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_action", func_001B57B0);

