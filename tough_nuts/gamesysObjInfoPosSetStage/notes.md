# debug_SelectPad2ControlGobj — parked

VRAM: 0x001A8770 (file_off 0x0A8770)
Asm source: asm/aug6/nonmatchings/common/src/gamesys/debug_SelectPad2ControlGobj.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `common/src/gamesys.c`

**Seed:** `tough_nuts/debug_SelectPad2ControlGobj/debug_SelectPad2ControlGobj.c`

Disassembly:

```
.align 3
nonmatching debug_SelectPad2ControlGobj, 0x11C

glabel debug_SelectPad2ControlGobj
    /* A8770 001A8770 40FFBD27 */  addiu      $29, $29, -0xC0
    /* A8774 001A8774 A000B4FF */  sd         $20, 0xA0($29)
    /* A8778 001A8778 7000B1FF */  sd         $17, 0x70($29)
    /* A877C 001A877C 2DA08000 */  daddu      $20, $4, $0
    /* A8780 001A8780 6000B0FF */  sd         $16, 0x60($29)
    /* A8784 001A8784 1000B127 */  addiu      $17, $29, 0x10
    /* A8788 001A8788 B000BFFF */  sd         $31, 0xB0($29)
    /* A878C 001A878C 2D800000 */  daddu      $16, $0, $0
    /* A8790 001A8790 9000B3FF */  sd         $19, 0x90($29)
    /* A8794 001A8794 E4F9040C */  jal        isysGObjGetExist_begin
    /* A8798 001A8798 8000B2FF */   sd        $18, 0x80($29)
    /* A879C 001A879C 2D304000 */  daddu      $6, $2, $0
    /* A87A0 001A87A0 1900C010 */  beqz       $6, .L001A8808
    /* A87A4 001A87A4 6100133C */   lui       $19, %hi(D_0060E1D8)
    /* A87A8 001A87A8 DCA29227 */  addiu      $18, $28, %gp_rel(D_0062AECC)
    /* A87AC 001A87AC 0C00C58C */  lw         $5, 0xC($6)
.align 2
  .L001A87B0:
    /* A87B0 001A87B0 02000224 */  addiu      $2, $0, 0x2
    /* A87B4 001A87B4 0300A210 */  beq        $5, $2, .L001A87C4
    /* A87B8 001A87B8 04000224 */   addiu     $2, $0, 0x4
    /* A87BC 001A87BC 0B00A214 */  bne        $5, $2, .L001A87EC
    /* A87C0 001A87C0 00000000 */   nop
.align 2
  .L001A87C4:
    /* A87C4 001A87C4 64000324 */  addiu      $3, $0, 0x64
    /* A87C8 001A87C8 2A00043C */  lui        $4, %hi(D_0029F060)
    /* A87CC 001A87CC 1818A300 */  mult       $3, $5, $3
    /* A87D0 001A87D0 C0101000 */  sll        $2, $16, 3
    /* A87D4 001A87D4 60F08424 */  addiu      $4, $4, %lo(D_0029F060)
    /* A87D8 001A87D8 21105100 */  addu       $2, $2, $17
    /* A87DC 001A87DC 040046AC */  sw         $6, 0x4($2)
    /* A87E0 001A87E0 01001026 */  addiu      $16, $16, 0x1
    /* A87E4 001A87E4 21186400 */  addu       $3, $3, $4
    /* A87E8 001A87E8 000043AC */  sw         $3, 0x0($2)
.align 2
  .L001A87EC:
    /* A87EC 001A87EC F8F9040C */  jal        isysGObjGetExist_next
    /* A87F0 001A87F0 2D20C000 */   daddu     $4, $6, $0
    /* A87F4 001A87F4 2D304000 */  daddu      $6, $2, $0
    /* A87F8 001A87F8 EDFFC054 */  bnel       $6, $0, .L001A87B0
    /* A87FC 001A87FC 0C00C58C */   lw        $5, 0xC($6)
    /* A8800 001A8800 02000010 */  b          .L001A880C
    /* A8804 001A8804 00000000 */   nop
.align 2
  .L001A8808:
    /* A8808 001A8808 DCA29227 */  addiu      $18, $28, %gp_rel(D_0062AECC)
.align 2
  .L001A880C:
    /* A880C 001A880C 01008056 */  bnel       $20, $0, .L001A8814
    /* A8810 001A8810 DCA280AF */   sw        $0, %gp_rel(D_0062AECC)($28)
.align 2
  .L001A8814:
    /* A8814 001A8814 0000B0AF */  sw         $16, 0x0($29)
    /* A8818 001A8818 D8E16426 */  addiu      $4, $19, %lo(D_0060E1D8)
    /* A881C 001A881C 0800B2AF */  sw         $18, 0x8($29)
    /* A8820 001A8820 0A000524 */  addiu      $5, $0, 0xA
    /* A8824 001A8824 32000624 */  addiu      $6, $0, 0x32
    /* A8828 001A8828 0B000724 */  addiu      $7, $0, 0xB
    /* A882C 001A882C 1000A827 */  addiu      $8, $29, 0x10
    /* A8830 001A8830 08000924 */  addiu      $9, $0, 0x8
    /* A8834 001A8834 2D500000 */  daddu      $10, $0, $0
    /* A8838 001A8838 7A93060C */  jal        func_001A4DE8
    /* A883C 001A883C 01000B24 */   addiu     $11, $0, 0x1
    /* A8840 001A8840 07004018 */  blez       $2, .L001A8860
    /* A8844 001A8844 DCA2838F */   lw        $3, %gp_rel(D_0062AECC)($28)
    /* A8848 001A8848 01000224 */  addiu      $2, $0, 0x1
    /* A884C 001A884C C0180300 */  sll        $3, $3, 3
    /* A8850 001A8850 2120A303 */  addu       $4, $29, $3
    /* A8854 001A8854 1400858C */  lw         $5, 0x14($4)
    /* A8858 001A8858 04000010 */  b          .L001A886C
    /* A885C 001A885C 209285AF */   sw        $5, %gp_rel(D_00629E10)($28)
.align 2
  .L001A8860:
    /* A8860 001A8860 27180200 */  nor        $3, $0, $2
    /* A8864 001A8864 FFFF0224 */  addiu      $2, $0, -0x1
    /* A8868 001A8868 0B100300 */  movn       $2, $0, $3
.align 2
  .L001A886C:
    /* A886C 001A886C B000BFDF */  ld         $31, 0xB0($29)
    /* A8870 001A8870 A000B4DF */  ld         $20, 0xA0($29)
    /* A8874 001A8874 9000B3DF */  ld         $19, 0x90($29)
    /* A8878 001A8878 8000B2DF */  ld         $18, 0x80($29)
    /* A887C 001A887C 7000B1DF */  ld         $17, 0x70($29)
    /* A8880 001A8880 6000B0DF */  ld         $16, 0x60($29)
    /* A8884 001A8884 0800E003 */  jr         $31
    /* A8888 001A8888 C000BD27 */   addiu     $29, $29, 0xC0
endlabel debug_SelectPad2ControlGobj
    /* A888C 001A888C 00000000 */  nop
```
