#include "common.h"

extern void CopyQuaternion(void *a0, int a1);
extern int GetSkeltonFocusNode(void *a0, int code);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionZ(void *a0, int a1);
extern void stage_PlayBgAnimation(void *a0, int a1, void *a2, float a3);
extern void stage_SetLoopFlag(void *a0, int a1);

void SetActressLight(void *a0, int a1, int a2, void *a3) {
    char buf[0x10];
    int r1 = GetSkeltonFocusNode(a0, a1);
    int r2 = GetSkeltonFocusNode(a0, a2);
    stage_SetLoopFlag(a3, 1);
    CopyQuaternion(buf, *(int *)(*(char **)((char *)a0 + 0x15C) + 0x10) + r1 * 0x10);
    RotQuaternionX(buf, 0x4000);
    RotQuaternionZ(buf, 0x4000);
    stage_PlayBgAnimation(a3, *(int *)(*(char **)((char *)a0 + 0x15C) + 0xC) + r2 * 0x40 + 0x30, buf, 0.0f);
    stage_SetLoopFlag(a3, 0);
}
