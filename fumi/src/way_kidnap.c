#include "common.h"

typedef struct Nd {
    int f0; int _4;
    struct Nd *f8; struct Nd *fC;
    int f10; char _14[0xC];
    int f20; char _24[0x4];
    int f28; char _2C[0x14];
} Nd;
typedef struct Head { char _0[8]; Nd *f8; Nd *fC; int f10; int f14; char _18[0x1C]; } Head;

extern char D_004C6FF0[];
extern Nd D_004C7CF0[];
extern void sceVu0CopyVector(int *, int);

int add_wp_pos(int a0)
{
    Nd *node = &D_004C7CF0[0];
    int i;
    for (i = 0; i < 0xD7; i++) {
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

int AddWayPoint(int a0, int a1)
{
    Head *ch = (Head *)&D_004C6FF0[a0 * 0x34];
    Nd *node = &D_004C7CF0[a1];
    if (ch->f8 == 0) {
        ch->f8 = node;
        ch->fC = node;
    } else {
        Nd *tail = ch->fC;
        ch->fC = node;
        tail->fC = node;
        node->f8 = tail;
        node->fC = 0;
    }
    node->f20 = a0;
    ch->f10++;
    return 0;
}

int AddWayPointTop(int a0, int a1)
{
    int *ch = (int *)&D_004C6FF0[a0 * 0x34];
    Nd *node = &D_004C7CF0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}

typedef struct WayNode { char _0[8]; struct WayNode *prev; struct WayNode *next; char _10[0x30]; } WayNode;

int InsertWayPointAfter(int a0, int a1, int a2) {
    WayNode *A = &D_004C7CF0[a1];
    WayNode *B = &D_004C7CF0[a2];
    WayNode *old = A->next;
    A->next = B;
    B->prev = A;
    B->next = old;
    old->prev = B;
    return 0;
}

int NearestEnemyFromGirl(int a0)
{
    Nd *node = &D_004C7CF0[a0];
    Nd *prev = node->f8;
    Head *head = (Head *)&D_004C6FF0[node->f20 * 0x34];
    Nd *next = node->fC;
    int count = head->f10;

    if (count < 4) {
        head->f14 = 0;
    }
    if (head->f14 != 0) {
        if (node == head->f8) {
            head->f8 = next;
            head->f10 = count - 1;
            node->f0 = 0;
            return 0;
        }
        if (node == head->fC) {
            head->fC = prev;
            head->f10 = count - 1;
            node->f0 = 0;
            return 0;
        }
    }
    if (prev != 0)
        prev->fC = next;
    else if (next != 0)
        head->f8 = next;
    if (next != 0)
        next->f8 = prev;
    else if (prev != 0)
        head->fC = prev;
    if (prev == 0 && next == 0) {
        head->f8 = 0;
        head->fC = 0;
    }
    node->f0 = 0;
    head->f10 = count - 1;
    return 0;
}

typedef struct WpNode { int f0; char _4[0x14]; int f18; char _1C[0x0C]; int f28; char _2C[0x08]; } WpNode;
extern WpNode D_004C6FBC;

WpNode *NumOfWpPos(void)
{
    WpNode *p = &D_004C6FBC;
    WpNode *end = p + 64;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0) return p;
        } while (p != end);
    }
    return 0;
}

extern WpNode D_004C7CBC;

WpNode *CopyWpPos(WpNode *p)
{
    WpNode *end = &D_004C7CBC;
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
    WpNode *p = &D_004C6FBC;
    WpNode *end = p + 64;
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
    WpNode *end = &D_004C7CBC;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0 && q->f28 != 0) return q;
        } while (q != end);
    }
    return 0;
}

WpNode *WayPointWithRangeFromGObj(void)
{
    WpNode *p = &D_004C6FBC;
    WpNode *end = p + 64;
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
    WpNode *end = &D_004C7CBC;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0) return q;
        } while (q != end);
    }
    return 0;
}
