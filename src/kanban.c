#include "common.h"

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
INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanExec);
