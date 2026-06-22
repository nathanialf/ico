#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", _FUNC_GetWay_begin);

extern void func_00174650(int a0);
extern int D_00271268[];

void avoid_obstacle2(int a0) {
    D_00271268[0] = 0;
    func_00174650(a0);
}

extern int func_0013D648(void *a0);
extern int func_0013D698(void *a0);
extern void func_00173DB0(void *a0);
extern int D_00271240[];
extern char D_002E34F0[];
extern char D_002ED618[];
extern char D_002ED684[];
extern unsigned int D_00629D00;
extern int D_0062A7F0;
extern int D_0062A7F4;
extern int D_0062A7F8;
extern int D_006C8AB8[];
extern int D_006C8AF0[];

typedef struct { char _0[8]; int f_8; int f_C; char _10[8]; } BoxBridgeEntry;  /* stride 0x18 */
extern BoxBridgeEntry D_006A5900[];

void create_box_bridge(int *a0) {
    BoxBridgeEntry *entry = &D_006A5900[a0[0x3C / 4]];
    if (D_00271240[0x28 / 4] == 0) {
        return;
    }
    {
        int v = entry->f_C;
        if ((unsigned int) (v + D_0062A7F0) < D_00629D00) {
            D_0062A7F4 = 0;
        }
        if ((unsigned int) (v + 5) < D_00629D00) {
            func_0013D698(D_006C8AB8);
            if (D_006C8AB8[0x24 / 4] > 0) {
                func_0013D648(D_006C8AB8);
            }
        }
        if (D_00271240[0x28 / 4] != 0) {
            func_0013D698(D_006C8AF0);
            if (D_006C8AF0[0x24 / 4] > 0) {
                func_0013D648(D_006C8AF0);
            }
        }
        if (D_0062A7F4 != 0) {
            int w = entry->f_8;
            char *p = (char *) D_002E34F0;
            p += 0x8000;
            *(int *) (p + 0x21AC) = w;
            *(int *) (p + 0x2140) = w;
            if (w >= 0) {
                if (D_0062A7F8 != 0) {
                    func_00173DB0(D_002ED618);
                    func_00173DB0(D_002ED684);
                }
            }
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetWay_next);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetNearNigePointN);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetWay_begin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", BridgeBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", DeleteGuideWay);
