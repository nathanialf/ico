/*
 * ico2/fumi/include/way_util.h
 *
 * The declarations of what way_util.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WAY_UTIL_H
#define WAY_UTIL_H

#include "way_llf.h"

/* way_util.o's global */
extern int load_save_flag;

/* The path-search work block WayUtilWorkAlloc allocates: per-group flags,
   a 94-by-94 cost matrix with its row pointers, and two predecessor and two
   distance arrays (shortest_path uses prev and dist, GetWgAll prev2 and dist2). */
typedef struct WgAll { /* field names derived */
    char *visited;     /* 0x00 visited flag per group */
    int *costBuf;      /* 0x04 the cost matrix's storage */
    int **cost;        /* 0x08 the cost matrix's rows */
    int *prev;         /* 0x0C */
    int *prev2;        /* 0x10 */
    int *dist;         /* 0x14 */
    int *dist2;        /* 0x18 */
} WgAll; /* derived name */

/* The three way points set_check_wp fills: the current one and the two ends
   of the crossing between a group and a bridge. */
typedef struct CheckWp { /* field names derived */
    WayPoint *cur;
    WayPoint *start;
    WayPoint *cross;
} CheckWp; /* derived name */

/* way_util.c's `inline` functions, in the order of their definitions'
   out-of-line copies at the end of the object (first-declaration order). */
WayPoint *visible_waypoint_of_all_except_gid(float *pos, int gid);
WayPoint *visible_waypoint_of_all_except_gid_ThreadVersion(float *pos, int gid);
WayPoint *visible_waypoint_of_all_except_temp(float *pos, int gid);
WayPoint *visible_waypoint_of_all_except_temp_ThreadVersion(float *pos, int gid);
void ez_line(void *a, void *b, unsigned int col);
void ez_circle(void *pos, void *base, unsigned int col, float r);
int short_direction_between_wp(WayPoint *from, WayPoint *to);
int wgid_next(int me, int target);
WgAll *WayUtilWorkAlloc(void);
void WayUtilWorkFree(WgAll *self);
int shortest_path(int from, int to, WgAll *w);
int shortest_path_ThreadVersion(int from, int to, WgAll *w);
int GetWgAll(int from, int to, WgAll *w);
void set_check_wp(CheckWp *out, int wp, int gid);
int set_bridge(int gid);
WayPoint *nearest_waypoint_of_group(float *arg0, int handle);
WayPoint *nearest_waypoint(float *a0);
WayPoint *nearest_waypoint_from_gobj(void *dobj);
WayPoint *nearest_waypoint_by_lineseg_of_group(void *arg0, int gid);
WayPoint *nearest_waypoint_by_lineseg(void *arg0);
WayPoint *nearest_waypoint_by_lineseg_of_group_from_gobj(void *dobj, int gid);
WayPoint *nearest_waypoint_by_lineseg_from_gobj(void *dobj);
WayPoint *waypoint_with_range(float *arg0, float thresh);
WayPoint *nearest_waypoint_of_all_except_group(float *arg0, int a1);
WayPoint *nearest_waypoint_of_all_not_bridge_except_group(float *arg0, int gid);
WayPoint *nearest_waypoint_of_all(float *a0);
WayPoint *visible_waypoint_of_all(void *a0);
void visible_waypoint_of_all_from_gobj(void *a0);
WayPoint *visible_waypoint(float *arg0, int handle);
WayPoint *visible_waypoint_from_gobj(void *dobj, int handle);
WayPoint *get_wp_nearest_bridge_side_me(int arg0, int arg1);
WayPoint *get_wp_nearest_bridge_side_bridge(int arg0, int arg1);
int direction_across_bridge(WayGroup *bridge, int gid);
WayGroup *waybridge_between_group(int a0, int a1);
WayPoint *bridge_waypoint_side_me(int me, int target);
WayPoint *waypoint_connect_group_side_me(WayGroup *a0, int a1);
WayPoint *bridge_waypoint_side_bridge(int a0, int a1);
WayPoint *waypoint_connect_group_side_bridge(WayGroup *a0, int a1);
int NearestWgFromTarget(int cur, int end, WgAll *w);

#endif /* WAY_UTIL_H */
