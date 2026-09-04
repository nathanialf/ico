#include "common.h"

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
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FC30);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FD30);
ASM_LIT4_SLOT(D_0063928C, 0.001f);
extern void ExecMotionOrient();

void func_0019FE30(int a0, int a1, int a2, int a3)
{
    ExecMotionOrient(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FE38);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", _ACTSendMailToBird);
extern float acosf(float a0);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0Normalize(void *dst, void *src);

float vector_angle_degree(void *a0, void *a1) {
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a0);
    sceVu0Normalize(v1, a1);
    return acosf(sceVu0InnerProduct(v0, v1)) * 360.0f / 6.2831855f;
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FF18);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", InitBirdGeo);
void BirdAI(void) {}
extern void _ACTSendMailToBird();
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *o);

void _ACTSendMailToBirdAll(void *a0, void *a1) {
    void *obj = isysGObjSearchFromObjKindID_begin(0x20);
    while (obj != 0) {
        _ACTSendMailToBird(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
