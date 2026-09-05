#include "common.h"

extern void CopyVector(void *dst, void *src);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void HotInitCageGeo(void *gobj);
/* prototypes: their order is the inline tail's emission order */
int GetCageChainPoint(char *a0, char *a1, char *a2);
void SetCageVelocityFriction(char *a0, float a1);
void StabilizeAllLayoutedCage(void);
void SetCageChainHangableFlag(char *a0, int a1);
INCLUDE_ASM("asm/nonmatchings/src/cage", CageRideFunc);
INCLUDE_ASM("asm/nonmatchings/src/cage", SetCageFixGeometry);
inline int GetCageChainPoint(char *a0, char *a1, char *a2)
{
    char *w = *(char **)(*(char **)(a2 + 0x15C) + 0x830);
    CopyVector(a0, *(char **)(*(char **)(*(char **)(w + 0x20) + 8)));
    CopyVector(a1, *(char **)(*(char **)(*(char **)(w + 0x20) + 8)) + 0x10);
    *(float *)(a0 + 4) = *(float *)(a0 + 4) + 50.0f;
    *(float *)(a1 + 4) = *(float *)(a1 + 4) - 150.0f;
    return *(int *)(w + 0x40);
}
INCLUDE_ASM("asm/nonmatchings/src/cage", InitCageGeo);
inline void SetCageChainHangableFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x40) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/cage", HotInitCageGeo);
inline void StabilizeAllLayoutedCage(void)
{
    void *gobj;

    gobj = isysGObjSearchFromObjKindID_begin(0x2C);
    while (gobj != 0) {
        HotInitCageGeo(gobj);
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}
inline void SetCageVelocityFriction(char *a0, float a1) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x3C) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/cage", CageGeo);
INCLUDE_ASM("asm/nonmatchings/src/cage", CageDL);
