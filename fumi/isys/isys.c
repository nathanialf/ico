#include "common.h"

void isysInitialize(int *a0, int a1) {
    int *node = (int *)a0[0xB];
    while (node) {
        if (node[7] == a1) {
            node[6] = 0;
        }
        node = (int *)node[2];
    }
}

void func_0013F360(int *a0) {
    a0[6] = 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/isys", func_0013F370);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/isys", func_0013F3A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/isys", func_0013F3E0);

extern int isysGObjProcessAlloc(int a0, int a1, int a2, int a3, int a4, int a5);

int func_0013F418(int a0, int a1, int a2, int a3, int a4) {
    return isysGObjProcessAlloc(a0, 0, a1, a2 & 0xFF, a3, a4);
}

void func_0013F448(int *a0, int a1) {
    int *node = (int *)a0[0xB];
    while (node) {
        if (node[7] == a1) {
            node[6] = 1;
        }
        node = (int *)node[2];
    }
}

void func_0013F478(int *p) {
    *p = 0;
}

extern void func_0013F488(void);

void func_0013F480(void) {
    func_0013F488();
}

extern void isysGObjKindTableInit(int a0);
extern void isysGObjProcRemove(int a0);
extern void isysGObjProcessInit(void);
extern void isysGObjLinkCameraDLAfterGObj(void);

void func_0013F488(void) {
    isysGObjKindTableInit(0x140);
    isysGObjProcRemove(0x500);
    isysGObjProcessInit();
    isysGObjLinkCameraDLAfterGObj();
}
