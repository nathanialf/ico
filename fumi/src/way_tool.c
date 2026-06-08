#include "common.h"

extern int D_0062BB80;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", group_create);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", group_select);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_delete);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_insert);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", quick_load_wpfile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", ExtractWayData);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", wp_print_out);

extern int D_0062AF84;
extern int D_0070BBFC[];
extern unsigned char D_006141F8[];
extern void traceLine(int, int, int, void *);
extern char *visible_waypoint_of_all(int *, float);

int draw_way_group(void) {
    int *p;
    int v;

extern char D_004CB2B0[];


    if (D_0062AF84 & 1) {
        unsigned int color = 0xFF000000;
        traceLine(0x12, 0x36, color, D_006141F8);
    }
    v = D_0070BBFC[0];
    if (v & 0x20) {
        p = (int *)visible_waypoint_of_all((int *)D_004CB2B0, 60.0f);
        if (p == 0) {
            return 0;
        }
        D_0062BB80 = p[1];
        if (p[1] >= 0) {
            p[10] ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", way_toolDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", debug_WayTool);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", play_way);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", point_nige);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", quick_save_wpfile);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", cursor_control);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", func_00204EF0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_tool", func_002050B0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
} S_004CB550;  /* stride 0x8 */

/* end struct shapes */
