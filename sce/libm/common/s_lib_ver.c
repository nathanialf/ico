/* libm.a member s_lib_ver.o: no code, one read-only word, the global
 * __fdlib_version (math.h's _LIB_VERSION) at the member's .rodata offset 0
 * (MAIN.MAP lines 504, 6753-6754).  The ROM word is 1, __fdlibm_xopen: the
 * X/Open error-handling mode. */
#include <math.h>

const _LIB_VERSION_TYPE _LIB_VERSION = _XOPEN_;
