
---

## Attempt at 2026-05-13

**Reason parked:** do-while vs while-with-b structure differs

Seed: `tough_nuts/func_001CE7C8/0CE7C8.c`

Disassembly excerpt:

```
glabel func_001CE7C8
    /* CE7C8 001CE7C8 2D408000 */  daddu      $t0, $a0, $zero
    /* CE7CC 001CE7CC 5C01028D */  lw         $v0, 0x15C($t0)
    /* CE7D0 001CE7D0 8800478C */  lw         $a3, 0x88($v0)
    /* CE7D4 001CE7D4 0D00E018 */  blez       $a3, .L001CE80C
    /* CE7D8 001CE7D8 2D300000 */   daddu     $a2, $zero, $zero
    /* CE7DC 001CE7DC 03000010 */  b          .L001CE7EC
    /* CE7E0 001CE7E0 01000924 */   addiu     $t1, $zero, 0x1
    /* CE7E4 001CE7E4 00000000 */  nop
.align 2
  .L001CE7E8:
    /* CE7E8 001CE7E8 5C01028D */  lw         $v0, 0x15C($t0)
.align 2
  .L001CE7EC:
    /* CE7EC 001CE7EC 0008448C */  lw         $a0, 0x800($v0)
    /* CE7F0 001CE7F0 80100600 */  sll        $v0, $a2, 2
    /* CE7F4 001CE7F4 1400838C */  lw         $v1, 0x14($a0)
    /* CE7F8 001CE7F8 0100C624 */  addiu      $a2, $a2, 0x1
    /* CE7FC 001CE7FC 2A28C700 */  slt        $a1, $a2, $a3
    /* CE800 001CE800 21104300 */  addu       $v0, $v0, $v1
    /* CE804 001CE804 F8FFA014 */  bnez       $a1, .L001CE7E8
    /* CE808 001CE808 000049AC */   sw        $t1, 0x0($v0)
.align 2
  .L001CE80C:
    /* CE80C 001CE80C 0800E003 */  jr         $ra
    /* CE810 001CE810 00000000 */   nop
endlabel func_001CE7C8
```
