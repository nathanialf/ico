#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", actClipCollisionCore);
extern int D_0063B754;
extern void func_001CDD30();
int CreateClipCollisionManagerGObj(void) {
    int v = CreateGObjByFuncSet(0, 0, 0, 0, func_001CDD30, 0, 0);
    D_0063B754 = v;
    return v;
}
extern void actClipCollisionCore(volatile unsigned int self);
extern void *actCreateSubThreadGOppArg(void *entry, int arg);

void *RequestClipCollision(int *a0) {
    void *t = actCreateSubThreadGOppArg(actClipCollisionCore, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}
extern void _ACTWait(int a0);

void func_001CDD30(void)
{
    for (;;) {
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", func_001CDD48);
