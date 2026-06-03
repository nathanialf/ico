# voBufIncCount — parked

VRAM: 0x0019BAC8 (file_off 0x09BAC8)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_vobuf/voBufIncCount.s

## Attempt at 2026-06-03

**Reason parked:** 30-stall (clean, no crutches). Body matches at rc2; the 2 diffs are store-order + unfilled jr-delay. PROVEN toolchain finding, not a source floor: ROM is a 4-insn frameless leaf (sw 12; sw 8; jr; nop) but gcc -O2 dbr ALWAYS fills the jr delay (3-insn fn) for a 2-store leaf, and -O2 sorts stores ascending. Exact ROM bytes require -O1 (descending order) + -fno-delayed-branch (gcc leaves delay) + old assembler 2.9-991111 (does not over-fill). i.e. the ito/mpeg movie module was built with different flags than the game. Per-func extra_cflags/explicit-nop rejected as crutches; correct fix is module-level build config (deferred). Permuter cannot help (operates under -O2+2.96).

**TU:** `ito/mpeg/mv_vobuf.c`

**Seed:** `tough_nuts/voBufIncCount/voBufIncCount.c`

Disassembly:

```
.align 3
nonmatching voBufIncCount, 0x10

glabel voBufIncCount
    /* 9BAC8 0019BAC8 0C0080AC */  sw         $0, 0xC($4)
    /* 9BACC 0019BACC 080080AC */  sw         $0, 0x8($4)
    /* 9BAD0 0019BAD0 0800E003 */  jr         $31
    /* 9BAD4 0019BAD4 00000000 */   nop
endlabel voBufIncCount
```

## Permuter status (user-requested shot, this session)
Permuter CANNOT run on this function: tools/permute_run.sh is hardwired for the
retail `cod` segment layout (asm/matchings/cod/<file_off>/func_<hex>.s, func_XXXXXXXX
names). aug6 uses asm/aug6/matchings/<module>/<TU>/<name>.s with NAMED functions, so
the script can locate neither the named form (name-guard reject) nor the hex form
(func_0019BAC8 -> looks for asm/matchings/cod/09BAC8/, which doesn't exist on aug6).
=> auto_permute.sh / the Step-4 offline batch is a NO-OP for aug6 named funcs.
Independently, the permuter builds under -O2/2.96 and the residual is a module
build-flag issue (-O1/-fno-delayed-branch/old-as), so it could not help even if ported.
