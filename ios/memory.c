#include "common.h"

#include "vu0.h"

typedef struct IosMemTag {
    char c[16];
} IosMemTag;
typedef struct IosMemNode {
    char tag[16];                  /* 0x00 */
    char name[16];                 /* 0x10 */
    struct IosMemNode *prev;       /* 0x20 */
    struct IosMemNode *next;       /* 0x24 */
    struct IosMemNode *free_prev;  /* 0x28 */
    struct IosMemNode *free_next;  /* 0x2C */
    struct IosMemPart *part;       /* 0x30 */
    int size;                      /* 0x34 */
    int line;                      /* 0x38 */
    int pad3C;                     /* 0x3C */
    struct IosMemNode *pad40;      /* 0x40 (partition header view) */
    struct IosMemNode *head;       /* 0x44 (partition header view: free-list head) */
} IosMemNode;
typedef struct IosMemPart {
    char tag[16];                  /* 0x00 */
    char name[16];                 /* 0x10 */
    int unk20[9];                  /* 0x20 */
    IosMemNode *free_list;         /* 0x44 */
} IosMemPart;

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocSetPartition);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocResetPartition);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocSetPartitionName);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocClearPartition);

extern char D_00556F70[];
extern char D_00556FB8[];
extern char D_00556FD8[];
extern void debug_assertMessage();
extern int func_00265024(int *a0, const char *a1);
extern void func_00265168(unsigned char *ptr, int value);

int iosMallocDebug(int *a0, int a1)
{
    if (a0 == 0)
    {
        debug_assertMessage(D_00556FB8);
        return 0;
    }
    if (func_00265024(a0, D_00556F70) != 0)
    {
        debug_assertMessage(D_00556FD8);
        return 0;
    }
    func_00265168((unsigned char *)((char *) a0 + 0x10), a1);
}

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138C78);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138E30);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001392A8);

extern char D_005572B8[];
extern int func_001007A0(int a0);
extern void *iosMallocCheckLeak2(void *a0);

void iosMallocCheckLeak(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    func_001007A0(0);
    iosMallocCheckLeak2((void *)a0);
    debug_assertMessage(D_005572B8, a1, a2, a0, end);
    {
        register int g = (unsigned int) a0 < (unsigned int) end;
        if (g)
        {
            do
            {
                *(unsigned int *) a0 = 0xFFFFFFFFu;
                a0++;
            } while ((unsigned int) a0 < (unsigned int) end);
        }
    }
    func_001007A0(0);
}

extern char D_00556F80[];
extern char D_005570E0[];
extern char D_00557220[];
extern char D_005572D8[];
extern char D_005572E8[];
extern char D_00557300[];
extern char D_00557320[];
extern char D_00557360[];
extern char D_00557370[];
extern char D_00557390[];
extern char D_005573A0[];
extern char D_005573B0[];
extern char D_005573C8[];
extern char D_006320B8[];
extern char D_006320C8[];
extern void func_001AD748(char *file, int line, char *msg);
extern void func_00263FF0(char *file, int line, char *expr);
extern int func_00264028(void *a0);
extern void func_00264DF8();
extern int func_002653B8(void *a0, void *a1, int a2);

void *iosMallocCheckLeak2(void *ptr)
{
    char buf[1024];
    IosMemNode *node;
    IosMemNode *next;
    IosMemNode *prev;
    IosMemNode *fn;
    int n;

    debug_assertMessage(D_005572D8);
    if (ptr == 0) {
        debug_assertMessage(D_005572E8);
        __asm__ __volatile__("break");
        func_001AD748(D_005570E0, 0x334, D_00557300);
        func_00263FF0(D_005570E0, 0x334, D_006320B8);
        return 0;
    }
    prev = (IosMemNode *)((char *)ptr - 0x10);
    next = ptr;
    if (func_002653B8(prev, D_006320C8, 5) == 0) {
        n = func_00264028((char *)ptr - 0xB);
        *((char *)ptr - 0x10) = 0;
        next = (IosMemNode *)((char *)prev - (n - 0x10));
    }
    node = (IosMemNode *)((char *)next - 0x40);
    if (func_00265024((int *)node, D_00557220) != 0) {
        func_00264DF8(buf, D_00557320, node->prev, node, node->next);
        func_001AD748(D_005570E0, 0x344, buf);
        func_00263FF0(D_005570E0, 0x344, D_006320B8);
        return 0;
    }
    next = node->next;
    prev = node->prev;
    if (prev != 0) {
        if (func_00265024((int *)prev, D_00556F80) == 0) {
            if (next != 0) {
                if (func_00265024((int *)next, D_00556F80) == 0) {
                    if (prev->free_next == next) {
                        fn = next->free_next;
                        prev->free_next = fn;
                        if (fn != 0) {
                            fn->free_prev = prev;
                        }
                    } else if (next->free_next == prev) {
                        fn = next->free_prev;
                        prev->free_prev = fn;
                        if (fn == 0) {
                            ((IosMemNode *)node->part)->head = prev;
                        } else {
                            fn->free_next = prev;
                        }
                    } else {
                        fn = next->free_prev;
                        if (fn == 0) {
                            ((IosMemNode *)node->part)->head = next->free_next;
                        } else {
                            fn->free_next = next->free_next;
                        }
                        if (next->free_next != 0) {
                            next->free_next->free_prev = next->free_prev;
                        }
                    }
                    {
                        int t = prev->size + 4;
                        t += next->size;
                        prev->next = next->next;
                        prev->size = t;
                    }
                    *(IosMemTag *)next = *(IosMemTag *)D_00557360;
                    if (next->next != 0) {
                        next->next->prev = prev;
                    }
                } else if (func_00265024((int *)next, D_00557220) == 0) {
                    prev->next = next;
                    next->prev = prev;
                } else {
                    func_001AD748(D_005570E0, 0x389, D_00557370);
                    func_00263FF0(D_005570E0, 0x389, D_006320B8);
                    return 0;
                }
            } else {
                prev->next = 0;
            }
            {
                int t = prev->size;
                t += 4;
                t += node->size;
                prev->size = t;
            }
            *(IosMemTag *)node = *(IosMemTag *)D_00557390;
            goto ret_ptr;
        }
        if (func_00265024((int *)prev, D_00557220) != 0) {
            goto err_3bf;
        }
    }
    if (next == 0) {
        goto tail_node;
    }
    if (func_00265024((int *)next, D_00557220) == 0) {
        node->free_prev = 0;
        node->free_next = ((IosMemNode *)node->part)->head;
        ((IosMemNode *)node->part)->head = node;
        if (node->free_next != 0) {
            node->free_next->free_prev = node;
        }
        goto tag_free;
    }
    if (func_00265024((int *)next, D_00556F80) != 0) {
        goto err_3b5;
    }
    fn = next->free_prev;
    if (fn == 0) {
        ((IosMemNode *)node->part)->head = node;
    } else {
        fn->free_next = node;
    }
    node->free_prev = next->free_prev;
    node->free_next = next->free_next;
    {
        int t = node->size;
        t += 4;
        t += next->size;
        node->size = t;
    }
    node->next = next->next;
    *(IosMemTag *)next = *(IosMemTag *)D_005573A0;
    if (next->next != 0) {
        next->next->prev = node;
    }
    if (next->free_next != 0) {
        next->free_next->free_prev = node;
    }
    goto tag_free;
tail_node:
    node->free_prev = 0;
    node->free_next = ((IosMemNode *)node->part)->head;
    if (((IosMemNode *)node->part)->head != 0) {
        ((IosMemNode *)node->part)->head = node;
        node->free_next->free_prev = node;
    }
    func_001AD748(D_005570E0, 0x3C2, D_005573B0);
    func_00263FF0(D_005570E0, 0x3C2, D_006320B8);
    goto tag_free;
err_3b5:
    func_001AD748(D_005570E0, 0x3C5, D_00557370);
    func_00263FF0(D_005570E0, 0x3C5, D_006320B8);
    return 0;
tag_free:
    *(IosMemTag *)node = *(IosMemTag *)D_00556F80;
    goto ret_ptr;
err_3bf:
    func_001AD748(D_005570E0, 0x3CF, D_005573C8);
    func_00263FF0(D_005570E0, 0x3CF, D_006320B8);
ret_ptr:
    return ptr;
}

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosReallocDebug);

extern char D_00556F80[];
extern char D_00557060[];
extern char D_00557220[];
extern char D_00557458[];
extern char D_00557470[];
extern char D_00557480[];
extern char D_00557490[];
extern char D_005574A8[];
extern char D_006A6970[];
extern void debug_assertMessage__p4(const char *fmt, ...) __asm__("debug_assertMessage");
extern int func_00265570(char *dst, int src, int n);

void iosMallocInitPartition(int a0, int a1) {
    int node = *(int *)(a0 + a1 + 0x38);
    int r;

    debug_assertMessage__p4(D_00557458, a0);
    if (node == 0) {
        return;
    }
    do {
            node += a1;
            func_00265570(D_006A6970, node + 0x10, 0xF);
            D_006A6970[0xF] = 0;
            r = func_00265024((int *)node, D_00557220);
            if (r == 0) {
                debug_assertMessage__p4(D_00557470, node - a1, D_006A6970);
                r = 0xB;
                goto delay;
            }
            r = func_00265024((int *)node, D_00556F80);
            if (r == 0) {
                debug_assertMessage__p4(D_00557480, node - a1);
                r = 0xB;
                goto delay;
            }
            r = func_00265024((int *)node, D_00557060);
            if (r != 0) {
                debug_assertMessage__p4(D_005574A8, node - a1, node);
                return;
            }
            debug_assertMessage__p4(D_00557490);
            r = 0xB;
        delay:
            do {
                r--;
                VU0_NOP();
                VU0_NOP();
                VU0_NOP();
                VU0_NOP();
            } while (r >= 0);
            node = *(volatile int *)(node + 0x24);
    } while (node != 0);
}

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139FE8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A0F8);

extern int func_00138E30(void);

int func_0013A200(void)
{
    return func_00138E30();
}

