#include "common.h"

#include "ico/types.h"
#include "vu0.h"
#include "sugiCommon.h"

extern void StopSEPackage(int a0);
extern void ExecuteSEPackage(int a0, int a1);
typedef struct TorchGeoWork {
    /* 0x00 */ int   flags;
    /* 0x04 */ int   unk04;
    /* 0x08 */ int   unk08;
    /* 0x0C */ int   unk0C;
    /* 0x10 */ float pos[4];
    /* 0x20 */ int   lightOn;
    /* 0x24 */ int   unk24;
    /* 0x28 */ int   life;
    /* 0x2C */ int   lifeMax;
    /* 0x30 */ int   chainFlag;
    /* 0x34 */ int   unk34;
    /* 0x38 */ int   unk38;
    /* 0x3C */ int   unk3C;
    /* 0x40 */ int   unk40;
    /* 0x44 */ int   unk44;
    /* 0x48 */ int   unk48;
    /* 0x4C */ int   unk4C;
} __attribute__((aligned(16))) TorchGeoWork;
extern int D_0063A438;
extern const char D_00621338[];
extern TorchGeoWork D_004ED120;
extern void GetRootPosition(void *a0, void *a1);
extern void *iosMallocDebug(int heap, int size, const char *file, int line);
extern void sceVu0UnitMatrix(void *m);
extern void LightTorchOn(char *gobj);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void CopyVector(void *a0, void *a1);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
/* prototypes: their order is the inline tail's emission order */
char *InitTorchGeo(char *a0, char *a1);
void TorchDL(void);
int IsTorchLightOn(char *a0);
char *CheckTorchChainReaction(char *a0, float dist);
void SetTorchLife(char *a0, int a1, int a2);
void SetTorchChainReactionFlag(char *a0, int a1);
void UpdateRealTimeGeometryValue(char *a0);
inline void SetTorchChainReactionFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) = a1;
}
void torchOffSE(int a0) {
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
}
INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOn);
INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOff);
INCLUDE_ASM("asm/nonmatchings/src/torch", torchDrainControl);
INCLUDE_ASM("asm/nonmatchings/src/torch", moveTorch);
INCLUDE_ASM("asm/nonmatchings/src/torch", setPauseFlag);
inline int IsTorchLightOn(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20);
}
inline void SetTorchLife(char *a0, int a1, int a2) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x28) = a1;
    *(int *)(p + 0x2C) = a1 - a2;
}
inline char *InitTorchGeo(char *a0, char *a1) {
    TorchGeoWork *p = (TorchGeoWork *)iosMallocDebug(D_0063A438, 0x50, D_00621338, 0xE8);
    *p = D_004ED120;
    sceVu0UnitMatrix((char *)*(void **)(a0 + 0x15C) + 0x20);
    *(void **)((char *)*(void **)(a0 + 0x15C) + 0x830) = p;
    if (*(int *)(a1 + 0x30) & 1) {
        LightTorchOn(a0);
    } else {
        *(int *)((char *)*(void **)(a0 + 0x15C) + 0x83C) = 0;
    }
    p->flags = *(int *)(a1 + 0x30) & ~1;
    GetRootPosition(p->pos, a0);
    return (char *)p;
}
inline char *CheckTorchChainReaction(char *a0, float dist) {
    float pos[4];
    float pos2[4];
    char *o;
    float dist2;

    GetRootPosition(pos, a0);

    o = (char *)isysGObjSearchFromObjKindID_begin(10);
    dist2 = dist * dist;
    while (o != 0) {
        TorchGeoWork *w = *(TorchGeoWork **)(*(char **)(o + 0x15C) + 0x830);
        if (o != a0 && IsTorchLightOn(o) && *(int *)(o + 0x16C) != 0 && w->flags != 2) {
            GetRootPosition(pos2, o);
            if (distance_squared(pos2, pos) < dist2) {
                return o;
            }
        }
        o = (char *)isysGObjSearchFromObjKindID_next(o);
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/torch", CheckTorchChainReactionReverse);
inline void UpdateRealTimeGeometryValue(char *a0) {
    int buf[4];
    char *sub;
    GetRootPosition(buf, a0);
    sub = *(char **)(a0 + 0x15C);
    sceVu0SubVector(sub + 0x130, buf, sub + 0x1F0);
    sub = *(char **)(a0 + 0x15C);
    CopyVector(sub + 0x1F0, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/torch", procChainReaction);
INCLUDE_ASM("asm/nonmatchings/src/torch", TorchGeo);
inline void TorchDL(void) {}
