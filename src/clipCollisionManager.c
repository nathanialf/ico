#include "common.h"

#include "ico/types.h"

/* clipCollisionManager.h prototype: the inline tail's emission order */
void *RequestClipCollision(int *a0);

extern int D_0063B754;
extern void actClipCollisionCore(volatile unsigned int self);
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
extern void _ACTWait(int a0);

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", actClipCollisionCore);

inline void *RequestClipCollision(int *a0) {
    void *t = actCreateSubThreadGOppArg(actClipCollisionCore, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}

/* listing line 72: the manager thread's idle body, handed to
   CreateGObjByFuncSet; a static inline forced out of line by its address */
static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}

int CreateClipCollisionManagerGObj(void) {
    int v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    D_0063B754 = v;
    return v;
}
