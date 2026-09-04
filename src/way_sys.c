#include "common.h"

typedef struct { int pad[8]; int f20; int pad2[7]; } WVTElem;
typedef struct { char pad[0x64]; int w64; } WVTObj;
typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;

INCLUDE_ASM("asm/nonmatchings/src/way_sys", avoid_obstacle2);
INCLUDE_ASM("asm/nonmatchings/src/way_sys", create_box_bridge);
INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetWay_next);
INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetNearNigePointN);
extern int func_0017D5D0(void *a0, int a1, int a2, int a3);

int GetWay_begin(void *a0, int a1, int a2) {
    return func_0017D5D0(a0, a1, a2, 0);
}
void BridgeBox(void) {}
extern Nd D_004F31E0[];
extern char D_00554220[];
extern int DeleteWayGroup(int a0);
extern extern void debug_StdPrintfDummy();

extern WVTElem D_004C7CF0_ve[] __asm__("D_004F31E0");

void DeleteGuideWay(WVTObj *o) {
    if (o->w64 >= 0) {
        debug_StdPrintfDummy(D_00554220, o->w64);
        {
            WVTElem *e = &D_004C7CF0_ve[o->w64];
            DeleteWayGroup(e->f20);
        }
        o->w64 = -1;
    }
}
