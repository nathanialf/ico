#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", POSITIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", NEGATIVE_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", CUR_SE);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_TESTFUNCTION);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", _la_mcard_error_check);


extern void init_layout_texture(void);
extern void kanbanBootMain(void);
extern void kanbanBootMcCheck(void);
extern void GetRealModelId(int a0, int a1);
extern void func_001ADFF8(void);
extern int initSceneGObj(int a0);
typedef struct { int _0; int f4; char _8[0x50]; } LaFlags;
extern LaFlags D_002715D0;
typedef struct { char _0[0x2C]; int f2C; } LaMcState;
extern LaMcState D_00271240;
extern int D_0062B30C;

int _la_memory_card_check(void) {
    int i;
    int v;

    init_layout_texture();
    if (D_002715D0.f4 & 0x8000) {
        v = D_00271240.f2C;
        if (v > 0) {
            kanbanBootMain();
            D_00271240.f2C = v - 1;
        }
    } else if (D_002715D0.f4 & 0x2000) {
        v = D_00271240.f2C;
        if (v < 0xE) {
            kanbanBootMain();
            D_00271240.f2C = v + 1;
        }
    }
    if (D_002715D0.f4 & 0x10) {
        kanbanBootMcCheck();
        D_00271240.f2C = 7;
    }
    for (i = 0; i < 0xF; i++) {
        GetRealModelId(i + 0x158, 1);
    }
    GetRealModelId(D_00271240.f2C + 0x158, 0);
    if (D_002715D0.f4 & 0x40) {
        func_001ADFF8();
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x36;
    }
    return -1;
}


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

extern void debug_StdPrintfDummy(void *a0, ...);
extern char D_0060F8D8[];
extern char D_0060F8E8[];

int _la_set_current_port_lock_2(void *a0, int a1) {
    debug_StdPrintfDummy(D_0060F8D8);
    return a1;
}

int _la_set_current_port_new(void *a0, int a1) {
    debug_StdPrintfDummy(D_0060F8E8);
    return a1;
}

extern int D_002715D4[];
extern int lt_set_fade_mode(int a0);

int la_boot_confirm_memory_card(void)
{
    if (D_002715D4[0] & 0x40) {
        return lt_set_fade_mode(0);
    }
    return -1;
}

extern void stgmgrNextStagePreLoadForceStageSet(int a0);
extern void iosPadDisable(void);
extern void func_0013E828(int a0, int a1);
extern void func_00178E08(int a0);
extern int D_00629D00;
extern int D_0062C18C;
extern int D_00271254[];

int la_title_continue_or_new(int a0) {
    if (a0 != 0) {
        stgmgrNextStagePreLoadForceStageSet(0);
        D_0062C18C = D_00629D00;
        D_00271254[0] = 1;
        iosPadDisable();
        func_0013E828(0, 0);
        func_00178E08(0x160);
        if (D_0062B31C == 0) {
            D_0062B31C = 1;
        }
    }
    return -1;
}

int la_title_new_game_only(void) {
    return -1;
}

typedef struct { int d[4]; } LaPrev16;

extern int lt_set_item_select_func(void);
extern void func_001B4740(int a0, int a1);
extern int D_0062B2FC;
extern int D_0062B308;
extern int D_0062B30C;
extern int D_0062B368;
extern int D_0062B420;
extern char D_0027CFE0[];
extern char D_00700710[];

int _la_set_preview_info(void) {
    int i;
    int ret;

    D_0062B2FC = lt_set_item_select_func() - 0x1B;
    if (D_0062B30C == 0) {
        D_0062B420 = 1;
        return -1;
    }
    for (i = 0; i < 10; i++) {
        if (((D_0062B308 >> i) & 1) &&
            *(unsigned int *)(D_0027CFE0 + i * 16 + D_0062B368 * 396) != 0xFFFFFFFFU) {
            func_001B4740(i + 0x1B, 0);
            func_001B4740(i + 0x11, 1);
        } else {
            func_001B4740(i + 0x1B, 1);
            func_001B4740(i + 0x11, 0);
        }
    }
    *(LaPrev16 *)&D_00700710 = *(LaPrev16 *)(D_0027CFE0 + D_0062B368 * 396 + D_0062B2FC * 16);
    ret = -1;
    if (D_002715D0.f4 & 0x50) {
        ret = D_0062B2FC;
    }
    return ret;
}


extern int D_0062B308;
extern int D_0062B2FC;
extern void func_001AF120(void);

int la_mc_preview_info(void) {
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

int la_general_mc_confirm(void) {
    if (D_002715D4[0] & 0x40) {
        return lt_set_item_select_func();
    }
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_confirm_no_data);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_start_check);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/layout_action", la_load_processing);

extern void debug_StdPrintfDummy(void *a0, ...);
extern void func_001AF120(void);
extern int initSceneGObj(int a0);
extern char D_00700710[];
extern char D_0027D2F8[];
extern char D_0060FB70[];
extern char D_0060FB88[];
extern int D_0062B308;
extern int D_0062B2FC;
extern int D_00271254[];
extern int D_0062B304;
extern int D_0062B30C;

int la_mc_confirm_save_file(int a0, int a1) {
    if (a0 != 0) {
        __builtin_memcpy(D_00700710, D_0027D2F8, 0x10);
        D_0062B308 = 0x3FF;
        func_001AF120();
        debug_StdPrintfDummy(D_0060FB70, D_0062B308, D_0062B2FC);
    }
    if (a1 != -1) {
        debug_StdPrintfDummy(D_0060FB88, 0xE9, 0xEA, a1);
    }
    switch (a1) {
    case 0xE9:
        D_00271254[0] = 0;
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x32;
    case 0xEA:
        D_0062B304 = 1;
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x3B;
    }
    return -1;
}

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

int la_game_loading(int a0) {
    if (a0) {
        D_00271258[0] = 1;
    }
    return -1;
}

extern int D_00629C90;
extern int D_002715D4[];
extern int D_0062B35C;
extern int D_0062B3F0;
extern int D_0062B304;
extern int D_0062B30C;
extern char D_0060FB98[];
extern int iosPadEnableGet(void);
extern int func_00178DB0(int a0);
extern void func_00178E08(int a0);
extern void debug_StdPrintfDummy(void *a0, ...);
extern void stgmgrForceSwitchWithFade(int a0, float a1, float a2);
extern int initSceneGObj(int a0);

int la_save_processing(int a0) {
    if (a0 != 0) {
        if (D_00629C90 == 1) {
            iosPadEnableGet();
        }
    }
    if ((D_002715D4[0] & 0x800) == 0) {
        return -1;
    }
    if (func_00178DB0(0x162) != 0) {
        debug_StdPrintfDummy(D_0060FB98);
        func_00178E08(0x162);
        D_0062B35C ^= 1;
        D_0062B304 = D_0062B3F0;
        stgmgrForceSwitchWithFade(D_0062B3F0, 8.0f, 4.0f);
        if (D_0062B3F0 == 0xFFFFFFFF) {
            D_0062B3F0 = 1;
        }
        initSceneGObj(0);
        D_0062B30C = 0;
        return 0x3B;
    }
    return -1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060FBB0;  /* stride 0x4 */

/* end struct shapes */
