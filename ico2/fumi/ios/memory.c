#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include <eekernel.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "include_asm.h"

typedef struct IosMemTag { /* field names derived */
    char c[16];
} IosMemTag; /* derived name */

/* the node name the heap walk copies out before printing it */
/* */
static char nodeName[32]; /* derived name */

inline IosMemPart *iosMallocInitPartition(unsigned int start, unsigned int end)
{
    IosMemPart *part;
    IosMemNode *node;
    unsigned int top;

    part = (IosMemPart *)((start + 0xF) & 0xFFFFFFF0);
    top = (end + 1) & 0xFFFFFFF0;

    if (top - (unsigned int)part < 160) {
        debug_StdPrintfDummy("mem:partition size too small\n");
        return 0;
    }

    *(IosMemTag *)part = *(IosMemTag *)"<PARTITION>____";

    part->parent = 0;
    part->next = 0;
    part->child = 0;

    part->start = (char *)(node = (IosMemNode *)((char *)part + 80));
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
    if (strcmp(part->tag, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return 0;
    }
    avail = part->free - 5;
    need = (((size + 0xF) & 0xFFFFFFF0) + 144) >> 4;
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
    base->parent = part;
    if (part->child != 0) {
        base->next = part->child;
    }
    part->nused = part->nused + 1;
    part->top = (char *)base;
    part->free = part->free - need;
    part->child = base;
    part->head->size = part->head->size - need;
    return base;
}

IosMemPart *iosMallocResetPartition(IosMemPart *part)
{
    IosMemNode *node;
    IosMemPart *parent;
    IosMemPart *next;
    IosMemPart *child;

    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return 0;
    }
    if (strcmp(part->tag, "<PARTITION>____") != 0) {
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
    parent = part->parent;
    next = part->next;
    child = part->child;
    iosMallocInitPartition((unsigned int)part, (unsigned int)part->end);
    part->parent = parent;
    part->next = next;
    part->child = child;
    return part;
}

int iosMallocSetPartitionName(IosMemPart *part, char *name)
{
    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return 0;
    }
    if (strcmp(part->tag, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return 0;
    }
    strcpy(part->name, name);
}

void iosMallocClearPartition(IosMemPart *part)
{
    IosMemPart *child;

    if (part == 0) {
        debug_StdPrintfDummy("mem:null partition pointer\n");
        return;
    }
    if (strcmp(part->tag, "<PARTITION>____") != 0) {
        debug_StdPrintfDummy("mem:illegal partition pointer\n");
        return;
    }
    if (part->parent != 0 && part != part->parent->child) {
        debug_StdPrintfDummy("mem:not last partition\n");
        return;
    }
    if (part->child != 0) {
        child = part->child;
        while (child != part) {
            if (child->child != 0) {
                child = child->child;
            } else if (strcmp(child->tag, "<PARTITION>____") != 0) {
                debug_StdPrintfDummy("mem:illegal partition pointer\n");
                return;
            } else {
                *(IosMemTag *)child = *(IosMemTag *)" del partition ";
                if (child->next == 0) {
                    child->parent->child = 0;
                    child = child->parent;
                } else {
                    child = child->next;
                }
            }
        }
    }
    if (part->parent != 0) {
        part->parent->child = part->next;
        part->parent->top = part->end;
        part->parent->free = (unsigned int)(part->end - part->parent->start) >> 4;
    }
    *(IosMemTag *)part = *(IosMemTag *)" del partition ";
}

/* set while an allocation is in progress, which the re-entry check tests */
static int mallocBusy = 0; /* derived name */

/* the file and line of the allocation in progress, which the re-entry check
   prints */
static const char *mallocFile; /* derived name */

static int mallocLine; /* derived name */

static void *_iosMallocDebug(IosMemPart *part, int size, const char *file, int line);

INCLUDE_ASM(iosMallocDebug);

inline void *iosMallocAlignDebug(IosMemPart *part, int size, int align, const char *file, int line)
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

void _iosFreeWithFill(int *ptr, char *file, int line)
{
    int *end = *(int **)((char *)ptr - 0x1C);
    FlushCache(0);
    iosFree(ptr);
    debug_StdPrintfDummy("IOSFILLFREE %s(%d) %p - %p\n", file, line, ptr, end);
    {
        register int g = (unsigned int)ptr < (unsigned int)end;
        if (g) {
            do {
                *(unsigned int *)ptr = 0xFFFFFFFFu;
                ptr++;
            } while ((unsigned int)ptr < (unsigned int)end);
        }
    }
    FlushCache(0);
}

INCLUDE_ASM(iosFree);

INCLUDE_ASM(iosMallocCheckLeak);

INCLUDE_ASM(iosMallocCheckLeak2);

/* the 0x3C-byte node record realloc moves: everything up to the line number */
typedef struct IosMemNodeRec {    /* field names derived */
    char tag[16];                 /* 0x00 */
    char name[16];                /* 0x10 */
    struct IosMemNode *prev;      /* 0x20 */
    struct IosMemNode *next;      /* 0x24 */
    struct IosMemNode *free_prev; /* 0x28 */
    struct IosMemNode *free_next; /* 0x2C */
    struct IosMemPart *part;      /* 0x30 */
    int size;                     /* 0x34 */
    int line;                     /* 0x38 */
} IosMemNodeRec;                  /* derived name */

INCLUDE_ASM(iosReallocDebug);
