#include "common.h"

extern char D_0028F8F0[];
extern int D_00639EA4;
extern void GetRootPosition(void *a0, int a1);
extern int GetSkeltonFocusNode(int a0, int a1);
extern void GetWormCaptureVector__pn(void *a0, int a1, int a2, float f12) __asm__("GetWormCaptureVector");
extern void GetWormRoute(int a0, int a1);
extern void SetDirectRootPosition(int a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1);
extern void disp(void);
typedef struct {
    float x, y, z, w;
} WormVec;
typedef struct {
    int num;
    int pad[19];
} WormSeg;
typedef struct {
    WormVec *pos;
    int pad[103];
} WormPnt;
typedef struct {
    WormSeg *seg;
    int nseg;
    WormPnt *pnt;
} WormRoute;
typedef struct {
    WormRoute *route;
    WormVec **src;
    float reduce;
    float ratio;
} WormWork;
extern void CopyVector(void *dst, void *src);
extern void sceVu0InterVectorXYZ(void *v0, void *v1, void *v2, float t);
/* prototypes: their order is the inline tail's emission order */
void SetDirectWormTargetPos(int act, void *pos);
void SetWormReduceRatio(int a0, float f12);
void TraceWormRoute(int act, float t);
INCLUDE_ASM("asm/nonmatchings/src/worm", outerProcess);
INCLUDE_ASM("asm/nonmatchings/src/worm", simulate);
ASM_LIT4_SLOT(D_00639710, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/worm", getAnimation);
ASM_LIT4_SLOT(D_00639714, 0.02f);
INCLUDE_ASM("asm/nonmatchings/src/worm", disp);
inline void SetWormReduceRatio(int a0, float f12) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) = f12;
}
INCLUDE_ASM("asm/nonmatchings/src/worm", GetWormRoute);
inline void SetDirectWormTargetPos(int act, void *pos) {
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i;

    for (i = 0; i < r->nseg; i++) {
        int n = r->seg[i].num;
        CopyVector(&r->pnt[i].pos[n - 1], pos);
        r->pnt[i].pos[n - 1].w = 1.0f;
    }
    w->ratio = 1.0f;
}
inline void TraceWormRoute(int act, float t) {
    WormWork *w = *(WormWork **)(*(int *)(act + 0x15C) + 0x830);
    WormRoute *r = w->route;
    int i, j;
    float step = t * 8.99999f;

    for (i = 0; i < r->nseg; i++) {
        int n = r->seg[i].num;
        for (j = 1; j < n; j++) {
            float f = step * (float)j / (float)(n - 1);
            sceVu0InterVectorXYZ(&r->pnt[i].pos[j],
                                 &w->src[i][(int)f + 1],
                                 &w->src[i][(int)f],
                                 f - (float)(int)f);
            r->pnt[i].pos[j].w = 1.0f;
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/worm", InitWormGeo);
void GetWormCaptureVector(void *a0, char *a1, float f12) {
    sceVu0SubVector(a0, (void *)(*(int *)(a1 + 0x15C) + 0x50));
    sceVu0Normalize(a0, a0);
    sceVu0ScaleVector(a0, a0, f12);
}
ASM_LIT4_SLOT(D_00639718, 0.05f);
ASM_LIT4_SLOT(D_0063971C, 8.99999f);
INCLUDE_ASM("asm/nonmatchings/src/worm", WormGeo);
void WormDL(void) {
    disp();
}
