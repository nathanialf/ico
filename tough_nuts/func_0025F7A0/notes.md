# func_0025F7A0 — parked

VRAM: 0x0025F7A0 (file_off 0x15F7A0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025F7A0.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=67). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025F7A0/func_0025F7A0.c`

Disassembly:

```
.align 3
nonmatching func_0025F7A0, 0x10C

glabel func_0025F7A0
    /* 15F7A0 0025F7A0 0000838C */  lw         $3, 0x0($4)
    /* 15F7A4 0025F7A4 2D380000 */  daddu      $7, $0, $0
    /* 15F7A8 0025F7A8 0400888C */  lw         $8, 0x4($4)
    /* 15F7AC 0025F7AC 0200622C */  sltiu      $2, $3, 0x2
    /* 15F7B0 0025F7B0 05004010 */  beqz       $2, .L0025F7C8
    /* 15F7B4 0025F7B4 0C00858C */   lw        $5, 0xC($4)
    /* 15F7B8 0025F7B8 1000023C */  lui        $2, (0x100000 >> 16)
    /* 15F7BC 0025F7BC FF000724 */  addiu      $7, $0, 0xFF
    /* 15F7C0 0025F7C0 26000010 */  b          .L0025F85C
    /* 15F7C4 0025F7C4 2528A200 */   or        $5, $5, $2
.align 2
  .L0025F7C8:
    /* 15F7C8 0025F7C8 04006238 */  xori       $2, $3, 0x4
    /* 15F7CC 0025F7CC 14004010 */  beqz       $2, .L0025F820
    /* 15F7D0 0025F7D0 02006238 */   xori      $2, $3, 0x2
    /* 15F7D4 0025F7D4 03004014 */  bnez       $2, .L0025F7E4
    /* 15F7D8 0025F7D8 00000000 */   nop
    /* 15F7DC 0025F7DC 1F000010 */  b          .L0025F85C
    /* 15F7E0 0025F7E0 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025F7E4:
    /* 15F7E4 0025F7E4 1E00A010 */  beqz       $5, .L0025F860
    /* 15F7E8 0025F7E8 80FF033C */   lui       $3, (0xFF800000 >> 16)
    /* 15F7EC 0025F7EC 0800838C */  lw         $3, 0x8($4)
    /* 15F7F0 0025F7F0 82FF6228 */  slti       $2, $3, -0x7E
    /* 15F7F4 0025F7F4 07004010 */  beqz       $2, .L0025F814
    /* 15F7F8 0025F7F8 82FF0224 */   addiu     $2, $0, -0x7E
    /* 15F7FC 0025F7FC 23104300 */  subu       $2, $2, $3
    /* 15F800 0025F800 1A004328 */  slti       $3, $2, 0x1A
    /* 15F804 0025F804 14006014 */  bnez       $3, .L0025F858
    /* 15F808 0025F808 06284500 */   srlv      $5, $5, $2
    /* 15F80C 0025F80C 12000010 */  b          .L0025F858
    /* 15F810 0025F810 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025F814:
    /* 15F814 0025F814 80006228 */  slti       $2, $3, 0x80
    /* 15F818 0025F818 04004014 */  bnez       $2, .L0025F82C
    /* 15F81C 0025F81C 7F006724 */   addiu     $7, $3, 0x7F
.align 2
  .L0025F820:
    /* 15F820 0025F820 FF000724 */  addiu      $7, $0, 0xFF
    /* 15F824 0025F824 0D000010 */  b          .L0025F85C
    /* 15F828 0025F828 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025F82C:
    /* 15F82C 0025F82C 40000224 */  addiu      $2, $0, 0x40
    /* 15F830 0025F830 7F00A330 */  andi       $3, $5, 0x7F
    /* 15F834 0025F834 04006254 */  bnel       $3, $2, .L0025F848
    /* 15F838 0025F838 3F00A524 */   addiu     $5, $5, 0x3F
    /* 15F83C 0025F83C 8000A330 */  andi       $3, $5, 0x80
    /* 15F840 0025F840 4000A224 */  addiu      $2, $5, 0x40
    /* 15F844 0025F844 0B284300 */  movn       $5, $2, $3
.align 2
  .L0025F848:
    /* 15F848 0025F848 0400A304 */  bgezl      $5, .L0025F85C
    /* 15F84C 0025F84C C2290500 */   srl       $5, $5, 7
    /* 15F850 0025F850 42280500 */  srl        $5, $5, 1
    /* 15F854 0025F854 0100E724 */  addiu      $7, $7, 0x1
.align 2
  .L0025F858:
    /* 15F858 0025F858 C2290500 */  srl        $5, $5, 7
.align 2
  .L0025F85C:
    /* 15F85C 0025F85C 80FF033C */  lui        $3, (0xFF800000 >> 16)
.align 2
  .L0025F860:
    /* 15F860 0025F860 7F00023C */  lui        $2, (0x7FFFFF >> 16)
    /* 15F864 0025F864 2430C300 */  and        $6, $6, $3
    /* 15F868 0025F868 FFFF4234 */  ori        $2, $2, (0x7FFFFF & 0xFFFF)
    /* 15F86C 0025F86C 2410A200 */  and        $2, $5, $2
    /* 15F870 0025F870 7F80033C */  lui        $3, (0x807FFFFF >> 16)
    /* 15F874 0025F874 2530C200 */  or         $6, $6, $2
    /* 15F878 0025F878 FFFF6334 */  ori        $3, $3, (0x807FFFFF & 0xFFFF)
    /* 15F87C 0025F87C FF00E430 */  andi       $4, $7, 0xFF
    /* 15F880 0025F880 2430C300 */  and        $6, $6, $3
    /* 15F884 0025F884 C0250400 */  sll        $4, $4, 23
    /* 15F888 0025F888 FF7F023C */  lui        $2, (0x7FFFFFFF >> 16)
    /* 15F88C 0025F88C 2530C400 */  or         $6, $6, $4
    /* 15F890 0025F890 FFFF4234 */  ori        $2, $2, (0x7FFFFFFF & 0xFFFF)
    /* 15F894 0025F894 C01F0800 */  sll        $3, $8, 31
    /* 15F898 0025F898 2430C200 */  and        $6, $6, $2
    /* 15F89C 0025F89C 2530C300 */  or         $6, $6, $3
    /* 15F8A0 0025F8A0 00008644 */  mtc1       $6, $f0
    /* 15F8A4 0025F8A4 0800E003 */  jr         $31
    /* 15F8A8 0025F8A8 00000000 */   nop
endlabel func_0025F7A0
    /* 15F8AC 0025F8AC 00000000 */  nop
```
