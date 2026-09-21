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
/* libgcc.a(_ctors.o)'s common lists, MAIN.MAP line 7656. */
extern func_ptr __CTOR_LIST__[];

void __do_global_dtors(void)
{
    while (*D_0054CBB8[0]) {
        D_0054CBB8[0]++;
        (*(D_0054CBB8[0] - 1))();
    }
}

/* libgcc2.c's __do_global_ctors is one line, the DO_GLOBAL_CTORS_BODY macro
   gbl-ctors.h defines, and that macro is written in the ordinary multi-statement
   `do { ... } while (0)` form. The wrapper is transcribed here because it is the
   member's source: it is also what puts the counter in $17 and the address in
   $16, since the extra loop level raises the loop depth flow.c weights the two
   allocnos' reference counts by and carries the address register's count across
   a floor_log2 step in allocno_compare. */
void __do_global_ctors(void)
{
    do {
        unsigned long nptrs = (unsigned long)__CTOR_LIST__[0];
        unsigned i;

        if (nptrs == (unsigned long)-1)
            for (nptrs = 0; __CTOR_LIST__[nptrs + 1] != 0; nptrs++)
                ;
        for (i = nptrs; i >= 1; i--)
            __CTOR_LIST__[i]();
    } while (0);
}

extern void __do_global_ctors();
extern int D_00736168[];

void __main(void)
{
    if (D_00736168[0] == 0) {
        D_00736168[0] = 1;
        __do_global_ctors();
    }
}
