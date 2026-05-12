
---

## Attempt at 2026-05-12

**Reason parked:** 3-store wrapper: gcc reorders to do f13 conv+store first, then f12 store last; expected has f12 first

Seed: `tough_nuts/func_001EF9A8/0EF9A8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001EF9A8; check asm/matchings/cod/0EF9A8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** C (int)float emits trunc.w.s but target has cvt.w.s; no CVT macro available

Seed: `tough_nuts/func_001EF9A8/0EF9A8.c.new`

Disassembly excerpt:

```
glabel func_001EF9A8
    /* EF9A8 001EF9A8 2700023C */  lui        $v0, %hi(D_00275120)
    /* EF9AC 001EF9AC 20514224 */  addiu      $v0, $v0, %lo(D_00275120)
    /* EF9B0 001EF9B0 24600046 */  .word      0x46006024                    # cvt.w.s    $f0, $f12 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* EF9B4 001EF9B4 EC0040E4 */  swc1       $f0, 0xEC($v0)
    /* EF9B8 001EF9B8 F80044AC */  sw         $a0, 0xF8($v0)
    /* EF9BC 001EF9BC 24680046 */  .word      0x46006824                    # cvt.w.s    $f0, $f13 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* EF9C0 001EF9C0 F00040E4 */  swc1       $f0, 0xF0($v0)
    /* EF9C4 001EF9C4 0800E003 */  jr         $ra
    /* EF9C8 001EF9C8 00000000 */   nop
endlabel func_001EF9A8
```
