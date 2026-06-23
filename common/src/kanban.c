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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanInit);


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

extern void gif_SpriteOffset(int a0);
extern void gsb_Reduction(int a0);
extern void gsb_KeepFrameBuffer(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern void gif_StartPacket(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void func_0010F9D0(void);
extern void kanbanReqDelFade(Node *a0);
typedef struct { char b[16]; } Pkt16;
extern Pkt16 D_0060F680;

void func_001ADB38(void) {
    Node *k;
    unsigned char col[4];
    Pkt16 pkt;

    if (D_0062C15C != 0) {
        int o = ((Node *)D_0062C15C)->f0;
        col[0] = (int)(*(float *)(o + 0x10) * 255.0f);
        col[1] = (int)(*(float *)(o + 0x14) * 255.0f);
        col[2] = (int)(*(float *)(o + 0x18) * 255.0f);
        col[3] = (int)(*(float *)(o + 0x1C) * 127.0f);
        gif_SpriteOffset(0xB);
        gsb_Reduction(0);
        gsb_KeepFrameBuffer(0);
        gsb_SetFrame(1, 7, 0);
        pkt = D_0060F680;
        gif_StartPacket(&pkt, 0xFFFFFFFFu, 0, col, 1);
        gsb_KeepFrameBuffer(1);
        gsb_Reduction(1);
        func_0010F9D0();
    }
    k = (Node *)D_0062C15C;
    if (k != 0) {
        do {
            kanbanReqDelFade(k);
            k = k->f18;
        } while (k != 0);
    }
}


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
