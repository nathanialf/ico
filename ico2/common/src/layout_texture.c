#include "typedef.h"
#include "layout_texture.h"
#include "debug.h"
#include "StageManager.h"
#include "gflag.h"
#include "layout_action.h"
#include <string.h>
#include <stdlib.h>
#include "debug_exception.h"
#include "tableSin.h"
#include "s_init.h"
#include <assert.h>
#include "charFileManager.h"
#include "main.h"

typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SprCol; /* derived name */

/* .sdata: the continue screen's decided flag, which
   layout_action sets and op's countdown waits on; the two highlight colours;
   the current layout; the selected item; the item-select handler's flag; the
   fade state and type; lt_item_select_disable; the fade-end handler; the
   highlight blink's count and length. */
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

/* .sbss, two words: the pad buttons of the last frame and the layout
   switched to. */
static int lastButton; /* derived name */

static int nextLayout; /* derived name */

/* memset with an int count, which this TU's calls pin over <string.h>'s
   unsigned one */
extern void *memset(void *dst, int c, int n);

#include "Texture.h"
#include "include_asm.h"

static void default_item_select(int no);

/* The sprite rectangle the gif helpers take: origin and size, in 1/16 pixels. */
typedef struct { /* field names derived */
    int x;
    int y;
    int w;
    int h;
} SprRect; /* derived name */

/* the screen rectangle lt_draw_primary_sprite draws, in 1/16 pixels: 640 x 226
   pixels centred on the origin */
static const SprRect primarySpriteRect = {-5120, -1808, 10240, 3616}; /* derived name */

static void display_texture_fade_cancel_chk(int from, int to)
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

            if (p->texFileNo == q->texFileNo && p->texU == q->texU && p->texV == q->texV &&
                p->texW == q->texW && p->texH == q->texH && p->dispX == q->dispX &&
                p->dispY == q->dispY && p->dispW == q->dispW && p->dispH == q->dispH) {
                q->fade_cancel = 1;
                p->fade_cancel = 1;
            }
        }
    }
}

void lt_analog2Pad(void)
{
    if (pad[0].ana[3] < 20) {
        pad[0].now |= 0x1000;
        if ((lastButton & 0x1000) == 0) {
            pad[0].flags |= 0x1000;
        }
    }
    if (pad[0].ana[3] >= 236) {
        pad[0].now |= 0x4000;
        if ((lastButton & 0x4000) == 0) {
            pad[0].flags |= 0x4000;
        }
    }
    if (pad[0].ana[2] < 20) {
        pad[0].now |= 0x8000;
        if ((lastButton & 0x8000) == 0) {
            pad[0].flags |= 0x8000;
        }
    }
    if (pad[0].ana[2] >= 236) {
        pad[0].now |= 0x2000;
        if ((lastButton & 0x2000) == 0) {
            pad[0].flags |= 0x2000;
        }
    }
    lastButton = pad[0].now;
}

/* a file static (src/jimaku has a global of the same name and src/kanban a
   file static) */
static void display_texture(int no, LtProperty *e);

/* whether property item no is shown; the second range is a conditional
   expression */
static inline int lt_property_visible(int no) /* derived name */
{
    int vis = 1;

    if (gFlagGameClear == 0 && current_layout_id == 58 && no >= 300 &&
        (no < 308 || (no < 330 ? no >= 325 : 0))) {
        vis = 0;
    }
    return vis;
}

static inline void lt_draw_layout(int no) /* derived name */
{
    int i = texLayout[no].first;
    int last = texLayout[no].last;

    for (; i < last; i++) {
        if (lt_property_visible(i)) {
            display_texture(no, &texProperty[i]);
        }
    }
}

/* lt_switch_layout's body as default_item_select's two call sites have it.
   The copies differ: the first site's else arm sets fadeState to 7 where the
   out-of-line function and the second site set 3. */
static inline void lt_switch_layout_7(int no) /* derived name */
{
    if ((fadeState == 2 && no != current_layout_id) || no == 62) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            fadeState = 7;
        }
    }
}

static inline void lt_switch_layout_3(int no) /* derived name */
{
    if ((fadeState == 2 && no != current_layout_id) || no == 62) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            fadeState = 3;
        }
    }
}

INCLUDE_ASM(default_item_select);

static inline void lt_reset_property_chain(int no) /* derived name */
{
    LtProp *p = &texLayout[no];
    int i = p->link;

    while (i >= 0) {
        p = &texLayout[i];
        p->curItem = p->defaultItem;
        p->procFirst = 1;
        i = p->link;
    }
}

/* the layout fade's state machine; fadeState is read and written as the
   file static itself, as in the rest of this TU */
static void texture_fading(LtProp *p)
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
            if (p->fadeInTime == 0.0f) {
                fadeState = 2;
            }
            break;
        case 3:
            if (p->fadeOutTime == 0.0f) {
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
        ltBlinkLength = (int)(p->fadeInTime * ((60 - systemStatus[0] * 10) / systemStatus[1]));
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
    case 3:
        fadeState = 4;
        ltBlinkLength = (int)(p->fadeOutTime * ((60 - systemStatus[0] * 10) / systemStatus[1]));
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
        cur = &texLayout[current_layout_id].curItem;
        *cur = texLayout[current_layout_id].defaultItem;
        ltSelectFlag = 1;
        fadeState = 0;
        if (texLayout[current_layout_id].fadeInTime == 0.0f) {
            lt_item_select_disable = 1;
            fadeState = 2;
        }
        lt_reset_property_chain(current_layout_id);
        break;
    }
}

/* GifPacket.h's entry points, which this TU does not include: its calls pass
   the sprites' z as a 32-bit unsigned int, where the header takes a long
   long */
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(long long alpha, long long mode, long long fix);
extern void gif_SpriteSensitive(SprRect *r, unsigned int z, SprRect *uv, SprCol *col, int prim);
extern void gif_EndPacket(void);
extern void gif_SpriteSensitiveOffset(SprRect *r, unsigned int z, SprRect *uv, SprCol *col,
                                      int prim);
extern void gif_PointOffset(int *v, long long z, SprCol *col, int prim);
extern void gif_SetGsReg(long long reg, long long data);

/* the pulsing highlight sprite, inlined three times by display_texture */
static inline void lt_glow_sprite(SprRect *box, SprRect *ofs, int r, int g, int b, float t, int dx,
                                  int dy) /* derived name */
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

/* a file static */
INCLUDE_ASM(display_texture_layout_texture);

static inline void lt_draw_primary_sprite(SprCol *col) /* derived name */
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

INCLUDE_ASM(display_primary_texture_layout);

INCLUDE_ASM(exec_layout_texture);

/* init_textures_of_specified_property is a file static, as is
   ico2/common/src/kanban's function of the same name */
/* texProperty's texNo column, &texProperty[0].texNo */
extern char D_002E3508[];
/* sce/'s string.h does not declare it */
extern char *strtok(char *s, const char *sep);

static inline char *lt_texture_base_name(char *src) /* derived name */
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

static inline int lt_texture_no_of_property(int idx) /* derived name */
{
    int n;
    char *src;
    char *name;
    int no;

    n = texProperty[idx].texFileNo;
    src = texFile[n].path;
    name = lt_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy("no texture loaded.(%s)\n", src);
        debug_assert(__FILE__, 1287);
        __assert(__FILE__, 1287, "0");
    }
    return no;
}

static void init_textures_of_specified_property(int first, int last);

INCLUDE_ASM(init_textures_of_specified_property_layout_texture);

static inline void lt_init_stage_textures(int stage) /* derived name */
{
    int i = stageData[stage].layoutFirst;
    int last = stageData[stage].layoutLast;

    for (; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
    ltCurrentItem = texLayout[current_layout_id].defaultItem;
}

INCLUDE_ASM(init_layout_texture);

inline void lt_mask_property(int idx, int flag)
{
    LtProperty *p = &texProperty[idx];
    p->masked = flag & 1;
}

inline void lt_default_mask_property(int idx, int flag)
{
    LtProperty *p = &texProperty[idx];
    p->defaultMask = flag & 1;
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

INCLUDE_ASM(lt_switch_layout);

INCLUDE_ASM(lt_current_property_item);

INCLUDE_ASM(lt_link_layout);

INCLUDE_ASM(lt_prev_layout);

INCLUDE_ASM(lt_next_layout);
