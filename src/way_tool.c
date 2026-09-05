#include "common.h"

typedef struct { int w[13]; } WayRec;

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_create);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_select);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", point_delete);
extern int CreateWayPoint(void *a0);
extern WayRec D_004F1EC0[];
extern char D_004F76A0[];
extern char D_00622340[];
extern char D_00622350[];
extern int D_0063B13C;
extern int D_0063BD78;
extern char D_0063BD88[];
extern int D_0063BD98;
extern int D_00729B7C[];
extern int InsertWayPointAfter(int a0, int a1, int a2);
extern void debug_Printf();
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void *nearest_waypoint_by_lineseg(void *a0);

int point_insert(void) {
    WayRec *entry = &D_004F1EC0[D_0063BD78];
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, D_00622340);
        if (D_0063B13C & 1) {
            debug_Printf(0x1A, 0x42, 0xFF808000, D_0063BD88, entry->w[4]);
        }
    }
    D_0063BD98 = 1;
    f = D_00729B7C[0];
    if (!(f & 0x20)) {
        if (f & 0x40) {
            D_0063BD98 = 0;
            return -1;
        }
        return 0;
    }
    {
        void *res = nearest_waypoint_by_lineseg(D_004F76A0);
        if (*(int *) ((char *) res + 0xC) == 0) {
            return 0;
        }
        {
            int n = CreateWayPoint(D_004F76A0);
            InsertWayPointAfter(D_0063BD78, *(int *) ((char *) res + 4), n);
            entry->w[4] = entry->w[4] + 1;
            debug_StdPrintfDummy(D_00622350, n);
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/way_tool", quick_load_wpfile);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", ExtractWayData);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", wp_print_out);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", draw_way_group);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", way_toolDL);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", debug_WayTool);
extern char D_0063BDA0[];
extern int D_0063BD9C;
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *o);

int play_way(void) {
    char *g;
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, D_0063BDA0);
    }
    f = D_00729B7C[0];
    if (f & 0x20) {
        g = isysGObjSearchFromObjKindID_begin(2);
        switch (D_0063BD9C) {
        case 0:
            while (g != 0) {
                *(int *)(*(char **)(g + 0x164) + 0x350) = 1;
                g = isysGObjSearchFromObjKindID_next(g);
            }
            break;
        case 1:
            while (g != 0) {
                *(int *)(*(char **)(g + 0x164) + 0x350) = 0;
                g = isysGObjSearchFromObjKindID_next(g);
            }
            break;
        }
        D_0063BD9C ^= 1;
    } else if (f & 0x40) {
        return -1;
    }
    return 0;
}
extern unsigned char D_00622368[];
extern int D_0063BD80;
extern void debug_Printf__pn(int, int, int, void *) __asm__("debug_Printf");
extern char *waypoint_with_range(int *, float);

int point_nige(void) {
    int *p;
    int v;

extern char D_004F76A0[];


    if (D_0063B13C & 1) {
        unsigned int color = 0xFF000000;
        debug_Printf__pn(0x12, 0x36, color, D_00622368);
    }
    v = D_00729B7C[0];
    if (v & 0x20) {
        p = (int *)waypoint_with_range((int *)D_004F76A0, 60.0f);
        if (p == 0) {
            return 0;
        }
        D_0063BD80 = p[1];
        if (p[1] >= 0) {
            p[10] ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}
extern char D_00622378[];
extern int load_save_flag;
extern char D_0063BDA8[];
extern char D_0063BDB0[];
extern unsigned char D_00729BF0[];
extern int debugSceClose(int a0);
extern int debugSceOpen(void *a0, int a1);
extern void debug_StdPrintfDummy__pn() __asm__("debug_StdPrintfDummy");
extern void sceWrite(int a0, void *a1, int a2);
extern void sprintf(void *a0, char *a1);

int quick_save_wpfile(void) {
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    load_save_flag = 1;
    sprintf(buf, D_0063BDA8);
    s0 = debugSceOpen(buf, 0x202);
    if (s0 < 0) {
        debug_StdPrintfDummy__pn((int)D_00622378);
        load_save_flag = 0;
        return 0;
    }
    i = 0xF;
    p = &D_00729BF0[i];
    do {
        *p = i;
        p--;
        i--;
    } while (i >= 0);
    sceWrite(s0, D_00729BF0, 0x10);
    debugSceClose(s0);
    debug_StdPrintfDummy__pn((int)D_0063BDB0);
    load_save_flag = 0;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/way_tool", cursor_control);
