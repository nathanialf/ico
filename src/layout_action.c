#include "common.h"

typedef struct { int d[4]; } LaPrev16;

typedef struct { int _0; int f4; char _8[0x50]; } LaFlags;
typedef struct { char _0[0x2C]; int f2C; } LaMcState;











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

extern LaMcState D_00274EC0;
extern LaFlags D_00275250;
extern void GetRealModelId(int a0, int a1);
extern void func_001B0A68(void);
extern void init_layout_texture(void);
extern void kanbanBootMain(void);
extern void kanbanBootMcCheck(void);

int _la_memory_card_check(void) {
    int i;
    int v;

    init_layout_texture();
    if (D_00275250.f4 & 0x8000) {
        v = D_00274EC0.f2C;
        if (v > 0) {
            kanbanBootMain();
            D_00274EC0.f2C = v - 1;
        }
    } else if (D_00275250.f4 & 0x2000) {
        v = D_00274EC0.f2C;
        if (v < 0xE) {
            kanbanBootMain();
            D_00274EC0.f2C = v + 1;
        }
    }
    if (D_00275250.f4 & 0x10) {
        kanbanBootMcCheck();
        D_00274EC0.f2C = 7;
    }
    for (i = 0; i < 0xF; i++) {
        GetRealModelId(i + 0x158, 1);
    }
    GetRealModelId(D_00274EC0.f2C + 0x158, 0);
    if (D_00275250.f4 & 0x40) {
        func_001B0A68();
        initSceneGObj(0);
        D_0063304C = 0;
        return 0x36;
    }
    return -1;
}

extern int D_00274EEC[];
extern int D_00633028;

int _la_set_current_port_2(void)
{
  if (D_00633028 == 0)
  {
    return -1;
  }
  D_00274EEC[0] = 7;
  D_0063305C = 1;
  initSceneGObj(0);
  D_0063304C = (float) 0;
  return 0x33;
}

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

extern char D_00280C60[];
extern int D_006330A8;
extern int D_00633160;
extern char D_00706F10[];
extern void func_001B7218(int a0, int a1);

int _la_set_preview_info(void) {
    int i;
    int ret;

    D_0063303C = lt_set_item_select_func() - 0x1B;
    if (D_0063304C == 0) {
        D_00633160 = 1;
        return -1;
    }
    for (i = 0; i < 10; i++) {
        if (((D_00633048 >> i) & 1) &&
            *(unsigned int *)(D_00280C60 + i * 16 + D_006330A8 * 396) != 0xFFFFFFFFU) {
            func_001B7218(i + 0x1B, 0);
            func_001B7218(i + 0x11, 1);
        } else {
            func_001B7218(i + 0x1B, 1);
            func_001B7218(i + 0x11, 0);
        }
    }
    *(LaPrev16 *)&D_00706F10 = *(LaPrev16 *)(D_00280C60 + D_006330A8 * 396 + D_0063303C * 16);
    ret = -1;
    if (D_00275250.f4 & 0x50) {
        ret = D_0063303C;
    }
    return ret;
}

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

extern char D_00280F78__p4[] __asm__("D_00280F78");
extern char D_00617170[];
extern char D_00617188[];
extern int D_00633044;

int la_mc_confirm_save_file(int a0, int a1) {
    if (a0 != 0) {
        __builtin_memcpy(D_00706F10, D_00280F78__p4, 0x10);
        D_00633048 = 0x3FF;
        func_001B1B90();
        debug_assertMessage(D_00617170, D_00633048, D_0063303C);
    }
    if (a1 != -1) {
        debug_assertMessage(D_00617188, 0xE9, 0xEA, a1);
    }
    switch (a1) {
    case 0xE9:
        D_00274ED4[0] = 0;
        initSceneGObj(0);
        D_0063304C = 0;
        return 0x32;
    case 0xEA:
        D_00633044 = 1;
        initSceneGObj(0);
        D_0063304C = 0;
        return 0x3B;
    }
    return -1;
}

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

