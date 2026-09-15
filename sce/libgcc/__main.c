/* libgcc.a member __main.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
    unsigned long long f10;
} PCmpV2;

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/__main", __do_global_dtors);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/__main", __do_global_ctors);

extern void __do_global_ctors();
extern int D_00736168[];

void __main(void)
{
    if (D_00736168[0] == 0) {
        D_00736168[0] = 1;
        __do_global_ctors();
    }
}
