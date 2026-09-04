#include "common.h"

typedef struct WayGroup {
    int f0;
    char _4[0x14];
    int f18;
    char _1c[0xC];
    int f28;
    char _2c[0x8];
} WayGroup;

typedef struct { int w[13]; } WayRec;

typedef struct { int w[16]; } WayGroup_DW;

typedef struct { int w[16]; } WayGroup_CT;

typedef struct WpNode { int f0; char _4[0x14]; int f18; char _1C[0x0C]; int f28; char _2C[0x08]; } WpNode;

typedef struct NdW {
    int f0; int _4;
    struct NdW *f8; struct NdW *fC;
    int f10; char _14[0xC];
    int f20; char _24[0x4];
    int f28; char _2C[0x14];
} NdW;
typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;

INCLUDE_ASM("asm/nonmatchings/src/way_llf", InitWayPointSystem);
INCLUDE_ASM("asm/nonmatchings/src/way_llf", func_00215FA8);
INCLUDE_ASM("asm/nonmatchings/src/way_llf", func_00216020);
INCLUDE_ASM("asm/nonmatchings/src/way_llf", DeleteWayGroup);
extern unsigned char D_004F1EC0[];

void CloseWayGroup(int idx)
{
    int *node = (int *)((char *)D_004F1EC0 + idx * 0x34);
    int v1 = node[8 / 4];
    int v0 = node[12 / 4];
    node[20 / 4] = 1;
    *(int *)(v1 + 8) = v0;
    *(int *)(v0 + 12) = v1;
}
extern Nd D_004F31E0[];
extern void sceVu0CopyVector(int *, int);

int CreateWayPoint(int a0)
{
    NdW *node = (NdW *)D_004F31E0;
    int i;
    for (i = 0; i < 0x113; i++) {
        if (node->f0 == 0) {
            node->f0 = 1;
            node->f20 = -1;
            node->f8 = 0;
            node->fC = 0;
            node->f28 = 0;
            sceVu0CopyVector(&node->f10, a0);
            return i;
        }
        node++;
    }
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/way_llf", AddWayPoint);
int AddWayPointTop(int a0, int a1)
{
    int *ch = (int *)&D_004F1EC0[a0 * 0x34];
    Nd *node = &D_004F31E0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}
int InsertWayPointAfter(int dummy, int idx1, int idx2)
{
    int *node_a = (int *)((char *)D_004F31E0 + idx1 * 0x40);
    int *node_b = (int *)((char *)D_004F31E0 + idx2 * 0x40);
    int *old = (int *)node_a[3];
    node_a[3] = (int)node_b;
    node_b[2] = (int)node_a;
    node_b[3] = (int)old;
    old[2] = (int)node_b;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/way_llf", DeleteWayPoint);
extern WpNode D_004F1E8C;

WpNode *WayGroup_begin(void)
{
    WpNode *p = &D_004F1E8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0) return p;
        } while (p != end);
    }
    return 0;
}
extern WpNode D_004F31A4;

WpNode *WayGroup_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0) return q;
        } while (q != end);
    }
    return 0;
}
WpNode *WayBridge_begin(void)
{
    WpNode *p = &D_004F1E8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0) return p;
        } while (p != end);
    }
    return 0;
}
WpNode *WayBridge_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0 && q->f28 != 0) return q;
        } while (q != end);
    }
    return 0;
}
WpNode *WayBridgeAll_begin(void)
{
    WpNode *p = &D_004F1E8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0) return p;
        } while (p != end);
    }
    return 0;
}
WpNode *WayBridgeAll_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0) return q;
        } while (q != end);
    }
    return 0;
}
extern WayRec D_004F1E8C__pn[] __asm__("D_004F1E8C");

void *WayBridgeVar_begin(void) {
    WayRec *p = D_004F1E8C__pn;
    WayRec *end = D_004F1E8C__pn + 94;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++; ; p++) {
        if (p->w[0] != 0 && p->w[6] != 0 && p->w[10] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}
extern WayGroup D_004F31A4__pn __asm__("D_004F31A4");

WayGroup *WayBridgeVar_next(WayGroup *a0) {
    WayGroup *p, *end = &D_004F31A4__pn;
    if (a0 != 0 && a0 != end) {
        for (p = a0 + 1; ; p++) {
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0)
                return p;
            if (p == end)
                break;
        }
    }
    return 0;
}
extern WayGroup_CT D_004F31A0[];

void *WayPoint_begin(void) {
    WayGroup_CT *p = D_004F31A0;
    WayGroup_CT *end = D_004F31A0 + 275;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++;; p++) {
        if (p->w[0] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}
extern WayGroup_DW D_004F7660;

void *WayPoint_next(WayGroup_DW *a0) {
    WayGroup_DW *end = &D_004F7660;
    if (a0 == 0) goto ret0;
    if (a0 == end) goto ret0;
    for (a0++; ; a0++) {
        if (a0->w[0] != 0) return a0;
        if (a0 == end) break;
    }
ret0:
    return 0;
}
extern WayRec D_004F1EC0__pn[] __asm__("D_004F1EC0");

int WayPointList_begin(int a0) {
    return D_004F1EC0__pn[a0].w[2];
}
int WayPointList_next(int *a0) {
    register int v __asm__("$4") = (int)a0;
    __asm__ (
        ".set noreorder\n\t"
        "daddu  $5, $4, $0\n\t"
        "lui    $2, %%hi(D_004F1EC0)\n\t"
        "lw     $3, 0x20($5)\n\t"
        "addiu  $4, $0, 0x34\n\t"
        "addiu  $2, $2, %%lo(D_004F1EC0)\n\t"
        "mult   $3, $3, $4\n\t"
        "addu   $3, $3, $2\n\t"
        "beqz   $5, 1f\n\t"
        " daddu $4, $0, $0\n\t"
        "lw     $4, 0xC($5)\n\t"
        "lw     $2, 0x8($3)\n\t"
        "xor    $2, $4, $2\n\t"
        "movz   $4, $0, $2\n\t"
        "1:\n\t"
        ".set reorder\n\t"
        : "+r"(v) : : "$2", "$3", "$5");
    return v;
}
extern char D_00621EB0[];
extern void debug_StdPrintfDummy(char *fmt, ...);

int waypoint_bidirectional_list(int *self, int which) {
    if (self == 0) {
        return 0;
    }
    debug_StdPrintfDummy(D_00621EB0, self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}
void SetWayGroupActive(int a0, int a1) {
    D_004F1EC0__pn[a0].w[10] = a1;
}
int CheckWayGroupActive(int idx)
{
    return D_004F1EC0__pn[idx].w[10] != 0;
}
