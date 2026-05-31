/*
 * include/matching.h — formerly a header-macro library of ee-gcc 2.9
 * matching crutches (register pins, scheduler/CSE barriers, operand-order
 * forcers, libm bit-twiddle bodies).
 *
 * Those Bucket A/B macros were DELETED: a regalloc / scheduling /
 * coalescing diff is a SOURCE-SHAPE mismatch, not a gcc floor, and must be
 * cracked by recovering the 2000-era dev's C (decl order, signatures,
 * goto-CFG, unions, pointer lifetime) — not by forcing codegen with inline
 * asm. Every function that relied on one of those macros was parked to
 * tough_nuts/ for clean re-derivation.
 *
 * Removed (Bucket A — regalloc/scheduling/coalescing nudges):
 *   REG (regpin.h), ANCHOR, MATERIALIZE, KEEP_LIVE, KEEP_LIVE_MEM,
 *   KEEP_LIVE_FP, KEEP_LIVE_FP2, MEM_BARRIER, NOREORDER_BARRIER, NOP,
 *   DEFEAT_TCO, VOLATILE_RELOAD_CALL, DEAD_DADDU_V0_SP, ADDU_RT, ADDU_RS,
 *   LA_SPLIT.
 * Removed (Bucket B — libm intrinsic bit-twiddle bodies):
 *   FABSF_BIT_TWIDDLE, COPYSIGNF_BIT_TWIDDLE, ISNANF_BIT_TWIDDLE.
 *
 * What stays here is ONLY non-matching parity machinery (Bucket C):
 * ROM/linker byte-layout helpers that have no source-shape alternative.
 */

#ifndef MATCHING_H
#define MATCHING_H

/* Retained as an empty stub (REG removed). Kept so TUs that include it
 * still resolve. */
#include "regpin.h"

/* File-scope 4-byte zero pad (a nop) emitted into .text immediately
 * after the preceding function body.  Use at file scope when the
 * original codegen reserves a 4-byte trailing slot after a tail-call
 * function (whose own delay slot is already filled) to align the
 * NEXT TU's first function to 8 bytes.  Splat consolidates that
 * trailing pad into the TU's size, so the .o must emit the pad even
 * though gcc's natural tail-call sequence ends one nop short.
 *
 * This is Bucket C (linker/layout parity), NOT a matching crutch:
 * there is no source-shape that produces an inter-function alignment
 * pad, so it is retained. */
#define TRAILING_PAD_NOP()          asm("\t.4byte 0")

#endif /* MATCHING_H */
