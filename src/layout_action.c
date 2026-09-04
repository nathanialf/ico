#include "common.h"

struct S40 { char b[0x40]; };

typedef struct {
    int _0;
    int flags;
    char _8[0x50];
} R58;

void POSITIVE_SE(void) {
    soundSeDefPlay(0x19C, 0xFFFFFFFE, 0, 0);
}
void NEGATIVE_SE(void) {
    soundSeDefPlay(0x19D, 0xFFFFFFFE, 0, 0);
}
void CUR_SE(void) {
    soundSeDefPlay(0x19B, 0xFFFFFFFE, 0, 0);
}
extern int D_0061D750[];
extern void debug_StdPrintfDummy();

void la_TESTFUNCTION(void) {
    debug_StdPrintfDummy(D_0061D750);
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_mcard_error_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_memory_card_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_current_port_2);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_current_port_lock_2);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_current_port_new);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_vibe_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_title_continue_or_new);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_title_new_game_only);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_file_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_mask_preview_info);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", _la_set_preview_info);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_game_memory_card_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_load_file_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_confirm_no_memory_card);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_confirm_no_data);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_start_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_load_processing);
ASM_LIT4_SLOT(D_00639360, 0.05f);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_confirm_save_file);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_game_memory_card_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", progressive_bar);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_save_file_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_start_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_confirm_overwrite);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_format_confirm);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_system_save_processing);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_processing);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_end_confirm);
ASM_LIT4_SLOT(D_00639364, 0.025f);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_delete_processing);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_game_loop);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_game_over_continue);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_key_config);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_game_option);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_adjust_screen);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_boot_memory_card_check);
extern int D_0061D948[];
extern void debug_StdPrintfDummy();

int la_boot_no_memory_card(int a0, int a1)
{
    debug_StdPrintfDummy(D_0061D948);
    return a1;
}
extern int D_0061D958[];

int la_boot_no_free_area(int a0, int a1)
{
    debug_StdPrintfDummy(D_0061D958);
    return a1;
}
extern int D_0028F8F4[];
extern int lt_link_layout();

int la_boot_confirm_memory_card(void)
{
    if (D_0028F8F4[0] & 0x40) {
        return lt_link_layout(0);
    }
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_scei_logo);
int la_title_demo(void) {
    return -1;
}
extern int D_0063B4E4;
extern int D_0063B4F0;
extern void _la_set_preview_info();

int la_mc_preview_info(void) {
    if (D_0063B4F0 == 0) {
        if ((1 >> D_0063B4E4) & 1) {
            return -1;
        }
    }
    _la_set_preview_info();
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_current_slot);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_load_current_slot_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_save_current_slot_select);
extern int lt_current_property_item(void);

int la_general_mc_confirm(void)
{
    if (D_0028F8F4[0] & 0x40) {
        return lt_current_property_item();
    }
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_confirm_no_memory_card);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_confirm_no_free_area);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_format_processing);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_save_confirm_complete);
int la_save_confirm_fail(void) {
    return -1;
}
int la_format_confirm_fail(void)
{
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_delete_start_check);
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_delete_confirm);
extern int D_0063B4F4;
extern void lt_set_item_select_func(int a0);
int la_delete_confirm_complete(void) {
    int ret;
    if ((D_0028F8F4[0] & 0x10) == 0) goto fail;
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    ret = 0x1E;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}
int la_delete_confirm_fail(void)
{
    return -1;
}
extern int D_0028F4D8[];

int la_game_loading(int a0) {
    if (a0 != 0) {
        D_0028F4D8[0] = 1;
    }
    return -1;
}
extern int D_0028F4D4[];
extern int D_0029B9D0[];
void la_playtime_count(void) {
    if (D_0028F4D4[0] == 0) {
        D_0029B9D0[2]++;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_game_demo);
extern int D_0028F4D4[];
extern int D_0063B4F4;
int la_game_demo_pause(int a0) {
    if (a0) {
        D_0028F4D4[0] = 1;
    }
    if ((D_0028F8F4[0] & 0x800) == 0) {
        return -1;
    }
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    return 0x37;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_game_pause);
extern int D_0063B4EC;
extern int fightSoundPlayChk(void);
extern void stgmgrForceSwitchWithFade(float a0, float a1, int a2);

int la_switching_stage(void) {
    if (fightSoundPlayChk() == 0) {
        stgmgrForceSwitchWithFade(0.4f, 4.0f, D_0063B4EC);
    }
    return -1;
}
int la_save_confirm_yesno(void)
{
    if (D_0028F8F4[0] & 0x10) {
        return lt_current_property_item();
    }
    return -1;
}
extern R58 D_0028F8F0[];

int PSH_POSITIVE_OR_NEGATIVE(int idx)
{
    int v = D_0028F8F0[idx].flags;
    if ((v & 0x40) != 0) goto one;
    if ((v & 0x10) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}
extern struct S40 D_0029BC00;
extern struct S40 D_0061D968;

void keyconfig_reset(void) {
    struct S40 tmp;
    tmp = D_0061D968;
    D_0029BC00 = tmp;
}
INCLUDE_ASM("asm/nonmatchings/src/layout_action", la_mc_saved_file_select);
