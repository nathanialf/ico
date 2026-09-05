#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/puddle", InitPuddleGeo);
INCLUDE_ASM("asm/nonmatchings/src/puddle", baseSetup);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawAreaSetup);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawAreaRestore);
INCLUDE_ASM("asm/nonmatchings/src/puddle", leveldown);
INCLUDE_ASM("asm/nonmatchings/src/puddle", copy);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawRipple);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawRipples);
INCLUDE_ASM("asm/nonmatchings/src/puddle", PuddleDL);
extern int D_0028F4C0[];

inline void PuddleGeo(char *a0)
{
    char *p;
    int i;

    p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    for (i = 0; i < 6; i++) {
        if (*(float *)(p + 0x20) < 200.0f) {
            *(float *)(p + 0x20) += 60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 2.0f;
        }
        p += 0x20;
    }
}
extern void CopyVector(void *a0, void *a1);

typedef struct {
    float pos[4];
    float t;
    float pad[3];
} Ripple;

typedef struct {
    int pad0;
    int idx;
    int pad8[2];
    Ripple rip[6];
} PuddleWork;

inline void EntryRippleToPuddle(char *a0, void *vec)
{
    PuddleWork *w;

    w = *(PuddleWork **)(*(char **)(a0 + 0x15C) + 0x830);
    CopyVector(w->rip[w->idx].pos, vec);
    w->rip[w->idx].t = 0.0f;
    w->idx = w->idx + 1;
    if (w->idx >= 6) {
        w->idx = 0;
    }
}
inline int puddleRideFunc(char **a0, char *a1)
{
    float v[4];
    char *e;
    int n;

    e = *(char **)(a1 + 0x15C);
    if (*(int *)(e + 0x63C) != 0) {
        n = *(int *)(e + 0x220);
        if (n != -1) {
            CopyVector(v, *(char **)(e + 0xC) + n * 0x40 + 0x30);
            EntryRippleToPuddle(*a0, v);
        }
    }
    return 1;
}
