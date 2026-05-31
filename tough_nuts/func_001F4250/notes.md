# func_001F4250 — parked

VRAM: 0x001F4250 (file_off 0x0F4250)
Asm source: asm/matchings/cod/0F4250/func_001F4250.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/weapon.c`

**Seed:** `tough_nuts/func_001F4250/func_001F4250.c`

Disassembly:

```
.align 3
nonmatching func_001F4250, 0x80

glabel func_001F4250
    /* F4250 001F4250 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F4254 001F4254 2000B2FF */  sd         $18, 0x20($29)
    /* F4258 001F4258 1000B1FF */  sd         $17, 0x10($29)
    /* F425C 001F425C 2D90A000 */  daddu      $18, $5, $0
    /* F4260 001F4260 3000BFFF */  sd         $31, 0x30($29)
    /* F4264 001F4264 2D28C000 */  daddu      $5, $6, $0
    /* F4268 001F4268 0000B0FF */  sd         $16, 0x0($29)
    /* F426C 001F426C 5C01908C */  lw         $16, 0x15C($4)
    /* F4270 001F4270 0008048E */  lw         $4, 0x800($16)
    /* F4274 001F4274 0800828C */  lw         $2, 0x8($4)
    /* F4278 001F4278 03004010 */  beqz       $2, .L001F4288
    /* F427C 001F427C A0001126 */   addiu     $17, $16, 0xA0
    /* F4280 001F4280 5C01428C */  lw         $2, 0x15C($2)
    /* F4284 001F4284 300640AC */  sw         $0, 0x630($2)
.align 2
  .L001F4288:
    /* F4288 001F4288 FFFF0324 */  addiu      $3, $0, -0x1
    /* F428C 001F428C 01000224 */  addiu      $2, $0, 0x1
    /* F4290 001F4290 040082AC */  sw         $2, 0x4($4)
    /* F4294 001F4294 0C0083AC */  sw         $3, 0xC($4)
    /* F4298 001F4298 0300A010 */  beqz       $5, .L001F42A8
    /* F429C 001F429C 080080AC */   sw        $0, 0x8($4)
    /* F42A0 001F42A0 0C36040C */  jal        func_0010D830
    /* F42A4 001F42A4 50010426 */   addiu     $4, $16, 0x150
.align 2
  .L001F42A8:
    /* F42A8 001F42A8 30010426 */  addiu      $4, $16, 0x130
    /* F42AC 001F42AC C017040C */  jal        func_00105F00
    /* F42B0 001F42B0 2D284002 */   daddu     $5, $18, $0
    /* F42B4 001F42B4 9C0020AE */  sw         $0, 0x9C($17)
    /* F42B8 001F42B8 3000BFDF */  ld         $31, 0x30($29)
    /* F42BC 001F42BC 2000B2DF */  ld         $18, 0x20($29)
    /* F42C0 001F42C0 1000B1DF */  ld         $17, 0x10($29)
    /* F42C4 001F42C4 0000B0DF */  ld         $16, 0x0($29)
    /* F42C8 001F42C8 0800E003 */  jr         $31
    /* F42CC 001F42CC 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001F4250
```
