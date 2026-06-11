#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x190 - 0x134 - 4];
} MotionNode;
extern MotionNode D_0055DA10[];
extern int D_004C0A98[];

void pursueNodeList(int a0) {
    int i;
    for (i = 0; i <= 0x43F; i++) {
        if (D_0055DA10[i].node_id == a0) {
            D_004C0A98[i] = 0;
        }
    }
}

int InitMotionFile(void *a0) {
    return (char *)a0 + 0x10 < *(char **)((char *)a0 + 0x8) ? 0 : -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", InitMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetDynamicMotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetStatic2MotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5928);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5AF0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5C50);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5D00);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A30;  /* stride 0x4 */

/* end struct shapes */
