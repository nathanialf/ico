#include "common.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocSetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocResetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocSetPartitionName);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocClearPartition);

extern int func_002613B4(int *a0, const char *a1);
extern void func_002614F8(unsigned char *ptr, int value);
extern void debug_assertMessage(const char *fmt, ...);

extern char D_00551340[];

extern char D_00551388[];

extern char D_005513A8[];

int iosMallocDebug(int *a0, int a1)
{
    if (a0 == 0)
    {
        debug_assertMessage(D_00551388);
        return 0;
    }
    if (func_002613B4(a0, D_00551340) != 0)
    {
        debug_assertMessage(D_005513A8);
        return 0;
    }
    func_002614F8((unsigned char *)((char *) a0 + 0x10), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", _iosFreeWithFill);

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
} IosMemNode;                      /* 0x40 */

typedef struct IosMemPart {
    char tag[16];                  /* 0x00 */
    char name[16];                 /* 0x10 */
    int unk20[9];                  /* 0x20 */
    IosMemNode *free_list;         /* 0x44 */
} IosMemPart;

extern void func_001AACE0(char *file, int line, char *msg);
extern void func_001AAD00(char *file, int line);
extern void func_00260380(char *file, int line, char *expr);
extern void func_00261188(char *buf, const char *fmt, ...);
extern unsigned int func_0026160C(char *s);
extern int func_00260340(float val);
extern int func_00261900(char *dst, int src, int n);

extern int D_0062A3B0;
extern char *D_0062BF8C;
extern int D_0062BF90;

extern char D_00551350[];
extern char D_00551468[];
extern char D_005514B0[];
extern char D_005514C0[];
extern char D_005514F0[];
extern char D_00551510[];
extern char D_00551538[];
extern char D_00551550[];
extern char D_00551578[];
extern char D_00551590[];
extern char D_005515B8[];
extern char D_005515D0[];
extern char D_005515F0[];
extern char D_00551600[];
extern char D_00551610[];
extern char D_00551620[];
extern char D_00551638[];
extern char D_0062C238[];
extern char D_0062C240[];

void *iosFree(IosMemPart *part, int size, char *file, int line)
{
    char buf[1040];
    char buf2[1024];
    IosMemNode *p;
    IosMemNode *best;
    IosMemNode *newnode;
    int want;
    int i;
    int n;
    int t;
    int sz;
    int v;
    int q;
    int j;
    int len;
    char *name;
    char *ret;
    char *dst;

    if (D_0062A3B0 != 0) {
        func_00261188(buf, D_00551468, part->name, size, D_0062BF8C, D_0062BF90);
        func_001AACE0(file, line, buf);
    }
    D_0062BF8C = file;
    D_0062A3B0 = 1;
    D_0062BF90 = line;

    if (part == 0) {
        func_001AACE0(D_005514B0, 0x228, D_005514C0);
        func_00260380(D_005514B0, 0x228, D_0062C238);
        D_0062A3B0 = 0;
        return 0;
    }
    if (func_002613B4((int *)part, D_00551340) != 0) {
        func_001AACE0(D_005514B0, 0x22F, D_005514C0);
        func_00260380(D_005514B0, 0x22F, D_0062C238);
        D_0062A3B0 = 0;
        return 0;
    }

    want = (((size + 0xF) & 0xFFFFFFF0) + 0x40) >> 4;

    p = part->free_list;
    if (p != 0) {
        do {
            if (func_002613B4((int *)p, D_00551350) != 0) {
                debug_assertMessage(D_005514F0);
                if (p->prev != 0) {
                    debug_assertMessage(D_00551510, p->prev, p->prev->name);
                    debug_assertMessage(D_00551538, p->prev);
                }
                debug_assertMessage(D_00551550, p, p->name);
                debug_assertMessage(D_00551578, p);
                if (p->next != 0) {
                    debug_assertMessage(D_00551590, p->next, p->next->name);
                    debug_assertMessage(D_005515B8, p->next);
                }
                debug_assertMessage(D_005515D0, file, line);
                D_0062A3B0 = 0;
                func_001AAD00(D_005514B0, 0x253);
                func_00260380(D_005514B0, 0x253, D_0062C240);
                return 0;
            }
            if (p->size >= want) {
                best = p;
                p = p->free_next;
                n = 9;
                if (p != 0) {
                    do {
                        sz = p->size;
                        if (sz >= want) {
                            if (sz < best->size) {
                                best = p;
                            }
                        }
                        t = n;
                        p = p->free_next;
                        n--;
                        if (t <= 0) {
                            break;
                        }
                    } while (p != 0);
                }
                p = best;
                newnode = (IosMemNode *)((char *)p + (want << 4));
                *(IosMemTag *)newnode = *(IosMemTag *)D_00551350;
                newnode->prev = p;
                newnode->next = p->next;
                newnode->size = p->size - want;
                newnode->free_prev = p->free_prev;
                newnode->free_next = p->free_next;
                if (p->free_prev == 0) {
                    part->free_list = newnode;
                } else {
                    p->free_prev->free_next = newnode;
                }
                if (best->free_next != 0) {
                    best->free_next->free_prev = newnode;
                }
                if (best->next != 0) {
                    best->next->prev = newnode;
                }
                name = best->name;
                *(IosMemTag *)p = *(IosMemTag *)D_005515F0;
                func_00261900(name, (int)file, 0xF);
                if (func_0026160C(file) < 0x10) {
                    func_0026160C(file);
                }
                len = func_0026160C(name);
                while (len < 0xF) {
                    name[len] = ' ';
                    len++;
                }
                ret = (char *)best + 0x40;
                q = line / 10;
                v = line;
                dst = name;
                dst += 14;
                for (i = 3; i >= 0; i--) {
                    *dst = (v - q * 10) + 0x30;
                    dst--;
                    v = q;
                    q = v / 10;
                }
                best->part = part;
                best->line = line;
                best->next = newnode;
                best->size = want - 4;
                best->name[0xF] = 0;
                debug_assertMessage(D_00551600, best, best);
                debug_assertMessage(D_00551610, best->next, best->next);
                D_0062A3B0 = 0;
                return ret;
            }
            p = p->free_next;
        } while (p != 0);
    }

    debug_assertMessage(D_00551620, size);
    debug_assertMessage(D_005515D0, file, line);
    func_00261188(buf2, D_00551638, part->name, size,
                  func_00260340((float)size * 0.0009765625f * 0.0009765625f));
    func_001AACE0(file, line, buf2);
    __asm__ __volatile__("break");
    func_001AAD00(D_005514B0, 0x2C0);
    func_00260380(D_005514B0, 0x2C0, D_0062C240);
    D_0062A3B0 = 0;
    return 0;
}


extern int func_001007A0(int a0);

extern char D_00551688[];

void iosMallocCheckLeak(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    func_001007A0(0);
    iosMallocCheckLeak2(a0);
    debug_assertMessage(D_00551688, a1, a2, a0, end);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocCheckLeak2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosReallocDebug);

extern int func_00261900(char *dst, int src, int n);
extern char D_00551350[];
extern char D_00551430[];
extern char D_005515F0[];
extern char D_00551828[];
extern char D_00551840[];
extern char D_00551850[];
extern char D_00551860[];
extern char D_00551878[];
extern char D_006A04F0[];

void iosMallocInitPartition(int a0, int a1) {
    int node = *(int *)(a0 + a1 + 0x38);
    int r;

    debug_assertMessage(D_00551828, a0);
    if (node == 0) {
        return;
    }
    do {
            node += a1;
            func_00261900(D_006A04F0, node + 0x10, 0xF);
            D_006A04F0[0xF] = 0;
            r = func_002613B4((int *)node, D_005515F0);
            if (r == 0) {
                debug_assertMessage(D_00551840, node - a1, D_006A04F0);
                r = 0xB;
                goto delay;
            }
            r = func_002613B4((int *)node, D_00551350);
            if (r == 0) {
                debug_assertMessage(D_00551850, node - a1);
                r = 0xB;
                goto delay;
            }
            r = func_002613B4((int *)node, D_00551430);
            if (r != 0) {
                debug_assertMessage(D_00551878, node - a1, node);
                return;
            }
            debug_assertMessage(D_00551860);
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


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", func_00139B40);
