#include "common.h"

struct S40 { char b[0x40]; };




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

extern void Vibration_WaveDecode(void);
extern int InitStageLight(void);
extern int lt_set_item_select_func(void);
extern void kanbanBootMcCheck(int a0);
extern void AdpcmFadeCloseAll(int a0);

int lt_analog2Pad(int a0) {
    int v;
    if (a0 != 0) {
        D_00274ED4[0] = 1;
        Vibration_WaveDecode();
    }
    if (InitStageLight() != 2) {
        return -1;
    }
    v = D_00275250[0].flags;
    if (v & 0x40) {
        if (lt_set_item_select_func() != 0x108) {
            v = D_00275250[0].flags;
            if ((v & 0x810) == 0) {
                return -1;
            }
        }
    } else {
        if ((v & 0x810) == 0) {
            return -1;
        }
    }
    kanbanBootMcCheck(0);
    AdpcmFadeCloseAll(0);
    initSceneGObj(0);
    D_0063304C = 0;
    return 0x32;
}

extern float D_0063110C;
extern int D_00633044;
extern void StageManager(float a0, float a1, int a2);
extern int fightSoundClose(void);

int default_item_select(void) {
    if (fightSoundClose() == 0) {
        StageManager(D_0063110C, 4.0f, D_00633044);
    }
    return -1;
}

extern int lt_set_item_select_func(void);

int texture_fading(void)
{
    if (D_00275254[0] & 0x10) {
        return lt_set_item_select_func();
    }
    return -1;
}

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

extern struct S40 D_00281180;
extern struct S40 D_00616EF8;

void display_primary_texture_layout(void) {
    struct S40 tmp;
    tmp = D_00616EF8;
    D_00281180 = tmp;
}

extern int D_00280C60[];
extern int D_006330A8;
extern void init_layout_texture();
extern void kanbanBootMain(void);

int exec_layout_texture(int a0) {
    int i = a0 - 0x1B;
    int start = i;
    int prop, off;

    init_layout_texture();
    prop = D_00275254[0];
    off = D_006330A8 * 0x18C;

    do {
        if (prop & 0x1000) {
            i += 5;
        } else if (prop & 0x4000) {
            i -= 5;
        } else if (prop & 0x8000) {
            i -= 1;
        } else if (prop & 0x2000) {
            i += 1;
        } else if (*(int *)((char *)D_00280C60 + off + i * 16) == 0xFFFFFFFF) {
            i += 1;
        }
        if (i < 0) {
            i += 10;
        }
        if (i >= 10) {
            i -= 10;
        }
    } while (*(int *)((char *)D_00280C60 + off + i * 16) == 0xFFFFFFFF);

    if (start != i) {
        kanbanBootMain();
    }
    return i + 0x1B;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B5C38);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", init_layout_texture);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_switch_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_current_property_item);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_link_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_prev_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_next_layout);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_mask_property);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_default_mask_property);

extern int D_0063314C;
extern int D_00633158;
extern int D_0063315C;
extern int D_00633EC0;
extern void func_001B5C38(int, int);

void lt_fade_status(int a0) {
    if ((D_00633158 == 2 && a0 != D_0063314C) || a0 == 0x3A) {
        D_00633EC0 = a0;
        func_001B5C38(D_0063314C, a0);
        if (D_0063315C == 1) {
            D_00633158 = 5;
        } else {
            D_00633158 = 3;
        }
    }
}

int lt_set_item_select_func(void) {
    return D_00633150;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", lt_set_fade_mode);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B7100);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B7190);

extern char D_002E81F0[];

void func_001B7218(int idx, int flag)
{
    int *p = (int *)(D_002E81F0 + idx * 0x6C);
    p[0x1A] = (p[0x1A] & ~2) | ((flag & 1) << 1);
}

