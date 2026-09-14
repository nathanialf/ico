/*
 * ito/include/mv_defs.h - the `ito` programmer's movie/MPEG private header.
 *
 * PROVENANCE. baserom/pal/SRCFILE.TXT attributes instructions inside 16
 * functions across 6 ito/mpeg TUs to `ito/include/mv_defs.h`, plus three
 * out-of-line copies of `Free` (mv_videodec 0x001A6F80, mv_vobuf 0x001A7318,
 * mv_vibuf 0x0025A4A8). Census rows: decomp/pal_source_tree.md, section
 * `ito/../ito/include/mv_defs.h`. Earlier analysis of the same header on the
 * Aug-2001 prototype: decomp/mv_defs_h.md (that build's helper at these lines
 * dequeued a message; the 2002 PAL build's allocates - re-derived below).
 *
 * LINE NUMBERS ARE LOAD-BEARING; DO NOT REFLOW THIS FILE. The line-42 helper
 * bakes __FILE__/__LINE__ into .rodata and the ROM's immediates are 0x2B (43)
 * for the alloc call and 0x2C (44) for the assert; the strings it references
 * are "../ito/include/mv_defs.h" (D_005576A8) and "p != NULL" (D_005576C8).
 * For __FILE__ to come out as that path a consuming TU must be listed in
 * config/include_ito.txt, which makes tools/compile_c.sh build it from CWD
 * ${ROOT}/ito with a relative -I../ito/include. That is why this header lives
 * under ito/include/ and not in include/ with the others.
 *
 * `Free` is the developer's own name, read out of the local symbol table of
 * the binary we build against (a file-static, hence absent from MAIN.MAP).
 * Every other name here is OURS - inlined everywhere, so no symbol at all.
 */
#ifndef MV_DEFS_H
#define MV_DEFS_H

/* lines 30-31 - PROVEN: factored out of 4 matched hosts (Free/mv_videodec,
   func_001A7318/mv_vobuf, func_0025A4A8/mv_vibuf, loadImage/mv_disp). */
static __inline__ int phys_addr(int p)
{ return p & 0x0FFFFFFF; }

/* lines 35-36 - RECONSTRUCTION (7 census hosts, all still INCLUDE_ASM):
   the same mask, ORed into the uncached-accelerated segment. */
static __inline__ int uncached_accel_addr(int p)
{ return (p & 0x0FFFFFFF) | 0x20000000; }
extern int D_0063A468;   /* movie heap handle; gp-relative in the ROM */
extern int iosMallocAlignDebug(int heap, int size, int align, const char *file, int line);
extern void debug_assert(const char *file, int line);   /* assert reporter */
extern void __assert(const char *file, int line, const char *expr);  extern void *memset(void *p, int c, int n);
#ifdef MV_DEFS_WANT_ALLOC   /* opt-in: see the note below line 46 */
static __inline__ int alloc_zeroed(int size, int align)  /* RECONSTRUCTION; 5 census hosts; align = 0x40 at four sites, 4 at viBufCreate's third */
{ int p = iosMallocAlignDebug(D_0063A468, size, align, __FILE__, __LINE__);
  if (p == 0) { debug_assert(__FILE__, __LINE__); __assert(__FILE__, __LINE__, "p != NULL"); }
  memset((void *)p, 0, size); return p; }
#endif
/* The line-42 helper is behind MV_DEFS_WANT_ALLOC because ee-gcc 2.9 emits
   the two string literals into .rodata even when the unused static itself is
   dropped, which would grow every consuming .o. Define the macro before the
   include in the TU that actually calls it. Lines 46..82 of the developer's
   header carry no census rows at all, so nothing is known about them; they
   are left blank so `Free` below lands on its recorded line 83. */






























/* TODO(line 83) `Free`: the census puts the body `iosFree(phys_addr(p))` on
   this line, with the line-30 mask inlined into it, and shows it emitted
   OUT OF LINE once per including TU (three copies, listed above). It is a
   header file-static, so writing it here would make every consumer that
   does not call it in C drop the definition (unused static), breaking the
   asm callers' relocs, and it would collide with the copy mv_videodec.c
   already defines. Materialise it once its callers are C; until then each
   TU keeps its own copy (Free, func_001A7318, func_0025A4A8), all three of
   which now call phys_addr() from this header. */

#endif /* MV_DEFS_H */
