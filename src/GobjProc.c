#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern int D_0063C0C8;

INCLUDE_ASM("asm/nonmatchings/src/GobjProc", ResetGObjProc);
int GetMaxGObj(void) {
    return D_0063C0C8;
}
extern int D_0072A2C0[];

int GetGObjP(int idx)
{
    return D_0072A2C0[idx];
}
extern int D_0063C0C8;
extern int D_0072A2C0[];

int GetGObjId(int a0) {
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
        if (a0 == D_0072A2C0[i]) {
            return i;
        }
    }
    return -1;
}
extern char D_0063C0D0[];
extern void debug_StdPrintfDummy();

void PrintGObjID(int a0) {
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
        if (a0 == D_0072A2C0[i]) {
            debug_StdPrintfDummy(D_0063C0D0, i);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", InitCameraGObjs);
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", CreateGObj);
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", CreateGObjByFuncSet);
