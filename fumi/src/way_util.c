#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_except_gid);

extern int GetNearNigePointN(void *a0, int a1, int a2, int a3);

int visible_waypoint_of_all_except_gid_ThreadVersion(void *a0, int a1, int a2) {
    return GetNearNigePointN(a0, a1, a2, 0);
}

void visible_waypoint_of_all_except_temp(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_except_temp_ThreadVersion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", ez_line);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", ez_circle);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", short_direction_between_wp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", wgid_next);

void WayUtilWorkAlloc(void) {
    unsigned char work[0x30];
}

void WayUtilWorkFree(void) {
    unsigned char work[0x30];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", shortest_path);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", shortest_path_ThreadVersion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", GetWgAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", set_check_wp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", set_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_of_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_of_group_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_with_range);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_not_bridge_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_from_gobj);

extern int ez_line(void *a0, int a1);

int get_wp_nearest_bridge_side_me(void *a0) {
    return ez_line(a0, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", get_wp_nearest_bridge_side_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", direction_across_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waybridge_between_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", bridge_waypoint_side_me);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_connect_group_side_me);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", bridge_waypoint_side_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_connect_group_side_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", NearestWgFromTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", wpsort_compfnc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178B08);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178BB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178C00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178C58);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178C90);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178D28);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178D70);

extern unsigned char D_00286890[];

int func_00178DB0(int a0) {
    return (D_00286890[a0 >> 3] >> (a0 & 7)) & 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178E08);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_004C7CF0;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_006C8B28;  /* stride 0x8 */

typedef struct {
    unsigned char      f_0;  /* 0x00 */
} S_00286890;

/* end struct shapes */
