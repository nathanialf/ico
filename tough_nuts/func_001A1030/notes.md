
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_001A1030/0A1030.c`

Disassembly excerpt:

```
glabel func_001A1030
    /* A1030 001A1030 6E00023C */  lui        $v0, %hi(D_006E4890)
    /* A1034 001A1034 50940334 */  ori        $v1, $zero, 0x9450
    /* A1038 001A1038 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* A103C 001A103C 90484424 */  addiu      $a0, $v0, %lo(D_006E4890)
    /* A1040 001A1040 21288300 */  addu       $a1, $a0, $v1
    /* A1044 001A1044 0000BFFF */  sd         $ra, 0x0($sp)
    /* A1048 001A1048 A89F80AF */  sw         $zero, %gp_rel(D_00632898)($gp)
    /* A104C 001A104C 4B00033C */  lui        $v1, %hi(D_004B2FD0)
.align 2
  .L001A1050:
    /* A1050 001A1050 D02F6824 */  addiu      $t0, $v1, %lo(D_004B2FD0)
    /* A1054 001A1054 07000269 */  ldl        $v0, 0x7($t0)
    /* A1058 001A1058 0000026D */  ldr        $v0, 0x0($t0)
    /* A105C 001A105C 0F000669 */  ldl        $a2, 0xF($t0)
    /* A1060 001A1060 0800066D */  ldr        $a2, 0x8($t0)
    /* A1064 001A1064 17000769 */  ldl        $a3, 0x17($t0)
    /* A1068 001A1068 1000076D */  ldr        $a3, 0x10($t0)
    /* A106C 001A106C 070082B0 */  sdl        $v0, 0x7($a0)
    /* A1070 001A1070 000082B4 */  sdr        $v0, 0x0($a0)
    /* A1074 001A1074 0F0086B0 */  sdl        $a2, 0xF($a0)
    /* A1078 001A1078 080086B4 */  sdr        $a2, 0x8($a0)
    /* A107C 001A107C 170087B0 */  sdl        $a3, 0x17($a0)
    /* A1080 001A1080 100087B4 */  sdr        $a3, 0x10($a0)
    /* A1084 001A1084 18008424 */  addiu      $a0, $a0, 0x18
    /* A1088 001A1088 2A108500 */  slt        $v0, $a0, $a1
    /* A108C 001A108C 00000000 */  nop
    /* A1090 001A1090 00000000 */  nop
    /* A1094 001A1094 EEFF4014 */  bnez       $v0, .L001A1050
    /* A1098 001A1098 00000000 */   nop
    /* A109C 001A109C BE2C060C */  jal        func_0018B2F8
    /* A10A0 001A10A0 00000000 */   nop
    /* A10A4 001A10A4 0000BFDF */  ld         $ra, 0x0($sp)
    /* A10A8 001A10A8 FC330608 */  j          func_0018CFF0
    /* A10AC 001A10AC 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001A1030
```
