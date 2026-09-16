/*
 * ico2/fumi/include/way_util.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what way_util.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WAY_UTIL_H
#define WAY_UTIL_H

void ez_circle(void);
char *nearest_waypoint_by_lineseg(void *arg0);
int set_bridge(int gid);
int visible_waypoint_of_all(void *a0);
char *visible_waypoint_of_all_except_gid(int *pos, int gid);
char *waypoint_with_range(int *arg0, float thresh);

#endif /* WAY_UTIL_H */
