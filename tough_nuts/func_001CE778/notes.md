
---

## Attempt at 2026-05-13

**Reason parked:** do-while vs while-with-b structure differs

Seed: `tough_nuts/func_001CE778/0CE778.c`

Disassembly excerpt:

```
glabel func_001CE778
    /* CE778 001CE778 2D408000 */  daddu      $t0, $a0, $zero
    /* CE77C 001CE77C 5C01028D */  lw         $v0, 0x15C($t0)
    /* CE780 001CE780 8800478C */  lw         $a3, 0x88($v0)
    /* CE784 001CE784 0D00E018 */  blez       $a3, .L001CE7BC
    /* CE788 001CE788 2D300000 */   daddu     $a2, $zero, $zero
    /* CE78C 001CE78C 04000010 */  b          .L001CE7A0
    /* CE790 001CE790 0008448C */   lw        $a0, 0x800($v0)
    /* CE794 001CE794 00000000 */  nop
.align 2
  .L001CE798:
    /* CE798 001CE798 5C01028D */  lw         $v0, 0x15C($t0)
    /* CE79C 001CE79C 0008448C */  lw         $a0, 0x800($v0)
.align 2
  .L001CE7A0:
    /* CE7A0 001CE7A0 80100600 */  sll        $v0, $a2, 2
    /* CE7A4 001CE7A4 1400838C */  lw         $v1, 0x14($a0)
    /* CE7A8 001CE7A8 0100C624 */  addiu      $a2, $a2, 0x1
    /* CE7AC 001CE7AC 2A28C700 */  slt        $a1, $a2, $a3
    /* CE7B0 001CE7B0 21104300 */  addu       $v0, $v0, $v1
    /* CE7B4 001CE7B4 F8FFA014 */  bnez       $a1, .L001CE798
    /* CE7B8 001CE7B8 000040AC */   sw        $zero, 0x0($v0)
.align 2
  .L001CE7BC:
    /* CE7BC 001CE7BC 0800E003 */  jr         $ra
    /* CE7C0 001CE7C0 00000000 */   nop
endlabel func_001CE778
```
