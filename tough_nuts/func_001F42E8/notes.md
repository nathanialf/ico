
---

## Attempt at 2026-05-12

**Reason parked:** offset folding: built embeds +0xC in addiu, expected embeds it in lwc1 offset

Seed: `tough_nuts/func_001F42E8/0F42E8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F42E8; check asm/matchings/cod/0F42E8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** float table lookup: addu dst reg swap + cvt.s.w in jr delay vs before jr

Seed: `tough_nuts/func_001F42E8/0F42E8.c.new`

Disassembly excerpt:

```
glabel func_001F42E8
    /* F42E8 001F42E8 5C01828C */  lw         $v0, 0x15C($a0)
    /* F42EC 001F42EC 24000524 */  addiu      $a1, $zero, 0x24
    /* F42F0 001F42F0 6100033C */  lui        $v1, %hi(D_006124F8)
    /* F42F4 001F42F4 0008448C */  lw         $a0, 0x800($v0)
    /* F42F8 001F42F8 F8246324 */  addiu      $v1, $v1, %lo(D_006124F8)
    /* F42FC 001F42FC 0000828C */  lw         $v0, 0x0($a0)
    /* F4300 001F4300 18104500 */  mult       $v0, $v0, $a1
    /* F4304 001F4304 21186200 */  addu       $v1, $v1, $v0
    /* F4308 001F4308 0C0060C4 */  lwc1       $f0, 0xC($v1)
    /* F430C 001F430C 20008046 */  cvt.s.w    $f0, $f0
    /* F4310 001F4310 0800E003 */  jr         $ra
    /* F4314 001F4314 00000000 */   nop
endlabel func_001F42E8
```
