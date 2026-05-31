
---

## Attempt at 2026-05-31

**Reason parked:** dummy_sp_prologue RETIRED. 13C17C's first instr addiu sp,+16 is func_0023C148's epilogue restore borrowed into 17C's entry (overlap: 148 is in shared_sp_restore, ends at jr 0x23C178, delay slot = 0x23C17C = 17C's first byte). Two C funcs cannot share an instruction, so ee-gcc can never emit the leading +16 (proven 22 shapes). asm encodes the overlap directly; 148 keeps its shared_sp_restore entry and borrows 17C's first asm byte. NOT a codegen quirk — a linker-layout instruction overlap.

Seed: `tough_nuts/func_0023C17C/13C17C.c`

Disassembly excerpt:

```
glabel func_0023C17C
    /* 13C17C 0023C17C 1000BD27 */  addiu      $sp, $sp, 0x10
    /* 13C180 0023C180 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 13C184 0023C184 0000BFFF */  sd         $ra, 0x0($sp)
    /* 13C188 0023C188 282C060C */  jal        func_0018B0A0
    /* 13C18C 0023C18C 00000000 */   nop
    /* 13C190 0023C190 2D184000 */  daddu      $v1, $v0, $zero
    /* 13C194 0023C194 03000224 */  addiu      $v0, $zero, 0x3
    /* 13C198 0023C198 03006210 */  beq        $v1, $v0, .L0023C1A8
    /* 13C19C 0023C19C 09000224 */   addiu     $v0, $zero, 0x9
    /* 13C1A0 0023C1A0 02006214 */  bne        $v1, $v0, .L0023C1AC
    /* 13C1A4 0023C1A4 2D180000 */   daddu     $v1, $zero, $zero
.align 2
  .L0023C1A8:
    /* 13C1A8 0023C1A8 FFFF0324 */  addiu      $v1, $zero, -0x1
.align 2
  .L0023C1AC:
    /* 13C1AC 0023C1AC FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 13C1B0 0023C1B0 0000BFDF */  ld         $ra, 0x0($sp)
    /* 13C1B4 0023C1B4 0B100300 */  movn       $v0, $zero, $v1
    /* 13C1B8 0023C1B8 0800E003 */  jr         $ra
    /* 13C1BC 0023C1BC 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0023C17C
```
