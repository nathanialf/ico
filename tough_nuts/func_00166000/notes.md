
---

## Attempt at 2026-05-12

**Reason parked:** volatile spill emits but extra reload/daddu; gcc allocates cache reg differently (v0 expected, a0/v1 built)

Seed: `tough_nuts/func_00166000/066000.c`

Disassembly excerpt:

```
glabel func_00166000
    /* 66000 00166000 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 66004 00166004 0000A4AF */  sw         $a0, 0x0($sp)
    /* 66008 00166008 0000A28F */  lw         $v0, 0x0($sp)
    /* 6600C 0016600C 5C01438C */  lw         $v1, 0x15C($v0)
    /* 66010 00166010 500560AC */  sw         $zero, 0x550($v1)
    /* 66014 00166014 5C01448C */  lw         $a0, 0x15C($v0)
    /* 66018 00166018 800380AC */  sw         $zero, 0x380($a0)
    /* 6601C 0016601C 0800E003 */  jr         $ra
    /* 66020 00166020 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00166000
```
