# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-08 18:58:18 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4294 total in `asm/cod/*.s`, 102 parked, 4192 considered
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

_2 total in this bucket; showing top 2._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00264298` | 0x3C | 15 | 1 |  | `addiu sd sd daddu` | asm/cod/164094.s:190 |
| `func_0023EFF8` | 0x38 | 14 | 1 |  | `addiu lw beqz sd` | asm/cod/13EFF4.s:19 |

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

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-3jal-mid"></a>
## 0x28-0x40, exactly 3 jal, no VU (3-call wrapper, often w/ tail call)

_0 total in this bucket; showing top 0._

(empty)

<a id="wrap-gp-1jal"></a>
## 1 jal + gp_rel %gp_rel(D), no VU (D[0] + arg passthrough)

_97 total in this bucket; showing top 50._

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
| `func_001EBA40` | 0xA8 | 42 | 1 |  | `lui addiu lw sd` | asm/cod/0EBA3C.s:18 |
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
| `func_0018DD80` | 0x70 | 28 | 1 |  | `addiu lw sd sd` | asm/cod/08CFF8.s:1031 |
| `func_00140CE0` | 0x74 | 29 | 1 |  | `addiu addiu sd daddu` | asm/cod/040BDC.s:97 |
| `func_00191C80` | 0x84 | 33 | 1 |  | `addiu lw sd blez` | asm/cod/0906B8.s:1841 |
| `func_0012DF98` | 0x13C | 79 | 1 |  | `addiu lui sd lui` | asm/cod/02BC0C.s:2747 |
| `func_00169190` | 0x15C | 87 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:387 |
| `func_00169020` | 0x170 | 92 | 1 |  | `addiu lw sd sd` | asm/cod/068CC8.s:273 |
| `func_001CBE20` | 0x58 | 22 | 1 |  | `addiu daddu sd lui` | asm/cod/0CBD88.s:59 |
| `func_00148278` | 0xC4 | 49 | 1 |  | `addiu lw sd beqz` | asm/cod/045648.s:3323 |
| `func_0023C090` | 0x58 | 22 | 1 |  | `addiu lwc1 sd sd` | asm/cod/13B518.s:893 |

<a id="cond-deref-leaf"></a>
## Leaf (no jal) with branch, no VU (cond-return / deref+if)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00165B50` | 0x30 | 12 | 0 |  | `lw lw beqz sw` | asm/cod/0654E0.s:499 |

<a id="wrap-1jal-0x40-0x60"></a>
## 0x40-0x60, exactly 1 jal, no VU (mid-size wrapper)

_51 total in this bucket; showing top 50._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0015F650` | 0x48 | 18 | 1 |  | `addiu addiu sw addiu` | asm/cod/05F578.s:85 |
| `func_0011FCD8` | 0x4C | 19 | 1 |  | `addiu addiu sd lh` | asm/cod/01EE84.s:1028 |
| `func_001F2320` | 0x4C | 19 | 1 |  | `addiu addiu sw sd` | asm/cod/0F231C.s:18 |
| `func_00247088` | 0x4C | 19 | 1 |  | `addiu addiu sd lui` | asm/cod/146BD4.s:383 |
| `func_00107DD8` | 0x50 | 20 | 1 |  | `addiu daddu sd sd` | asm/cod/006E34.s:1130 |
| `func_0023FDA0` | 0x50 | 20 | 1 |  | `addiu sd sd daddu` | asm/cod/13F95C.s:334 |
| `func_00240600` | 0x50 | 20 | 1 |  | `addiu sd sd daddu` | asm/cod/13F95C.s:961 |
| `func_002642D8` | 0x50 | 20 | 1 |  | `addiu lui sd sd` | asm/cod/164094.s:211 |
| `func_0013A7C8` | 0x54 | 21 | 1 |  | `addiu lui sd sd` | asm/cod/03A248.s:453 |
| `func_001E8A60` | 0x54 | 21 | 1 |  | `addiu lui sd sd` | asm/cod/0E6DA0.s:2089 |
| `func_00260BA0` | 0x54 | 21 | 1 |  | `addiu lui sd sd` | asm/cod/160900.s:237 |
| `func_00268DA0` | 0x54 | 21 | 1 |  | `lui lui lw addiu` | asm/cod/1668B4.s:3069 |
| `func_0013C820` | 0x58 | 22 | 1 |  | `addiu sd daddu beqz` | asm/cod/03C5B4.s:206 |
| `func_00176398` | 0x5C | 23 | 1 |  | `addiu addiu sd daddu` | asm/cod/0761B8.s:159 |
| `func_0026D128` | 0x5C | 23 | 1 |  | `addiu sd sd lui` | asm/cod/16CF2C.s:187 |
| `func_0013C538` | 0x60 | 24 | 1 |  | `addiu sd sd daddu` | asm/cod/03C538.s:13 |
| `func_0013CF80` | 0x60 | 24 | 1 |  | `addiu sd sd daddu` | asm/cod/03CF7C.s:18 |
| `func_001444A0` | 0x60 | 24 | 1 |  | `addiu lui sd sd` | asm/cod/044308.s:145 |
| `func_00245410` | 0x60 | 24 | 1 |  | `addiu sd daddu sw` | asm/cod/1453CC.s:41 |
| `func_0025AC18` | 0x48 | 18 | 1 |  | `andi sll sll sll` | asm/cod/158D0C.s:2396 |
| `func_0019B948` | 0x50 | 20 | 1 |  | `addiu addiu sd sd` | asm/cod/09B948.s:13 |
| `func_00251CF8` | 0x50 | 20 | 1 |  | `addiu daddu beqz sd` | asm/cod/151C68.s:73 |
| `func_001F41C8` | 0x60 | 24 | 1 |  | `addiu sd sd sd` | asm/cod/0F40D8.s:93 |
| `func_00193CE8` | 0x48 | 18 | 1 |  | `addiu daddu sd lui` | asm/cod/093A78.s:203 |
| `func_0015F248` | 0x4C | 19 | 1 |  | `addiu sd lw lw` | asm/cod/05F244.s:18 |
| `func_001BA7E8` | 0x4C | 19 | 1 |  | `addiu daddu sd sd` | asm/cod/0BA7E4.s:18 |
| `func_001F10A8` | 0x4C | 19 | 1 |  | `addiu lui mult addiu` | asm/cod/0F0F98.s:105 |
| `func_0025E198` | 0x50 | 20 | 1 |  | `addiu daddu sd sltiu` | asm/cod/15E198.s:13 |
| `func_0013D440` | 0x54 | 21 | 1 |  | `addiu daddu sd sd` | asm/cod/03D3F8.s:39 |
| `func_001AE1B8` | 0x54 | 21 | 1 |  | `addiu sd sd daddu` | asm/cod/0AE1B8.s:13 |
| `func_001F0878` | 0x5C | 23 | 1 |  | `addiu addiu sd lui` | asm/cod/0F0878.s:13 |
| `func_001019E0` | 0x60 | 24 | 1 |  | `addiu lui sd addiu` | asm/cod/0019E0.s:13 |
| `func_0024E4C8` | 0x60 | 24 | 1 |  | `addiu addiu mult mult1` | asm/cod/14DAB8.s:817 |
| `func_0025DEF0` | 0x60 | 24 | 1 |  | `addiu ori dsll sd` | asm/cod/15DDEC.s:102 |
| `func_0025DF50` | 0x60 | 24 | 1 |  | `addiu ori dsll sd` | asm/cod/15DDEC.s:133 |
| `func_001BA770` | 0x4C | 19 | 1 |  | `addiu lui sd addiu` | asm/cod/0BA6F0.s:59 |
| `func_0025C490` | 0x4C | 19 | 1 |  | `daddu daddu daddu addiu` | asm/cod/158D0C.s:4283 |
| `func_00138138` | 0x50 | 20 | 1 |  | `addiu nop addiu daddu` | asm/cod/038138.s:13 |
| `func_0024E528` | 0x50 | 20 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14DAB8.s:847 |
| `func_0024E710` | 0x50 | 20 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14DAB8.s:1015 |
| `func_00205AD8` | 0x54 | 21 | 1 |  | `addiu sd sd daddu` | asm/cod/105A94.s:41 |
| `func_0024EF20` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14DAB8.s:1681 |
| `func_0010A1A0` | 0x5C | 23 | 1 |  | `addiu sd lw daddu` | asm/cod/00A19C.s:18 |
| `func_0024EEC0` | 0x5C | 23 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14DAB8.s:1649 |
| `func_0024EF78` | 0x54 | 21 | 1 |  | `daddu addiu addiu mult1` | asm/cod/14DAB8.s:1713 |
| `func_0017B398` | 0x60 | 24 | 1 |  | `addiu sd sd daddu` | asm/cod/07B394.s:18 |
| `func_0013D8E0` | 0x44 | 17 | 1 |  | `addiu sltiu bnez sd` | asm/cod/03D8DC.s:18 |
| `func_0013D3F8` | 0x48 | 18 | 1 |  | `addiu daddu sd bnez` | asm/cod/03D3F8.s:13 |
| `func_001ADBC0` | 0x54 | 21 | 1 |  | `addiu lui sd addiu` | asm/cod/0ADBBC.s:18 |
| `func_0023C540` | 0x58 | 22 | 1 |  | `addiu sd jal nop` | asm/cod/13C1C0.s:305 |

<a id="wrap-2jal-0x40-0x60"></a>
## 0x40-0x60, exactly 2 jal, no VU (2-call mid-size wrapper)

_62 total in this bucket; showing top 50._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00258558` | 0x44 | 17 | 2 |  | `addiu addiu sd sd` | asm/cod/15846C.s:94 |
| `func_0010DDF8` | 0x48 | 18 | 2 |  | `addiu sd sd daddu` | asm/cod/00DDF4.s:18 |
| `func_00165FB8` | 0x48 | 18 | 2 |  | `addiu daddu sd addiu` | asm/cod/065FB4.s:18 |
| `func_0017CA58` | 0x48 | 18 | 2 |  | `addiu sd jal sd` | asm/cod/07CA54.s:18 |
| `func_001AC300` | 0x48 | 18 | 2 |  | `addiu sd jal addiu` | asm/cod/0ABF7C.s:290 |
| `func_00203A58` | 0x48 | 18 | 2 |  | `addiu sd bnez sd` | asm/cod/103A58.s:13 |
| `func_00237BD0` | 0x48 | 18 | 2 |  | `addiu lw beqz sd` | asm/cod/136C70.s:1231 |
| `func_001BA2E0` | 0x4C | 19 | 2 |  | `addiu sd sd daddu` | asm/cod/0B81B8.s:2417 |
| `func_00240A20` | 0x4C | 19 | 2 |  | `addiu sd sd sd` | asm/cod/140960.s:70 |
| `func_00258508` | 0x4C | 19 | 2 |  | `addiu sd sd daddu` | asm/cod/15846C.s:69 |
| `func_001CCA70` | 0x50 | 20 | 2 |  | `addiu sd sd jal` | asm/cod/0CBE84.s:904 |
| `func_002633B8` | 0x54 | 21 | 2 |  | `addiu sd daddu sd` | asm/cod/1633B4.s:18 |
| `func_00246918` | 0x58 | 22 | 2 |  | `addiu sd sd sd` | asm/cod/146030.s:739 |
| `func_00252590` | 0x58 | 22 | 2 |  | `lui daddu addiu lw` | asm/cod/15258C.s:18 |
| `func_001CE690` | 0x5C | 23 | 2 |  | `addiu sd sd daddu` | asm/cod/0CBE84.s:2972 |
| `func_001F3308` | 0x5C | 23 | 2 |  | `addiu sd sd daddu` | asm/cod/0F23D8.s:1101 |
| `func_001AE948` | 0x60 | 24 | 2 |  | `addiu sd sd daddu` | asm/cod/0AE948.s:13 |
| `func_0010EC08` | 0x44 | 17 | 2 |  | `mtc1 addiu c.lt.s nop` | asm/cod/00E950.s:255 |
| `func_0015F2D8` | 0x44 | 17 | 2 |  | `addiu lui mtc1 sd` | asm/cod/05F2D4.s:18 |
| `func_0014A700` | 0x48 | 18 | 2 |  | `addiu sd sd daddu` | asm/cod/04A2C4.s:387 |
| `func_001CEB68` | 0x48 | 18 | 2 |  | `addiu addiu sd addiu` | asm/cod/0CEB64.s:18 |
| `func_0019E1D8` | 0x4C | 19 | 2 |  | `addiu sd sd daddu` | asm/cod/09E1D8.s:13 |
| `func_00204F58` | 0x4C | 19 | 2 |  | `addiu sd sd bnez` | asm/cod/104E98.s:73 |
| `func_0016A240` | 0x5C | 23 | 2 |  | `addiu sd sd lui` | asm/cod/06A1D4.s:51 |
| `func_0017D1D0` | 0x60 | 24 | 2 |  | `addiu sw sd jal` | asm/cod/07D0F8.s:87 |
| `func_001A31C0` | 0x44 | 17 | 2 |  | `addiu lw addiu beq` | asm/cod/0A2E24.s:291 |
| `func_001AE9A8` | 0x44 | 17 | 2 |  | `addiu addiu sd jal` | asm/cod/0AE948.s:47 |
| `func_001AE830` | 0x4C | 19 | 2 |  | `addiu lui sd sd` | asm/cod/0AE82C.s:18 |
| `func_001B56D0` | 0x54 | 21 | 2 |  | `addiu addiu beq sd` | asm/cod/0B5620.s:75 |
| `func_001F16A0` | 0x54 | 21 | 2 |  | `addiu lui lw addiu` | asm/cod/0F1260.s:339 |
| `func_0015EE78` | 0x58 | 22 | 2 |  | `addiu sw sd lui` | asm/cod/05EE74.s:18 |
| `func_0017DEE0` | 0x58 | 22 | 2 |  | `addiu sd sd jal` | asm/cod/07DCD4.s:196 |
| `func_0023E228` | 0x58 | 22 | 2 |  | `addiu daddu sd daddu` | asm/cod/13E180.s:71 |
| `func_001EBB10` | 0x60 | 24 | 2 |  | `addiu sd daddu sd` | asm/cod/0EBA3C.s:88 |
| `func_001447E0` | 0x44 | 17 | 2 |  | `addiu sd sd jal` | asm/cod/0445C8.s:187 |
| `func_001CD490` | 0x44 | 17 | 2 |  | `addiu lw sd jal` | asm/cod/0CBE84.s:1652 |
| `func_0025C570` | 0x44 | 17 | 2 |  | `addiu sd sd jal` | asm/cod/158D0C.s:4355 |
| `func_00205000` | 0x48 | 18 | 2 |  | `addiu swc1 sd bnez` | asm/cod/104E98.s:137 |
| `func_0013DB60` | 0x50 | 20 | 2 |  | `addiu sd sd sd` | asm/cod/03D944.s:193 |
| `func_00243E70` | 0x50 | 20 | 2 |  | `addiu sd sd daddu` | asm/cod/143C00.s:218 |
| `func_0015E658` | 0x54 | 21 | 2 |  | `addiu sd sw nop` | asm/cod/05D488.s:1323 |
| `func_0015F578` | 0x58 | 22 | 2 |  | `addiu sw lui sd` | asm/cod/05F578.s:13 |
| `func_0014B708` | 0x5C | 23 | 2 |  | `addiu addiu sd sd` | asm/cod/04B5B4.s:114 |
| `func_00164FD0` | 0x48 | 18 | 2 |  | `addiu addiu sd lui` | asm/cod/064FCC.s:18 |
| `func_00144178` | 0x4C | 19 | 2 |  | `addiu daddu sd sd` | asm/cod/043CCC.s:395 |
| `func_001C92D8` | 0x4C | 19 | 2 |  | `addiu lui lw addiu` | asm/cod/0C8EF4.s:331 |
| `func_001ADCB0` | 0x50 | 20 | 2 |  | `addiu addiu sd addiu` | asm/cod/0ADBBC.s:90 |
| `func_00211780` | 0x50 | 20 | 2 |  | `addiu sd jal addiu` | asm/cod/111620.s:125 |
| `func_00229D88` | 0x54 | 21 | 2 |  | `lui addiu addiu sw` | asm/cod/129CB0.s:83 |
| `func_00229DE0` | 0x54 | 21 | 2 |  | `lui addiu addiu sw` | asm/cod/129CB0.s:111 |

<a id="vu-leaf-4-0x10"></a>
## 4-insn / 0x10 leaf, no jal, has VU (VU0 macro)

_0 total in this bucket; showing top 0._

(empty)

<a id="vu-leaf-56-0x14-0x18"></a>
## 5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)

_1 total in this bucket; showing top 1._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00245258` | 0x18 | 6 | 0 | Y | `lw addiu sq sw` | asm/cod/145228.s:31 |

<a id="uncategorized"></a>
## Uncategorized (not in any shape bucket above)

_3971 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

