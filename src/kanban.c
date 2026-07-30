#include "common.h"




extern int D_00706110[];
extern int D_00633E70;
extern int *D_00633E6C;
INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanReqAdd);

void init_textures_of_specified_property(void) {}

INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanInit);

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001AFCC8);

INCLUDE_ASM("asm/nonmatchings/src/kanban", fade_exec);

INCLUDE_ASM("asm/nonmatchings/src/kanban", display_layout);

INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanReqDel);

INCLUDE_ASM("asm/nonmatchings/src/kanban", kanbanReqDelFade);

void kanbanReqAllDel(int *self)
{
    int *next = (int *)self[0x1C / 4];
    int *prev = (int *)self[0x18 / 4];
    if (next == 0) {
        D_00633E6C = prev;
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

void kanbanReqAllDelFade(int a0)
{
    int v1 = D_00633E70;
    *(int *)(a0 + 0xC) |= 1;
    if (a0 == v1) {
        D_00633E70 = 0;
    }
}

void kanbanExec(void)
{
    int i;
    for (i = 0x1D; i >= 0; i--) {
        D_00706110[i * 8] = 0;
    }
    D_00633E6C = 0;
    D_00633E70 = 0;
}

void func_001B0570(void)
{
    int *p = D_00706110;
    int i = 0x1D;
    do {
        if (p[0] != 0) {
            p[3] |= 1;
        }
        i--;
        p += 8;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B05A8);

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B06D8);

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B08E0);

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B0A38);

extern int D_00633024;

void func_001B0A58(void)
{
    D_00633024 = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B0A68);

