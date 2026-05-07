# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-07 06:22:42 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4632 total in `asm/cod/*.s`, 0 parked, 4632 considered
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

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00209AB0` | 0x10 | 4 | 0 |  | `addiu daddu j addiu` | asm/cod/105B4C.s:4877 |

<a id="leaf-5-0x14"></a>
## 5-insn / 0x14 leaf, no jal, no VU (store-and-forward)

_18 total in this bucket; showing top 18._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00137EF0` | 0x14 | 5 | 0 |  | `ld andi andi jr` | asm/cod/037EF0.s:13 |
| `func_001C8A00` | 0x14 | 5 | 0 |  | `addiu mult addu jr` | asm/cod/0C3984.s:5903 |
| `func_0025C668` | 0x14 | 5 | 0 |  | `daddu addiu addiu j` | asm/cod/158CEC.s:4461 |
| `func_0025CCB0` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:4961 |
| `func_0025CCC8` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:4972 |
| `func_0025CCF8` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/15CCF8.s:13 |
| `func_0025CD10` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/15CCF8.s:25 |
| `func_00194EA8` | 0x14 | 5 | 0 |  | `lui addiu swc1 jr` | asm/cod/0945B4.s:707 |
| `func_0019C010` | 0x14 | 5 | 0 |  | `addiu lui sw j` | asm/cod/09BB5C.s:350 |
| `func_0025E100` | 0x14 | 5 | 0 |  | `daddu daddu addiu j` | asm/cod/15CE90.s:1525 |
| `func_0013DD88` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/03D944.s:364 |
| `func_0016BCF0` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/06A69C.s:1776 |
| `func_00197FE8` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/097338.s:997 |
| `func_0025DCF0` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/15CE90.s:1159 |
| `func_0025DD08` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/15CE90.s:1171 |
| `func_0025E020` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/15CE90.s:1437 |
| `func_0025E038` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/15CE90.s:1449 |
| `func_001869F8` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/082C14.s:4380 |

<a id="leaf-6-0x18"></a>
## 6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101A88` | 0x18 | 6 | 0 |  | `mfc0 lui and ei` | asm/cod/000C90.s:1209 |
| `func_001C8B48` | 0x18 | 6 | 0 |  | `lwc1 nop nop div.s` | asm/cod/0C3984.s:6012 |

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_17 total in this bucket; showing top 17._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0010D408` | 0x1C | 7 | 0 |  | `lw lui addiu sll` | asm/cod/00D198.s:205 |
| `func_0010D428` | 0x1C | 7 | 0 |  | `lw lui addiu daddu` | asm/cod/00D198.s:219 |
| `func_0011BF40` | 0x1C | 7 | 0 |  | `lw lw lb daddu` | asm/cod/018AB4.s:4024 |
| `func_0015F208` | 0x1C | 7 | 0 |  | `lw lw lwu dsll32` | asm/cod/05EF50.s:233 |
| `func_001AD748` | 0x1C | 7 | 0 |  | `nop nop nop nop` | asm/cod/0AD748.s:13 |
| `func_001BB7E0` | 0x1C | 7 | 0 |  | `lw lwu dsll32 dsra32` | asm/cod/0BA5E0.s:1463 |
| `func_001F3368` | 0x1C | 7 | 0 |  | `lw daddu lw addiu` | asm/cod/0F2250.s:1287 |
| `func_00168A40` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:18 |
| `func_00168A60` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:33 |
| `func_0012FE78` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/02FE78.s:13 |
| `func_00176AE8` | 0x1C | 7 | 0 |  | `daddu addiu lui daddu` | asm/cod/07614C.s:732 |
| `func_001E8D50` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0E8D4C.s:18 |
| `func_0024B8A8` | 0x1C | 7 | 0 |  | `lui sll addiu addu` | asm/cod/14B8A8.s:13 |
| `func_00258CF0` | 0x1C | 7 | 0 |  | `lui sll addiu sll` | asm/cod/158CEC.s:18 |
| `func_002608E0` | 0x1C | 7 | 0 |  | `mfc1 lui ori and` | asm/cod/15CE90.s:4685 |
| `func_00175F60` | 0x1C | 7 | 0 |  | `lwc1 lwc1 sub.s .word` | asm/cod/075CB0.s:233 |
| `func_0018CF60` | 0x1C | 7 | 0 |  | `lw bnez lui jr` | asm/cod/08CF60.s:13 |

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_6 total in this bucket; showing top 6._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00154CC8` | 0x20 | 8 | 1 |  | `addiu sd sw nop` | asm/cod/054CC8.s:13 |
| `func_00176198` | 0x20 | 8 | 1 |  | `addiu sd sw jal` | asm/cod/07614C.s:41 |
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F2250.s:109 |
| `func_0024BFAC` | 0x20 | 8 | 1 |  | `sd jal daddu sync` | asm/cod/14BBC0.s:353 |
| `func_001683A8` | 0x20 | 8 | 1 |  | `addiu lw sd jalr` | asm/cod/0654E0.s:3587 |
| `func_0024A980` | 0x20 | 8 | 1 |  | `addiu daddu sd jal` | asm/cod/14A754.s:183 |

<a id="wrap-9-0x24"></a>
## 9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)

_15 total in this bucket; showing top 15._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101C08` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/001B64.s:73 |
| `func_00101C30` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/001B64.s:88 |
| `func_00101C58` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/001B64.s:103 |
| `func_0012BBE8` | 0x24 | 9 | 1 |  | `addiu addiu sd addiu` | asm/cod/028710.s:4169 |
| `func_0015F4B8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05F244.s:224 |
| `func_0015F4F0` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05F4F0.s:13 |
| `func_001684E8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0684E8.s:13 |
| `func_00168510` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0684E8.s:29 |
| `func_001685B8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0685B8.s:13 |
| `func_00180580` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/07EC94.s:1954 |
| `func_00245DB8` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/145674.s:612 |
| `func_0024FBD0` | 0x24 | 9 | 1 |  | `addiu sd jal daddu` | asm/cod/14BBC0.s:5279 |
| `func_00251D48` | 0x24 | 9 | 1 |  | `addiu addiu sd daddu` | asm/cod/151C28.s:125 |
| `func_00260610` | 0x24 | 9 | 1 |  | `addiu sd ld jal` | asm/cod/15CE90.s:4471 |
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

_4572 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

