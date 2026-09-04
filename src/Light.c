#include "common.h"

#include "vu0.h"
typedef struct AmbientVolume {
    char _pad0[0x90];
    int f_90;                   /* 0x90 */
    struct AmbientVolume *next; /* 0x94 */
    struct AmbientVolume *prev; /* 0x98 */
} AmbientVolume;

INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkAmbient);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_AddLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getNearLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getAmbientLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_MakeLightMatrix);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_DispVolume);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_GetColorAnalog);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_DrawCursor);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_Tool);
extern char D_0063A088[8];
extern int D_0063C134;
extern int D_0063C138;

void light_InitLight(void) {
    D_0063C134 = 0;
    D_0063C138 = 0;
    *(int *)D_0063A088 = 0;
}
void light_ResetLight(void) {}
INCLUDE_ASM("asm/nonmatchings/src/Light", light_KillAllFixLight);
extern int D_0063C138;
extern void light_killLinkAmbient();

void light_KillAllAmbient(void)
{
    AmbientVolume *p = (AmbientVolume *)D_0063C138;
    while (p != 0) {
        int v = p->f_90;
        if (v < 3) {
            if (v >= 0) {
                AmbientVolume *node = p;
                p = p->prev;
                light_killLinkAmbient((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/Light", light_AddAmbientObject);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_resetFlatLight);
