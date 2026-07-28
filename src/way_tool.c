#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_create);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_select);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_delete);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_insert);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", quick_load_wpfile);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", ExtractWayData);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", wp_print_out);

extern char D_004D06A0[];
extern unsigned char D_0061B668[];
extern int D_00632CBC;
extern int D_00633878;
extern int D_0071257C[];
extern void traceLine(int, int, int, void *);
extern char *visible_waypoint_of_all(int *, float);

int draw_way_group(void) {
    int *p;
    int v;

extern char D_004D06A0[];


    if (D_00632CBC & 1) {
        unsigned int color = 0xFF000000;
        traceLine(0x12, 0x36, color, D_0061B668);
    }
    v = D_0071257C[0];
    if (v & 0x20) {
        p = (int *)visible_waypoint_of_all((int *)D_004D06A0, 60.0f);
        if (p == 0) {
            return 0;
        }
        D_00633878 = p[1];
        if (p[1] >= 0) {
            p[10] ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}

extern char D_0061B678[];
extern int D_00632590;
extern char D_006338A0[];
extern char D_006338A8[];
extern unsigned char D_007125F0[];
extern void debug_assertMessage();
extern int func_001AA4F0(void *a0, int a1);
extern int func_001AA550(int a0);
extern void func_00247C30(int a0, void *a1, int a2);
extern void func_00264DF8(void *a0, char *a1);

int way_toolDL(void) {
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    D_00632590 = 1;
    func_00264DF8(buf, D_006338A0);
    s0 = func_001AA4F0(buf, 0x202);
    if (s0 < 0) {
        debug_assertMessage((int)D_0061B678);
        D_00632590 = 0;
        return 0;
    }
    i = 0xF;
    p = &D_007125F0[i];
    do {
        *p = i;
        p--;
        i--;
    } while (i >= 0);
    func_00247C30(s0, D_007125F0, 0x10);
    func_001AA550(s0);
    debug_assertMessage((int)D_006338A8);
    D_00632590 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/way_tool", debug_WayTool);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", play_way);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_nige);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", quick_save_wpfile);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", cursor_control);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", func_00207A88);

INCLUDE_ASM("asm/nonmatchings/src/way_tool", func_00207C48);

