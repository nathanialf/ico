# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-13 08:36:20 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4437 total in `asm/cod/*.s`, 225 parked, 4212 considered
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
- [0x40-0x60, exactly 1 jal, no VU (mid-size wrapper)](#wrap-1jal-0x40-0x60)
- [0x40-0x60, exactly 2 jal, no VU (2-call mid-size wrapper)](#wrap-2jal-0x40-0x60)
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

_0 total in this bucket; showing top 0._

(empty)

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001F08B8` | 0x1C | 7 | 0 |  | `lw ld sw ld` | asm/cod/0F08B8.s:13 |

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F236C.s:18 |
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

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00264298` | 0x3C | 15 | 1 |  | `addiu sd sd daddu` | asm/cod/164094.s:190 |

<a id="wrap-spill-reload"></a>
## Any size, has sw $a0,0($sp); lw $a0,0($sp), no VU (volatile unsigned int a0 + volatile int local)

_5 total in this bucket; showing top 5._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00165918` | 0x234 | 141 | 18 |  | `addiu sw sd swc1` | asm/cod/065540.s:303 |
| `func_00175350` | 0x2EC | 187 | 32 |  | `addiu sd sd addiu` | asm/cod/07534C.s:18 |
| `func_0015EAB0` | 0x304 | 193 | 24 |  | `addiu sw lw sd` | asm/cod/05EAAC.s:18 |
| `func_00156840` | 0xAAC | 683 | 80 |  | `lui addiu lw addiu` | asm/cod/056488.s:299 |
| `func_00156840` | 0xAAC | 683 | 80 |  | `lui addiu lw addiu` | asm/cod/0564CC.s:273 |

<a id="wrap-2jal-0x18-0x24"></a>
## 0x18-0x24, exactly 2 jal, no VU (compact 2-call wrapper)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-2jal-0x28-0x40"></a>
## 0x28-0x40, exactly 2 jal, no VU (2-call wrapper, mid-size)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-3jal-mid"></a>
## 0x28-0x40, exactly 3 jal, no VU (3-call wrapper, often w/ tail call)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-gp-1jal"></a>
## 1 jal + gp_rel %gp_rel(D), no VU (D[0] + arg passthrough)

_85 total in this bucket; showing top 50._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_001B6FD8` | 0x64 | 25 | 1 |  | `addiu lw sd addiu` | asm/cod/0B59D0.s:1747 |
| `func_001A1030` | 0x80 | 32 | 1 |  | `lui ori addiu addiu` | asm/cod/0A1030.s:13 |
| `func_001A10B0` | 0x88 | 34 | 1 |  | `lui ori addiu addiu` | asm/cod/0A1030.s:53 |
| `func_001A10B0` | 0x88 | 34 | 1 |  | `lui ori addiu addiu` | asm/cod/0A10B0.s:13 |
| `func_00111EF8` | 0xAC | 43 | 1 |  | `addiu addiu sd addiu` | asm/cod/011948.s:415 |
| `func_001E0C98` | 0xB4 | 45 | 1 |  | `addiu lw sd lw` | asm/cod/0E0C34.s:47 |
| `func_001FC2E0` | 0xD0 | 52 | 1 |  | `addiu sd sd daddu` | asm/cod/0FC2DC.s:18 |
| `func_001AC348` | 0xF0 | 60 | 1 |  | `addiu lui sd addiu` | asm/cod/0AC348.s:13 |
| `func_00169E58` | 0x128 | 74 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:1401 |
| `func_00129E28` | 0x130 | 76 | 1 |  | `addiu lw sd sd` | asm/cod/029AA8.s:301 |
| `func_001547B8` | 0x134 | 77 | 1 |  | `addiu lui sd lui` | asm/cod/0547B8.s:13 |
| `func_001692F0` | 0x150 | 84 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:497 |
| `func_001101E0` | 0x200 | 128 | 1 |  | `addiu addiu sd addiu` | asm/cod/00F5D4.s:842 |
| `func_001FAAB0` | 0x3E4 | 249 | 1 |  | `addiu sd sd daddu` | asm/cod/0FAAB0.s:13 |
| `func_00205498` | 0x7C | 31 | 1 |  | `addiu addiu mult lui` | asm/cod/10507C.s:346 |
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
| `func_0018DD80` | 0x70 | 28 | 1 |  | `addiu lw sd sd` | asm/cod/08CFF8.s:1031 |
| `func_00140CE0` | 0x74 | 29 | 1 |  | `addiu addiu sd daddu` | asm/cod/040BDC.s:97 |
| `func_00191C80` | 0x84 | 33 | 1 |  | `addiu lw sd blez` | asm/cod/0918EC.s:326 |
| `func_0012DF98` | 0x13C | 79 | 1 |  | `addiu lui sd lui` | asm/cod/02BC0C.s:2747 |
| `func_00169190` | 0x15C | 87 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:387 |
| `func_00169020` | 0x170 | 92 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:273 |
| `func_00148278` | 0xC4 | 49 | 1 |  | `addiu lw sd beqz` | asm/cod/045648.s:3323 |
| `func_001BA928` | 0x88 | 34 | 1 |  | `addiu daddu sd sd` | asm/cod/0BA880.s:61 |
| `func_00204160` | 0x9C | 39 | 1 |  | `addiu lw sd sd` | asm/cod/103F48.s:191 |
| `func_0017A410` | 0xAC | 43 | 1 |  | `addiu addiu mult lui` | asm/cod/07905C.s:1530 |
| `func_0017A4C0` | 0xB4 | 45 | 1 |  | `lw addiu addiu lui` | asm/cod/07905C.s:1587 |
| `func_0018B180` | 0xC8 | 50 | 1 |  | `addiu daddu lui mtc1` | asm/cod/08B0A8.s:83 |
| `func_001122C8` | 0xF4 | 61 | 1 |  | `addiu daddu sd addiu` | asm/cod/011948.s:719 |
| `func_001122C8` | 0xF4 | 61 | 1 |  | `addiu daddu sd addiu` | asm/cod/012184.s:125 |
| `func_001AB058` | 0xF4 | 61 | 1 |  | `addiu lui sd lw` | asm/cod/0AAF28.s:109 |
| `func_00102680` | 0x10C | 67 | 1 |  | `lw addiu addiu addiu` | asm/cod/0024F8.s:137 |
| `func_001AFB98` | 0x12C | 75 | 1 |  | `addiu addiu mult lui` | asm/cod/0AFB98.s:13 |
| `func_00110580` | 0x210 | 132 | 1 |  | `addiu addiu sd addiu` | asm/cod/00F5D4.s:1094 |
| `func_001F4FE8` | 0x7C | 31 | 1 |  | `lw addiu sd addiu` | asm/cod/0F4DE8.s:181 |
| `func_0023CE38` | 0x8C | 35 | 1 |  | `addiu sd sd jal` | asm/cod/13CD1C.s:106 |

<a id="cond-deref-leaf"></a>
## Leaf (no jal) with branch, no VU (cond-return / deref+if)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-1jal-0x40-0x60"></a>
## 0x40-0x60, exactly 1 jal, no VU (mid-size wrapper)

_14 total in this bucket; showing top 14._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_002642D8` | 0x50 | 20 | 1 |  | `addiu lui sd sd` | asm/cod/164094.s:211 |
| `func_00268DA0` | 0x54 | 21 | 1 |  | `lui lui lw addiu` | asm/cod/1668B4.s:3069 |
| `func_0013C820` | 0x58 | 22 | 1 |  | `addiu sd daddu beqz` | asm/cod/03C5B4.s:206 |
| `func_00245410` | 0x60 | 24 | 1 |  | `addiu sd daddu sw` | asm/cod/145410.s:13 |
| `func_001019E0` | 0x60 | 24 | 1 |  | `addiu lui sd addiu` | asm/cod/0019E0.s:13 |
| `func_0024E710` | 0x50 | 20 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E578.s:153 |
| `func_0024E710` | 0x50 | 20 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E6A4.s:53 |
| `func_0024EF20` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E578.s:819 |
| `func_0024EF20` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E794.s:625 |
| `func_0010A1A0` | 0x5C | 23 | 1 |  | `addiu sd lw daddu` | asm/cod/00A19C.s:18 |
| `func_0024EEC0` | 0x5C | 23 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E578.s:787 |
| `func_0024EEC0` | 0x5C | 23 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E794.s:594 |
| `func_0024EF78` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E578.s:851 |
| `func_0024EF78` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14E794.s:656 |

<a id="wrap-2jal-0x40-0x60"></a>
## 0x40-0x60, exactly 2 jal, no VU (2-call mid-size wrapper)

_3 total in this bucket; showing top 3._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_002633B8` | 0x54 | 21 | 2 |  | `addiu sd daddu sd` | asm/cod/1633B4.s:18 |
| `func_00252590` | 0x58 | 22 | 2 |  | `lui daddu addiu lw` | asm/cod/15258C.s:18 |
| `func_0015E658` | 0x54 | 21 | 2 |  | `addiu sd sw nop` | asm/cod/05D488.s:1323 |

<a id="vu-leaf-4-0x10"></a>
## 4-insn / 0x10 leaf, no jal, has VU (VU0 macro)

_0 total in this bucket; showing top 0._

(empty)

<a id="vu-leaf-56-0x14-0x18"></a>
## 5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00245258` | 0x18 | 6 | 0 | Y | `lw addiu sq sw` | asm/cod/145254.s:18 |

<a id="uncategorized"></a>
## Uncategorized (not in any shape bucket above)

_4100 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

