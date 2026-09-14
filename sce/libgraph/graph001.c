/* libgraph.a member graph001.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/sce/libgraph/graph001", sceGsResetGraph);

extern int D_0054A2B0[];

void *sceGsGetGParam(void)
{
    return D_0054A2B0;
}

extern void *sceGsGetGParam(void);
