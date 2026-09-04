#include "common.h"

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
typedef struct { char b[16]; } Pkt16;

INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanReqAdd);
INCLUDE_ASM("asm/nonmatchings/src/kanban", init_textures_of_specified_property);
INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanInit);
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B8B10);
INCLUDE_ASM("asm/nonmatchings/src/kanban", fade_exec);
INCLUDE_ASM("asm/nonmatchings/src/kanban", display_layout);
extern int *D_0063C398;

void kanbanReqDel(int *self)
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
extern int D_0063C39C;

void kanbanReqDelFade(int a0)
{
    int v1 = D_0063C39C;
    *(int *)(a0 + 0xC) |= 1;
    if (a0 == v1) {
        D_0063C39C = 0;
    }
}
extern int D_0071CB10[];

void kanbanReqAllDel(void)
{
    int i;
    for (i = 0x1D; i >= 0; i--) {
        D_0071CB10[i * 8] = 0;
    }
    D_0063C398 = 0;
    D_0063C39C = 0;
}
void kanbanReqAllDelFade(void)
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
extern Pkt16 D_0061D698;
extern void display_layout(Node *a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_SpriteSensitive(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_StartPacketPri(int a0);

void kanbanExec(void) {
    Node *k;
    unsigned char col[4];
    Pkt16 pkt;

    if (D_0063C398 != 0) {
        int o = ((Node *)D_0063C398)->f0;
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
