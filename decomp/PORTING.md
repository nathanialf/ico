# Porting aug6-matched C into retail — runbook

The aug6 prototype branch (`main` in the AUG6_ROOT checkout, default
`/primary/dev/ico`) accumulates byte-matched clean-room C continuously. A
large share of those functions survive into retail SLUS-20218 with the *same
instruction stream* — only the relocation literals moved, because the two
links lay memory out differently. `tools/port_from_aug6.py` harvests that
overlap mechanically.

**Run it after every push to aug6 `main`.** Every new aug6 match is a
potential retail match at near-zero cost, and the driver is idempotent:
functions the retail tree has already matched are skipped automatically.

## The one-command cadence

```sh
cd /primary/dev/ico-retail
.venv/bin/python tools/port_from_aug6.py scan --force     # refresh candidates
.venv/bin/python tools/port_from_aug6.py port-all --apply # port everything new
./tools/build.sh setup && .venv/bin/ninja                 # -> verify_elf: OK
./tools/check_no_rom.sh
.venv/bin/python tools/port_from_aug6.py ledger           # compact + account
git commit -m "retail-v2 phase 4 (wave W, batch N): port <TUs>"
```

`port-all` runs ~200 TUs in a few minutes. For a large harvest, split it with
`--limit` / `--skip` and gate each chunk with `ninja` separately — a batch
SHA failure then needs a much smaller bisect.

## How it works

1. **Correlate.** `scan` joins retail `type:func` symbols against aug6 matched
   glabels (`asm/aug6/matchings/**/*.s`) **by name**, lifts the retail
   instruction words straight out of `baserom/baseelf.rom`, and diffs the two
   streams with the classifier from `decomp/retail_port/near_miss_scan.py`.
   A `.s` under `matchings/` whose function is no longer defined in the aug6
   C is a stale splat leftover and is dropped.

2. **Bind symbols.** The aug6 `.s` carries the relocation annotations
   (`%hi(sym)`, `%lo(sym)`, `%gp_rel(sym)`, `jal sym`). Walking it in lockstep
   with the retail words gives, for each aug6 symbol, the retail *address*
   occupying the same reloc slot — hence the retail symbol name. `%lo` slots
   are resolved against the nearest preceding retail `lui`; `%gp_rel` against
   `_gp` from `config/ico.us.ld`. Wave-3 streams are not index-aligned, so a
   `difflib` opcode-key alignment supplies the index map instead of the
   identity. Any slot that cannot be bound unambiguously aborts the function.

3. **Splice.** The aug6 body is lifted by brace match, every aug6 identifier
   rebound, and externs synthesized **from the aug6 declarations** (the aug6
   typing is part of the matching shape) directly above the body — which is
   where the aug6 dev put them too. Headers, TU-local typedefs and carried
   inlined helpers go into the file's leading header block.

4. **Gate.** `tools/quick_diff.sh <tu-stem> <func>` must come back clean, and
   the TU object must not have grown any allocatable non-`.text` section.
   Anything else reverts to `INCLUDE_ASM` and is ledgered. **No function is
   ever hand-tuned in this phase** — that is what makes the whole thing safe
   to run unattended.

## Waves

| wave | population | meaning |
|---|---|---|
| 1 | retail symbol twin-anchored (named, untagged) **and** reloc-normalized identical to the aug6 twin | highest confidence |
| 2 | `provisional-ordinal` and raw streams byte-identical | the `identical` near-miss bucket |
| 3 | `provisional-ordinal` and `trivial` (<=4 differing insns, or every diff immediate-only) | the differing fields are usually exactly the reloc literals the driver rebinds |

Wave 0 (`divergent` / `moderate`) is out of scope: the retail source genuinely
differs and needs a normal matching grind.

## Subcommands

| command | does |
|---|---|
| `scan [--force]` | rebuild `.port_cache/candidates.json` |
| `status [--waves N,…]` | ported / pending / jtbl-skip counts per wave |
| `tus [--waves N,…]` | candidate count per retail TU |
| `plan <tu>` | what is still portable in one TU |
| `port <tu> [--apply] [--waves …]` | port one TU (dry-run without `--apply`) |
| `port-all [--apply] [--waves …] [--limit N] [--skip N]` | port every TU |
| `ledger` | compact `decomp/port_ledger.md` + regenerate the accounting table |
| `revert-func <tu> <func> [--reason …]` | post-hoc revert after a batch SHA bisect |

Environment: `PORT_AUG6_ROOT` (aug6 checkout, default `/primary/dev/ico`),
`PORT_DEBUG_DUMP=<dir>` (write every spliced candidate TU there for
inspection), `OBJDUMP`.

## Gates, and why each one exists

- **`quick_diff.sh` per function.** Tolerates three coalesced-TU disassembly
  artifacts, all cosmetic: a same-function relative branch whose absolute
  address differs between the isolated baseline object and the multi-function
  built one; a call unresolved on *both* sides; and — the one that only
  appears once bodies are spliced — a call the built object resolves in-TU
  while the isolated baseline leaves at `0`. The third is granted **only**
  when the resolved side names a symbol this function's own reloc walk bound,
  so a call retargeted to the wrong function is still caught here.
- **No data growth.** Retail carves no data. A string literal or an
  out-of-line float constant in a ported body appends new `.sdata`/`.rodata`/
  `.lit4` bytes, shifts the whole data layout, and breaks every `%hi/%lo` and
  `$gp`-relative reference in the game — while passing the per-function
  instruction diff cleanly. The driver compiles the TU once before splicing
  and rejects any body that grows an allocatable non-`.text` section
  (`emits-data`; deferred to a Phase-5 rodata carve).
- **Full `ninja` SHA-1.** The real safety net. On mismatch, bisect with
  `tools/first_diff.py` or by halving the modified-file set, then
  `revert-func` the offender and continue.
- **`check_no_rom.sh`.** Every commit. Note it also caps tracked files at
  256 KiB — that is why Phase 4 accounting lives in `decomp/port_ledger.md`
  rather than being appended to `decomp/transplant_ledger.md`.

## Revert-reason classes

`unresolved-symbol` (a reloc slot the walk could not bind) · `emits-data` ·
`callee-sig-conflict` / `arity` (a sibling retail body declares the callee
with a placeholder signature the aug6 body contradicts, and the alias trick
below did not resolve it) · `undeclared` / `parse` (declaration context) ·
`missing-body` · `codegen` (compiles, wrong bytes — a genuine
retail-vs-prototype source difference) · `jtbl` (skipped, Phase-5 queue).

## The alias trick

When the retail TU already has a symbol in scope with a type the aug6 body
contradicts — a Phase-3 body's placeholder signature, or a TU-local
`struct GObj` whose members were never mined — redeclaring is a hard error and
inheriting the wrong type is a *silent* miss (implicit `int` return where the
ROM has an `f0` float; a 4-parameter prototype where the aug6 call passes 2).
The driver binds a fresh identifier to the same linker symbol using the dev
tree's own `__asm__("REALNAME")` idiom, so the aug6 typing governs codegen and
the call still reaches the same address. aug6 TU-local struct tags that
collide with retail's shared headers are renamed (`GObj` -> `GObj__p4`):
identical layout, identical codegen, no clash. Alias renames deliberately skip
string literals — an inline-asm body spelling `%hi(D_X)` is assembler text and
the gcc asm-label indirection does not apply to it.

## Related

- `decomp/port_ledger.md` — per-function Phase 4 accounting.
- `decomp/transplant_ledger.md` — Phase 3 (old-`retail`-branch transplant).
- `decomp/retail_port/` (gitignored) — `correlate.py`, `near_miss_scan.py`,
  `portmap.py`: the analysis tools this driver was built from. `portmap.py`
  runs the same reloc-slot walk in the *opposite* direction (retail C onto an
  aug6 twin).
