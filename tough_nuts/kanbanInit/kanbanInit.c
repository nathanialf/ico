#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqAdd);

void init_textures_of_specified_property(void) {
}

extern char D_00536530[];
extern char D_0060F658[];
extern int *D_0062C15C;
extern void *D_0062C160;
extern int D_006FF910[];
struct U4 { char b[4]; };
typedef struct Node {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    struct Node *f18;
    struct Node *f1C;
} Node;
extern struct U4 D_0062B2C0;
extern Node kanban_reqs[] __asm__("D_006FF910");
extern void debug_assertMessage();

void *kanbanInit(int a0, int a1) {
    Node *p, *q;
    int t;
    int i;
    Node *node;

    node = kanban_reqs;
    a0 *= 0x38;
    a0 += (int)D_00536530;
    i = 0;
    do {
        if (node->f0 == 0) {
            goto found;
        }
        node++;
    } while (++i < 0x1E);
    debug_assertMessage(D_0060F658);
    return 0;
found:
    node->f8 = 0;
    node->fC &= ~1;
    node->f0 = a0;
    node->f10 = 0;
    t = *(int *)(a0 + 0x28);
    p = (Node *)D_0062C15C;
    node->f14 = *(int *)&D_0062B2C0;
    *(int *)(a0 + 0x2C) = t;
    node->f4 = a1;
    if (p == 0) {
        D_0062C15C = (int *)node;
        node->f1C = 0;
        goto end;
    }
    if (a1 < p->f4) {
        p->f1C = node;
        node->f18 = p;
        node->f1C = 0;
        D_0062C15C = (int *)node;
        goto post;
    }
    q = p->f18;
    if (q == 0) {
        p->f18 = node;
        goto append;
    }
    p = q;
    for (;;) {
        q = p->f18;
        if (q == 0) {
            p->f18 = node;
            goto append;
        }
        if (a1 < p->f4) {
            node->f1C = p->f1C;
            p->f1C = node;
            node->f18 = p;
            goto post;
        }
        p = q;
    }
append:
    node->f1C = p;
end:
    node->f18 = 0;
post:
    if (t != -1) {
        D_0062C160 = node;
    }
    return node;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001AD258);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", fade_exec);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", display_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqDel);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqDelFade);

extern int *D_0062C15C;

void kanbanReqAllDel(int *self)
{
    int *next = (int *)self[0x1C / 4];
    int *prev = (int *)self[0x18 / 4];
    if (next == 0) {
        D_0062C15C = prev;
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

extern void *D_0062C160;

void kanbanReqAllDelFade(void *a0) {
    *(int *)((char *)a0 + 0xC) |= 1;
    if (a0 == D_0062C160) {
        D_0062C160 = 0;
    }
}

extern int D_006FF910[];

void kanbanExec(void)
{
    int i;
    for (i = 0x1D; i >= 0; i--) {
        D_006FF910[i * 8] = 0;
    }
    D_0062C15C = 0;
    D_0062C160 = 0;
}

void func_001ADB00(void) {
    int *p = D_006FF910;
    int i;
    for (i = 0x1D; i >= 0; i--) {
        if (p[0] != 0) {
            p[3] |= 1;
        }
        p += 8;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADB38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADC68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADE70);

extern int D_0062B2DC, D_0062B2E4, D_0062B2E8, D_0062BA78;
extern int D_0027126C[];

void func_001ADFC8(void) {
    D_0062B2DC = 0;
    D_0027126C[0] = 0;
    D_0062B2E8 = 0;
    D_0062BA78 = 0;
    D_0062B2E4 = 0;
}

extern int D_0062B2E4;

void func_001ADFE8(void) {
    D_0062B2E4 = 1;
}

extern void soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, int a2, int a3);

void func_001ADFF8(void) {
    soundSeDefPlayWithVolumeRate(0x190, 0xFFFFFFFE, 0, 0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0060F6C0;  /* stride 0x4 */

/* end struct shapes */
