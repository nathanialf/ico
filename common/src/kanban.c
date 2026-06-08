#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqAdd);

void init_textures_of_specified_property(void) {
}

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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADB00);

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
