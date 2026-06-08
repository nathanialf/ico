#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmInit);

extern void iosOmInit(void);

void _iosOmMain(void) {
    iosOmInit();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmMain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmCreateDL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmExeEachGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmExeEachGObjAll);

extern int isysGObjAddBeforeGObj(void *a0);

void iosOmReturnExeEachGObj(int *a0, int *a1) {
    *a0 = 0x140;
    *a1 = isysGObjAddBeforeGObj(a0);
}

extern int *D_0027DDF0[];

int *iosOmGetGObjStatus(int idx, int target)
{
    int *p = D_0027DDF0[idx];
    if (p != 0) {
        do {
            if (p[0] == target) {
                return p;
            }
            p = (int *)p[0x10/4];
        } while (p != 0);
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmSearchGObjId);

void iosOmSearchGObjIdAll(void) {
}

int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6)
{
    register char *self = self_arg;
    int *p = (int *)(self + 0x54);
    int count = p[1];
    register int idx;
    register char *addr;
    if (count == 0x20) return -1;
    idx = count * 8;
    __asm__("addu %0, %1, %2" : "=r"(addr) : "r"(self), "0"(idx));
    *(int *)(addr + 0x5C) = val5;
    {
        int c2 = p[1];
        register int idx2;
        register char *addr2;
        p[1] = c2 + 1;
        idx2 = c2 * 8;
        __asm__("addu %0, %1, %2" : "=r"(addr2) : "r"(self), "0"(idx2));
        *(int *)(addr2 + 0x60) = val6;
    }
    return 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DDF0;  /* stride 0x4 */

/* end struct shapes */
