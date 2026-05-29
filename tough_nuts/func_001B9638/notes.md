# func_001B9638 — parked

VRAM: 0x001B9638 (file_off 0x0B9638)
Asm source: asm/nonmatchings/src/a_p_1/func_001B9638.s

## Attempt at 2026-05-29

**Reason parked:** best=108 (from 138). Structural fixes landed: pin bb=$16/s1=$17/k=$19 (regalloc-swap cascade 136->125), single work-var buf-selection reusing d->_88/_94 value (beql idiom, 125->119), pin work value sel to $2 (119->108). RESIDUAL ROOT: GCSE caches &m10 (sp+0x10, loop-invariant, used 8x) in an extra callee-saved (s4), displacing d-base %hi to s5 -> frame -192 vs -176; this s4/s5 renumber accounts for ~20 of the 108 sites incl the blk2-4 d-base/FP cluster. Documented pointer-reuse-forces-remat shape (func_00194840) - permuter cracked that, hand cannot. -fno-gcse fixes the frame but (a) only nets -2 here and (b) breaks 2 siblings (func_001B94B0, func_001BA090) since the TU is one source file = GCSE-on. ~31 distinct hand hypotheses tried (pins/reorders/barriers/struct/count-up/caller-saved-pins/GCSE). For offline auto_permute.

**TU:** `src/a_p_1.c`

**Seed:** `tough_nuts/func_001B9638/func_001B9638.1.c`

Disassembly:

```
.align 3
nonmatching func_001B9638, 0x378

glabel func_001B9638
    /* B9638 001B9638 50FFBD27 */  addiu      $29, $29, -0xB0
    /* B963C 001B963C 7000B2FF */  sd         $18, 0x70($29)
    /* B9640 001B9640 A000BFFF */  sd         $31, 0xA0($29)
    /* B9644 001B9644 2D908000 */  daddu      $18, $4, $0
    /* B9648 001B9648 9000B4FF */  sd         $20, 0x90($29)
    /* B964C 001B964C 8000B3FF */  sd         $19, 0x80($29)
    /* B9650 001B9650 6000B1FF */  sd         $17, 0x60($29)
    /* B9654 001B9654 5000B0FF */  sd         $16, 0x50($29)
    /* B9658 001B9658 5C01478E */  lw         $7, 0x15C($18)
    /* B965C 001B965C 0000E28C */  lw         $2, 0x0($7)
    /* B9660 001B9660 05004010 */  beqz       $2, .L001B9678
    /* B9664 001B9664 2700023C */   lui       $2, %hi(D_00274EC0)
    /* B9668 001B9668 4C7D060C */  jal        func_0019F530
    /* B966C 001B966C 00000000 */   nop
    /* B9670 001B9670 5C01478E */  lw         $7, 0x15C($18)
    /* B9674 001B9674 2700023C */  lui        $2, %hi(D_00274EC0)
.align 2
  .L001B9678:
    /* B9678 001B9678 0A000624 */  addiu      $6, $0, 0xA
    /* B967C 001B967C C04E458C */  lw         $5, %lo(D_00274EC0)($2)
    /* B9680 001B9680 3C000324 */  addiu      $3, $0, 0x3C
    /* B9684 001B9684 C04E4224 */  addiu      $2, $2, %lo(D_00274EC0)
    /* B9688 001B9688 7042013C */  lui        $1, (0x42700000 >> 16)
    /* B968C 001B968C 00188144 */  mtc1       $1, $f3
    /* B9690 001B9690 1828A600 */  mult       $5, $5, $6
    /* B9694 001B9694 0400448C */  lw         $4, 0x4($2)
    /* B9698 001B9698 003F013C */  lui        $1, (0x3F000000 >> 16)
    /* B969C 001B969C 00088144 */  mtc1       $1, $f1
    /* B96A0 001B96A0 4C00143C */  lui        $20, %hi(D_004BECD0)
    /* B96A4 001B96A4 01008050 */  beql       $4, $0, .L001B96AC
    /* B96A8 001B96A8 CD010000 */   break     0, 7
.align 2
  .L001B96AC:
    /* B96AC 001B96AC D0EC9026 */  addiu      $16, $20, %lo(D_004BECD0)
    /* B96B0 001B96B0 23186500 */  subu       $3, $3, $5
    /* B96B4 001B96B4 3401E2C4 */  lwc1       $f2, 0x134($7)
    /* B96B8 001B96B8 1A006400 */  div        $0, $3, $4
    /* B96BC 001B96BC 12180000 */  mflo       $3
    /* B96C0 001B96C0 00008344 */  mtc1       $3, $f0
    /* B96C4 001B96C4 20008046 */  cvt.s.w    $f0, $f0
    /* B96C8 001B96C8 00000000 */  nop
    /* B96CC 001B96CC 00000000 */  nop
    /* B96D0 001B96D0 C3180046 */  div.s      $f3, $f3, $f0
    /* B96D4 001B96D4 42180146 */  mul.s      $f1, $f3, $f1
    /* B96D8 001B96D8 42080346 */  mul.s      $f1, $f1, $f3
    /* B96DC 001B96DC 80100146 */  add.s      $f2, $f2, $f1
    /* B96E0 001B96E0 3401E2E4 */  swc1       $f2, 0x134($7)
    /* B96E4 001B96E4 5C01468E */  lw         $6, 0x15C($18)
    /* B96E8 001B96E8 A000C424 */  addiu      $4, $6, 0xA0
    /* B96EC 001B96EC 3001C624 */  addiu      $6, $6, 0x130
    /* B96F0 001B96F0 E260040C */  jal        func_00118388
    /* B96F4 001B96F4 2D288000 */   daddu     $5, $4, $0
    /* B96F8 001B96F8 5C01458E */  lw         $5, 0x15C($18)
    /* B96FC 001B96FC 2D200002 */  daddu      $4, $16, $0
    /* B9700 001B9700 C017040C */  jal        func_00105F00
    /* B9704 001B9704 F001A524 */   addiu     $5, $5, 0x1F0
    /* B9708 001B9708 5C01458E */  lw         $5, 0x15C($18)
    /* B970C 001B970C 10000426 */  addiu      $4, $16, 0x10
    /* B9710 001B9710 C017040C */  jal        func_00105F00
    /* B9714 001B9714 A000A524 */   addiu     $5, $5, 0xA0
    /* B9718 001B9718 040000C6 */  lwc1       $f0, 0x4($16)
    /* B971C 001B971C 2D200002 */  daddu      $4, $16, $0
    /* B9720 001B9720 4842013C */  lui        $1, (0x42480000 >> 16)
    /* B9724 001B9724 00088144 */  mtc1       $1, $f1
    /* B9728 001B9728 01000146 */  sub.s      $f0, $f0, $f1
    /* B972C 001B972C 78A1050C */  jal        func_001685E0
    /* B9730 001B9730 040000E6 */   swc1      $f0, 0x4($16)
    /* B9734 001B9734 8800028E */  lw         $2, 0x88($16)
    /* B9738 001B9738 08004050 */  beql       $2, $0, .L001B975C
    /* B973C 001B973C 9400028E */   lw        $2, 0x94($16)
    /* B9740 001B9740 0800A2AF */  sw         $2, 0x8($29)
    /* B9744 001B9744 8700036A */  ldl        $3, 0x87($16)
    /* B9748 001B9748 8000036E */  ldr        $3, 0x80($16)
    /* B974C 001B974C 0700A3B3 */  sdl        $3, 0x7($29)
    /* B9750 001B9750 0000A3B7 */  sdr        $3, 0x0($29)
    /* B9754 001B9754 09000010 */  b          .L001B977C
    /* B9758 001B9758 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001B975C:
    /* B975C 001B975C 07004050 */  beql       $2, $0, .L001B977C
    /* B9760 001B9760 2D100000 */   daddu     $2, $0, $0
    /* B9764 001B9764 0800A2AF */  sw         $2, 0x8($29)
    /* B9768 001B9768 9300036A */  ldl        $3, 0x93($16)
    /* B976C 001B976C 8C00036E */  ldr        $3, 0x8C($16)
    /* B9770 001B9770 0700A3B3 */  sdl        $3, 0x7($29)
    /* B9774 001B9774 0000A3B7 */  sdr        $3, 0x0($29)
    /* B9778 001B9778 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L001B977C:
    /* B977C 001B977C 68004010 */  beqz       $2, .L001B9920
    /* B9780 001B9780 4C00103C */   lui       $16, %hi(D_004BECF0)
    /* B9784 001B9784 5C01448E */  lw         $4, 0x15C($18)
    /* B9788 001B9788 F0EC1026 */  addiu      $16, $16, %lo(D_004BECF0)
    /* B978C 001B978C 03001324 */  addiu      $19, $0, 0x3
    /* B9790 001B9790 2D280002 */  daddu      $5, $16, $0
    /* B9794 001B9794 C017040C */  jal        func_00105F00
    /* B9798 001B9798 A0008424 */   addiu     $4, $4, 0xA0
    /* B979C 001B979C 5C01448E */  lw         $4, 0x15C($18)
    /* B97A0 001B97A0 2700053C */  lui        $5, %hi(D_00275850)
    /* B97A4 001B97A4 5058A524 */  addiu      $5, $5, %lo(D_00275850)
    /* B97A8 001B97A8 C017040C */  jal        func_00105F00
    /* B97AC 001B97AC 30018424 */   addiu     $4, $4, 0x130
    /* B97B0 001B97B0 80000526 */  addiu      $5, $16, 0x80
    /* B97B4 001B97B4 38E3060C */  jal        func_001B8CE0
    /* B97B8 001B97B8 2D204002 */   daddu     $4, $18, $0
    /* B97BC 001B97BC 2D204002 */  daddu      $4, $18, $0
    /* B97C0 001B97C0 3A7D060C */  jal        func_0019F4E8
    /* B97C4 001B97C4 2D28A003 */   daddu     $5, $29, $0
    /* B97C8 001B97C8 160A040C */  jal        func_00102858
    /* B97CC 001B97CC 2D204002 */   daddu     $4, $18, $0
    /* B97D0 001B97D0 5C01428E */  lw         $2, 0x15C($18)
    /* B97D4 001B97D4 4C00103C */  lui        $16, %hi(D_004BEBA0)
    /* B97D8 001B97D8 A0EB1026 */  addiu      $16, $16, %lo(D_004BEBA0)
    /* B97DC 001B97DC 1000A427 */  addiu      $4, $29, 0x10
    /* B97E0 001B97E0 0008518C */  lw         $17, 0x800($2)
    /* B97E4 001B97E4 5010040C */  jal        func_00104140
    /* B97E8 001B97E8 2D284002 */   daddu     $5, $18, $0
    /* B97EC 001B97EC 20003126 */  addiu      $17, $17, 0x20
.align 2
  .L001B97F0:
    /* B97F0 001B97F0 2D202002 */  daddu      $4, $17, $0
    /* B97F4 001B97F4 2D300002 */  daddu      $6, $16, $0
    /* B97F8 001B97F8 1000A527 */  addiu      $5, $29, 0x10
    /* B97FC 001B97FC 9261040C */  jal        func_00118648
    /* B9800 001B9800 FFFF7326 */   addiu     $19, $19, -0x1
    /* B9804 001B9804 10002426 */  addiu      $4, $17, 0x10
    /* B9808 001B9808 2D300002 */  daddu      $6, $16, $0
    /* B980C 001B980C 1000A527 */  addiu      $5, $29, 0x10
    /* B9810 001B9810 9261040C */  jal        func_00118648
    /* B9814 001B9814 10001026 */   addiu     $16, $16, 0x10
    /* B9818 001B9818 F5FF6106 */  bgez       $19, .L001B97F0
    /* B981C 001B981C 50003126 */   addiu     $17, $17, 0x50
    /* B9820 001B9820 D0EC9026 */  addiu      $16, $20, %lo(D_004BECD0)
    /* B9824 001B9824 8800028E */  lw         $2, 0x88($16)
    /* B9828 001B9828 06004010 */  beqz       $2, .L001B9844
    /* B982C 001B982C 2D204002 */   daddu     $4, $18, $0
    /* B9830 001B9830 90A2050C */  jal        func_00168A40
    /* B9834 001B9834 2D200002 */   daddu     $4, $16, $0
    /* B9838 001B9838 5C01438E */  lw         $3, 0x15C($18)
    /* B983C 001B983C F80562AC */  sw         $2, 0x5F8($3)
    /* B9840 001B9840 2D204002 */  daddu      $4, $18, $0
.align 2
  .L001B9844:
    /* B9844 001B9844 1A28040C */  jal        func_0010A068
    /* B9848 001B9848 40000524 */   addiu     $5, $0, 0x40
    /* B984C 001B984C 05004014 */  bnez       $2, .L001B9864
    /* B9850 001B9850 2D204002 */   daddu     $4, $18, $0
    /* B9854 001B9854 1A28040C */  jal        func_0010A068
    /* B9858 001B9858 50000524 */   addiu     $5, $0, 0x50
    /* B985C 001B985C 10004050 */  beql       $2, $0, .L001B98A0
    /* B9860 001B9860 D0EC9026 */   addiu     $16, $20, %lo(D_004BECD0)
.align 2
  .L001B9864:
    /* B9864 001B9864 1E34040C */  jal        func_0010D078
    /* B9868 001B9868 8000048E */   lw        $4, 0x80($16)
    /* B986C 001B986C 5C01428E */  lw         $2, 0x15C($18)
    /* B9870 001B9870 4842013C */  lui        $1, (0x42480000 >> 16)
    /* B9874 001B9874 00108144 */  mtc1       $1, $f2
    /* B9878 001B9878 A40041C4 */  lwc1       $f1, 0xA4($2)
    /* B987C 001B987C 40080246 */  add.s      $f1, $f1, $f2
    /* B9880 001B9880 34000146 */  c.lt.s     $f0, $f1
    /* B9884 001B9884 00000000 */  nop
    /* B9888 001B9888 04000045 */  bc1f       .L001B989C
    /* B988C 001B988C 2D204002 */   daddu     $4, $18, $0
    /* B9890 001B9890 26000524 */  addiu      $5, $0, 0x26
    /* B9894 001B9894 E2FF040C */  jal        func_0013FF88
    /* B9898 001B9898 2D304002 */   daddu     $6, $18, $0
.align 2
  .L001B989C:
    /* B989C 001B989C D0EC9026 */  addiu      $16, $20, %lo(D_004BECD0)
.align 2
  .L001B98A0:
    /* B98A0 001B98A0 9400028E */  lw         $2, 0x94($16)
    /* B98A4 001B98A4 3A004010 */  beqz       $2, .L001B9990
    /* B98A8 001B98A8 2D100000 */   daddu     $2, $0, $0
    /* B98AC 001B98AC 98A2050C */  jal        func_00168A60
    /* B98B0 001B98B0 2D200002 */   daddu     $4, $16, $0
    /* B98B4 001B98B4 5C01438E */  lw         $3, 0x15C($18)
    /* B98B8 001B98B8 2D204002 */  daddu      $4, $18, $0
    /* B98BC 001B98BC 40000524 */  addiu      $5, $0, 0x40
    /* B98C0 001B98C0 1228040C */  jal        func_0010A048
    /* B98C4 001B98C4 F80562AC */   sw        $2, 0x5F8($3)
    /* B98C8 001B98C8 05004014 */  bnez       $2, .L001B98E0
    /* B98CC 001B98CC 2D204002 */   daddu     $4, $18, $0
    /* B98D0 001B98D0 1228040C */  jal        func_0010A048
    /* B98D4 001B98D4 50000524 */   addiu     $5, $0, 0x50
    /* B98D8 001B98D8 2D004010 */  beqz       $2, .L001B9990
    /* B98DC 001B98DC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001B98E0:
    /* B98E0 001B98E0 1E34040C */  jal        func_0010D078
    /* B98E4 001B98E4 8C00048E */   lw        $4, 0x8C($16)
    /* B98E8 001B98E8 5C01428E */  lw         $2, 0x15C($18)
    /* B98EC 001B98EC 4842013C */  lui        $1, (0x42480000 >> 16)
    /* B98F0 001B98F0 00108144 */  mtc1       $1, $f2
    /* B98F4 001B98F4 A40041C4 */  lwc1       $f1, 0xA4($2)
    /* B98F8 001B98F8 40080246 */  add.s      $f1, $f1, $f2
    /* B98FC 001B98FC 34000146 */  c.lt.s     $f0, $f1
    /* B9900 001B9900 00000000 */  nop
    /* B9904 001B9904 04000045 */  bc1f       .L001B9918
    /* B9908 001B9908 2D204002 */   daddu     $4, $18, $0
    /* B990C 001B990C 26000524 */  addiu      $5, $0, 0x26
    /* B9910 001B9910 E2FF040C */  jal        func_0013FF88
    /* B9914 001B9914 2D308000 */   daddu     $6, $4, $0
.align 2
  .L001B9918:
    /* B9918 001B9918 1D000010 */  b          .L001B9990
    /* B991C 001B991C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001B9920:
    /* B9920 001B9920 D0EC9026 */  addiu      $16, $20, %lo(D_004BECD0)
    /* B9924 001B9924 FA43013C */  lui        $1, (0x43FA0000 >> 16)
    /* B9928 001B9928 00088144 */  mtc1       $1, $f1
    /* B992C 001B992C 140000C6 */  lwc1       $f0, 0x14($16)
    /* B9930 001B9930 2D200002 */  daddu      $4, $16, $0
    /* B9934 001B9934 00000146 */  add.s      $f0, $f0, $f1
    /* B9938 001B9938 4EA1050C */  jal        func_00168538
    /* B993C 001B993C 140000E6 */   swc1      $f0, 0x14($16)
    /* B9940 001B9940 5C01468E */  lw         $6, 0x15C($18)
    /* B9944 001B9944 2D200002 */  daddu      $4, $16, $0
    /* B9948 001B9948 4842013C */  lui        $1, (0x42480000 >> 16)
    /* B994C 001B994C 00608144 */  mtc1       $1, $f12
    /* B9950 001B9950 2D284002 */  daddu      $5, $18, $0
    /* B9954 001B9954 E418040C */  jal        func_00106390
    /* B9958 001B9958 A000C624 */   addiu     $6, $6, 0xA0
    /* B995C 001B995C 02000324 */  addiu      $3, $0, 0x2
    /* B9960 001B9960 0B004314 */  bne        $2, $3, .L001B9990
    /* B9964 001B9964 FFFF0224 */   addiu     $2, $0, -0x1
    /* B9968 001B9968 5C01448E */  lw         $4, 0x15C($18)
    /* B996C 001B996C 2700053C */  lui        $5, %hi(D_00275850)
    /* B9970 001B9970 5058A524 */  addiu      $5, $5, %lo(D_00275850)
    /* B9974 001B9974 C017040C */  jal        func_00105F00
    /* B9978 001B9978 30018424 */   addiu     $4, $4, 0x130
    /* B997C 001B997C 2D204002 */  daddu      $4, $18, $0
    /* B9980 001B9980 1A000524 */  addiu      $5, $0, 0x1A
    /* B9984 001B9984 E2FF040C */  jal        func_0013FF88
    /* B9988 001B9988 2D308000 */   daddu     $6, $4, $0
    /* B998C 001B998C FFFF0224 */  addiu      $2, $0, -0x1
.align 2
  .L001B9990:
    /* B9990 001B9990 A000BFDF */  ld         $31, 0xA0($29)
    /* B9994 001B9994 9000B4DF */  ld         $20, 0x90($29)
    /* B9998 001B9998 8000B3DF */  ld         $19, 0x80($29)
    /* B999C 001B999C 7000B2DF */  ld         $18, 0x70($29)
    /* B99A0 001B99A0 6000B1DF */  ld         $17, 0x60($29)
    /* B99A4 001B99A4 5000B0DF */  ld         $16, 0x50($29)
    /* B99A8 001B99A8 0800E003 */  jr         $31
    /* B99AC 001B99AC B000BD27 */   addiu     $29, $29, 0xB0
endlabel func_001B9638
```

## UPDATE (permuter Step-4b crack): best 108 -> 106, FRAME FIXED (-176)

The 5-min permuter shot on the 108 seed found the m10 lever (score 5410):
**reuse the $2-pinned `sel` variable to hold `(int)m10`** —
`sel = (int)m10; func_00104140(sel,self); ... func_00118648(.., sel, ..)`.
Because $2 is caller-saved, the calls clobber it, so gcc rematerializes
`&m10` instead of parking it in a callee-saved -> frame -192 -> -176, the
whole s4/s5 d-base renumber cascade gone. Re-applied cleanly by hand (the
seed already pins bb/s1/k and sel=$2). Verified: inline `(int)m10` in the
loop reverts to -192, so the loop MUST consume `sel` for the matrix.

Residual 106 (scheduling/regalloc tail, NOT structural):
 - v0->a1 copy each call (`daddu a1,v0` vs orig `addiu a1,sp,16`): 2 sites,
   inherent to routing m10 through the $2 var; couldn't eliminate by hand
   ($5-pin / per-call reassign both regressed).
 - q-divide/0x134 block (blk2-4): self->15C lands in t0 vs orig a3; const
   10 in a0 vs a2; div/lwc1 order; $f2 vs $f3. Caching self->15C didn't move it.
 - buf.ll sdl/sdr store placement (blk8,10).
Frame-fix was the headline; the rest is the low-yield scheduling tail.
Left for offline auto_permute to chew the tail.

## 2nd permuter shot (at the 106 30-stall): no VALID improvement -> chase terminated
Lower-real_count outputs were all semantically invalid false-minima:
 - output-4975 (rc102): moves func_00102858 into the q-block (early). Original
   calls it LATE (B97C8, after func_0019F4E8, before func_00104140) -> permanent
   >=2-line call-position diff, cannot reach 0.
 - output-5090 (rc96): drops the (float*) cast on the 0x134 store
   (`*(char*)(p+0x134) = floatexpr`) -> emits sb+convert instead of swc1; wrong.
On-path outputs (correct call order + correct store) did not beat 106.
=> Valid floor for hand+permuter is 106 (frame fixed; scheduling/regalloc tail:
   self->15C temp choice, FP $f2/$f3, prologue self->s2 timing, v0->a1 copy).
   Left for offline auto_permute.
