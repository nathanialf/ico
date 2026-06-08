/* ito/include/mv_defs.h
 *
 * Reconstructed private header for the movie/MPEG playback code
 * (decomp/mv_defs_h.md). Included by the ito/mpeg TUs (mv_*) and by
 * common/GobjProc. The load-bearing artifact is the deq_movie_mes inline
 * below: its deq_mes_th() call and assert are inlined verbatim into every
 * consumer, so the __FILE__/__LINE__ literals baked into .rodata pin these
 * exact line numbers -- deq MUST stay on line 42, the assert on line 43.
 * deq_movie_mes is a reconstruction name: the function is inlined everywhere,
 * so it has no VMA / MAIN.MAP symbol. We know it exists because the identical
 * block (deq_mes_th with line 42 in the jal delay, then the assert with line 43
 * twice) appears inlined in 5 functions across 4 .c files -- termAll (mv_main),
 * readBufBeginGet (mv_readbuf), voBufDelete (mv_vobuf), func_00239E18 (mv_sub)
 * and func_0023BE80 (GobjProc). A constant __FILE__/__LINE__ across separate
 * .c files can only come from shared inlined header code.
 *
 * Capturing __FILE__ into `fp` before the deq is LOAD-BEARING: it makes ee-gcc
 * allocate the struct param to $s1 and the file pointer to $s2 (matching the
 * ROM). Without it the inliner swaps them and the consumer fails to match.
 *
 * The carved .rodata (file string + "p != NULL") for each consuming TU is
 * owned by that TU's .o; ee-gcc 2.9 does no cross-.o string dedup, so each
 * TU emits its own copy -- which is what makes the data per-TU attributable.
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
static __inline int deq_movie_mes(int size)
{
    int p; const char *fp = __FILE__;
    p = deq_mes_th(D_0062A340, size, 0x40, fp, __LINE__);
    if (p == NULL) { func_001AAD00(fp, __LINE__); func_00260380(fp, __LINE__, "p != NULL"); }
    func_00260568(p, 0, size);
    return p;
}
#endif /* MV_DEFS_H */
