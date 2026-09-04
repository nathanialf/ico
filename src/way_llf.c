#include "common.h"

typedef struct { int w[13]; } WayRec;

typedef struct { int w[16]; } WayGroup_DW;

typedef struct WayGroup {
    int f0;
    char _4[0x14];
    int f18;
    char _1c[0xC];
    int f28;
    char _2c[0x8];
} WayGroup;



extern WayRec D_004CAEC0[];
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_0061B1B0[];
extern WayRec D_004CAE8C[];

void *InitWayPointSystem(void) {
    WayRec *p = D_004CAE8C;
    WayRec *end = D_004CAE8C + 94;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++; ; p++) {
        if (p->w[0] != 0 && p->w[6] != 0 && p->w[10] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}

extern WayGroup D_004CC1A4;

WayGroup *CreateWayGroup(WayGroup *a0) {
    WayGroup *p, *end = &D_004CC1A4;
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

typedef struct { int w[16]; } WayGroup_CT;
extern WayGroup_CT D_004CC1A0[];

void *WayPoint_begin(void) {
    WayGroup_CT *p = D_004CC1A0;
    WayGroup_CT *end = D_004CC1A0 + 275;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++;; p++) {
        if (p->w[0] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}

extern WayGroup_DW D_004D0660;

void *WayPoint_next(WayGroup_DW *a0) {
    WayGroup_DW *end = &D_004D0660;
    if (a0 == 0) goto ret0;
    if (a0 == end) goto ret0;
    for (a0++; ; a0++) {
        if (a0->w[0] != 0) return a0;
        if (a0 == end) break;
    }
ret0:
    return 0;
}


int WayPointList_begin(int a0) {
    return D_004CAEC0[a0].w[2];
}

int WayPointList_next(int *a0) {
    register int v __asm__("$4") = (int)a0;
    __asm__ (
        ".set noreorder\n\t"
        "daddu  $5, $4, $0\n\t"
        "lui    $2, %%hi(D_004CAEC0)\n\t"
        "lw     $3, 0x20($5)\n\t"
        "addiu  $4, $0, 0x34\n\t"
        "addiu  $2, $2, %%lo(D_004CAEC0)\n\t"
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

int waypoint_bidirectional_list(int *self, int which) {
    if (self == 0) {
        return 0;
    }
    debug_StdPrintfDummy(D_0061B1B0, self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}

void SetWayGroupActive(int a0, int a1) {
    D_004CAEC0[a0].w[10] = a1;
}

int CheckWayGroupActive(int idx)
{
    return D_004CAEC0[idx].w[10] != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_llf", DeleteWayPoint);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", WayGroup_begin);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", WayGroup_next);

extern char D_004D06A0[];
extern char D_0061B640[];
extern char D_0061B650[];
extern int D_00632CBC;
extern int D_00633874;
extern char D_00633880[];
extern int D_00633890;
extern int D_0071257C[];
extern int InsertWayPointAfter(int a0, int a1, int a2);
extern int CreateWayPoint(void *a0);
extern void *nearest_waypoint_of_all_except_group(void *a0);
extern void traceLine();

int WayBridge_begin(void) {
    WayRec *entry = &D_004CAEC0[D_00633874];
    int f;

    if (D_00632CBC & 1) {
        traceLine(0x12, 0x36, 0xFF000000, D_0061B640);
        if (D_00632CBC & 1) {
            traceLine(0x1A, 0x42, 0xFF808000, D_00633880, entry->w[4]);
        }
    }
    D_00633890 = 1;
    f = D_0071257C[0];
    if (!(f & 0x20)) {
        if (f & 0x40) {
            D_00633890 = 0;
            return -1;
        }
        return 0;
    }
    {
        void *res = nearest_waypoint_of_all_except_group(D_004D06A0);
        if (*(int *) ((char *) res + 0xC) == 0) {
            return 0;
        }
        {
            int n = CreateWayPoint(D_004D06A0);
            InsertWayPointAfter(D_00633874, *(int *) ((char *) res + 4), n);
            entry->w[4] = entry->w[4] + 1;
            debug_StdPrintfDummy(D_0061B650, n);
        }
    }
    return 0;
}

