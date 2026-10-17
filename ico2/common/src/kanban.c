#include "typedef.h"
#include "debug.h"
#include "Texture.h"
#include "debug_exception.h"
#include "layout_texture.h"
#include <assert.h>
#include "charFileManager.h"
#include "kanban.h"

typedef union { /* field names derived */
    int i[4];
    char b[16];
} Pkt16; /* derived name */

/* The list head and the sign the layout key follows (.sbss), and the pool
   (.bss) of thirty signs that kanbanReqAdd and kanbanReqAllDel walk. */
static Kanban *kanbanList; /* derived name */

static Kanban *kanbanCurrent; /* derived name */

static Kanban kanbanNodes[30]; /* derived name */

/* kanban quest box over */
static const char kanbanOverMsg[] = "かんばんクエストボックスオーバー\n"; /* derived name */

/* The sprite the kanban is drawn as, {x, y, width, height} centred on the
   origin, the same rectangle src/staffroll.c uses for the roll. */
static const Pkt16 kanbanSprite = {{-5120, -1792, 10240, 3584}}; /* derived name */

/* .sdata: kanbanCommonRead and the sign's initial colour */
int kanbanCommonRead = 0;

/* the colour a new sign starts with */
static KanbanCol kanbanStartCol = {{0x80, 0x80, 0x80, 0}}; /* derived name */

/* texProperty's texNo column, &texProperty[0].texNo */
extern char D_0030D014[];
/* a file static, as are the functions of the same name in
   ico2/fumi/src/jimaku and ico2/common/src/layout_texture */
static void display_texture(LtProp *pr, LtProperty *e, KanbanCol *col);
/* sce/'s string.h does not declare it */
extern char *strtok(char *s, const char *sep);
/* GifPacket.h's entry points, which this TU does not include; the sprite
   calls take z as an unsigned int here, a long long in the header */
extern void gif_EndPacket(void);
extern void gif_SetAlpha(long long alpha, long long mode, long long fix);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SpriteSensitive(int *r, unsigned int z, int *uv, unsigned char *col, int prim);
extern void gif_SpriteSensitiveOffset(int *r, unsigned int z, int *uv, unsigned char *col,
                                      int prim);
extern void gif_PointOffset(int *v, long long z, unsigned char *col, int prim);
extern void gif_StartPacketPri(int pri);

#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "include_asm.h"

static void init_textures_of_specified_property(int first, int last);

static inline char *get_texture_base_name(char *src) /* derived name */
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

/* The texture-number lookup PAL's init_textures_of_specified_property inlines
   is not carried: that function is a stub here, and the demo's form of the
   lookup prints no "tex_id" line (its two strings are the stub's row). */

static inline void init_textures_of_property_range(int first, int last) /* derived name */
{
    int i;

    for (i = first; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
}

static inline int kanban_layout_key(LtProp *pr) /* derived name */
{
    int ret = 0;
    LtProperty *e = &texProperty[pr->curItem];

    if ((pad[0].flags & 0x1000) && e->upItem > 0) {
        pr->curItem = e->upItem;
    } else if ((pad[0].flags & 0x4000) && e->downItem > 0) {
        pr->curItem = e->downItem;
    } else if ((pad[0].flags & 0x8000) && e->leftItem > 0) {
        pr->curItem = e->leftItem;
    } else if ((pad[0].flags & 0x2000) && e->rightItem > 0) {
        pr->curItem = e->rightItem;
    } else {
        unsigned long button = pad[0].flags;

        if (button & 0x40) {
            ret = 1;
        } else {
            ret = (button & 0x10) ? 2 : 0;
        }
    }
    return ret;
}

Kanban *kanbanReqAdd(int no, int pri)
{
    Kanban *p;
    LtProp *pr;
    Kanban *cur;
    int i;

    p = kanbanNodes;
    pr = &texLayout[no];
    for (i = 0; i < 30; i++, p++) {
        if (p->layout == 0)
            goto found;
    }
    debug_StdPrintfDummy(kanbanOverMsg);
    return 0;

found:
    p->layout = pr;
    p->key = 0;
    pr->curItem = pr->defaultItem;
    p->flags &= ~1;
    p->alpha = 0;
    p->col = kanbanStartCol;
    p->pri = pri;
    cur = kanbanList;
    if (cur != 0) {
        if (pri < cur->pri) {
            cur->prev = p;
            p->next = cur;
            p->prev = 0;
            kanbanList = p;
        } else {
            for (;;) {
                if (cur->next == 0) {
                    goto append;
                }
                if (pri < cur->pri) {
                    break;
                }
                cur = cur->next;
            }
            p->prev = cur->prev;
            cur->prev = p;
            p->next = cur;
            goto done;
        append:
            cur->next = p;
            p->prev = cur;
            p->next = 0;
        }
    } else {
        kanbanList = p;
        p->prev = 0;
        p->next = 0;
    }
done:
    if (pr->defaultItem != -1) {
        kanbanCurrent = p;
    }
    return p;
}

INCLUDE_ASM(init_textures_of_specified_property_kanban);

INCLUDE_ASM(kanbanInit);

INCLUDE_ASM(display_texture_kanban);

static int fade_exec(Kanban *p)
{
    int ret = 0;
    float f;

    if ((p->flags & 1) == 0) {
        f = 127.0f /
            (p->layout->fadeInTime * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (f == 0.0f) {
            f = 127.0f;
        }

        p->alpha = p->alpha + f;
        if (p->alpha > 127.0f) {
            p->alpha = 127.0f;
            ret = 1;
        }
    } else {
        f = 127.0f /
            (p->layout->fadeOutTime * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (f == 0.0f) {
            f = 127.0f;
        }
        p->alpha = p->alpha - f;
        if (p->alpha < 0.0f) {
            p->alpha = 0.0f;
            ret = -1;
        }
    }
    p->col.b[3] = (char)p->alpha;
    return ret;
}

static void display_layout(Kanban *k);

INCLUDE_ASM(display_layout);

INCLUDE_ASM(kanbanReqDel);

INCLUDE_ASM(kanbanReqAllDel);

INCLUDE_ASM(kanbanReqAllDelFade);

INCLUDE_ASM(kanbanExec);

INCLUDE_ASM(func_001A3140);
