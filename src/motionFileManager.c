#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", pursueNodeList);
INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", InitMotionFile);
extern int D_0063C46C;
extern int D_0063C470;

void InitMotionMemorySize(void) {
    D_0063C46C = 0;
    D_0063C470 = 0;
}
extern int D_0063C46C;
extern int D_0063C470;

int AddMotionMemorySize(int a0, int a1)
{
    int v0;
    if (a1 != 0) {
        v0 = D_0063C470 + a0;
        D_0063C470 = v0;
    } else {
        v0 = D_0063C46C + a0;
        D_0063C46C = v0;
    }
    return v0;
}
int GetMotionMemorySize(int a0)
{
    return a0 ? D_0063C470 : D_0063C46C;
}
INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetDynamicMotionManager);
typedef struct { char pad[0x134]; int node_id; char pad2[0x194 - 0x138]; } MotFileRec;
extern MotFileRec D_0055FE58[];
extern int D_004EB758[];
void ResetStatic2MotionManager(int a0) {
    int i;
    for (i = 0; i <= 0x47A; i++) {
        if (D_0055FE58[i].node_id == a0) {
            D_004EB758[i] = 0;
        }
    }
}
int CheckMotionIncludeFacialData(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2]) r = 0; else r = -1;
    return r;
}
