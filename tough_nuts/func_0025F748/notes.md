# func_0025F748 — parked

VRAM: 0x0025F748 (file_off 0x15F748)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025F748.s

## Attempt at 2026-06-13

**Reason parked:** rc5 stall=30/30. movz/movn coalescing tie: ROM keeps hi=(int)((d<<2)>>32) in t0, a3=hi|1 (ori), movz a3,t0,lo (if lo==0 a3=hi). gcc coalesces hi into a3 and emits movn (a3=hi default, ->hi|1 if lo!=0). func_0025EBD8(&t,&out) (t=(ll)a0, sd spill); a3=hi|((d&0x3FFFFFFF)!=0 sticky); func_00260310(out.a,out.b,out.c,a3). ~30 forms: ternary(->sltu+or merge), explicit-if(->movn rc5), eq/neq polarity, lo int/ll/uint temps, copy/new_var, d4 split, shift-test. struct={int a,b,c,pad;ll d}. Permuter-class.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025F748/func_0025F748.c`

Disassembly:

```
.align 3
nonmatching func_0025F748, 0x54

glabel func_0025F748
    /* 15F748 0025F748 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 15F74C 0025F74C 2000A4FF */  sd         $4, 0x20($29)
    /* 15F750 0025F750 2D28A003 */  daddu      $5, $29, $0
    /* 15F754 0025F754 3000BFFF */  sd         $31, 0x30($29)
    /* 15F758 0025F758 F67A090C */  jal        func_0025EBD8
    /* 15F75C 0025F75C 2000A427 */   addiu     $4, $29, 0x20
    /* 15F760 0025F760 1000A2DF */  ld         $2, 0x10($29)
    /* 15F764 0025F764 FF3F033C */  lui        $3, (0x3FFFFFFF >> 16)
    /* 15F768 0025F768 FFFF6334 */  ori        $3, $3, (0x3FFFFFFF & 0xFFFF)
    /* 15F76C 0025F76C 0000A48F */  lw         $4, 0x0($29)
    /* 15F770 0025F770 B8400200 */  dsll       $8, $2, 2
    /* 15F774 0025F774 3F400800 */  dsra32     $8, $8, 0
    /* 15F778 0025F778 0400A58F */  lw         $5, 0x4($29)
    /* 15F77C 0025F77C 24104300 */  and        $2, $2, $3
    /* 15F780 0025F780 01000735 */  ori        $7, $8, 0x1
    /* 15F784 0025F784 0800A68F */  lw         $6, 0x8($29)
    /* 15F788 0025F788 C480090C */  jal        func_00260310
    /* 15F78C 0025F78C 0A380201 */   movz      $7, $8, $2
    /* 15F790 0025F790 3000BFDF */  ld         $31, 0x30($29)
    /* 15F794 0025F794 0800E003 */  jr         $31
    /* 15F798 0025F798 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_0025F748
    /* 15F79C 0025F79C 00000000 */  nop
```

## Permuter run (2026-06-13) — resolution (b), rc1 near-miss is semantics-deviating
- ~780 iterations on clean seed; harvest by real_count: output-200-1 = rc1.
- rc1 form = my rc5 seed with `d = (int)out.d` (truncate out.d to 32-bit then
  sign-extend) instead of `d = out.d`. This FLIPS the movz (rc5's movn→movz,
  fixing the coalescing) BUT changes the load from `ld` (ROM, full 64-bit) to
  `lw` → the sole remaining rc1 diff is `ld v0,16(sp)` (E) vs `lw v0,16(sp)` (B).
- CATCH-22 (confirmed ~40 hand forms + permuter): `ld` (full 64-bit out.d, the
  dev's shape) REQUIRES `long long d; d = out.d;` → gcc coalesces hi into a3 →
  **movn** (rc5). Getting **movz** requires truncating d (`(int)`/`unsigned int`
  field) → **lw** (rc1, wrong load). No hand/permuter form found full-`ld` + movz.
- rc1 is semantics-deviating (truncates out.d), like func_002416F0's rc7 — NOT a
  valid match path. Valid floor = rc5 (full d, movn). Parked at rc5.
- RESUME: the dev's source has full `ld` + movz simultaneously — find what keeps
  `hi` in a separate reg (uncoalesced from a3) WITHOUT truncating d. Maybe hi is
  used elsewhere, or a3 is the func-arg reg forcing hi to a scratch.
