# Matching candidates

Auto-generated unmatched-function shortlist for the ICO matching loop.

- Generated: 2026-05-07 02:28:06 UTC
- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)
- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)
- Filter: functions registered under `tough_nuts/<func>/` are excluded
- Functions: 4687 total in `asm/cod/*.s`, 3 parked, 4684 considered
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

_27 total in this bucket; showing top 27._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0010B2C0` | 0x10 | 4 | 0 |  | `lw lw j addiu` | asm/cod/00AB28.s:577 |
| `func_0010EC50` | 0x10 | 4 | 0 |  | `daddu lw j sw` | asm/cod/00E950.s:283 |
| `func_0010ECC8` | 0x10 | 4 | 0 |  | `lui lw j lw` | asm/cod/00E950.s:369 |
| `func_00159230` | 0x10 | 4 | 0 |  | `lw lw j addiu` | asm/cod/054CC8.s:5259 |
| `func_00187308` | 0x10 | 4 | 0 |  | `lw lw j lw` | asm/cod/082C14.s:5092 |
| `func_00187318` | 0x10 | 4 | 0 |  | `lw lw j lw` | asm/cod/082C14.s:5101 |
| `func_0019D9D8` | 0x10 | 4 | 0 |  | `lui ori j and` | asm/cod/09B948.s:2419 |
| `func_0019E150` | 0x10 | 4 | 0 |  | `lui ori j and` | asm/cod/09DBE4.s:427 |
| `func_0019E4E8` | 0x10 | 4 | 0 |  | `lui ori j and` | asm/cod/09E310.s:163 |
| `func_001E8EA8` | 0x10 | 4 | 0 |  | `lw lw j lw` | asm/cod/0E8BF0.s:259 |
| `func_001F0540` | 0x10 | 4 | 0 |  | `lw lw j lw` | asm/cod/0EFA60.s:807 |
| `func_001F6C88` | 0x10 | 4 | 0 |  | `lui lui j sw` | asm/cod/0F6AA0.s:157 |
| `func_0023E170` | 0x10 | 4 | 0 |  | `lui ori j and` | asm/cod/13D38C.s:1131 |
| `func_0023E770` | 0x10 | 4 | 0 |  | `lw slt j movz` | asm/cod/13E294.s:361 |
| `func_00240950` | 0x10 | 4 | 0 |  | `lui ori j and` | asm/cod/13F17C.s:1830 |
| `func_002523A0` | 0x10 | 4 | 0 |  | `lui addiu j sw` | asm/cod/151ED0.s:415 |
| `func_00137538` | 0x10 | 4 | 0 |  | `daddu daddu j sw` | asm/cod/036094.s:1594 |
| `func_00137548` | 0x10 | 4 | 0 |  | `daddu daddu j sw` | asm/cod/036094.s:1603 |
| `func_00145638` | 0x10 | 4 | 0 |  | `lw daddu j sw` | asm/cod/0445C8.s:1317 |
| `func_0015D348` | 0x10 | 4 | 0 |  | `lui mtc1 j nop` | asm/cod/054CC8.s:10175 |
| `func_00209AB0` | 0x10 | 4 | 0 |  | `addiu daddu j addiu` | asm/cod/104E98.s:6085 |
| `func_0010D520` | 0x10 | 4 | 0 |  | `lui sw j addiu` | asm/cod/00D198.s:315 |
| `func_001F0A28` | 0x10 | 4 | 0 |  | `lui sw j addiu` | asm/cod/0EFA60.s:1215 |
| `func_0023F7E0` | 0x10 | 4 | 0 |  | `daddu lui j addiu` | asm/cod/13F17C.s:511 |
| `func_00252550` | 0x10 | 4 | 0 |  | `daddu lui j addiu` | asm/cod/151ED0.s:553 |
| `func_0017B5A0` | 0x10 | 4 | 0 |  | `lwc1 lwc1 j lwc1` | asm/cod/07A9D4.s:1018 |
| `func_0019FF98` | 0x10 | 4 | 0 |  | `daddu daddu j daddu` | asm/cod/09F4E8.s:823 |

<a id="leaf-5-0x14"></a>
## 5-insn / 0x14 leaf, no jal, no VU (store-and-forward)

_27 total in this bucket; showing top 27._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0011EE58` | 0x14 | 5 | 0 |  | `daddu daddu addiu j` | asm/cod/01BFC0.s:3459 |
| `func_0011EE70` | 0x14 | 5 | 0 |  | `daddu daddu addiu j` | asm/cod/01BFC0.s:3471 |
| `func_00137EF0` | 0x14 | 5 | 0 |  | `ld andi andi jr` | asm/cod/037EF0.s:13 |
| `func_001A7820` | 0x14 | 5 | 0 |  | `daddu lui daddu j` | asm/cod/0A6E24.s:786 |
| `func_001C3970` | 0x14 | 5 | 0 |  | `addiu mult addu j` | asm/cod/0C2F20.s:841 |
| `func_001D12C0` | 0x14 | 5 | 0 |  | `lw sll addu j` | asm/cod/0D03E8.s:1203 |
| `func_001F0550` | 0x14 | 5 | 0 |  | `lw lw lw j` | asm/cod/0EFA60.s:817 |
| `func_0026F420` | 0x14 | 5 | 0 |  | `lui ori and j` | asm/cod/16D6C8.s:2359 |
| `func_0026F560` | 0x14 | 5 | 0 |  | `lui ori and j` | asm/cod/16D6C8.s:2469 |
| `func_001C8A00` | 0x14 | 5 | 0 |  | `addiu mult addu jr` | asm/cod/0C2F20.s:6757 |
| `func_0025C668` | 0x14 | 5 | 0 |  | `daddu addiu addiu j` | asm/cod/158CEC.s:4461 |
| `func_0025CCB0` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:4961 |
| `func_0025CCC8` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:4972 |
| `func_0025CCF8` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:4994 |
| `func_0025CD10` | 0x14 | 5 | 0 |  | `daddu daddu daddu j` | asm/cod/158CEC.s:5005 |
| `func_00194EA8` | 0x14 | 5 | 0 |  | `lui addiu swc1 jr` | asm/cod/093F78.s:1219 |
| `func_0019C010` | 0x14 | 5 | 0 |  | `addiu lui sw j` | asm/cod/09B948.s:527 |
| `func_0025E100` | 0x14 | 5 | 0 |  | `daddu daddu addiu j` | asm/cod/158CEC.s:6625 |
| `func_0013DD88` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/03D944.s:364 |
| `func_0016BCF0` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/06A2C4.s:2071 |
| `func_00197FE8` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/097338.s:997 |
| `func_001CB910` | 0x14 | 5 | 0 |  | `daddu swc1 lui j` | asm/cod/0C9338.s:2551 |
| `func_0025DCF0` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/158CEC.s:6272 |
| `func_0025DD08` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/158CEC.s:6283 |
| `func_0025E020` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/158CEC.s:6541 |
| `func_0025E038` | 0x14 | 5 | 0 |  | `addiu daddu daddu j` | asm/cod/158CEC.s:6552 |
| `func_001869F8` | 0x14 | 5 | 0 |  | `lui daddu addiu j` | asm/cod/082C14.s:4380 |

<a id="leaf-6-0x18"></a>
## 6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)

_20 total in this bucket; showing top 20._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101A88` | 0x18 | 6 | 0 |  | `mfc0 lui and ei` | asm/cod/000C90.s:1209 |
| `func_0013D3D8` | 0x18 | 6 | 0 |  | `bnez nop j nop` | asm/cod/03D0A0.s:271 |
| `func_0014BDD8` | 0x18 | 6 | 0 |  | `addiu addiu movn ori` | asm/cod/04BDD4.s:18 |
| `func_0015D470` | 0x18 | 6 | 0 |  | `lw lw lw addiu` | asm/cod/054CC8.s:10271 |
| `func_00187990` | 0x18 | 6 | 0 |  | `addiu lw mult lw` | asm/cod/087904.s:66 |
| `func_00193818` | 0x18 | 6 | 0 |  | `lw lw lw addiu` | asm/cod/0920A4.s:1827 |
| `func_001D4DD0` | 0x18 | 6 | 0 |  | `bnez lw jr lw` | asm/cod/0D4DA4.s:35 |
| `func_001E93D0` | 0x18 | 6 | 0 |  | `lw lw lw lw` | asm/cod/0E8F38.s:335 |
| `func_001F5608` | 0x18 | 6 | 0 |  | `lui addiu sw sw` | asm/cod/0F4DE8.s:645 |
| `func_0025CCE0` | 0x18 | 6 | 0 |  | `daddu daddu daddu daddu` | asm/cod/158CEC.s:4983 |
| `func_0025CE78` | 0x18 | 6 | 0 |  | `daddu daddu daddu daddu` | asm/cod/158CEC.s:5131 |
| `func_001C8B48` | 0x18 | 6 | 0 |  | `lwc1 nop nop div.s` | asm/cod/0C2F20.s:6869 |
| `func_001B0A68` | 0x18 | 6 | 0 |  | `lui addiu ori daddu` | asm/cod/0B0A64.s:18 |
| `func_001B0A80` | 0x18 | 6 | 0 |  | `lui addiu ori daddu` | asm/cod/0B0A64.s:29 |
| `func_001B0A98` | 0x18 | 6 | 0 |  | `lui addiu ori daddu` | asm/cod/0B0A64.s:40 |
| `func_001D1410` | 0x18 | 6 | 0 |  | `lw lwc1 .word mfc1` | asm/cod/0D03E8.s:1323 |
| `func_00240B70` | 0x18 | 6 | 0 |  | `lui sll addiu addu` | asm/cod/140B70.s:13 |
| `func_0024B890` | 0x18 | 6 | 0 |  | `lui sll addiu addu` | asm/cod/14B88C.s:18 |
| `func_00258C90` | 0x18 | 6 | 0 |  | `lui sll addiu addu` | asm/cod/158C90.s:13 |
| `func_00258CA8` | 0x18 | 6 | 0 |  | `lui sll addiu addu` | asm/cod/158C90.s:25 |

<a id="leaf-7-0x1C"></a>
## 7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)

_29 total in this bucket; showing top 29._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0010D408` | 0x1C | 7 | 0 |  | `lw lui addiu sll` | asm/cod/00D198.s:205 |
| `func_0010D428` | 0x1C | 7 | 0 |  | `lw lui addiu daddu` | asm/cod/00D198.s:219 |
| `func_0011BF40` | 0x1C | 7 | 0 |  | `lw lw lb daddu` | asm/cod/018AB4.s:4024 |
| `func_0015F208` | 0x1C | 7 | 0 |  | `lw lw lwu dsll32` | asm/cod/05EF50.s:233 |
| `func_001882B0` | 0x1C | 7 | 0 |  | `lw bne nop j` | asm/cod/088228.s:63 |
| `func_0019DB50` | 0x1C | 7 | 0 |  | `lw daddu slt movn` | asm/cod/09B948.s:2555 |
| `func_001AD748` | 0x1C | 7 | 0 |  | `nop nop nop nop` | asm/cod/0AD748.s:13 |
| `func_001BB7E0` | 0x1C | 7 | 0 |  | `lw lwu dsll32 dsra32` | asm/cod/0BA5E0.s:1463 |
| `func_001F3368` | 0x1C | 7 | 0 |  | `lw daddu lw addiu` | asm/cod/0F2250.s:1287 |
| `func_00245E88` | 0x1C | 7 | 0 |  | `lw lui ori sw` | asm/cod/145674.s:684 |
| `func_00168A40` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:18 |
| `func_00168A60` | 0x1C | 7 | 0 |  | `lw beqz daddu jr` | asm/cod/068A3C.s:33 |
| `func_0012FE78` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/02FE78.s:13 |
| `func_0014BB00` | 0x1C | 7 | 0 |  | `lw lui mtc1 lw` | asm/cod/04B86C.s:220 |
| `func_0015F228` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/05EF50.s:247 |
| `func_00176AE8` | 0x1C | 7 | 0 |  | `daddu addiu lui daddu` | asm/cod/07614C.s:732 |
| `func_0019BB40` | 0x1C | 7 | 0 |  | `lw lui mtc1 lw` | asm/cod/09B948.s:177 |
| `func_001A2D58` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0A1030.s:2201 |
| `func_001E8D30` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0E8BF0.s:113 |
| `func_001E8D50` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0E8BF0.s:127 |
| `func_001F1148` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/0F1108.s:39 |
| `func_00205A78` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/104E98.s:1105 |
| `func_00205B30` | 0x1C | 7 | 0 |  | `addiu lui mult addiu` | asm/cod/104E98.s:1175 |
| `func_0024B8A8` | 0x1C | 7 | 0 |  | `lui sll addiu addu` | asm/cod/14B88C.s:29 |
| `func_00258CF0` | 0x1C | 7 | 0 |  | `lui sll addiu sll` | asm/cod/158CEC.s:18 |
| `func_002608E0` | 0x1C | 7 | 0 |  | `mfc1 lui ori and` | asm/cod/158CEC.s:9762 |
| `func_00132610` | 0x1C | 7 | 0 |  | `daddu addiu lui sw` | asm/cod/02FFF0.s:2827 |
| `func_00175F60` | 0x1C | 7 | 0 |  | `lwc1 lwc1 sub.s .word` | asm/cod/075CB0.s:233 |
| `func_0018CF60` | 0x1C | 7 | 0 |  | `lw bnez lui jr` | asm/cod/08CF60.s:13 |

<a id="wrap-8-0x20"></a>
## 8-insn / 0x20, exactly 1 jal, no VU (passthrough call)

_12 total in this bucket; showing top 12._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_0011E708` | 0x20 | 8 | 1 |  | `addiu lw sd jal` | asm/cod/01BFC0.s:2867 |
| `func_00154CC8` | 0x20 | 8 | 1 |  | `addiu sd sw nop` | asm/cod/054CC8.s:13 |
| `func_00176198` | 0x20 | 8 | 1 |  | `addiu sd sw jal` | asm/cod/07614C.s:41 |
| `func_0017C990` | 0x20 | 8 | 1 |  | `addiu sd jal nop` | asm/cod/07A9D4.s:2549 |
| `func_001F2370` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/0F2250.s:109 |
| `func_0024BFAC` | 0x20 | 8 | 1 |  | `sd jal daddu sync` | asm/cod/14BBC0.s:353 |
| `func_001383D8` | 0x20 | 8 | 1 |  | `addiu sd jal addiu` | asm/cod/037EF0.s:417 |
| `func_001683A8` | 0x20 | 8 | 1 |  | `addiu lw sd jalr` | asm/cod/0654E0.s:3587 |
| `func_0024A980` | 0x20 | 8 | 1 |  | `addiu daddu sd jal` | asm/cod/14A754.s:183 |
| `func_00250F70` | 0x20 | 8 | 1 |  | `addiu daddu sd jal` | asm/cod/14BBC0.s:6877 |
| `func_00123C00` | 0x20 | 8 | 1 |  | `addiu lui sd jal` | asm/cod/022C88.s:1041 |
| `func_00241A00` | 0x20 | 8 | 1 |  | `addiu lui sd jal` | asm/cod/140B70.s:1155 |

<a id="wrap-9-0x24"></a>
## 9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)

_27 total in this bucket; showing top 27._

| Function | Size | Insns | jal | VU | First mnemonics | Source |
|---|---:|---:|---:|:---:|---|---|
| `func_00101AE8` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/000C90.s:1245 |
| `func_00101B40` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/000C90.s:1279 |
| `func_00101C08` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/000C90.s:1353 |
| `func_00101C30` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/000C90.s:1369 |
| `func_00101C58` | 0x24 | 9 | 1 |  | `addiu sw daddu sd` | asm/cod/000C90.s:1385 |
| `func_0012BBE8` | 0x24 | 9 | 1 |  | `addiu addiu sd addiu` | asm/cod/028710.s:4169 |
| `func_0015F4B8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05EF50.s:475 |
| `func_0015F4F0` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/05F4F0.s:13 |
| `func_001684E8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0684E8.s:13 |
| `func_00168510` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0684E8.s:29 |
| `func_001685B8` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/0685B8.s:13 |
| `func_00180580` | 0x24 | 9 | 1 |  | `addiu sw lw sd` | asm/cod/07EC94.s:1954 |
| `func_00194590` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/093F78.s:497 |
| `func_00245DB8` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/145674.s:612 |
| `func_0024FBD0` | 0x24 | 9 | 1 |  | `addiu sd jal daddu` | asm/cod/14BBC0.s:5279 |
| `func_00251D48` | 0x24 | 9 | 1 |  | `addiu addiu sd daddu` | asm/cod/151C28.s:125 |
| `func_002657F0` | 0x24 | 9 | 1 |  | `lui addiu lw sd` | asm/cod/164D60.s:853 |
| `func_0026B178` | 0x24 | 9 | 1 |  | `lui addiu lw sd` | asm/cod/16B144.s:35 |
| `func_0026D488` | 0x24 | 9 | 1 |  | `lui addiu lw sd` | asm/cod/16CF2C.s:488 |
| `func_001AB190` | 0x24 | 9 | 1 |  | `addiu lwc1 sd jal` | asm/cod/0AB190.s:13 |
| `func_00260610` | 0x24 | 9 | 1 |  | `addiu sd ld jal` | asm/cod/158CEC.s:9550 |
| `func_00144E30` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/0445C8.s:685 |
| `func_0016A678` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/06A2C4.s:298 |
| `func_001AA660` | 0x24 | 9 | 1 |  | `addiu lui sd jal` | asm/cod/0AA5C0.s:73 |
| `func_001ABF58` | 0x24 | 9 | 1 |  | `addiu sd jal nop` | asm/cod/0AB1D8.s:999 |
| `func_001F6E00` | 0x24 | 9 | 1 |  | `addiu lui sd addiu` | asm/cod/0F6DB8.s:37 |
| `func_0017E330` | 0x24 | 9 | 1 |  | `addiu daddu sd daddu` | asm/cod/07E330.s:13 |

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

_4541 unmatched functions are not in any shape bucket above._

Tweak the buckets in `tools/gen_candidates.py` to surface more shapes.

