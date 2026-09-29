/* The period toolchain (ee-gcc 2.9-991111's driver, cpp/cc1 and ee-as, and
 * SCE's 2.10 assembler) is 32-bit Linux code that takes obstack from the
 * host's libc.  Asked for a default-sized chunk (size 0), glibc of the time
 * gave 4096 minus malloc's overhead rounded to 8 bytes, 4072; glibc since
 * 2.28 rounds to 16 and gives 4064.  ee-as's R5900 short-loop padding counts
 * to the end of an obstack-backed frag, so the chunk size decides where its
 * padding nops land.  Preloaded into those tools, this restores the chunk
 * size the original build machine had. */
#include <stddef.h>

extern void *dlsym(void *, const char *);
#define RTLD_NEXT ((void *)-1l)

typedef int (*obstack_begin_fn)(void *, size_t, size_t, void *, void *);

int _obstack_begin(void *h, size_t size, size_t alignment, void *chunkfun, void *freefun)
{
    static obstack_begin_fn next;

    if (next == 0)
        next = (obstack_begin_fn)dlsym(RTLD_NEXT, "_obstack_begin");
    if (size == 0)
        size = 4072;
    return next(h, size, alignment, chunkfun, freefun);
}
