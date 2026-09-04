#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmInit);

extern void iosOmInit(void);

void _iosOmMain(void) {
    iosOmInit();
}

extern int D_0027DE30[];
extern int D_0062A4CC;
extern void *D_0062A4D4;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/obj_manager", iosOmMain);


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

/* 8-bucket linked-list search: for each of 8 buckets, walk the ->next(0x10)
 * chain and return the node whose id (p[0]) matches a0; else 0. The found node
 * funnels through v0 to a per-bucket `if(found)return found` check. The exact
 * shape matters: a do-while inner loop guarded by the head-null `if(p!=0)`, the
 * match writing `found = p` and jumping to the check, and a SINGLE `found = 0;`
 * after the guard (feeding both head-null and list-exhaust paths). That single
 * found=0 keeps `found`'s live range off the loop body so it coalesces into v0,
 * and leaves the not-found `return 0` its own `jr ra` with `daddu v0,0` in the
 * delay slot (distinct from the found-exit `jr ra; nop`) — reproducing ROM's two
 * separate returns instead of gcc's shared epilogue. */
int *iosOmSearchGObjId(int a0) {
    int i;
    for (i = 0; i < 8; i++) {
        int *p = D_0027DDF0[i];
        int *found;
        if (p != 0) {
            do {
                if (p[0] == a0) { found = p; goto check; }
                p = (int *)p[4];
            } while (p != 0);
        }
        found = 0;
    check:
        if (found != 0) return found;
    }
    return 0;
}

void iosOmSearchGObjIdAll(void) {
}

int iosOmSendMail(char *self_arg, int val5, int val6)
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
