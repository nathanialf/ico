#include "common.h"

extern void ExtractWayData();
extern char D_002C1270[];
extern void iosOmSendMail(int *a0, int a1, int *a2);
extern int *isysGObjGetExist_begin(int a0);
extern int *isysGObjGetExist_next(int *a0);
extern int D_0063C414;
extern int D_0063C418;
extern int D_0063C41C;
extern char *CreateGObj(char *layout, int id, int a2, int a3, int a4);
extern int CSVSYSTEM_InitDObj(int modelId, int arg);
extern void light_AddLight(char *gobj, int a1, int a2);
extern char D_0063B640;
extern int D_0063B644;
extern float D_0071D960[];
extern float D_0071D970[];
extern int exit_no;
/* prototypes: their order is the inline tail's emission order */
void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0);
char *CreateLayoutedGObj(int id, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5);
void test_nextstage_firstwalk_set(int unused, int a, int b, int c);
int GetStageStartInfo(int a0, int a1, int a2, int *p, int *q, int *r);
void MoveNextStage_Clear(void);
inline void MoveNextStage_Set(float *a0, float *a1, int a2, int a3, int a4, int a5) {
    D_0071D960[0] = a0[0];
    D_0071D960[1] = a0[1];
    D_0071D960[2] = a0[2];
    D_0063C414 = a2;
    D_0063C418 = a3;
    D_0063C41C = a4;
    D_0063B644 = a5;
    D_0071D970[0] = a1[0];
    D_0071D970[1] = a1[1];
    D_0071D970[2] = a1[2];
    D_0063B640 = 1;
}
inline void test_nextstage_firstwalk_set(int unused, int a, int b, int c) {
    D_0063C414 = a;
    D_0063C418 = b;
    D_0063C41C = c;
}
inline int GetStageStartInfo(int a0, int a1, int a2, int *p, int *q, int *r) {
    int ret = 1;
    if (exit_no == 0) {
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
inline void ChangeStageStartInfo(int a0, int a1, int a2, int a3, int t0)
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
inline void MoveNextStage_Clear(void) {
    D_0063B640 = 0;
    D_0063B644 = -1;
}
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", GetRealModelId);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", InitStageLight);
inline char *CreateLayoutedGObj(int id, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    char *layout = D_002C1270 + id * 0x64;
    char *gobj = CreateGObj(layout, id, a5, a6, a7);
    int dobj = CSVSYSTEM_InitDObj(a1, a4);
    int (*fn)(char *, int);

    *(int *)(gobj + 0x15C) = dobj;
    *(int *)(dobj + 0x844) = a2;

    light_AddLight(gobj, a3, 1);

    fn = *(int (**)(char *, int))(layout + 0x58);
    if (fn != 0) {
        *(int *)(*(int *)(gobj + 0x15C) + 0x830) = fn(gobj, a4);
    }
    return gobj;
}
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", initSceneGObj);
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", initParentLink);
void initWayData(int a0, int a1, int a2, int a3)
{
    ExtractWayData(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/sceneManager", InitSceneObjects);
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
