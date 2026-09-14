#include "common.h"

extern int D_0063B60C;
extern unsigned int D_0063B610;
extern int D_0063B618;
extern int D_0063B61C;
extern int D_0063B624;
extern int D_0063C3F4;
extern int D_0063C3F8;

/* The 0x70-byte layout-property records. */
typedef struct LtProperty {
    char pad0[0x20];
    int up;    /* 0x20 */
    int down;  /* 0x24 */
    int left;  /* 0x28 */
    int right; /* 0x2C */
    char pad30[0x6C - 0x30];
    int flags; /* 0x6C */
} LtProperty;

extern LtProperty D_0030CFF8[];

/* The stage table this TU shares with src/generator: 0x194-byte records whose
   0x130 / 0x134 pair is the first and one-past-last layout of the stage. */
typedef struct LtStageRange {
    char pad0[0x130];
    int first; /* 0x130 */
    int last;  /* 0x134 */
    char pad138[0x194 - 0x138];
} LtStageRange;

extern LtStageRange D_005F5D50[];
extern void display_texture_fade_cancel_chk(int from, int to);
/* prototypes: their order is the inline tail's emission order */
void lt_switch_layout(int no);
int lt_current_property_item(void);
int lt_link_layout(int dir);
int lt_prev_layout(int stage);
int lt_next_layout(int stage);
void lt_mask_property(int idx, int flag);
void lt_default_mask_property(int idx, int flag);
int lt_fade_status(void);
void lt_set_item_select_func(int val);
void lt_set_fade_mode(int val);

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", display_texture_fade_cancel_chk);

/* The pad record at D_0028F8F0: the button word at +0 and the trigger word at
   +4, with the two analog-stick axes as unsigned bytes at +0x56 and +0x57. */
typedef struct LtPad {
    int button;  /* 0x00 */
    int trigger; /* 0x04 */
    char pad8[0x56 - 8];
    unsigned char ry; /* 0x56 */
    unsigned char rx; /* 0x57 */
} LtPad;

extern LtPad D_0028F8F0;
extern int D_0063C3F0;

void lt_analog2Pad(void)
{
    if (D_0028F8F0.rx < 20) {
        D_0028F8F0.button |= 0x1000;
        if ((D_0063C3F0 & 0x1000) == 0) {
            D_0028F8F0.trigger |= 0x1000;
        }
    }
    if (D_0028F8F0.rx >= 236) {
        D_0028F8F0.button |= 0x4000;
        if ((D_0063C3F0 & 0x4000) == 0) {
            D_0028F8F0.trigger |= 0x4000;
        }
    }
    if (D_0028F8F0.ry < 20) {
        D_0028F8F0.button |= 0x8000;
        if ((D_0063C3F0 & 0x8000) == 0) {
            D_0028F8F0.trigger |= 0x8000;
        }
    }
    if (D_0028F8F0.ry >= 236) {
        D_0028F8F0.button |= 0x2000;
        if ((D_0063C3F0 & 0x2000) == 0) {
            D_0028F8F0.trigger |= 0x2000;
        }
    }
    D_0063C3F0 = D_0028F8F0.button;
}

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", default_item_select);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", texture_fading);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001BF960);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", display_primary_texture_layout);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", exec_layout_texture);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001C09A8);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", init_layout_texture);

inline void lt_switch_layout(int no)
{
    if ((D_0063B618 == 2 && no != D_0063B60C) || no == 62) {
        D_0063C3F4 = no;
        display_texture_fade_cancel_chk(D_0063B60C, no);
        if (D_0063B61C == 1) {
            D_0063B618 = 5;
        } else {
            D_0063C3F8 = 3;
            D_0063B618 = 3;
        }
    }
}

inline int lt_current_property_item(void)
{
    return D_0063B610;
}

inline int lt_link_layout(int dir)
{
    switch (dir) {
    case 0:
        return D_0030CFF8[lt_current_property_item()].right;
    case 1:
        return D_0030CFF8[lt_current_property_item()].left;
    case 2:
        return D_0030CFF8[lt_current_property_item()].down;
    case 3:
        return D_0030CFF8[lt_current_property_item()].up;
    }
    return -1;
}

inline int lt_prev_layout(int stage)
{
    D_0063B60C = D_0063B60C - 1;
    if (D_0063B60C < D_005F5D50[stage].first) {
        D_0063B60C = D_005F5D50[stage].last - 1;
    }
    lt_switch_layout(D_0063B60C);
    return D_0063B60C;
}

inline int lt_next_layout(int stage)
{
    D_0063B60C = D_0063B60C + 1;
    if (D_0063B60C >= D_005F5D50[stage].last) {
        D_0063B60C = D_005F5D50[stage].first;
    }
    lt_switch_layout(D_0063B60C);
    return D_0063B60C;
}

inline void lt_mask_property(int idx, int flag)
{
    int *p = (int *)((char *)D_0030CFF8 + idx * 0x70);
    p[0x1B] = (p[0x1B] & ~0x10) | ((flag & 1) << 4);
}

inline void lt_default_mask_property(int idx, int flag)
{
    int *p = (int *)((char *)D_0030CFF8 + idx * 0x70);
    p[0x1B] = (p[0x1B] & ~0x20) | ((flag & 1) << 5);
}

inline int lt_fade_status(void)
{
    return D_0063B618;
}

inline void lt_set_item_select_func(int val)
{
    D_0063B624 = val;
}

inline void lt_set_fade_mode(int val)
{
    D_0063B61C = val;
}
