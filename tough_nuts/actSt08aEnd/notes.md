# actSt08aEnd — parked

VRAM: 0x00220690 (file_off 0x120690)
Asm source: asm/aug6/nonmatchings/script/src/st08a/actSt08aEnd.s

## Attempt at 2026-06-11

**Reason parked:** rc9: full structure recovered (volatile-arg + s0=actInitialize(a0) callee-saved + if(func_00178DB0(0xFD)==0){door-setup}else{KillPlay(0x133,0,-1)}). CORRECT: prologue, s0, branch direction (bnez), KillPlay, _ACTWait, control flow. RESIDUAL: door-setup tie (same as func_00220918) — v0/v1 swap (D_004CCDE0 should be v0), [1] store should be in BoxBarSoundOn delay slot, mid-func %hi grouping. Hand floor rc9 across store-order/typing/capture/new_var/base-fold/explicit-ptr. Permuter candidate.

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/actSt08aEnd/actSt08aEnd.c`

Disassembly:

```
.align 3
nonmatching actSt08aEnd, 0x98

glabel actSt08aEnd
    /* 120690 00220690 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 120694 00220694 0000A4AF */  sw         $4, 0x0($29)
    /* 120698 00220698 1000B0FF */  sd         $16, 0x10($29)
    /* 12069C 0022069C 0000A28F */  lw         $2, 0x0($29)
    /* 1206A0 002206A0 0000A48F */  lw         $4, 0x0($29)
    /* 1206A4 002206A4 2000BFFF */  sd         $31, 0x20($29)
    /* 1206A8 002206A8 3CFE070C */  jal        actInitialize
    /* 1206AC 002206AC 00000000 */   nop
    /* 1206B0 002206B0 2D804000 */  daddu      $16, $2, $0
    /* 1206B4 002206B4 6004080C */  jal        _ACTWait
    /* 1206B8 002206B8 01000424 */   addiu     $4, $0, 0x1
    /* 1206BC 002206BC 6CE3050C */  jal        func_00178DB0
    /* 1206C0 002206C0 FD000424 */   addiu     $4, $0, 0xFD
    /* 1206C4 002206C4 11004014 */  bnez       $2, .L0022070C
    /* 1206C8 002206C8 33010424 */   addiu     $4, $0, 0x133
    /* 1206CC 002206CC 2D280000 */  daddu      $5, $0, $0
    /* 1206D0 002206D0 76A5040C */  jal        stage_KillPlayBgAnimation
    /* 1206D4 002206D4 2D300000 */   daddu     $6, $0, $0
    /* 1206D8 002206D8 4D00023C */  lui        $2, %hi(D_004CCDE0)
    /* 1206DC 002206DC 2200033C */  lui        $3, %hi(actSt06aSuimonChk)
    /* 1206E0 002206E0 E0CD4224 */  addiu      $2, $2, %lo(D_004CCDE0)
    /* 1206E4 002206E4 0000A48F */  lw         $4, 0x0($29)
    /* 1206E8 002206E8 C0EB6324 */  addiu      $3, $3, %lo(actSt06aSuimonChk)
    /* 1206EC 002206EC 89010524 */  addiu      $5, $0, 0x189
    /* 1206F0 002206F0 B40002AE */  sw         $2, 0xB4($16)
    /* 1206F4 002206F4 F867050C */  jal        BoxBarSoundOn
    /* 1206F8 002206F8 040043AC */   sw        $3, 0x4($2)
    /* 1206FC 002206FC 6004080C */  jal        _ACTWait
    /* 120700 00220700 2D200000 */   daddu     $4, $0, $0
    /* 120704 00220704 05000010 */  b          .L0022071C
    /* 120708 00220708 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0022070C:
    /* 12070C 0022070C 2D280000 */  daddu      $5, $0, $0
    /* 120710 00220710 76A5040C */  jal        stage_KillPlayBgAnimation
    /* 120714 00220714 FFFF0624 */   addiu     $6, $0, -0x1
    /* 120718 00220718 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L0022071C:
    /* 12071C 0022071C 1000B0DF */  ld         $16, 0x10($29)
    /* 120720 00220720 0800E003 */  jr         $31
    /* 120724 00220724 3000BD27 */   addiu     $29, $29, 0x30
endlabel actSt08aEnd
```
