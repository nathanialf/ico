#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/act_bird", interp_vector_sa);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", birdBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", trans_bird);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019E7F8);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FC30);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FD30);
extern void ExecMotionOrient();

void func_0019FE30(int a0, int a1, int a2, int a3)
{
    ExecMotionOrient(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019FE38);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", _ACTSendMailToBird);
INCLUDE_ASM("asm/nonmatchings/src/act_bird", vector_angle_degree);
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
