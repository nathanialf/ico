# func_001EA3E0 — parked

VRAM: 0x001EA3E0 (file_off 0x0EA3E0)
Asm source: asm/nonmatchings/src/spider/func_001EA3E0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/spider.c`

**Seed:** `tough_nuts/func_001EA3E0/func_001EA3E0.c`

Disassembly:

```
.align 3
nonmatching func_001EA3E0, 0x9C

glabel func_001EA3E0
    /* EA3E0 001EA3E0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* EA3E4 001EA3E4 01000324 */  addiu      $3, $0, 0x1
    /* EA3E8 001EA3E8 4000B4FF */  sd         $20, 0x40($29)
    /* EA3EC 001EA3EC 1000B1FF */  sd         $17, 0x10($29)
    /* EA3F0 001EA3F0 2DA08000 */  daddu      $20, $4, $0
    /* EA3F4 001EA3F4 5000BFFF */  sd         $31, 0x50($29)
    /* EA3F8 001EA3F8 2D880000 */  daddu      $17, $0, $0
    /* EA3FC 001EA3FC 3000B3FF */  sd         $19, 0x30($29)
    /* EA400 001EA400 2000B2FF */  sd         $18, 0x20($29)
    /* EA404 001EA404 0000B0FF */  sd         $16, 0x0($29)
    /* EA408 001EA408 5C01828E */  lw         $2, 0x15C($20)
    /* EA40C 001EA40C 0008528C */  lw         $18, 0x800($2)
    /* EA410 001EA410 2000538E */  lw         $19, 0x20($18)
    /* EA414 001EA414 0F00601A */  blez       $19, .L001EA454
    /* EA418 001EA418 280043AE */   sw        $3, 0x28($18)
    /* EA41C 001EA41C 2400428E */  lw         $2, 0x24($18)
.align 2
  .L001EA420:
    /* EA420 001EA420 80801100 */  sll        $16, $17, 2
    /* EA424 001EA424 01003126 */  addiu      $17, $17, 0x1
    /* EA428 001EA428 21100202 */  addu       $2, $16, $2
    /* EA42C 001EA42C D2EB060C */  jal        func_001BAF48
    /* EA430 001EA430 0000448C */   lw        $4, 0x0($2)
    /* EA434 001EA434 2400428E */  lw         $2, 0x24($18)
    /* EA438 001EA438 01000524 */  addiu      $5, $0, 0x1
    /* EA43C 001EA43C 21800202 */  addu       $16, $16, $2
    /* EA440 001EA440 74E9060C */  jal        func_001BA5D0
    /* EA444 001EA444 0000048E */   lw        $4, 0x0($16)
    /* EA448 001EA448 2A103302 */  slt        $2, $17, $19
    /* EA44C 001EA44C F4FF4054 */  bnel       $2, $0, .L001EA420
    /* EA450 001EA450 2400428E */   lw        $2, 0x24($18)
.align 2
  .L001EA454:
    /* EA454 001EA454 2D208002 */  daddu      $4, $20, $0
    /* EA458 001EA458 5000BFDF */  ld         $31, 0x50($29)
    /* EA45C 001EA45C 4000B4DF */  ld         $20, 0x40($29)
    /* EA460 001EA460 65000524 */  addiu      $5, $0, 0x65
    /* EA464 001EA464 3000B3DF */  ld         $19, 0x30($29)
    /* EA468 001EA468 2000B2DF */  ld         $18, 0x20($29)
    /* EA46C 001EA46C 1000B1DF */  ld         $17, 0x10($29)
    /* EA470 001EA470 0000B0DF */  ld         $16, 0x0($29)
    /* EA474 001EA474 AA440708 */  j          func_001D12A8
    /* EA478 001EA478 6000BD27 */   addiu     $29, $29, 0x60
endlabel func_001EA3E0
    /* EA47C 001EA47C 00000000 */  nop
```
