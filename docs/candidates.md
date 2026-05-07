# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-07 16:01:36 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4439 total in `asm/cod/*.s`, 15 parked, 4424 considered
- Sort within each section: hard-pattern penalty asc, insn count asc, size asc, name asc.

Hard-pattern penalty up-weights known near-miss shapes:
split `la` macro (`lui %hi` ... `addiu %lo`), `daddu rX, $zero, $zero`,
and `mtc1`/`lwc1`/`swc1`/`cvt.*`/`mfc1` float-pair sequences.

## Sections

- [4-insn / 0x10 leaf, no jal, no VU (bulk getter/setter)](#leaf-4-0x10)
- [5-insn / 0x14 leaf, no jal, no VU (store-and-forward)](#leaf-5-0x14)
- [6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)](#leaf-6-0x18)
- [7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)](#leaf-7-0x1C)
- [8-insn / 0x20, exactly 1 jal, no VU (passthrough call)](#wrap-8-0x20)
- [9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)](#wrap-9-0x24)
- [4-insn / 0x10 leaf, no jal, has VU (VU0 macro)](#vu-leaf-4-0x10)
- [5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)](#vu-leaf-56-0x14-0x18)

<a id="leaf-4-0x10"></a>
## 4-insn / 0x10 leaf, no jal, no VU (bulk getter/setter)

_0 total in this bucket; showing top 0._

(empty)

<a id="leaf-5-0x14"></a>
## 5-insn / 0x14 leaf, no jal, no VU (store-and-forward)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00137EF0` | 0x14 | 5 | 0 |  | `ld andi andi jr` | asm/cod/037EF0.s:13 |

<a id="leaf-6-0x18"></a>
## 6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101A88` | 0x18 | 6 | 0 |  | `mfc0 lui and ei` | asm/cod/0011E4.s:752 |

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_3 total in this bucket; showing top 3._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0015F208` | 0x1C | 7 | 0 |  | `lw lw lwu dsll32` | asm/cod/05EF50.s:233 |
| `func_001AD748` | 0x1C | 7 | 0 |  | `nop nop nop nop` | asm/cod/0AD748.s:13 |
| `func_001BB7E0` | 0x1C | 7 | 0 |  | `lw lwu dsll32 dsra32` | asm/cod/0BB398.s:343 |

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F2250.s:109 |
| `func_0024BFAC` | 0x20 | 8 | 1 |  | `sd jal daddu sync` | asm/cod/14BBC0.s:353 |

<a id="wrap-9-0x24"></a>
## 9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0024FBD0` | 0x24 | 9 | 1 |  | `addiu sd jal daddu` | asm/cod/14BBC0.s:5279 |

<a id="vu-leaf-4-0x10"></a>
## 4-insn / 0x10 leaf, no jal, has VU (VU0 macro)

_0 total in this bucket; showing top 0._

(empty)

<a id="vu-leaf-56-0x14-0x18"></a>
## 5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00245258` | 0x18 | 6 | 0 | Y | `lw addiu sq sw` | asm/cod/1450C8.s:149 |

<a id="uncategorized"></a>
## Uncategorized (not in any shape bucket above)

_4415 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

