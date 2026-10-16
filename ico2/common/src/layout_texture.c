#include "typedef.h"
#include "layout_texture.h"
#include "debug.h"
#include "StageManager.h"
#include "gflag.h"
#include "layout_action.h"
#include <string.h>
#include <stdlib.h>
#include "debug_exception.h"
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

static inline void lt_draw_layout(int no) /* derived name */
{
    int i = texLayout[no].first;
    int last = texLayout[no].last;

    for (; i < last; i++) {
        display_texture(no, &texProperty[i]);
    }
}

/* lt_switch_layout's body as default_item_select's two call sites have it */
static inline void lt_switch_layout_3(int no) /* derived name */
{
    if ((fadeState == 2 && no != current_layout_id) || no == 58) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
            fadeState = 3;
        }
    }
}

static void default_item_select(int no)
{
    LtProp *p = &texLayout[no];
    LtProperty *e = &texProperty[p->curItem];
    int prev;

    if (p->curItem < 0) {
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
        prev = p->curItem;
        if ((pad[0].flags & 0x1000) && e->upItem >= 0) {
            p->curItem = e->upItem;
        } else if ((pad[0].flags & 0x4000) && e->downItem >= 0) {
            p->curItem = e->downItem;
        } else if ((pad[0].flags & 0x8000) && e->leftItem >= 0) {
            p->curItem = e->leftItem;
        } else if ((pad[0].flags & 0x2000) && e->rightItem >= 0) {
            p->curItem = e->rightItem;
        }
        if (p->curItem != prev) {
            soundSeDefPlay(399, 0xFFFFFFFE, 0, 0);
        }
    } else {
        p->curItem = ((int (*)(int))fadeCallback)(p->curItem);
        fadeCallback = 0;
    }
    if (pad[0].flags & 0x40) {
        if (e->right >= 0) {
            if (fadeState == 2) {
                soundSeDefPlay(400, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_3(e->right);
                return;
            }
        }
    }
    if (pad[0].flags & 0x10) {
        if (e->left >= 0) {
            if (fadeState == 2) {
                soundSeDefPlay(401, 0xFFFFFFFE, 0, 0);
                lt_switch_layout_3(e->left);
            }
        }
    }
}

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

/* a file static */
static void display_texture(int no, LtProperty *e)
{
    SprRect ofs;
    SprRect box;

    int pt[2];

    int sel;
    int i;

    ofs.x = (e->texU << 4) + 8;
    ofs.y = (e->texV << 4) + 8;
    ofs.w = e->texW << 4;
    ofs.h = e->texH << 4;

    box.w = e->dispW << 4;
    box.h = e->dispH << 3;
    if (box.w == 0) {
        box.w = ofs.w;
    }
    if (box.h == 0) {
        box.h = ofs.h >> 1;
    }
    if (e->centerX != 0) {
        box.x = (10240 - box.w) / 2 - 5120;
    } else {
        box.x = (e->dispX - 320) * 16;
    }
    box.y = (e->dispY - 113) * 16;

    sel = (e == &texProperty[texLayout[no].curItem]);
    if (sel && lt_item_select_disable == 0 && fadeState == 2) {
        SprCol pcol = {128, 128, 128, 127};

        gif_StartPacketPri(11);
        gif_SetZTest(0);
        for (i = 0; i < box.w * box.h / 1200; i++) {
            pt[0] = box.x + rand() % box.w;
            pt[1] = box.y + rand() % box.h;
            pcol.a = rand() % 127 + 32;
            gif_PointOffset(pt, 0x800000, &pcol, 1);
        }
        gif_EndPacket();
    }
    if (e->masked == 0) {
        tex_TransTexture(e->texNo, 11);

        gif_StartPacketPri(11);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 7, 0);
        box.y = box.y + 8;
        box.h = box.h - 8;
        ofs.h = ofs.h - 8;
        if (e->fade_cancel == 0) {
            ltCursorColor[0] = ~GlobalStageSetting.reductionCol[0];
            ltCursorColor[1] = ~GlobalStageSetting.reductionCol[1];
            ltCursorColor[2] = ~GlobalStageSetting.reductionCol[2];
            gif_SpriteSensitiveOffset(&box, 0xFFFFFF9B, &ofs, (SprCol *)ltCursorColor, 1);
        } else {
            ltHighlightColor.r = ~GlobalStageSetting.reductionCol[0];
            ltHighlightColor.g = ~GlobalStageSetting.reductionCol[1];
            ltHighlightColor.b = ~GlobalStageSetting.reductionCol[2];
            gif_SpriteSensitiveOffset(&box, 0xFFFFFF9B, &ofs, &ltHighlightColor, 1);
        }
        gif_SetZWrite(1);
        gif_EndPacket();
    }
}

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

static void display_primary_texture_layout(int no, int sel)
{
    SprCol col;
    LtProp *p = &texLayout[no];

    col.r = (int)(p->colR * 255.0f);
    col.g = (int)(p->colG * 255.0f);
    col.b = (int)(p->colB * 255.0f);
    col.a = (int)(p->colA * 127.0f);
    lt_draw_primary_sprite(&col);
    if (p->proc != 0 && (fadeState == 1 || fadeState == 2)) {
        sel = p->proc(ltSelectFlag, sel);
        if (sel != -1) {
            lt_switch_layout_3(sel);
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

    p = &texLayout[current_layout_id];
    for (;;) {
        for (j = p->first; j < p->last; j++) {
            LtProperty *e = &texProperty[j];

            e->masked = e->defaultMask;
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
        v = p->curItem;
        ltCurrentItem = v;
        if (p->proc != 0 && (fadeState == 1 || fadeState == 2)) {
            ret = p->proc(p->procFirst, ret);
            p->procFirst = 0;
            v = p->curItem;
        } else {
            ret = -1;
        }
        if (v >= 0 && lt_item_select_disable == 0) {
            default_item_select(list[n]);
        }
    }
    p = &texLayout[current_layout_id];
    ltCurrentItem = p->curItem;
    display_primary_texture_layout(current_layout_id, ret);
    if (p->curItem >= 0 && lt_item_select_disable == 0) {
        default_item_select(current_layout_id);
    }
    for (k = 0; list[k] >= 0; k++) {
        lt_draw_layout(list[k]);
    }
    lt_item_select_disable = 0;
}

/* init_textures_of_specified_property is a file static, as is
   ico2/common/src/kanban's function of the same name */
/* texProperty's texNo column, &texProperty[0].texNo */
extern char D_002E8208[];
/* sce/'s string.h does not declare it */
extern char *strtok(char *s, const char *sep);

static inline char *lt_texture_base_name(const char *src) /* derived name */
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
    const char *src;
    char *name;
    int no;

    n = texProperty[idx].texFileNo;
    src = texFile[n].path;
    name = lt_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy("no texture loaded.(%s)\n", src);
        debug_assert(__FILE__, 1054);
        __assert(__FILE__, 1054, "0");
    }
    return no;
}

static void init_textures_of_specified_property(int first, int last)
{
    int i;
    int no;

    for (i = first; i < last; i++) {
        no = lt_texture_no_of_property(i);
        *(int *)(D_002E8208 + i * 108) = no;
        *(void **)(D_002E8208 + i * 108 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_002E8208 + i * 108 - 4), 1, 1);
    }
}

static inline void lt_init_stage_textures(int stage) /* derived name */
{
    int i = stageData[stage].layoutFirst;
    int last = stageData[stage].layoutLast;

    for (; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
    ltCurrentItem = texLayout[current_layout_id].defaultItem;
}

void init_layout_texture(int stage)
{
    fadeCallback = 0;
    if (stage == 1) {
        gflagInit();
        if (layout_boot_flag == 0) {
            current_layout_id = 4;
        } else if (mpegPlayReturnStage == stage) {
            mpegPlayReturnStage = 0;
            if (stage_after_skipping_demo == 0xFFFFFFFE) {
                title_demo_mode = title_demo_mode ^ 1;
                current_layout_id = 10;
            } else if (stage_after_skipping_demo == 0xFFFFFFFF) {
                current_layout_id = 7;
                title_demo_mode = title_demo_mode ^ 1;
            } else {
                current_layout_id = 10;
            }
        } else {
            current_layout_id = 10;
        }
    } else {
        current_layout_id = 50;
    }
    lt_init_stage_textures(stage);
    texLayout[current_layout_id].curItem = texLayout[current_layout_id].defaultItem;
    ltSelectFlag = 1;
    fadeState = 0;
    lt_reset_property_chain(current_layout_id);
}

inline void lt_switch_layout(int no)
{
    if ((fadeState == 2 && no != current_layout_id) || no == 58) {
        nextLayout = no;
        display_texture_fade_cancel_chk(current_layout_id, no);
        if (fadeType == 1) {
            fadeState = 5;
        } else {
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
