#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", actClipCollisionCore);
INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", CreateClipCollisionManagerGObj);
extern void actClipCollisionCore(volatile unsigned int self);
extern void *actCreateSubThreadGOppArg(void *entry, int arg);

void *RequestClipCollision(int *a0) {
    void *t = actCreateSubThreadGOppArg(actClipCollisionCore, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}
INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", func_001CDD30);
