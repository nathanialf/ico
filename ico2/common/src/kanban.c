#include "typedef.h"
#include "debug.h"
#include "Texture.h"
#include "debug_exception.h"
#include "layout_texture.h"

typedef struct { /* field names derived */
    unsigned char b[4];
} KanbanCol; /* derived name */

typedef struct KanbanProp KanbanProp;

typedef struct Node {
    KanbanProp *f0;
    int f4;
    int f8;
    int fC;
    float f10;
    KanbanCol f14;
    struct Node *f18;
    struct Node *f1C;
} Node;

typedef union {
    int i[4];
    char b[16];
} Pkt16;

/* .sbss and .bss, owned by kanban.o and reached only from this file (MAIN.MAP
   names no symbol in either run).  The list head and the sign the layout key
   follows are the .sbss run in the ROM's order; the pool is the head of the
   .bss run, thirty Node entries of 0x20 bytes, which is the count both
   kanbanReqAdd and kanbanReqAllDel walk.  The run's last 0x30 bytes are not
   this pool and nothing in the ROM reads them: they stay in the blob. */
static int *kanbanList;

static int kanbanCurrent;

static int kanbanNodes[30 * 8];

/* kanban.o's whole .rodata run opens with these two named objects: the
   overflow message is printed far down the file and the sprite packet is
   read further down still, but the ROM has them first. */
/* kanban quest box over */
static const char kanbanOverMsg[] = "かんばんクエストボックスオーバー\n";

/* The sprite the kanban is drawn as, {x, y, width, height} centred on the
   origin, the same rectangle src/staffroll.c uses for the roll. */
static const Pkt16 kanbanSprite = {{-5120, -1792, 10240, 3584}};

struct KanbanProp {
    int first;
    int last;
    float f8;
    float fC;
    float f10;
    float f14;
    float f18;
    float f1C;
    unsigned char pad20[8];
    int f28;
    int f2C;
    unsigned char pad30[8];
};

extern StgPre stageData[];
extern KanbanProp texLayout[];

/* kanban.o's .sdata run (VMA 0x63B498..0x63B4BC, 0x24 B = MAIN.MAP), in the
   ROM's order: kanbanCommonRead (MAIN.MAP global), the sign's initial colour,
   the texture-name separator and assert text at their first uses, and the
   initialiser of display_texture's point colour. */
int kanbanCommonRead = 0;

/* the colour a new sign starts with */
static KanbanCol kanbanStartCol = {{0x80, 0x80, 0x80, 0}}; /* derived name */

extern char D_0030D014[];
/* census display_texture, a file static; MAIN.MAP carries no global of that
   name, so the twins in ico2/fumi/src/jimaku and ico2/common/src/layout_texture
   are statics too and `static` here keeps this one's ELF symbol local */
static void display_texture(KanbanProp *pr, LtProperty *e, KanbanCol *col);
extern char texFile[][52];
extern char *strtok(char *s, const char *sep);
extern char *strrchr(const char *s, int c);
/* kept local: agrees with mv_defs.h, which this TU does not include */
extern void __assert(const char *file, int line, const char *expr);
extern void display_layout(Node *a0);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_EndPacket(void);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_SetAlpha(long long a0, long long a1, long long a2);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_SetZTest(int a0);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_SetZWrite(int a0);
/* kept local: z is unsigned int here, long long in GifPacket.h */
extern void gif_SpriteSensitive(int *r, unsigned int z, int *uv, unsigned char *col, int prim);
/* kept local: z is unsigned int here, long long in GifPacket.h */
extern void gif_SpriteSensitiveOffset(int *r, unsigned int z, int *uv, unsigned char *col,
                                      int prim);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_PointOffset(int *v, long long z, unsigned char *col, int prim);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitive, gif_SpriteSensitiveOffset differ) */
extern void gif_StartPacketPri(int pri);

#include "kanban.h"
#include <string.h>
#include <stdlib.h>
#include "main.h"

static inline char *get_texture_base_name(char *src)
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

static inline int get_texture_no_of_property(int idx)
{
    int n;
    char *src;
    char *name;
    int no;

    n = texProperty[idx].texFileNo;
    src = texFile[n];
    name = get_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy("tex_id %d\n", n);
        debug_StdPrintfDummy("no texture loaded.(%s)\n", src);
        debug_assert(__FILE__, 0x110);
        __assert(__FILE__, 0x110, "0");
    }
    return no;
}

static inline void init_textures_of_property_range(int first, int last)
{
    int i;

    for (i = first; i < last; i++) {
        init_textures_of_specified_property(texLayout[i].first, texLayout[i].last);
    }
}

static inline int kanban_layout_key(KanbanProp *pr)
{
    int ret = 0;
    LtProperty *e = &texProperty[pr->f2C];

    if ((pad[0].flags & 0x1000) && e->upItem > 0) {
        pr->f2C = e->upItem;
    } else if ((pad[0].flags & 0x4000) && e->downItem > 0) {
        pr->f2C = e->downItem;
    } else if ((pad[0].flags & 0x8000) && e->leftItem > 0) {
        pr->f2C = e->leftItem;
    } else if ((pad[0].flags & 0x2000) && e->rightItem > 0) {
        pr->f2C = e->rightItem;
    } else {
        unsigned long button = pad[0].flags; /* derived name */

        if (button & 0x40) {
            ret = 1;
        } else {
            ret = (button & 0x10) ? 2 : 0;
        }
    }
    return ret;
}

void kanbanReqAllDel(void);
void kanbanReqAllDelFade(void);
void kanbanExec(void);
void kanbanReqAllDel(void);
void kanbanReqAllDelFade(void);
void kanbanExec(void);

inline void kanbanReqAllDel(void)
{
    int i;
    for (i = 0x1D; i >= 0; i--) {
        kanbanNodes[i * 8] = 0;
    }
    kanbanList = 0;
    kanbanCurrent = 0;
}

Node *kanbanReqAdd(int no, int pri)
{
    Node *p;
    KanbanProp *pr;
    Node *cur;
    int i;

    p = (Node *)kanbanNodes;
    pr = &texLayout[no];
    for (i = 0; i < 30; i++, p++) {
        if (p->f0 == 0)
            goto found;
    }
    debug_StdPrintfDummy(kanbanOverMsg);
    return 0;

found:
    p->f0 = pr;
    p->f8 = 0;
    pr->f2C = pr->f28;
    p->fC &= ~1;
    p->f10 = 0;
    p->f14 = kanbanStartCol;
    p->f4 = pri;
    cur = (Node *)kanbanList;
    if (cur != 0) {
        if (pri < cur->f4) {
            cur->f1C = p;
            p->f18 = cur;
            p->f1C = 0;
            kanbanList = (int *)p;
        } else {
            for (;;) {
                if (cur->f18 == 0) {
                    goto append;
                }
                if (pri < cur->f4) {
                    break;
                }
                cur = cur->f18;
            }
            p->f1C = cur->f1C;
            cur->f1C = p;
            p->f18 = cur;
            goto done;
        append:
            cur->f18 = p;
            p->f1C = cur;
            p->f18 = 0;
        }
    } else {
        kanbanList = (int *)p;
        p->f1C = 0;
        p->f18 = 0;
    }
done:
    if (pr->f28 != -1) {
        kanbanCurrent = (int)p;
    }
    return p;
}

inline void kanbanReqDel(int *self)
{
    int *next = (int *)self[0x1C / 4];
    int *prev = (int *)self[0x18 / 4];
    if (next == 0) {
        kanbanList = prev;
        if (prev != 0) {
            prev[0x1C / 4] = 0;
        }
    } else {
        next[0x18 / 4] = (int)prev;
        if (prev != 0) {
            ((int *)self[0x18 / 4])[0x1C / 4] = self[0x1C / 4];
        }
    }
    self[0] = 0;
}

inline void kanbanReqDelFade(int a0)
{
    int v1 = kanbanCurrent;
    *(int *)(a0 + 0xC) |= 1;
    if (a0 == v1) {
        kanbanCurrent = 0;
    }
}

inline void kanbanReqAllDelFade(void)
{
    int *p = kanbanNodes;
    int i = 0x1D;
    do {
        if (p[0] != 0) {
            p[3] |= 1;
        }
        i--;
        p += 8;
    } while (i >= 0);
}

void init_textures_of_specified_property(int first, int last)
{
    int i;
    int no;

    for (i = first; i < last; i++) {
        debug_StdPrintfDummy("propertyId %d\n", i);
        no = get_texture_no_of_property(i);
        *(int *)(D_0030D014 + i * 0x70) = no;
        *(void **)(D_0030D014 + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030D014 + i * 0x70 - 4), 1, 1);
    }
}

void kanbanInit(int no)
{
    if (no != 0) {
        init_textures_of_property_range(stageData[no].layoutFirst, stageData[no].layoutLast);
    } else {
        init_textures_of_property_range(0, 1);
        kanbanReqAllDel();
        kanbanCommonRead = 1;
    }
}

static void display_texture(KanbanProp *pr, LtProperty *e, KanbanCol *col)
{
    int uv[4];
    int r[4];
    int pt[4];
    int i;
    int alpha;

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

    if (e == &texProperty[pr->f2C]) {
        /* its initialiser is the anonymous 4-byte template at the end of
           the TU's .sdata run, which the ROM reaches with %hi/%lo */
        KanbanCol col2 = {{0x80, 0x80, 0x80, 0x7F}};

        gif_StartPacketPri(11);
        gif_SetZTest(0);

        for (i = 0; i < r[2] * r[3] / 300; i++) {
            pt[0] = r[0] + rand() % r[2];
            pt[1] = r[1] + rand() % r[3];
            alpha = rand() % 127 + 32;
            col2.b[3] = alpha;
            if (col->b[3] < col2.b[3]) {
                col2.b[3] = col->b[3];
            }

            gif_PointOffset(pt, 0x800000, col2.b, 1);
        }
        gif_EndPacket();
    }
}

int fade_exec(Node *p)
{
    int ret = 0;
    float f;

    if ((p->fC & 1) == 0) {
        f = 127.0f / (p->f0->f8 * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (f == 0.0f) {
            f = 127.0f;
        }

        p->f10 = p->f10 + f;
        if (p->f10 > 127.0f) {
            p->f10 = 127.0f;
            ret = 1;
        }
    } else {
        f = 127.0f / (p->f0->fC * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (f == 0.0f) {
            f = 127.0f;
        }
        p->f10 = p->f10 - f;
        if (p->f10 < 0.0f) {
            p->f10 = 0.0f;
            ret = -1;
        }
    }
    p->f14.b[3] = (char)p->f10;
    return ret;
}

void display_layout(Node *k)
{
    KanbanProp *pr;
    int i;

    pr = k->f0;

    k->f8 = 0;
    if (kanbanCurrent != 0 && ((Node *)kanbanCurrent)->f0 == pr && (k->fC & 1) == 0) {
        k->f8 = kanban_layout_key(pr);
    }

    if (fade_exec(k) < 0) {
        kanbanReqDel((int *)k);
    } else {
        for (i = pr->first; i < pr->last; i++) {
            display_texture(pr, &texProperty[i], &k->f14);
        }
    }
}

inline void kanbanExec(void)
{
    Node *k;
    unsigned char col[4];
    Pkt16 pkt;

    if (kanbanList != 0) {
        int o = (int)((Node *)kanbanList)->f0;
        col[0] = (int)(*(float *)(o + 0x10) * 255.0f);
        col[1] = (int)(*(float *)(o + 0x14) * 255.0f);
        col[2] = (int)(*(float *)(o + 0x18) * 255.0f);
        col[3] = (int)(*(float *)(o + 0x1C) * 127.0f);
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 7, 0);
        pkt = kanbanSprite;
        gif_SpriteSensitive(&pkt, 0xFFFFFFFFu, 0, col, 1);
        gif_SetZWrite(1);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    k = (Node *)kanbanList;
    if (k != 0) {
        do {
            display_layout(k);
            k = k->f18;
        } while (k != 0);
    }
}
