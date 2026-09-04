# func_001F17B0 — parked

VRAM: 0x001F17B0 (file_off 0x0F17B0)
Asm source: asm/nonmatchings/cod/0F17B0/func_001F17B0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE)

**TU:** `src/sugiTree.c`

**Seed:** `tough_nuts/func_001F17B0/func_001F17B0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001F17B0, 0x84

glabel func_001F17B0
    /* F17B0 001F17B0 90FFBD27 */  addiu      $29, $29, -0x70
    /* F17B4 001F17B4 6200063C */  lui        $6, %hi(D_0061A6D8)
    /* F17B8 001F17B8 4000B2FF */  sd         $18, 0x40($29)
    /* F17BC 001F17BC D8A6C624 */  addiu      $6, $6, %lo(D_0061A6D8)
    /* F17C0 001F17C0 6000BFFF */  sd         $31, 0x60($29)
    /* F17C4 001F17C4 23000724 */  addiu      $7, $0, 0x23
    /* F17C8 001F17C8 5000B3FF */  sd         $19, 0x50($29)
    /* F17CC 001F17CC 3000B1FF */  sd         $17, 0x30($29)
    /* F17D0 001F17D0 2000B0FF */  sd         $16, 0x20($29)
    /* F17D4 001F17D4 5C01828C */  lw         $2, 0x15C($4)
    /* F17D8 001F17D8 2097848F */  lw         $4, %gp_rel(D_00632010)($gp) /* gp_rel: (D_00632010) */
    /* F17DC 001F17DC 2008438C */  lw         $3, 0x820($2)
    /* F17E0 001F17E0 2E007080 */  lb         $16, 0x2E($3)
    /* F17E4 001F17E4 3EE8040C */  jal        func_0013A0F8
    /* F17E8 001F17E8 40281000 */   sll       $5, $16, 1
    /* F17EC 001F17EC 0900001A */  blez       $16, .L001F1814
    /* F17F0 001F17F0 2D904000 */   daddu     $18, $2, $0
    /* F17F4 001F17F4 2D880002 */  daddu      $17, $16, $0
    /* F17F8 001F17F8 2D804002 */  daddu      $16, $18, $0
    /* F17FC 001F17FC 00000000 */  nop
.align 2
  .L001F1800:
    /* F1800 001F1800 5893090C */  jal        rand
    /* F1804 001F1804 FFFF3126 */   addiu     $17, $17, -0x1
    /* F1808 001F1808 000002A6 */  sh         $2, 0x0($16)
    /* F180C 001F180C FCFF2016 */  bnez       $17, .L001F1800
    /* F1810 001F1810 02001026 */   addiu     $16, $16, 0x2
.align 2
  .L001F1814:
    /* F1814 001F1814 2D104002 */  daddu      $2, $18, $0
    /* F1818 001F1818 6000BFDF */  ld         $31, 0x60($29)
    /* F181C 001F181C 5000B3DF */  ld         $19, 0x50($29)
    /* F1820 001F1820 4000B2DF */  ld         $18, 0x40($29)
    /* F1824 001F1824 3000B1DF */  ld         $17, 0x30($29)
    /* F1828 001F1828 2000B0DF */  ld         $16, 0x20($29)
    /* F182C 001F182C 0800E003 */  jr         $31
    /* F1830 001F1830 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_001F17B0
    /* F1834 001F1834 00000000 */  nop
```
