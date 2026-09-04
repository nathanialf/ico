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
extern char D_00551490[];
extern char D_005514D8[];
extern char D_005514F8[];
extern void debug_StdPrintfDummy();
extern int strcmp(int *a0, const char *a1);
extern void strcpy(unsigned char *ptr, int value);

int iosMallocSetPartitionName(int *a0, int a1)
{
    if (a0 == 0)
    {
        debug_StdPrintfDummy(D_005514D8);
        return 0;
    }
    if (strcmp(a0, D_00551490) != 0)
    {
        debug_StdPrintfDummy(D_005514F8);
        return 0;
    }
    strcpy((unsigned char *)((char *) a0 + 0x10), a1);
}
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocClearPartition);
INCLUDE_ASM("asm/nonmatchings/ios/memory", _iosMallocDebug);
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocAlignDebug);
extern char D_005517D8[];
extern int FlushCache(int a0);
extern void *iosFree(void *a0);

void _iosFreeWithFill(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    FlushCache(0);
    iosFree((void *)a0);
    debug_StdPrintfDummy(D_005517D8, a1, a2, a0, end);
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
    FlushCache(0);
}
extern char D_005514A0[];
extern char D_00551600[];
extern char D_00551740[];
extern char D_005517F8[];
extern char D_00551808[];
extern char D_00551820[];
extern char D_00551840[];
extern char D_00551880[];
extern char D_00551890[];
extern char D_005518B0[];
extern char D_005518C0[];
extern char D_005518D0[];
extern char D_005518E8[];
extern char D_0063A4E0[];
extern char D_0063A4F0[];
extern void __assert(char *file, int line, char *expr);
extern int atoi(void *a0);
extern void func_001B6230(char *file, int line, char *msg);
extern void sprintf();
extern int strncmp(void *a0, void *a1, int a2);

void *iosFree(void *ptr)
{
    char buf[1024];
    IosMemNode *node;
    IosMemNode *next;
    IosMemNode *prev;
    IosMemNode *fn;
    int n;

    debug_StdPrintfDummy(D_005517F8);
    if (ptr == 0) {
        debug_StdPrintfDummy(D_00551808);
        __asm__ __volatile__("break");
        func_001B6230(D_00551600, 0x334, D_00551820);
        __assert(D_00551600, 0x334, D_0063A4E0);
        return 0;
    }
    prev = (IosMemNode *)((char *)ptr - 0x10);
    next = ptr;
    if (strncmp(prev, D_0063A4F0, 5) == 0) {
        n = atoi((char *)ptr - 0xB);
        *((char *)ptr - 0x10) = 0;
        next = (IosMemNode *)((char *)prev - (n - 0x10));
    }
    node = (IosMemNode *)((char *)next - 0x40);
    if (strcmp((int *)node, D_00551740) != 0) {
        sprintf(buf, D_00551840, node->prev, node, node->next);
        func_001B6230(D_00551600, 0x344, buf);
        __assert(D_00551600, 0x344, D_0063A4E0);
        return 0;
    }
    next = node->next;
    prev = node->prev;
    if (prev != 0) {
        if (strcmp((int *)prev, D_005514A0) == 0) {
            if (next != 0) {
                if (strcmp((int *)next, D_005514A0) == 0) {
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
                    *(IosMemTag *)next = *(IosMemTag *)D_00551880;
                    if (next->next != 0) {
                        next->next->prev = prev;
                    }
                } else if (strcmp((int *)next, D_00551740) == 0) {
                    prev->next = next;
                    next->prev = prev;
                } else {
                    func_001B6230(D_00551600, 0x389, D_00551890);
                    __assert(D_00551600, 0x389, D_0063A4E0);
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
            *(IosMemTag *)node = *(IosMemTag *)D_005518B0;
            goto ret_ptr;
        }
        if (strcmp((int *)prev, D_00551740) != 0) {
            goto err_3bf;
        }
    }
    if (next == 0) {
        goto tail_node;
    }
    if (strcmp((int *)next, D_00551740) == 0) {
        node->free_prev = 0;
        node->free_next = ((IosMemNode *)node->part)->head;
        ((IosMemNode *)node->part)->head = node;
        if (node->free_next != 0) {
            node->free_next->free_prev = node;
        }
        goto tag_free;
    }
    if (strcmp((int *)next, D_005514A0) != 0) {
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
    *(IosMemTag *)next = *(IosMemTag *)D_005518C0;
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
    func_001B6230(D_00551600, 0x3C2, D_005518D0);
    __assert(D_00551600, 0x3C2, D_0063A4E0);
    goto tag_free;
err_3b5:
    func_001B6230(D_00551600, 0x3C5, D_00551890);
    __assert(D_00551600, 0x3C5, D_0063A4E0);
    return 0;
tag_free:
    *(IosMemTag *)node = *(IosMemTag *)D_005514A0;
    goto ret_ptr;
err_3bf:
    func_001B6230(D_00551600, 0x3CF, D_005518E8);
    __assert(D_00551600, 0x3CF, D_0063A4E0);
ret_ptr:
    return ptr;
}
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocCheckLeak);
extern char D_00551580[];
extern char D_00551978[];
extern char D_00551990[];
extern char D_005519A0[];
extern char D_005519B0[];
extern char D_005519C8[];
extern char D_006BC918[];
extern int strncpy(char *dst, int src, int n);

void iosMallocCheckLeak2(int a0, int a1) {
    int node = *(int *)(a0 + a1 + 0x38);
    int r;

    debug_StdPrintfDummy(D_00551978, a0);
    if (node == 0) {
        return;
    }
    do {
            node += a1;
            strncpy(D_006BC918, node + 0x10, 0xF);
            D_006BC918[0xF] = 0;
            r = strcmp((int *)node, D_00551740);
            if (r == 0) {
                debug_StdPrintfDummy(D_00551990, node - a1, D_006BC918);
                r = 0xB;
                goto delay;
            }
            r = strcmp((int *)node, D_005514A0);
            if (r == 0) {
                debug_StdPrintfDummy(D_005519A0, node - a1);
                r = 0xB;
                goto delay;
            }
            r = strcmp((int *)node, D_00551580);
            if (r != 0) {
                debug_StdPrintfDummy(D_005519C8, node - a1, node);
                return;
            }
            debug_StdPrintfDummy(D_005519B0);
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
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosReallocDebug);
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocInitPartition);
INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocDebug);
extern int _iosMallocDebug(void);

int iosMallocDebugNoAssert(void)
{
    return _iosMallocDebug();
}
