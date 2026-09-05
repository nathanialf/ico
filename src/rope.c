#include "common.h"

#include "ico/types.h"

extern void ropeGeo(void *o);
extern void GetRootPosition(void *dst, void *src);
extern float GetChainCollision(void *a0, void *a1, float w);
extern void *D_00639EA4;
INCLUDE_ASM("asm/nonmatchings/src/rope", InitRopeGeo);
inline int CheckRopeUpperWallClimbable(int a0, char *a1) {
    return *(int *)(*(char **)(*(char **)(a1 + 0x15C) + 0x830) + 4);
}
void SetRopeFixPoint(char *a0, void *a1) {
    CopyVector(**(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) + 0x20, a1);
}
INCLUDE_ASM("asm/nonmatchings/src/rope", HoldRope);
inline void ReleaseRope(void) {}
INCLUDE_ASM("asm/nonmatchings/src/rope", ropeGeo);
/* The listing inlines rope.c:215-221 into RopeGeo: the chain-length update
   is a static helper defined above it (its name is not recoverable). */
/* prototypes: their order is the inline tail's emission order */
int CheckRopeUpperWallClimbable(int a0, char *a1);
void ReleaseRope(void);
void RopeGeo(void *a0);
static inline void ropeChainCollision(void *a0)
{
    void *g = D_00639EA4;
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    float m[4];
    float w;

    GetRootPosition(m, g);
    w = GetChainCollision(obj[0], m, 200.0f);
    do {
        if (0.0f < w) {
            *(float *)((char *)*(void **)((char *)g + 0x15C) + 0x618) = w;
        }
    } while (0);
}
inline void RopeGeo(void *a0)
{
    ropeGeo(a0);
    ropeChainCollision(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/rope", RopeDL);
