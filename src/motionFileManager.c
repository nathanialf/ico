#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x190 - 0x134 - 4];
} MotionNode;
extern MotionNode D_00565060[];
extern int D_004C49A8[];

void pursueNodeList(int a0) {
    int i;
    for (i = 0; i <= 0x43D; i++) {
        if (D_00565060[i].node_id == a0) {
            D_004C49A8[i] = 0;
        }
    }
}

int InitMotionFile(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2]) r = 0; else r = -1;
    return r;
}

extern char D_004C5AE0[];
extern char D_004C5AF0[];
extern char D_004C5B00[];
extern char D_004C5B10[];
extern char D_004C5B20[];
extern void func_001D4A58(void *a0, void *a1, void *a2, void *a3, int a4);

void InitMotionMemorySize(void) {
    func_001D4A58(D_004C5AF0, D_004C5AE0, D_004C5B10, D_004C5AE0, -1);
    func_001D4A58(D_004C5B10, D_004C5AE0, D_004C5B00, D_004C5AE0, -1);
    func_001D4A58(D_004C5B00, D_004C5AE0, D_004C5B20, D_004C5AE0, -1);
    func_001D4A58(D_004C5B20, D_004C5AE0, D_004C5AF0, D_004C5AE0, -1);
}

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetDynamicMotionManager);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetStatic2MotionManager);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8590);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8758);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D88B8);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8968);

