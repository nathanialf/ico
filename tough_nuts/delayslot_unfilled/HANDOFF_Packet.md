# Packet.c `pac_makeMaterialTable` / `pac_makeMaterialTableLine` — BOTH MATCHED

Base: HEAD 8fe30da6, whole-image byte-identical,
`verify_elf: OK (build/ico.rom sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`.
Same sha1 after both matches — ROM bytes unchanged, both functions are now
real C instead of `INCLUDE_ASM`. Queue rows #5 and #6 → MATCHED.

Neither residual was a delay slot. As HANDOFF_enemy.md predicted, gcc
2.9-991111's own reorg pass filled the `j debug_assertMessage` slot on the
**first** attempt for both functions, once the parked C's `volatile` was
gone. The real work was two unrelated dev-data-model errors.

## Data model

`D_00672FD0` is the packet-builder context. `pac_setMaterialPacket` (already
matched, same TU) sets four running write cursors into the packet buffer:
`+0x20`, `+0x24`, `+0x28` masked with `0x0FFFFFFF` (DMA-physical addresses),
`+0x2C` unmasked. `pac_makeMaterialTable` writes a 2-word VIF UNPACK header
through cursor `+0x24`; `pac_makeMaterialTableLine` pushes a `0x17000000`
(VIF MSCNT) word plus three padding words through cursor `+0x2C`. Both then
tail-call the debug printer.

## Mechanism 1 — `pac_makeMaterialTable`: the 5th argument is `$8`, EABI

First C got 17 of 18 insns with the delay slot already filled; the one ROM
instruction the source could not emit was `daddu $8,$4,$0`. Read as o32 that
looks like a parameter copy into `t0` and there is no C shape that forces
one here. The project builds with **`-mabi=eabi`** (`grep -o -- '-mabi=[a-z]*'
build.ninja`), where integer arguments 5-8 live in **`$8-$11`**. So
`daddu $8,$4,$0` is *argument 5* = the incoming `a0`, and it needs no stack
slot — which is why the call stayed a frameless tail call. The format string
`"VIFUNPACK :%08x %08x (%p:%d)\n"` has four conversions, so the call is
five-ary: `(fmt, p[0], p[1], p, a0)`. Adding the trailing `a0` argument took
it to byte-identical in one step. The three separate `lw 0x24` reloads come
free from the `*(int *)` sub-object idiom (same alias set as the `int`
stores), exactly as in the enemy match.

## Mechanism 2 — `pac_makeMaterialTableLine`: alias-set-driven DSE, then base form

Two successive corrections:

1. Spelling the cursor write-back as `*(int **)(ctx+0x2C) = p` (an `int *`
   store) put it in a different alias set from the `*p = 0` data stores, so
   the intervening data stores did not block dead-store elimination and gcc
   deleted **three of the four** cursor stores, leaving only the last. Writing
   the cursor as `*(int *)(ctx+0x2C) = (int)p` — same `int` alias set as the
   data stores — keeps all four. Same lever family as the enemy `int`-typed
   load; here it defeats DSE rather than CSE.
2. With all eight stores present the residual was the address form: ROM keeps
   one base register and derives cursor values with `addiu base,N`
   (`sw v0/a0/a2/a1,44(v1)` from `v0=q+1`), while a fully post-incremented
   `*p++` chain re-bases every step. ROM's base is `q+1`, not `q`: the source
   post-increments **once**, for the header word, then indexes off the
   resulting pointer. `*p++ = 0x17000000; cur = p; p[0]=0; cur = p+1; p[1]=0;
   cur = p+2; p[2]=0; cur = p+3; f(p+3);` reproduces both the single rebase
   and the ROM's `daddu a0,a1,zero` (the final `p+3` is needed twice: as the
   cursor value and as the call argument).

## Landed source (`src/Packet.c`)

```c
void pac_makeMaterialTable(int a0)
{
    char *ctx = D_00672FD0;
    *(int *)(*(int *)(ctx + 0x24)) = 0;
    *(int *)(*(int *)(ctx + 0x24) + 4) = (a0 << 16) | 0x6C008000;
    debug_assertMessage(D_005551A0, *(int *)(*(int *)(ctx + 0x24)),
                        *(int *)(*(int *)(ctx + 0x24) + 4),
                        *(int *)(ctx + 0x24), a0);
}

void pac_makeMaterialTableLine(void)
{
    char *ctx = D_00672FD0;
    int *p = (int *)*(int *)(ctx + 0x2C);
    *p++ = 0x17000000;
    *(int *)(ctx + 0x2C) = (int)p;
    p[0] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 1);
    p[1] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 2);
    p[2] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 3);
    debug_assertMessage(p + 3);
}
```

No crutches: no pins, no barriers, no `volatile`, no inline asm, no flags.

## Probes measured (project CFLAGS + period ee-as 2.9-991111)

| # | func | source shape | result |
|---|------|--------------|--------|
| 1 | Table | `*(int *)` cursor loads, plain `int` stores, 4-ary call | 17/18 insns, **delay slot already filled** with `lw a2,4(v0)`; only `daddu $8,$4,$0` missing |
| 2 | Table | same + 5th argument `a0` | **byte-identical** |
| 3 | Line | `int *`-typed cursor store (`*(int **)... = p`) | DSE deletes 3 of 4 cursor stores; 14 insns |
| 4 | Line | `int`-typed cursor store (`= (int)p`), `*p++` chain | all 8 stores, 17 insns; addresses chain `addiu a0,a0,4` instead of ROM's base+offset |
| 5 | Line | all indices off the original `q` (`q[0..3]`, cursors `q+1..q+4`) | base stays `q`, offsets 4/8/12/16; 21 insns, worse |
| 6 | Line | one `*p++` for the header, then indices off the rebased `p` | **byte-identical** |

## Revert bookkeeping — REVERSED

- `const char D_005551A0[0x20] = "VIFUNPACK :%08x %08x (%p:%d)\n";` restored to
  its C definition site, immediately after `D_00555190` and before
  `pac_setMaterialPacket`. The splat stub `.s` still carries the migrated
  `dlabel D_005551A0`, but that file is no longer `INCLUDE_ASM`'d, so there is
  no duplicate.
- `D_005551C0` needed no move: it already sat after the two (now removed)
  `INCLUDE_ASM` lines, which is still after `D_005551A0`, so `.o` section
  order continues to equal VMA order under the `(.rodata*)` glob.
- No `config/`, `tools/` or `lib/` change of any kind;
  `config/use_modern_as.txt` still empty.
- `tools/check_no_rom.sh: OK (726 files scanned)`.

## Status

Full `.venv/bin/ninja` gate: `verify_elf: OK (build/ico.rom
sha1=fbf50c75cd5911273511c4f9af90503ff8423582)`. The delay-slot queue now has
one open row left: #3 `func_00244958` (see HANDOFF_vendor_2418A0.md).
