# func_001B8720 (a_p_1) — best real_count 159 (was 299), 367-insn constructor

2026-05-29 session: hand-ground 299 → **159** (47% reduction) via the
PA2-dev typed-struct reframing + a stack of structural levers. Remaining
~159 is dominated by ONE gcc cross-block scheduling artifact (the Tmpl50
"dst-hoist", below) that cascades ~25 lines and resisted 6+ distinct hand
levers — the canonical permuter target. Blocks 0/1 (prologue) and block 2
(E32 float store) are now byte-clean.

## Applied levers (all IN the current seed — keep these)
1. **§5.7 far-global %hi caching** — `extern const char FN8550[] __asm__("D_00618550");`
   and `A33210[] __asm__("D_00633210");`; reference via the alias at every
   use. Forces `lui $sN,%hi` cached in a callee reg + `addiu ,%lo` per use.
   FN8550 supplied $s6, A33210 supplied the 9th callee reg → **frame -224
   matches** (was -208). This collapsed the original 299→293 frame cascade.
2. **func_00264D60 returns int** (NOT void). `this[0x270] = func_00264D60() & 0x1F`
   — the masked value is the CALL'S RETURN ($2 after jal), not a reloaded
   self[0x15C]. The old seed's `self[0x15C] & 0x1F` forced a spurious reload
   (extra insn → branch-offset cascade). 293→256-ish across several.
3. **PA2-dev typed structs — THE big unlock (256→172).** `struct Obj` (this,
   with `struct Sub *m194,*m198` at 0x194/0x198, `Tmpl50 t50[4]` at 0x10,
   `Tmpl12 t12[2]` at 0x150) and `struct Sub` (fields f8/fC/f10/f818/f840).
   Access the sub-objects as `this->m194->field` (macros M194/M198). TBAA
   then separates the *pointer* reload of m194 from the *int* field stores,
   so gcc reloads m194 only across calls (matching) instead of caching it in
   a callee reg (built was wrong). The old `((int*)this[0x194/4])[..]` int-
   cast form made every int store alias the m194 reload (uniform inline blew
   up to 343). **This is the key insight: type it like the 2000-era dev did.**
4. **struct Bec member store** for `D_004BEC00+8` (struct_member_offset) —
   `((struct Bec*)D_004BEC00)->f8 = ...` keeps D_004BEC00 as base reg + offset-8
   store, killing the `+8/-8` base-fold. 172→168.
5. **base-accumulate E32 element** — `eb=(char*)D_00623468; eb+=idx*0x20`. 168→167.
6. **offset-accumulator entry-init loops** — the m194->f840 entry loop uses a
   separate UP-counting `off += 0x50` + DOWN counter `i` (NOT `i*0x50`, which
   iterates reverse and emits mult). 167→165.
7. **removed the `i` REG("$17") pin** — typed structs now carry the this→$s2
   allocation naturally; the pin became a net negative. 164→163.
8. **float-store-last** — load `f18` into a temp, do the 3 int stores
   (0x278/0x274/0x270), THEN `((Bec*)...)->f8 = f18` last → the `swc1` lands in
   the func_00105F00 jal delay slot (matching). 163→**159**. Block 2 now clean.
9. matrix loop uses its own counter `k` (orig counter = $s3, not the shared i).

## Remaining (PERMUTER TARGET)
- **Tmpl50 dst-hoist (dominant, ~25-line cascade):** gcc schedules the Tmpl12
  loop's `dst = this+0x150` (`addiu a3,s2,336`) up into the **Tmpl50 loop
  preamble**, stealing `$a3` from the Tmpl50 stride-0x50 const (→ stride to
  $t0) and shifting the struct-copy temps `$t0-$t3` → `$t1-$t4`, plus +4/+8
  branch offsets through Tmpl12/matrix. The ORIGINAL computes `addiu $2,$18,0x150`
  in the Tmpl12 preamble (NOT hoisted). This is gcc cross-block (sched2)
  instruction placement — pure scheduling, no semantic difference.
  FAILED hand levers (all reverted): ANCHOR(this), MEM_BARRIER before the
  block, MATERIALIZE(dst), early-advance `next=i+1`, separate Tmpl12/entry
  counter `j`, un-typed t50/t12, dst=&t50[4]. → permuter.
- **1-line commutative addu** (block 2): `addu v1,a0,v1` (built) vs
  `addu v1,v1,a0` (orig). The element `eb += idx`. swap_addu_operands.txt
  (scoped rd=$3) would fix it but it's TU-global (sibling risk; run tu_check).
- build-block register numbering (m194 reload $a2 vs $v0; entry-loop offset
  $a1 vs $a3) — gcc-internal regalloc, cascades from / co-varies with the
  dst-hoist. Likely resolves once the dst-hoist is fixed.

## Permuter
CFLAGS = `-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -Iinclude`
Seed = the whole TU (park_tu.py); permute_run reduces to the func. The
dst-hoist is a scheduling perturbation — squarely in permuter's domain.
Measure real_count (match_loop diff), NOT permuter score, on harvest.

---

## Attempt at 2026-05-29

**Reason parked:** best rc159 (was 299); PA2-dev typed structs + 8 structural levers; remaining = Tmpl50 dst-hoist scheduling cascade (permuter target)

**TU:** `src/a_p_1.c`

**Seed:** `tough_nuts/func_001B8720/func_001B8720.1.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1
.extern D_00632024, 1

.align 3
nonmatching func_001B8720, 0x5BC

glabel func_001B8720
    /* B8720 001B8720 20FFBD27 */  addiu      $29, $29, -0xE0
    /* B8724 001B8724 E4000724 */  addiu      $7, $0, 0xE4
    /* B8728 001B8728 9000B5FF */  sd         $21, 0x90($29)
    /* B872C 001B872C 2DA88000 */  daddu      $21, $4, $0
    /* B8730 001B8730 A000B6FF */  sd         $22, 0xA0($29)
    /* B8734 001B8734 8000B4FF */  sd         $20, 0x80($29)
    /* B8738 001B8738 6200163C */  lui        $22, %hi(D_00618550)
    /* B873C 001B873C 2DA0A000 */  daddu      $20, $5, $0
    /* B8740 001B8740 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* B8744 001B8744 6000B2FF */  sd         $18, 0x60($29)
    /* B8748 001B8748 80020524 */  addiu      $5, $0, 0x280
    /* B874C 001B874C 5000B1FF */  sd         $17, 0x50($29)
    /* B8750 001B8750 5085C626 */  addiu      $6, $22, %lo(D_00618550)
    /* B8754 001B8754 4000B0FF */  sd         $16, 0x40($29)
    /* B8758 001B8758 2D880000 */  daddu      $17, $0, $0
    /* B875C 001B875C D000BFFF */  sd         $31, 0xD0($29)
    /* B8760 001B8760 01001024 */  addiu      $16, $0, 0x1
    /* B8764 001B8764 C000BEFF */  sd         $30, 0xC0($29)
    /* B8768 001B8768 B000B7FF */  sd         $23, 0xB0($29)
    /* B876C 001B876C 3EE8040C */  jal        func_0013A0F8
    /* B8770 001B8770 7000B3FF */   sd        $19, 0x70($29)
    /* B8774 001B8774 2D904000 */  daddu      $18, $2, $0
    /* B8778 001B8778 3000838E */  lw         $3, 0x30($20)
    /* B877C 001B877C 5C01A28E */  lw         $2, 0x15C($21)
    /* B8780 001B8780 07000424 */  addiu      $4, $0, 0x7
    /* B8784 001B8784 040050AE */  sw         $16, 0x4($18)
    /* B8788 001B8788 6C0140AE */  sw         $0, 0x16C($18)
    /* B878C 001B878C 680140AE */  sw         $0, 0x168($18)
    /* B8790 001B8790 C40140AE */  sw         $0, 0x1C4($18)
    /* B8794 001B8794 C80140AE */  sw         $0, 0x1C8($18)
    /* B8798 001B8798 C00140AE */  sw         $0, 0x1C0($18)
    /* B879C 001B879C 000852AC */  sw         $18, 0x800($2)
    /* B87A0 001B87A0 000043AE */  sw         $3, 0x0($18)
    /* B87A4 001B87A4 5893090C */  jal        func_00264D60
    /* B87A8 001B87A8 080044AE */   sw        $4, 0x8($18)
    /* B87AC 001B87AC 0000448E */  lw         $4, 0x0($18)
    /* B87B0 001B87B0 6200033C */  lui        $3, %hi(D_00623468)
    /* B87B4 001B87B4 68346324 */  addiu      $3, $3, %lo(D_00623468)
    /* B87B8 001B87B8 4C00063C */  lui        $6, %hi(D_004BEC00)
    /* B87BC 001B87BC 40210400 */  sll        $4, $4, 5
    /* B87C0 001B87C0 00ECC624 */  addiu      $6, $6, %lo(D_004BEC00)
    /* B87C4 001B87C4 21186400 */  addu       $3, $3, $4
    /* B87C8 001B87C8 1F004230 */  andi       $2, $2, 0x1F
    /* B87CC 001B87CC 180060C4 */  lwc1       $f0, 0x18($3)
    /* B87D0 001B87D0 2D28C000 */  daddu      $5, $6, $0
    /* B87D4 001B87D4 780250AE */  sw         $16, 0x278($18)
    /* B87D8 001B87D8 B0014426 */  addiu      $4, $18, 0x1B0
    /* B87DC 001B87DC 740240AE */  sw         $0, 0x274($18)
    /* B87E0 001B87E0 700242AE */  sw         $2, 0x270($18)
    /* B87E4 001B87E4 C017040C */  jal        func_00105F00
    /* B87E8 001B87E8 0800C0E4 */   swc1      $f0, 0x8($6)
    /* B87EC 001B87EC 9E61040C */  jal        func_00118678
    /* B87F0 001B87F0 F0014426 */   addiu     $4, $18, 0x1F0
    /* B87F4 001B87F4 9E61040C */  jal        func_00118678
    /* B87F8 001B87F8 30024426 */   addiu     $4, $18, 0x230
    /* B87FC 001B87FC D0014426 */  addiu      $4, $18, 0x1D0
    /* B8800 001B8800 140A040C */  jal        func_00102850
    /* B8804 001B8804 2D28A002 */   daddu     $5, $21, $0
    /* B8808 001B8808 E0014426 */  addiu      $4, $18, 0x1E0
    /* B880C 001B880C 4211040C */  jal        func_00104508
    /* B8810 001B8810 2D28A002 */   daddu     $5, $21, $0
    /* B8814 001B8814 4C00023C */  lui        $2, %hi(D_004BEA80)
    /* B8818 001B8818 50000724 */  addiu      $7, $0, 0x50
    /* B881C 001B881C 80EA4524 */  addiu      $5, $2, %lo(D_004BEA80)
    /* B8820 001B8820 4000A624 */  addiu      $6, $5, 0x40
    /* B8824 001B8824 18182702 */  mult       $3, $17, $7
.align 2
  .L001B8828:
    /* B8828 001B8828 01002426 */  addiu      $4, $17, 0x1
    /* B882C 001B882C 21107200 */  addu       $2, $3, $18
    /* B8830 001B8830 2D18A000 */  daddu      $3, $5, $0
    /* B8834 001B8834 10004224 */  addiu      $2, $2, 0x10
.align 2
  .L001B8838:
    /* B8838 001B8838 000068DC */  ld         $8, 0x0($3)
    /* B883C 001B883C 080069DC */  ld         $9, 0x8($3)
    /* B8840 001B8840 10006ADC */  ld         $10, 0x10($3)
    /* B8844 001B8844 18006BDC */  ld         $11, 0x18($3)
    /* B8848 001B8848 000048FC */  sd         $8, 0x0($2)
    /* B884C 001B884C 080049FC */  sd         $9, 0x8($2)
    /* B8850 001B8850 10004AFC */  sd         $10, 0x10($2)
    /* B8854 001B8854 18004BFC */  sd         $11, 0x18($2)
    /* B8858 001B8858 20006324 */  addiu      $3, $3, 0x20
    /* B885C 001B885C 20004224 */  addiu      $2, $2, 0x20
    /* B8860 001B8860 00000000 */  nop
    /* B8864 001B8864 F4FF6614 */  bne        $3, $6, .L001B8838
    /* B8868 001B8868 00000000 */   nop
    /* B886C 001B886C 2D888000 */  daddu      $17, $4, $0
    /* B8870 001B8870 000064DC */  ld         $4, 0x0($3)
    /* B8874 001B8874 080068DC */  ld         $8, 0x8($3)
    /* B8878 001B8878 000044FC */  sd         $4, 0x0($2)
    /* B887C 001B887C 080048FC */  sd         $8, 0x8($2)
    /* B8880 001B8880 0400222A */  slti       $2, $17, 0x4
    /* B8884 001B8884 E8FF4014 */  bnez       $2, .L001B8828
    /* B8888 001B8888 18182702 */   mult      $3, $17, $7
    /* B888C 001B888C 2800033C */  lui        $3, %hi(D_00282660)
    /* B8890 001B8890 50014226 */  addiu      $2, $18, 0x150
    /* B8894 001B8894 01001124 */  addiu      $17, $0, 0x1
.align 2
  .L001B8898:
    /* B8898 001B8898 60266624 */  addiu      $6, $3, %lo(D_00282660)
    /* B889C 001B889C 0700CB68 */  ldl        $11, 0x7($6)
    /* B88A0 001B88A0 0000CB6C */  ldr        $11, 0x0($6)
    /* B88A4 001B88A4 0800C48C */  lw         $4, 0x8($6)
    /* B88A8 001B88A8 07004BB0 */  sdl        $11, 0x7($2)
    /* B88AC 001B88AC 00004BB4 */  sdr        $11, 0x0($2)
    /* B88B0 001B88B0 080044AC */  sw         $4, 0x8($2)
    /* B88B4 001B88B4 FFFF3126 */  addiu      $17, $17, -0x1
    /* B88B8 001B88B8 0C004224 */  addiu      $2, $2, 0xC
    /* B88BC 001B88BC 00000000 */  nop
    /* B88C0 001B88C0 00000000 */  nop
    /* B88C4 001B88C4 F4FF2106 */  bgez       $17, .L001B8898
    /* B88C8 001B88C8 00000000 */   nop
    /* B88CC 001B88CC 5C01A28E */  lw         $2, 0x15C($21)
    /* B88D0 001B88D0 4C00033C */  lui        $3, %hi(D_004BEBA0)
    /* B88D4 001B88D4 A0EB6324 */  addiu      $3, $3, %lo(D_004BEBA0)
    /* B88D8 001B88D8 2D20A003 */  daddu      $4, $29, $0
    /* B88DC 001B88DC 0008508C */  lw         $16, 0x800($2)
    /* B88E0 001B88E0 2D28A002 */  daddu      $5, $21, $0
    /* B88E4 001B88E4 2D886000 */  daddu      $17, $3, $0
    /* B88E8 001B88E8 5010040C */  jal        func_00104140
    /* B88EC 001B88EC 03001324 */   addiu     $19, $0, 0x3
    /* B88F0 001B88F0 20001026 */  addiu      $16, $16, 0x20
    /* B88F4 001B88F4 00000000 */  nop
.align 2
  .L001B88F8:
    /* B88F8 001B88F8 2D200002 */  daddu      $4, $16, $0
    /* B88FC 001B88FC 2D302002 */  daddu      $6, $17, $0
    /* B8900 001B8900 2D28A003 */  daddu      $5, $29, $0
    /* B8904 001B8904 9261040C */  jal        func_00118648
    /* B8908 001B8908 FFFF7326 */   addiu     $19, $19, -0x1
    /* B890C 001B890C 10000426 */  addiu      $4, $16, 0x10
    /* B8910 001B8910 2D302002 */  daddu      $6, $17, $0
    /* B8914 001B8914 2D28A003 */  daddu      $5, $29, $0
    /* B8918 001B8918 9261040C */  jal        func_00118648
    /* B891C 001B891C 10003126 */   addiu     $17, $17, 0x10
    /* B8920 001B8920 F5FF6106 */  bgez       $19, .L001B88F8
    /* B8924 001B8924 50001026 */   addiu     $16, $16, 0x50
    /* B8928 001B8928 0400428E */  lw         $2, 0x4($18)
    /* B892C 001B892C BD004014 */  bnez       $2, .L001B8C24
    /* B8930 001B8930 4C00033C */   lui       $3, %hi(D_004BEAD0)
    /* B8934 001B8934 05000424 */  addiu      $4, $0, 0x5
    /* B8938 001B8938 C47C060C */  jal        func_0019F310
    /* B893C 001B893C 2D288002 */   daddu     $5, $20, $0
    /* B8940 001B8940 0C00438C */  lw         $3, 0xC($2)
    /* B8944 001B8944 05006010 */  beqz       $3, .L001B895C
    /* B8948 001B8948 940142AE */   sw        $2, 0x194($18)
    /* B894C 001B894C FF0F043C */  lui        $4, (0xFFFFFFF >> 16)
    /* B8950 001B8950 FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B8954 001B8954 66E5040C */  jal        func_00139598
    /* B8958 001B8958 24206400 */   and       $4, $3, $4
.align 2
  .L001B895C:
    /* B895C 001B895C 9401468E */  lw         $6, 0x194($18)
    /* B8960 001B8960 1000C28C */  lw         $2, 0x10($6)
    /* B8964 001B8964 05004010 */  beqz       $2, .L001B897C
    /* B8968 001B8968 FF0F043C */   lui       $4, (0xFFFFFFF >> 16)
    /* B896C 001B896C FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B8970 001B8970 66E5040C */  jal        func_00139598
    /* B8974 001B8974 24204400 */   and       $4, $2, $4
    /* B8978 001B8978 9401468E */  lw         $6, 0x194($18)
.align 2
  .L001B897C:
    /* B897C 001B897C 5085D026 */  addiu      $16, $22, %lo(D_00618550)
    /* B8980 001B8980 1000C0AC */  sw         $0, 0x10($6)
    /* B8984 001B8984 0C00C0AC */  sw         $0, 0xC($6)
    /* B8988 001B8988 00010524 */  addiu      $5, $0, 0x100
    /* B898C 001B898C 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B8990 001B8990 2D300002 */  daddu      $6, $16, $0
    /* B8994 001B8994 3EE8040C */  jal        func_0013A0F8
    /* B8998 001B8998 05010724 */   addiu     $7, $0, 0x105
    /* B899C 001B899C 9401438E */  lw         $3, 0x194($18)
    /* B89A0 001B89A0 40000524 */  addiu      $5, $0, 0x40
    /* B89A4 001B89A4 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B89A8 001B89A8 2D300002 */  daddu      $6, $16, $0
    /* B89AC 001B89AC 0C0062AC */  sw         $2, 0xC($3)
    /* B89B0 001B89B0 3EE8040C */  jal        func_0013A0F8
    /* B89B4 001B89B4 05010724 */   addiu     $7, $0, 0x105
    /* B89B8 001B89B8 9401438E */  lw         $3, 0x194($18)
    /* B89BC 001B89BC 04000424 */  addiu      $4, $0, 0x4
    /* B89C0 001B89C0 4008658C */  lw         $5, 0x840($3)
    /* B89C4 001B89C4 100062AC */  sw         $2, 0x10($3)
    /* B89C8 001B89C8 0500A010 */  beqz       $5, .L001B89E0
    /* B89CC 001B89CC 080064AC */   sw        $4, 0x8($3)
    /* B89D0 001B89D0 FF0F043C */  lui        $4, (0xFFFFFFF >> 16)
    /* B89D4 001B89D4 FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B89D8 001B89D8 66E5040C */  jal        func_00139598
    /* B89DC 001B89DC 2420A400 */   and       $4, $5, $4
.align 2
  .L001B89E0:
    /* B89E0 001B89E0 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B89E4 001B89E4 2D300002 */  daddu      $6, $16, $0
    /* B89E8 001B89E8 40010524 */  addiu      $5, $0, 0x140
    /* B89EC 001B89EC 3EE8040C */  jal        func_0013A0F8
    /* B89F0 001B89F0 05010724 */   addiu     $7, $0, 0x105
    /* B89F4 001B89F4 9401468E */  lw         $6, 0x194($18)
    /* B89F8 001B89F8 FEFF0A24 */  addiu      $10, $0, -0x2
    /* B89FC 001B89FC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* B8A00 001B8A00 00008144 */  mtc1       $1, $f0
    /* B8A04 001B8A04 FDFF0924 */  addiu      $9, $0, -0x3
    /* B8A08 001B8A08 4008C2AC */  sw         $2, 0x840($6)
    /* B8A0C 001B8A0C FBFF0824 */  addiu      $8, $0, -0x5
    /* B8A10 001B8A10 2D280000 */  daddu      $5, $0, $0
    /* B8A14 001B8A14 03000724 */  addiu      $7, $0, 0x3
.align 2
  .L001B8A18:
    /* B8A18 001B8A18 4008C48C */  lw         $4, 0x840($6)
    /* B8A1C 001B8A1C FFFFE724 */  addiu      $7, $7, -0x1
    /* B8A20 001B8A20 2120A400 */  addu       $4, $5, $4
    /* B8A24 001B8A24 380082DC */  ld         $2, 0x38($4)
    /* B8A28 001B8A28 24104A00 */  and        $2, $2, $10
    /* B8A2C 001B8A2C 380082FC */  sd         $2, 0x38($4)
    /* B8A30 001B8A30 9401438E */  lw         $3, 0x194($18)
    /* B8A34 001B8A34 4008648C */  lw         $4, 0x840($3)
    /* B8A38 001B8A38 2120A400 */  addu       $4, $5, $4
    /* B8A3C 001B8A3C 380082DC */  ld         $2, 0x38($4)
    /* B8A40 001B8A40 24104900 */  and        $2, $2, $9
    /* B8A44 001B8A44 380082FC */  sd         $2, 0x38($4)
    /* B8A48 001B8A48 9401438E */  lw         $3, 0x194($18)
    /* B8A4C 001B8A4C 4008628C */  lw         $2, 0x840($3)
    /* B8A50 001B8A50 2110A200 */  addu       $2, $5, $2
    /* B8A54 001B8A54 380043DC */  ld         $3, 0x38($2)
    /* B8A58 001B8A58 400040AC */  sw         $0, 0x40($2)
    /* B8A5C 001B8A5C 24186800 */  and        $3, $3, $8
    /* B8A60 001B8A60 440040AC */  sw         $0, 0x44($2)
    /* B8A64 001B8A64 380043FC */  sd         $3, 0x38($2)
    /* B8A68 001B8A68 480040AC */  sw         $0, 0x48($2)
    /* B8A6C 001B8A6C 9401448E */  lw         $4, 0x194($18)
    /* B8A70 001B8A70 4C0040E4 */  swc1       $f0, 0x4C($2)
    /* B8A74 001B8A74 4008838C */  lw         $3, 0x840($4)
    /* B8A78 001B8A78 2D308000 */  daddu      $6, $4, $0
    /* B8A7C 001B8A7C 2118A300 */  addu       $3, $5, $3
    /* B8A80 001B8A80 280060E4 */  swc1       $f0, 0x28($3)
    /* B8A84 001B8A84 5000A524 */  addiu      $5, $5, 0x50
    /* B8A88 001B8A88 300060AC */  sw         $0, 0x30($3)
    /* B8A8C 001B8A8C 340060E4 */  swc1       $f0, 0x34($3)
    /* B8A90 001B8A90 3A0060A4 */  sh         $0, 0x3A($3)
    /* B8A94 001B8A94 200060E4 */  swc1       $f0, 0x20($3)
    /* B8A98 001B8A98 DFFFE104 */  bgez       $7, .L001B8A18
    /* B8A9C 001B8A9C 240060E4 */   swc1      $f0, 0x24($3)
    /* B8AA0 001B8AA0 02000224 */  addiu      $2, $0, 0x2
    /* B8AA4 001B8AA4 2D288002 */  daddu      $5, $20, $0
    /* B8AA8 001B8AA8 180882A4 */  sh         $2, 0x818($4)
    /* B8AAC 001B8AAC C47C060C */  jal        func_0019F310
    /* B8AB0 001B8AB0 06000424 */   addiu     $4, $0, 0x6
    /* B8AB4 001B8AB4 0C00438C */  lw         $3, 0xC($2)
    /* B8AB8 001B8AB8 05006010 */  beqz       $3, .L001B8AD0
    /* B8ABC 001B8ABC 980142AE */   sw        $2, 0x198($18)
    /* B8AC0 001B8AC0 FF0F043C */  lui        $4, (0xFFFFFFF >> 16)
    /* B8AC4 001B8AC4 FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B8AC8 001B8AC8 66E5040C */  jal        func_00139598
    /* B8ACC 001B8ACC 24206400 */   and       $4, $3, $4
.align 2
  .L001B8AD0:
    /* B8AD0 001B8AD0 9801468E */  lw         $6, 0x198($18)
    /* B8AD4 001B8AD4 1000C28C */  lw         $2, 0x10($6)
    /* B8AD8 001B8AD8 05004010 */  beqz       $2, .L001B8AF0
    /* B8ADC 001B8ADC FF0F043C */   lui       $4, (0xFFFFFFF >> 16)
    /* B8AE0 001B8AE0 FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B8AE4 001B8AE4 66E5040C */  jal        func_00139598
    /* B8AE8 001B8AE8 24204400 */   and       $4, $2, $4
    /* B8AEC 001B8AEC 9801468E */  lw         $6, 0x198($18)
.align 2
  .L001B8AF0:
    /* B8AF0 001B8AF0 5085D026 */  addiu      $16, $22, %lo(D_00618550)
    /* B8AF4 001B8AF4 1000C0AC */  sw         $0, 0x10($6)
    /* B8AF8 001B8AF8 0C00C0AC */  sw         $0, 0xC($6)
    /* B8AFC 001B8AFC 00010524 */  addiu      $5, $0, 0x100
    /* B8B00 001B8B00 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B8B04 001B8B04 2D300002 */  daddu      $6, $16, $0
    /* B8B08 001B8B08 3EE8040C */  jal        func_0013A0F8
    /* B8B0C 001B8B0C 08010724 */   addiu     $7, $0, 0x108
    /* B8B10 001B8B10 9801438E */  lw         $3, 0x198($18)
    /* B8B14 001B8B14 40000524 */  addiu      $5, $0, 0x40
    /* B8B18 001B8B18 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B8B1C 001B8B1C 2D300002 */  daddu      $6, $16, $0
    /* B8B20 001B8B20 0C0062AC */  sw         $2, 0xC($3)
    /* B8B24 001B8B24 3EE8040C */  jal        func_0013A0F8
    /* B8B28 001B8B28 08010724 */   addiu     $7, $0, 0x108
    /* B8B2C 001B8B2C 9801438E */  lw         $3, 0x198($18)
    /* B8B30 001B8B30 04000424 */  addiu      $4, $0, 0x4
    /* B8B34 001B8B34 4008658C */  lw         $5, 0x840($3)
    /* B8B38 001B8B38 100062AC */  sw         $2, 0x10($3)
    /* B8B3C 001B8B3C 0500A010 */  beqz       $5, .L001B8B54
    /* B8B40 001B8B40 080064AC */   sw        $4, 0x8($3)
    /* B8B44 001B8B44 FF0F043C */  lui        $4, (0xFFFFFFF >> 16)
    /* B8B48 001B8B48 FFFF8434 */  ori        $4, $4, (0xFFFFFFF & 0xFFFF)
    /* B8B4C 001B8B4C 66E5040C */  jal        func_00139598
    /* B8B50 001B8B50 2420A400 */   and       $4, $5, $4
.align 2
  .L001B8B54:
    /* B8B54 001B8B54 3497848F */  lw         $4, (D_00632024) /* gp_rel: (D_00632024) */
    /* B8B58 001B8B58 2D300002 */  daddu      $6, $16, $0
    /* B8B5C 001B8B5C 40010524 */  addiu      $5, $0, 0x140
    /* B8B60 001B8B60 3EE8040C */  jal        func_0013A0F8
    /* B8B64 001B8B64 08010724 */   addiu     $7, $0, 0x108
    /* B8B68 001B8B68 9801468E */  lw         $6, 0x198($18)
    /* B8B6C 001B8B6C FEFF0A24 */  addiu      $10, $0, -0x2
    /* B8B70 001B8B70 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* B8B74 001B8B74 00008144 */  mtc1       $1, $f0
    /* B8B78 001B8B78 FDFF0924 */  addiu      $9, $0, -0x3
    /* B8B7C 001B8B7C 4008C2AC */  sw         $2, 0x840($6)
    /* B8B80 001B8B80 FBFF0824 */  addiu      $8, $0, -0x5
    /* B8B84 001B8B84 2D280000 */  daddu      $5, $0, $0
    /* B8B88 001B8B88 03000724 */  addiu      $7, $0, 0x3
    /* B8B8C 001B8B8C 00000000 */  nop
.align 2
  .L001B8B90:
    /* B8B90 001B8B90 4008C48C */  lw         $4, 0x840($6)
    /* B8B94 001B8B94 FFFFE724 */  addiu      $7, $7, -0x1
    /* B8B98 001B8B98 2120A400 */  addu       $4, $5, $4
    /* B8B9C 001B8B9C 380082DC */  ld         $2, 0x38($4)
    /* B8BA0 001B8BA0 24104A00 */  and        $2, $2, $10
    /* B8BA4 001B8BA4 380082FC */  sd         $2, 0x38($4)
    /* B8BA8 001B8BA8 9801438E */  lw         $3, 0x198($18)
    /* B8BAC 001B8BAC 4008648C */  lw         $4, 0x840($3)
    /* B8BB0 001B8BB0 2120A400 */  addu       $4, $5, $4
    /* B8BB4 001B8BB4 380082DC */  ld         $2, 0x38($4)
    /* B8BB8 001B8BB8 24104900 */  and        $2, $2, $9
    /* B8BBC 001B8BBC 380082FC */  sd         $2, 0x38($4)
    /* B8BC0 001B8BC0 9801438E */  lw         $3, 0x198($18)
    /* B8BC4 001B8BC4 4008628C */  lw         $2, 0x840($3)
    /* B8BC8 001B8BC8 2110A200 */  addu       $2, $5, $2
    /* B8BCC 001B8BCC 380043DC */  ld         $3, 0x38($2)
    /* B8BD0 001B8BD0 400040AC */  sw         $0, 0x40($2)
    /* B8BD4 001B8BD4 24186800 */  and        $3, $3, $8
    /* B8BD8 001B8BD8 440040AC */  sw         $0, 0x44($2)
    /* B8BDC 001B8BDC 380043FC */  sd         $3, 0x38($2)
    /* B8BE0 001B8BE0 480040AC */  sw         $0, 0x48($2)
    /* B8BE4 001B8BE4 9801448E */  lw         $4, 0x198($18)
    /* B8BE8 001B8BE8 4C0040E4 */  swc1       $f0, 0x4C($2)
    /* B8BEC 001B8BEC 4008838C */  lw         $3, 0x840($4)
    /* B8BF0 001B8BF0 2D308000 */  daddu      $6, $4, $0
    /* B8BF4 001B8BF4 2118A300 */  addu       $3, $5, $3
    /* B8BF8 001B8BF8 280060E4 */  swc1       $f0, 0x28($3)
    /* B8BFC 001B8BFC 5000A524 */  addiu      $5, $5, 0x50
    /* B8C00 001B8C00 300060AC */  sw         $0, 0x30($3)
    /* B8C04 001B8C04 340060E4 */  swc1       $f0, 0x34($3)
    /* B8C08 001B8C08 3A0060A4 */  sh         $0, 0x3A($3)
    /* B8C0C 001B8C0C 200060E4 */  swc1       $f0, 0x20($3)
    /* B8C10 001B8C10 DFFFE104 */  bgez       $7, .L001B8B90
    /* B8C14 001B8C14 240060E4 */   swc1      $f0, 0x24($3)
    /* B8C18 001B8C18 02000224 */  addiu      $2, $0, 0x2
    /* B8C1C 001B8C1C 1D000010 */  b          .L001B8C94
    /* B8C20 001B8C20 180882A4 */   sh        $2, 0x818($4)
.align 2
  .L001B8C24:
    /* B8C24 001B8C24 6200023C */  lui        $2, %hi(D_00618550)
    /* B8C28 001B8C28 50855424 */  addiu      $20, $2, %lo(D_00618550)
    /* B8C2C 001B8C2C D0EA7324 */  addiu      $19, $3, %lo(D_004BEAD0)
    /* B8C30 001B8C30 FFFF1E24 */  addiu      $30, $0, -0x1
    /* B8C34 001B8C34 6200173C */  lui        $23, %hi(D_00618560)
    /* B8C38 001B8C38 6300163C */  lui        $22, %hi(D_00633210)
    /* B8C3C 001B8C3C 70015026 */  addiu      $16, $18, 0x170
    /* B8C40 001B8C40 08001124 */  addiu      $17, $0, 0x8
    /* B8C44 001B8C44 00000000 */  nop
.align 2
  .L001B8C48:
    /* B8C48 001B8C48 0000658E */  lw         $5, 0x0($19)
    /* B8C4C 001B8C4C C427040C */  jal        func_00109F10
    /* B8C50 001B8C50 2D20A002 */   daddu     $4, $21, $0
    /* B8C54 001B8C54 09005E14 */  bne        $2, $30, .L001B8C7C
    /* B8C58 001B8C58 000002AE */   sw        $2, 0x0($16)
    /* B8C5C 001B8C5C 2D208002 */  daddu      $4, $20, $0
    /* B8C60 001B8C60 0D010524 */  addiu      $5, $0, 0x10D
    /* B8C64 001B8C64 D2B5060C */  jal        func_001AD748
    /* B8C68 001B8C68 6085E626 */   addiu     $6, $23, %lo(D_00618560)
    /* B8C6C 001B8C6C 2D208002 */  daddu      $4, $20, $0
    /* B8C70 001B8C70 0D010524 */  addiu      $5, $0, 0x10D
    /* B8C74 001B8C74 FC8F090C */  jal        func_00263FF0
    /* B8C78 001B8C78 1032C626 */   addiu     $6, $22, %lo(D_00633210)
.align 2
  .L001B8C7C:
    /* B8C7C 001B8C7C 04001026 */  addiu      $16, $16, 0x4
    /* B8C80 001B8C80 FFFF3126 */  addiu      $17, $17, -0x1
    /* B8C84 001B8C84 F0FF2106 */  bgez       $17, .L001B8C48
    /* B8C88 001B8C88 04007326 */   addiu     $19, $19, 0x4
    /* B8C8C 001B8C8C 980140AE */  sw         $0, 0x198($18)
    /* B8C90 001B8C90 940140AE */  sw         $0, 0x194($18)
.align 2
  .L001B8C94:
    /* B8C94 001B8C94 0A000424 */  addiu      $4, $0, 0xA
    /* B8C98 001B8C98 2D280000 */  daddu      $5, $0, $0
    /* B8C9C 001B8C9C E43B070C */  jal        func_001CEF90
    /* B8CA0 001B8CA0 0A000624 */   addiu     $6, $0, 0xA
    /* B8CA4 001B8CA4 9C0142AE */  sw         $2, 0x19C($18)
    /* B8CA8 001B8CA8 2D104002 */  daddu      $2, $18, $0
    /* B8CAC 001B8CAC D000BFDF */  ld         $31, 0xD0($29)
    /* B8CB0 001B8CB0 C000BEDF */  ld         $30, 0xC0($29)
    /* B8CB4 001B8CB4 B000B7DF */  ld         $23, 0xB0($29)
    /* B8CB8 001B8CB8 A000B6DF */  ld         $22, 0xA0($29)
    /* B8CBC 001B8CBC 9000B5DF */  ld         $21, 0x90($29)
    /* B8CC0 001B8CC0 8000B4DF */  ld         $20, 0x80($29)
    /* B8CC4 001B8CC4 7000B3DF */  ld         $19, 0x70($29)
    /* B8CC8 001B8CC8 6000B2DF */  ld         $18, 0x60($29)
    /* B8CCC 001B8CCC 5000B1DF */  ld         $17, 0x50($29)
    /* B8CD0 001B8CD0 4000B0DF */  ld         $16, 0x40($29)
    /* B8CD4 001B8CD4 0800E003 */  jr         $31
    /* B8CD8 001B8CD8 E000BD27 */   addiu     $29, $29, 0xE0
endlabel func_001B8720
    /* B8CDC 001B8CDC 00000000 */  nop
```
