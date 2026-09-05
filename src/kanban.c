#include "common.h"

typedef struct { unsigned char b[4]; } Col4;
typedef struct KanbanProp KanbanProp;
typedef struct Node {
    KanbanProp *f0;
    int f4;
    int f8;
    int fC;
    float f10;
    Col4 f14;
    struct Node *f18;
    struct Node *f1C;
} Node;
typedef struct { char b[16]; } Pkt16;
extern int *D_0063C398;
extern int D_0063C39C;
extern int D_0071CB10[];
extern Pkt16 D_0061D698;
typedef struct {
    unsigned char pad0[0x130];
    int texFirst;
    int texLast;
    unsigned char pad1[0x194 - 0x138];
} KanbanStage;
struct KanbanProp {
    int first;
    int last;
    float f8;
    float fC;
    float f10;
    float f14;
    float f18;
    float f1C;
    unsigned char pad20[0x08];
    int f28;
    int f2C;
    unsigned char pad30[0x08];
};
extern KanbanStage D_005F5D50[];
extern KanbanProp D_00533FE8[];
extern int kanbanCommonRead;
extern Col4 D_0063B4A0;
extern char D_0061D670[];
extern int D_0028F4C0[];
extern void debug_StdPrintfDummy();
typedef struct {
    unsigned char pad00[0x18];
    void *f18;
    int f1C;
    unsigned char pad20[0x10];
    int f30;
    int f34;
    int f38;
    int f3C;
    unsigned char pad40[0x18];
    int f58;
    unsigned char pad5C[0x14];
} LayoutTex;
extern LayoutTex D_0030CFF8[];
extern char D_0030D014[];
extern int D_0028F8F0[];
extern void func_001B8B10(KanbanProp *pr, LayoutTex *e, Col4 *col);
extern char D_00535168[][0x34];
extern char D_0063B4A8[];
extern char D_0063B4B0[];
extern char D_0061D6A8[];
extern char D_0061D6B8[];
extern char D_0061D6D0[];
extern char D_0061D6E0[];
extern char *strcpy(char *dst, const char *src);
extern char *strtok(char *s, const char *sep);
extern char *strrchr(const char *s, int c);
extern int tex_GetTextureNo(char *name);
extern void *tex_GetTextureData(int no);
extern void tex_SetSamplingType(void *td, int a1, int a2);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void init_textures_of_specified_property(int first, int last);
extern void display_layout(Node *a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_SpriteSensitive(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_StartPacketPri(int a0);
/* prototypes: their order is the inline tail's emission order */
void kanbanReqDel(int *self);
void kanbanReqDelFade(int a0);
void kanbanReqAllDel(void);
void kanbanReqAllDelFade(void);
void kanbanExec(void);
static inline char *get_texture_base_name(char *src)
{
    char buf[256];
    char *p;
    char *t;

    p = buf;

    strcpy(buf, src);

    t = strtok(buf, D_0063B4A8);
    if (t != 0) {
        do {
            p = t;
            t = strtok(0, D_0063B4A8);
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

    n = D_0030CFF8[idx].f58;
    src = D_00535168[n];
    name = get_texture_base_name(src);

    no = tex_GetTextureNo(name);

    if (no < 0) {
        debug_StdPrintfDummy(D_0061D6A8, n);
        debug_StdPrintfDummy(D_0061D6B8, src);
        debug_assert(D_0061D6D0, 0x110);
        __assert(D_0061D6D0, 0x110, D_0063B4B0);
    }
    return no;
}
static inline void init_textures_of_property_range(int first, int last)
{
    int i;

    for (i = first; i < last; i++) {
        init_textures_of_specified_property(D_00533FE8[i].first, D_00533FE8[i].last);
    }
}
static inline int kanban_layout_key(KanbanProp *pr)
{
    int ret = 0;
    LayoutTex *e = &D_0030CFF8[pr->f2C];

    if ((D_0028F8F0[1] & 0x1000) && e->f3C > 0) {
        pr->f2C = e->f3C;
    } else if ((D_0028F8F0[1] & 0x4000) && e->f38 > 0) {
        pr->f2C = e->f38;
    } else if ((D_0028F8F0[1] & 0x8000) && e->f34 > 0) {
        pr->f2C = e->f34;
    } else if ((D_0028F8F0[1] & 0x2000) && e->f30 > 0) {
        pr->f2C = e->f30;
    } else {
        unsigned long pad = D_0028F8F0[1];

        if (pad & 0x40) {
            ret = 1;
        } else {
            ret = (pad & 0x10) ? 2 : 0;
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
        D_0071CB10[i * 8] = 0;
    }
    D_0063C398 = 0;
    D_0063C39C = 0;
}
Node *kanbanReqAdd(int no, int pri)
{
    Node *p;
    KanbanProp *pr;
    Node *cur;
    int i;

    p = (Node *)D_0071CB10;
    pr = &D_00533FE8[no];
    for (i = 0; i < 30; i++, p++) {
        if (p->f0 == 0) goto found;
    }
    debug_StdPrintfDummy(D_0061D670);
    return 0;

found:
    p->f0 = pr;
    p->f8 = 0;
    pr->f2C = pr->f28;
    p->fC &= ~1;
    p->f10 = 0;
    p->f14 = D_0063B4A0;
    p->f4 = pri;
    cur = (Node *)D_0063C398;
    if (cur != 0) {
        if (pri < cur->f4) {
            cur->f1C = p;
            p->f18 = cur;
            p->f1C = 0;
            D_0063C398 = (int *)p;
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
        D_0063C398 = (int *)p;
        p->f1C = 0;
        p->f18 = 0;
    }
done:
    if (pr->f28 != -1) {
        D_0063C39C = (int)p;
    }
    return p;
}
inline void kanbanReqDel(int *self)
{
    int *next = (int *)self[0x1C / 4];
    int *prev = (int *)self[0x18 / 4];
    if (next == 0) {
        D_0063C398 = prev;
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
    int v1 = D_0063C39C;
    *(int *)(a0 + 0xC) |= 1;
    if (a0 == v1) {
        D_0063C39C = 0;
    }
}
inline void kanbanReqAllDelFade(void)
{
    int *p = D_0071CB10;
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
        debug_StdPrintfDummy(D_0061D6E0, i);
        no = get_texture_no_of_property(i);
        *(int *)(D_0030D014 + i * 0x70) = no;
        *(void **)(D_0030D014 + i * 0x70 - 4) = tex_GetTextureData(no);
        tex_SetSamplingType(*(void **)(D_0030D014 + i * 0x70 - 4), 1, 1);
    }
}
void kanbanInit(int no)
{
    if (no != 0) {
        init_textures_of_property_range(D_005F5D50[no].texFirst, D_005F5D50[no].texLast);
    } else {
        init_textures_of_property_range(0, 1);
        kanbanReqAllDel();
        kanbanCommonRead = 1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B8B10);
int fade_exec(Node *p)
{
    int ret = 0;
    float f;

    if ((p->fC & 1) == 0) {
        f = 127.0f / (p->f0->f8 * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        if (f == 0.0f) {
            f = 127.0f;
        }

        p->f10 = p->f10 + f;
        if (p->f10 > 127.0f) {
            p->f10 = 127.0f;
            ret = 1;
        }
    } else {
        f = 127.0f / (p->f0->fC * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
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
    if (D_0063C39C != 0 && ((Node *)D_0063C39C)->f0 == pr && (k->fC & 1) == 0) {
        k->f8 = kanban_layout_key(pr);
    }

    if (fade_exec(k) < 0) {
        kanbanReqDel((int *)k);
    } else {
        for (i = pr->first; i < pr->last; i++) {
            func_001B8B10(pr, &D_0030CFF8[i], &k->f14);
        }
    }
}
inline void kanbanExec(void) {
    Node *k;
    unsigned char col[4];
    Pkt16 pkt;

    if (D_0063C398 != 0) {
        int o = (int)((Node *)D_0063C398)->f0;
        col[0] = (int)(*(float *)(o + 0x10) * 255.0f);
        col[1] = (int)(*(float *)(o + 0x14) * 255.0f);
        col[2] = (int)(*(float *)(o + 0x18) * 255.0f);
        col[3] = (int)(*(float *)(o + 0x1C) * 127.0f);
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 7, 0);
        pkt = D_0061D698;
        gif_SpriteSensitive(&pkt, 0xFFFFFFFFu, 0, col, 1);
        gif_SetZWrite(1);
        gif_SetZTest(1);
        gif_EndPacket();
    }
    k = (Node *)D_0063C398;
    if (k != 0) {
        do {
            display_layout(k);
            k = k->f18;
        } while (k != 0);
    }
}
