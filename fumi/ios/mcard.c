#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcHandlerWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrChdirProduct);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrSaveSeg);

extern void iosMcMgrChdirProduct(void *a0, int a1);

void iosMcMgrLoadSeg(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrChdirProduct(a0, 0);
}

extern void iosMcMgrSaveSeg(void *a0, int a1);

void iosMcMgrSaveProductBlock(void *a0) {
    *(int *)((char *)a0 + 0x24) = 0;
    iosMcMgrSaveSeg(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrLoadProductBlock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrGetBlockSaveInfo);

void iosMcManager(void) {
}

int iosMcMgrSync(void *a0) {
    unsigned long long x = *(unsigned long long *)a0;
    return -((unsigned char)x & 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcTest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcSync);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcGetInfo);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_10;  /* 0x10 */
} S_006A0498;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027CF80;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005512E0;  /* stride 0x4 */

/* end struct shapes */
