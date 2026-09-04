#include "common.h"

int initGeometryState(volatile int *a0) {
    return a0[3] != a0[4] ? a0[0] + a0[2] * 0x151800 : 0;
}

int initMatrixDObj(volatile int *self) {
    if (self[3] != 0) {
        int e = self[2] - self[3];
        int d = self[4];
        return self[1] + (e + d) % d * 0xA0A40;
    }
    return 0;
}

void voBufDecCount(void *a0) {
    if (*(volatile int *)((char *)a0 + 0xC) > 0) {
        *(volatile int *)((char *)a0 + 0xC) = *(volatile int *)((char *)a0 + 0xC) - 1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", initInitialInverseMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", initPolygonState);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", CSVSYSTEM_InitDObj);

extern int D_0062A310;
extern int iosFree(int a0, int a1, int *a2, int a3);
extern void SetDirectRootPositionNoFittingWithNodePoint(int v, int *self);

extern char D_0060B090[];

void FreeDObj(int *self) {
    int v = iosFree(D_0062A310, self[0x88/4] << 6, (int*)D_0060B090, 0x14C);
    self[0x90/4] = v;
    SetDirectRootPositionNoFittingWithNodePoint(v, self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", LinkParentOfDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", UnlinkParentOfDObj);

void func_0019CAA0(void) {
}

typedef struct { long long x; } __attribute__((packed, aligned(4))) PackedLL_19CAF0;
extern void GetRootMatrixRotOffsetByDObj();

void func_0019CAA8(void *a0, PackedLL_19CAF0 *a1) {
    PackedLL_19CAF0 *p;
    GetRootMatrixRotOffsetByDObj(a0, a1);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = *a1;
}

extern PackedLL_19CAF0 D_0062A6A0;
extern void SetRootMatrixRotOffsetByDObj(void *a0);
void func_0019CAF0(void *a0) {
    PackedLL_19CAF0 *p;
    SetRootMatrixRotOffsetByDObj(a0);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = D_0062A6A0;
}

extern void debug_StdPrintfDummy();
extern void func_0013E828(int a0, int a1);
extern int func_0013D4B0(int a0);
extern void cut_gobj_link(void);
extern void sceGsSyncPath(int a0, int a1);
extern void func_001025B8(void);
extern void avoid_obstacle2(void *a0);
extern void iosMallocClearPartition(int a0);
extern void func_001D2180(void);
extern char D_00271240[], D_00286840[];
extern char D_0060B128[], D_0060B140[], D_0060B158[], D_0062C990[];
extern int D_00629CA0, D_00629D20, D_00629DE4, D_00629DE8;
extern int D_0062A308, D_0062A310, D_0062A318, D_0062A324, D_0062A330, D_0062A52C;

typedef struct { char _0[0x150]; void (*fp)(void); char _154[0x190 - 0x154]; } Ent5EBC48;
extern Ent5EBC48 D_005EBC48[];

void func_0019CB28(void) {
    int i;
    char *base;
    void (*fp)(void);
    debug_StdPrintfDummy(D_0060B128);
    D_00629D20 = 0;
    for (i = 0; i < 8; i++) {
        func_0013E828(i, 0);
    }
    fp = D_005EBC48[D_00629CA0].fp;
    if (fp != 0) {
        fp();
    }
    func_0013D4B0(0);
    cut_gobj_link();
    sceGsSyncPath(0, 0);
    func_001025B8();
    base = D_00271240;
    if (*(int *)(base + 0x28) != 0) {
        avoid_obstacle2(D_00286840);
        *(int *)(base + 0x28) = 0;
    }
    if (D_0062A52C == 0) {
        debug_StdPrintfDummy(D_0060B140);
        iosMallocClearPartition(D_0062A330);
    } else {
        debug_StdPrintfDummy(D_0060B158);
    }
    iosMallocClearPartition(D_0062A324);
    iosMallocClearPartition(D_0062A310);
    iosMallocClearPartition(D_0062A318);
    iosMallocClearPartition(D_0062A308);
    func_001D2180();
    debug_StdPrintfDummy(D_0062C990);
    func_001025B8();
    D_00629DE8 = 0;
    D_00629DE4 = 0;
}

