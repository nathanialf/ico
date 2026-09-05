#include "common.h"

extern int CreateGObjByFuncSet();
extern int D_0063BC50;
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
extern int _FUNC_GetWay_begin();
extern void _ACTWait(int a0);
/* prototypes: their order is the inline tail's emission order */
void *RequestGetWayBegin(int *a0);
static void actWaySystemCore(volatile unsigned int self);
static void thStart(void);
static inline void actWaySystemCore(volatile unsigned int self)
{
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = _FUNC_GetWay_begin((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}
inline void *RequestGetWayBegin(int *a0) {
    void *t = actCreateSubThreadGOppArg(actWaySystemCore, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}
static inline void thStart(void) {
    for (;;) {
        _ACTWait(1);
    }
}
int CreateWaySystemManagerGObj(void) {
    int v = CreateGObjByFuncSet(0, 0, 0, 0, (int)&thStart, 0, 0);
    D_0063BC50 = v;
    return v;
}
