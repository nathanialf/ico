/*
 * sce/libc/assert.h
 *
 * The assert macro and the __assert entry point it calls, under the public
 * name of the newlib header for them (assert.h).  __assert is the signature
 * of the member that defines it in sce/ (stdlib/assert.c).  Like newlib's,
 * the header has no include guard: assert follows NDEBUG at each inclusion.
 */
#undef assert

#ifdef NDEBUG
#define assert(e) ((void)0)
#else
#define assert(e) ((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
#endif

void __assert(const char *file, int line, const char *failedexpr); /* definition in sce/ */
