# func_00175C18 — parked

VRAM: 0x00175C18 (file_off 0x075C18)
Asm source: asm/matchings/src/commonact/func_00175C18.s

## Attempt at 2026-05-31 (resume, clean-C grind)

**Reason parked:** genuine 30-stall (`match_loop next` = park at stall 31/30,
best=11). Clean (no-REG) seed; the retired `REG("$2")` form is gone.

**TU:** `src/commonact.c`

**Seed:** `tough_nuts/func_00175C18/func_00175C18.c`

### Root cause (single cascade — fix it and all 11 diffs collapse)

The seed is structurally CORRECT (result-var single exit; `bnel` with the
speculative `sub[0x30]` load in its delay; one shared `daddu v0,0` default;
`sltiu` true-result). The entire 11-diff residual is ONE register-coalescing
tie:

- ORIGINAL allocation: `v`(=sub[0x30] load)→`$a0`, const `0x45`→`$v1`
  (reuses the just-dead `sub` base), `r`→`$v0`. 20 insns, no move.
- BUILT (ours): gcc COALESCES the load-dest `v` into the dying base `$v1`
  (`lw v1,48(v1)`); that pushes const `0x45`→`$v0`; so `r` (born `daddu` in
  the `bne` delay, must avoid live `v`+const) is forced to `$a0`, needing a
  trailing `daddu v0,a0,zero` fixup → 21 insns. All 11 diffs are this rotation
  + the extra move.

Pivot: the speculative taken-block load `*(int*)(sub+0x30)` must land in `$a0`
(its own reg), NOT coalesce into `$v1`. Then const→`$v1`, `$v0` stays free for
`r`. The historical match achieved this with `REG("$4")`(v) + `REG("$2")`(r)
pins — both retired. No clean-C shape found that breaks the coalesce while
keeping `bnel`.

### Levers tried (~26 distinct, all → 11 unless noted; none below 11)

- result-var / anon-temp / 3-term `&&` return / single-ternary(27, worse) /
  early-return split(17) / `goto ret0` shared exit (splits into 2 `jr`, worse)
  / inverted bit-branch(28, worse).
- decl order r-before-v / v-before-r; `register int v`; operand swap
  `0x45 == v` (gcc canonicalizes — no effect).
- pointer split `p30 = sub+0x30` (gcc folds back); `unsigned char *D` pointer
  (12); D hoisted to top (13); named `flags`/`d5d` temps; `!D[0x58]`;
  `D[0x5D]` truthy; unsigned r; `char*` vs `int*[off/4]` vs typed `struct`
  member access (TBAA on) — all 11.
- **early-read** (load `v` before the bit-branch): UNIQUELY forces `v→$a0`
  (sub still live at load), but the load leaves the taken block so `bnel`
  degrades to `bne` (always-exec delay) and const still grabs `$v0`, `r→$a1`
  → 13. The ONLY lever that moved `v` off `$v1`; needs a companion that
  restores `bnel` while keeping `v` in `$a0`.

### Next levers for the offline batch / a future resume

- The permuter's job here is the structural live-range-split that breaks the
  `v`↔`$v1` coalesce (cf. func_001FB768's assignment-in-condition crack).
  Seed it WITH the clean form above; `--stop-on-zero`.
- Hand idea not yet exhausted: find a source shape that keeps `bnel` (load in
  taken block) yet makes `sub` interfere with `v` at the load so gcc can't
  coalesce — i.e. a *real* second use of `sub` in the taken block, or enough
  register pressure to deny the coalesce, WITHOUT emitting extra instructions.

### Disassembly

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE8, 1

.align 3
nonmatching func_00175C18, 0x54

glabel func_00175C18
    /* 75C18 00175C18 F891838F */  lw         $3, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* 75C1C 00175C1C 6401638C */  lw         $3, 0x164($3)
    /* 75C20 00175C20 180062DC */  ld         $2, 0x18($3)
    /* 75C24 00175C24 3E110200 */  dsrl32     $2, $2, 4
    /* 75C28 00175C28 01004230 */  andi       $2, $2, 0x1
    /* 75C2C 00175C2C 03004054 */  bnel       $2, $0, .L00175C3C
    /* 75C30 00175C30 3000648C */   lw        $4, 0x30($3)
    /* 75C34 00175C34 0800E003 */  jr         $31
    /* 75C38 00175C38 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L00175C3C:
    /* 75C3C 00175C3C 45000324 */  addiu      $3, $0, 0x45
    /* 75C40 00175C40 08008314 */  bne        $4, $3, .L00175C64
    /* 75C44 00175C44 2D100000 */   daddu     $2, $0, $0
    /* 75C48 00175C48 2900033C */  lui        $3, %hi(D_002883D0)
    /* 75C4C 00175C4C D0836324 */  addiu      $3, $3, %lo(D_002883D0)
    /* 75C50 00175C50 5D006490 */  lbu        $4, 0x5D($3)
    /* 75C54 00175C54 03008010 */  beqz       $4, .L00175C64
    /* 75C58 00175C58 00000000 */   nop
    /* 75C5C 00175C5C 58006290 */  lbu        $2, 0x58($3)
    /* 75C60 00175C60 0100422C */  sltiu      $2, $2, 0x1
.align 2
  .L00175C64:
    /* 75C64 00175C64 0800E003 */  jr         $31
    /* 75C68 00175C68 00000000 */   nop
endlabel func_00175C18
    /* 75C6C 00175C6C 00000000 */  nop
```
