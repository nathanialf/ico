#include "common.h"
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

typedef struct {
    int w[13];
} WayRec;

/* way_tool.o .data +0x00: the scratch world position the tool builds a point
   at; the fourth word is the homogeneous 1.0f. */
static float wayWorkPos[4] = {0.0f, 0.0f, 0.0f, 1.0f};

extern WayRec D_004F1EC0[];
extern int D_00639EA4;
extern int D_0063B13C;
extern int D_0063BD78;
extern int D_0063BD84;
extern char D_0063BD88[];
extern WayRec *D_0063C4CC;
extern int D_00729B7C[];
/* kept local: this TU's uses of AddWayPoint do not fit the prototype in way_llf.h */
extern int AddWayPoint(int g, int p);
/* kept local: this TU's uses of CloseWayGroup do not fit the prototype in way_llf.h */
extern int CloseWayGroup(int g);
/* kept local: this TU's uses of CreateWayGroup do not fit the prototype in way_llf.h */
extern int CreateWayGroup(void);
/* kept local: this TU's uses of CreateWayPoint do not fit the prototype in way_llf.h */
extern int CreateWayPoint(void *a0);
/* kept local: this TU's uses of DeleteWayGroup do not fit the prototype in way_llf.h */
extern int DeleteWayGroup(int g);
/* Deferred-`inline` tail members: a plain `inline` function's out-of-line copy
   is emitted at the END of the object in PROTOTYPE order, while its string
   literals are emitted where it is DEFINED. */
inline int play_way(void);
inline int point_nige(void);
inline int quick_save_wpfile(void);
inline void cursor_control(volatile int a0);

int group_create(void)
{
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, "group + create");
    }
    if (D_0063BD84 == 0) {
        int g = CreateWayGroup();

        D_0063BD84 = 1;
        D_0063BD78 = g;
        D_0063C4CC = &D_004F1EC0[g];
        debug_StdPrintfDummy("search:%p %p\n", isysGObjSearchFromObjKindID_begin(0), D_00639EA4);
        return 0;
    }
    if (D_0063BD84 != 1) {
        return 0;
    }
    if (D_0063B13C & 1) {
        debug_Printf(0x1A, 0x42, 0xFF808000, D_0063BD88, D_0063C4CC->w[4]);
    }
    f = D_00729B7C[0];
    if (f & 0x20) {
        int p = CreateWayPoint(wayWorkPos);

        AddWayPoint(D_0063BD78, p);
        debug_StdPrintfDummy("create waypoint %d\n", p);
        return 0;
    }
    if (f & 0x40) {
        if (D_0063C4CC->w[4] == 0) {
            DeleteWayGroup(D_0063BD78);
        }
        D_0063BD84 = 0;
        return -1;
    }
    if (f & 0x80) {
        CloseWayGroup(D_0063BD78);
        D_0063BD84 = 0;
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

extern WayRec D_004F1EC0[];
extern char D_0063BD90[];
extern int D_00729B7C[];
extern int D_0063BD74;
extern int D_0063BD78;
extern int D_0063BD94;
extern int D_0063C4D0;
extern int sprintf();
extern char *strcat(char *d, char *s);
/* kept local: this TU's uses of set_bridge do not fit the prototype in way_util.h */
extern int set_bridge(int gid);

/* relabels the way-group selector; the 2001 source has it as a helper between
   group_create and group_select (SRCFILE.TXT rows 299-311) and group_select
   inlines it at all three of its call sites */
static inline void relabel_way_groups(void)
{
    int n = 0;
    int i;

    for (i = 0; i < 94; i++) {
        if (D_004F1EC0[i].w[0] == 1) {
            sprintf(debugWayGroupSelect[n].s, "% 2d (% 2d) ", n, D_004F1EC0[i].w[4]);
            if (D_004F1EC0[i].w[6] == 1) {
                strcat(debugWayGroupSelect[n].s, D_0063BD90);
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
    WayRec *e;
    int state;
    int i;
    int r;

    state = D_0063BD94;
    if (state == 0) {
        relabel_way_groups();
        for (i = 0; i < 94; i++) {
            e = &D_004F1EC0[i];
            if (e->w[0] == 1) {
                if (i == D_0063BD78) {
                    D_0063C4D0 = i;
                    break;
                }
            }
        }
        D_0063BD94 = 1;
    } else if (state == 1) {
        if (D_00729B7C[0] & 0x2000) {
            set_bridge(D_0063BD78);
            relabel_way_groups();
        } else if (D_00729B7C[0] & 0x8000) {
            D_004F1EC0[D_0063BD78].w[6] = 0;
            relabel_way_groups();
        }
        r = debug_SelectCsvWindow("group + select", 0x12, 0x36, 0xB, debugWayGroupSelect, 8, 0, 1,
                                  D_0063BD74, &D_0063C4D0);
        switch (r) {
        case 0:
            D_0063BD78 = D_0063C4D0;
            return 0;
        case -1:
            D_0063BD94 = 0;
            return -1;
        default:
            D_0063BD94 = 2;
            break;
        }
    } else if (state == 2) {
        D_0063BD78 = D_0063C4D0;
        D_0063BD94 = 0;
        return -1;
    }
    return 0;
}

extern WayRec D_004F1EC0[];
extern int D_0063B13C;
extern int D_0063BD78;
extern int D_0063BD80;
extern char D_0063BD88[];
extern int D_00729B7C[];
/* kept local: this TU's uses of waypoint_with_range do not fit the prototype in way_util.h */
extern char *waypoint_with_range(int *, float);
/* kept local: this TU's uses of DeleteWayPoint do not fit the prototype in way_llf.h */
extern int DeleteWayPoint(int n);
/* kept local: this TU's uses of DeleteWayGroup do not fit the prototype in way_llf.h */
extern int DeleteWayGroup(int g);

int point_delete(void)
{
    WayRec *entry = &D_004F1EC0[D_0063BD78];
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, "point + delete\n");
        if (D_0063B13C & 1) {
            debug_Printf(0x1A, 0x42, 0xFF808000, D_0063BD88, entry->w[4]);
        }
    }
    f = D_00729B7C[0];
    if (f & 0x20) {
        char *res = waypoint_with_range((int *)wayWorkPos, 60.0f);

        if (res == 0) {
            return 0;
        }
        {
            int n = *(int *)(res + 4);

            D_0063BD80 = n;
            if (n >= 0) {
                DeleteWayPoint(n);
                if (entry->w[4] == 0) {
                    DeleteWayGroup(D_0063BD78);
                }
                debug_StdPrintfDummy("delete waypoint %d\n", D_0063BD80);
                return 0;
            }
        }
    } else if (f & 0x40) {
        return -1;
    }
    return 0;
}

/* kept local: this TU's uses of CreateWayPoint do not fit the prototype in way_llf.h */
extern int CreateWayPoint(void *a0);
extern WayRec D_004F1EC0[];
extern int D_0063B13C;
extern int D_0063BD78;
extern char D_0063BD88[];
extern int D_0063BD98;
extern int D_00729B7C[];
/* kept local: this TU's uses of InsertWayPointAfter do not fit the prototype in way_llf.h */
extern int InsertWayPointAfter(int a0, int a1, int a2);
/* kept local: this TU's uses of nearest_waypoint_by_lineseg do not fit the prototype in way_util.h */
extern void *nearest_waypoint_by_lineseg(void *a0);

int point_insert(void)
{
    WayRec *entry = &D_004F1EC0[D_0063BD78];
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, "point + insert\n");
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
        void *res = nearest_waypoint_by_lineseg(wayWorkPos);
        if (*(int *)((char *)res + 0xC) == 0) {
            return 0;
        }
        {
            int n = CreateWayPoint(wayWorkPos);
            InsertWayPointAfter(D_0063BD78, *(int *)((char *)res + 4), n);
            entry->w[4] = entry->w[4] + 1;
            debug_StdPrintfDummy("insert waypoint %d\n", n);
        }
    }
    return 0;
}

extern char D_0063BDA0[];
extern int D_0063BD9C;

inline int play_way(void)
{
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

extern int D_0063BD80;
/* kept local: this TU's uses of waypoint_with_range do not fit the prototype in way_util.h */
extern char *waypoint_with_range(int *, float);

inline int point_nige(void)
{
    int *p;
    int v;

    if (D_0063B13C & 1) {
        unsigned int color = 0xFF000000;
        debug_Printf(0x12, 0x36, color, "point + nige\n");
    }
    v = D_00729B7C[0];
    if (v & 0x20) {
        p = (int *)waypoint_with_range((int *)wayWorkPos, 60.0f);
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

extern int load_save_flag;
extern char D_0063BDA8[];
extern char D_0063BDB0[];
extern unsigned char D_00729BF0[];
extern void sceWrite(int a0, void *a1, int a2);
extern int sprintf();

inline int quick_save_wpfile(void)
{
    char buf[0x70];
    int s0;
    int i;
    unsigned char *p;
    load_save_flag = 1;
    sprintf(buf, D_0063BDA8);
    s0 = debugSceOpen(buf, 0x202);
    if (s0 < 0) {
        debug_StdPrintfDummy("cannot save wp file");
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
    debug_StdPrintfDummy(D_0063BDB0);
    load_save_flag = 0;
    return 1;
}

extern int load_save_flag;
extern char D_0063BDA8[];
extern char D_0063BDB8[];
extern char D_0063BDC0[];
extern char D_0063BDC8[];
extern unsigned char D_00729BF0[];
extern char D_00729BFF[];
extern void sceRead(int a0, void *a1, int a2);
extern int sprintf();
extern void FlushCache(int a0);

int quick_load_wpfile(void)
{
    char buf[0x70];
    int s0;
    int i;
    char *p;

    load_save_flag = 1;
    sprintf(buf, D_0063BDA8);
    s0 = debugSceOpen(buf, 1);
    if (s0 < 0) {
        debug_StdPrintfDummy("cannot load wp file\n");
        load_save_flag = 0;
        return 0;
    }
    FlushCache(0);
    i = 0x1F;
    p = (char *)&D_00729BF0[i];
    do {
        *p = -1;
        p--;
        i--;
    } while (i >= 0);
    sceRead(s0, D_00729BFF, 0x10);
    debugSceClose(s0);
    for (i = -15; i < 17; i++) {
        debug_StdPrintfDummy(D_0063BDB8, D_00729BFF[i]);
    }
    debug_StdPrintfDummy(D_0063BDC0);
    debug_StdPrintfDummy(D_0063BDC8);
    load_save_flag = 0;
    return 1;
}

/* the 0x194-byte per-stage record D_005F5D50: +0x164 is the last way group of
   the stage, +0x170 the first */
typedef struct {
    int _0[0x59];
    int wayGroupEnd;
    int _168[2];
    int wayGroupStart;
    int _174[8];
} WayStgRec;

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

/* the runtime way point node, 0x40 bytes */
typedef struct {
    int _0[4];
    float pos[4];
    int _20;
    float f24;
    int f28;
    float f2C;
    int f30;
    int _34[3];
} WayNode;

/* the way bridge list node */
typedef struct WayBridge {
    int f0;
    int f4;
} WayBridge;

typedef struct {
    float f[4];
} __attribute__((aligned(8))) WayPos;

extern WayStgRec D_005F5D50[];
extern WaySrcGrp wayGroupSheet[];
extern WaySrcPt wayPointSheet[];
extern WayNode D_004F31E0[];
extern WayRec D_004F1EC0[];
extern int D_0063BD74;
extern int D_0063BD78;
/* kept local: this TU's uses of AddWayPoint do not fit the prototype in way_llf.h */
extern int AddWayPoint(int g, int p);
/* kept local: this TU's uses of CloseWayGroup do not fit the prototype in way_llf.h */
extern int CloseWayGroup(int g);
/* kept local: this TU's uses of CreateWayGroup do not fit the prototype in way_llf.h */
extern int CreateWayGroup(void);
/* kept local: this TU's uses of CreateWayPoint do not fit the prototype in way_llf.h */
extern int CreateWayPoint(void *a0);
extern void memset(void *p, int a, int n);
/* kept local: this TU's uses of set_bridge do not fit the prototype in way_util.h */
extern int set_bridge(int gid);
extern WayBridge *WayBridgeAll_begin(void);
extern WayBridge *WayBridgeAll_next(WayBridge *p);

void ExtractWayData(int stage_no)
{
    WayPos v;
    WaySrcGrp *e;
    WaySrcPt *q;
    WayNode *w;
    WayBridge *b;
    int start;
    int end;
    int i;
    int j;
    int g;
    int p;

    start = D_005F5D50[stage_no].wayGroupStart;
    end = D_005F5D50[stage_no].wayGroupEnd;

    for (i = start; i < end; i++) {
        e = &wayGroupSheet[i];
        g = CreateWayGroup();
        D_004F1EC0[g].w[6] = e->f2C;
        D_004F1EC0[g].w[8] = e->f30;
        D_004F1EC0[g].w[9] = e->f34;
        D_004F1EC0[g].w[10] = e->f38;
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
            p = CreateWayPoint(&v);
            AddWayPoint(g, p);
            w = &D_004F31E0[p];
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

    D_0063BD74 = end - start;
    D_0063BD78 = 0;
}

/* the editable way-file base name in .sdata */
typedef struct {
    char s[8];
} WpName;

extern WpName D_0063BDD0[];
extern char D_0063BDD8[];
extern int load_save_flag;
extern int sprintf();
extern int strlen(char *s);
extern void sceWrite(int fd, void *buf, int n);
extern WayRec *WayGroup_begin(void);
extern WayRec *WayGroup_next(WayRec *p);
/* kept local: this TU's uses of WayPointList_begin do not fit the prototype in way_llf.h */
extern WayNode *WayPointList_begin(int g);
/* kept local: this TU's uses of WayPointList_next do not fit the prototype in way_llf.h */
extern WayNode *WayPointList_next(WayNode *p);

int wp_print_out(void)
{
    WpName name = D_0063BDD0[0];
    char line[0x100];
    char fname[0x70];
    WayRec *g;
    WayNode *p;
    int fd;
    int n;

    load_save_flag = 1;
    sprintf(fname, D_0063BDD8, name.s);
    fd = debugSceOpen(fname, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy("cannot open file");
        load_save_flag = 0;
        return 0;
    }
    sprintf(line, "equn\t\t%s_start\n", name.s);
    sceWrite(fd, line, strlen(line));
    for (n = 0, g = WayGroup_begin(); g != 0; g = WayGroup_next(g)) {
        if (g->w[7] != 1) {
            sprintf(line, "\t%d\t%d\t%s_%d_start\t%s_%d_end\t%d\t%d\t%d\t%d\n", n, n, name.s, n,
                    name.s, n, g->w[5], g->w[6], -1, -1);
            sceWrite(fd, line, strlen(line));
            n++;
        }
    }
    sprintf(line, "equn\t\t%s_end\n", name.s);
    sceWrite(fd, line, strlen(line));
    for (n = 0, g = WayGroup_begin(); g != 0; g = WayGroup_next(g)) {
        if (g->w[7] != 1) {
            sprintf(line, "equn\t%s_%d_start\n", name.s, n);
            sceWrite(fd, line, strlen(line));
            for (p = WayPointList_begin(g->w[1]); p != 0; p = WayPointList_next(p)) {
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

typedef struct {
    int c[4];
} WayCol;

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

extern WayRec D_004F1EC0[];
extern int D_0063BD80;
extern WayCol D_00729B60;
extern unsigned int frame_count;
extern void memset(void *p, int a, int n);
/* kept local: this TU's uses of SetVObjRT do not fit the prototype in vobj.h */
extern void SetVObjRT(void *m, void *pos);
/* kept local: this TU's uses of DrawVObj do not fit the prototype in vobj.h */
extern void DrawVObj(int a0, void *v);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
extern void sceVu0UnitMatrix(void *m);

static inline void set_way_point_color(char *p, WayCol *col)
{
    WayCol *d = &D_00729B60;

    if (*(int *)(p + 0x28) != 0) {
        *d = wayColorLinked;
    } else if (*(int *)(p + 0x4) == D_0063BD80) {
        *d = wayColorSelected;
    } else {
        *d = *col;
    }
    if (*(int *)(p + 0x30) != 0 && (frame_count & 0x10)) {
        *d = wayColorBlink;
    }
}

void draw_way_group(int g, WayCol *col)
{
    WayRec *e = &D_004F1EC0[g];
    WayVec m;
    WayVec blink;
    char *p;
    char *q;

    memset(&blink, 0, 16);
    blink.f[1] = (float)frame_count * 0.116355285f;
    m = blink;

    p = *(char **)&e->w[2];
    while (p != 0) {
        q = p + 0x10;
        SetVObjRT(&m, q);
        set_way_point_color(p, col);
        DrawVObj(0, &D_00729B60);
        if (*(int *)(p + 0xC) != 0) {
            gif_StartPacketPri(11);
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            DrawLine(q, *(char **)(p + 0xC) + 0x10, col, 0x800000);
            gif_EndPacket();
        }
        if (*(char **)(p + 0xC) == *(char **)&e->w[2]) {
            break;
        }
        p = *(char **)(p + 0xC);
    }
}

/* the way node position vectors: D_004F31F0 is the +0x10 member of the first
   0x40-byte node of D_004F31E0, so this view indexes the same nodes by their
   position */
typedef struct {
    float v[4];
    char _10[0x30];
} WayNodePos;

extern WayNodePos D_004F31F0[];
extern int D_0063B168;
extern int load_save_flag;
extern int D_00639EA4;
extern int D_0063BD78;
/* kept local: this TU's uses of GetRootPosition do not fit the prototype in geometryManager.h */
extern void GetRootPosition(void *dst, int self);
/* kept local: this TU's uses of visible_waypoint_of_all do not fit the prototype in way_util.h */
extern char *visible_waypoint_of_all(void *pos);
/* kept local: this TU's uses of ez_circle do not fit the prototype in way_util.h */
extern void ez_circle(void *pos, void *base, unsigned int col, float r);

void way_toolDL(int a0)
{
    WayVec m;
    WayVec blink;
    WayVec pp;
    WayRec *e;
    char *w;
    int i;

    if (D_0063B168 == 0) {
        return;
    }
    if (load_save_flag != 0) {
        return;
    }
    GetRootPosition(wayWorkPos, a0);

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());

    memset(&blink, 0, 16);
    blink.f[1] = (float)frame_count * 0.116355285f;
    m = blink;
    SetVObjRT(&m, wayWorkPos);
    DrawVObj(0, &wayColorCursor);

    for (i = 0; i < 94; i++) {
        e = &D_004F1EC0[i];
        if (e->w[0] == 1) {
            if (e->w[10] != 0) {
                if (i == D_0063BD78) {
                    draw_way_group(i, &wayColorOpenCurrent);
                } else {
                    draw_way_group(i, &wayColorOpenOther);
                }
            } else {
                if (i == D_0063BD78) {
                    draw_way_group(i, &wayColorClosedCurrent);
                } else {
                    draw_way_group(i, &wayColorClosedOther);
                }
            }
            if (e->w[6] == 1) {
                sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                gif_StartPacketPri(11);
                if (e->w[8] != -1) {
                    DrawLine(*(char **)&e->w[2] + 0x10, D_004F31F0[e->w[8]].v, &wayColorBridge,
                             0x800000);
                    DrawLine(*(char **)&e->w[3] + 0x10, D_004F31F0[e->w[9]].v, &wayColorBridge,
                             0x800000);
                }
                gif_EndPacket();
            }
        }
    }
    MatrixDrive_PopMatrix();

    GetRootPosition(&blink, D_00639EA4);
    GetRootProjectionPosOfGObj(&pp, D_00639EA4);
    w = visible_waypoint_of_all(&pp);
    if (w != 0) {
        ez_circle(w + 0x10, &blink, 0x80800080, 20.0f);
    }
}

typedef struct {
    char *name;
    int (*fn)();
} WayMenu;

/* way_tool.o .data +0x2A0: the way-tool menu, nine {label, action} lines.
   Line 5's label is the play/stop text the tool rewrites at runtime. */
extern char D_0063BDE0[];
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int group_create(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int point_delete(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int point_insert(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int point_nige(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int play_way(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int quick_save_wpfile(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int quick_load_wpfile(void);
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern int wp_print_out(void);

WayMenu debugWayMenu[9] = {{"group + create", group_create},  {"      + select", group_select},
                           {"point + delete", point_delete},  {"      + insert", point_insert},
                           {"      + nige", point_nige},      {D_0063BDE0, play_way},
                           {"quick save", quick_save_wpfile}, {"quick load", quick_load_wpfile},
                           {"save text", wp_print_out}};

extern int D_0063A44C;
extern int D_00639EC0;
extern int D_0063BD70;
extern int D_0063BDE8;
extern int D_0063BDEC;
extern int D_0063C4D4;
extern char *D_0063C4D8;
extern char D_00729B70[];
extern char D_00729BD0[];
extern char iosPadConfDefault[];
/* kept local: the declaration in way_tool.h changes this TU codegen */
extern void cursor_control(volatile int a0);
/* kept local: this TU's uses of GetRootPosition do not fit the prototype in geometryManager.h */
extern void GetRootPosition(void *dst, int self);
/* kept local: this TU's uses of SetDirectRootPosition do not fit the prototype in geometryManager.h */
extern void SetDirectRootPosition(void *obj, void *pos);

int debug_WayTool(void)
{
    float pos[4];
    int r;
    int (*f)(int);
    int state;

    D_0063C4D8 = isysGObjSearchFromObjLayoutID(2);
    if (D_0063C4D8 != 0) {
        if (D_0063BD70 == 0) {
            *(void **)(D_0063C4D8 + 0x164) = iosMallocDebug(D_0063A44C, 0x850, __FILE__, 0x4AA);
            isysGObjProcAdd(D_0063C4D8, cursor_control, 0, 0x13);
            isysGObjLinkObjDL(D_0063C4D8, way_toolDL, 0, 0, 0xFFFFFFFF);
            D_0063BD70 = 1;
        }
    }

    if (D_0063BD70 == 1) {
        D_0063C4D4 = D_00639EC0;
        D_00639EC0 = (int)D_0063C4D8;
        GetRootPosition(pos, D_0063C4D4);
        SetDirectRootPosition((void *)D_00639EC0, pos);
        Camctrl_SetTarget(D_00639EC0, 0, 3);
        D_0063BD70 = 2;
    }

    iosPadConnect(D_00729B70, 0, 0, iosPadConfDefault);
    iosPadRead(D_00729B70);
    iosPadGetStick(D_00729B70, D_00729BD0, 1, 0, 0, 0);

    state = D_0063BDE8;
    if (state == 1) {
        r = debug_SelectCsvWindow("Way Tool", 0x12, 0x36, 0xB, debugWayMenu, 8, 0, 1, 9,
                                  &D_0063BDEC);
        switch (r) {
        case 0:
            return 0;
        case -1:
            D_0063BD70 = 1;
            D_0063BDE8 = 1;
            D_00639EC0 = D_0063C4D4;
            Camctrl_SetTarget(D_00639EC0, 0, 3);
            return -1;
        default:
            D_0063BD70 = 1;
            D_0063BDE8 = 2;
            break;
        }
    } else if (state == 2) {
        f = debugWayMenu[D_0063BDEC].fn;
        if (f == 0) {
            D_0063BDE8 = 1;
        } else {
            r = f(D_0063BD70);
            if (r == -1) {
                D_0063BDE8 = 1;
            } else if (r != 0) {
                D_0063BDE8 = 1;
            }
        }
    }
    return 0;
}

extern char iosPadConfDefault[];
extern int D_00639EC0;

inline void cursor_control(volatile int a0)
{
    char *w = *(char **)(a0 + 0x164);

    iosPadConnect(w + 0x2D8, 0, 0, iosPadConfDefault);

    while (1) {
        iosPadRead(w + 0x2D8);

        if (a0 == D_00639EC0 && (*(int *)(w + 0x2E4) & 1)) {
            ACTDebugMove(a0, 1);
        }
        _ACTWait(1);
    }
}
