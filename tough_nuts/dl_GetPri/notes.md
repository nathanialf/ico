# dl_GetPri — parked

VRAM: 0x001F8520 (file_off 0x0F8520)
Asm source: asm/aug6/nonmatchings/seki/src/DisplayList/dl_GetPri.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=24). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `seki/src/DisplayList.c`

**Seed:** `tough_nuts/dl_GetPri/dl_GetPri.c`

Disassembly:

```
.align 3
nonmatching dl_GetPri, 0x140

glabel dl_GetPri
    /* F8520 001F8520 70B6838F */  lw         $3, %gp_rel(D_0062C260)($28)
    /* F8524 001F8524 28000424 */  addiu      $4, $0, 0x28
    /* F8528 001F8528 7100023C */  lui        $2, %hi(D_0070A5C0)
    /* F852C 001F852C FF7F053C */  lui        $5, (0x7FFFFFFF >> 16)
    /* F8530 001F8530 FFFFA534 */  ori        $5, $5, (0x7FFFFFFF & 0xFFFF)
    /* F8534 001F8534 18186400 */  mult       $3, $3, $4
    /* F8538 001F8538 C0A54224 */  addiu      $2, $2, %lo(D_0070A5C0)
    /* F853C 001F853C 06000424 */  addiu      $4, $0, 0x6
    /* F8540 001F8540 21386200 */  addu       $7, $3, $2
    /* F8544 001F8544 0800E2DC */  ld         $2, 0x8($7)
    /* F8548 001F8548 1800E3DC */  ld         $3, 0x18($7)
    /* F854C 001F854C 24104500 */  and        $2, $2, $5
    /* F8550 001F8550 0C006410 */  beq        $3, $4, .L001F8584
    /* F8554 001F8554 3C400200 */   dsll32    $8, $2, 0
    /* F8558 001F8558 0700622C */  sltiu      $2, $3, 0x7
    /* F855C 001F855C 05004010 */  beqz       $2, .L001F8574
    /* F8560 001F8560 07000224 */   addiu     $2, $0, 0x7
    /* F8564 001F8564 08006050 */  beql       $3, $0, .L001F8588
    /* F8568 001F8568 2400E48C */   lw        $4, 0x24($7)
    /* F856C 001F856C 19000010 */  b          .L001F85D4
    /* F8570 001F8570 1000E59C */   lwu       $5, 0x10($7)
.align 2
  .L001F8574:
    /* F8574 001F8574 10006250 */  beql       $3, $2, .L001F85B8
    /* F8578 001F8578 2400E28C */   lw        $2, 0x24($7)
    /* F857C 001F857C 15000010 */  b          .L001F85D4
    /* F8580 001F8580 1000E59C */   lwu       $5, 0x10($7)
.align 2
  .L001F8584:
    /* F8584 001F8584 2400E48C */  lw         $4, 0x24($7)
.align 2
  .L001F8588:
    /* F8588 001F8588 0400E68C */  lw         $6, 0x4($7)
    /* F858C 001F858C 23108600 */  subu       $2, $4, $6
    /* F8590 001F8590 02110200 */  srl        $2, $2, 4
    /* F8594 001F8594 FFFF4224 */  addiu      $2, $2, -0x1
    /* F8598 001F8598 3C100200 */  dsll32     $2, $2, 0
    /* F859C 001F859C 3E280200 */  dsrl32     $5, $2, 0
    /* F85A0 001F85A0 0E00A014 */  bnez       $5, .L001F85DC
    /* F85A4 001F85A4 0800622C */   sltiu     $2, $3, 0x8
    /* F85A8 001F85A8 F0FF8224 */  addiu      $2, $4, -0x10
    /* F85AC 001F85AC 0000E0AC */  sw         $0, 0x0($7)
    /* F85B0 001F85B0 0800E003 */  jr         $31
    /* F85B4 001F85B4 2400E2AC */   sw        $2, 0x24($7)
.align 2
  .L001F85B8:
    /* F85B8 001F85B8 0400E68C */  lw         $6, 0x4($7)
    /* F85BC 001F85BC 23104600 */  subu       $2, $2, $6
    /* F85C0 001F85C0 02110200 */  srl        $2, $2, 4
    /* F85C4 001F85C4 FFFF4224 */  addiu      $2, $2, -0x1
    /* F85C8 001F85C8 3C100200 */  dsll32     $2, $2, 0
    /* F85CC 001F85CC 02000010 */  b          .L001F85D8
    /* F85D0 001F85D0 3E280200 */   dsrl32    $5, $2, 0
.align 2
  .L001F85D4:
    /* F85D4 001F85D4 0400E68C */  lw         $6, 0x4($7)
.align 2
  .L001F85D8:
    /* F85D8 001F85D8 0800622C */  sltiu      $2, $3, 0x8
.align 2
  .L001F85DC:
    /* F85DC 001F85DC 1D004010 */  beqz       $2, .L001F8654
    /* F85E0 001F85E0 6100033C */   lui       $3, %hi(jtbl_00613750)
    /* F85E4 001F85E4 1800E28C */  lw         $2, 0x18($7)
    /* F85E8 001F85E8 50376324 */  addiu      $3, $3, %lo(jtbl_00613750)
    /* F85EC 001F85EC 80100200 */  sll        $2, $2, 2
    /* F85F0 001F85F0 21104300 */  addu       $2, $2, $3
    /* F85F4 001F85F4 0000448C */  lw         $4, 0x0($2)
    /* F85F8 001F85F8 08008000 */  jr         $4
    /* F85FC 001F85FC 00000000 */   nop
.align 2
  jlabel .L001F8600
    /* F8600 001F8600 12000010 */  b          .L001F864C
    /* F8604 001F8604 0010023C */   lui       $2, (0x10000000 >> 16)
.align 2
  jlabel .L001F8608
    /* F8608 001F8608 0020023C */  lui        $2, (0x20000000 >> 16)
    /* F860C 001F860C 0F000010 */  b          .L001F864C
    /* F8610 001F8610 25100201 */   or        $2, $8, $2
.align 2
  jlabel .L001F8614
    /* F8614 001F8614 0030023C */  lui        $2, (0x30000000 >> 16)
    /* F8618 001F8618 0C000010 */  b          .L001F864C
    /* F861C 001F861C 25100201 */   or        $2, $8, $2
.align 2
  jlabel .L001F8620
    /* F8620 001F8620 0040023C */  lui        $2, (0x40000000 >> 16)
    /* F8624 001F8624 09000010 */  b          .L001F864C
    /* F8628 001F8628 25100201 */   or        $2, $8, $2
.align 2
  jlabel .L001F862C
    /* F862C 001F862C 08000010 */  b          .L001F8650
    /* F8630 001F8630 2510A800 */   or        $2, $5, $8
.align 2
  jlabel .L001F8634
    /* F8634 001F8634 0050023C */  lui        $2, (0x50000000 >> 16)
    /* F8638 001F8638 04000010 */  b          .L001F864C
    /* F863C 001F863C 25100201 */   or        $2, $8, $2
.align 2
  jlabel .L001F8640
    /* F8640 001F8640 02000010 */  b          .L001F864C
    /* F8644 001F8644 0060023C */   lui       $2, (0x60000000 >> 16)
.align 2
  jlabel .L001F8648
    /* F8648 001F8648 0070023C */  lui        $2, (0x70000000 >> 16)
.align 2
  .L001F864C:
    /* F864C 001F864C 2510A200 */  or         $2, $5, $2
.align 2
  .L001F8650:
    /* F8650 001F8650 0000C2FC */  sd         $2, 0x0($6)
.align 2
  .L001F8654:
    /* F8654 001F8654 0800C0FC */  sd         $0, 0x8($6)
    /* F8658 001F8658 0800E003 */  jr         $31
    /* F865C 001F865C 0000E0AC */   sw        $0, 0x0($7)
endlabel dl_GetPri
```
