/*
 * include/typedef.h — the `common` programmer's shared typedef header.
 *
 * PROVENANCE.  Dev path `common/include/typedef.h`, reached from `fumi/` as
 * `../common/include/typedef.h`.  `baserom/pal/SRCFILE.TXT` attributes
 * instructions to exactly one of its lines (census:
 * decomp/pal_source_tree.md, section `fumi/../common/include/typedef.h`):
 *
 *   line 74 — avoid_obstacle2 (src/way_sys, 0x0017DA50), 3 rows / 2 expansions
 *
 * so the header holds at least one `static` helper besides whatever typedefs
 * its name implies.  Instructions from a MACRO expansion would be attributed
 * to the caller's line, not to line 74, so line 74 is a function.
 *
 * TODO(line 74) — a float absolute value.  Both expansions in the ROM are
 * `mtc1 $zero,$fN; c.lt.s $f1,$fN; bc1tl <skip>; neg.s $f1,$f1`, i.e.
 * `x < 0.0f ? -x : x`.  It is NOT written here: the rule for defining a
 * census-only helper is >= 2 HOSTS with the same sequence, and this has one
 * host (twice).  Its host is still INCLUDE_ASM; write the helper when
 * avoid_obstacle2 is matched, and name it then — the helper is never emitted
 * out of line, so it has no symbol in baserom/pal/MAIN.MAP and no known name.
 *
 * SPLIT RULE (see decomp/HEADERS.md).  Nothing has been moved out of
 * include/ico/types.h into this file.  ico/types.h holds the CROSS-PROGRAMMER
 * engine object shapes (GObj, Sub15C, Obj7F0, ...) recovered mechanically
 * from load offsets and shared by every programmer's TUs; a per-programmer
 * header may only claim a declaration when the census shows that programmer's
 * header is where the code using it lived.  For this header the census shows
 * one helper and nothing else, so there is nothing yet to claim.
 */
#ifndef TYPEDEF_H
#define TYPEDEF_H

#endif /* TYPEDEF_H */
