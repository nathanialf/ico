/* libgcc.a member __main.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "libgcc2.h"

typedef void (*func_ptr)(void);
/* libgcc2.c's DO_GLOBAL_DTORS_BODY: the cursor is this member's own file
   static, initialised to __DTOR_LIST__ + 1, and it lives at 0x0054CBB8. */
extern func_ptr *D_0054CBB8[]; /* one pointer; spelled as an array so the
                                  reference is not gp-relative, as in the
                                  shipped member */
/* __CTOR_LIST__ */
extern func_ptr D_0063C5C8[];

void __do_global_dtors(void)
{
    while (*D_0054CBB8[0]) {
        D_0054CBB8[0]++;
        (*(D_0054CBB8[0] - 1))();
    }
}

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
