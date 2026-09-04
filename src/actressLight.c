#include "common.h"

extern void CopyQuaternion(void *a0, int a1);
extern int GetSkeltonFocusNode(void *a0, int code);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionZ(void *a0, int a1);
extern void stage_PlayBgAnimation(void *a0, int a1, void *a2, float a3);
extern void stage_SetLoopFlag(void *a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", SetActressLight);
