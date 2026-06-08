/* ito/include/mv_defs.h
 *
 * Reconstructed private header for the movie/MPEG playback code
 * (decomp/mv_defs_h.md). Included by the ito/mpeg TUs (mv_*) and by
 * common/GobjProc. The load-bearing artifact is the func_mvDeqMes inline
 * below: its deq_mes_th() call and assert are inlined verbatim into every
 * consumer, so the __FILE__/__LINE__ literals baked into .rodata pin these
 * exact line numbers (deq = line 42, assert = line 43). Keep the inline body
 * on its current lines. func_mvDeqMes is a reconstruction placeholder name
 * (inlined everywhere -> no MAIN.MAP symbol). The inline emits the exact
 * strings/lines but a consumer rewritten to call it does not yet byte-match
 * (open permuter-class $s1/$s2 regalloc swap -- see decomp/mv_defs_h.md).
 */
#ifndef MV_DEFS_H
#define MV_DEFS_H
#include "common.h"
#ifndef NULL
#define NULL 0
#endif
/* Shared movie message queue (global handle). */
extern int D_0062A340;

/* IOS debug-instrumented message dequeue; trailing args are __FILE__/__LINE__. */
extern int deq_mes_th(int queue, int size, int flags, const char *file, int line);

/* Assert primitives + message-bind helper (all in common/src/PObj.c). */
extern void func_001AAD00(const char *file, int line);
extern void func_00260380(const char *file, int line, const char *expr);
extern void func_00260568(int handle, int a1, int size);
/* assert(expr): report (__FILE__, __LINE__, "expr") on failure; binds here. */
#define MV_ASSERT(expr)                          \
    do {                                         \
        if (!(expr)) {                           \
            func_001AAD00(__FILE__, __LINE__);   \
            func_00260380(__FILE__, __LINE__, #expr); \
        }                                        \
    } while (0)

static __inline int func_mvDeqMes(int size)
{
    int p;
    p = deq_mes_th(D_0062A340, size, 0x40, __FILE__, __LINE__);
    MV_ASSERT(p != NULL);
    func_00260568(p, 0, size);
    return p;
}

#endif /* MV_DEFS_H */
