# func_0013D928 — parked

VRAM: 0x0013D928 (file_off 0x03D928)
Asm source: asm/matchings/ios/thread/func_0013D928.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (DEFEAT_TCO)

**TU:** `ios/thread.c`

**Seed:** `tough_nuts/func_0013D928/func_0013D928.c`

Disassembly:

```
.align 3
nonmatching func_0013D928, 0x1C

glabel func_0013D928
    /* 3D928 0013D928 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 3D92C 0013D92C 0000BFFF */  sd         $31, 0x0($29)
    /* 3D930 0013D930 1401040C */  jal        func_00100450
    /* 3D934 0013D934 3000848C */   lw        $4, 0x30($4)
    /* 3D938 0013D938 0000BFDF */  ld         $31, 0x0($29)
    /* 3D93C 0013D93C 0800E003 */  jr         $31
    /* 3D940 0013D940 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0013D928
    /* 3D944 0013D944 00000000 */  nop
```
