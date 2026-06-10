# iosMsgSetEvent — parked

VRAM: 0x00139E68 (file_off 0x039E68)
Asm source: asm/aug6/nonmatchings/fumi/ios/message/iosMsgSetEvent.s

## Attempt at 2026-06-10

**Reason parked:** rc5: clean for(;;) thread-loop is byte-perfect EXCEPT gcc hoists assert __FILE__ (D_00551910) to preheader; ROM recomputes it at loop header on the func_00100540 back-edge (lui in delay, %hi in v0). 31-stall: single/nested/goto loops, file var, block scope, type changes, temps, store/index forms — none flip the hoist. save-order(s2/s3)+backedge(+0x5c) both downstream of the hoist. permuter-class (cf func_001FB768).

**TU:** `fumi/ios/message.c`

**Seed:** `tough_nuts/iosMsgSetEvent/iosMsgSetEvent.c`

Disassembly:

```
.align 3
nonmatching iosMsgSetEvent, 0x118

glabel iosMsgSetEvent
    /* 39E68 00139E68 60FFBD27 */  addiu      $29, $29, -0xA0
    /* 39E6C 00139E6C 8000B6FF */  sd         $22, 0x80($29)
    /* 39E70 00139E70 7000B5FF */  sd         $21, 0x70($29)
    /* 39E74 00139E74 5500163C */  lui        $22, %hi(D_00551930)
    /* 39E78 00139E78 6000B4FF */  sd         $20, 0x60($29)
    /* 39E7C 00139E7C 6300153C */  lui        $21, %hi(D_0062C268)
    /* 39E80 00139E80 4000B2FF */  sd         $18, 0x40($29)
    /* 39E84 00139E84 5500143C */  lui        $20, %hi(D_00551948)
    /* 39E88 00139E88 9000BFFF */  sd         $31, 0x90($29)
    /* 39E8C 00139E8C 5000B3FF */  sd         $19, 0x50($29)
    /* 39E90 00139E90 3000B1FF */  sd         $17, 0x30($29)
    /* 39E94 00139E94 0401040C */  jal        func_00100410
    /* 39E98 00139E98 2000B0FF */   sd        $16, 0x20($29)
    /* 39E9C 00139E9C F2F4040C */  jal        func_0013D3C8
    /* 39EA0 00139EA0 2D204000 */   daddu     $4, $2, $0
    /* 39EA4 00139EA4 3400528C */  lw         $18, 0x34($2)
    /* 39EA8 00139EA8 6300043C */  lui        $4, %hi(D_0062C278)
    /* 39EAC 00139EAC 3000458C */  lw         $5, 0x30($2)
    /* 39EB0 00139EB0 78C28424 */  addiu      $4, $4, %lo(D_0062C278)
    /* 39EB4 00139EB4 9440468E */  lw         $6, 0x4094($18)
    /* 39EB8 00139EB8 F290060C */  jal        debug_assertMessage
    /* 39EBC 00139EBC 189882AF */   sw        $2, %gp_rel(D_0062A408)($28)
    /* 39EC0 00139EC0 5500023C */  lui        $2, %hi(D_00551910)
.align 2
  .L00139EC4:
    /* 39EC4 00139EC4 10195324 */  addiu      $19, $2, %lo(D_00551910)
.align 2
  .L00139EC8:
    /* 39EC8 00139EC8 B6F3040C */  jal        iosSemaCreate
    /* 39ECC 00139ECC 00000000 */   nop
    /* 39ED0 00139ED0 9040508E */  lw         $16, 0x4090($18)
    /* 39ED4 00139ED4 3019C426 */  addiu      $4, $22, %lo(D_00551930)
    /* 39ED8 00139ED8 0A000016 */  bnez       $16, .L00139F04
    /* 39EDC 00139EDC 9440518E */   lw        $17, 0x4094($18)
    /* 39EE0 00139EE0 F290060C */  jal        debug_assertMessage
    /* 39EE4 00139EE4 00000000 */   nop
    /* 39EE8 00139EE8 2D206002 */  daddu      $4, $19, $0
    /* 39EEC 00139EEC 40AB060C */  jal        func_001AAD00
    /* 39EF0 00139EF0 25010524 */   addiu     $5, $0, 0x125
    /* 39EF4 00139EF4 2D206002 */  daddu      $4, $19, $0
    /* 39EF8 00139EF8 25010524 */  addiu      $5, $0, 0x125
    /* 39EFC 00139EFC E080090C */  jal        func_00260380
    /* 39F00 00139F00 68C2A626 */   addiu     $6, $21, %lo(D_0062C268)
.align 2
  .L00139F04:
    /* 39F04 00139F04 2C00048E */  lw         $4, 0x2C($16)
    /* 39F08 00139F08 6401040C */  jal        func_00100590
    /* 39F0C 00139F0C 2D28A003 */   daddu     $5, $29, $0
    /* 39F10 00139F10 0400A28F */  lw         $2, 0x4($29)
    /* 39F14 00139F14 0800058E */  lw         $5, 0x8($16)
    /* 39F18 00139F18 0500A214 */  bne        $5, $2, .L00139F30
    /* 39F1C 00139F1C 48198426 */   addiu     $4, $20, %lo(D_00551948)
    /* 39F20 00139F20 F290060C */  jal        debug_assertMessage
    /* 39F24 00139F24 00000000 */   nop
    /* 39F28 00139F28 E7FF0010 */  b          .L00139EC8
    /* 39F2C 00139F2C 00000000 */   nop
.align 2
  .L00139F30:
    /* 39F30 00139F30 0400038E */  lw         $3, 0x4($16)
    /* 39F34 00139F34 01004050 */  beql       $2, $0, .L00139F3C
    /* 39F38 00139F38 CD010000 */   break     0, 7
.align 2
  .L00139F3C:
    /* 39F3C 00139F3C 0000048E */  lw         $4, 0x0($16)
    /* 39F40 00139F40 21186500 */  addu       $3, $3, $5
    /* 39F44 00139F44 1A006200 */  div        $0, $3, $2
    /* 39F48 00139F48 10100000 */  mfhi       $2
    /* 39F4C 00139F4C 80100200 */  sll        $2, $2, 2
    /* 39F50 00139F50 21104400 */  addu       $2, $2, $4
    /* 39F54 00139F54 000051AC */  sw         $17, 0x0($2)
    /* 39F58 00139F58 0800038E */  lw         $3, 0x8($16)
    /* 39F5C 00139F5C 01006324 */  addiu      $3, $3, 0x1
    /* 39F60 00139F60 080003AE */  sw         $3, 0x8($16)
    /* 39F64 00139F64 0C00A28F */  lw         $2, 0xC($29)
    /* 39F68 00139F68 D7FF4018 */  blez       $2, .L00139EC8
    /* 39F6C 00139F6C 00000000 */   nop
    /* 39F70 00139F70 5001040C */  jal        func_00100540
    /* 39F74 00139F74 2C00048E */   lw        $4, 0x2C($16)
    /* 39F78 00139F78 D2FF0010 */  b          .L00139EC4
    /* 39F7C 00139F7C 5500023C */   lui       $2, %hi(D_00551910)
endlabel iosMsgSetEvent
```
