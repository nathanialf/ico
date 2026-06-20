#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmInit);

extern void iosOmInit(void);

void _iosOmMain(void) {
    iosOmInit();
}

extern int D_0027DE30[];
extern int D_0062A4CC;
extern void *D_0062A4D4;

void iosOmMain(void) {
    char *s2 = D_0062A4D4;
    int i;
    int var2;
    if (s2 == 0) {
        return;
    }
    var2 = D_0062A4CC & 1;
    do {
        i = 0;
        if (var2 != 0) {
            void (*f)(void *) = *(void (**)(void *))(s2 + 0x48);
            if (f != 0) {
                f(s2);
            }
        }
        do {
            if (((D_0062A4CC >> i) & 1) && ((*(int *)(s2 + 0x4C) >> i) & 1)) {
                char *s0 = (char *)D_0027DE30[i];
                if (s0 != 0) {
                    do {
                        void (*g)(void *);
                        if (*(int *)(s0 + 0x16C) != 0 &&
                            (*(int *)(s2 + 0x50) & *(int *)(s0 + 0x50)) != 0) {
                            g = *(void (**)(void *))(s0 + 0x48);
                            if (g != 0) {
                                g(s0);
                            }
                        }
                        s0 = *(char **)(s0 + 0x34);
                    } while (s0 != 0);
                }
            }
            i++;
        } while (i < 0x20);
        s2 = *(char **)(s2 + 0x34);
        var2 = D_0062A4CC & 1;
    } while (s2 != 0);
}


extern int *D_0027DDF0[];
void iosOmCreateDL(int idx, void (*func)(int *, void *), void *arg) {
    int *node = D_0027DDF0[idx];
    while (node != 0) {
        func(node, arg);
        node = (int *)node[4];
    }
}

extern int *D_0027DDF0[];
void iosOmExeEachGObj(void (*func)(int *, void *), void *arg) {
    int i;
    for (i = 0; i < 8; i++) {
        int *node = D_0027DDF0[i];
        while (node != 0) {
            func(node, arg);
            node = (int *)node[4];
        }
    }
}

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
