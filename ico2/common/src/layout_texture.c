#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "gflag.h"

extern int D_0063B60C;
extern unsigned int D_0063B610;
extern int D_0063B618;
extern int D_0063B61C;
extern int D_0063B624;
extern int D_0063C3F4;
extern int D_0063C3F8;

/* The 0x70-byte layout-property records. */
typedef struct LtProperty {
    char pad0[0x10];
    int f10; /* 0x10 */
    char pad14[0x1C - 0x14];
    int f1C;   /* 0x1C */
    int up;    /* 0x20 */
    int down;  /* 0x24 */
    int left;  /* 0x28 */
    int right; /* 0x2C */
    int f30;   /* 0x30 */
    int f34;   /* 0x34 */
    int f38;   /* 0x38 */
    int f3C;   /* 0x3C */
    int f40;   /* 0x40 */
    int f44;   /* 0x44 */
    int f48;   /* 0x48 */
    int f4C;   /* 0x4C */
    int f50;   /* 0x50 */
    int f54;   /* 0x54 */
    int f58;   /* 0x58 */
    int f5C;   /* 0x5C */
    int f60;   /* 0x60 */
    int f64;   /* 0x64 */
    int f68;   /* 0x68 */
    /* 0x6C: the flag word, declared as bits.  The ROM's instruction order is
       the evidence (rung: ROM bytes): gcc 2.9 gives a bitfield reference alias
       set 0, and only with set 0 does the record's flag load come after the
       short store in the two chase loops of display_texture_fade_cancel_chk,
       and the `.last` load before it.  Only bit 2 is touched in this TU; the
       names of the other bits are unknown, so they stay numbered. */
    unsigned int f6C_b0 : 1;
    unsigned int f6C_b1 : 1;
    unsigned int fade_cancel : 1;
    unsigned int f6C_b3 : 1;
    unsigned int f6C_b4 : 1;
    unsigned int f6C_b5 : 27;
} LtProperty;

extern LtProperty D_0030CFF8[];
extern StgPre D_005F5D50[];
extern int D_0063B5F0;
extern int D_0063B614;
extern int layout_boot_flag;
extern int mpegPlayReturnStage;
extern int title_demo_mode;

/* The 0x38-byte layout property records this TU shares with src/kanban. */
typedef struct LtProp {
    int first; /* 0x00 */
    int last;  /* 0x04 */
    float f8;  /* 0x08 */
    float fC;  /* 0x0C */
    float f10; /* 0x10 */
    float f14; /* 0x14 */
    float f18; /* 0x18 */
    float f1C; /* 0x1C */
    void *f20; /* 0x20 */
    int f24;   /* 0x24 */
    int f28;   /* 0x28 */
    int f2C;   /* 0x2C */
    int link;  /* 0x30 */
    char pad34[0x38 - 0x34];
} LtProp;

extern LtProp D_00533FE8[];

#include "layout_texture.h"
#include <string.h>
#include "Texture.h"

/* source lines 342-390 */
void display_texture_fade_cancel_chk(int from, int to)
{
    short list1[256];
    short list2[256];
    int i, j;
    int k, l;
    int n1 = 0;
    int n2 = 0;

    for (i = from; i >= 0; i = D_00533FE8[i].link) {
        for (j = D_00533FE8[i].first; j < D_00533FE8[i].last; j++) {
            LtProperty *pr = &D_0030CFF8[j];

            pr->fade_cancel = 0;
            list1[n1++] = j;
        }
    }
    for (i = to; i >= 0; i = D_00533FE8[i].link) {
        for (j = D_00533FE8[i].first; j < D_00533FE8[i].last; j++) {
            LtProperty *pr = &D_0030CFF8[j];

            pr->fade_cancel = 0;
            list2[n2++] = j;
        }
    }
    for (k = 0; k < n1; k++) {
        LtProperty *p = &D_0030CFF8[list1[k]];

        for (l = 0; l < n2; l++) {
            LtProperty *q = &D_0030CFF8[list2[l]];

            if (p->f58 == q->f58 && p->f5C == q->f5C && p->f68 == q->f68 && p->f64 == q->f64 &&
                p->f60 == q->f60 && p->f54 == q->f54 && p->f50 == q->f50 && p->f4C == q->f4C &&
                p->f48 == q->f48) {
                q->fade_cancel = 1;
                p->fade_cancel = 1;
            }
        }
    }
}

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

extern int frame_count;
extern int D_0063C408;
extern int D_0028F8F4[];
extern int D_0063B620;
extern int D_0063AA00;
/* census name: display_texture (the name is also src/jimaku's global and
   src/kanban's file-local one). */
extern void func_001BF960(int no, LtProperty *e);

/* source lines 533-541 */
/* source line 533-541. The second range is spelled as a conditional expression,
   not `no < 330 && no >= 325`: as an && pair fold_range_test collapses it to
   `addiu -325` + `sltiu 5`, where the ROM keeps both `slti` tests. */
static inline int lt_property_visible(int no)
{
    int vis = 1;

    if (D_0063AA00 == 0 && D_0063B60C == 58 && no >= 300 &&
        (no < 308 || (no < 330 ? no >= 325 : 0))) {
        vis = 0;
    }
    return vis;
}

/* source lines 1066-1075 */
static inline void lt_draw_layout(int no)
{
    int i = D_00533FE8[no].first;
    int last = D_00533FE8[no].last;

    for (; i < last; i++) {
        if (lt_property_visible(i)) {
            func_001BF960(no, &D_0030CFF8[i]);
        }
    }
}

/* kept local: the declaration in s_init.h changes this TU codegen */
extern int soundSeDefPlay(int se, unsigned int handle, float *pos, int a3);
extern unsigned int D_0063C400;
extern unsigned int D_0063C404;
extern signed char D_0063C3FC;
extern int D_0028F4C0[];

/* Source lines 441-451.  lt_switch_layout is a real global at its own ROM slot
   and the PAL listing inlines its body into default_item_select twice, so the two
   call sites below need static inline stand-ins (INTERIM: they go away when the
   deferred tail is closed and the public definition can be marked inline).
   The two copies are NOT identical: the first site's else arm stores 7 to
   D_0063B618 where the out-of-line function and the second site store 3.  That is
   what the ROM has (0x001BF548 `addiu $3,$0,0x7` feeding `sw $3,%gp_rel(D_0063B618)`
   against 0x001BF5EC's `sw $2` with $2 = 3), and it is also what keeps the two
   else arms from cross-jumping: with one constant the pair of stores is the
   ordinary adjacent-store reversal (D_0063B618 first, then D_0063C3F8) and with two
   it stays in source order, so the tails do not match.  A single stand-in taking
   the value as a parameter compiles one instruction short for exactly that
   reason. */
static inline void lt_switch_layout_7(int no)
{
    if ((D_0063B618 == 2 && no != D_0063B60C) || no == 62) {
        D_0063C3F4 = no;
        display_texture_fade_cancel_chk(D_0063B60C, no);
        if (D_0063B61C == 1) {
            D_0063B618 = 5;
        } else {
            D_0063C3F8 = 3;
            D_0063B618 = 7;
        }
    }
}

static inline void lt_switch_layout_3(int no)
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

/* source lines 621-705 */
void default_item_select(int no)
{
    LtProp *p = &D_00533FE8[no];
    LtProperty *e = &D_0030CFF8[p->f2C];
    int prev;

    if (p->f2C < 0) {
        return;
    }
    if (D_0063B620 != 0) {
        return;
    }
    if (D_0063B618 != 2) {
        return;
    }
    if (D_0063B624 == 0) {
        lt_analog2Pad();
        prev = p->f2C;
        if ((D_0028F8F0.trigger & 0x50) == 0) {
            if ((D_0028F8F0.trigger & 0x1000) && e->f3C >= 0) {
                p->f2C = e->f3C;
                while (!lt_property_visible(p->f2C)) {
                    p->f2C = D_0030CFF8[p->f2C].f3C;
                }
            } else if ((D_0028F8F0.trigger & 0x4000) && e->f38 >= 0) {
                p->f2C = e->f38;
                while (!lt_property_visible(p->f2C)) {
                    p->f2C = D_0030CFF8[p->f2C].f38;
                }
            } else if ((D_0028F8F0.trigger & 0x8000) && e->f34 >= 0) {
                p->f2C = e->f34;
            } else if ((D_0028F8F0.trigger & 0x2000) && e->f30 >= 0) {
                p->f2C = e->f30;
            }
        }
        if (p->f2C != prev) {
            soundSeDefPlay(411, 0xFFFFFFFE, 0, 0);
            D_0063C3FC = 1;
            D_0063C404 = (unsigned int)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.25f);
            D_0063C408 = frame_count;
            D_0063C400 = 0;
        }
    } else {
        p->f2C = ((int (*)(void))D_0063B624)();
        D_0063B624 = 0;
    }

    e = &D_0030CFF8[p->f2C];
    if (D_0028F8F0.trigger & 0x40) {
        if (e->right >= 0) {
            if (D_0063B618 == 2) {
                soundSeDefPlay(412, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_7(e->right);
                return;
            }
        }
    }
    if (D_0028F8F0.trigger & 0x10) {
        if (e->left >= 0) {
            if (D_0063B618 == 2) {
                soundSeDefPlay(413, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_3(e->left);
            }
        }
    }
}

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

extern unsigned char D_0063B600[4];
extern unsigned int D_0063B628;
extern unsigned int D_0063B62C;
extern unsigned int D_0063C40C;
extern unsigned int D_0063C410;

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_texture", texture_fading);

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int on);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int on);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_SpriteSensitive do not fit the prototype in GifPacket.h */
extern void gif_SpriteSensitive(void *rect, unsigned int z, void *uv, void *col, int prim);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
extern void texture_fading(LtProp *p);

/* The sprite rectangle the gif helpers take: origin and size, in 1/16 pixels. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} SprRect;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SprCol;

extern SprRect D_0061DD50;
/* The census display_texture body (still INCLUDE_ASM below) reads these:
   D_0063B608 is the second highlight colour, D_0028F720 the system record whose
   bytes at 0xD0/0xD4/0xD8 it inverts, and GetTableSin/gif_SpriteSensitiveOffset/
   gif_PointOffset/gif_SetGsReg/rand are its callees. */
extern SprCol D_0063B608;
extern unsigned char D_0028F720[];
extern float GetTableSin(int a);
extern void gif_SpriteSensitiveOffset(void *rect, unsigned int z, void *ofs, void *col, int prim);
extern void gif_PointOffset(void *pt, unsigned int z, void *col, int prim);
extern void gif_SetGsReg(int reg, int val);
extern int rand(void);

/* census display_texture, a file static (MAIN.MAP carries no global of that
   name), takes the name as static display_texture once this body is C: the stub
   assembles a glabel that would emit a global display_texture */
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_texture", func_001BF960);

/* source lines 715-735 */
static inline void lt_draw_primary_sprite(SprCol *col)
{
    SprRect r;

    gif_StartPacketPri(11);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 7, 0);
    r = D_0061DD50;
    gif_SpriteSensitive(&r, 0xFFFFFFFF, (void *)0, col, 1);
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_EndPacket();
}

void display_primary_texture_layout(int no, int sel)
{
    SprCol col;
    LtProp *p = &D_00533FE8[no];
    int m;
    int flag;

    col.r = (int)(p->f10 * 255.0f);
    col.g = (int)(p->f14 * 255.0f);
    col.b = (int)(p->f18 * 255.0f);
    col.a = (int)(p->f1C * 127.0f);
    lt_draw_primary_sprite(&col);
    if (p->f20 != 0 && (D_0063B618 == 1 || D_0063B618 == 2)) {
        if (p->f2C >= 0) {
            int *e = (int *)((char *)D_0030CFF8 + p->f2C * 0x70);

            m = e[0x1B] & 3;
        } else {
            m = 0;
        }
        sel = ((int (*)(int, int))p->f20)(D_0063B614, sel);
        if (sel != -1) {
            flag = 0;
            if ((D_0028F8F4[0] & 0x40) != 0) {
                flag = m == 1;
            }
            if ((D_0063B618 == 2 && sel != D_0063B60C) || sel == 62) {
                D_0063C3F4 = sel;
                display_texture_fade_cancel_chk(D_0063B60C, sel);
                if (D_0063B61C == 1) {
                    D_0063B618 = 5;
                } else {
                    D_0063C3F8 = 3;
                    D_0063B618 = flag ? 7 : 3;
                }
            }
        } else if ((D_0028F8F4[0] & 0x40) != 0) {
            if (m == 2) {
                D_0063C3F8 = m;
                D_0063B618 = 7;
            }
        }
        D_0063B614 = 0;
    }
    texture_fading(p);
    lt_draw_layout(no);
}

void exec_layout_texture(void)
{
    int n = 0;
    int list[16];
    int ret = -1;
    LtProp *p;
    int v;
    int j;
    int k;

    if (frame_count - D_0063C408 == 0 || frame_count - D_0063C408 == 1) {
        D_0028F8F4[0] = 0;
    }
    p = &D_00533FE8[D_0063B60C];
    for (;;) {
        for (j = p->first; j < p->last; j++) {
            int *e = (int *)((char *)D_0030CFF8 + j * 0x70);

            e[0x1B] = (e[0x1B] & ~0x10) | (((unsigned int)e[0x1B] >> 1) & 0x10);
        }
        if (p->link >= 0) {
            list[n++] = p->link;
            p = &D_00533FE8[p->link];
        } else {
            break;
        }
    }
    list[n] = -1;
    for (n--; n != -1; n--) {
        p = &D_00533FE8[list[n]];
        v = p->f2C;
        D_0063B610 = v;
        if (p->f20 != 0 && (D_0063B618 == 1 || D_0063B618 == 2)) {
            ret = ((int (*)(int, int))p->f20)(p->f24, ret);
            p->f24 = 0;
            v = p->f2C;
        } else {
            ret = -1;
        }
        if (v >= 0 && D_0063B620 == 0) {
            default_item_select(list[n]);
        }
    }
    p = &D_00533FE8[D_0063B60C];
    D_0063B610 = p->f2C;
    display_primary_texture_layout(D_0063B60C, ret);
    if (p->f2C >= 0 && D_0063B620 == 0) {
        default_item_select(D_0063B60C);
    }
    for (k = 0; list[k] >= 0; k++) {
        lt_draw_layout(list[k]);
    }
    D_0063B620 = 0;
}

/* census init_textures_of_specified_property, a file static; MAIN.MAP carries no
   global of that name, so ico2/common/src/kanban's twin is a static too and
   `static` here keeps this one's ELF symbol local */
extern char D_00535168[][0x34];
extern char D_0030D014[];
extern char D_0061DDA8[]; /* "no texture loaded.(%s)\n" */
extern char D_0061DDC0[]; /* "src/layout_texture.c" */
extern char D_0063B630[]; /* "/" */
extern char D_0063B638[]; /* "0" */
extern char *strtok(char *s, const char *sep);
extern char *strrchr(const char *s, int c);
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

static void init_textures_of_specified_property(int first, int last)
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

/* source lines 1322-1331 */
static inline void lt_init_stage_textures(int stage)
{
    int i = D_005F5D50[stage].layoutFirst;
    int last = D_005F5D50[stage].layoutLast;

    for (; i < last; i++) {
        init_textures_of_specified_property(D_00533FE8[i].first, D_00533FE8[i].last);
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
    if (D_0063B60C < D_005F5D50[stage].layoutFirst) {
        D_0063B60C = D_005F5D50[stage].layoutLast - 1;
    }
    lt_switch_layout(D_0063B60C);
    return D_0063B60C;
}

inline int lt_next_layout(int stage)
{
    D_0063B60C = D_0063B60C + 1;
    if (D_0063B60C >= D_005F5D50[stage].layoutLast) {
        D_0063B60C = D_005F5D50[stage].layoutFirst;
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
