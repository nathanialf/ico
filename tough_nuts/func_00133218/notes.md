# func_00133218 (ios/cdvd.c) — DFDATAS path normaliser

**Status:** regalloc near-miss (~9 lines) — permuter candidate.

Algorithm is correct: func_00264DF8 formats into a 256-byte stack buffer,
then an in-place do-while loop maps '/'→'\\' (0x2F→0x5C) and uppercases
ASCII letters via the D_0062FC79 ctype table (`(tbl[sc] & 2) ? sc-0x20 :
sc`, emitted as movz), then func_00265168(a0, buf).

Solved sub-points:
- do-while (not while): the original processes the NUL terminator too.
- `unsigned char c = *p; (signed char)c` → lbu + sll/sra (not lb).
- `register ... REG("$16")` pins the cursor to s0 (a0 → s1).

Remaining diffs are register choices ee-gcc won't take from C:
- the running byte wants to live in v1 ($3) with a `daddu $3,$2` copy at
  the loop bottom (keep_live_v1 shape), built keeps it in v0.
- the first `lbu` reads `0(sp)` (expected) vs `0(s0)` (built); the
  '\\'/table-base constants land in swapped a2/a3.

A register-assignment shuffle — permuter territory. NOTE: seed #includes
regpin.h; the tracked cdvd.c does NOT (it has no other REG user), so any
promotion must add that include.
