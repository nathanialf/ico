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

void func_0013F370(int a0) {
    int p = *(int *)(a0 + 0x2C);
    while (p != 0) {
        *(int *)(p + 0x18) = 1;
        p = *(int *)(p + 0x8);
    }
}

extern void isysGObjProcAddS(void *a0);

void isysGObjProcRemoveAll(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x2C);
    while (p != 0) {
        isysGObjProcAddS(p);
        p = *(void **)((char *)p + 0x8);
    }
}

extern void iosThreadCancelWakeup(int a0);

void isysGObjProcThreadSleep(int a0)
{
    while (a0 != 0) {
        iosThreadCancelWakeup(0);
        a0--;
    }
}

extern int isysGObjProcessAlloc(int a0, int a1, int a2, int a3, int a4, int a5);

int isysGObjProcAddSGOppArg(int a0, int a1, int a2, int a3, int a4) {
    return isysGObjProcessAlloc(a0, 0, a1, a2 & 0xFF, a3, a4);
}

void isysGObjProcActivePtr(int *a0, int a1) {
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
