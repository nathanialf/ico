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
#ifdef VERSION_JUN26
extern char D_002CC054[];
#else
#ifdef VERSION_AUG6
extern char D_002E3508[];
#else
#ifdef VERSION_NTSC
extern char D_002E8208[];
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
#ifdef VERSION_KOR
extern char D_0030A6EC[];
#else
extern char D_0030A66C[];
#endif
#else
extern char D_0030D014[];
#endif
#endif
#endif
#endif

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

static void init_textures_of_specified_property(int first, int last);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
static inline char *get_texture_base_name(const char *src) /* derived name */
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
static inline char *get_texture_base_name(const char *src) /* derived name */
#else
static inline char *get_texture_base_name(char *src) /* derived name */
#endif
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
#endif

static inline int get_texture_no_of_property(int idx) /* derived name */
{
    int n;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)
    const char *src;
#else
#ifdef VERSION_JUN26
    const char *src;
#else
    char *src;
#endif
#endif
    char *name;
    int no;

    n = texProperty[idx].texFileNo;
    src = texFile[n].path;
#ifdef VERSION_JUN26
    name = get_texture_base_name((char *)src);
#else
    name = get_texture_base_name(src);
#endif

    no = tex_GetTextureNo(name);

    if (no < 0) {
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_NTSC)
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        debug_StdPrintfDummy("tex_id %d\n", n);
#endif
#endif
        debug_StdPrintfDummy("no texture loaded.(%s)\n", src);
        debug_assert(__FILE__, LN(272, 265, 265, 255, 255, 255));
        __assert(__FILE__, LN(272, 265, 265, 255, 255, 255), "0");
    }
    return no;
}

static inline void init_textures_of_property_range(int first, int last) /* derived name */
{
    int i;

    for (i = first; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
}

static inline int kanban_layout_key(LtProp *pr) /* derived name */
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int ret;
    unsigned int button;
#else
    int ret = 0;
#endif
    LtProperty *e = &texProperty[pr->curItem];

    if ((pad[0].flags & 0x1000) && e->upItem > 0) {
        pr->curItem = e->upItem;
    } else if ((pad[0].flags & 0x4000) && e->downItem > 0) {
        pr->curItem = e->downItem;
    } else if ((pad[0].flags & 0x8000) && e->leftItem > 0) {
        pr->curItem = e->leftItem;
    } else if ((pad[0].flags & 0x2000) && e->rightItem > 0) {
        pr->curItem = e->rightItem;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    }
    button = pad[0].flags;
    ret = 0;
    if (button & 0x40) {
        ret = 1;
    }
    if (button & 0x10) {
        ret = 2;
#else
    } else {
        unsigned long button = pad[0].flags;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        if (button & 0x20) {
#else
        if (button & 0x40) {
#endif
            ret = 1;
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            ret = (button & 0x40) ? 2 : 0;
#else
            ret = (button & 0x10) ? 2 : 0;
#endif
        }
#endif
    }
    return ret;
}

inline void kanbanReqAllDel(void)
{
    int i;
    for (i = 29; i >= 0; i--) {
        kanbanNodes[i].layout = 0;
    }
    kanbanList = 0;
    kanbanCurrent = 0;
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

inline void kanbanReqDel(Kanban *self)
{
    Kanban *prev = self->prev;
    Kanban *next = self->next;
    if (prev == 0) {
        kanbanList = next;
        if (next != 0) {
            next->prev = 0;
        }
    } else {
        prev->next = next;
        if (next != 0) {
            self->next->prev = self->prev;
        }
    }
    self->layout = 0;
}

inline void kanbanReqDelFade(Kanban *self)
{
    Kanban *cur = kanbanCurrent;
    self->flags |= 1;
    if (self == cur) {
        kanbanCurrent = 0;
    }
}

inline void kanbanReqAllDelFade(void)
{
    Kanban *p = kanbanNodes;
    int i = 29;
    do {
        if (p->layout != 0) {
            p->flags |= 1;
        }
        i--;
        p++;
    } while (i >= 0);
}

static void init_textures_of_specified_property(int first, int last)
{
    int i;
    int no;

    for (i = first; i < last; i++) {
#ifdef VERSION_NTSC
        no = get_texture_no_of_property(i);
        *(int *)(D_002E8208 + i * 108) = no;
        *(void **)(D_002E8208 + i * 108 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_002E8208 + i * 108 - 4), 1, 1);
#else
#ifdef VERSION_AUG6
        no = get_texture_no_of_property(i);
        *(int *)(D_002E3508 + i * 108) = no;
        *(void **)(D_002E3508 + i * 108 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_002E3508 + i * 108 - 4), 1, 1);
#else
#ifdef VERSION_JUN26
        no = get_texture_no_of_property(i);
        *(int *)(D_002CC054 + i * 88) = no;
        *(void **)(D_002CC054 + i * 88 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_002CC054 + i * 88 - 4), 1, 1);
#else
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
        debug_StdPrintfDummy("propertyId %d\n", i);
#endif
        no = get_texture_no_of_property(i);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
#ifdef VERSION_KOR
        *(int *)(D_0030A6EC + i * 0x70) = no;
        *(void **)(D_0030A6EC + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030A6EC + i * 0x70 - 4), 1, 1);
#else
        *(int *)(D_0030A66C + i * 0x70) = no;
        *(void **)(D_0030A66C + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030A66C + i * 0x70 - 4), 1, 1);
#endif
#else
        *(int *)(D_0030D014 + i * 0x70) = no;
        *(void **)(D_0030D014 + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030D014 + i * 0x70 - 4), 1, 1);
#endif
#endif
#endif
#endif
    }
}

void kanbanInit(int no)
{
    if (no != 0) {
        init_textures_of_property_range(stageData[no].layoutFirst, stageData[no].layoutLast);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)
        init_textures_of_property_range(0, 4);
#else
#ifdef VERSION_JUN26
        init_textures_of_property_range(0, 4);
#else
        init_textures_of_property_range(0, 1);
#endif
#endif
        kanbanReqAllDel();
        kanbanCommonRead = 1;
    }
}

#ifdef VERSION_NTSC
static void display_texture(LtProp *pr, LtProperty *e, KanbanCol *col)
{
    int uv[4];
    int r[4];
    int pt[4];
    int i;

    uv[0] = (e->texU << 4) + 8;
    uv[1] = (e->texV << 4) + 8;
    uv[2] = e->texW << 4;
    uv[3] = e->texH << 4;

    r[2] = e->dispW << 4;
    r[3] = e->dispH << 3;
    if (r[2] == 0) {
        r[2] = uv[2];
    }
    if (r[3] == 0) {
        r[3] = uv[3] >> 1;
    }

    if (e->centerX) {
        r[0] = (0x2800 - r[2]) / 2 - 0x1400;
    } else {
        r[0] = (e->dispX - 320) << 4;
    }
    r[1] = (e->dispY - 112) << 4;

    if (e->masked == 0) {
        tex_TransTexture(e->texNo, 11);

        gif_StartPacketPri(11);

        gif_SetAlpha(1, 7, 0);

        gif_SetZWrite(0);

        r[1] += 8;

        r[3] -= 8;
        uv[3] -= 8;

        gif_SpriteSensitiveOffset(r, 0xFFFFFF9B, uv, col->b, 1);
        gif_SetZWrite(1);
        gif_EndPacket();
    }

    if (e == &texProperty[pr->curItem]) {
        KanbanCol col2 = {{0x80, 0x80, 0x80, 0x7F}};

        gif_StartPacketPri(11);
        gif_SetZTest(0);

        for (i = 0; i < r[2] * r[3] / 1200; i++) {
            pt[0] = r[0] + rand() % r[2];
            pt[1] = r[1] + rand() % r[3];
            col2.b[3] = rand() % 127 + 32;

            gif_PointOffset(pt, 0x800000, col2.b, 1);
        }
        gif_EndPacket();
    }
}
#else
static void display_texture(LtProp *pr, LtProperty *e, KanbanCol *col)
{
    int uv[4];
    int r[4];
    int pt[4];
    int i;
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    int alpha;
#endif

    uv[0] = (e->texU << 4) + 8;
    uv[1] = (e->texV << 4) + 8;
    uv[2] = e->texW << 4;
    uv[3] = e->texH << 4;

    r[2] = e->dispW << 4;
    r[3] = e->dispH << 3;
    if (r[2] == 0) {
        r[2] = uv[2];
    }
    if (r[3] == 0) {
        r[3] = uv[3] >> 1;
    }

    if (e->centerX) {
        r[0] = (0x2800 - r[2]) / 2 - 0x1400;
    } else {
        r[0] = (e->dispX - 320) << 4;
    }
    r[1] = (e->dispY - 112) << 4;

    if (e->masked == 0) {
        tex_TransTexture(e->texNo, 11);

        gif_StartPacketPri(11);

        gif_SetAlpha(1, 7, 0);

        gif_SetZWrite(0);

        r[1] += 8;

        r[3] -= 8;
        uv[3] -= 8;

        gif_SpriteSensitiveOffset(r, 0xFFFFFF9B, uv, col->b, 1);
        gif_SetZWrite(1);
        gif_EndPacket();
    }

    if (e == &texProperty[pr->curItem]) {
        KanbanCol col2 = {{0x80, 0x80, 0x80, 0x7F}};

        gif_StartPacketPri(11);
        gif_SetZTest(0);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        for (i = 0; i < r[2] * r[3] / 1200; i++) {
            pt[0] = r[0] + rand() % r[2];
            pt[1] = r[1] + rand() % r[3];
            col2.b[3] = rand() % 127 + 32;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        for (i = 0; i < r[2] * r[3] / 1200; i++) {
#else
        for (i = 0; i < r[2] * r[3] / 300; i++) {
#endif
            pt[0] = r[0] + rand() % r[2];
            pt[1] = r[1] + rand() % r[3];
            alpha = rand() % 127 + 32;
            col2.b[3] = alpha;
            if (col->b[3] < col2.b[3]) {
                col2.b[3] = col->b[3];
            }
#endif

            gif_PointOffset(pt, 0x800000, col2.b, 1);
        }
        gif_EndPacket();
    }
}
#endif

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

#ifdef VERSION_NTSC
static void display_layout(Kanban *k)
{
    LtProp *pr;
    int i;

    pr = k->layout;

    k->key = 0;
    if (kanbanCurrent != 0 && kanbanCurrent->layout == pr) {
        k->key = kanban_layout_key(pr);
    }

    if (fade_exec(k) < 0) {
        kanbanReqDel(k);
    } else {
        for (i = pr->first; i < pr->last; i++) {
            display_texture(pr, &texProperty[i], &k->col);
        }
    }
}
#else
static void display_layout(Kanban *k)
{
    LtProp *pr;
    int i;

    pr = k->layout;

    k->key = 0;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (kanbanCurrent != 0 && kanbanCurrent->layout == pr) {
#else
    if (kanbanCurrent != 0 && kanbanCurrent->layout == pr && (k->flags & 1) == 0) {
#endif
        k->key = kanban_layout_key(pr);
    }

    if (fade_exec(k) < 0) {
        kanbanReqDel(k);
    } else {
        for (i = pr->first; i < pr->last; i++) {
            display_texture(pr, &texProperty[i], &k->col);
        }
    }
}
#endif

inline void kanbanExec(void)
{
    Kanban *k;
    unsigned char col[4];
    Pkt16 pkt;

    if (kanbanList != 0) {
        LtProp *pr = kanbanList->layout;
        col[0] = (int)(pr->colR * 255.0f);
        col[1] = (int)(pr->colG * 255.0f);
        col[2] = (int)(pr->colB * 255.0f);
        col[3] = (int)(pr->colA * 127.0f);
        gif_StartPacketPri(11);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 7, 0);
        pkt = kanbanSprite;
        gif_SpriteSensitive(pkt.i, 0xFFFFFFFFu, 0, col, 1);
        gif_SetZWrite(1);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    k = kanbanList;
    if (k != 0) {
        do {
            display_layout(k);
            k = k->next;
        } while (k != 0);
    }
}
