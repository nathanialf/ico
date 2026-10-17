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

INCLUDE_ASM(iosMallocSetPartitionName);

INCLUDE_ASM(iosMallocClearPartition);

/* set while an allocation is in progress, which the re-entry check tests;
   ahead of iosMallocDebug's strings in the demo's .sdata */
static int mallocBusy = 0; /* derived name */

INCLUDE_ASM(iosMallocDebug);

/* the file and line of the allocation in progress, which the re-entry check
   prints */
static const char *mallocFile; /* derived name */

static int mallocLine; /* derived name */

static void *_iosMallocDebug(IosMemPart *part, int size, const char *file, int line);

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

INCLUDE_ASM(iosMallocInitPartition);

INCLUDE_ASM(iosMallocAlignDebug);
