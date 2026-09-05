#include "common.h"

#include "vu0.h"

typedef struct Light {
    char _pad0[0x10];
    float f_10[4];              /* 0x10 */
    float f_20[4];              /* 0x20 */
    float f_30;                 /* 0x30 */
    int f_34;                   /* 0x34 */
    float f_38;                 /* 0x38 */
    float f_3C;                 /* 0x3C */
    char _pad40[4];
    short f_44;                 /* 0x44 */
    char _pad46[2];
    struct Light *next;         /* 0x48 */
    struct Light *prev;         /* 0x4C */
} Light;
typedef struct AmbientVolume {
    char _pad0[0x80];
    float f_80;                 /* 0x80 */
    char _pad84[0xC];
    int f_90;                   /* 0x90 */
    struct AmbientVolume *next; /* 0x94 */
    struct AmbientVolume *prev; /* 0x98 */
} AmbientVolume;

INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkAmbient);
ASM_LIT4_SLOT(D_00638BD8, 0.3333f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_AddLight);
ASM_LIT4_SLOT(D_00638BDC, 0.3333f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getNearLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_getAmbientLight);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_MakeLightMatrix);
ASM_LIT4_SLOT(D_00638BE0, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_DispVolume);
ASM_LIT4_SLOT(D_00638BE4, 3.1415927f);
ASM_LIT4_SLOT(D_00638BE8, 2.0943952f);
ASM_LIT4_SLOT(D_00638BEC, 4.1887903f);
ASM_LIT4_SLOT(D_00638BF0, 3.1415927f);
ASM_LIT4_SLOT(D_00638BF4, 3.1415927f);
ASM_LIT4_SLOT(D_00638BF8, -3.1415927f);
ASM_LIT4_SLOT(D_00638BFC, 3.1415927f);
ASM_LIT4_SLOT(D_00638C00, -3.1415927f);
ASM_LIT4_SLOT(D_00638C04, 3.1415927f);
ASM_LIT4_SLOT(D_00638C08, -3.1415927f);
ASM_LIT4_SLOT(D_00638C0C, 3.1415927f);
ASM_LIT4_SLOT(D_00638C10, 2.0943952f);
ASM_LIT4_SLOT(D_00638C14, 1.2f);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_GetColorAnalog);
INCLUDE_ASM("asm/nonmatchings/src/Light", light_DrawCursor);
ASM_LIT4_SLOT(D_00638C18, 0.01f);
ASM_LIT4_SLOT(D_00638C1C, 0.01f);
ASM_LIT4_SLOT(D_00638C20, 1.01f);
ASM_LIT4_SLOT(D_00638C24, 0.99f);
ASM_LIT4_SLOT(D_00638C28, 0.01f);
ASM_LIT4_SLOT(D_00638C2C, 0.01f);
ASM_LIT4_SLOT(D_00638C30, 1.01f);
ASM_LIT4_SLOT(D_00638C34, 0.99f);
ASM_LIT4_SLOT(D_00638C38, 0.3333f);
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
extern int D_0063C13C;
extern void light_killLinkLight(char *node);

void light_KillAllFixLight(void)
{
    Light *p = (Light *)D_0063C134;
    while (p != 0) {
        short v = p->f_44;
        if (v < 4) {
            if (v >= 2) {
                Light *node = p;
                p = p->prev;
                light_killLinkLight((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
    D_0063C13C = 0;
}
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
extern char D_0054F0C8[];
extern int D_0063A44C;
extern void *iosMallocDebug(int part, int size, char *file, int line);

static inline void light_setLinkAmbient(AmbientVolume *p)
{
    if (D_0063C138 != 0)
        ((AmbientVolume *)D_0063C138)->next = p;
    p->next = 0;
    p->prev = (AmbientVolume *)D_0063C138;
    D_0063C138 = (int)p;
}

AmbientVolume *light_AddAmbientObject(int obj)
{
    AmbientVolume *p;

    p = (AmbientVolume *)iosMallocDebug(D_0063A44C, 0xA0, D_0054F0C8, 723);
    p->f_90 = obj;
    p->f_80 = 1.0f;
    light_setLinkAmbient(p);
    return p;
}
typedef struct StageSetting {
    float flatLightDir[3][4];   /* 0x00 */
    float flatLightCol[3][4];   /* 0x30 */
} StageSetting;

extern StageSetting D_0028F720;
extern Light *D_002908B8[];
extern void _CopyVector(void *dst, void *src);
extern void _NormalizeVector(void *dst, void *src);

void light_resetFlatLight(void)
{
    int i;
    Light *l;

    for (i = 0; i < 3; i++) {
        l = D_002908B8[i];
        if (l != 0) {
            _CopyVector(l->f_20, D_0028F720.flatLightCol[i]);
            _NormalizeVector(l->f_10, D_0028F720.flatLightDir[i]);
            l->f_30 = 1.0f;
            l->f_34 = 0;
            l->f_38 = 1.0f;
            l->f_3C = (l->f_20[0] + l->f_20[1] + l->f_20[2]) * 0.3333f;
        }
    }
}
