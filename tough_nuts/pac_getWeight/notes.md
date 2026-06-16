# pac_getWeight (seki/src/Packet, func_00119090, 0x21C) — near-miss notes

## State: rc17 (void) / rc14 (int) ; structure CORRECT. Residual = coupled gcc artifact.

Seed C lives in Packet.with_getWeight.c (the void@17 version). To resume:
apply that getWeight body into seki/src/Packet.c, `match_loop reset`, re-attack the
a1/frame cluster (permuter-class).

## What's SOLVED (do not re-derive):
- **VOID return**, not int. `dl_GetPri()` called (not returned) -> TCO sibcall `j dl_GetPri`
  (matches expected .1A0 NOT setting v0). int-return gives `jal`+`jr ra` (never sibcalls here,
  even with single exit — confirmed). No external callers, so void is observationally safe.
- Dispatch = nested `switch(a0)` / `switch(a1)` / `switch(a2)` / `switch(a3)` -> gcc binary-search
  tree (slti a0,2 range split, beql a1,3). Matches byte-for-byte (blk2-21).
- case 1 a1: `if(a1==0){w=0x14}` then nested. a2==a0 MUST be a branch not cmov:
  `if(a2==0)goto c1_aff4; if(a2!=a0) return/goto; w=0x16;` (explicit distinct control flow).
  `break` (fall to w-check) re-triggers cmov (`xori a2,1`). a3!=-1 branch is ASYMMETRIC:
  `if(a2==a0) goto c1_w16` (w=0x16 OUT of line) vs a3==-1 inline. Matches.
- ternary direction: `(D_0062AFF4 != 1) ? 0x14 : 0x18` -> movn default-0x18 (NOT `==1?0x18:0x14`
  which gives movz). case2 `(D==0)?0x16:0x18` -> movz (correct).
- **PakBuf struct: pointer FIELDS must be `volatile int *volatile`** (field-volatile, not just
  pointee). This pins f0C/f14 store order (64->17 crack). cur/start/tag all field-volatile;
  f_18/f_1C `volatile int`. Data writes via `volatile int *p` + `*(volatile ull*)`. This makes
  the packet build (blk37) match byte-for-byte.

## RESIDUAL (rc17, ~3 coupled diffs, PERMUTER-CLASS):
1. **frame 0x30 vs my 0x20** — expected reserves a PHANTOM 0x10 slot (sp+0..0xf unused; only
   ra@0x20,s0@0x10 touched). makeNormalStrip (same calls, 2 args) is 0x20. Same 5-arg signature
   yet differs => 100% body-driven (allocator reserves spill slot it then coalesces away).
   Frame is DOWNSTREAM of #2 (different blocks -> different allocation -> reserved slot).
2. **a1 branch direction**: expected `bne a1,zero,.178` (w=0x14 INLINE, default out-of-line,
   `addiu v0,-1` a3-const filling the bne delay). gcc gives `beq a1,zero` (w=0x14 out-of-line)
   because the small w=0x14 block ends in an unconditional jump -> gcc out-lines it. Tried:
   natural if-else, goto-c1_def, c1_def-after-case3 (rc30), c1_def-after-Lret (rc52). All beq/worse.
3. **w-check constant threading**: expected materializes 0xffff (`dli v0,0xffff`) in branch delay
   slots feeding the shared .164 w-check, routing all early exits through ONE .1A0. Mine makes
   separate epilogues. `goto wcheck`(route)->cmov; `goto Lret`(separate)->no cmov but dup epilogue.
   Tension resolved in original by gcc delay-slot fill (internal). err-variable tried -> rc37.

## Hypotheses tested & REJECTED (~22): switch vs if-else, void vs int, full/partial volatile,
return vs break vs goto-Lret vs goto-wcheck routing, ternary forms, c1_def placement (3 spots),
err-variable, if-wrapped build, consolidated returns. None moved the a1/frame/routing cluster.

## Next ideas for resume: permuter (may strip volatile - verify packet survives); or find the
gcc lever that keeps 0xffff live in a reg across the tree (threading) -> would unlock #2+#3+#1.

---

## Attempt at 2026-06-16

**Reason parked:** rc17 void (correct structure); coupled gcc bb-layout/delay-slot v0-threading tie (a1 branch-direction -> frame phantom 0x10 cascade); ~36 hand hyps exhausted; permuter-class

**TU:** `seki/src/Packet.c`

**Seed:** `tough_nuts/pac_getWeight/pac_getWeight.c`

Disassembly:

```
.align 3
nonmatching pac_getWeight, 0x21C

glabel pac_getWeight
    /* 19090 00119090 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 19094 00119094 2D580001 */  daddu      $11, $8, $0
    /* 19098 00119098 2000BFFF */  sd         $31, 0x20($29)
    /* 1909C 0011909C FFFF0834 */  ori        $8, $0, 0xFFFF
    /* 190A0 001190A0 01000324 */  addiu      $3, $0, 0x1
    /* 190A4 001190A4 30008310 */  beq        $4, $3, .L00119168
    /* 190A8 001190A8 1000B0FF */   sd        $16, 0x10($29)
    /* 190AC 001190AC 02008228 */  slti       $2, $4, 0x2
    /* 190B0 001190B0 05004010 */  beqz       $2, .L001190C8
    /* 190B4 001190B4 02000224 */   addiu     $2, $0, 0x2
    /* 190B8 001190B8 09008010 */  beqz       $4, .L001190E0
    /* 190BC 001190BC FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 190C0 001190C0 4C000010 */  b          .L001191F4
    /* 190C4 001190C4 00000000 */   nop
.align 2
  .L001190C8:
    /* 190C8 001190C8 40008210 */  beq        $4, $2, .L001191CC
    /* 190CC 001190CC 03000224 */   addiu     $2, $0, 0x3
    /* 190D0 001190D0 46008210 */  beq        $4, $2, .L001191EC
    /* 190D4 001190D4 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 190D8 001190D8 46000010 */  b          .L001191F4
    /* 190DC 001190DC 00000000 */   nop
.align 2
  .L001190E0:
    /* 190E0 001190E0 0900A010 */  beqz       $5, .L00119108
    /* 190E4 001190E4 03000224 */   addiu     $2, $0, 0x3
    /* 190E8 001190E8 4100A250 */  beql       $5, $2, .L001191F0
    /* 190EC 001190EC 26000824 */   addiu     $8, $0, 0x26
    /* 190F0 001190F0 1900C310 */  beq        $6, $3, .L00119158
    /* 190F4 001190F4 0200C228 */   slti      $2, $6, 0x2
    /* 190F8 001190F8 0E004010 */  beqz       $2, .L00119134
    /* 190FC 001190FC 02000224 */   addiu     $2, $0, 0x2
    /* 19100 00119100 08000010 */  b          .L00119124
    /* 19104 00119104 00000000 */   nop
.align 2
  .L00119108:
    /* 19108 00119108 FFFF0224 */  addiu      $2, $0, -0x1
    /* 1910C 0011910C 1200E210 */  beq        $7, $2, .L00119158
    /* 19110 00119110 02000224 */   addiu     $2, $0, 0x2
    /* 19114 00119114 3600E210 */  beq        $7, $2, .L001191F0
    /* 19118 00119118 24000824 */   addiu     $8, $0, 0x24
    /* 1911C 0011911C 34000010 */  b          .L001191F0
    /* 19120 00119120 20000824 */   addiu     $8, $0, 0x20
.align 2
  .L00119124:
    /* 19124 00119124 0700C010 */  beqz       $6, .L00119144
    /* 19128 00119128 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 1912C 0011912C 31000010 */  b          .L001191F4
    /* 19130 00119130 00000000 */   nop
.align 2
  .L00119134:
    /* 19134 00119134 0A00C210 */  beq        $6, $2, .L00119160
    /* 19138 00119138 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 1913C 0011913C 2D000010 */  b          .L001191F4
    /* 19140 00119140 00000000 */   nop
.align 2
  .L00119144:
    /* 19144 00119144 0200E338 */  xori       $3, $7, 0x2
    /* 19148 00119148 20000824 */  addiu      $8, $0, 0x20
    /* 1914C 0011914C 24000224 */  addiu      $2, $0, 0x24
    /* 19150 00119150 27000010 */  b          .L001191F0
    /* 19154 00119154 0A404300 */   movz      $8, $2, $3
.align 2
  .L00119158:
    /* 19158 00119158 25000010 */  b          .L001191F0
    /* 1915C 0011915C 22000824 */   addiu     $8, $0, 0x22
.align 2
  .L00119160:
    /* 19160 00119160 23000010 */  b          .L001191F0
    /* 19164 00119164 26000824 */   addiu     $8, $0, 0x26
.align 2
  .L00119168:
    /* 19168 00119168 0300A014 */  bnez       $5, .L00119178
    /* 1916C 0011916C FFFF0224 */   addiu     $2, $0, -0x1
    /* 19170 00119170 1F000010 */  b          .L001191F0
    /* 19174 00119174 14000824 */   addiu     $8, $0, 0x14
.align 2
  .L00119178:
    /* 19178 00119178 0700E214 */  bne        $7, $2, .L00119198
    /* 1917C 0011917C 00000000 */   nop
    /* 19180 00119180 0B00C010 */  beqz       $6, .L001191B0
    /* 19184 00119184 04A4828F */   lw        $2, %gp_rel(D_0062AFF4)($28)
    /* 19188 00119188 1A00C414 */  bne        $6, $4, .L001191F4
    /* 1918C 0011918C FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 19190 00119190 18000010 */  b          .L001191F4
    /* 19194 00119194 16000824 */   addiu     $8, $0, 0x16
.align 2
  .L00119198:
    /* 19198 00119198 0500C010 */  beqz       $6, .L001191B0
    /* 1919C 0011919C 04A4828F */   lw        $2, %gp_rel(D_0062AFF4)($28)
    /* 191A0 001191A0 0800C410 */  beq        $6, $4, .L001191C4
    /* 191A4 001191A4 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 191A8 001191A8 12000010 */  b          .L001191F4
    /* 191AC 001191AC 00000000 */   nop
.align 2
  .L001191B0:
    /* 191B0 001191B0 18000824 */  addiu      $8, $0, 0x18
    /* 191B4 001191B4 14000324 */  addiu      $3, $0, 0x14
    /* 191B8 001191B8 01004238 */  xori       $2, $2, 0x1
    /* 191BC 001191BC 0C000010 */  b          .L001191F0
    /* 191C0 001191C0 0B406200 */   movn      $8, $3, $2
.align 2
  .L001191C4:
    /* 191C4 001191C4 0A000010 */  b          .L001191F0
    /* 191C8 001191C8 16000824 */   addiu     $8, $0, 0x16
.align 2
  .L001191CC:
    /* 191CC 001191CC 0300A014 */  bnez       $5, .L001191DC
    /* 191D0 001191D0 04A4838F */   lw        $3, %gp_rel(D_0062AFF4)($28)
    /* 191D4 001191D4 06000010 */  b          .L001191F0
    /* 191D8 001191D8 14000824 */   addiu     $8, $0, 0x14
.align 2
  .L001191DC:
    /* 191DC 001191DC 18000824 */  addiu      $8, $0, 0x18
    /* 191E0 001191E0 16000224 */  addiu      $2, $0, 0x16
    /* 191E4 001191E4 02000010 */  b          .L001191F0
    /* 191E8 001191E8 0A404300 */   movz      $8, $2, $3
.align 2
  .L001191EC:
    /* 191EC 001191EC 12000824 */  addiu      $8, $0, 0x12
.align 2
  .L001191F0:
    /* 191F0 001191F0 FFFF0234 */  ori        $2, $0, 0xFFFF
.align 2
  .L001191F4:
    /* 191F4 001191F4 2A000211 */  beq        $8, $2, .L001192A0
    /* 191F8 001191F8 2000BFDF */   ld        $31, 0x20($29)
    /* 191FC 001191FC 4C00103C */  lui        $16, %hi(D_004C3850)
    /* 19200 00119200 0010073C */  lui        $7, (0x10000000 >> 16)
    /* 19204 00119204 50381026 */  addiu      $16, $16, %lo(D_004C3850)
    /* 19208 00119208 0015033C */  lui        $3, (0x15000000 >> 16)
    /* 1920C 0011920C 1000028E */  lw         $2, 0x10($16)
    /* 19210 00119210 25180301 */  or         $3, $8, $3
    /* 19214 00119214 180000AE */  sw         $0, 0x18($16)
    /* 19218 00119218 00130A3C */  lui        $10, (0x13000000 >> 16)
    /* 1921C 0011921C 140002AE */  sw         $2, 0x14($16)
    /* 19220 00119220 08004424 */  addiu      $4, $2, 0x8
    /* 19224 00119224 0C0002AE */  sw         $2, 0xC($16)
    /* 19228 00119228 0C004624 */  addiu      $6, $2, 0xC
    /* 1922C 0011922C 1C0000AE */  sw         $0, 0x1C($16)
    /* 19230 00119230 10004524 */  addiu      $5, $2, 0x10
    /* 19234 00119234 000047FC */  sd         $7, 0x0($2)
    /* 19238 00119238 0060093C */  lui        $9, (0x60000000 >> 16)
    /* 1923C 0011923C 100004AE */  sw         $4, 0x10($16)
    /* 19240 00119240 18004724 */  addiu      $7, $2, 0x18
    /* 19244 00119244 080043AC */  sw         $3, 0x8($2)
    /* 19248 00119248 1C004824 */  addiu      $8, $2, 0x1C
    /* 1924C 0011924C 100006AE */  sw         $6, 0x10($16)
    /* 19250 00119250 20004324 */  addiu      $3, $2, 0x20
    /* 19254 00119254 0C004AAC */  sw         $10, 0xC($2)
    /* 19258 00119258 2D206001 */  daddu      $4, $11, $0
    /* 1925C 0011925C 100005AE */  sw         $5, 0x10($16)
    /* 19260 00119260 140005AE */  sw         $5, 0x14($16)
    /* 19264 00119264 100049FC */  sd         $9, 0x10($2)
    /* 19268 00119268 100007AE */  sw         $7, 0x10($16)
    /* 1926C 0011926C 180040AC */  sw         $0, 0x18($2)
    /* 19270 00119270 100008AE */  sw         $8, 0x10($16)
    /* 19274 00119274 1C0040AC */  sw         $0, 0x1C($2)
    /* 19278 00119278 BAE1070C */  jal        dpk_SwapBuffer
    /* 1927C 0011927C 100003AE */   sw        $3, 0x10($16)
    /* 19280 00119280 0C00058E */  lw         $5, 0xC($16)
    /* 19284 00119284 2D300000 */  daddu      $6, $0, $0
    /* 19288 00119288 C4E1070C */  jal        dpk_Init
    /* 1928C 0011928C 05000424 */   addiu     $4, $0, 0x5
    /* 19290 00119290 2000BFDF */  ld         $31, 0x20($29)
    /* 19294 00119294 1000B0DF */  ld         $16, 0x10($29)
    /* 19298 00119298 48E10708 */  j          dl_GetPri
    /* 1929C 0011929C 3000BD27 */   addiu     $29, $29, 0x30
.align 2
  .L001192A0:
    /* 192A0 001192A0 1000B0DF */  ld         $16, 0x10($29)
    /* 192A4 001192A4 0800E003 */  jr         $31
    /* 192A8 001192A8 3000BD27 */   addiu     $29, $29, 0x30
endlabel pac_getWeight
    /* 192AC 001192AC 00000000 */  nop
```

---

## Attempt at 2026-06-16

**Reason parked:** rc17 void (callers confirm void; nested-switch dispatch + field-volatile packet build all byte-match); residual=coupled gcc bb-layout/delay-slot v0-threading tie (a1 branch-direction -> frame phantom 0x10); 30-stall hand-exhausted; permute

**TU:** `seki/src/Packet.c`

**Seed:** `tough_nuts/pac_getWeight/pac_getWeight.1.c`

Disassembly:

```
.align 3
nonmatching pac_getWeight, 0x21C

glabel pac_getWeight
    /* 19090 00119090 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 19094 00119094 2D580001 */  daddu      $11, $8, $0
    /* 19098 00119098 2000BFFF */  sd         $31, 0x20($29)
    /* 1909C 0011909C FFFF0834 */  ori        $8, $0, 0xFFFF
    /* 190A0 001190A0 01000324 */  addiu      $3, $0, 0x1
    /* 190A4 001190A4 30008310 */  beq        $4, $3, .L00119168
    /* 190A8 001190A8 1000B0FF */   sd        $16, 0x10($29)
    /* 190AC 001190AC 02008228 */  slti       $2, $4, 0x2
    /* 190B0 001190B0 05004010 */  beqz       $2, .L001190C8
    /* 190B4 001190B4 02000224 */   addiu     $2, $0, 0x2
    /* 190B8 001190B8 09008010 */  beqz       $4, .L001190E0
    /* 190BC 001190BC FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 190C0 001190C0 4C000010 */  b          .L001191F4
    /* 190C4 001190C4 00000000 */   nop
.align 2
  .L001190C8:
    /* 190C8 001190C8 40008210 */  beq        $4, $2, .L001191CC
    /* 190CC 001190CC 03000224 */   addiu     $2, $0, 0x3
    /* 190D0 001190D0 46008210 */  beq        $4, $2, .L001191EC
    /* 190D4 001190D4 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 190D8 001190D8 46000010 */  b          .L001191F4
    /* 190DC 001190DC 00000000 */   nop
.align 2
  .L001190E0:
    /* 190E0 001190E0 0900A010 */  beqz       $5, .L00119108
    /* 190E4 001190E4 03000224 */   addiu     $2, $0, 0x3
    /* 190E8 001190E8 4100A250 */  beql       $5, $2, .L001191F0
    /* 190EC 001190EC 26000824 */   addiu     $8, $0, 0x26
    /* 190F0 001190F0 1900C310 */  beq        $6, $3, .L00119158
    /* 190F4 001190F4 0200C228 */   slti      $2, $6, 0x2
    /* 190F8 001190F8 0E004010 */  beqz       $2, .L00119134
    /* 190FC 001190FC 02000224 */   addiu     $2, $0, 0x2
    /* 19100 00119100 08000010 */  b          .L00119124
    /* 19104 00119104 00000000 */   nop
.align 2
  .L00119108:
    /* 19108 00119108 FFFF0224 */  addiu      $2, $0, -0x1
    /* 1910C 0011910C 1200E210 */  beq        $7, $2, .L00119158
    /* 19110 00119110 02000224 */   addiu     $2, $0, 0x2
    /* 19114 00119114 3600E210 */  beq        $7, $2, .L001191F0
    /* 19118 00119118 24000824 */   addiu     $8, $0, 0x24
    /* 1911C 0011911C 34000010 */  b          .L001191F0
    /* 19120 00119120 20000824 */   addiu     $8, $0, 0x20
.align 2
  .L00119124:
    /* 19124 00119124 0700C010 */  beqz       $6, .L00119144
    /* 19128 00119128 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 1912C 0011912C 31000010 */  b          .L001191F4
    /* 19130 00119130 00000000 */   nop
.align 2
  .L00119134:
    /* 19134 00119134 0A00C210 */  beq        $6, $2, .L00119160
    /* 19138 00119138 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 1913C 0011913C 2D000010 */  b          .L001191F4
    /* 19140 00119140 00000000 */   nop
.align 2
  .L00119144:
    /* 19144 00119144 0200E338 */  xori       $3, $7, 0x2
    /* 19148 00119148 20000824 */  addiu      $8, $0, 0x20
    /* 1914C 0011914C 24000224 */  addiu      $2, $0, 0x24
    /* 19150 00119150 27000010 */  b          .L001191F0
    /* 19154 00119154 0A404300 */   movz      $8, $2, $3
.align 2
  .L00119158:
    /* 19158 00119158 25000010 */  b          .L001191F0
    /* 1915C 0011915C 22000824 */   addiu     $8, $0, 0x22
.align 2
  .L00119160:
    /* 19160 00119160 23000010 */  b          .L001191F0
    /* 19164 00119164 26000824 */   addiu     $8, $0, 0x26
.align 2
  .L00119168:
    /* 19168 00119168 0300A014 */  bnez       $5, .L00119178
    /* 1916C 0011916C FFFF0224 */   addiu     $2, $0, -0x1
    /* 19170 00119170 1F000010 */  b          .L001191F0
    /* 19174 00119174 14000824 */   addiu     $8, $0, 0x14
.align 2
  .L00119178:
    /* 19178 00119178 0700E214 */  bne        $7, $2, .L00119198
    /* 1917C 0011917C 00000000 */   nop
    /* 19180 00119180 0B00C010 */  beqz       $6, .L001191B0
    /* 19184 00119184 04A4828F */   lw        $2, %gp_rel(D_0062AFF4)($28)
    /* 19188 00119188 1A00C414 */  bne        $6, $4, .L001191F4
    /* 1918C 0011918C FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 19190 00119190 18000010 */  b          .L001191F4
    /* 19194 00119194 16000824 */   addiu     $8, $0, 0x16
.align 2
  .L00119198:
    /* 19198 00119198 0500C010 */  beqz       $6, .L001191B0
    /* 1919C 0011919C 04A4828F */   lw        $2, %gp_rel(D_0062AFF4)($28)
    /* 191A0 001191A0 0800C410 */  beq        $6, $4, .L001191C4
    /* 191A4 001191A4 FFFF0234 */   ori       $2, $0, 0xFFFF
    /* 191A8 001191A8 12000010 */  b          .L001191F4
    /* 191AC 001191AC 00000000 */   nop
.align 2
  .L001191B0:
    /* 191B0 001191B0 18000824 */  addiu      $8, $0, 0x18
    /* 191B4 001191B4 14000324 */  addiu      $3, $0, 0x14
    /* 191B8 001191B8 01004238 */  xori       $2, $2, 0x1
    /* 191BC 001191BC 0C000010 */  b          .L001191F0
    /* 191C0 001191C0 0B406200 */   movn      $8, $3, $2
.align 2
  .L001191C4:
    /* 191C4 001191C4 0A000010 */  b          .L001191F0
    /* 191C8 001191C8 16000824 */   addiu     $8, $0, 0x16
.align 2
  .L001191CC:
    /* 191CC 001191CC 0300A014 */  bnez       $5, .L001191DC
    /* 191D0 001191D0 04A4838F */   lw        $3, %gp_rel(D_0062AFF4)($28)
    /* 191D4 001191D4 06000010 */  b          .L001191F0
    /* 191D8 001191D8 14000824 */   addiu     $8, $0, 0x14
.align 2
  .L001191DC:
    /* 191DC 001191DC 18000824 */  addiu      $8, $0, 0x18
    /* 191E0 001191E0 16000224 */  addiu      $2, $0, 0x16
    /* 191E4 001191E4 02000010 */  b          .L001191F0
    /* 191E8 001191E8 0A404300 */   movz      $8, $2, $3
.align 2
  .L001191EC:
    /* 191EC 001191EC 12000824 */  addiu      $8, $0, 0x12
.align 2
  .L001191F0:
    /* 191F0 001191F0 FFFF0234 */  ori        $2, $0, 0xFFFF
.align 2
  .L001191F4:
    /* 191F4 001191F4 2A000211 */  beq        $8, $2, .L001192A0
    /* 191F8 001191F8 2000BFDF */   ld        $31, 0x20($29)
    /* 191FC 001191FC 4C00103C */  lui        $16, %hi(D_004C3850)
    /* 19200 00119200 0010073C */  lui        $7, (0x10000000 >> 16)
    /* 19204 00119204 50381026 */  addiu      $16, $16, %lo(D_004C3850)
    /* 19208 00119208 0015033C */  lui        $3, (0x15000000 >> 16)
    /* 1920C 0011920C 1000028E */  lw         $2, 0x10($16)
    /* 19210 00119210 25180301 */  or         $3, $8, $3
    /* 19214 00119214 180000AE */  sw         $0, 0x18($16)
    /* 19218 00119218 00130A3C */  lui        $10, (0x13000000 >> 16)
    /* 1921C 0011921C 140002AE */  sw         $2, 0x14($16)
    /* 19220 00119220 08004424 */  addiu      $4, $2, 0x8
    /* 19224 00119224 0C0002AE */  sw         $2, 0xC($16)
    /* 19228 00119228 0C004624 */  addiu      $6, $2, 0xC
    /* 1922C 0011922C 1C0000AE */  sw         $0, 0x1C($16)
    /* 19230 00119230 10004524 */  addiu      $5, $2, 0x10
    /* 19234 00119234 000047FC */  sd         $7, 0x0($2)
    /* 19238 00119238 0060093C */  lui        $9, (0x60000000 >> 16)
    /* 1923C 0011923C 100004AE */  sw         $4, 0x10($16)
    /* 19240 00119240 18004724 */  addiu      $7, $2, 0x18
    /* 19244 00119244 080043AC */  sw         $3, 0x8($2)
    /* 19248 00119248 1C004824 */  addiu      $8, $2, 0x1C
    /* 1924C 0011924C 100006AE */  sw         $6, 0x10($16)
    /* 19250 00119250 20004324 */  addiu      $3, $2, 0x20
    /* 19254 00119254 0C004AAC */  sw         $10, 0xC($2)
    /* 19258 00119258 2D206001 */  daddu      $4, $11, $0
    /* 1925C 0011925C 100005AE */  sw         $5, 0x10($16)
    /* 19260 00119260 140005AE */  sw         $5, 0x14($16)
    /* 19264 00119264 100049FC */  sd         $9, 0x10($2)
    /* 19268 00119268 100007AE */  sw         $7, 0x10($16)
    /* 1926C 0011926C 180040AC */  sw         $0, 0x18($2)
    /* 19270 00119270 100008AE */  sw         $8, 0x10($16)
    /* 19274 00119274 1C0040AC */  sw         $0, 0x1C($2)
    /* 19278 00119278 BAE1070C */  jal        dpk_SwapBuffer
    /* 1927C 0011927C 100003AE */   sw        $3, 0x10($16)
    /* 19280 00119280 0C00058E */  lw         $5, 0xC($16)
    /* 19284 00119284 2D300000 */  daddu      $6, $0, $0
    /* 19288 00119288 C4E1070C */  jal        dpk_Init
    /* 1928C 0011928C 05000424 */   addiu     $4, $0, 0x5
    /* 19290 00119290 2000BFDF */  ld         $31, 0x20($29)
    /* 19294 00119294 1000B0DF */  ld         $16, 0x10($29)
    /* 19298 00119298 48E10708 */  j          dl_GetPri
    /* 1929C 0011929C 3000BD27 */   addiu     $29, $29, 0x30
.align 2
  .L001192A0:
    /* 192A0 001192A0 1000B0DF */  ld         $16, 0x10($29)
    /* 192A4 001192A4 0800E003 */  jr         $31
    /* 192A8 001192A8 3000BD27 */   addiu     $29, $29, 0x30
endlabel pac_getWeight
    /* 192AC 001192AC 00000000 */  nop
```
