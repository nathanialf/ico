#include "common.h"

typedef struct {
    int w[13];
} WayRec;

extern WayRec D_004F1EC0[];
extern char D_004F76A0[];
extern char D_00621EC0[];
extern char D_00621ED0[];
extern char D_00621EE0[];
extern int D_00639EA4;
extern int D_0063B13C;
extern int D_0063BD78;
extern int D_0063BD84;
extern char D_0063BD88[];
extern WayRec *D_0063C4CC;
extern int D_00729B7C[];
extern int AddWayPoint(int g, int p);
extern int CloseWayGroup(int g);
extern int CreateWayGroup(void);
extern int CreateWayPoint(void *a0);
extern int DeleteWayGroup(int g);
extern void debug_Printf();
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void *isysGObjSearchFromObjKindID_begin(int id);

int group_create(void)
{
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, D_00621EC0);
    }
    if (D_0063BD84 == 0) {
        int g = CreateWayGroup();

        D_0063BD84 = 1;
        D_0063BD78 = g;
        D_0063C4CC = &D_004F1EC0[g];
        debug_StdPrintfDummy(D_00621ED0, isysGObjSearchFromObjKindID_begin(0), D_00639EA4);
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
        int p = CreateWayPoint(D_004F76A0);

        AddWayPoint(D_0063BD78, p);
        debug_StdPrintfDummy(D_00621EE0, p);
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

INCLUDE_ASM("asm/nonmatchings/src/way_tool", group_select);

extern WayRec D_004F1EC0[];
extern char D_004F76A0[];
extern char D_00622318[];
extern char D_00622328[];
extern int D_0063B13C;
extern int D_0063BD78;
extern int D_0063BD80;
extern char D_0063BD88[];
extern int D_00729B7C[];
extern void debug_Printf();
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char *waypoint_with_range(int *, float);
extern int DeleteWayPoint(int n);
extern int DeleteWayGroup(int g);

int point_delete(void)
{
    WayRec *entry = &D_004F1EC0[D_0063BD78];
    int f;

    if (D_0063B13C & 1) {
        debug_Printf(0x12, 0x36, 0xFF000000, D_00622318);
        if (D_0063B13C & 1) {
            debug_Printf(0x1A, 0x42, 0xFF808000, D_0063BD88, entry->w[4]);
        }
    }
    f = D_00729B7C[0];
    if (f & 0x20) {
        char *res = waypoint_with_range((int *)D_004F76A0, 60.0f);

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
                debug_StdPrintfDummy(D_00622328, D_0063BD80);
                return 0;
            }
        }
    } else if (f & 0x40) {
        return -1;
    }
    return 0;
}

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

int point_insert(void)
{
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
        if (*(int *)((char *)res + 0xC) == 0) {
            return 0;
        }
        {
            int n = CreateWayPoint(D_004F76A0);
            InsertWayPointAfter(D_0063BD78, *(int *)((char *)res + 4), n);
            entry->w[4] = entry->w[4] + 1;
            debug_StdPrintfDummy(D_00622350, n);
        }
    }
    return 0;
}

extern int load_save_flag;
extern char D_00622390[];
extern char D_0063BDA8[];
extern char D_0063BDB8[];
extern char D_0063BDC0[];
extern char D_0063BDC8[];
extern unsigned char D_00729BF0[];
extern char D_00729BFF[];
extern int debugSceClose(int a0);
extern int debugSceOpen(void *a0, int a1);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern void sceRead(int a0, void *a1, int a2);
extern void sprintf(void *a0, char *a1);
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
        debug_StdPrintfDummy(D_00622390);
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

INCLUDE_ASM("asm/nonmatchings/src/way_tool", ExtractWayData);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", wp_print_out);

typedef struct {
    float f[4];
} __attribute__((aligned(8))) WayVec;

typedef struct {
    int c[4];
} WayCol;

extern WayRec D_004F1EC0[];
extern WayCol D_004F78B0;
extern WayCol D_004F78C0;
extern WayCol D_004F78D0;
extern int D_0063BD80;
extern WayCol D_00729B60;
extern unsigned int frame_count;
extern void memset(void *p, int a, int n);
extern void SetVObjRT(void *m, void *pos);
extern void DrawVObj(int a0, void *v);
extern void DrawLine(void *a, void *b, void *col, int flags);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);

static inline void set_way_point_color(char *p, WayCol *col)
{
    WayCol *d = &D_00729B60;

    if (*(int *)(p + 0x28) != 0) {
        *d = D_004F78C0;
    } else if (*(int *)(p + 0x4) == D_0063BD80) {
        *d = D_004F78B0;
    } else {
        *d = *col;
    }
    if (*(int *)(p + 0x30) != 0 && (frame_count & 0x10)) {
        *d = D_004F78D0;
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

ASM_LIT4_SLOT(D_00639868, 0.116355285f);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", way_toolDL);
INCLUDE_ASM("asm/nonmatchings/src/way_tool", debug_WayTool);

extern char D_0063BDA0[];
extern int D_0063BD9C;
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *o);

int play_way(void)
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

extern unsigned char D_00622368[];
extern int D_0063BD80;
extern void debug_Printf__pn(int, int, int, void *) __asm__("debug_Printf");
extern char *waypoint_with_range(int *, float);

int point_nige(void)
{
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

int quick_save_wpfile(void)
{
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

extern char iosPadConfDefault[];
extern int D_00639EC0;
extern void ACTDebugMove(int a0, int a1);
extern void _ACTWait(int a0);
extern int iosPadConnect(void *a0, int a1, int a2, void *a3);
extern void iosPadRead(void *a0);

void cursor_control(volatile int a0)
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
