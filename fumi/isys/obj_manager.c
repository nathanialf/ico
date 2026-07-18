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

/* NEAR-MISS (rc9, W3 convergence). LOGIC + STRUCTURE recovered (8-bucket hash
 * linked-list search). Dev shape:
 *   int *iosOmSearchGObjId(int a0) {
 *       int i;
 *       for (i = 0; i < 8; i++) {
 *           int *p = D_0027DDF0[i];
 *           while (p != 0) {
 *               if (p[0] == a0) return p;
 *               p = (int *)p[0x10/4];       // ->next at 0x10
 *           }
 *       }
 *       return 0;
 *   }
 * Matched: outer for(i<8) with base-ptr `addiu a2,a2,4` GIV, `lw p,0(a2)` head, the
 * inner list walk `lw id,0(p); ... lw p,16(p)`, the counter/slti/bne back-edges.
 * Residual (rc9): ROM FUNNELS the found node through v0 to a per-bucket shared exit
 * `.L3FA40: bnez v0` (match sets `daddu v0,p` in the beq delay -> v0; the head-null
 * and list-exhaust paths set v0=0; the outer check returns v0 or continues). It uses
 * PLAIN `beq v1,zero` (head) + `beq v0,a0` (match). gcc instead RETURNS directly on
 * match, emitting branch-LIKELY `beql v1,zero` (head, i++ in delay) + `bnel v0,a0`
 * (inverted match) + a separate `jr ra` found-exit. ~4 forms (direct-return while,
 * do-while+if-guard, found-var funnel [rc20], compound `while(p&&p[0]!=a0)` [rc13])
 * don't reproduce the plain-beq v0-funnel. NEXT LEVER: recover the shape that keeps
 * the found node in v0 flowing to a single per-bucket `if(found)return` check (blocks
 * the branch-likely + direct-exit). NOT a floor. */
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
