#include "common.h"

/* header prototypes (order fixes the inline tail) */
void ExitIcoMisc(void);
extern char D_0061D3E0[];
extern char D_0061D418[];
extern void *D_0063A428;
extern char D_0071CA90[];
extern void debug_PrintfDummy(int a0, int a1, unsigned int a2, void *a3);
extern void iosMallocCheckLeak(void *a0);
extern void sprintf();
inline void ExitIcoMisc(void) {}
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", disp_memory_partition_bar);
void disp_memory_partition(void) {
    char *p;
    int y = 0x70;
    debug_PrintfDummy(0x18, 0x64, 0xFFFFFF00, D_0061D3E0);
    iosMallocCheckLeak(D_0063A428);
    p = *(char **)((char *)D_0063A428 + 0x28);
    if (p != 0) {
        do {
            unsigned int sum = 0;
            unsigned int max = 0;
            char *e;
            int diff;
            iosMallocCheckLeak(p);
            e = *(char **)(p + 0x44);
            if (e != 0) {
                do {
                    unsigned int v = *(int *)(e + 0x34) << 4;
                    if (max < v) {
                        max = v;
                    }
                    sum += v;
                    e = *(char **)(e + 0x2C);
                } while (e != 0);
            }
            diff = *(int *)(p + 0x3C) - *(int *)(p + 0x38) + 0x10;
            sprintf(D_0071CA90, D_0061D418, p + 0x10, p, sum, diff, max);
            debug_PrintfDummy(0x64, y, 0xFFFFFF00, D_0071CA90);
            y += 8;
            p = *(char **)(p + 0x24);
        } while (p != 0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", ExecIcoMisc);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", InitIcoMisc);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", DispIcoMisc);
