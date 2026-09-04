#include "common.h"

extern void isysGObjCameraDlInit(void);
extern void isysGObjDlInit();
extern void isysGObjInit();
extern void isysGObjProcessInit();

void iosOmInit(void)
{
    isysGObjInit(0x140);
    isysGObjProcessInit(0x500);
    isysGObjDlInit();
    return isysGObjCameraDlInit();
}
INCLUDE_ASM("asm/nonmatchings/isys/obj_manager", _iosOmMain);
extern void _iosOmMain();

void iosOmMain(int a0, int a1, int a2, int a3)
{
    _iosOmMain(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/isys/obj_manager", iosOmCreateDL);
extern int *D_0029C4F0[];

void iosOmExeEachGObj(int idx, void (*fn)(int *, int), int arg)
{
    int *node = D_0029C4F0[idx];
    if (node != 0) {
        do {
            fn(node, arg);
            node = (int *)node[0x10 / 4];
        } while (node != 0);
    }
}
void iosOmExeEachGObjAll(void (*fn)(int *, int), int arg)
{
    int i = 0;
    do {
        int *node = D_0029C4F0[i];
        if (node != 0) {
            do {
                fn(node, arg);
                node = (int *)node[0x10 / 4];
            } while (node != 0);
        }
        i++;
    } while (i < 8);
}
int iosOmReturnExeEachGObj(int a0, int (*fn)(int *, int), int arg, int flag)
{
    int *node = D_0029C4F0[a0];
    int ret = 0;
    if (node != 0) {
        do {
            ret = fn(node, arg);
            if (flag != 0) {
                if (flag == 1) {
                    if (ret != 0) return ret;
                }
            }
        } while (node != 0);
    }
    return ret;
}
extern int isysGetNbAllocedGObjs();

void iosOmGetGObjStatus(int a0, int a1)
{
    *(int *)a0 = 0x140;
    *(int *)a1 = isysGetNbAllocedGObjs(a0);
}
int *iosOmSearchGObjId(int idx, int target)
{
    int *p = D_0029C4F0[idx];
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
int *iosOmSearchGObjIdAll(int a0) {
    int i;
    for (i = 0; i < 8; i++) {
        int *p = D_0029C4F0[i];
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
void iosOmBeforeFuncStandard(void) {}
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
int iosOmSendMailLink(int a0, int val5, int val6)
{
    int *node = D_0029C4F0[a0];
    int ret = 0;
    if (node != 0) {
        do {
            int full;
            int *p = (int *)((char *)node + 0x54);
            int count = p[1];

            if (count == 0x20) {
                full = -1;
            } else {
                register int idx;
                register char *addr;
                idx = count * 8;
                __asm__("addu %0, %1, %2" : "=r"(addr) : "r"(node), "0"(idx));
                full = 0;
                *(int *)(addr + 0x5C) = val5;
                {
                    int c2 = p[1];
                    register int idx2;
                    register char *addr2;
                    p[1] = c2 + 1;
                    idx2 = c2 * 8;
                    __asm__("addu %0, %1, %2" : "=r"(addr2) : "r"(node), "0"(idx2));
                    *(int *)(addr2 + 0x60) = val6;
                }
            }
            node = (int *)node[0x10 / 4];
            if (full != 0) ret = -1;
        } while (node != 0);
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/isys/obj_manager", iosOmExeMail);
