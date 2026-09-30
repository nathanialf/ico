/* libgcc.a member _ctors.o: libgcc2.c built with L_ctors, no code, the two
 * empty constructor and destructor lists __main.o walks (MAIN.MAP lines 522,
 * 681-683, 7654: .scommon 0x10). Uninitialised, they are common symbols, and
 * the linker gives common symbols no larger than its -G the small common
 * section, so they sit in .sbss after every object's own .sbss. */
#include "libgcc2.h"

typedef void (*func_ptr)(void);

/* Provide default definitions for the lists of constructors and
   destructors, so that we don't get linker errors.  These symbols are
   intentionally bss symbols, so that gld and/or collect will provide
   the right values.  */

/* We declare the lists here with two elements each,
   so that they are valid empty lists if no other definition is loaded.  */
func_ptr __CTOR_LIST__[2];

func_ptr __DTOR_LIST__[2];
