#include "debug.h"
#include "memory.h"
#include "pad.h"
#include "gobj.h"
#include "gobj_dl.h"
#include "gobj_process.h"
#include "act.h"
#include "camera-root.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include <stdio.h>
#include <eekernel.h>
#include <libvu0.h>
#include <sifdev.h>
#include "way_llf.h"
#include "typedef.h"
#include "vobj.h"
#include "geometryManager.h"
#include "ios.h"
#include "GifPacket.h"
#include <string.h>
#include "way_util.h"
#include "way_tool.h"
#include "main.h"

/* way_tool.o .data +0x00: the scratch world position the tool builds a point
   at; the fourth word is the homogeneous 1.0f. */
static float wayWorkPos[4] = {0.0f, 0.0f, 0.0f, 1.0f};

/* the way point the tool has picked, -1 for none: point_delete sets it,
   point_nige moves it and set_way_point_color highlights it */
static int wayPointSel = -1; /* derived name */

/* .sbss, owned by way_tool.o (MAIN.MAP names no symbol in the run), in the ROM's run order: the way
   record the tool is showing, the group the selection window is on, the camera
   target saved while the tool holds the camera, and the cursor object */
static WayGroup *selectedWay;

static int wayGroupSel;

static int savedCamTarget;

static char *cursorGObj;

typedef struct {
    int c[4];
} WayCol;

/* .bss, owned by way_tool.o (MAIN.MAP sizes its own link's run 0xD0 and names
   no symbol in it), in the ROM's run order: the colour packet every way point
   is drawn through, the pad handle and its read buffer, the stick buffer, and
   the 32-byte way-point file block quick_save_wpfile writes and
   quick_load_wpfile reads back. */
static WayCol wayDrawCol;

static char wayToolPad[96];

static char wayToolStick[32];

static unsigned char wpBuf[32];

/* RECONSTRUCTION: the last 0x220 bytes of the TU's .bss (VMA 0x729C10..
   0x729E30), which nothing in the retail ELF or the January listing reads.
   What the bytes pin: an uninitialised object of 544 bytes after wpBuf and
   before access.o's run; the January listing's link lays it out at the same
   place, and MAIN.MAP sizes way_tool.o's .bss 0x20 above its seven live
   statics, the same 32-byte buffer this file keeps elsewhere, grown by 0x200
   in retail.  What they cannot pin: its type, name or the debug code that
   used it. */
static char wayToolBuf[544]; /* derived name */

/* Deferred-`inline` tail members: a plain `inline` function's out-of-line copy
   is emitted at the END of the object in PROTOTYPE order, while its string
   literals are emitted where it is DEFINED. */
inline int play_way(void);
inline int point_nige(void);
inline int quick_save_wpfile(void);
inline void cursor_control(volatile int a0);

int group_create(void)
{
    static int createState = 0; /* derived name */
    int f;

    if (debug_font_flag & 1) {
        debug_Printf(18, 54, 0xFF000000, "group + create");
    }
    if (createState == 0) {
        int g = CreateWayGroup();

        createState = 1;
        current_select_gid = g;
        selectedWay = &way_group[g];
        debug_StdPrintfDummy("search:%p %p\n", isysGObjSearchFromObjKindID_begin(0), (int)boyGObj);
        return 0;
    }
    if (createState != 1) {
        return 0;
    }
    if (debug_font_flag & 1) {
        debug_Printf(26, 66, 0xFF808000, "pt.%d", selectedWay->f10);
    }
    f = *(int *)&wayToolPad[12];
    if (f & 0x20) {
        int p = CreateWayPoint(wayWorkPos);

        AddWayPoint(current_select_gid, p);
        debug_StdPrintfDummy("create waypoint %d\n", p);
        return 0;
    }
    if (f & 0x40) {
        if (selectedWay->f10 == 0) {
            DeleteWayGroup(current_select_gid);
        }
        createState = 0;
        return -1;
    }
    if (f & 0x80) {
        CloseWayGroup(current_select_gid);
        createState = 0;
        return -1;
    }
    return 0;
}

/* one line of the way-group selector: debug_SelectCsvWindow walks debugWayGroupSelect
   with stride 8 and dereferences the first word */
typedef struct {
    char *s;
    int _4;
} WayMenuLine;

/* way_tool.o .data +0x10: the way-group selector's 64 lines.  The label text is
   a 2001 string literal per line (" 0 ( -)  " .. "63 ( -)  ") that
   relabel_way_groups rewrites in place; until the TU's .rodata run is carved
   the literals are reached as the externs the blob defines. */

WayMenuLine debugWayGroupSelect[64] = {
    {" 0 ( -)  ", 0}, {" 1 ( -)  ", 0}, {" 2 ( -)  ", 0}, {" 3 ( -)  ", 0}, {" 4 ( -)  ", 0},
    {" 5 ( -)  ", 0}, {" 6 ( -)  ", 0}, {" 7 ( -)  ", 0}, {" 8 ( -)  ", 0}, {" 9 ( -)  ", 0},
    {"10 ( -)  ", 0}, {"11 ( -)  ", 0}, {"12 ( -)  ", 0}, {"13 ( -)  ", 0}, {"14 ( -)  ", 0},
    {"15 ( -)  ", 0}, {"16 ( -)  ", 0}, {"17 ( -)  ", 0}, {"18 ( -)  ", 0}, {"19 ( -)  ", 0},
    {"20 ( -)  ", 0}, {"21 ( -)  ", 0}, {"22 ( -)  ", 0}, {"23 ( -)  ", 0}, {"24 ( -)  ", 0},
    {"25 ( -)  ", 0}, {"26 ( -)  ", 0}, {"27 ( -)  ", 0}, {"28 ( -)  ", 0}, {"29 ( -)  ", 0},
    {"30 ( -)  ", 0}, {"31 ( -)  ", 0}, {"32 ( -)  ", 0}, {"33 ( -)  ", 0}, {"34 ( -)  ", 0},
    {"35 ( -)  ", 0}, {"36 ( -)  ", 0}, {"37 ( -)  ", 0}, {"38 ( -)  ", 0}, {"39 ( -)  ", 0},
    {"40 ( -)  ", 0}, {"41 ( -)  ", 0}, {"42 ( -)  ", 0}, {"43 ( -)  ", 0}, {"44 ( -)  ", 0},
    {"45 ( -)  ", 0}, {"46 ( -)  ", 0}, {"47 ( -)  ", 0}, {"48 ( -)  ", 0}, {"49 ( -)  ", 0},
    {"50 ( -)  ", 0}, {"51 ( -)  ", 0}, {"52 ( -)  ", 0}, {"53 ( -)  ", 0}, {"54 ( -)  ", 0},
    {"55 ( -)  ", 0}, {"56 ( -)  ", 0}, {"57 ( -)  ", 0}, {"58 ( -)  ", 0}, {"59 ( -)  ", 0},
    {"60 ( -)  ", 0}, {"61 ( -)  ", 0}, {"62 ( -)  ", 0}, {"63 ( -)  ", 0}};

/* relabels the way-group selector; the 2001 source has it as a helper between
   group_create and group_select (SRCFILE.TXT rows 299-311) and group_select
   inlines it at all three of its call sites */
static inline void relabel_way_groups(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 94; i++) {
        if (way_group[i].f0 == 1) {
            sprintf(debugWayGroupSelect[n].s, "% 2d (% 2d) ", n, way_group[i].f10);
            if (way_group[i].f18 == 1) {
                strcat(debugWayGroupSelect[n].s, "b");
            }
            n++;
        }
    }
}

/* census group_select, a file static: MAIN.MAP puts the only global
   group_select in ico2/omori/src/camera-editor.o.  debugWayMenu below holds
   its address, which is why this TU kept the global symbol until the table
   became C. */
static int group_select(void)
{
    static int selectState = 0; /* derived name */
    WayGroup *e;
    int state;
    int i;
    int r;

    state = selectState;
    if (state == 0) {
        relabel_way_groups();
        for (i = 0; i < 94; i++) {
            e = &way_group[i];
            if (e->f0 == 1) {
                if (i == current_select_gid) {
                    wayGroupSel = i;
                    break;
                }
            }
        }
        selectState = 1;
    } else if (state == 1) {
        if ((*(int *)&wayToolPad[12]) & 0x2000) {
            set_bridge(current_select_gid);
            relabel_way_groups();
        } else if ((*(int *)&wayToolPad[12]) & 0x8000) {
            way_group[current_select_gid].f18 = 0;
            relabel_way_groups();
        }
        r = debug_SelectCsvWindow("group + select", 0x12, 0x36, 0xB, debugWayGroupSelect, 8, 0, 1,
                                  n_way_group, &wayGroupSel);
        switch (r) {
        case 0:
            current_select_gid = wayGroupSel;
            return 0;
        case -1:
            selectState = 0;
            return -1;
        default:
            selectState = 2;
            break;
        }
    } else if (state == 2) {
        current_select_gid = wayGroupSel;
        selectState = 0;
        return -1;
    }
    return 0;
}

int point_delete(void)
{
    WayGroup *entry = &way_group[current_select_gid];
    int f;

    if (debug_font_flag & 1) {
        debug_Printf(18, 54, 0xFF000000, "point + delete\n");
        if (debug_font_flag & 1) {
            debug_Printf(26, 66, 0xFF808000, "pt.%d", entry->f10);
        }
    }
    f = *(int *)&wayToolPad[12];
    if (f & 0x20) {
        WayPoint *res = waypoint_with_range(wayWorkPos, 60.0f);

        if (res == 0) {
            return 0;
        }
        {
            int n = res->f4;

            wayPointSel = n;
            if (n >= 0) {
                DeleteWayPoint(n);
                if (entry->f10 == 0) {
                    DeleteWayGroup(current_select_gid);
                }
                debug_StdPrintfDummy("delete waypoint %d\n", wayPointSel);
                return 0;
            }
        }
    } else if (f & 0x40) {
        return -1;
    }
    return 0;
}

int point_insert(void)
{
    static int insertState = 0; /* derived name */
    WayGroup *entry = &way_group[current_select_gid];
    int f;

    if (debug_font_flag & 1) {
        debug_Printf(18, 54, 0xFF000000, "point + insert\n");
        if (debug_font_flag & 1) {
            debug_Printf(26, 66, 0xFF808000, "pt.%d", entry->f10);
        }
    }
    insertState = 1;
    f = *(int *)&wayToolPad[12];
    if (!(f & 0x20)) {
        if (f & 0x40) {
            insertState = 0;
            return -1;
        }
        return 0;
    }
    {
        WayPoint *res = nearest_waypoint_by_lineseg(wayWorkPos);
        if (res->fC == 0) {
            return 0;
        }
        {
            int n = CreateWayPoint(wayWorkPos);
            InsertWayPointAfter(current_select_gid, res->f4, n);
            entry->f10 = entry->f10 + 1;
            debug_StdPrintfDummy("insert waypoint %d\n", n);
        }
    }
    return 0;
}

inline int play_way(void)
{
    static int playMode = 0; /* derived name */
    char *g;
    int f;

    if (debug_font_flag & 1) {
        debug_Printf(18, 54, 0xFF000000, "to boy\n");
    }
    f = *(int *)&wayToolPad[12];
    if (f & 0x20) {
        g = isysGObjSearchFromObjKindID_begin(2);
        switch (playMode) {
        case 0:
            while (g != 0) {
                GOBJ_ACT(g)->f_350 = 1;
                g = isysGObjSearchFromObjKindID_next(g);
            }
            break;
        case 1:
            while (g != 0) {
                GOBJ_ACT(g)->f_350 = 0;
                g = isysGObjSearchFromObjKindID_next(g);
            }
            break;
        }
        playMode ^= 1;
    } else if (f & 0x40) {
        return -1;
    }
    return 0;
}

inline int point_nige(void)
{
    WayPoint *p;
    int v;

    if (debug_font_flag & 1) {
        unsigned int color = 0xFF000000;
        debug_Printf(18, 54, color, "point + nige\n");
    }
    v = *(int *)&wayToolPad[12];
    if (v & 0x20) {
        p = waypoint_with_range(wayWorkPos, 60.0f);
        if (p == 0) {
            return 0;
        }
        wayPointSel = p->f4;
        if (p->f4 >= 0) {
            p->f28 ^= 1;
        }
    } else if (v & 0x40) {
        return -1;
    }
    return 0;
}

inline int quick_save_wpfile(void)
{
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    load_save_flag = 1;
    sprintf(buf, "test.wp");
    s0 = debugSceOpen(buf, 0x202);
    if (s0 < 0) {
        debug_StdPrintfDummy("cannot save wp file");
        load_save_flag = 0;
        return 0;
    }
    i = 0xF;
    p = &wpBuf[i];
    do {
        *p = i;
        p--;
        i--;
    } while (i >= 0);
    sceWrite(s0, wpBuf, 0x10);
    debugSceClose(s0);
    debug_StdPrintfDummy("saved\n");
    load_save_flag = 0;
    return 1;
}

int quick_load_wpfile(void)
{
    char buf[0x70];
    int s0;
    int i;
    char *p;

    load_save_flag = 1;
    sprintf(buf, "test.wp");
    s0 = debugSceOpen(buf, 1);
    if (s0 < 0) {
        debug_StdPrintfDummy("cannot load wp file\n");
        load_save_flag = 0;
        return 0;
    }
    FlushCache(0);
    i = 0x1F;
    p = (char *)&wpBuf[i];
    do {
        *p = -1;
        p--;
        i--;
    } while (i >= 0);
    sceRead(s0, &wpBuf[15], 0x10);
    debugSceClose(s0);
    for (i = -15; i < 17; i++) {
        debug_StdPrintfDummy("%d ", ((char *)wpBuf)[i + 15]);
    }
    debug_StdPrintfDummy("\n");
    debug_StdPrintfDummy("loaded\n");
    load_save_flag = 0;
    return 1;
}

/* the authored way group table: one 0x3C record per group */
typedef struct {
    int _0[8];
    int firstPoint;
    int lastPoint;
    int closed;
    int f2C;
    int f30;
    int f34;
    int f38;
} WaySrcGrp;

/* the authored way point table: one 0x1C record per point */
typedef struct {
    float x;
    float y;
    float z;
    float fC;
    int f10;
    float f14;
    int f18;
} WaySrcPt;

typedef struct {
    float f[4];
} __attribute__((aligned(8))) WayPos;

extern StgPre stageData[];
extern WaySrcGrp wayGroupSheet[];
extern WaySrcPt wayPointSheet[];

void ExtractWayData(int stage_no)
{
    WayPos v;
    WaySrcGrp *e;
    WaySrcPt *q;
    WayPoint *w;
    WayGroup *b;
    int start;
    int end;
    int i;
    int j;
    int g;
    int p;

    start = stageData[stage_no].wayGroupStart;
    end = stageData[stage_no].wayGroupEnd;

    for (i = start; i < end; i++) {
        e = &wayGroupSheet[i];
        g = CreateWayGroup();
        way_group[g].f18 = e->f2C;
        way_group[g].end[0] = e->f30;
        way_group[g].end[1] = e->f34;
        way_group[g].f28 = e->f38;
        for (j = e->firstPoint; j < e->lastPoint; j++) {
            q = &wayPointSheet[j];
            {
                WayPos t;

                memset(&t, 0, 16);
                t.f[0] = -q->x;
                t.f[1] = -q->y;
                t.f[2] = -q->z;
                v = t;
            }
            p = CreateWayPoint(v.f);
            AddWayPoint(g, p);
            w = &way_point[p];
            w->f24 = q->fC;
            w->f28 = q->f10;
            w->f2C = q->f14;
            w->f30 = q->f18;
        }
        if (e->closed == 1) {
            CloseWayGroup(g);
        }
    }

    for (b = WayBridgeAll_begin(); b != 0; b = WayBridgeAll_next(b)) {
        set_bridge(b->f4);
    }

    n_way_group = end - start;
    current_select_gid = 0;
}

/* the editable way-file base name in .sdata */
typedef struct {
    char s[8];
} WpName;

int wp_print_out(void)
{
    WpName name = {"way0000"};
    char line[0x100];
    char fname[0x70];
    WayGroup *g;
    WayPoint *p;
    int fd;
    int n;

    load_save_flag = 1;
    sprintf(fname, "%s.txt", name.s);
    fd = debugSceOpen(fname, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy("cannot open file");
        load_save_flag = 0;
        return 0;
    }
    sprintf(line, "equn\t\t%s_start\n", name.s);
    sceWrite(fd, line, strlen(line));
    for (n = 0, g = WayGroup_begin(); g != 0; g = WayGroup_next(g)) {
        if (g->f1C != 1) {
            sprintf(line, "\t%d\t%d\t%s_%d_start\t%s_%d_end\t%d\t%d\t%d\t%d\n", n, n, name.s, n,
                    name.s, n, g->f14, g->f18, -1, -1);
            sceWrite(fd, line, strlen(line));
            n++;
        }
    }
    sprintf(line, "equn\t\t%s_end\n", name.s);
    sceWrite(fd, line, strlen(line));
    for (n = 0, g = WayGroup_begin(); g != 0; g = WayGroup_next(g)) {
        if (g->f1C != 1) {
            sprintf(line, "equn\t%s_%d_start\n", name.s, n);
            sceWrite(fd, line, strlen(line));
            for (p = WayPointList_begin(g->f4); p != 0; p = WayPointList_next(p)) {
                sprintf(line, "\t\t\t%d\t%d\t%d\t\t%d\t%d\n", (int)-p->pos[0], (int)-p->pos[1],
                        (int)-p->pos[2], (int)p->f24, p->f28);
                sceWrite(fd, line, strlen(line));
            }
            sprintf(line, "equn\t%s_%d_end\n", name.s, n);
            sceWrite(fd, line, strlen(line));
            n++;
        }
    }
    debugSceClose(fd);
    load_save_flag = 0;
    return -1;
}

typedef struct {
    float f[4];
} __attribute__((aligned(8))) WayVec;

/* way_tool.o .data +0x210: the nine RGBA packets the tool draws with. */
static WayCol wayColorSelected = {{0xFF, 0xFF, 0xFF, 0xFF}};

static WayCol wayColorLinked = {{0xFF, 0x08, 0xFF, 0xFF}};

static WayCol wayColorBlink = {{0xFF, 0xFF, 0xFF, 0xFF}};

static WayCol wayColorCursor = {{0x80, 0xFF, 0x1E, 0xFF}};

static WayCol wayColorOpenCurrent = {{0x20, 0xFF, 0x20, 0xFF}};

static WayCol wayColorOpenOther = {{0x20, 0x80, 0x20, 0x30}};

static WayCol wayColorClosedCurrent = {{0x40, 0x40, 0x00, 0xFF}};

static WayCol wayColorClosedOther = {{0x40, 0x40, 0x00, 0x40}};

static WayCol wayColorBridge = {{0xFF, 0x00, 0xFF, 0xFF}};

static inline void set_way_point_color(WayPoint *p, WayCol *col)
{
    WayCol *d = &wayDrawCol;

    if (p->f28 != 0) {
        *d = wayColorLinked;
    } else if (p->f4 == wayPointSel) {
        *d = wayColorSelected;
    } else {
        *d = *col;
    }
    if (p->f30 != 0 && (((unsigned int)frame_count) & 0x10)) {
        *d = wayColorBlink;
    }
}

void draw_way_group(int g, WayCol *col)
{
    WayGroup *e = &way_group[g];
    WayVec m;
    WayVec blink;
    WayPoint *p;
    float *q;

    memset(&blink, 0, 16);
    blink.f[1] = (float)((unsigned int)frame_count) * 0.116355285f;
    m = blink;

    p = e->f8;
    while (p != 0) {
        q = p->pos;
        SetVObjRT(&m, q);
        set_way_point_color(p, col);
        DrawVObj(0, &wayDrawCol);
        if (p->fC != 0) {
            gif_StartPacketPri(11);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLine(q, p->fC->pos, col, 0x800000);
            gif_EndPacket();
        }
        if (p->fC == e->f8) {
            break;
        }
        p = p->fC;
    }
}

void way_toolDL(int a0)
{
    WayVec m;
    WayVec blink;
    WayVec pp;
    WayGroup *e;
    WayPoint *w;
    int i;

    if (debug_wayline == 0) {
        return;
    }
    if (load_save_flag != 0) {
        return;
    }
    GetRootPosition(wayWorkPos, a0);

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());

    memset(&blink, 0, 16);
    blink.f[1] = (float)((unsigned int)frame_count) * 0.116355285f;
    m = blink;
    SetVObjRT(&m, wayWorkPos);
    DrawVObj(0, &wayColorCursor);

    for (i = 0; i < 94; i++) {
        e = &way_group[i];
        if (e->f0 == 1) {
            if (e->f28 != 0) {
                if (i == current_select_gid) {
                    draw_way_group(i, &wayColorOpenCurrent);
                } else {
                    draw_way_group(i, &wayColorOpenOther);
                }
            } else {
                if (i == current_select_gid) {
                    draw_way_group(i, &wayColorClosedCurrent);
                } else {
                    draw_way_group(i, &wayColorClosedOther);
                }
            }
            if (e->f18 == 1) {
                sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                gif_StartPacketPri(11);
                if (e->end[0] != -1) {
                    DrawLine(e->f8->pos, way_point[e->end[0]].pos, &wayColorBridge, 0x800000);
                    DrawLine(e->fC->pos, way_point[e->end[1]].pos, &wayColorBridge, 0x800000);
                }
                gif_EndPacket();
            }
        }
    }
    MatrixDrive_PopMatrix();

    GetRootPosition(&blink, (int)boyGObj);
    GetRootProjectionPosOfGObj(&pp, (int)boyGObj);
    w = visible_waypoint_of_all(&pp);
    if (w != 0) {
        ez_circle(w->pos, &blink, 0x80800080, 20.0f);
    }
}

typedef struct {
    char *name;
    int (*fn)();
} WayMenu;

/* way_tool.o .data +0x2A0: the way-tool menu, nine {label, action} lines.
   Line 5's label is the play/stop text the tool rewrites at runtime. */

WayMenu debugWayMenu[9] = {{"group + create", group_create},  {"      + select", group_select},
                           {"point + delete", point_delete},  {"      + insert", point_insert},
                           {"      + nige", point_nige},      {"play", play_way},
                           {"quick save", quick_save_wpfile}, {"quick load", quick_load_wpfile},
                           {"save text", wp_print_out}};

extern char iosPadConfDefault[];

int debug_WayTool(void)
{
    static int menuState = 1; /* derived name */
    static int menuSel = 0;   /* derived name */
    float pos[4];
    int r;
    int (*f)(int);
    int state;

    cursorGObj = isysGObjSearchFromObjLayoutID(2);
    if (cursorGObj != 0) {
        if (first_waytool == 0) {
            *(void **)(cursorGObj + 0x164) =
                iosMallocDebug(ios_partition_seki, 0x850, __FILE__, 0x4AA);
            isysGObjProcAdd(cursorGObj, cursor_control, 0, 0x13);
            isysGObjLinkObjDL(cursorGObj, way_toolDL, 0, 0, 0xFFFFFFFF);
            first_waytool = 1;
        }
    }

    if (first_waytool == 1) {
        savedCamTarget = (int)CurrentTargetGObj;
        CurrentTargetGObj = (int)cursorGObj;
        GetRootPosition(pos, savedCamTarget);
        SetDirectRootPosition((void *)((int)CurrentTargetGObj), pos);
        Camctrl_SetTarget((int)CurrentTargetGObj, 0, 3);
        first_waytool = 2;
    }

    iosPadConnect(wayToolPad, 0, 0, iosPadConfDefault);
    iosPadRead(wayToolPad);
    iosPadGetStick(wayToolPad, wayToolStick, 1, 0, 0, 0);

    state = menuState;
    if (state == 1) {
        r = debug_SelectCsvWindow("Way Tool", 0x12, 0x36, 0xB, debugWayMenu, 8, 0, 1, 9, &menuSel);
        switch (r) {
        case 0:
            return 0;
        case -1:
            first_waytool = 1;
            menuState = 1;
            CurrentTargetGObj = savedCamTarget;
            Camctrl_SetTarget((int)CurrentTargetGObj, 0, 3);
            return -1;
        default:
            first_waytool = 1;
            menuState = 2;
            break;
        }
    } else if (state == 2) {
        f = debugWayMenu[menuSel].fn;
        if (f == 0) {
            menuState = 1;
        } else {
            r = f(first_waytool);
            if (r == -1) {
                menuState = 1;
            } else if (r != 0) {
                menuState = 1;
            }
        }
    }
    return 0;
}

inline void cursor_control(volatile int a0)
{
    Act *w = GOBJ_ACT(a0);

    iosPadConnect((char *)w + 0x2D8, 0, 0, iosPadConfDefault);

    while (1) {
        iosPadRead((char *)w + 0x2D8);

        if (a0 == (int)CurrentTargetGObj && (w->unk2E4 & 1)) {
            ACTDebugMove(a0, 1);
        }
        _ACTWait(1);
    }
}
