# func_001AF648 — parked

VRAM: 0x001AF648 (file_off 0x0AF648)
Asm source: asm/aug6/nonmatchings/common/src/kanbanBoot/func_001AF648.s

## Attempt at 2026-06-21

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=3). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/kanbanBoot.c`

**Seed:** `tough_nuts/func_001AF648/func_001AF648.c`

Disassembly:

```
.align 3
nonmatching func_001AF648, 0x130

glabel func_001AF648
    /* AF648 001AF648 E0FFBD27 */  addiu      $29, $29, -0x20
    /* AF64C 001AF64C 0000B0FF */  sd         $16, 0x0($29)
    /* AF650 001AF650 1000BFFF */  sd         $31, 0x10($29)
    /* AF654 001AF654 2D800000 */  daddu      $16, $0, $0
    /* AF658 001AF658 29000426 */  addiu      $4, $16, 0x29
    /* AF65C 001AF65C 00000000 */  nop
.align 2
  .L001AF660:
    /* AF660 001AF660 D0D1060C */  jal        func_001B4740
    /* AF664 001AF664 01000524 */   addiu     $5, $0, 0x1
    /* AF668 001AF668 33000426 */  addiu      $4, $16, 0x33
    /* AF66C 001AF66C D0D1060C */  jal        func_001B4740
    /* AF670 001AF670 01000524 */   addiu     $5, $0, 0x1
    /* AF674 001AF674 3D000426 */  addiu      $4, $16, 0x3D
    /* AF678 001AF678 D0D1060C */  jal        func_001B4740
    /* AF67C 001AF67C 01000524 */   addiu     $5, $0, 0x1
    /* AF680 001AF680 47000426 */  addiu      $4, $16, 0x47
    /* AF684 001AF684 D0D1060C */  jal        func_001B4740
    /* AF688 001AF688 01000524 */   addiu     $5, $0, 0x1
    /* AF68C 001AF68C 51000426 */  addiu      $4, $16, 0x51
    /* AF690 001AF690 D0D1060C */  jal        func_001B4740
    /* AF694 001AF694 01000524 */   addiu     $5, $0, 0x1
    /* AF698 001AF698 5B000426 */  addiu      $4, $16, 0x5B
    /* AF69C 001AF69C D0D1060C */  jal        func_001B4740
    /* AF6A0 001AF6A0 01000524 */   addiu     $5, $0, 0x1
    /* AF6A4 001AF6A4 01001026 */  addiu      $16, $16, 0x1
    /* AF6A8 001AF6A8 0A00022A */  slti       $2, $16, 0xA
    /* AF6AC 001AF6AC ECFF4014 */  bnez       $2, .L001AF660
    /* AF6B0 001AF6B0 29000426 */   addiu     $4, $16, 0x29
    /* AF6B4 001AF6B4 27000424 */  addiu      $4, $0, 0x27
    /* AF6B8 001AF6B8 D0D1060C */  jal        func_001B4740
    /* AF6BC 001AF6BC 01000524 */   addiu     $5, $0, 0x1
    /* AF6C0 001AF6C0 2D800000 */  daddu      $16, $0, $0
    /* AF6C4 001AF6C4 28000424 */  addiu      $4, $0, 0x28
    /* AF6C8 001AF6C8 D0D1060C */  jal        func_001B4740
    /* AF6CC 001AF6CC 01000524 */   addiu     $5, $0, 0x1
    /* AF6D0 001AF6D0 65000426 */  addiu      $4, $16, 0x65
    /* AF6D4 001AF6D4 00000000 */  nop
.align 2
  .L001AF6D8:
    /* AF6D8 001AF6D8 D0D1060C */  jal        func_001B4740
    /* AF6DC 001AF6DC 01000524 */   addiu     $5, $0, 0x1
    /* AF6E0 001AF6E0 01001026 */  addiu      $16, $16, 0x1
    /* AF6E4 001AF6E4 2700022A */  slti       $2, $16, 0x27
    /* AF6E8 001AF6E8 FBFF4014 */  bnez       $2, .L001AF6D8
    /* AF6EC 001AF6EC 65000426 */   addiu     $4, $16, 0x65
    /* AF6F0 001AF6F0 2700023C */  lui        $2, %hi(D_002715D0)
    /* AF6F4 001AF6F4 D0154224 */  addiu      $2, $2, %lo(D_002715D0)
    /* AF6F8 001AF6F8 0400428C */  lw         $2, 0x4($2)
    /* AF6FC 001AF6FC 40004330 */  andi       $3, $2, 0x40
    /* AF700 001AF700 11006050 */  beql       $3, $0, .L001AF748
    /* AF704 001AF704 10004230 */   andi      $2, $2, 0x10
    /* AF708 001AF708 5AD1060C */  jal        lt_set_item_select_func
    /* AF70C 001AF70C 00000000 */   nop
    /* AF710 001AF710 69FF4224 */  addiu      $2, $2, -0x97
    /* AF714 001AF714 7000033C */  lui        $3, %hi(D_00700700)
    /* AF718 001AF718 C0200200 */  sll        $4, $2, 3
    /* AF71C 001AF71C 00076324 */  addiu      $3, $3, %lo(D_00700700)
    /* AF720 001AF720 21208300 */  addu       $4, $4, $3
    /* AF724 001AF724 08A782AF */  sw         $2, %gp_rel(D_0062B2F8)($28)
    /* AF728 001AF728 00A784AF */  sw         $4, %gp_rel(D_0062B2F0)($28)
    /* AF72C 001AF72C FEB7060C */  jal        func_001ADFF8
    /* AF730 001AF730 04A782AF */   sw        $2, %gp_rel(D_0062B2F4)($28)
    /* AF734 001AF734 ECD1060C */  jal        initSceneGObj
    /* AF738 001AF738 2D200000 */   daddu     $4, $0, $0
    /* AF73C 001AF73C 1CA780AF */  sw         $0, %gp_rel(D_0062B30C)($28)
    /* AF740 001AF740 09000010 */  b          .L001AF768
    /* AF744 001AF744 10000224 */   addiu     $2, $0, 0x10
.align 2
  .L001AF748:
    /* AF748 001AF748 07004010 */  beqz       $2, .L001AF768
    /* AF74C 001AF74C FFFF0224 */   addiu     $2, $0, -0x1
    /* AF750 001AF750 04B8060C */  jal        kanbanBootMcCheck
    /* AF754 001AF754 00000000 */   nop
    /* AF758 001AF758 ECD1060C */  jal        initSceneGObj
    /* AF75C 001AF75C 2D200000 */   daddu     $4, $0, $0
    /* AF760 001AF760 1CA780AF */  sw         $0, %gp_rel(D_0062B30C)($28)
    /* AF764 001AF764 09000224 */  addiu      $2, $0, 0x9
.align 2
  .L001AF768:
    /* AF768 001AF768 1000BFDF */  ld         $31, 0x10($29)
    /* AF76C 001AF76C 0000B0DF */  ld         $16, 0x0($29)
    /* AF770 001AF770 0800E003 */  jr         $31
    /* AF774 001AF774 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001AF648
```
