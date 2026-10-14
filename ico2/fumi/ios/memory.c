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

INCLUDE_ASM(iosMallocSetPartition);

INCLUDE_ASM(iosMallocResetPartition);

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

void iosMallocCheckLeak(IosMemPart *part)
{
    IosMemNode *node;
    IosMemNode *next;
    int found = 0;
    int i;
    int p;

    node = (IosMemNode *)part->start;
    while (node != 0) {
        if (strcmp(node->tag, "<ALLOC>________") != 0 &&
            strcmp(node->tag, "<FREE AREA>____") != 0 &&
            strcmp(node->tag, " free memory   ") != 0) {
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
            if (strcmp(node->tag, "<ALLOC>________") == 0) {
                debug_StdPrintfDummy("ALLOC ");
            } else if (strcmp(node->tag, "<FREE AREA>____") == 0) {
                debug_StdPrintfDummy("FREEAREA ");
            } else if (strcmp(node->tag, " free memory   ") == 0) {
                debug_StdPrintfDummy("DELETED_MEMORY ");
            } else {
                debug_StdPrintfDummy("!!! unrecognized memory block !!!\n");
                return;
            }
            debug_StdPrintfDummy("siz:$%5x ", node->size << 4);
            for (p = 0; p < 12; p++) {
                debug_StdPrintfDummy("%c", node->name[p]);
            }
            debug_StdPrintfDummy("\n");
            node = node->next;
        }
    }
}

void iosMallocCheckLeak2(int part, int offset)
{
    char *node = *(char **)(part + offset + 0x38);
    int i;

    debug_StdPrintfDummy("<<< check leak2 >>> %p\n", part);
    if (node == 0) {
        return;
    }
    do {
        node += offset;
        strncpy(nodeName, node + 16, 15);
        nodeName[15] = 0;
        if (strcmp(node, "<ALLOC>________") == 0) {
            debug_StdPrintfDummy("%p:ALLOC %s\n", node - offset, nodeName);
        } else if (strcmp(node, "<FREE AREA>____") == 0) {
            debug_StdPrintfDummy("%p:FREEAREA\n", node - offset);
        } else if (strcmp(node, " free memory   ") == 0) {
            debug_StdPrintfDummy("%p:DELETED_MEMORY\n");
        } else {
            debug_StdPrintfDummy("%p:!!! unrecognized block!!!:%s\n", node - offset, node);
            return;
        }
        for (i = 0; i < 12; i++) {}
        node = *(char *volatile *)(node + 0x24);
    } while (node != 0);
}

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

INCLUDE_ASM(iosMallocInitPartition);

INCLUDE_ASM(iosMallocAlignDebug);
