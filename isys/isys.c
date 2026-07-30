#include "common.h"





extern void isysGObjLinkCameraDLAfterGObj(void);
extern void isysGObjKindTableInit();
extern void isysGObjProcRemove();
extern void isysGObjProcessInit();
extern int isysGObjProcessAlloc();
extern void iosThreadCancelWakeup(int a0);
extern void isysGObjProcAddS(int *a0);
void isysInitialize(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 0;
        }
        p = *(int **)((char *)p + 0x8);
    }
}

void func_0013F878(char *self) {
    *(int *)(self + 0x18) = 1;
}

void func_0013F888(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        *(int *)((char *)p + 0x18) = 1;
        p = *(int **)((char *)p + 0x8);
    }
}

void func_0013F8C0(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x2C);
    while (p != 0) {
        isysGObjProcAddS(p);
        p = *(void **)((char *)p + 0x8);
    }
}

void func_0013F8F8(int a0)
{
    while (a0 != 0) {
        iosThreadCancelWakeup(0);
        a0--;
    }
}

int func_0013F930(int a, int b, int c, int d, int e)
{
    return isysGObjProcessAlloc(a, 0, b, c & 0xFF, d, e);
}

void func_0013F960(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 1;
        }
        p = *(int **)((char *)p + 0x8);
    }
}

void func_0013F990(char *self) {
    *(int *)(self + 0x0) = 0;
}

extern void func_0013F9A0(void);

void func_0013F998(void)
{
    func_0013F9A0();
}

void func_0013F9A0(void)
{
    isysGObjKindTableInit(0x140);
    isysGObjProcRemove(0x500);
    isysGObjProcessInit();
    return isysGObjLinkCameraDLAfterGObj();
}

