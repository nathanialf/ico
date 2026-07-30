#include "common.h"

typedef struct { char _0[8]; int f_8; int f_C; char _10[8]; } BoxBridgeEntry;


extern int D_00274EE8[];
extern void func_00176AA0();
INCLUDE_ASM("asm/nonmatchings/src/way_sys", _FUNC_GetWay_begin);

void avoid_obstacle2(void)
{
    D_00274EE8[0] = 0;
    func_00176AA0();
}

extern int D_00274EC0[];
extern char D_002E81F0[];
extern char D_002F2318[];
extern char D_002F2384[];
extern unsigned int D_00631A00;
extern int D_00632510;
extern int D_00632514;
extern int D_00632518;
extern BoxBridgeEntry D_006ABE40[];
extern int D_006CEFF8[];
extern int D_006CF030[];
extern int func_0013DB60(void *a0);
extern int func_0013DBB0(void *a0);
extern void func_00176200(void *a0);

void create_box_bridge(int *a0) {
    BoxBridgeEntry *entry = &D_006ABE40[a0[0x3C / 4]];
    if (D_00274EC0[0x28 / 4] == 0) {
        return;
    }
    {
        int v = entry->f_C;
        if ((unsigned int) (v + D_00632510) < D_00631A00) {
            D_00632514 = 0;
        }
        if ((unsigned int) (v + 5) < D_00631A00) {
            func_0013DBB0(D_006CEFF8);
            if (D_006CEFF8[0x24 / 4] > 0) {
                func_0013DB60(D_006CEFF8);
            }
        }
        if (D_00274EC0[0x28 / 4] != 0) {
            func_0013DBB0(D_006CF030);
            if (D_006CF030[0x24 / 4] > 0) {
                func_0013DB60(D_006CF030);
            }
        }
        if (D_00632514 != 0) {
            int w = entry->f_8;
            char *p = (char *) D_002E81F0;
            p += 0x8000;
            *(int *) (p + 0x21AC) = w;
            *(int *) (p + 0x2140) = w;
            if (w >= 0) {
                if (D_00632518 != 0) {
                    func_00176200(D_002F2318);
                    func_00176200(D_002F2384);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetWay_next);

void func_00176DD0(void)
{
    D_00632514 = 0;
    D_00632518 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetNearNigePointN);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetWay_begin);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", BridgeBox);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", DeleteGuideWay);

