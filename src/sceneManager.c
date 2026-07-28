#include "common.h"







extern int D_00633EC4;
extern int D_00633EC8;
extern int D_00633ECC;
extern void group_select();
extern int D_0063315C;
extern int D_00633164;
extern int D_00633158;
extern char D_002E81F0[];
void GetRealModelId(int a0, int a1)
{
    int *p = (int *)(D_002E81F0 + a0 * 0x6C);
    p[0x68 / 4] = (p[0x68 / 4] & ~1) | (a1 & 1);
}

int InitStageLight(void) {
    return D_00633158;
}

void initSceneGObj(int val) {
    D_00633164 = val;
}

void initParentLink(int val) {
    D_0063315C = val;
}

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", initWayData);

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", InitSceneObjects);

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", HotInitSceneObjects);

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", ChangeStageStartInfo);

void CreateLayoutedGObj(int a0, int a1, int a2, int a3)
{
    group_select(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", MoveNextStage_Set);

extern char D_002A31B8[];
extern int *func_0013ECF8(int *a0);
extern void iosOmBeforeFuncStandard(int *a0, int a1, int *a2);
extern int *isysGObjRemoveObjDL(int a0);

int test_nextstage_firstwalk_set(int a0) {
    int *node = isysGObjRemoveObjDL(a0);
    if (node != 0) {
        do {
            int idx = node[3];
            if (idx >= 0) {
                char *e = D_002A31B8 + idx * 0x64;
                void (*fn)(int *);
                if (*(int *)(e + 0x60) != 0) {
                    iosOmBeforeFuncStandard(node, 0x2F, node);
                }
                fn = *(void (**)(int *))(e + 0x54);
                if (fn != 0) {
                    fn(node);
                }
            }
            node = func_0013ECF8(node);
        } while (node != 0);
    }
    return 1;
}

void GetStageStartInfo(int a0, int a1, int a2, int a3, int t0)
{
    if (a2 >= 0) {
        D_00633EC4 = a2;
    }
    if (a3 >= 0) {
        D_00633EC8 = a3;
    }
    if (t0 >= 0) {
        D_00633ECC = t0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", MoveNextStage_Clear);

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", func_001B80B0);

