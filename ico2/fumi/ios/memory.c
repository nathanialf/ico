#include "common.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include <eekernel.h>
#include <stdlib.h>
#include <stdio.h>

/* kept local: the TUs that call iosMallocDebugNoAssert declare it themselves; it
   passes its four arguments straight through to _iosMallocDebug. */
void *iosMallocDebugNoAssert(IosMemPart *part, int size, char *file, int line);

typedef struct IosMemTag {
    char c[16];
} IosMemTag;

typedef struct IosMemNode {
    char tag[16];                 /* 0x00 */
    char name[16];                /* 0x10 */
    struct IosMemNode *prev;      /* 0x20 */
    struct IosMemNode *next;      /* 0x24 */
    struct IosMemNode *free_prev; /* 0x28 */
    struct IosMemNode *free_next; /* 0x2C */
    struct IosMemPart *part;      /* 0x30 */
    int size;                     /* 0x34 */
    int line;                     /* 0x38 */
    int pad3C;                    /* 0x3C */
    struct IosMemNode *pad40;     /* 0x40 (partition header view) */
    struct IosMemNode *head;      /* 0x44 (partition header view: free-list head) */
} IosMemNode;

extern int strcmp(int *a0, const char *a1);
extern void strcpy(unsigned char *ptr, int value);
extern char D_0063A4E0[];
extern char D_0063A4F0[];
extern void __assert(char *file, int line, char *expr);
extern int strncmp(void *a0, void *a1, int a2);

/* .bss, owned by memory.o (MAIN.MAP sizes the run 0x20 and names no
   symbol in it): the node name the heap walk copies out before printing it. */
/* */
static char nodeName[32];

extern int strncpy(char *dst, int src, int n);
extern char D_0063A4E8[];

inline IosMemPart *iosMallocInitPartition(unsigned int start, unsigned int end)
{
    IosMemPart *part;
    IosMemNode *node;
    unsigned int top;

    part = (IosMemPart *)((start + 0xF) & 0xFFFFFFF0);
    top = (end + 1) & 0xFFFFFFF0;

    if (top - (unsigned int)part < 0xA0) {
        debug_StdPrintfDummy("mem:partition size too small\n");
        return 0;
    }

    *(IosMemTag *)part = *(IosMemTag *)"<PARTITION>____";

    part->prev = 0;
    part->next = 0;
    part->parent = 0;

    part->start = (char *)(node = (IosMemNode *)((char *)part + 0x50));
    part->end = (char *)top;
    part->total = (top - (unsigned int)node) >> 4;

    part->nused = 0;
    part->top = (char *)top;
    part->free = (top - (unsigned int)node) >> 4;

    part->head = node;

    *(IosMemTag *)node = *(IosMemTag *)"<FREE AREA>____";
    node->prev = 0;
    node->next = 0;
    node->free_prev = 0;
    node->free_next = 0;
    node->size = part->free - 4;

    debug_StdPrintfDummy("mem:init partition 0x%08x - 0x%08x\n", part->start, part->end - 1);
    return part;
}

IosMemPart *iosMallocSetPartition(IosMemPart *part, int size, int align)
{
    IosMemPart *base;
    int avail;
    int need;

    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return 0;
    }
    if (strcmp((int *)part, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return 0;
    }
    avail = part->free - 5;
    need = (((size + 0xF) & 0xFFFFFFF0) + 0x90) >> 4;
    if (avail < need) {
        debug_StdPrintfDummy("mem: memory lack %dqw > parent:%dqw\n", need, avail);
        return 0;
    }
    base = (IosMemPart *)(part->top - (need << 4));
    debug_StdPrintfDummy("mem:set partition 0x%08x\n", base);
    if (iosMallocInitPartition((unsigned int)base, (unsigned int)part->top - 1) == 0) {
        debug_StdPrintfDummy("mem:fail init partition\n");
        return 0;
    }
    base->prev = part;
    if (part->parent != 0) {
        base->next = part->parent;
    }
    part->nused = part->nused + 1;
    part->top = (char *)base;
    part->free = part->free - need;
    part->parent = base;
    part->head->size = part->head->size - need;
    return base;
}

IosMemPart *iosMallocResetPartition(IosMemPart *part)
{
    IosMemNode *node;
    IosMemPart *prev;
    IosMemPart *next;
    IosMemPart *parent;

    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return 0;
    }
    if (strcmp((int *)part, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return 0;
    }
    node = (IosMemNode *)part->start;
    if (node != 0) {
        do {
            *(IosMemTag *)node = *(IosMemTag *)" free memory   ";
            node = node->next;
        } while (node != 0);
    }
    prev = part->prev;
    next = part->next;
    parent = part->parent;
    iosMallocInitPartition((unsigned int)part, (unsigned int)part->end);
    part->prev = prev;
    part->next = next;
    part->parent = parent;
    return part;
}

int iosMallocSetPartitionName(int *a0, int a1)
{
    if (a0 == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return 0;
    }
    if (strcmp(a0, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return 0;
    }
    strcpy((unsigned char *)((char *)a0 + 0x10), a1);
}

void iosMallocClearPartition(IosMemPart *part)
{
    IosMemPart *child;

    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return;
    }
    if (strcmp((int *)part, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return;
    }
    if (part->prev != 0 && part != part->prev->parent) {
        debug_StdPrintfDummy("mem:not last partition\n");
        return;
    }
    if (part->parent != 0) {
        child = part->parent;
        while (child != part) {
            if (child->parent != 0) {
                child = child->parent;
            } else if (strcmp((int *)child, "<PARTITION>____") != 0) {
                debug_StdPrintfDummy("mem:illegal partition pointer\n");
                return;
            } else {
                *(IosMemTag *)child = *(IosMemTag *)" del partition ";
                if (child->next == 0) {
                    child->prev->parent = 0;
                    child = child->prev;
                } else {
                    child = child->next;
                }
            }
        }
    }
    if (part->prev != 0) {
        part->prev->parent = part->next;
        part->prev->top = part->end;
        part->prev->free = (unsigned int)(part->end - part->prev->start) >> 4;
    }
    *(IosMemTag *)part = *(IosMemTag *)" del partition ";
}

extern int D_0063A4D8;

/* .sbss, memory.o's two words in the ROM's order (MAIN.MAP line 7583 sizes
   the run 8 and names no symbol in it, so the names are ours): the file and
   line of the allocation in progress, which the re-entry check prints. */
static char *mallocFile;

static int mallocLine;

extern unsigned int strlen(char *s);

void *_iosMallocDebug(IosMemPart *part, int size, char *file, int line)
{
    char buf[1024];
    /* the 16 bytes between buf and the register saves: SRCFILE.TXT gives
       memory.c rows 529-539 no instructions at all, and the ROM's frame is
       0x4B0 where buf plus the ten saved doublewords account for only 0x4A0 */
    char tag[16];
    IosMemNode *node;
    IosMemNode *best;
    IosMemNode *newnode;
    char *name;
    int need;
    int i;
    int len;
    int v;
    int q;
    int n;

    if (D_0063A4D8 != 0) {
        sprintf(buf, "MALLOC: REENTER FOR PARTITION \"%s\" SIZE %d\nBEFORE FILE %s LINE %d",
                part->name, size, mallocFile, mallocLine);
        debug_assertMessage(file, line, buf);
    }
    D_0063A4D8 = 1;
    mallocFile = file;
    mallocLine = line;
    if (part == 0) {
        debug_assertMessage(__FILE__, 555, "IOSMALLOC():\nNULL PARTITION POINTER AT MALLOC\n");
        __assert(__FILE__, 555, D_0063A4E0);
        D_0063A4D8 = 0;
        return 0;
    }
    if (strcmp((int *)part, "<PARTITION>____") != 0) {
        debug_assertMessage(__FILE__, 562, "IOSMALLOC():\nNULL PARTITION POINTER AT MALLOC\n");
        __assert(__FILE__, 562, D_0063A4E0);
        D_0063A4D8 = 0;
        return 0;
    }
    need = (((size + 0xF) & 0xFFFFFFF0) + 0x40) >> 4;
    for (node = part->head; node != 0; node = node->free_next) {
        if (strcmp((int *)node, "<FREE AREA>____") != 0) {
            debug_StdPrintfDummy("mem:illegal free area pointer\n");
            if (node->prev != 0) {
                debug_StdPrintfDummy("mem: prev block, %08x called at %s\n", node->prev,
                                     node->prev->name);
                debug_StdPrintfDummy("mem:prev magic %s\n", node->prev);
            }
            debug_StdPrintfDummy("mem:cur block, %08x called at %s\n", node, node->name);
            debug_StdPrintfDummy("mem:cur magic %s\n", node);
            if (node->next != 0) {
                debug_StdPrintfDummy("mem: next block, %08x called at %s\n", node->next,
                                     node->next->name);
                debug_StdPrintfDummy("mem:next magic %s\n", node->next);
            }
            debug_StdPrintfDummy("mem:called by %s of line %d\n", file, line);
            D_0063A4D8 = 0;
            debug_assert(__FILE__, 598);
            __assert(__FILE__, 598, D_0063A4E8);
            return 0;
        }
        if (node->size >= need) {
            best = node;
            node = node->free_next;
            if (node != 0) {
                n = 9;
                do {
                    if (node->size >= need && node->size < best->size) {
                        best = node;
                    }
                    node = node->free_next;
                } while (n-- > 0 && node != 0);
            }
            node = best;
            newnode = (IosMemNode *)((char *)node + (need << 4));
            *(IosMemTag *)newnode = *(IosMemTag *)"<FREE AREA>____";
            newnode->prev = node;
            newnode->next = node->next;
            newnode->free_prev = node->free_prev;
            newnode->free_next = node->free_next;
            newnode->size = node->size - need;
            if (node->free_prev == 0) {
                part->head = newnode;
            } else {
                node->free_prev->free_next = newnode;
            }
            if (best->free_next != 0) {
                best->free_next->free_prev = newnode;
            }
            if (best->next != 0) {
                best->next->prev = newnode;
            }
            *(IosMemTag *)node = *(IosMemTag *)"<ALLOC>________";
            name = best->name;
            strncpy(name, (int)file, 15);
            if (strlen(file) < 16) {
                len = strlen(file);
            }
            for (len = strlen(name); len < 15; len++) {
                name[len] = ' ';
            }
            v = line;
            q = v / 10;
            /* the subscript through best->name (not name + i + 11): the array
               reference computes i + 11 first, so loop.c strength-reduces the
               store address to the ROM's pointer off name + 14 and keeps i as
               the counter */
            for (i = 3; i >= 0; i--) {
                best->name[i + 11] = v - q * 10 + '0';
                v = q;
                q = v / 10;
            }
            best->part = part;
            best->line = line;
            best->next = newnode;
            best->size = need - 4;
            best->name[15] = 0;
            debug_StdPrintfDummy("cur: %8p %s\n", best, best);
            debug_StdPrintfDummy("next:%8p %s\n", best->next, best->next);
            D_0063A4D8 = 0;
            return (char *)best + 0x40;
        }
    }
    D_0063A4D8 = 0;
    return 0;
}

inline void *iosMallocDebug(IosMemPart *part, int size, char *file, int line)
{
    char buf[1024];
    void *ptr;

    ptr = _iosMallocDebug(part, size, file, line);
    if (ptr == 0) {
        debug_StdPrintfDummy("mem:no memory for %d\n", size);
        debug_StdPrintfDummy("mem:called by %s of line %d\n", file, line);
        sprintf(buf, "MALLOC: NO EMEMORY FOR PARTITION \"%s\"\nSIZE %d BYTES (%1.1fM)\n",
                part->name, size, (float)size / 1024.0f / 1024.0f);
        debug_assertMessage(file, line, buf);
        __asm__ __volatile__("break");
        debug_assert(__FILE__, 716);
        __assert(__FILE__, 716, D_0063A4E8);
    }
    return ptr;
}

inline void *iosMallocDebugNoAssert(IosMemPart *part, int size, char *file, int line)
{
    return _iosMallocDebug(part, size, file, line);
}

void *iosMallocAlignDebug(IosMemPart *part, int size, int align, char *file, int line)
{
    unsigned int ptr;
    int ofs;

    if (align <= 16) {
        return iosMallocDebug(part, size, file, line);
    }
    align = (align + 15) / 16 * 16;
    size += align - 16;
    ptr = (unsigned int)iosMallocDebug(part, size, file, line);
    if (ptr % align != 0) {
        ofs = align - ptr % align;
        ptr = ptr + ofs;
        sprintf((char *)ptr - 16, "align%05d", ofs);
    }
    return (void *)ptr;
}

void _iosFreeWithFill(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *)a0 - 0x1C);
    FlushCache(0);
    iosFree((void *)a0);
    debug_StdPrintfDummy("IOSFILLFREE %s(%d) %p - %p\n", a1, a2, a0, end);
    {
        register int g = (unsigned int)a0 < (unsigned int)end;
        if (g) {
            do {
                *(unsigned int *)a0 = 0xFFFFFFFFu;
                a0++;
            } while ((unsigned int)a0 < (unsigned int)end);
        }
    }
    FlushCache(0);
}

void *iosFree(void *ptr)
{
    char buf[1024];
    IosMemNode *node;
    IosMemNode *next;
    IosMemNode *prev;
    IosMemNode *fn;
    int n;

    debug_StdPrintfDummy("mem:free ");
    if (ptr == 0) {
        debug_StdPrintfDummy("null memory pointer\n");
        __asm__ __volatile__("break");
        debug_assertMessage(__FILE__, 820, "IOSFREE(): NULL MEMORY POINTER\n");
        __assert(__FILE__, 820, D_0063A4E0);
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
    if (strcmp((int *)node, "<ALLOC>________") != 0) {
        sprintf(buf, "IOSFREE():\n\tPREV MAGIC: %s\n\t CUR MAGIC: %s\n\tNEXT MAGIC: %s\n",
                node->prev, node, node->next);
        debug_assertMessage(__FILE__, 836, buf);
        __assert(__FILE__, 836, D_0063A4E0);
        return 0;
    }
    next = node->next;
    prev = node->prev;
    if (prev != 0) {
        if (strcmp((int *)prev, "<FREE AREA>____") == 0) {
            if (next != 0) {
                if (strcmp((int *)next, "<FREE AREA>____") == 0) {
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
                    *(IosMemTag *)next = *(IosMemTag *)" free memory0  ";
                    if (next->next != 0) {
                        next->next->prev = prev;
                    }
                } else if (strcmp((int *)next, "<ALLOC>________") == 0) {
                    prev->next = next;
                    next->prev = prev;
                } else {
                    debug_assertMessage(__FILE__, 905, "IOSFREE(): MEMORY LINK MISS\n");
                    __assert(__FILE__, 905, D_0063A4E0);
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
            *(IosMemTag *)node = *(IosMemTag *)" free memory1  ";
            goto ret_ptr;
        }
        if (strcmp((int *)prev, "<ALLOC>________") != 0) {
            goto err_3bf;
        }
    }
    if (next == 0) {
        goto tail_node;
    }
    if (strcmp((int *)next, "<ALLOC>________") == 0) {
        node->free_prev = 0;
        node->free_next = ((IosMemNode *)node->part)->head;
        ((IosMemNode *)node->part)->head = node;
        if (node->free_next != 0) {
            node->free_next->free_prev = node;
        }
        goto tag_free;
    }
    if (strcmp((int *)next, "<FREE AREA>____") != 0) {
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
    *(IosMemTag *)next = *(IosMemTag *)" free memory2  ";
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
    debug_assertMessage(__FILE__, 962, "IOSFREE(): ALLOC NULL\n");
    __assert(__FILE__, 962, D_0063A4E0);
    goto tag_free;
err_3b5:
    debug_assertMessage(__FILE__, 965, "IOSFREE(): MEMORY LINK MISS\n");
    __assert(__FILE__, 965, D_0063A4E0);
    return 0;
tag_free:
    *(IosMemTag *)node = *(IosMemTag *)"<FREE AREA>____";
    goto ret_ptr;
err_3bf:
    debug_assertMessage(__FILE__, 975, "IOSFREE(): ??\n");
    __assert(__FILE__, 975, D_0063A4E0);
ret_ptr:
    return ptr;
}

extern char D_0063A4F8[];
extern char D_0063A500[];
extern char D_0063A508[];

void iosMallocCheckLeak(IosMemPart *part)
{
    IosMemNode *node;
    IosMemNode *next;
    int found = 0;
    int i;
    int p;

    node = (IosMemNode *)part->start;
    while (node != 0) {
        if (strcmp((int *)node, "<ALLOC>________") != 0 &&
            strcmp((int *)node, "<FREE AREA>____") != 0 &&
            strcmp((int *)node, " free memory   ") != 0) {
            debug_StdPrintfDummy("magic broken :%p\n", node);
            found = 1;
            break;
        }
        next = node->next;
        for (i = 0; i < 12; i++) {}
        node = next;
    }
    if (found == 1) {
        node = (IosMemNode *)part->start;
        while (node != 0) {
            debug_StdPrintfDummy("mem:addr:$%08x ", node);
            if (strcmp((int *)node, "<ALLOC>________") == 0) {
                debug_StdPrintfDummy(D_0063A4F8);
            } else if (strcmp((int *)node, "<FREE AREA>____") == 0) {
                debug_StdPrintfDummy("FREEAREA ");
            } else if (strcmp((int *)node, " free memory   ") == 0) {
                debug_StdPrintfDummy("DELETED_MEMORY ");
            } else {
                debug_StdPrintfDummy("!!! unrecognized memory block !!!\n");
                return;
            }
            debug_StdPrintfDummy("siz:$%5x ", node->size << 4);
            for (p = 0; p < 12; p++) {
                debug_StdPrintfDummy(D_0063A500, node->name[p]);
            }
            debug_StdPrintfDummy(D_0063A508);
            node = node->next;
        }
    }
}

void iosMallocCheckLeak2(int a0, int a1)
{
    int node = *(int *)(a0 + a1 + 0x38);
    int i;

    debug_StdPrintfDummy("<<< check leak2 >>> %p\n", a0);
    if (node == 0) {
        return;
    }
    do {
        node += a1;
        strncpy(nodeName, node + 0x10, 0xF);
        nodeName[0xF] = 0;
        if (strcmp((int *)node, "<ALLOC>________") == 0) {
            debug_StdPrintfDummy("%p:ALLOC %s\n", node - a1, nodeName);
        } else if (strcmp((int *)node, "<FREE AREA>____") == 0) {
            debug_StdPrintfDummy("%p:FREEAREA\n", node - a1);
        } else if (strcmp((int *)node, " free memory   ") == 0) {
            debug_StdPrintfDummy("%p:DELETED_MEMORY\n");
        } else {
            debug_StdPrintfDummy("%p:!!! unrecognized block!!!:%s\n", node - a1, node);
            return;
        }
        for (i = 0; i < 12; i++) {}
        node = *(volatile int *)(node + 0x24);
    } while (node != 0);
}

/* the 0x3C-byte node record realloc moves: everything up to the line number,
   which is the seven ldl/ldr pairs plus the trailing word the ROM emits */
typedef struct IosMemNodeRec {
    char tag[16];                 /* 0x00 */
    char name[16];                /* 0x10 */
    struct IosMemNode *prev;      /* 0x20 */
    struct IosMemNode *next;      /* 0x24 */
    struct IosMemNode *free_prev; /* 0x28 */
    struct IosMemNode *free_next; /* 0x2C */
    struct IosMemPart *part;      /* 0x30 */
    int size;                     /* 0x34 */
    int line;                     /* 0x38 */
} IosMemNodeRec;

void *iosReallocDebug(void *ptr, unsigned int size)
{
    char buf[1024];
    IosMemNode *node;
    IosMemNode *nd;
    IosMemNode *p;
    IosMemNode *prev;
    IosMemNode *next;
    int n;
    int d;

    if (ptr == 0) {
        debug_assertMessage(__FILE__, 1182, "IOSREALLOC():\nNULL MEMORY POINTER AT MALLOC\n");
        __assert(__FILE__, 1182, D_0063A4E0);
        return 0;
    }
    next = ptr;
    prev = (IosMemNode *)((char *)ptr - 0x10);
    if (strncmp(prev, D_0063A4F0, 5) == 0) {
        n = atoi((char *)ptr - 0xB);
        next = (IosMemNode *)((char *)prev - (n - 0x10));
        *((char *)ptr - 0x10) = 0;
    }
    node = (IosMemNode *)((char *)next - 0x40);
    if (strcmp((int *)node, "<ALLOC>________") != 0) {
        sprintf(buf, "IOSFREE():\n\tPREV MAGIC: %s\n\t CUR MAGIC: %s\n\tNEXT MAGIC: %s\n",
                node->prev, node, node->next);
        debug_assertMessage(__FILE__, 1199, buf);
        __assert(__FILE__, 1199, D_0063A4E0);
        return 0;
    }
    nd = node->next;
    if (strcmp((int *)nd, "<FREE AREA>____") != 0) {
        debug_StdPrintfDummy("mem:realloc; not support yet\n");
        __asm__ __volatile__("break");
        return 0;
    }
    n = (size + 0xF) >> 4;
    if (node->size - 0x40 < n) {
        debug_StdPrintfDummy("mem:realloc; not enough memory\n");
        __asm__ __volatile__("break");
        return 0;
    }
    d = node->size - n;
    p = (IosMemNode *)((char *)ptr + (n << 4));
    *(IosMemNodeRec *)p = *(IosMemNodeRec *)nd;
    node->size = node->size - d;
    p->size = p->size + d;
    *(IosMemTag *)nd = *(IosMemTag *)" free memory   ";
    node->next = p;
    if (p->next != 0) {
        p->next->prev = p;
    }
    if (p->free_prev != 0) {
        p->free_prev->free_next = p;
    } else {
        ((IosMemNode *)node->part)->head = p;
    }
    if (p->free_next != 0) {
        p->free_next->free_prev = p;
    }
    return ptr;
}
