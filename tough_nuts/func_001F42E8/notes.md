# func_001F42E8 — parked

VRAM: 0x001F42E8 (file_off 0x0F42E8)
Asm source: asm/matchings/cod/0F42E8/func_001F42E8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (NOP)

**TU:** `src/weapon.c`

**Seed:** `tough_nuts/func_001F42E8/func_001F42E8.c`

Disassembly:

```
.align 3
nonmatching func_001F42E8, 0x30

glabel func_001F42E8
    /* F42E8 001F42E8 5C01828C */  lw         $2, 0x15C($4)
    /* F42EC 001F42EC 24000524 */  addiu      $5, $0, 0x24
    /* F42F0 001F42F0 6100033C */  lui        $3, %hi(D_006124F8)
    /* F42F4 001F42F4 0008448C */  lw         $4, 0x800($2)
    /* F42F8 001F42F8 F8246324 */  addiu      $3, $3, %lo(D_006124F8)
    /* F42FC 001F42FC 0000828C */  lw         $2, 0x0($4)
    /* F4300 001F4300 18104500 */  mult       $2, $2, $5
    /* F4304 001F4304 21186200 */  addu       $3, $3, $2
    /* F4308 001F4308 0C0060C4 */  lwc1       $f0, 0xC($3)
    /* F430C 001F430C 20008046 */  cvt.s.w    $f0, $f0
    /* F4310 001F4310 0800E003 */  jr         $31
    /* F4314 001F4314 00000000 */   nop
endlabel func_001F42E8
```
