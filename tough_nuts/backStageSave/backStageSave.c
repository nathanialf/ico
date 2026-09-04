#include "common.h"

extern int D_0062AB2C;

void backStageProcessOutStage(int a0) {
    D_0062AB2C = a0;
}

extern int D_00271240[];
extern int D_004AEE28[];
extern int D_004B1D90[];
extern void gamesysMemorySave(int *, int *, int);

void CheckPoint(void) {
    if (D_00271240[2] != 0) {
        gamesysMemorySave(D_004AEE28, D_004B1D90, 0);
        D_00271240[3] = 1;
    }
}

extern int D_0062AB18;
extern int D_0062AB24;
extern int D_0062AB34;

void routeSetPos(void) {
    D_0062AB18 = 0;
    D_0062AB24 = 0;
    D_0062AB34 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageProcessInStage);

extern int func_00178DB0(int);
extern void sceVu0CopyVector(void *, void *);
extern void memset(void *, int, int);
extern int disp_memory_partition_bar();
extern void SetInfoSpKidnapGenerator(void *);
extern void _RotGV(void *);
extern void debug_StdPrintfDummy(char *);
extern int func_0018A0E8(void);
extern void func_00151840(void);
extern void func_0018E670(int);
extern void RequestStageChangeKidnapEnd(int, int);
extern int D_0062B23C;
extern int D_0062B40C;
extern int D_00629C90;
extern int D_0062C114;
extern int D_0062C118;
extern int D_0062C11C;
extern int D_0062C134;
extern int D_0062C138;
extern int D_0062C120;
extern char D_0060B368[];
extern unsigned char D_004AF010[];
extern unsigned char D_002A0A90[];
extern float D_006DE100[];

void backStageSave(void) {
    unsigned char *obj = D_004AF010;
    unsigned char *e;

    D_0062B23C = 0;
    if (func_00178DB0(0x164) != 0) {
        return;
    }
    if (D_0062B40C != 0x32) {
        return;
    }
    if (D_00629C90 == *(unsigned short *)(obj + 0x44)) {
        return;
    }
    if (D_0062C114 == 1) {
        if (D_0062C118-- < 0) {
            if (D_0062C138 != 0) {
                float *tbl = (float *)(D_002A0A90 + 0x3862C);
                struct { float a, b, c, d; } q;
                float w[4];
                w[0] = D_006DE100[0];
                w[1] = D_006DE100[1] - 10.0f;
                w[2] = D_006DE100[2];
                memset(&q, 0, 0x10);
                q.a = tbl[0];
                q.b = tbl[1];
                q.c = tbl[2];
                disp_memory_partition_bar(0xD57, 4, *(unsigned short *)(obj + 0x44),
                                          obj + 0x50, obj + 0x60, q);
                e = (unsigned char *)disp_memory_partition_bar(
                    0xD58, 0x21, *(unsigned short *)(obj + 0x44), w, &w[4]);
                D_0062C120 = (e - obj) >> 6;
                SetInfoSpKidnapGenerator(obj + 0x30);
                _RotGV(e + 0x30);
                if (e == 0 || obj == 0) {
                    debug_StdPrintfDummy(D_0060B368);
                    D_0062C114 = 1;
                } else {
                    *(int *)(e + 0x30) = 4;
                }
            } else {
                unsigned char *cap = obj + (D_0062C120 << 6);
                sceVu0CopyVector(cap + 0x10, obj + 0x50);
                *(int *)(cap + 0x30) = 4;
                D_0062C114 = 2;
            }
        }
    } else if (D_0062C114 == 2) {
        if (func_0018A0E8() != 4) {
            if (D_0062C134 == 0) {
                func_00151840();
                D_0062C134 = 1;
            }
            D_0062B23C = 1;
            if (D_0062C11C-- < 0) {
                unsigned char *cap = obj + (D_0062C120 << 6);
                int hp = *(unsigned short *)(obj + 0x44);
                func_0018E670(*(unsigned short *)(cap + 0x2));
                RequestStageChangeKidnapEnd(hp, (int)cap);
            }
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/backStage", backStageProcessInit);

extern int func_001AB750(void *, void *, int);
extern int gamesysMemoryHandlerRead(void *, void *, int);
extern int D_0062AB50;
extern int D_0062C114;
extern int D_0062C118;
extern int D_0062C11C;
extern int D_0062C120;
extern int D_0062C124;
extern int D_0062C128;
extern int D_0062C12C;
extern int D_0062C130;

void backStageDebugTimeZero(void *a0) {
    func_001AB750(a0, &D_0062AB50, 4);
    func_001AB750(a0, &D_0062C114, 4);
    func_001AB750(a0, &D_0062C118, 4);
    func_001AB750(a0, &D_0062C11C, 4);
    func_001AB750(a0, &D_0062C120, 4);
    func_001AB750(a0, &D_0062C124, 4);
    func_001AB750(a0, &D_0062C128, 4);
    func_001AB750(a0, &D_0062C12C, 4);
    func_001AB750(a0, &D_0062C130, 4);
}

void backStageTsuresariReturn(void *a0) {
    gamesysMemoryHandlerRead(a0, &D_0062AB50, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C114, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C118, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C11C, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C120, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C124, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C128, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C12C, 4);
    gamesysMemoryHandlerRead(a0, &D_0062C130, 4);
}

extern int D_0062AB50;
extern int D_0062C120;
extern int D_0062C114;
extern int D_0062C134;

void func_0019E5A8(void) {
    D_0062AB50 = 0;
    D_0062C120 = -1;
    D_0062C114 = 0;
    D_0062C134 = 0;
}
