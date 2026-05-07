# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-07 08:09:00 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4491 total in `asm/cod/*.s`, 0 parked, 4491 considered
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

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101A88` | 0x18 | 6 | 0 |  | `mfc0 lui and ei` | asm/cod/0011E4.s:752 |
| `func_001C8B48` | 0x18 | 6 | 0 |  | `lwc1 nop nop div.s` | asm/cod/0C8A14.s:116 |

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_9 total in this bucket; showing top 9._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0015F208` | 0x1C | 7 | 0 |  | `lw lw lwu dsll32` | asm/cod/05EF50.s:233 |
| `func_001AD748` | 0x1C | 7 | 0 |  | `nop nop nop nop` | asm/cod/0AD748.s:13 |
| `func_001BB7E0` | 0x1C | 7 | 0 |  | `lw lwu dsll32 dsra32` | asm/cod/0BB398.s:343 |
| `func_00168A40` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:18 |
| `func_00168A60` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:33 |
| `func_001E8D50` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0E8D4C.s:18 |
| `func_00258CF0` | 0x1C | 7 | 0 |  | `lui sll addiu sll` | asm/cod/158CEC.s:18 |
| `func_002608E0` | 0x1C | 7 | 0 |  | `mfc1 lui ori and` | asm/cod/160634.s:215 |
| `func_0018CF60` | 0x1C | 7 | 0 |  | `lw bnez lui jr` | asm/cod/08CF60.s:13 |

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_4 total in this bucket; showing top 4._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00154CC8` | 0x20 | 8 | 1 |  | `addiu sd sw nop` | asm/cod/054CC8.s:13 |
| `func_00176198` | 0x20 | 8 | 1 |  | `addiu sd sw jal` | asm/cod/07614C.s:41 |
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F2250.s:109 |
| `func_0024BFAC` | 0x20 | 8 | 1 |  | `sd jal daddu sync` | asm/cod/14BBC0.s:353 |

<a id="wrap-9-0x24"></a>
## 9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)

_8 total in this bucket; showing top 8._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0012BBE8` | 0x24 | 9 | 1 |  | `addiu addiu sd addiu` | asm/cod/02AA80.s:1371 |
| `func_0015F4B8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05F244.s:224 |
| `func_0015F4F0` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05F4F0.s:13 |
| `func_00180580` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/07EC94.s:1954 |
| `func_00245DB8` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/145680.s:611 |
| `func_0024FBD0` | 0x24 | 9 | 1 |  | `addiu sd jal daddu` | asm/cod/14BBC0.s:5279 |
| `func_00251D48` | 0x24 | 9 | 1 |  | `addiu addiu sd daddu` | asm/cod/151C28.s:125 |
| `func_001F6E00` | 0x24 | 9 | 1 |  | `addiu lui sd addiu` | asm/cod/0F6DB8.s:37 |

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

_4466 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

