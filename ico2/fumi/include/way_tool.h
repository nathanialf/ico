/*
 * ico2/fumi/include/way_tool.h
 *
 * The declarations of what way_tool.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WAY_TOOL_H
#define WAY_TOOL_H

struct GObj;

/* way_tool.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int play_way(void);
int point_nige(void);
int quick_save_wpfile(void);
void cursor_control(struct GObj *volatile a0);
void ExtractWayData(int stage_no);
int group_create(void);
int point_delete(void);
int point_insert(void);
int quick_load_wpfile(void);
int wp_print_out(void);
int debug_WayTool(void);

/* way-point: one source way point, 0x1C bytes. Reader:
 * ico2/fumi/src/way_tool.c (WaySrcPt, ExtractWayData into WayPoint). Owner:
 * ico2/fumi/include/way_tool.h. */
typedef struct {   /* field names derived */
    float pos[3];  /* 0x00, negated into the way point */
    float float0C; /* 0x0C, WayPoint+0x24 */
    int word10;    /* 0x10, WayPoint+0x28 */
    float float14; /* 0x14, WayPoint+0x2C */
    int bridgeEnd; /* 0x18, WayPoint+0x30 */
} WaySrcPt;        /* derived name */

/* way-group: one source way group, 0x3C bytes. Reader: ico2/fumi/src/
 * way_tool.c (WaySrcGrp, ExtractWayData into WayGroup). Owner:
 * ico2/fumi/include/way_tool.h. */
typedef struct {      /* field names derived */
    char name[32];    /* 0x00 */
    int firstPoint;   /* 0x20 */
    int lastPoint;    /* 0x24 */
    int closed;       /* 0x28 */
    int bridge;       /* 0x2C, WayGroup+0x18 */
    int bridgeEnd[2]; /* 0x30, WayGroup+0x20 */
    int active;       /* 0x38, WayGroup+0x28 */
} WaySrcGrp;          /* derived name */
extern const WaySrcGrp wayGroupSheet[];

extern WaySrcPt wayPointSheet[];

#endif /* WAY_TOOL_H */
