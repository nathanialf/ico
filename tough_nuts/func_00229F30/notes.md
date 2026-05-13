
---

## Attempt at 2026-05-08

**Reason parked:** wait-loop chain: ee-gcc 41 insns; original 44 (a0 spill+reload pattern + extra alignment nops)

Seed: `tough_nuts/func_00229F30/129F30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00229F30; check asm/matchings/cod/129F30/)
```

---

## Attempt at 2026-05-13

**Reason parked:** loop alignment nops missing; sw a0 in beq delay

Seed: `tough_nuts/func_00229F30/129F30.c.new`

Disassembly excerpt:

```
glabel func_00229F30
    /* 129F30 00229F30 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 129F34 00229F34 1000BFFF */  sd         $ra, 0x10($sp)
    /* 129F38 00229F38 0000A4AF */  sw         $a0, 0x0($sp)
    /* 129F3C 00229F3C 04000010 */  b          .L00229F50
    /* 129F40 00229F40 00000000 */   nop
    /* 129F44 00229F44 00000000 */  nop
.align 2
  .L00229F48:
    /* 129F48 00229F48 A80E080C */  jal        func_00203AA0
    /* 129F4C 00229F4C 01000424 */   addiu     $a0, $zero, 0x1
.align 2
  .L00229F50:
    /* 129F50 00229F50 0000A48F */  lw         $a0, 0x0($sp)
    /* 129F54 00229F54 C842013C */  lui        $at, (0x42C80000 >> 16)
    /* 129F58 00229F58 00608144 */  mtc1       $at, $f12
    /* 129F5C 00229F5C B6F5050C */  jal        func_0017D6D8
    /* 129F60 00229F60 F491858F */   lw        $a1, %gp_rel(D_00631AE4)($gp)
    /* 129F64 00229F64 F8FF4010 */  beqz       $v0, .L00229F48
    /* 129F68 00229F68 00000000 */   nop
    /* 129F6C 00229F6C F6DB060C */  jal        func_001B6FD8
    /* 129F70 00229F70 33000424 */   addiu     $a0, $zero, 0x33
    /* 129F74 00229F74 96EC050C */  jal        func_0017B258
    /* 129F78 00229F78 73000424 */   addiu     $a0, $zero, 0x73
    /* 129F7C 00229F7C 01000224 */  addiu      $v0, $zero, 0x1
    /* 129F80 00229F80 01000424 */  addiu      $a0, $zero, 0x1
    /* 129F84 00229F84 A80E080C */  jal        func_00203AA0
    /* 129F88 00229F88 C49C82AF */   sw        $v0, %gp_rel(D_006325B4)($gp)
    /* 129F8C 00229F8C 40010424 */  addiu      $a0, $zero, 0x140
    /* 129F90 00229F90 01000524 */  addiu      $a1, $zero, 0x1
    /* 129F94 00229F94 E8A5040C */  jal        func_001297A0
    /* 129F98 00229F98 2D300000 */   daddu     $a2, $zero, $zero
    /* 129F9C 00229F9C 04000010 */  b          .L00229FB0
    /* 129FA0 00229FA0 00000000 */   nop
    /* 129FA4 00229FA4 00000000 */  nop
.align 2
  .L00229FA8:
    /* 129FA8 00229FA8 A80E080C */  jal        func_00203AA0
    /* 129FAC 00229FAC 01000424 */   addiu     $a0, $zero, 0x1
.align 2
  .L00229FB0:
    /* 129FB0 00229FB0 A0AA040C */  jal        func_0012AA80
    /* 129FB4 00229FB4 40010424 */   addiu     $a0, $zero, 0x140
    /* 129FB8 00229FB8 FBFF4010 */  beqz       $v0, .L00229FA8
    /* 129FBC 00229FBC 00000000 */   nop
    /* 129FC0 00229FC0 A80E080C */  jal        func_00203AA0
    /* 129FC4 00229FC4 01000424 */   addiu     $a0, $zero, 0x1
    /* 129FC8 00229FC8 F6DB060C */  jal        func_001B6FD8
    /* 129FCC 00229FCC 32000424 */   addiu     $a0, $zero, 0x32
    /* 129FD0 00229FD0 1000BFDF */  ld         $ra, 0x10($sp)
    /* 129FD4 00229FD4 C49C80AF */  sw         $zero, %gp_rel(D_006325B4)($gp)
    /* 129FD8 00229FD8 0800E003 */  jr         $ra
    /* 129FDC 00229FDC 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00229F30
```
