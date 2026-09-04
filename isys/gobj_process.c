#include "common.h"

/* header prototypes (order fixes the inline tail) */
void isysGObjProcessAlloc(unsigned int a0);
int isysGObjProcAdd(int a0, int a1, int a2, int a3);
int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4);
int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3);
void isysGObjProcPause(char *self);
void isysGObjProcPauseAll(int *p);
void isysGObjProcPausePtr(void *a0, int a1);
void isysGObjProcActive(char *self);
void isysGObjProcActiveAll(void *a0);
void isysGObjProcRemoveAll(void *a0);
void isysGObjProcThreadSleep(int a0);
int isysGObjProcAddSGOppArg(int a, int b, int c, int d, int e);
void isysGObjProcActivePtr(void *a0, int a1);
void free_gobj_process_resource(char *self);
extern void isysGObjProcessAlloc(unsigned int a0);
extern void cut_gobj_process_link(int a0);
extern int iosThreadDestroy(int a0);
extern char D_00551FF0[];
extern int D_0063A430;
extern char *D_0063C1B0;
extern int D_0063C1B4;
extern int iosMallocDebug(int a0, int a1, const char *fmt, int line);
extern int isysGObjProcAdd_(int a0, int a1, int a2, int a3, int a4, int a5);
extern void iosThreadStop(int a0);
extern int isysGObjProcAdd___pn() __asm__("isysGObjProcAdd_");
void isysGObjProcessInit(unsigned int a0) {
    isysGObjProcessAlloc(a0);
}
inline void isysGObjProcessAlloc(unsigned int a0) {
    int ret = iosMallocDebug(D_0063A430, a0 * 0x94, D_00551FF0, 0x49);
    unsigned int i;
    D_0063C1B4 = a0;
    D_0063C1B0 = (char *)ret;
    for (i = 0; i < a0; i++) {
        *(int *)(D_0063C1B0 + i * 0x94) = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAdd_);
inline int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3) {
    return isysGObjProcAdd_(a0, 0, a1, a2 & 0xFF, a3, 0x1800);
}
inline int isysGObjProcAdd(int a0, int a1, int a2, int a3) {
    return isysGObjProcAdd_(a0, a0, a1, a2 & 0xFF, a3, 0x1800);
}
inline int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4) {
    return isysGObjProcAdd_(a0, a0, a1, a2 & 0xFF, a3, a4);
}
inline int isysGObjProcAddSGOppArg(int a, int b, int c, int d, int e)
{
    return isysGObjProcAdd___pn(a, 0, b, c & 0xFF, d, e);
}
inline void isysGObjProcPause(char *self) {
    *(int *)(self + 0x18) = 0;
}
inline void isysGObjProcPauseAll(int *p)
{
    int *cur = (int *)p[0x2C/4];
    if (cur != 0) {
        do {
            cur[0x18/4] = 0;
            cur = (int *)cur[0x8/4];
        } while (cur != 0);
    }
}
inline void isysGObjProcPausePtr(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 0;
        }
        p = *(int **)((char *)p + 0x8);
    }
}
inline void isysGObjProcActive(char *self) {
    *(int *)(self + 0x18) = 1;
}
inline void isysGObjProcActiveAll(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        *(int *)((char *)p + 0x18) = 1;
        p = *(int **)((char *)p + 0x8);
    }
}
inline void isysGObjProcActivePtr(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 1;
        }
        p = *(int **)((char *)p + 0x8);
    }
}
inline void free_gobj_process_resource(char *self) {
    *(int *)(self + 0x0) = 0;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", cut_gobj_process_link);
void isysGObjProcRemove(int *a0)
{
    int v0;
    cut_gobj_process_link((int)a0);
    v0 = a0[4];
    a0[0] = 0;
    if (v0 != 0) {
        return;
    }
    return iosThreadDestroy((int)a0 + 0x24);
}
inline void isysGObjProcRemoveAll(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x2C);
    while (p != 0) {
        isysGObjProcRemove(p);
        p = *(void **)((char *)p + 0x8);
    }
}
inline void isysGObjProcThreadSleep(int a0)
{
    while (a0 != 0) {
        iosThreadStop(0);
        a0--;
    }
}
