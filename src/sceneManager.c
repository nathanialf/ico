#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", GetRealModelId);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", InitStageLight);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", initSceneGObj);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", initParentLink);
extern void ExtractWayData();

void initWayData(int a0, int a1, int a2, int a3)
{
    ExtractWayData(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", InitSceneObjects);
extern char D_002C1270[];
extern void iosOmSendMail(int *a0, int a1, int *a2);
extern int *isysGObjGetExist_begin(int a0);
extern int *isysGObjGetExist_next(int *a0);

int HotInitSceneObjects(int a0) {
    int *node = isysGObjGetExist_begin(a0);
    if (node != 0) {
        do {
            int idx = node[3];
            if (idx >= 0) {
                char *e = D_002C1270 + idx * 0x64;
                void (*fn)(int *);
                if (*(int *)(e + 0x60) != 0) {
                    iosOmSendMail(node, 0x2F, node);
                }
                fn = *(void (**)(int *))(e + 0x54);
                if (fn != 0) {
                    fn(node);
                }
            }
            node = isysGObjGetExist_next(node);
        } while (node != 0);
    }
    return 1;
}
extern int D_0063C414;
extern int D_0063C418;
extern int D_0063C41C;

void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0)
{
    if (a2 >= 0) {
        D_0063C414 = a2;
    }
    if (a3 >= 0) {
        D_0063C418 = a3;
    }
    if (t0 >= 0) {
        D_0063C41C = t0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", CreateLayoutedGObj);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", MoveNextStage_Set);
void test_nextstage_firstwalk_set(int unused, int a, int b, int c) {
    D_0063C414 = a;
    D_0063C418 = b;
    D_0063C41C = c;
}
extern int D_00639D30;

int GetStageStartInfo(int a0, int a1, int a2, int *p, int *q, int *r) {
    int ret = 1;
    if (D_00639D30 == 0) {
        *r = 1;
        *q = 1;
        *p = 1;
    } else {
        *p = D_0063C414;
        *q = D_0063C418;
        *r = D_0063C41C;
        if (*q == 0) ret = 0;
        if (*p == 0) *p = 1;
        if (*q == 0) *q = 1;
        if (*r == 0) *r = 1;
    }
    *q = 0x32;
    return ret;
}
extern char D_0063B640;
extern int D_0063B644;

void MoveNextStage_Clear(void) {
    D_0063B640 = 0;
    D_0063B644 = -1;
}
