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

/* .sdata: the two highlight colours (this build has no continue-screen
   decided flag in front of them, which PAL has);
   the current layout; the selected item; the item-select handler's flag; the
   fade state and type; lt_item_select_disable; the fade-end handler; the
   highlight blink's count and length. */
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

/* .sbss, one word: the layout switched to, which lt_switch_layout,
   lt_next_layout and lt_prev_layout set and texture_fading reads (this build
   keeps no button, glow, selection or fade state here: no function of the
   demo addresses one). */
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

static void display_texture_fade_cancel_chk(int from, int to);

INCLUDE_ASM(display_texture_fade_cancel_chk);

void lt_analog2Pad(void);
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

/* defined before texture_fading: the demo's .rodata has the rectangle it
   reads (gcc writes it at that first use) before that function's jump table */
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

/* the layout fade's state machine; fadeState is read and written as the
   file static itself, as in the rest of this TU */
INCLUDE_ASM(texture_fading);

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

INCLUDE_ASM(display_primary_texture_layout);

INCLUDE_ASM(exec_layout_texture);

/* init_textures_of_specified_property is a file static, as is
   ico2/common/src/kanban's function of the same name */
/* texProperty's texNo column, &texProperty[0].texNo */
extern char D_0030D014[];
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

/* PAL's inline texture-number lookup is not carried: its only caller,
   init_textures_of_specified_property, is a stub here, and the lookup's two
   strings are that stub's row. */

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

INCLUDE_ASM(lt_switch_layout);

INCLUDE_ASM(lt_current_property_item);

INCLUDE_ASM(lt_link_layout);

INCLUDE_ASM(lt_prev_layout);

INCLUDE_ASM(lt_next_layout);

INCLUDE_ASM(lt_mask_property);

INCLUDE_ASM(lt_default_mask_property);

INCLUDE_ASM(lt_fade_status);

INCLUDE_ASM(lt_set_item_select_func);

INCLUDE_ASM(lt_set_fade_mode);
