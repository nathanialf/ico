#include "common.h"

typedef struct WpNode { int f0; char _4[0x14]; int f18; char _1C[0x0C]; int f28; char _2C[0x08]; } WpNode;


typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
extern unsigned char D_004CAEC0[];
extern Nd D_004CC1E0[];
typedef struct NdW {
    int f0; int _4;
    struct NdW *f8; struct NdW *fC;
    int f10; char _14[0xC];
    int f20; char _24[0x4];
    int f28; char _2C[0x14];
} NdW;
extern void sceVu0CopyVector(int *, int);

int CreateWayPoint(int a0)
{
    NdW *node = (NdW *)D_004CC1E0;
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

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", AddWayPoint);

int AddWayPointTop(int a0, int a1)
{
    int *ch = (int *)&D_004CAEC0[a0 * 0x34];
    Nd *node = &D_004CC1E0[a1];
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
    int *node_a = (int *)((char *)D_004CC1E0 + idx1 * 0x40);
    int *node_b = (int *)((char *)D_004CC1E0 + idx2 * 0x40);
    int *old = (int *)node_a[3];
    node_a[3] = (int)node_b;
    node_b[2] = (int)node_a;
    node_b[3] = (int)old;
    old[2] = (int)node_b;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", NearestEnemyFromGirl);

extern WpNode D_004CAE8C;

WpNode *NumOfWpPos(void)
{
    WpNode *p = &D_004CAE8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0) return p;
        } while (p != end);
    }
    return 0;
}

extern WpNode D_004CC1A4;

WpNode *CopyWpPos(WpNode *p)
{
    WpNode *end = &D_004CC1A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0) return q;
        } while (q != end);
    }
    return 0;
}

WpNode *WayLengthOfGObj_Pos(void)
{
    WpNode *p = &D_004CAE8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0) return p;
        } while (p != end);
    }
    return 0;
}

WpNode *WayLengthOfGObj_GObj(WpNode *p)
{
    WpNode *end = &D_004CC1A4;
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
    WpNode *p = &D_004CAE8C;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0) return p;
        } while (p != end);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayBridgeAll_next);

