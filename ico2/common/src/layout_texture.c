#include "typedef.h"
#include "debug.h"
#include "StageManager.h"
#include "gflag.h"
#include "layout_action.h"
#include <string.h>
#include <stdlib.h>
#include "debug_exception.h"
#include "tableSin.h"

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SprCol;

/* .sdata, layout_texture.o's run in the ROM's order (MAIN.MAP names
   current_layout_id and lt_item_select_disable; the January link had the
   continue flag's slot elsewhere): the continue screen's decided flag, which
   layout_action sets and op's countdown waits on; the two highlight colours;
   the current layout; the selected item; the item-select handler's flag; the
   fade state and type; lt_item_select_disable; the fade-end handler; the
   highlight blink's count and length.  The two short strings follow. */
int lt_continue_selected = 0; /* derived name */

static unsigned char ltCursorColor[4] = {128, 128, 128, 127}; /* derived name */

static SprCol ltHighlightColor = {128, 128, 128, 127}; /* derived name */

int current_layout_id = 0;

static unsigned int ltCurrentItem = -1; /* derived name */

static int ltSelectFlag = 1; /* derived name */

static int fadeState = 0; /* derived name */

static int fadeType = 0; /* derived name */

int lt_item_select_disable = 0;

static int fadeCallback = 0; /* derived name */

static unsigned int ltBlinkCount = 0; /* derived name */

static unsigned int ltBlinkLength = 0; /* derived name */

/* .sbss, layout_texture.o's nine words in the ROM's order (MAIN.MAP line 7619
   gives the January object's 8 bytes and no symbol, so the names are ours and
   the other seven are the retail revision's): the pad buttons of the last
   frame, the layout switched to and the fade state that follows the switch,
   the selection glow's flag, count and length, the frame of the last
   selection, and the switch fade's length and count. */
static int lastButton;

static int nextLayout;

static int nextFadeState;

static signed char glowOn;

static unsigned int glowCount;

static unsigned int glowLength;

static int selectFrame;

static unsigned int fadeLength;

static unsigned int fadeCount;

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
    unsigned int f6C_b5 : 1;
    unsigned int f6C_b6 : 26;
} LtProperty;

extern LtProperty texProperty[];
extern StgPre stageData[];

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

extern LtProp texLayout[];

#include "layout_texture.h"

/* No <string.h>: display_texture's 4-byte zero fill is a `jal memset` in the
   ROM, so newlib's builtin-compatible prototype was not in scope; memset is
   declared as layout_action.c (same directory) declares it. */
/* kept local: void * (void *, int, int) here, void * (void *, int, unsigned int) in string.h */
extern void *memset(void *dst, int c, int n);

#include "Texture.h"

/* The sprite rectangle the gif helpers take: origin and size, in 1/16 pixels. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} SprRect;

/* the screen rectangle lt_draw_primary_sprite draws, in 1/16 pixels: 640 x 226
   pixels centred on the origin; first in this object's .rodata, whose 16-byte
   section alignment (carried by texture_fading's switch table) is the ROM's
   12 B of fill before it */
static const SprRect primarySpriteRect = {-5120, -1808, 10240, 3616}; /* derived name */

/* source lines 342-390 */
void display_texture_fade_cancel_chk(int from, int to)
{
    short list1[256];
    short list2[256];
    int i, j;
    int k, l;
    int n1 = 0;
    int n2 = 0;

    for (i = from; i >= 0; i = texLayout[i].link) {
        for (j = texLayout[i].first; j < texLayout[i].last; j++) {
            LtProperty *pr = &texProperty[j];

            pr->fade_cancel = 0;
            list1[n1++] = j;
        }
    }
    for (i = to; i >= 0; i = texLayout[i].link) {
        for (j = texLayout[i].first; j < texLayout[i].last; j++) {
            LtProperty *pr = &texProperty[j];

            pr->fade_cancel = 0;
            list2[n2++] = j;
        }
    }
    for (k = 0; k < n1; k++) {
        LtProperty *p = &texProperty[list1[k]];

        for (l = 0; l < n2; l++) {
            LtProperty *q = &texProperty[list2[l]];

            if (p->f58 == q->f58 && p->f5C == q->f5C && p->f68 == q->f68 && p->f64 == q->f64 &&
                p->f60 == q->f60 && p->f54 == q->f54 && p->f50 == q->f50 && p->f4C == q->f4C &&
                p->f48 == q->f48) {
                q->fade_cancel = 1;
                p->fade_cancel = 1;
            }
        }
    }
}

/* The pad record at pad: the button word at +0 and the trigger word at
   +4, with the two analog-stick axes as unsigned bytes at +0x56 and +0x57. */
typedef struct LtPad {
    int button;  /* 0x00 */
    int trigger; /* 0x04 */
    char pad8[0x56 - 8];
    unsigned char ry; /* 0x56 */
    unsigned char rx; /* 0x57 */
} LtPad;

/* kept local: LtPad here, PadState [16] in main.h */
extern LtPad pad;

void lt_analog2Pad(void)
{
    if (pad.rx < 20) {
        pad.button |= 0x1000;
        if ((lastButton & 0x1000) == 0) {
            pad.trigger |= 0x1000;
        }
    }
    if (pad.rx >= 236) {
        pad.button |= 0x4000;
        if ((lastButton & 0x4000) == 0) {
            pad.trigger |= 0x4000;
        }
    }
    if (pad.ry < 20) {
        pad.button |= 0x8000;
        if ((lastButton & 0x8000) == 0) {
            pad.trigger |= 0x8000;
        }
    }
    if (pad.ry >= 236) {
        pad.button |= 0x2000;
        if ((lastButton & 0x2000) == 0) {
            pad.trigger |= 0x2000;
        }
    }
    lastButton = pad.button;
}

/* kept local: agrees with main.h, which this TU does not include (GlobalStageSetting, pad differ) */
extern int frame_count;
/* census display_texture: a file static here (the name is also src/jimaku's
   global and src/kanban's file-local one). */
static void display_texture(int no, LtProperty *e);

/* source lines 533-541 */
/* source line 533-541. The second range is spelled as a conditional expression,
   not `no < 330 && no >= 325`: as an && pair fold_range_test collapses it to
   `addiu -325` + `sltiu 5`, where the ROM keeps both `slti` tests. */
static inline int lt_property_visible(int no)
{
    int vis = 1;

    if (gFlagGameClear == 0 && current_layout_id == 58 && no >= 300 &&
        (no < 308 || (no < 330 ? no >= 325 : 0))) {
        vis = 0;
    }
    return vis;
}

/* source lines 1066-1075 */
static inline void lt_draw_layout(int no)
{
    int i = texLayout[no].first;
    int last = texLayout[no].last;

    for (; i < last; i++) {
        if (lt_property_visible(i)) {
            display_texture(no, &texProperty[i]);
        }
    }
}

/* kept local: int (int, unsigned int, float *, int) here, int (int, int, int, int) in s_init.h */
extern int soundSeDefPlay(int se, unsigned int handle, float *pos, int a3);
/* kept local: agrees with main.h, which this TU does not include (GlobalStageSetting, pad differ) */
extern int systemStatus[];

/* Source lines 441-451.  lt_switch_layout is a real global at its own ROM slot
   and the PAL listing inlines its body into default_item_select twice, so the two
   call sites below need static inline stand-ins (INTERIM: they go away when the
   deferred tail is closed and the public definition can be marked inline).
   The two copies are NOT identical: the first site's else arm stores 7 to
   fadeState where the out-of-line function and the second site store 3.  That is
   what the ROM has (0x001BF548 `addiu $3,$0,0x7` feeding `sw $3,%gp_rel(fadeState)`
   against 0x001BF5EC's `sw $2` with $2 = 3), and it is also what keeps the two
   else arms from cross-jumping: with one constant the pair of stores is the
   ordinary adjacent-store reversal (fadeState first, then nextFadeState) and with two
   it stays in source order, so the tails do not match.  A single stand-in taking
   the value as a parameter compiles one instruction short for exactly that
   reason. */
static inline void lt_switch_layout_7(int no)
{
    if ((fadeState == 2 && no != current_layout_id) || no == 62) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            nextFadeState = 3;
            fadeState = 7;
        }
    }
}

static inline void lt_switch_layout_3(int no)
{
    if ((fadeState == 2 && no != current_layout_id) || no == 62) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            nextFadeState = 3;
            fadeState = 3;
        }
    }
}

/* source lines 621-705 */
void default_item_select(int no)
{
    LtProp *p = &texLayout[no];
    LtProperty *e = &texProperty[p->f2C];
    int prev;

    if (p->f2C < 0) {
        return;
    }
    if (lt_item_select_disable != 0) {
        return;
    }
    if (fadeState != 2) {
        return;
    }
    if (fadeCallback == 0) {
        lt_analog2Pad();
        prev = p->f2C;
        if ((pad.trigger & 0x50) == 0) {
            if ((pad.trigger & 0x1000) && e->f3C >= 0) {
                p->f2C = e->f3C;
                while (!lt_property_visible(p->f2C)) {
                    p->f2C = texProperty[p->f2C].f3C;
                }
            } else if ((pad.trigger & 0x4000) && e->f38 >= 0) {
                p->f2C = e->f38;
                while (!lt_property_visible(p->f2C)) {
                    p->f2C = texProperty[p->f2C].f38;
                }
            } else if ((pad.trigger & 0x8000) && e->f34 >= 0) {
                p->f2C = e->f34;
            } else if ((pad.trigger & 0x2000) && e->f30 >= 0) {
                p->f2C = e->f30;
            }
        }
        if (p->f2C != prev) {
            soundSeDefPlay(411, 0xFFFFFFFE, 0, 0);
            glowOn = 1;
            glowLength = (unsigned int)((60 - systemStatus[0] * 10) / systemStatus[1] * 0.25f);
            selectFrame = frame_count;
            glowCount = 0;
        }
    } else {
        p->f2C = ((int (*)(void))fadeCallback)();
        fadeCallback = 0;
    }

    e = &texProperty[p->f2C];
    if (pad.trigger & 0x40) {
        if (e->right >= 0) {
            if (fadeState == 2) {
                soundSeDefPlay(412, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_7(e->right);
                return;
            }
        }
    }
    if (pad.trigger & 0x10) {
        if (e->left >= 0) {
            if (fadeState == 2) {
                soundSeDefPlay(413, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_3(e->left);
            }
        }
    }
}

static inline void lt_reset_property_chain(int no)
{
    LtProp *p = &texLayout[no];
    int i = p->link;

    while (i >= 0) {
        p = &texLayout[i];
        p->f2C = p->f28;
        p->f24 = 1;
        i = p->link;
    }
}

/* source lines 748-859.  The fade state fadeState is read and written as the
   global itself, as the rest of this TU does (the listing puts each `li N` on
   the line of its store, 783, 802, 815).  gcse's load/store PRE then carries the
   value in one register into the second switch, and its edge block for the
   fadeType default path (the load reorg later moves into the bne delay slot)
   sits between case 3's store and the join at jump2, which is what keeps case 0
   from cross-jumping into it; case 3's store then comes back inline after the
   `sb` with no line of its own, as rows 771-772 show. */
void texture_fading(LtProp *p)
{
    unsigned char *col = ltCursorColor;
    int *cur;

    switch (fadeType) {
    case 1:
        if (fadeState < 2) {
            if (fadeState >= 0) {
                fadeState = 2;
            }
        }
        break;
    case 0:
        switch (fadeState) {
        case 0:
            if (p->f8 == 0.0f) {
                fadeState = 2;
            }
            break;
        case 3:
            if (p->fC == 0.0f) {
                fadeState = 6;
                col[3] = 127;
            }
            break;
        }
        break;
    }
    switch (fadeState) {
    case 0:
        fadeState = 1;
        ltBlinkLength = (int)(p->f8 * ((60 - systemStatus[0] * 10) / systemStatus[1]));
        ltBlinkCount = ltBlinkLength;
        /* fall through */
    case 1:
        col[3] = (ltBlinkLength - ltBlinkCount) * 127 / ltBlinkLength;
        ltBlinkCount--;
        if (ltBlinkCount == 0) {
            fadeState = 2;
        }
        break;
    case 2:
        col[3] = 127;
        break;
    case 7:
        fadeState = 8;
        fadeLength = (unsigned int)((60 - systemStatus[0] * 10) / systemStatus[1] * 0.25f);
        fadeCount = 0;
        /* fall through */
    case 8:
        if (++fadeCount >= fadeLength) {
            fadeState = nextFadeState;
        }
        break;
    case 3:
        fadeState = 4;
        ltBlinkLength = (int)(p->fC * ((60 - systemStatus[0] * 10) / systemStatus[1]));
        ltBlinkCount = ltBlinkLength;
        break;
    case 4:
        col[3] = ltBlinkCount * 127 / ltBlinkLength;
        ltBlinkCount--;
        if (ltBlinkCount == 0) {
            fadeState = 5;
        }
        break;
    case 5:
        col[3] = 0;
        /* fall through */
    case 6:
        current_layout_id = nextLayout;
        cur = &texLayout[current_layout_id].f2C;
        *cur = texLayout[current_layout_id].f28;
        ltSelectFlag = 1;
        fadeState = 0;
        if (texLayout[current_layout_id].f8 == 0.0f) {
            lt_item_select_disable = 1;
            fadeState = 2;
        }
        lt_reset_property_chain(current_layout_id);
        break;
    }
    if (glowOn != 0) {
        if (glowCount++ >= glowLength) {
            glowOn = 0;
        }
    }
}

/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SetAlpha, gif_SpriteSensitive differ) */
extern void gif_StartPacketPri(int pri);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SetAlpha, gif_SpriteSensitive differ) */
extern void gif_SetZTest(int on);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SetAlpha, gif_SpriteSensitive differ) */
extern void gif_SetZWrite(int on);
/* kept local: void (int, int, int) here, void (long long, long long, long long) in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: void (void *, unsigned int, void *, void *, int) here, void (int *, long long, int *, unsigned char *, int) in GifPacket.h */
extern void gif_SpriteSensitive(void *rect, unsigned int z, void *uv, void *col, int prim);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SetAlpha, gif_SpriteSensitive differ) */
extern void gif_EndPacket(void);
extern void texture_fading(LtProp *p);
/* The census display_texture body below reads these:
   ltHighlightColor is the second highlight colour, GlobalStageSetting the system record whose
   bytes at 0xD0/0xD4/0xD8 it inverts, and GetTableSin/gif_SpriteSensitiveOffset/
   gif_PointOffset/gif_SetGsReg/rand are its callees. */
/* kept local: unsigned char [] here, StageSetting in main.h */
extern unsigned char GlobalStageSetting[];
/* kept local: void (void *, unsigned int, void *, void *, int) here, void (int *, long long, int *, unsigned char *, int) in GifPacket.h */
extern void gif_SpriteSensitiveOffset(void *rect, unsigned int z, void *ofs, void *col, int prim);
/* kept local: void (void *, unsigned int, void *, int) here, void (int *, long long, unsigned char *, int) in GifPacket.h */
extern void gif_PointOffset(void *pt, unsigned int z, void *col, int prim);
/* kept local: void (int, int) here, void (long long, long long) in GifPacket.h */
extern void gif_SetGsReg(int reg, int val);

/* source lines 870-887: the pulsing highlight sprite, inlined three times by
   display_texture.  The listing puts the parameter setup on the brace line
   (871) and the copy, the four colour stores and the GetTableSin call on 872,
   873 and 874, so the three locals are initialized declarations.  The
   aggregate initializer also clobbers `c` before its field stores, which is
   what lets sched1 take the copy ahead of the colour constant. */
static inline void lt_glow_sprite(SprRect *box, SprRect *ofs, int r, int g, int b, float t, int dx,
                                  int dy)
{
    SprRect rr = *box;
    SprCol c = {r, g, b, 127};
    float s = GetTableSin((short)(t * 3.1415926535897932 * 10430.3779296875));

    c.r = c.r * s;
    c.g = c.g * s;
    c.b = c.b * s;
    rr.x = rr.x - s * dx;
    rr.y = rr.y - s * dy;
    rr.w = rr.w + s * dx * 2;
    rr.h = rr.h + s * dy * 2;
    gif_SetAlpha(1, 5, 0);
    gif_SpriteSensitiveOffset(&rr, 0xFFFFFF9B, ofs, &c, 1);
}

/* census display_texture, a file static; source lines 896-1045 */
static void display_texture(int no, LtProperty *e)
{
    SprRect ofs;
    SprRect box;

    union {
        int pt[2];
        SprCol col;
    } u;

    int sel;
    int i;

    ofs.x = (e->f5C << 4) + 8;
    ofs.y = (e->f68 << 4) + 8;
    ofs.w = e->f64 << 4;
    ofs.h = e->f60 << 4;

    box.w = e->f4C << 4;
    box.h = e->f48 << 3;
    if (box.w == 0) {
        box.w = ofs.w;
    }
    if (box.h == 0) {
        box.h = ofs.h >> 1;
    }
    if (e->f44 != 0) {
        box.x = (10240 - box.w) / 2 - 5120;
    } else {
        box.x = (e->f54 - 320) * 16;
    }
    box.y = (e->f50 - 113) * 16;

    sel = (e == &texProperty[texLayout[no].f2C]);
    if (sel && lt_item_select_disable == 0 && fadeState == 2 && e->f6C_b3 == 0) {
        SprCol pcol;

        memset(&pcol, 0, sizeof(pcol));
        pcol.a = 127;
        gif_StartPacketPri(11);
        gif_SetZTest(0);
        for (i = 0; i < box.w * box.h / 1200; i++) {
            u.pt[0] = box.x + rand() % box.w;
            u.pt[1] = box.y + rand() % box.h;
            pcol.a = rand() % 127;
            gif_PointOffset(u.pt, 0x800000, &pcol, 1);
        }
        gif_EndPacket();
    }
    if (e->f6C_b4 == 0) {
        int flag;

        flag = (e->f3C >= 0 || e->f38 >= 0 || e->f34 >= 0 || e->f30 >= 0 || e->right >= 0 ||
                e->left >= 0 || e->down >= 0 || e->up >= 0);
        tex_TransTexture(e->f1C, 11);

        gif_StartPacketPri(11);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 7, 0);
        box.y = box.y + 4;
        box.x = box.x + 4;
        gif_SetGsReg(20, 96);
        box.h = box.h - 16;
        ofs.h = ofs.h - 16;
        box.w = box.w - 16;
        ofs.w = ofs.w - 16;
        if (e->fade_cancel == 0) {
            u.col = *(SprCol *)ltCursorColor;
        } else {
            u.col = *(SprCol *)&ltHighlightColor;
        }
        u.col.r = ~GlobalStageSetting[0xD0];
        u.col.g = ~GlobalStageSetting[0xD4];
        u.col.b = ~GlobalStageSetting[0xD8];
        if (u.col.r < 120 || u.col.g < 120 || u.col.b < 120) {
            if (u.col.r >= 17) {
                u.col.r = u.col.r - 16;
            } else {
                u.col.r = 0;
            }
            if (u.col.g >= 17) {
                u.col.g = u.col.g - 16;
            } else {
                u.col.g = 0;
            }
            if (u.col.b >= 17) {
                u.col.b = u.col.b - 16;
            } else {
                u.col.b = 0;
            }
        }
        if (texLayout[no].f2C != e->f10) {
            if (e->f6C_b3 != 0 && sel == 0 && (flag != 0 || e->f10 >= 0)) {
                u.col.r = u.col.r * 0.5f;
                u.col.g = u.col.g * 0.5f;
                u.col.b = u.col.b * 0.5f;
            }
        }
        gif_SpriteSensitiveOffset(&box, 0xFFFFFF9B, &ofs, &u.col, 1);

        if (e->f6C_b3 != 0 && sel != 0 && fadeState == 8) {
            float t = (float)fadeCount / (float)fadeLength;

            lt_glow_sprite(&box, &ofs, 80, 80, 80, t, 55, 50);
            lt_glow_sprite(&box, &ofs, 30, 30, 30, t, 110, 100);
        } else if (e->f6C_b3 != 0 && sel != 0 && glowOn != 0) {
            lt_glow_sprite(&box, &ofs, 54, 80, 115, (float)glowCount / (float)glowLength, 32, 32);
        }
        gif_SetZWrite(1);
        gif_EndPacket();
    }
}

/* source lines 715-735 */
static inline void lt_draw_primary_sprite(SprCol *col)
{
    SprRect r;

    gif_StartPacketPri(11);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 7, 0);
    r = primarySpriteRect;
    gif_SpriteSensitive(&r, 0xFFFFFFFF, (void *)0, col, 1);
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_EndPacket();
}

void display_primary_texture_layout(int no, int sel)
{
    SprCol col;
    LtProp *p = &texLayout[no];
    int m;
    int flag;

    col.r = (int)(p->f10 * 255.0f);
    col.g = (int)(p->f14 * 255.0f);
    col.b = (int)(p->f18 * 255.0f);
    col.a = (int)(p->f1C * 127.0f);
    lt_draw_primary_sprite(&col);
    if (p->f20 != 0 && (fadeState == 1 || fadeState == 2)) {
        if (p->f2C >= 0) {
            int *e = (int *)((char *)texProperty + p->f2C * 0x70);

            m = e[0x1B] & 3;
        } else {
            m = 0;
        }
        sel = ((int (*)(int, int))p->f20)(ltSelectFlag, sel);
        if (sel != -1) {
            flag = 0;
            if ((pad.trigger & 0x40) != 0) {
                flag = m == 1;
            }
            if ((fadeState == 2 && sel != current_layout_id) || sel == 62) {
                nextLayout = sel;
                display_texture_fade_cancel_chk(current_layout_id, sel);
                if (fadeType == 1) {
                    fadeState = 5;
                } else {
                    nextFadeState = 3;
                    fadeState = flag ? 7 : 3;
                }
            }
        } else if ((pad.trigger & 0x40) != 0) {
            if (m == 2) {
                nextFadeState = m;
                fadeState = 7;
            }
        }
        ltSelectFlag = 0;
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

    if (frame_count - selectFrame == 0 || frame_count - selectFrame == 1) {
        pad.trigger = 0;
    }
    p = &texLayout[current_layout_id];
    for (;;) {
        for (j = p->first; j < p->last; j++) {
            LtProperty *e = &texProperty[j];

            e->f6C_b4 = e->f6C_b5;
        }
        if (p->link >= 0) {
            list[n++] = p->link;
            p = &texLayout[p->link];
        } else {
            break;
        }
    }
    list[n] = -1;
    for (n--; n != -1; n--) {
        p = &texLayout[list[n]];
        v = p->f2C;
        ltCurrentItem = v;
        if (p->f20 != 0 && (fadeState == 1 || fadeState == 2)) {
            ret = ((int (*)(int, int))p->f20)(p->f24, ret);
            p->f24 = 0;
            v = p->f2C;
        } else {
            ret = -1;
        }
        if (v >= 0 && lt_item_select_disable == 0) {
            default_item_select(list[n]);
        }
    }
    p = &texLayout[current_layout_id];
    ltCurrentItem = p->f2C;
    display_primary_texture_layout(current_layout_id, ret);
    if (p->f2C >= 0 && lt_item_select_disable == 0) {
        default_item_select(current_layout_id);
    }
    for (k = 0; list[k] >= 0; k++) {
        lt_draw_layout(list[k]);
    }
    lt_item_select_disable = 0;
}

/* census init_textures_of_specified_property, a file static; MAIN.MAP carries no
   global of that name, so ico2/common/src/kanban's twin is a static too and
   `static` here keeps this one's ELF symbol local */
extern char texFile[][0x34];
extern char D_0030D014[];
extern char *strtok(char *s, const char *sep);
extern char *strrchr(const char *s, int c);
extern void __assert(char *file, int line, char *expr);

/* source lines 1249-1259 */
static inline char *lt_texture_base_name(char *src)
{
    char buf[256];
    char *p;
    char *t;

    p = buf;

    strcpy(buf, src);

    t = strtok(buf, "/");
    if (t != 0) {
        do {
            p = t;
            t = strtok(0, "/");
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

    n = texProperty[idx].f58;
    src = texFile[n];
    name = lt_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy("no texture loaded.(%s)\n", src);
        debug_assert(__FILE__, 0x507);
        __assert(__FILE__, 0x507, "0");
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
    int i = stageData[stage].layoutFirst;
    int last = stageData[stage].layoutLast;

    for (; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
    ltCurrentItem = texLayout[current_layout_id].f28;
}

void init_layout_texture(int stage)
{
    fadeCallback = 0;
    if (stage == 1) {
        gflagInit();
        if (layout_boot_flag == 0) {
            current_layout_id = 7;
        } else if (mpegPlayReturnStage == stage) {
            mpegPlayReturnStage = 0;
            if (stage_after_skipping_demo == 0xFFFFFFFE) {
                title_demo_mode = title_demo_mode ^ 1;
                current_layout_id = 13;
            } else if (stage_after_skipping_demo == 0xFFFFFFFF) {
                current_layout_id = 10;
                title_demo_mode = title_demo_mode ^ 1;
            } else {
                current_layout_id = 13;
            }
        } else {
            current_layout_id = 13;
        }
    } else {
        current_layout_id = 54;
    }
    lt_init_stage_textures(stage);
    texLayout[current_layout_id].f2C = texLayout[current_layout_id].f28;
    ltSelectFlag = 1;
    fadeState = 0;
    lt_reset_property_chain(current_layout_id);
}

inline void lt_switch_layout(int no)
{
    if ((fadeState == 2 && no != current_layout_id) || no == 62) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            nextFadeState = 3;
            fadeState = 3;
        }
    }
}

inline int lt_current_property_item(void)
{
    return ltCurrentItem;
}

inline int lt_link_layout(int dir)
{
    switch (dir) {
    case 0:
        return texProperty[lt_current_property_item()].right;
    case 1:
        return texProperty[lt_current_property_item()].left;
    case 2:
        return texProperty[lt_current_property_item()].down;
    case 3:
        return texProperty[lt_current_property_item()].up;
    }
    return -1;
}

inline int lt_prev_layout(int stage)
{
    current_layout_id = current_layout_id - 1;
    if (current_layout_id < stageData[stage].layoutFirst) {
        current_layout_id = stageData[stage].layoutLast - 1;
    }
    lt_switch_layout(current_layout_id);
    return current_layout_id;
}

inline int lt_next_layout(int stage)
{
    current_layout_id = current_layout_id + 1;
    if (current_layout_id >= stageData[stage].layoutLast) {
        current_layout_id = stageData[stage].layoutFirst;
    }
    lt_switch_layout(current_layout_id);
    return current_layout_id;
}

inline void lt_mask_property(int idx, int flag)
{
    LtProperty *p = &texProperty[idx];
    p->f6C_b4 = flag & 1;
}

inline void lt_default_mask_property(int idx, int flag)
{
    LtProperty *p = &texProperty[idx];
    p->f6C_b5 = flag & 1;
}

inline int lt_fade_status(void)
{
    return fadeState;
}

inline void lt_set_item_select_func(int val)
{
    fadeCallback = val;
}

inline void lt_set_fade_mode(int val)
{
    fadeType = val;
}
