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

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,MEM_BARRIER)

**TU:** `ios/cdvd.c`

**Seed:** `tough_nuts/func_00133218/func_00133218.1.c`

Disassembly:

```
.align 3
nonmatching func_00133218, 0x9C

glabel func_00133218
    /* 33218 00133218 D0FEBD27 */  addiu      $29, $29, -0x130
    /* 3321C 0013321C 6300053C */  lui        $5, %hi(D_00631F70)
    /* 33220 00133220 1001B1FF */  sd         $17, 0x110($29)
    /* 33224 00133224 701FA524 */  addiu      $5, $5, %lo(D_00631F70)
    /* 33228 00133228 0001B0FF */  sd         $16, 0x100($29)
    /* 3322C 0013322C 2D888000 */  daddu      $17, $4, $0
    /* 33230 00133230 2001BFFF */  sd         $31, 0x120($29)
    /* 33234 00133234 2D80A003 */  daddu      $16, $29, $0
    /* 33238 00133238 2D20A003 */  daddu      $4, $29, $0
    /* 3323C 0013323C 7E93090C */  jal        func_00264DF8
    /* 33240 00133240 2D302002 */   daddu     $6, $17, $0
    /* 33244 00133244 6300023C */  lui        $2, %hi(D_0062FC79)
    /* 33248 00133248 0000A393 */  lbu        $3, 0x0($29)
    /* 3324C 0013324C 2F000824 */  addiu      $8, $0, 0x2F
    /* 33250 00133250 5C000724 */  addiu      $7, $0, 0x5C
    /* 33254 00133254 79FC4624 */  addiu      $6, $2, %lo(D_0062FC79)
.align 2
  .L00133258:
    /* 33258 00133258 00160300 */  sll        $2, $3, 24
    /* 3325C 0013325C 032E0200 */  sra        $5, $2, 24
    /* 33260 00133260 0300A814 */  bne        $5, $8, .L00133270
    /* 33264 00133264 2120A600 */   addu      $4, $5, $6
    /* 33268 00133268 06000010 */  b          .L00133284
    /* 3326C 0013326C 000007A2 */   sb        $7, 0x0($16)
.align 2
  .L00133270:
    /* 33270 00133270 E0FFA324 */  addiu      $3, $5, -0x20
    /* 33274 00133274 00008290 */  lbu        $2, 0x0($4)
    /* 33278 00133278 02004230 */  andi       $2, $2, 0x2
    /* 3327C 0013327C 0A18A200 */  movz       $3, $5, $2
    /* 33280 00133280 000003A2 */  sb         $3, 0x0($16)
.align 2
  .L00133284:
    /* 33284 00133284 01001026 */  addiu      $16, $16, 0x1
    /* 33288 00133288 00000292 */  lbu        $2, 0x0($16)
    /* 3328C 0013328C F2FF4014 */  bnez       $2, .L00133258
    /* 33290 00133290 2D184000 */   daddu     $3, $2, $0
    /* 33294 00133294 2D202002 */  daddu      $4, $17, $0
    /* 33298 00133298 5A94090C */  jal        func_00265168
    /* 3329C 0013329C 2D28A003 */   daddu     $5, $29, $0
    /* 332A0 001332A0 2001BFDF */  ld         $31, 0x120($29)
    /* 332A4 001332A4 1001B1DF */  ld         $17, 0x110($29)
    /* 332A8 001332A8 0001B0DF */  ld         $16, 0x100($29)
    /* 332AC 001332AC 0800E003 */  jr         $31
    /* 332B0 001332B0 3001BD27 */   addiu     $29, $29, 0x130
endlabel func_00133218
    /* 332B4 001332B4 00000000 */  nop
```
