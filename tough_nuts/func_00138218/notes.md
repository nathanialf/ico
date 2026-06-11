# func_00138218 — parked

VRAM: 0x00138218 (file_off 0x038218)
Asm source: asm/aug6/nonmatchings/fumi/ios/mcdata/func_00138218.s

## Attempt at 2026-06-11

**Reason parked:** rc3 register-alloc-only: value flow byte-identical to ROM except a 3-insn redundant chunk backup (daddu a0,a2 in inner-loop beqz delay) + b + else-restore (daddu a2,a0) that gcc won't materialize in the chunk-clamp tail. 11 distinct source-shape forms tried (in-place/sz/sz=chunk/goto/ternary/two-call=2jals/saved+over=movn/comma-backup/assign-in-cond/cached-lim) all rc3 or worse. Permuter-class (cf func_00141048 branch-likely tail, func_001FB768 new_var).

**TU:** `fumi/ios/mcdata.c`

**Seed:** `tough_nuts/func_00138218/func_00138218.c`

Disassembly:

```
.align 3
nonmatching func_00138218, 0x108

glabel func_00138218
    /* 38218 00138218 90FFBD27 */  addiu      $29, $29, -0x70
    /* 3821C 0013821C FFFF0324 */  addiu      $3, $0, -0x1
    /* 38220 00138220 4000B3FF */  sd         $19, 0x40($29)
    /* 38224 00138224 2D380000 */  daddu      $7, $0, $0
    /* 38228 00138228 3000B2FF */  sd         $18, 0x30($29)
    /* 3822C 0013822C 2D400000 */  daddu      $8, $0, $0
    /* 38230 00138230 2000B1FF */  sd         $17, 0x20($29)
    /* 38234 00138234 2D90A000 */  daddu      $18, $5, $0
    /* 38238 00138238 1000B0FF */  sd         $16, 0x10($29)
    /* 3823C 0013823C 2D888000 */  daddu      $17, $4, $0
    /* 38240 00138240 6000BFFF */  sd         $31, 0x60($29)
    /* 38244 00138244 1400053C */  lui        $5, %hi(iosMallocResetPartition)
    /* 38248 00138248 5000B4FF */  sd         $20, 0x50($29)
    /* 3824C 0013824C 2D204002 */  daddu      $4, $18, $0
    /* 38250 00138250 2884A524 */  addiu      $5, $5, %lo(iosMallocResetPartition)
    /* 38254 00138254 2D480000 */  daddu      $9, $0, $0
    /* 38258 00138258 2000428E */  lw         $2, 0x20($18)
    /* 3825C 0013825C 2D500000 */  daddu      $10, $0, $0
    /* 38260 00138260 2D580000 */  daddu      $11, $0, $0
    /* 38264 00138264 2D800000 */  daddu      $16, $0, $0
    /* 38268 00138268 FF074624 */  addiu      $6, $2, 0x7FF
    /* 3826C 0013826C 2A186600 */  slt        $3, $3, $6
    /* 38270 00138270 FE0F4224 */  addiu      $2, $2, 0xFFE
    /* 38274 00138274 0B10C300 */  movn       $2, $6, $3
    /* 38278 00138278 C3120200 */  sra        $2, $2, 11
    /* 3827C 0013827C 2D30A003 */  daddu      $6, $29, $0
    /* 38280 00138280 C0120200 */  sll        $2, $2, 11
    /* 38284 00138284 4CC9040C */  jal        iosCdvdChgFileName
    /* 38288 00138288 0000A2AF */   sw        $2, 0x0($29)
    /* 3828C 0013828C 2D984000 */  daddu      $19, $2, $0
    /* 38290 00138290 0000A28F */  lw         $2, 0x0($29)
    /* 38294 00138294 17004018 */  blez       $2, .L001382F4
    /* 38298 00138298 01001424 */   addiu     $20, $0, 0x1
    /* 3829C 0013829C 00000000 */  nop
.align 2
  .L001382A0:
    /* 382A0 001382A0 0400A0AF */  sw         $0, 0x4($29)
    /* 382A4 001382A4 00000000 */  nop
.align 2
  .L001382A8:
    /* 382A8 001382A8 D4DE040C */  jal        func_00137B50
    /* 382AC 001382AC 2D202002 */   daddu     $4, $17, $0
    /* 382B0 001382B0 0400A68F */  lw         $6, 0x4($29)
    /* 382B4 001382B4 FCFFC010 */  beqz       $6, .L001382A8
    /* 382B8 001382B8 2D20C000 */   daddu     $4, $6, $0
    /* 382BC 001382BC 2000438E */  lw         $3, 0x20($18)
    /* 382C0 001382C0 21800602 */  addu       $16, $16, $6
    /* 382C4 001382C4 2A107000 */  slt        $2, $3, $16
    /* 382C8 001382C8 03004010 */  beqz       $2, .L001382D8
    /* 382CC 001382CC 23100302 */   subu      $2, $16, $3
    /* 382D0 001382D0 02000010 */  b          .L001382DC
    /* 382D4 001382D4 2330C200 */   subu      $6, $6, $2
.align 2
  .L001382D8:
    /* 382D8 001382D8 2D308000 */  daddu      $6, $4, $0
.align 2
  .L001382DC:
    /* 382DC 001382DC 0800A58F */  lw         $5, 0x8($29)
    /* 382E0 001382E0 E2D7040C */  jal        func_00135F88
    /* 382E4 001382E4 2D202002 */   daddu     $4, $17, $0
    /* 382E8 001382E8 0000A28F */  lw         $2, 0x0($29)
    /* 382EC 001382EC ECFF401C */  bgtz       $2, .L001382A0
    /* 382F0 001382F0 98B394AF */   sw        $20, %gp_rel(D_0062BF88)($28)
.align 2
  .L001382F4:
    /* 382F4 001382F4 C2CB040C */  jal        iosCdvdBackGroundMgrEntryNum
    /* 382F8 001382F8 2D206002 */   daddu     $4, $19, $0
    /* 382FC 001382FC 6000BFDF */  ld         $31, 0x60($29)
    /* 38300 00138300 2D100000 */  daddu      $2, $0, $0
    /* 38304 00138304 5000B4DF */  ld         $20, 0x50($29)
    /* 38308 00138308 4000B3DF */  ld         $19, 0x40($29)
    /* 3830C 0013830C 3000B2DF */  ld         $18, 0x30($29)
    /* 38310 00138310 2000B1DF */  ld         $17, 0x20($29)
    /* 38314 00138314 1000B0DF */  ld         $16, 0x10($29)
    /* 38318 00138318 0800E003 */  jr         $31
    /* 3831C 0013831C 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_00138218
```

## Resume session 2 — name/twin investigation + 21-form grind (still rc3)

- Confirmed ANONYMOUS: `func_00138218` has no dev name in symbol_addrs.aug6.txt
  (only the iosMcIcon* siblings are named). No matched twin: retail near-addr
  funcs (func_00138510/138618/138720) are the ios/memory.c partition manager,
  not this CD chunked-read loop. memory.c only *references* iosCdvdChgFileName.
- Identity is clear from callees + the 0x800(=CD sector) round-up: a CD-file
  chunked read/copy loop. Reconstruction matches 81/84 instructions.
- Residual = 3-insn register-alloc artifact ONLY: ROM keeps a redundant backup
  of the original chunk (`daddu a0,a2` in the inner-loop beqz delay) + `b` +
  else-restore (`daddu a2,a0`); gcc proves the else-value == chunk and just
  conditionally reduces it in place. Value flow is provably byte-identical.
- DISTINCT-SEMANTIC space exhausted (per dev-data-model discipline — if/ternary/
  goto/temp costume-changes fold to ONE rc3 RTL): in-place(rc3), two-call(rc19,
  2 jals — no cross-jump), acc-inside-inner-loop(rc4, shifts lim-load),
  pf-int*-cache(rc22, displaces a1's s2), char*-cache(rc4, permuter), volatile
  chunk(rc3), volatile buf(rc6), function-scope decls(rc3), saved+over(rc11 movn),
  goto-CFG-explicit-backup(rc4). Forced permuter (PERMUTE_FORCE=1, ~1000 iters):
  best output-360-1 = rc4 (anti-correlated score). Nothing beats rc3.
- VERDICT: genuine register-allocation near-floor. The redundant backup is not
  produced by any clean C tried. Needs either a fresh allocator-perturbing idea
  on resume, or a longer/seeded permuter run at a real 30-stall.
