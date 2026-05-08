# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-08 08:34:16 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4356 total in `asm/cod/*.s`, 63 parked, 4293 considered
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
- [0x28-0x30, exactly 1 jal, no VU (wrapper w/ buffer or extra spill)](#wrap-1jal-0x28-0x30)
- [0x34-0x40, exactly 1 jal, no VU (wrapper w/ stack buffer / arg pack)](#wrap-1jal-0x34-0x40)
- [Any size, has sw $a0,0($sp); lw $a0,0($sp), no VU (volatile unsigned int a0 + volatile int local)](#wrap-spill-reload)
- [0x18-0x24, exactly 2 jal, no VU (compact 2-call wrapper)](#wrap-2jal-0x18-0x24)
- [0x28-0x40, exactly 2 jal, no VU (2-call wrapper, mid-size)](#wrap-2jal-0x28-0x40)
- [0x28-0x40, exactly 3 jal, no VU (3-call wrapper, often w/ tail call)](#wrap-3jal-mid)
- [1 jal + gp_rel %gp_rel(D), no VU (D[0] + arg passthrough)](#wrap-gp-1jal)
- [Leaf (no jal) with branch, no VU (cond-return / deref+if)](#cond-deref-leaf)
- [4-insn / 0x10 leaf, no jal, has VU (VU0 macro)](#vu-leaf-4-0x10)
- [5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)](#vu-leaf-56-0x14-0x18)

<a id="leaf-4-0x10"></a>
## 4-insn / 0x10 leaf, no jal, no VU (bulk getter/setter)

_0 total in this bucket; showing top 0._

(empty)

<a id="leaf-5-0x14"></a>
## 5-insn / 0x14 leaf, no jal, no VU (store-and-forward)

_0 total in this bucket; showing top 0._

(empty)

<a id="leaf-6-0x18"></a>
## 6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101A88` | 0x18 | 6 | 0 |  | `mfc0 lui and ei` | asm/cod/0019E0.s:73 |

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F231C.s:43 |
| `func_0024BFAC` | 0x20 | 8 | 1 |  | `sd jal daddu sync` | asm/cod/14BDCC.s:173 |

<a id="wrap-9-0x24"></a>
## 9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-1jal-0x28-0x30"></a>
## 0x28-0x30, exactly 1 jal, no VU (wrapper w/ buffer or extra spill)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-1jal-0x34-0x40"></a>
## 0x34-0x40, exactly 1 jal, no VU (wrapper w/ stack buffer / arg pack)

_4 total in this bucket; showing top 4._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0019F530` | 0x38 | 14 | 1 |  | `addiu sd sd jal` | asm/cod/09F4E8.s:37 |
| `func_00264298` | 0x3C | 15 | 1 |  | `addiu sd sd daddu` | asm/cod/164094.s:190 |
| `func_00135BB8` | 0x40 | 16 | 1 |  | `addiu sd daddu beqz` | asm/cod/033510.s:3053 |
| `func_0023EFF8` | 0x38 | 14 | 1 |  | `addiu lw beqz sd` | asm/cod/13EFB8.s:36 |

<a id="wrap-spill-reload"></a>
## Any size, has sw $a0,0($sp); lw $a0,0($sp), no VU (volatile unsigned int a0 + volatile int local)

_4 total in this bucket; showing top 4._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00165918` | 0x234 | 141 | 18 |  | `addiu sw sd swc1` | asm/cod/0654E0.s:337 |
| `func_00175350` | 0x2EC | 187 | 32 |  | `addiu sd sd addiu` | asm/cod/06BD04.s:11293 |
| `func_0015EAB0` | 0x304 | 193 | 24 |  | `addiu sw lw sd` | asm/cod/05EAAC.s:18 |
| `func_00156840` | 0xAAC | 683 | 80 |  | `lui addiu lw addiu` | asm/cod/056488.s:299 |

<a id="wrap-2jal-0x18-0x24"></a>
## 0x18-0x24, exactly 2 jal, no VU (compact 2-call wrapper)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-2jal-0x28-0x40"></a>
## 0x28-0x40, exactly 2 jal, no VU (2-call wrapper, mid-size)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0015F298` | 0x3C | 15 | 2 |  | `addiu lui mtc1 sd` | asm/cod/05F244.s:47 |

<a id="wrap-3jal-mid"></a>
## 0x28-0x40, exactly 3 jal, no VU (3-call wrapper, often w/ tail call)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-gp-1jal"></a>
## 1 jal + gp_rel %gp_rel(D), no VU (D[0] + arg passthrough)

_101 total in this bucket; showing top 50._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001B6FD8` | 0x64 | 25 | 1 |  | `addiu lw sd addiu` | asm/cod/0B59D0.s:1747 |
| `func_001A1030` | 0x80 | 32 | 1 |  | `lui ori addiu addiu` | asm/cod/0A1030.s:13 |
| `func_001A10B0` | 0x88 | 34 | 1 |  | `lui ori addiu addiu` | asm/cod/0A1030.s:53 |
| `func_001B7190` | 0x88 | 34 | 1 |  | `addiu lui mult addiu` | asm/cod/0B7048.s:123 |
| `func_001B7100` | 0x8C | 35 | 1 |  | `addiu lui mult addiu` | asm/cod/0B7048.s:75 |
| `func_00111EF8` | 0xAC | 43 | 1 |  | `addiu addiu sd addiu` | asm/cod/011948.s:415 |
| `func_001E0C98` | 0xB4 | 45 | 1 |  | `addiu lw sd lw` | asm/cod/0E0C34.s:47 |
| `func_001FC2E0` | 0xD0 | 52 | 1 |  | `addiu sd sd daddu` | asm/cod/0FC2DC.s:18 |
| `func_0013A820` | 0x48 | 18 | 1 |  | `addiu addiu bne sd` | asm/cod/03A248.s:485 |
| `func_0017E4A0` | 0x50 | 20 | 1 |  | `addiu lw sd andi` | asm/cod/07E354.s:119 |
| `func_001EBA40` | 0xA8 | 42 | 1 |  | `lui addiu lw sd` | asm/cod/0EBA3C.s:18 |
| `func_0018DDF0` | 0x58 | 22 | 1 |  | `addiu lw sd sd` | asm/cod/08CFF8.s:1067 |
| `func_0015FB60` | 0x78 | 30 | 1 |  | `addiu lw sd sd` | asm/cod/05F6EC.s:370 |
| `func_0015FBD8` | 0x78 | 30 | 1 |  | `addiu lw sd sd` | asm/cod/05F6EC.s:409 |
| `func_001FBAA8` | 0x98 | 38 | 1 |  | `lw addiu addiu lui` | asm/cod/0FBAA8.s:13 |
| `func_001A9F28` | 0xB8 | 46 | 1 |  | `lw addiu addiu lui` | asm/cod/0A9F28.s:13 |
| `func_001A9FE0` | 0xB8 | 46 | 1 |  | `lw addiu addiu lui` | asm/cod/0A9F28.s:67 |
| `func_001AC348` | 0xF0 | 60 | 1 |  | `addiu lui sd addiu` | asm/cod/0ABF7C.s:313 |
| `func_00169E58` | 0x128 | 74 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1401 |
| `func_00129E28` | 0x130 | 76 | 1 |  | `addiu lw sd sd` | asm/cod/029AA8.s:301 |
| `func_001547B8` | 0x134 | 77 | 1 |  | `addiu lui sd lui` | asm/cod/0547B8.s:13 |
| `func_001692F0` | 0x150 | 84 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:497 |
| `func_001101E0` | 0x200 | 128 | 1 |  | `addiu addiu sd addiu` | asm/cod/00F5D4.s:842 |
| `func_001FAAB0` | 0x3E4 | 249 | 1 |  | `addiu sd sd daddu` | asm/cod/0FAAB0.s:13 |
| `func_0013E4D0` | 0x78 | 30 | 1 |  | `addiu addiu sd lui` | asm/cod/03E220.s:243 |
| `func_0013F700` | 0x78 | 30 | 1 |  | `addiu addiu sd lui` | asm/cod/03F6FC.s:18 |
| `func_00205498` | 0x7C | 31 | 1 |  | `addiu addiu mult lui` | asm/cod/104E98.s:519 |
| `func_00240BD0` | 0x80 | 32 | 1 |  | `addiu lw sd sd` | asm/cod/140B88.s:43 |
| `func_0012FF58` | 0x8C | 35 | 1 |  | `addiu sd sd jal` | asm/cod/02FE94.s:79 |
| `func_0012FD70` | 0x98 | 38 | 1 |  | `addiu sd sd daddu` | asm/cod/02FD6C.s:18 |
| `func_00130128` | 0xAC | 43 | 1 |  | `addiu sd jal nop` | asm/cod/02FFF0.s:105 |
| `func_001E69D8` | 0xBC | 47 | 1 |  | `addiu addiu sd lui` | asm/cod/0E6968.s:47 |
| `func_00140D58` | 0xF0 | 60 | 1 |  | `addiu lui sd lui` | asm/cod/040BDC.s:138 |
| `func_00168DA8` | 0x128 | 74 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:77 |
| `func_00169AA8` | 0x128 | 74 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1105 |
| `func_00169440` | 0x13C | 79 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:601 |
| `func_00169580` | 0x13C | 79 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:699 |
| `func_00169968` | 0x13C | 79 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1007 |
| `func_001696C0` | 0x140 | 80 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:799 |
| `func_00169D18` | 0x140 | 80 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1301 |
| `func_00169BD0` | 0x148 | 82 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1197 |
| `func_00168ED0` | 0x150 | 84 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:169 |
| `func_00169800` | 0x164 | 89 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:897 |
| `func_0013DDA0` | 0x58 | 22 | 1 |  | `addiu lui lui sd` | asm/cod/03DD9C.s:18 |
| `func_0018DD80` | 0x70 | 28 | 1 |  | `addiu lw sd sd` | asm/cod/08CFF8.s:1031 |
| `func_00140CE0` | 0x74 | 29 | 1 |  | `addiu addiu sd daddu` | asm/cod/040BDC.s:97 |
| `func_00191C80` | 0x84 | 33 | 1 |  | `addiu lw sd blez` | asm/cod/0906B8.s:1841 |
| `func_0012DF98` | 0x13C | 79 | 1 |  | `addiu lui sd lui` | asm/cod/02BC0C.s:2747 |
| `func_00169190` | 0x15C | 87 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:387 |
| `func_00169020` | 0x170 | 92 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:273 |

<a id="cond-deref-leaf"></a>
## Leaf (no jal) with branch, no VU (cond-return / deref+if)

_3 total in this bucket; showing top 3._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00244958` | 0x28 | 10 | 0 |  | `lui lui ori ori` | asm/cod/144748.s:169 |
| `func_00165B50` | 0x30 | 12 | 0 |  | `lw lw beqz sw` | asm/cod/0654E0.s:499 |
| `func_001AE188` | 0x30 | 12 | 0 |  | `lui addiu addiu lhu` | asm/cod/0ADBBC.s:475 |

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

_4176 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

