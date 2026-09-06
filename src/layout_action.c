#include "common.h"

struct S40 { char b[0x40]; };

typedef struct {
    int _0;
    int flags;
    char _8[0x50];
} R58;

typedef struct {
    unsigned int _0;
    int _4;
} R8;

void POSITIVE_SE(void) {
    soundSeDefPlay(0x19C, 0xFFFFFFFE, 0, 0);
}
void NEGATIVE_SE() {
    soundSeDefPlay(0x19D, 0xFFFFFFFE, 0, 0);
}
void CUR_SE(void) {
    soundSeDefPlay(0x19B, 0xFFFFFFFE, 0, 0);
}
extern R58 D_0028F8F0[];

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * PSH_POSITIVE_OR_NEGATIVE (line 730) into the two la_save_confirm_no_*
 * actions, so it is a public `inline` of the deferred tail; until the tail's
 * asm members are C its copy is emitted as a plain function at its ROM
 * position (before keyconfig_reset) and the callers inline this static
 * stand-in, which collapses at layout. */
static inline int pshPositiveOrNegative(int idx)
{
    int v = D_0028F8F0[idx].flags;
    if ((v & 0x40) != 0) goto one;
    if ((v & 0x10) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
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
extern int D_0063B4D0;
extern int D_0028F4EC[];
extern int layout_boot_flag;
extern int D_0063B4F4;
extern void lt_set_item_select_func(int a0);

int la_boot_memory_card_check(void)
{
    if (D_0063B4D0 == 0) {
        return -1;
    }
    D_0028F4EC[0] = 7;
    layout_boot_flag = 1;
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    return 0x37;
}
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
extern int D_0028F4D4[];
extern int lock_execIcoMisc;
extern int D_0063C3CC;
extern int layout_boot_flag;
extern void stgmgrNextStagePreLoadForceStageSet(int val);
extern void iosPadEnable(void);
extern void isysGObjActiveLink(int bit, int set);
extern void gflagOff(int a0);

int la_scei_logo(int a0)
{
    if (a0) {
        stgmgrNextStagePreLoadForceStageSet(0);
        D_0063C3CC = lock_execIcoMisc;
        D_0028F4D4[0] = 1;
        iosPadEnable();
        isysGObjActiveLink(0, 0);
        gflagOff(0x182);
        if (layout_boot_flag == 0) {
            layout_boot_flag = 1;
        }
    }
    return -1;
}
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
extern int D_0063B4E0;
int la_mc_current_slot(void) {
    lt_mask_property(0xB0, D_0063B4E0);
    lt_mask_property(0xB1, D_0063B4E0 ^ 1);
    return -1;
}
extern R8 D_0071D900[];
extern R8 *D_0063B4D8;
extern int D_0063B4DC;
extern int D_0063B4E0;
extern int D_0063B4F4;
extern void _la_mask_preview_info(void);
extern int lt_current_property_item(void);
extern void lt_set_item_select_func(int a0);

int la_mc_load_current_slot_select(void)
{
    _la_mask_preview_info();
    if (D_0028F8F4[0] & 0x40) {
        D_0063B4E0 = lt_current_property_item() - 0xBA;
        D_0063B4DC = D_0063B4E0;
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        POSITIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x13;
    }
    if (D_0028F8F4[0] & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0xC;
    }
    return -1;
}
extern R8 D_0071D900[];
extern R8 *D_0063B4D8;
extern int D_0063B4DC;
extern int D_0063B4E0;
extern int D_0063B4F4;
extern int lt_current_property_item(void);
extern void lt_set_item_select_func(int a0);

int la_mc_save_current_slot_select(void)
{
    if (D_0028F8F4[0] & 0x40) {
        POSITIVE_SE();
        D_0063B4E0 = lt_current_property_item() - 0xBA;
        D_0063B4DC = D_0063B4E0;
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    if (D_0028F8F4[0] & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    return -1;
}
extern int lt_current_property_item(void);

int la_general_mc_confirm(void)
{
    if (D_0028F8F4[0] & 0x40) {
        return lt_current_property_item();
    }
    return -1;
}
extern int mc[];
extern int D_0063B4F4;
extern int D_0063B528;
extern R8 *D_0063B4D8;
extern int _la_set_current_port_lock_2(void *p, int a1);
extern void lt_set_item_select_func(int a0);

int la_save_confirm_no_memory_card(int a0)
{
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}
extern int mc[];
extern int D_0063B4F4;
extern int D_0063B528;
extern R8 *D_0063B4D8;
extern int _la_set_current_port_lock_2(void *p, int a1);
extern void lt_set_item_select_func(int a0);

int la_save_confirm_no_free_area(int a0)
{
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((D_0063B4D8->_0 >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1F;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 4) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}
extern int D_0063B5C8;
extern int D_0063B4E0;
extern int D_0063B4F4;
extern int mc[];
extern void iosMcFormat(void *a0);
extern int iosMcSync(unsigned long *a0);
extern int _la_mcard_error_check(void *a0);
extern void lt_set_item_select_func(int a0);

int la_format_processing(int a0)
{
    if (a0) {
        D_0063B5C8 = 0;
    }
    switch (D_0063B5C8) {
    case 0:
        mc[2] = D_0063B4E0;
        mc[3] = 0;
        iosMcFormat(mc);
        D_0063B5C8++;
        break;
    case 1:
    case 3:
        if (iosMcSync((unsigned long *)mc) == 0) {
            break;
        }
        D_0063B5C8++;
        break;
    case 2:
        if (_la_mcard_error_check(mc) > 0) {
            D_0063B5C8++;
            break;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x2D;
    case 4:
        D_0063B5C8++;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x27;
    }
    return -1;
}
struct S14 { int w[5]; };
extern int D_0071D910[];
extern int D_0029B9D0[];
extern int D_0028F4D4[];
extern int D_0061DC40[];
extern int D_0061DC58[];
extern int D_0063B4F0;
extern int D_0063B4E4;
extern int D_0063B4EC;
extern int D_0063B4F4;
extern void _la_set_preview_info(void);
extern void debug_StdPrintfDummy();
extern void lt_set_item_select_func(int a0);

int la_save_confirm_complete(int a0, int a1)
{
    if (a0) {
        *(struct S14 *)D_0071D910 = *(struct S14 *)D_0029B9D0;
        D_0063B4F0 = 0x3FF;
        _la_set_preview_info();
        debug_StdPrintfDummy(D_0061DC40, D_0063B4F0, D_0063B4E4);
    }
    if (a1 != -1) {
        debug_StdPrintfDummy(D_0061DC58, 0x108, 0x109, a1);
    }
    switch (a1) {
    case 0x108:
        D_0028F4D4[0] = 0;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x36;
    case 0x109:
        D_0063B4EC = 1;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x3F;
    }
    return -1;
}
int la_save_confirm_fail(void) {
    return -1;
}
int la_format_confirm_fail(void)
{
    return -1;
}
extern int mc[];
extern int D_0063B4F4;
extern int D_0063B4E8;
extern R8 *D_0063B4D8;
extern int _la_set_current_port_2(void *p, int a1);
extern void lt_set_item_select_func(int a0);

int la_delete_start_check(int a0)
{
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    case 1:
        if ((D_0063B4D8->_4 >> D_0063B4E8) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x31;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    return -1;
}
extern int D_0063B4F4;
int la_delete_confirm(int a0, int a1) {
    switch (a1) {
    case 0xD6:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x32;
    case 0xD7:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    }
    return -1;
}
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
extern int stage_no;
extern int title_demo_mode;
extern int D_0063B5F0;
extern int D_0063B4EC;
extern int D_0063B4F4;
extern int D_0028F8F4[];
extern int D_0061DC68[];
extern void iosPadDisable(void);
extern int gflagChk(int a0);
extern void gflagOff(int a0);
extern void debug_StdPrintfDummy();
extern void stgmgrForceSwitchWithFade(float a0, float a1, int a2);
extern void lt_set_item_select_func(int a0);

int la_game_demo(int a0)
{
    if (a0) {
        if (stage_no == 1) {
            iosPadDisable();
        }
    }
    if ((D_0028F8F4[0] & 0x800) && gflagChk(0x184)) {
        debug_StdPrintfDummy(D_0061DC68);
        gflagOff(0x184);
        title_demo_mode ^= 1;
        D_0063B4EC = D_0063B5F0;
        stgmgrForceSwitchWithFade(8.0f, 4.0f, D_0063B4EC);
        if (D_0063B5F0 == 0xFFFFFFFF) {
            D_0063B5F0 = 1;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x3F;
    }
    return -1;
}
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
extern int D_0028F4D4[];
extern int D_00534CC0[];
extern R58 D_0028F8F0[];
extern int D_0063B4F4;
extern void iosPadActStopAll(void);
extern int lt_fade_status(void);
extern int lt_current_property_item(void);
extern void adpcmPauseRequest(int a0);
extern void lt_set_item_select_func(int a0);

int la_game_pause(int a0)
{
    if (a0) {
        D_0028F4D4[0] = 1;
        iosPadActStopAll();
        D_00534CC0[0] = 0x134;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if (((D_0028F8F0[0].flags & 0x40) && lt_current_property_item() == 0x127)
        || (D_0028F8F0[0].flags & 0x810)) {
        NEGATIVE_SE(0);
        adpcmPauseRequest(0);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x36;
    }
    return -1;
}
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
extern struct S40 D_0029BC00;
extern struct S40 D_0061D968;

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
void keyconfig_reset(void) {
    struct S40 tmp;
    tmp = D_0061D968;
    D_0029BC00 = tmp;
}
typedef struct {
    int _0;
    char _4[0x10];
} R14;

typedef struct {
    R14 f[20];
    char _190[0x60];
} R1F0;

extern R1F0 D_0029B5F0[];
extern int D_0063B550;
extern void lt_analog2Pad(void);

int la_mc_saved_file_select(int a0)
{
    int i = a0 - 0x3E;
    int old = i;

    lt_analog2Pad();
    do {
        if (D_0028F8F4[0] & 0x1000) {
            i += 5;
        } else if (D_0028F8F4[0] & 0x4000) {
            i -= 5;
        } else if (D_0028F8F4[0] & 0x8000) {
            i -= 1;
        } else if (D_0028F8F4[0] & 0x2000) {
            i += 1;
        } else if (D_0029B5F0[D_0063B550].f[i]._0 == 0xFFFFFFFF) {
            i++;
        }
        if (i < 0) {
            i += 10;
        }
        if (i >= 10) {
            i -= 10;
        }
    } while (D_0029B5F0[D_0063B550].f[i]._0 == 0xFFFFFFFF);
    if (old != i) {
        CUR_SE();
    }
    return i + 0x3E;
}
