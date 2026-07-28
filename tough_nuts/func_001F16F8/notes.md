# func_001F16F8 — parked

VRAM: 0x001F16F8 (file_off 0x0F16F8)
Asm source: asm/nonmatchings/cod/0F16F8/func_001F16F8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/sugiTree.c`

**Seed:** `tough_nuts/func_001F16F8/func_001F16F8.c`

Disassembly:

```
.align 3
nonmatching func_001F16F8, 0xB4

glabel func_001F16F8
    /* F16F8 001F16F8 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F16FC 001F16FC 3000B4E7 */  swc1       $f20, 0x30($29)
    /* F1700 001F1700 2000BFFF */  sd         $31, 0x20($29)
    /* F1704 001F1704 0000B0FF */  sd         $16, 0x0($29)
    /* F1708 001F1708 1000B1FF */  sd         $17, 0x10($29)
    /* F170C 001F170C 5C01918C */  lw         $17, 0x15C($4)
    /* F1710 001F1710 8043013C */  lui        $1, (0x43800000 >> 16)
    /* F1714 001F1714 00A08144 */  mtc1       $1, $f20
    /* F1718 001F1718 9E14040C */  jal        func_00105278
    /* F171C 001F171C 0008308E */   lw        $16, 0x800($17)
    /* F1720 001F1720 20002526 */  addiu      $5, $17, 0x20
    /* F1724 001F1724 C817040C */  jal        func_00105F20
    /* F1728 001F1728 2D204000 */   daddu     $4, $2, $0
    /* F172C 001F172C 543A040C */  jal        func_0010E950
    /* F1730 001F1730 00000486 */   lh        $4, 0x0($16)
    /* F1734 001F1734 02001446 */  mul.s      $f0, $f0, $f20
    /* F1738 001F1738 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* F173C 001F173C 00080444 */  mfc1       $4, $f1
    /* F1740 001F1740 00240400 */  sll        $4, $4, 16
    /* F1744 001F1744 F013040C */  jal        func_00104FC0
    /* F1748 001F1748 03240400 */   sra       $4, $4, 16
    /* F174C 001F174C 00000486 */  lh         $4, 0x0($16)
    /* F1750 001F1750 40240400 */  sll        $4, $4, 17
    /* F1754 001F1754 543A040C */  jal        func_0010E950
    /* F1758 001F1758 03240400 */   sra       $4, $4, 16
    /* F175C 001F175C 02001446 */  mul.s      $f0, $f0, $f20
    /* F1760 001F1760 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* F1764 001F1764 00080444 */  mfc1       $4, $f1
    /* F1768 001F1768 00240400 */  sll        $4, $4, 16
    /* F176C 001F176C D213040C */  jal        func_00104F48
    /* F1770 001F1770 03240400 */   sra       $4, $4, 16
    /* F1774 001F1774 9E14040C */  jal        func_00105278
    /* F1778 001F1778 00000000 */   nop
    /* F177C 001F177C 0C00248E */  lw         $4, 0xC($17)
    /* F1780 001F1780 C817040C */  jal        func_00105F20
    /* F1784 001F1784 2D284000 */   daddu     $5, $2, $0
    /* F1788 001F1788 00000296 */  lhu        $2, 0x0($16)
    /* F178C 001F178C 2000BFDF */  ld         $31, 0x20($29)
    /* F1790 001F1790 80004224 */  addiu      $2, $2, 0x80
    /* F1794 001F1794 1000B1DF */  ld         $17, 0x10($29)
    /* F1798 001F1798 000002A6 */  sh         $2, 0x0($16)
    /* F179C 001F179C 0000B0DF */  ld         $16, 0x0($29)
    /* F17A0 001F17A0 3000B4C7 */  lwc1       $f20, 0x30($29)
    /* F17A4 001F17A4 0800E003 */  jr         $31
    /* F17A8 001F17A8 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001F16F8
    /* F17AC 001F17AC 00000000 */  nop
```
