#include "common.h"

typedef struct { char _0[0x68]; int f_68; } RealModel;
extern RealModel D_002E34F0[];

void GetRealModelId(int a0, int a1) {
    RealModel *m = &D_002E34F0[a0];
    m->f_68 = (m->f_68 & ~1) | (a1 & 1);
}

extern int D_0062B418;

int InitStageLight(void) {
    return D_0062B418;
}

extern int D_0062B424;

void initSceneGObj(int a0) {
    D_0062B424 = a0;
}

extern int D_0062B41C;

void initParentLink(int a0) {
    D_0062B41C = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", initWayData);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", InitSceneObjects);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", HotInitSceneObjects);

extern void debug_StdPrintfDummy(char *a0, void *a1);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void *isysGObjAddHead(int a0);
extern char D_0060FC98[];
extern char D_0060FCE0[];
extern char D_0060FCF8[];
extern char D_0060FD08[];
extern char D_0062D2D0[];

typedef struct {
    char pad0[0x44];
    unsigned short f44;
    unsigned char f46;
    char pad1[0x4C - 0x47];
} StageA;

typedef struct {
    char pad0[0x44];
    int f44;
    char pad1[0x64 - 0x48];
} StageB;

extern StageA D_002A0A90_arr[] __asm__("D_002A0A90");
extern StageB D_0029F060_arr[] __asm__("D_0029F060");

void ChangeStageStartInfo(int a0) {
    StageA *info = &D_002A0A90_arr[a0];
    unsigned char modelId = info->f46;
    StageB *m = &D_0029F060_arr[modelId];
    unsigned short f44 = info->f44;
    void *g1;
    void *g2;

    if (m->f44 != 0 && f44 != 0 && modelId != 4) {
        g1 = isysGObjAddHead(a0);
        g2 = isysGObjAddHead(f44);
        if (g2 != 0) {
            if (g2 == g1) {
                debug_StdPrintfDummy(D_0060FC98, m);
                func_001AAD00(D_0060FCE0, 0x1E7);
                __assert(D_0060FCE0, 0x1E7, D_0062D2D0);
            }
            debug_StdPrintfDummy(D_0060FCF8, m);
            *(int *)(*(int *)((char *)g1 + 0x15C)) = (int)g2;
            *(int *)(*(int *)((char *)g1 + 0x15C) + 4) = 0;
        } else {
            debug_StdPrintfDummy(D_0060FD08, m);
            func_001AAD00(D_0060FCE0, 0x1F0);
            __assert(D_0060FCE0, 0x1F0, D_0062D2D0);
        }
    }
}



extern void group_select(int a0);

void CreateLayoutedGObj(int a0) {
    group_select(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", MoveNextStage_Set);

extern int *isysGObjGetExist_begin(int a0);
extern int *isysGObjGetExist_next(int *a0);
extern void iosOmSendMail(int *a0, int a1, int *a2);
extern char D_0029F060[];

int test_nextstage_firstwalk_set(int a0) {
    int *node = isysGObjGetExist_begin(a0);
    if (node != 0) {
        do {
            int idx = node[3];
            if (idx >= 0) {
                char *e = D_0029F060 + idx * 0x64;
                void (*fn)(int *);
                if (*(int *)(e + 0x60) != 0) {
                    iosOmSendMail(node, 0x2E, node);
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

extern int D_0062C1B4, D_0062C1B8, D_0062C1BC;

void GetStageStartInfo(int a0, int a1, int a2, int a3, int a4) {
    if (a2 >= 0) D_0062C1B4 = a2;
    if (a3 >= 0) D_0062C1B8 = a3;
    if (a4 >= 0) D_0062C1BC = a4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", MoveNextStage_Clear);

extern float D_00700750[];
extern float D_00700760[];
extern int D_0062B44C;
extern char D_0062B448;

void func_001B55D8(float *a0, float *a1, int a2, int a3, int a4, int a5) {
    D_00700750[0] = a0[0];
    D_00700750[1] = a0[1];
    D_00700750[2] = a0[2];
    D_0062C1B4 = a2;
    D_0062C1B8 = a3;
    D_0062C1BC = a4;
    D_0062B44C = a5;
    D_00700760[0] = a1[0];
    D_00700760[1] = a1[1];
    D_00700760[2] = a1[2];
    D_0062B448 = 1;
}


/* recovered struct shapes */
typedef struct {
    short              f_A0;  /* 0xA0 */
    short              f_A2;  /* 0xA2 */
    short              f_A6;  /* 0xA6 */
    unsigned int       f_108;  /* 0x108 */
    unsigned int       f_10C;  /* 0x10C */
    unsigned int       f_110;  /* 0x110 */
    unsigned int       f_114;  /* 0x114 */
    unsigned int       f_118;  /* 0x118 */
    unsigned int       f_128;  /* 0x128 */
    unsigned int       f_12C;  /* 0x12C */
    unsigned int       f_130;  /* 0x130 */
    unsigned int       f_134;  /* 0x134 */
    unsigned int       f_138;  /* 0x138 */
    unsigned int       f_13C;  /* 0x13C */
    unsigned int       f_140;  /* 0x140 */
    unsigned int       f_144;  /* 0x144 */
    unsigned int       f_14C;  /* 0x14C */
    unsigned int       f_150;  /* 0x150 */
    unsigned int       f_154;  /* 0x154 */
    unsigned int       f_168;  /* 0x168 */
    unsigned int       f_16C;  /* 0x16C */
    unsigned int       f_188;  /* 0x188 */
    unsigned short     f_18A;  /* 0x18A */
    unsigned int       f_18C;  /* 0x18C */
} S_005EBC48;  /* stride 0x190 */

typedef struct {
    unsigned int       f_30;  /* 0x30 */
    unsigned int       f_3C;  /* 0x3C */
    unsigned int       f_44;  /* 0x44 */
    unsigned int       f_58;  /* 0x58 */
} S_0029F060;  /* stride 0x64 */

typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
} S_00617BB0;  /* stride 0x28 */

/* end struct shapes */
