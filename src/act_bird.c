#include "common.h"

#include "itou_common.h"
#include "sugiCommon.h"

extern void ExecMotionOrient();
extern void iosOmSendMail(void *a0);
extern float acosf(float a0);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0Normalize(void *dst, void *src);
extern void _ACTWait(int a0);
extern void Debug_StickControl(void *gobj);
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
extern void *actInitialize(void *a0);
extern void actCreateSubThread(void *entry, int prio);
extern void func_0019E7F8();
extern int SetMotionRequest(void *a0, int id, void *work);
extern char D_00555788[];
extern void *D_0063A438;
extern char *iosMallocDebug(void *heap, int size, char *file, int line);
extern void memset(void *dst, int c, int n);
extern void CopyVector(void *dst, void *src);
extern void InitMotionOrient(void *o, int a1, int a2, int a3, int a4, int a5);
extern void SetLodLevel(void *o, int lod);
typedef union { int i; float f; } IntFloat;
extern void _ACTSendMailToBird();
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *o);
/* prototypes: their order is the inline tail's emission order */
float vector_angle_degree(void *a0, void *a1);
void subBirdControl(void *volatile gobj);
void subBirdCollision(void *volatile gobj);
void actBirdStart(void *a0);
char *InitBirdGeo(char *a0, void *a1);
void BirdAI(void);
void _ACTSendMailToBirdAll(void *a0, void *a1);
inline float vector_angle_degree(void *a0, void *a1) {
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a0);
    sceVu0Normalize(v1, a1);
    return radians_to_degrees(acosf(sceVu0InnerProduct(v0, v1)));
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", interp_vector_sa);
ASM_LIT4_SLOT(D_00639230, 10430.378f);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", birdBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", trans_bird);
ASM_LIT4_SLOT(D_00639234, 0.7f);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019E7F8);
ASM_LIT4_SLOT(D_00639238, 6.2831855f);
ASM_LIT4_SLOT(D_0063923C, 0.08726647f);
ASM_LIT4_SLOT(D_00639240, 6.2831855f);
ASM_LIT4_SLOT(D_00639244, 0.28f);
ASM_LIT4_SLOT(D_00639248, 0.28f);
ASM_LIT4_SLOT(D_0063924C, 0.4f);
ASM_LIT4_SLOT(D_00639250, 0.7f);
ASM_LIT4_SLOT(D_00639254, 6.2831855f);
ASM_LIT4_SLOT(D_00639258, 6.2831855f);
ASM_LIT4_SLOT(D_0063925C, 0.2f);
ASM_LIT4_SLOT(D_00639260, 6.2831855f);
ASM_LIT4_SLOT(D_00639264, 0.016666668f);
ASM_LIT4_SLOT(D_00639268, 6.2831855f);
ASM_LIT4_SLOT(D_0063926C, 6.2831855f);
ASM_LIT4_SLOT(D_00639270, 0.034906585f);
ASM_LIT4_SLOT(D_00639274, -0.034906585f);
ASM_LIT4_SLOT(D_00639278, 0.6f);
ASM_LIT4_SLOT(D_0063927C, -1.3f);
ASM_LIT4_SLOT(D_00639280, 0.6f);
ASM_LIT4_SLOT(D_00639284, 0.14285715f);
ASM_LIT4_SLOT(D_00639288, 0.2f);
inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        Debug_StickControl(gobj);
        _ACTWait(1);
    }
}
inline void subBirdCollision(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        _ACTWait(1);
    }
}
inline void actBirdStart(void *a0) {
    char *w;

    w = (char *)actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(func_0019E7F8, 0x14);
    actCreateSubThread(subBirdControl, 0x15);
    actCreateSubThread(subBirdCollision, 0x15);
    *(int *)(w + 0x130) = SetMotionRequest(a0, 0x10E, w + 0x620);
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", Debug_WireString_Bird);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", Debug_StickControl);
ASM_LIT4_SLOT(D_0063928C, 0.001f);
void func_0019FE30(int a0, int a1, int a2, int a3)
{
    ExecMotionOrient(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FE38);
inline char *InitBirdGeo(char *a0, void *a1) {
    char *w;

    w = iosMallocDebug(D_0063A438, 0x40, D_00555788, 978);
    memset(w, 0, 0x40);
    CopyVector(w, a1);
    w[0x10] = 0;
    InitMotionOrient(a0, 0x975, 0x9A3, -1, -1, 0x46E);

    *(int *)(*(int *)(a0 + 0x15C) + 0x544) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x54C) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x548) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x550) = 0;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f = random_unit() * 100.0f;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4B0))->f =
        ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f;
    *(int *)(*(int *)(a0 + 0x15C) + 0x4C4) = 0;
    SetLodLevel(a0, 3);
    return w;
}
inline void BirdAI(void) {}
void _ACTSendMailToBird(void *a0, void *a1, void *a2) {
    iosOmSendMail(a0);
}
inline void _ACTSendMailToBirdAll(void *a0, void *a1) {
    void *obj = isysGObjSearchFromObjKindID_begin(0x20);
    while (obj != 0) {
        _ACTSendMailToBird(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
