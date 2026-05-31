# func_001F40D8 — parked

VRAM: 0x001F40D8 (file_off 0x0F40D8)
Asm source: asm/nonmatchings/src/weapon/func_001F40D8.s

## Attempt at 2026-05-31

**Reason parked:** rc3 byte-perfect EXCEPT 1-reg tie-break. IDENTICAL to func_001F4150 (matching one gets both). Models matched sibling func_001F41C8 (p=self->0x15C->0x800; loop func reload p->0x54/p->0x50 each iter). Structure: if(p->f_50==0)return; func_001F2388(((int*)p->f_54)[0]); for(i=0;i<p->f_50;i++)func_001F1868(((int*)p->f_54)[i]). TWO linked residuals: (1) guard n-load -> v1 (built) vs v0 (ROM reuses v0 for n then arr); (2) ROM re-inits i=0 in BOTH the beqz AND blez delay slots, but gcc tracks i==0 across the func_001F2388 call and shares it (fills the blez delay with the epilogue ld ra instead). 6 forms (block/inline/while/early-i/arr[i]) all rc3; the redundant-i=0-across-call is a gcc value-tracking diff, not a clean source shape. Permuter-friendly (1 reg). NOT a floor, stall 4.

**TU:** `src/weapon.c`

**Seed:** `tough_nuts/func_001F40D8/func_001F40D8.c`

Disassembly:

```
.align 3
nonmatching func_001F40D8, 0x78

glabel func_001F40D8
    /* F40D8 001F40D8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* F40DC 001F40DC 2000BFFF */  sd         $31, 0x20($29)
    /* F40E0 001F40E0 1000B1FF */  sd         $17, 0x10($29)
    /* F40E4 001F40E4 0000B0FF */  sd         $16, 0x0($29)
    /* F40E8 001F40E8 5C01828C */  lw         $2, 0x15C($4)
    /* F40EC 001F40EC 0008518C */  lw         $17, 0x800($2)
    /* F40F0 001F40F0 5000228E */  lw         $2, 0x50($17)
    /* F40F4 001F40F4 11004010 */  beqz       $2, .L001F413C
    /* F40F8 001F40F8 2D800000 */   daddu     $16, $0, $0
    /* F40FC 001F40FC 5400228E */  lw         $2, 0x54($17)
    /* F4100 001F4100 E2C8070C */  jal        func_001F2388
    /* F4104 001F4104 0000448C */   lw        $4, 0x0($2)
    /* F4108 001F4108 5000228E */  lw         $2, 0x50($17)
    /* F410C 001F410C 0B004018 */  blez       $2, .L001F413C
    /* F4110 001F4110 2D800000 */   daddu     $16, $0, $0
    /* F4114 001F4114 5400238E */  lw         $3, 0x54($17)
.align 2
  .L001F4118:
    /* F4118 001F4118 80101000 */  sll        $2, $16, 2
    /* F411C 001F411C 01001026 */  addiu      $16, $16, 0x1
    /* F4120 001F4120 21104300 */  addu       $2, $2, $3
    /* F4124 001F4124 1AC6070C */  jal        func_001F1868
    /* F4128 001F4128 0000448C */   lw        $4, 0x0($2)
    /* F412C 001F412C 5000228E */  lw         $2, 0x50($17)
    /* F4130 001F4130 2A100202 */  slt        $2, $16, $2
    /* F4134 001F4134 F8FF4054 */  bnel       $2, $0, .L001F4118
    /* F4138 001F4138 5400238E */   lw        $3, 0x54($17)
.align 2
  .L001F413C:
    /* F413C 001F413C 2000BFDF */  ld         $31, 0x20($29)
    /* F4140 001F4140 1000B1DF */  ld         $17, 0x10($29)
    /* F4144 001F4144 0000B0DF */  ld         $16, 0x0($29)
    /* F4148 001F4148 0800E003 */  jr         $31
    /* F414C 001F414C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001F40D8
```
