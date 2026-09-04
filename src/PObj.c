#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"


/* .data */
unsigned int D_004D4230[32] = {
    0x656A626F, 0x732F7463, 0x622F6664, 0x6D2F796F,
    0x6C65646F, 0x796F622F, 0x65646F6D, 0x32702E6C,
    0x00000063, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x656A626F, 0x732F7463, 0x622F6664, 0x6D2F796F,
    0x6C65646F, 0x6468732F, 0x646F6D77, 0x702E6C65,
    0x00007332, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
}; /* "object/sdf/boy/model/boymodel.p2c" + "object/sdf/boy/model/shdwmodel.p2s" */

extern int D_00712CC0[];
extern int D_00633B98;

void MakeBoundingBox(void) {
    D_00633B98 = 0;
}

int MakePacket(void) {
    return D_00633B98;
}

int AllocPObj(int idx)
{
    return D_00712CC0[idx];
}

extern int D_00633B98;

int GetGObjId(int a0) {
    int i;
    for (i = 0; i < D_00633B98; i++) {
        if (a0 == D_00712CC0[i]) {
            return i;
        }
    }
    return -1;
}

extern char D_00633BA0[];
extern void debug_StdPrintfDummy();

void PrintGObjID(int a0) {
    int i;
    for (i = 0; i < D_00633B98; i++) {
        if (a0 == D_00712CC0[i]) {
            debug_StdPrintfDummy(D_00633BA0, i);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240C50);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240D40);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240EA0);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_00240FC8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002412D8);

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002413F0);

