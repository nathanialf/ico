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
    char pad30[0x48 - 0x30];
    int f48;   /* 0x48 */
    int f4C;   /* 0x4C */
    int f50;   /* 0x50 */
    int f54;   /* 0x54 */
    int f58;   /* 0x58 */
    int f5C;   /* 0x5C */
    int f60;   /* 0x60 */
    int f64;   /* 0x64 */
    int f68;   /* 0x68 */
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
extern int D_0063B5F0;
extern int D_0063B614;
extern int layout_boot_flag;
extern int mpegPlayReturnStage;
extern int title_demo_mode;
extern void gflagInit(void);

/* The 0x38-byte layout property records this TU shares with src/kanban. */
typedef struct LtProp {
    int first; /* 0x00 */
    int last;  /* 0x04 */
    char pad8[0x20 - 0x08];
    void *f20; /* 0x20 */
    int f24;   /* 0x24 */
    int f28;   /* 0x28 */
    int f2C;   /* 0x2C */
    int link;  /* 0x30 */
    char pad34[0x38 - 0x34];
} LtProp;

extern LtProp D_00533FE8[];
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

/* census name: init_textures_of_specified_property (src/kanban carries a global of
   that name, so the two cannot both keep it). */
extern char D_00535168[][0x34];
extern char D_0030D014[];
extern char D_0061DDA8[]; /* "no texture loaded.(%s)\n" */
extern char D_0061DDC0[]; /* "src/layout_texture.c" */
extern char D_0063B630[]; /* "/" */
extern char D_0063B638[]; /* "0" */
extern char *strcpy(char *dst, const char *src);
extern char *strtok(char *s, const char *sep);
extern char *strrchr(const char *s, int c);
extern int tex_GetTextureNo(char *name);
extern void *tex_GetTextureData(int no);
extern void tex_SetSamplingType(void *td, int a1, int a2);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

/* source lines 1249-1259 */
static inline char *lt_texture_base_name(char *src)
{
    char buf[256];
    char *p;
    char *t;

    p = buf;

    strcpy(buf, src);

    t = strtok(buf, D_0063B630);
    if (t != 0) {
        do {
            p = t;
            t = strtok(0, D_0063B630);
        } while (t != 0);
    }
    if ((t = strrchr(p, '.')) != 0) {
        *t = 0;
    }
    return p;
}

/* source lines 1275-1287 */
static inline int lt_texture_no_of_property(int idx)
{
    int n;
    char *src;
    char *name;
    int no;

    n = D_0030CFF8[idx].f58;
    src = D_00535168[n];
    name = lt_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy(D_0061DDA8, src);
        debug_assert(D_0061DDC0, 0x507);
        __assert(D_0061DDC0, 0x507, D_0063B638);
    }
    return no;
}

void func_001C09A8(int first, int last)
{
    int i;
    int no;

    for (i = first; i < last; i++) {
        no = lt_texture_no_of_property(i);
        *(int *)(D_0030D014 + i * 0x70) = no;
        *(void **)(D_0030D014 + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030D014 + i * 0x70 - 4), 1, 1);
    }
}

/* source lines 515-522: the property chain reset, inlined here and by
   texture_fading. */
static inline void lt_reset_property_chain(int no)
{
    int *p = (int *)((char *)D_00533FE8 + no * 0x38);
    int i = p[0xC];

    while (i >= 0) {
        p = (int *)((char *)D_00533FE8 + i * 0x38);
        p[0xB] = p[0xA];
        p[9] = 1;
        i = p[0xC];
    }
}

/* source lines 1322-1331 */
static inline void lt_init_stage_textures(int stage)
{
    int i = D_005F5D50[stage].first;
    int last = D_005F5D50[stage].last;

    for (; i < last; i++) {
        func_001C09A8(D_00533FE8[i].first, D_00533FE8[i].last);
    }
    D_0063B610 = D_00533FE8[D_0063B60C].f28;
}

void init_layout_texture(int stage)
{
    D_0063B624 = 0;
    if (stage == 1) {
        gflagInit();
        if (layout_boot_flag == 0) {
            D_0063B60C = 7;
        } else if (mpegPlayReturnStage == stage) {
            mpegPlayReturnStage = 0;
            if (D_0063B5F0 == 0xFFFFFFFE) {
                title_demo_mode = title_demo_mode ^ 1;
                D_0063B60C = 13;
            } else if (D_0063B5F0 == 0xFFFFFFFF) {
                D_0063B60C = 10;
                title_demo_mode = title_demo_mode ^ 1;
            } else {
                D_0063B60C = 13;
            }
        } else {
            D_0063B60C = 13;
        }
    } else {
        D_0063B60C = 54;
    }
    lt_init_stage_textures(stage);
    D_00533FE8[D_0063B60C].f2C = D_00533FE8[D_0063B60C].f28;
    D_0063B614 = 1;
    D_0063B618 = 0;
    lt_reset_property_chain(D_0063B60C);
}

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
