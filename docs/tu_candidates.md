# TU candidates — close-to-done first

Auto-generated TU-first matching shortlist. Drives `decomp/MATCH.md`'s TU picker. For the cod-shim reduction view (active coalesce sprint), see [`docs/tu_coalesce.md`](tu_coalesce.md).

- Generated: 2026-05-17 01:52:51 UTC
- Source: `tools/tu_candidates.py`
- Regenerate: runs at end of `tools/build.sh setup`
- Per-TU sort: close-to-done by text-matched ratio, ties broken by remaining unmatched count.
- Per-bucket sort: hard-pattern penalty, insn count, size.
- Showing top 40 TUs, up to 30 funcs each.

## Top picks

### src/attackCheckBoundary.c
_text 2/4 (50%) · coal 0/4 · cod 4 · uninsn 202 · data 6/12_

**uncategorized** (2)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001BBDD8` | 0x70 | src/cod/0BB8C0 |
| `0x001BBB20` | 0x2B8 | src/cod/0BB8C0 |

### src/attackhit.c
_text 3/6 (50%) · coal 6/6 · cod 0 · uninsn 358 · data 17/17_ 🎯 score-0 permuter hit pending

**uncategorized** (2)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00181D88` | 0x1B0 | src/attackhit |
| `0x00181960` | 0x258 | src/attackhit |

### ios/thread.c
_text 13/27 (48%) · coal 0/27 · cod 27 · uninsn 543 · data 20/82_

**uncategorized** (14)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0013D3D4` | 0x4 | src/cod/03D3D4 |
| `0x0013D494` | 0x4 | src/cod/03D494 |
| `0x0013D8DC` | 0x4 | src/cod/03D8DC |
| `0x0013D924` | 0x4 | src/cod/03D924 |
| `0x0013D944` | 0x4 | src/cod/03D944 |
| `0x0013DB00` | 0x60 | src/cod/03DA00 |
| `0x0013DA88` | 0x78 | src/cod/03DA00 |
| `0x0013D948` | 0x80 | src/cod/03D944 |
| `0x0013DBB0` | 0x80 | src/cod/03DBB0 |
| `0x0013DA00` | 0x88 | src/cod/03DA00 |
| `0x0013D498` | 0xA0 | src/cod/03D494 |
| `0x0013D700` | 0x1A0 | src/cod/03D550 |
| `0x0013D550` | 0x1B0 | src/cod/03D550 |
| `0x0013D1B0` | 0x218 | src/cod/03D0D0 |

### src/weapon.c
_text 8/19 (42%) · coal 0/19 · cod 19 · uninsn 925 · data 2/63_

**uncategorized** (10)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001F42E4` | 0x4 | src/cod/0F42E4 |
| `0x001F40D8` | 0x78 | src/cod/0F40D8 |
| `0x001F4150` | 0x78 | src/cod/0F40D8 |
| `0x001F4318` | 0xB8 | src/cod/0F4318 |
| `0x001F3FB0` | 0xE8 | src/cod/0F3FB0 |
| `0x001F43D0` | 0xF8 | src/cod/0F4318 |
| `0x001F3A28` | 0x1A8 | src/cod/0F3A28 |
| `0x001F34C8` | 0x228 | src/cod/0F3390 |
| `0x001F36F0` | 0x310 | src/cod/0F3390 |
| `0x001F3BD0` | 0x388 | src/cod/0F3A28 |

### src/enemy_act.c
_text 24/65 (37%) · coal 0/65 · cod 65 · uninsn 5725 · data 164/180_

**uncategorized** (40)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0015F9F4` | 0x4 | src/cod/05F9F4 |
| `0x00164EF4` | 0x4 | src/cod/064EF4 |
| `0x00164F3C` | 0x4 | src/cod/064F3C |
| `0x00164F84` | 0x4 | src/cod/064F84 |
| `0x00164FCC` | 0x4 | src/cod/064FCC |
| `0x00165174` | 0x4 | src/cod/065174 |
| `0x0016529C` | 0x4 | src/cod/06529C |
| `0x001652B4` | 0x4 | src/cod/0652B4 |
| `0x001652CC` | 0x4 | src/cod/0652CC |
| `0x00165344` | 0x4 | src/cod/065344 |
| `0x00165414` | 0x4 | src/cod/065414 |
| `0x00165488` | 0x40 | src/cod/065414 |
| `0x00165418` | 0x70 | src/cod/065414 |
| `0x00165540` | 0x70 | src/cod/065540 |
| `0x00163890` | 0xC0 | src/cod/05FC50 |
| `0x0015FC50` | 0x108 | src/cod/05FC50 |
| `0x0015F6F0` | 0x110 | src/cod/05F6EC |
| `0x00160AF8` | 0x110 | src/cod/05FC50 |
| `0x00165018` | 0x140 | src/cod/065018 |
| `0x00163068` | 0x150 | src/cod/05FC50 |
| `0x001609A0` | 0x158 | src/cod/05FC50 |
| `0x00163D60` | 0x158 | src/cod/05FC50 |
| `0x0015F9F8` | 0x168 | src/cod/05F9F4 |
| `0x00161AC8` | 0x170 | src/cod/05FC50 |
| `0x00164D30` | 0x180 | src/cod/05FC50 |
| `0x0015F800` | 0x1B0 | src/cod/05F6EC |
| `0x001613B0` | 0x1E8 | src/cod/05FC50 |
| `0x00162DB8` | 0x2B0 | src/cod/05FC50 |
| `0x00161C38` | 0x2D8 | src/cod/05FC50 |
| `0x00162AC8` | 0x2F0 | src/cod/05FC50 |
| … | | _10 more_ |

### sound/adpcm_init.c
_text 5/14 (36%) · coal 0/14 · cod 14 · uninsn 572 · data 11/21_

**uncategorized** (8)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00140B5C` | 0x4 | src/cod/040B5C |
| `0x00140B6C` | 0x4 | src/cod/040B6C |
| `0x00140BDC` | 0x4 | src/cod/040BDC |
| `0x00140BE0` | 0x100 | src/cod/040BDC |
| `0x00140A20` | 0x110 | src/cod/040748 |
| `0x00140748` | 0x140 | src/cod/040748 |
| `0x00140888` | 0x198 | src/cod/040748 |
| `0x00140340` | 0x3D0 | src/cod/040138 |

### src/commonact.c
_text 89/270 (33%) · coal 11/270 · cod 259 · uninsn 17668 · data 153/181_

**0x40-0x60, 2 jal (2-call mid)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x0015E658` | 0x58 | 21 | 2 | `addiu sd sw nop` |

**Spill+reload (volatile a0)** (2)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x00165918` | 0x238 | 141 | 18 | `addiu sw sd swc1` |
| `0x0015EAB0` | 0x308 | 193 | 24 | `addiu sw lw sd` |

**1 jal + %gp_rel (D[0] passthrough)** (14)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x00169E58` | 0x128 | 74 | 1 | `addiu lw sd sd` |
| `0x001692F0` | 0x150 | 84 | 1 | `addiu lw sd sd` |
| `0x00168DA8` | 0x128 | 74 | 1 | `addiu lw sd sd` |
| `0x00169AA8` | 0x128 | 74 | 1 | `addiu lw sd sd` |
| `0x00169440` | 0x140 | 79 | 1 | `addiu lw sd sd` |
| `0x00169580` | 0x140 | 79 | 1 | `addiu lw sd sd` |
| `0x00169968` | 0x140 | 79 | 1 | `addiu lw sd sd` |
| `0x001696C0` | 0x140 | 80 | 1 | `addiu lw sd sd` |
| `0x00169D18` | 0x140 | 80 | 1 | `addiu lw sd sd` |
| `0x00169BD0` | 0x148 | 82 | 1 | `addiu lw sd sd` |
| `0x00168ED0` | 0x150 | 84 | 1 | `addiu lw sd sd` |
| `0x00169800` | 0x168 | 89 | 1 | `addiu lw sd sd` |
| `0x00169190` | 0x160 | 87 | 1 | `addiu lw sd sd` |
| `0x00169020` | 0x170 | 92 | 1 | `addiu lw sd sd` |

**uncategorized** (153)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0015895C` | 0x4 | src/cod/05895C |
| `0x0015E7F4` | 0x4 | src/cod/05E7F4 |
| `0x0015EA7C` | 0x4 | src/cod/05EA7C |
| `0x0015EAAC` | 0x4 | src/cod/05EAAC |
| `0x0015EE74` | 0x4 | src/cod/05EE74 |
| `0x0015F224` | 0x4 | src/cod/05F224 |
| `0x0015F244` | 0x4 | src/cod/05F244 |
| `0x0015F294` | 0x4 | src/cod/05F294 |
| `0x0015F2D4` | 0x4 | src/cod/05F2D4 |
| `0x0015F31C` | 0x4 | src/cod/05F31C |
| `0x0015F4DC` | 0x4 | src/cod/05F4DC |
| `0x0015F514` | 0x4 | src/cod/05F514 |
| `0x0015F54C` | 0x4 | src/cod/05F54C |
| … | | _140 more_ |

### src/Light.c
_text 10/32 (31%) · coal 0/32 · cod 32 · uninsn 2932 · data 62/89_

**uncategorized** (19)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0011788C` | 0x4 | src/cod/01788C |
| `0x00117C5C` | 0x4 | src/cod/017C5C |
| `0x00117C7C` | 0x4 | src/cod/017C7C |
| `0x00117CCC` | 0x4 | src/cod/017CCC |
| `0x00117CEC` | 0x4 | src/cod/017CEC |
| `0x00114FC8` | 0xA0 | src/cod/014FC4 |
| `0x00115068` | 0xA0 | src/cod/014FC4 |
| `0x00117890` | 0xC0 | src/cod/01788C |
| `0x00117CF0` | 0xC0 | src/cod/017CEC |
| `0x00117DB0` | 0xC0 | src/cod/017CEC |
| `0x00115ED8` | 0xE0 | src/cod/014FC4 |
| `0x00117950` | 0x2D0 | src/cod/01788C |
| `0x001165A8` | 0x2E0 | src/cod/014FC4 |
| `0x00115108` | 0x308 | src/cod/014FC4 |
| `0x00116888` | 0x380 | src/cod/014FC4 |
| `0x00115410` | 0x468 | src/cod/014FC4 |
| `0x00115FB8` | 0x5F0 | src/cod/014FC4 |
| `0x00115878` | 0x660 | src/cod/014FC4 |
| `0x00116C08` | 0xB48 | src/cod/014FC4 |

### src/act-game.c
_text 11/37 (30%) · coal 0/37 · cod 37 · uninsn 1024 · data 29/39_

**uncategorized** (25)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00149EF4` | 0x4 | src/cod/049EF4 |
| `0x0014A2C4` | 0x4 | src/cod/04A2C4 |
| `0x0014A46C` | 0x4 | src/cod/04A46C |
| `0x0014A5FC` | 0x4 | src/cod/04A5FC |
| `0x0014A0A8` | 0x30 | src/cod/04A0A8 |
| `0x00149F20` | 0x50 | src/cod/049F20 |
| `0x0014A560` | 0x60 | src/cod/04A46C |
| `0x0014A470` | 0x70 | src/cod/04A46C |
| `0x0014A100` | 0x78 | src/cod/04A100 |
| `0x0014A330` | 0x78 | src/cod/04A330 |
| `0x00149F70` | 0x80 | src/cod/049F20 |
| `0x0014A4E0` | 0x80 | src/cod/04A46C |
| `0x0014A3A8` | 0x88 | src/cod/04A330 |
| `0x0014A980` | 0xA8 | src/cod/04A748 |
| `0x0014AEC8` | 0xA8 | src/cod/04A748 |
| `0x00149FF0` | 0xB8 | src/cod/049F20 |
| `0x0014A600` | 0xB8 | src/cod/04A5FC |
| `0x0014ADF8` | 0xD0 | src/cod/04A748 |
| `0x0014A748` | 0x108 | src/cod/04A748 |
| `0x0014AA28` | 0x108 | src/cod/04A748 |
| `0x00149D60` | 0x110 | src/cod/045648 |
| `0x0014A850` | 0x130 | src/cod/04A748 |
| `0x0014A178` | 0x138 | src/cod/04A100 |
| `0x0014AB30` | 0x148 | src/cod/04A748 |
| `0x0014AC78` | 0x180 | src/cod/04A748 |

### src/switch.c
_text 2/7 (29%) · coal 0/7 · cod 7 · uninsn 217 · data 1/31_

**uncategorized** (5)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001C0BF4` | 0x4 | src/cod/0C0BF4 |
| `0x001C0BF8` | 0x48 | src/cod/0C0BF4 |
| `0x001C0AE8` | 0xF8 | src/cod/0C0AE8 |
| `0x001C09C8` | 0x110 | src/cod/0C09C4 |
| `0x001C0C40` | 0x110 | src/cod/0C0BF4 |

### src/queen.c
_text 6/21 (29%) · coal 0/21 · cod 21 · uninsn 1274 · data 71/198_

**uncategorized** (15)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0019BAA4` | 0x4 | src/cod/09BAA4 |
| `0x0019BB5C` | 0x4 | src/cod/09BB5C |
| `0x0019AE50` | 0x48 | src/cod/099A5C |
| `0x0019B888` | 0x60 | src/cod/099A5C |
| `0x0019A9A0` | 0x80 | src/cod/099A5C |
| `0x0019BC58` | 0x88 | src/cod/09BB5C |
| `0x0019B7F8` | 0x90 | src/cod/099A5C |
| `0x0019BAA8` | 0x98 | src/cod/09BAA4 |
| `0x0019A8F0` | 0xB0 | src/cod/099A5C |
| `0x0019B998` | 0xC8 | src/cod/09B998 |
| `0x0019BB60` | 0xF8 | src/cod/09BB5C |
| `0x0019A7E8` | 0x108 | src/cod/099A5C |
| `0x0019B660` | 0x198 | src/cod/099A5C |
| `0x0019AA20` | 0x430 | src/cod/099A5C |
| `0x0019AE98` | 0x7C8 | src/cod/099A5C |

### src/boyact.c
_text 13/47 (28%) · coal 0/47 · cod 47 · uninsn 6464 · data 169/219_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x001547B8` | 0x138 | 77 | 1 | `addiu lui sd lui` |

**uncategorized** (33)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001538F4` | 0x4 | src/cod/0538F4 |
| `0x00154444` | 0x4 | src/cod/054444 |
| `0x00154644` | 0x4 | src/cod/054644 |
| `0x001546BC` | 0x4 | src/cod/0546BC |
| `0x0015479C` | 0x4 | src/cod/05479C |
| `0x001547AC` | 0x4 | src/cod/0547AC |
| `0x001502D8` | 0x70 | src/cod/04BDF8 |
| `0x00154B20` | 0x70 | src/cod/0547B8 |
| `0x001504D8` | 0x90 | src/cod/04BDF8 |
| `0x00154390` | 0x90 | src/cod/0539F0 |
| `0x00153918` | 0xA0 | src/cod/053918 |
| `0x001546C0` | 0xB0 | src/cod/0546BC |
| `0x00153FF0` | 0xB8 | src/cod/0539F0 |
| `0x001540A8` | 0xB8 | src/cod/0539F0 |
| `0x00154160` | 0xB8 | src/cod/0539F0 |
| `0x00154520` | 0xB8 | src/cod/054444 |
| `0x001548F0` | 0xC8 | src/cod/0547B8 |
| `0x00154448` | 0xD8 | src/cod/054444 |
| `0x001521F0` | 0xF0 | src/cod/04BDF8 |
| `0x001520E8` | 0x108 | src/cod/04BDF8 |
| `0x0014E5E8` | 0x120 | src/cod/04BDF8 |
| `0x00154B90` | 0x128 | src/cod/0547B8 |
| `0x0014E708` | 0x138 | src/cod/04BDF8 |
| `0x001501A0` | 0x138 | src/cod/04BDF8 |
| `0x001549B8` | 0x168 | src/cod/0547B8 |
| `0x00154218` | 0x178 | src/cod/0539F0 |
| `0x00150348` | 0x190 | src/cod/04BDF8 |
| `0x0014E840` | 0x1F0 | src/cod/04BDF8 |
| `0x00153478` | 0x448 | src/cod/04BDF8 |
| … | | _4 more_ |

### src/camera-ico2.c
_text 4/17 (24%) · coal 0/17 · cod 17 · uninsn 2855 · data 34/79_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x0018B180` | 0xC8 | 50 | 1 | `addiu daddu lui mtc1` |

**uncategorized** (12)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001886F4` | 0x4 | src/cod/0886F4 |
| `0x0018B300` | 0xA8 | src/cod/08B300 |
| `0x0018B248` | 0xB0 | src/cod/08B0A8 |
| `0x00189AC8` | 0xC0 | src/cod/0886F4 |
| `0x0018B0A8` | 0xD8 | src/cod/08B0A8 |
| `0x00188C98` | 0x198 | src/cod/0886F4 |
| `0x00189B88` | 0x1E0 | src/cod/0886F4 |
| `0x001897A8` | 0x320 | src/cod/0886F4 |
| `0x001886F8` | 0x5A0 | src/cod/0886F4 |
| `0x00189D68` | 0x698 | src/cod/0886F4 |
| `0x00188E30` | 0x978 | src/cod/0886F4 |
| `0x0018A400` | 0xC98 | src/cod/0886F4 |

### sound/s_init.c
_text 8/34 (24%) · coal 0/34 · cod 34 · uninsn 2881 · data 67/88_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x00142008` | 0x200 | 128 | 1 | `addiu lui sd sd` |

**uncategorized** (24)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0014139C` | 0x4 | src/cod/04139C |
| `0x0014328C` | 0x4 | src/cod/04328C |
| `0x00143CCC` | 0x4 | src/cod/043CCC |
| `0x00143D14` | 0x4 | src/cod/043D14 |
| `0x00141F58` | 0xB0 | src/cod/0413A8 |
| `0x00143AD0` | 0xB8 | src/cod/04328C |
| `0x00141D18` | 0xE8 | src/cod/0413A8 |
| `0x00141C28` | 0xF0 | src/cod/0413A8 |
| `0x00143138` | 0x108 | src/cod/0413A8 |
| `0x00141868` | 0x118 | src/cod/0413A8 |
| `0x00143B98` | 0x118 | src/cod/043B98 |
| `0x00143D18` | 0x148 | src/cod/043D14 |
| `0x00141E00` | 0x158 | src/cod/0413A8 |
| `0x00143E60` | 0x160 | src/cod/043D14 |
| `0x00143FC0` | 0x160 | src/cod/043D14 |
| `0x00143948` | 0x188 | src/cod/04328C |
| `0x00141660` | 0x208 | src/cod/0413A8 |
| `0x00143290` | 0x220 | src/cod/04328C |
| `0x00141980` | 0x2A8 | src/cod/0413A8 |
| `0x001413A8` | 0x2B8 | src/cod/0413A8 |
| `0x00142890` | 0x3D0 | src/cod/0413A8 |
| `0x001434B0` | 0x498 | src/cod/04328C |
| `0x00142C60` | 0x4D8 | src/cod/0413A8 |
| `0x00142208` | 0x688 | src/cod/0413A8 |

### src/stormTest.c
_text 2/9 (22%) · coal 0/9 · cod 9 · uninsn 737 · data 29/33_

**uncategorized** (7)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001F0564` | 0x4 | src/cod/0F0564 |
| `0x001F0568` | 0xA0 | src/cod/0F0564 |
| `0x001EFEE0` | 0x1B8 | src/cod/0EFA60 |
| `0x001EFD18` | 0x1C8 | src/cod/0EFA60 |
| `0x001F0098` | 0x1C8 | src/cod/0EFA60 |
| `0x001EFA60` | 0x2B8 | src/cod/0EFA60 |
| `0x001F0260` | 0x2E0 | src/cod/0EFA60 |

### src/RegistPacket.c
_text 3/17 (18%) · coal 0/17 · cod 17 · uninsn 1321 · data 35/85_

**uncategorized** (12)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0011EE6C` | 0x4 | src/cod/01EE6C |
| `0x0011EE84` | 0x4 | src/cod/01EE84 |
| `0x0011EF70` | 0xD0 | src/cod/01EE84 |
| `0x0011F398` | 0xD0 | src/cod/01EE84 |
| `0x0011EE88` | 0xE8 | src/cod/01EE84 |
| `0x0011ECE0` | 0x118 | src/cod/01E728 |
| `0x0011F248` | 0x150 | src/cod/01EE84 |
| `0x0011EB50` | 0x190 | src/cod/01E728 |
| `0x0011F040` | 0x208 | src/cod/01EE84 |
| `0x0011F8E8` | 0x340 | src/cod/01EE84 |
| `0x0011E728` | 0x428 | src/cod/01E728 |
| `0x0011F468` | 0x480 | src/cod/01EE84 |

### src/DObj.c
_text 1/6 (17%) · coal 0/6 · cod 6 · uninsn 916 · data 63/72_

**uncategorized** (5)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0019EB88` | 0x1A8 | src/cod/09E648 |
| `0x0019F310` | 0x1D0 | src/cod/09EF58 |
| `0x0019ED30` | 0x1E0 | src/cod/09E648 |
| `0x0019EF58` | 0x3B8 | src/cod/09EF58 |
| `0x0019E648` | 0x540 | src/cod/09E648 |

### src/enemyParts.c
_text 1/6 (17%) · coal 0/6 · cod 6 · uninsn 584 · data 48/56_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x001CF6C0` | 0xB0 | 44 | 1 | `addiu lwc1 sd sd` |

**uncategorized** (4)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001CF790` | 0x140 | src/cod/0CF790 |
| `0x001CF548` | 0x178 | src/cod/0CEC88 |
| `0x001CF288` | 0x2C0 | src/cod/0CEC88 |
| `0x001CEF90` | 0x2F8 | src/cod/0CEC88 |

### src/debug.c
_text 2/13 (15%) · coal 0/13 · cod 13 · uninsn 922 · data 336/418_

**uncategorized** (10)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001A2E24` | 0x4 | src/cod/0A2E24 |
| `0x001A3204` | 0x4 | src/cod/0A3204 |
| `0x001A3394` | 0x4 | src/cod/0A3394 |
| `0x001A2E28` | 0x58 | src/cod/0A2E24 |
| `0x001A2D78` | 0x98 | src/cod/0A2D74 |
| `0x001A2E80` | 0x120 | src/cod/0A2E24 |
| `0x001A3208` | 0x138 | src/cod/0A3204 |
| `0x001A2FA0` | 0x220 | src/cod/0A2E24 |
| `0x001A3980` | 0x2B8 | src/cod/0A3394 |
| `0x001A3398` | 0x5E8 | src/cod/0A3394 |

### isys/gobj.c
_text 2/14 (14%) · coal 0/14 · cod 14 · uninsn 604 · data 17/28_

**uncategorized** (10)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0013E4CC` | 0x4 | src/cod/03E4CC |
| `0x0013DDF8` | 0xA8 | src/cod/03DDF8 |
| `0x0013DFF0` | 0xD0 | src/cod/03DDF8 |
| `0x0013E0C0` | 0xD0 | src/cod/03DDF8 |
| `0x0013E728` | 0xD0 | src/cod/03E548 |
| `0x0013E648` | 0xE0 | src/cod/03E548 |
| `0x0013E548` | 0x100 | src/cod/03E548 |
| `0x0013E220` | 0x130 | src/cod/03E220 |
| `0x0013E350` | 0x138 | src/cod/03E220 |
| `0x0013DEA0` | 0x150 | src/cod/03DDF8 |

### ios/message.c
_text 1/8 (12%) · coal 0/8 · cod 8 · uninsn 337 · data 21/25_

**uncategorized** (7)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0013A5B4` | 0x4 | src/cod/03A5B4 |
| `0x0013A2F8` | 0x88 | src/cod/03A248 |
| `0x0013A250` | 0xA8 | src/cod/03A248 |
| `0x0013A498` | 0xE8 | src/cod/03A248 |
| `0x0013A5B8` | 0x108 | src/cod/03A5B4 |
| `0x0013A6C0` | 0x108 | src/cod/03A5B4 |
| `0x0013A380` | 0x118 | src/cod/03A248 |

### src/act.c
_text 1/8 (12%) · coal 0/8 · cod 8 · uninsn 1584 · data 393/399_

**uncategorized** (7)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00202148` | 0xC0 | src/cod/101DE0 |
| `0x00203918` | 0xF8 | src/cod/103918 |
| `0x002025E0` | 0x1E8 | src/cod/101DE0 |
| `0x002027C8` | 0x298 | src/cod/101DE0 |
| `0x00202208` | 0x3D8 | src/cod/101DE0 |
| `0x00202A60` | 0x6D0 | src/cod/101DE0 |
| `0x00203130` | 0x7E0 | src/cod/101DE0 |

### src/ebrain.c
_text 1/8 (12%) · coal 0/8 · cod 8 · uninsn 947 · data 62/85_

**uncategorized** (7)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001918EC` | 0x4 | src/cod/0918EC |
| `0x001918F0` | 0xB0 | src/cod/0918EC |
| `0x00191AA0` | 0xD0 | src/cod/0918EC |
| `0x001919A0` | 0x100 | src/cod/0918EC |
| `0x00191B70` | 0x110 | src/cod/0918EC |
| `0x00190D70` | 0x1C0 | src/cod/0906B8 |
| `0x00190F30` | 0x978 | src/cod/0906B8 |

### src/girl_brain_attract.c
_text 6/48 (12%) · coal 0/48 · cod 48 · uninsn 8547 · data 88/166_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x0016F2A8` | 0x168 | 90 | 1 | `addiu sd sd daddu` |

**Spill+reload (volatile a0)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x00175350` | 0x2F0 | 187 | 32 | `addiu sd sd addiu` |

**uncategorized** (39)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0017534C` | 0x4 | src/cod/07534C |
| `0x00175684` | 0x4 | src/cod/075684 |
| `0x001756CC` | 0x4 | src/cod/0756CC |
| `0x00175CDC` | 0x4 | src/cod/075CDC |
| `0x00175C18` | 0x58 | src/cod/0756CC |
| `0x00175A98` | 0xC0 | src/cod/0756CC |
| `0x00175B58` | 0xC0 | src/cod/0756CC |
| `0x00175CE0` | 0xE0 | src/cod/075CDC |
| `0x00173170` | 0xF8 | src/cod/06BD04 |
| `0x00175800` | 0xF8 | src/cod/0756CC |
| `0x001733D0` | 0x108 | src/cod/06BD04 |
| `0x0016EB68` | 0x110 | src/cod/06BD04 |
| `0x00173060` | 0x110 | src/cod/06BD04 |
| `0x00171AB0` | 0x118 | src/cod/06BD04 |
| `0x001756D0` | 0x130 | src/cod/0756CC |
| `0x00173268` | 0x168 | src/cod/06BD04 |
| `0x001736B8` | 0x168 | src/cod/06BD04 |
| `0x00174D78` | 0x188 | src/cod/06BD04 |
| `0x0016EC78` | 0x190 | src/cod/06BD04 |
| `0x00174F00` | 0x198 | src/cod/06BD04 |
| `0x001758F8` | 0x1A0 | src/cod/0756CC |
| `0x001718F0` | 0x1C0 | src/cod/06BD04 |
| `0x001734D8` | 0x1E0 | src/cod/06BD04 |
| `0x00175098` | 0x238 | src/cod/06BD04 |
| `0x0016E910` | 0x258 | src/cod/06BD04 |
| `0x001706E0` | 0x270 | src/cod/06BD04 |
| `0x00171BC8` | 0x280 | src/cod/06BD04 |
| `0x0016F9A8` | 0x2A0 | src/cod/06BD04 |
| … | | _11 more_ |

### src/StageAnimation.c
_text 2/17 (12%) · coal 0/17 · cod 17 · uninsn 2220 · data 31/54_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x00129E28` | 0x130 | 76 | 1 | `addiu lw sd sd` |

**uncategorized** (14)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0012A7A0` | 0x58 | src/cod/029AA8 |
| `0x0012AA80` | 0xD0 | src/cod/02AA80 |
| `0x00129970` | 0x108 | src/cod/0287E8 |
| `0x00129F58` | 0x108 | src/cod/029AA8 |
| `0x0012A618` | 0x188 | src/cod/029AA8 |
| `0x00129C90` | 0x198 | src/cod/029AA8 |
| `0x001297A0` | 0x1D0 | src/cod/0287E8 |
| `0x00128AF0` | 0x1E0 | src/cod/0287E8 |
| `0x00129AA8` | 0x1E8 | src/cod/029AA8 |
| `0x0012A7F8` | 0x280 | src/cod/029AA8 |
| `0x00128868` | 0x288 | src/cod/0287E8 |
| `0x0012A060` | 0x2B8 | src/cod/029AA8 |
| `0x0012A318` | 0x300 | src/cod/029AA8 |
| `0x00128CD0` | 0xAD0 | src/cod/0287E8 |

### src/particleEffect.c
_text 1/9 (11%) · coal 0/9 · cod 9 · uninsn 1764 · data 7/19_

**uncategorized** (7)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001E85D8` | 0x40 | src/cod/0E85D8 |
| `0x001E8810` | 0x120 | src/cod/0E85D8 |
| `0x001E83F8` | 0x1A0 | src/cod/0E6DA0 |
| `0x001E8618` | 0x1F8 | src/cod/0E85D8 |
| `0x001E80D8` | 0x320 | src/cod/0E6DA0 |
| `0x001E6DA0` | 0x608 | src/cod/0E6DA0 |
| `0x001E73A8` | 0xD30 | src/cod/0E6DA0 |

### src/way_util.c
_text 4/37 (11%) · coal 0/37 · cod 37 · uninsn 2306 · data 91/122_

**1 jal + %gp_rel (D[0] passthrough)** (2)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x0017A410` | 0xB0 | 43 | 1 | `addiu addiu mult lui` |
| `0x0017A4C0` | 0xB8 | 45 | 1 | `lw addiu addiu lui` |

**uncategorized** (31)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0017904C` | 0x4 | src/cod/07904C |
| `0x0017905C` | 0x4 | src/cod/07905C |
| `0x0017A9D4` | 0x4 | src/cod/07A9D4 |
| `0x0017AA04` | 0x4 | src/cod/07AA04 |
| `0x00179558` | 0x60 | src/cod/07905C |
| `0x0017A6F8` | 0x90 | src/cod/07905C |
| `0x0017AC48` | 0x90 | src/cod/07AA04 |
| `0x0017ACD8` | 0x90 | src/cod/07AA04 |
| `0x0017AD68` | 0x90 | src/cod/07AA04 |
| `0x0017A230` | 0x98 | src/cod/07905C |
| `0x0017A2C8` | 0xA0 | src/cod/07905C |
| `0x0017A368` | 0xA8 | src/cod/07905C |
| `0x0017A788` | 0xA8 | src/cod/07905C |
| `0x0017A910` | 0xA8 | src/cod/07905C |
| `0x0017A578` | 0xC0 | src/cod/07905C |
| `0x0017A638` | 0xC0 | src/cod/07905C |
| `0x0017A830` | 0xE0 | src/cod/07905C |
| `0x0017AA08` | 0x118 | src/cod/07AA04 |
| `0x00179438` | 0x120 | src/cod/07905C |
| `0x0017AB20` | 0x128 | src/cod/07AA04 |
| `0x00179E10` | 0x158 | src/cod/07905C |
| `0x00178990` | 0x190 | src/cod/07898C |
| `0x00178B20` | 0x1A8 | src/cod/07898C |
| `0x00178CC8` | 0x1B0 | src/cod/07898C |
| `0x00178E78` | 0x1C8 | src/cod/07898C |
| `0x00179060` | 0x1E8 | src/cod/07905C |
| `0x00179248` | 0x1F0 | src/cod/07905C |
| `0x001795B8` | 0x2C0 | src/cod/07905C |
| … | | _3 more_ |

### src/BgAnimation.c
_text 2/20 (10%) · coal 0/20 · cod 20 · uninsn 3577 · data 39/70_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x001F9418` | 0x268 | 153 | 1 | `addiu sd sd daddu` |

**uncategorized** (17)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001FA5DC` | 0x4 | src/cod/0FA5DC |
| `0x001FA5E0` | 0x78 | src/cod/0FA5DC |
| `0x001F9348` | 0xD0 | src/cod/0F6E28 |
| `0x001F9DD8` | 0x258 | src/cod/0F6E28 |
| `0x001F8398` | 0x268 | src/cod/0F6E28 |
| `0x001F74E8` | 0x2B8 | src/cod/0F6E28 |
| `0x001F8600` | 0x2C0 | src/cod/0F6E28 |
| `0x001F7D70` | 0x2C8 | src/cod/0F6E28 |
| `0x001F88C0` | 0x2D0 | src/cod/0F6E28 |
| `0x001F71D0` | 0x318 | src/cod/0F6E28 |
| `0x001F9680` | 0x320 | src/cod/0F6E28 |
| `0x001F8038` | 0x360 | src/cod/0F6E28 |
| `0x001F6E28` | 0x3A8 | src/cod/0F6E28 |
| `0x001F99A0` | 0x438 | src/cod/0F6E28 |
| `0x001FA030` | 0x560 | src/cod/0F6E28 |
| `0x001F77A0` | 0x5D0 | src/cod/0F6E28 |
| `0x001F8B90` | 0x7B8 | src/cod/0F6E28 |

### src/generator.c
_text 1/11 (9%) · coal 0/11 · cod 11 · uninsn 1240 · data 34/39_

**uncategorized** (10)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00192E08` | 0xB0 | src/cod/092B98 |
| `0x00192D20` | 0xE8 | src/cod/092B98 |
| `0x00193730` | 0xE8 | src/cod/092B98 |
| `0x00193600` | 0x130 | src/cod/092B98 |
| `0x00192478` | 0x168 | src/cod/0920A4 |
| `0x00192B98` | 0x188 | src/cod/092B98 |
| `0x00192EB8` | 0x1F8 | src/cod/092B98 |
| `0x00192908` | 0x250 | src/cod/0920A4 |
| `0x001925E0` | 0x328 | src/cod/0920A4 |
| `0x001930B0` | 0x550 | src/cod/092B98 |

### ios/cdvd.c
_text 2/22 (9%) · coal 0/22 · cod 22 · uninsn 2067 · data 144/227_

**uncategorized** (19)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0013262C` | 0x4 | src/cod/03262C |
| `0x00131560` | 0x48 | src/cod/02FFF0 |
| `0x00131780` | 0x98 | src/cod/02FFF0 |
| `0x00133218` | 0xA0 | src/cod/033218 |
| `0x00132038` | 0xB0 | src/cod/02FFF0 |
| `0x00131480` | 0xE0 | src/cod/02FFF0 |
| `0x001320E8` | 0xE0 | src/cod/02FFF0 |
| `0x001332B8` | 0xE0 | src/cod/033218 |
| `0x001312F0` | 0x190 | src/cod/02FFF0 |
| `0x001321C8` | 0x1C0 | src/cod/02FFF0 |
| `0x001315A8` | 0x1D8 | src/cod/02FFF0 |
| `0x00132FF0` | 0x1E8 | src/cod/03262C |
| `0x00132B90` | 0x230 | src/cod/03262C |
| `0x00132DC0` | 0x230 | src/cod/03262C |
| `0x00132388` | 0x250 | src/cod/02FFF0 |
| `0x00132930` | 0x260 | src/cod/03262C |
| `0x00132630` | 0x300 | src/cod/03262C |
| `0x00131C90` | 0x3A8 | src/cod/02FFF0 |
| `0x00131818` | 0x478 | src/cod/02FFF0 |

### src/girl_brain_main.c
_text 1/12 (8%) · coal 0/12 · cod 12 · uninsn 3907 · data 16/46_

**uncategorized** (11)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0016BD04` | 0x4 | src/cod/06BD04 |
| `0x0016BCA0` | 0x50 | src/cod/06AC50 |
| `0x0016BD08` | 0xF0 | src/cod/06BD04 |
| `0x0016D330` | 0x158 | src/cod/06BD04 |
| `0x0016E910` | 0x258 | src/cod/06BD04 |
| `0x0016D488` | 0x280 | src/cod/06BD04 |
| `0x0016B3C0` | 0x3D0 | src/cod/06AC50 |
| `0x0016B790` | 0x510 | src/cod/06AC50 |
| `0x0016AE48` | 0x578 | src/cod/06AC50 |
| `0x0016D708` | 0x1208 | src/cod/06BD04 |
| `0x0016BDF8` | 0x1538 | src/cod/06BD04 |

### src/geometryManager.c
_text 2/33 (6%) · coal 0/33 · cod 33 · uninsn 1843 · data 17/48_

**uncategorized** (31)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0010311C` | 0x4 | src/cod/00311C |
| `0x00104698` | 0x58 | src/cod/00311C |
| `0x001046F0` | 0x58 | src/cod/00311C |
| `0x00104638` | 0x60 | src/cod/00311C |
| `0x00102FA0` | 0x78 | src/cod/002E08 |
| `0x00103AD0` | 0x78 | src/cod/00311C |
| `0x001048C8` | 0x78 | src/cod/00311C |
| `0x001049C0` | 0x78 | src/cod/00311C |
| `0x001040C0` | 0x80 | src/cod/00311C |
| `0x00104140` | 0x80 | src/cod/00311C |
| `0x001041C0` | 0x80 | src/cod/00311C |
| `0x00104940` | 0x80 | src/cod/00311C |
| `0x00104508` | 0x88 | src/cod/00311C |
| `0x00104478` | 0x90 | src/cod/00311C |
| `0x00104590` | 0xA8 | src/cod/00311C |
| `0x00104A48` | 0xA8 | src/cod/004A48 |
| `0x00104818` | 0xB0 | src/cod/00311C |
| `0x00103120` | 0xC0 | src/cod/00311C |
| `0x001031E0` | 0xC8 | src/cod/00311C |
| `0x001032A8` | 0xC8 | src/cod/00311C |
| `0x00104748` | 0xD0 | src/cod/00311C |
| `0x00103018` | 0xF8 | src/cod/002E08 |
| `0x00103B48` | 0x100 | src/cod/00311C |
| `0x00103C48` | 0x108 | src/cod/00311C |
| `0x00104360` | 0x118 | src/cod/00311C |
| `0x00104240` | 0x120 | src/cod/00311C |
| `0x00103370` | 0x148 | src/cod/00311C |
| `0x00102E08` | 0x198 | src/cod/002E08 |
| `0x00103D50` | 0x1B0 | src/cod/00311C |
| `0x00103F00` | 0x1C0 | src/cod/00311C |
| … | | _1 more_ |

### src/motionManager.c
_text 2/35 (6%) · coal 0/35 · cod 35 · uninsn 6792 · data 78/152_

**uncategorized** (33)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001D9C58` | 0x58 | src/cod/0D4E88 |
| `0x001DC938` | 0x60 | src/cod/0DC938 |
| `0x001D9E10` | 0x80 | src/cod/0D4E88 |
| `0x001D9BB8` | 0xA0 | src/cod/0D4E88 |
| `0x001DAF30` | 0xD0 | src/cod/0D4E88 |
| `0x001DE250` | 0xE8 | src/cod/0DC938 |
| `0x001DE338` | 0xF0 | src/cod/0DC938 |
| `0x001DC998` | 0x130 | src/cod/0DC938 |
| `0x001DE588` | 0x130 | src/cod/0DC938 |
| `0x001DADF0` | 0x140 | src/cod/0D4E88 |
| `0x001DD668` | 0x140 | src/cod/0DC938 |
| `0x001DA360` | 0x158 | src/cod/0D4E88 |
| `0x001DA4B8` | 0x158 | src/cod/0D4E88 |
| `0x001D9CB0` | 0x160 | src/cod/0D4E88 |
| `0x001DE428` | 0x160 | src/cod/0DC938 |
| `0x001DC720` | 0x1B8 | src/cod/0D4E88 |
| `0x001DC558` | 0x1C8 | src/cod/0D4E88 |
| `0x001DED10` | 0x210 | src/cod/0DC938 |
| `0x001DE6B8` | 0x218 | src/cod/0DC938 |
| `0x001DF150` | 0x218 | src/cod/0DC938 |
| `0x001DEF20` | 0x230 | src/cod/0DC938 |
| `0x001D9890` | 0x328 | src/cod/0D4E88 |
| `0x001DE8D0` | 0x440 | src/cod/0DC938 |
| `0x001DC0E8` | 0x470 | src/cod/0D4E88 |
| `0x001DD1F0` | 0x478 | src/cod/0DC938 |
| `0x001D8E40` | 0x4A0 | src/cod/0D4E88 |
| `0x001D9E90` | 0x4D0 | src/cod/0D4E88 |
| `0x001DF368` | 0x558 | src/cod/0DC938 |
| `0x001D92E0` | 0x5B0 | src/cod/0D4E88 |
| `0x001DCAC8` | 0x728 | src/cod/0DC938 |
| … | | _3 more_ |

### src/Texture.c
_text 1/18 (6%) · coal 0/18 · cod 18 · uninsn 2411 · data 89/133_

**uncategorized** (17)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0012BC0C` | 0x4 | src/cod/02BC0C |
| `0x0012C610` | 0xE0 | src/cod/02BC0C |
| `0x0012AED0` | 0xF0 | src/cod/02AA80 |
| `0x0012D370` | 0x130 | src/cod/02BC0C |
| `0x0012D218` | 0x158 | src/cod/02BC0C |
| `0x0012BA68` | 0x180 | src/cod/02AA80 |
| `0x0012BEB0` | 0x1A0 | src/cod/02BC0C |
| `0x0012AFC0` | 0x200 | src/cod/02AA80 |
| `0x0012C6F0` | 0x208 | src/cod/02BC0C |
| `0x0012B850` | 0x218 | src/cod/02AA80 |
| `0x0012C3D0` | 0x240 | src/cod/02BC0C |
| `0x0012C8F8` | 0x278 | src/cod/02BC0C |
| `0x0012BC10` | 0x2A0 | src/cod/02BC0C |
| `0x0012CEF8` | 0x320 | src/cod/02BC0C |
| `0x0012C050` | 0x380 | src/cod/02BC0C |
| `0x0012CB70` | 0x388 | src/cod/02BC0C |
| `0x0012B1C0` | 0x690 | src/cod/02AA80 |

### src/chain.c
_text 1/21 (5%) · coal 0/21 · cod 21 · uninsn 2630 · data 73/85_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x0018DD80` | 0x70 | 28 | 1 | `addiu lw sd sd` |

**uncategorized** (19)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0018DE48` | 0xB8 | src/cod/08DE48 |
| `0x0018D640` | 0xC8 | src/cod/08CFF8 |
| `0x0018D708` | 0xC8 | src/cod/08CFF8 |
| `0x0018DAC8` | 0xC8 | src/cod/08CFF8 |
| `0x0018DF00` | 0xF8 | src/cod/08DE48 |
| `0x0018D3A0` | 0x150 | src/cod/08CFF8 |
| `0x0018D4F0` | 0x150 | src/cod/08CFF8 |
| `0x0018F798` | 0x150 | src/cod/08DE48 |
| `0x0018D7D0` | 0x158 | src/cod/08CFF8 |
| `0x0018EB70` | 0x158 | src/cod/08DE48 |
| `0x0018F640` | 0x158 | src/cod/08DE48 |
| `0x0018F8E8` | 0x188 | src/cod/08DE48 |
| `0x0018DFF8` | 0x190 | src/cod/08DE48 |
| `0x0018D928` | 0x1A0 | src/cod/08CFF8 |
| `0x0018DB90` | 0x1F0 | src/cod/08CFF8 |
| `0x0018D100` | 0x2A0 | src/cod/08CFF8 |
| `0x0018E188` | 0x428 | src/cod/08DE48 |
| `0x0018E5B0` | 0x5C0 | src/cod/08DE48 |
| `0x0018ECC8` | 0x978 | src/cod/08DE48 |

### src/motionOrientManager.c
_text 1/22 (5%) · coal 0/22 · cod 22 · uninsn 3545 · data 185/213_

**1 jal + %gp_rel (D[0] passthrough)** (1)

| vram | size | insns | jal | first mnemonics |
| --- | ---: | ---: | ---: | --- |
| `0x001E3E20` | 0x120 | 71 | 1 | `addiu sd sd sd` |

**uncategorized** (20)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001E237C` | 0x4 | src/cod/0E237C |
| `0x001E3F40` | 0x88 | src/cod/0E237C |
| `0x001E11D0` | 0xD0 | src/cod/0E0C34 |
| `0x001E10F0` | 0xE0 | src/cod/0E0C34 |
| `0x001E1ED8` | 0x100 | src/cod/0E0C34 |
| `0x001E0FE8` | 0x108 | src/cod/0E0C34 |
| `0x001E3D08` | 0x118 | src/cod/0E237C |
| `0x001E3FC8` | 0x1B8 | src/cod/0E237C |
| `0x001E0D50` | 0x298 | src/cod/0E0C34 |
| `0x001E2D68` | 0x2C8 | src/cod/0E237C |
| `0x001E2380` | 0x320 | src/cod/0E237C |
| `0x001E39E8` | 0x320 | src/cod/0E237C |
| `0x001E4180` | 0x340 | src/cod/0E237C |
| `0x001E26A0` | 0x348 | src/cod/0E237C |
| `0x001E1728` | 0x378 | src/cod/0E0C34 |
| `0x001E29E8` | 0x380 | src/cod/0E237C |
| `0x001E1FD8` | 0x398 | src/cod/0E0C34 |
| `0x001E1AA0` | 0x438 | src/cod/0E0C34 |
| `0x001E12A0` | 0x488 | src/cod/0E0C34 |
| `0x001E3030` | 0x9B8 | src/cod/0E237C |

### _unassigned
_text 0/0 (0%) · coal 0/0 · cod 0 · uninsn 0 · data 0/77_

_(nothing pickable in defined buckets)_

### ios/mblock.c
_text 0/1 (0%) · coal 1/1 · cod 0 · uninsn 64 · data 45/45_

**uncategorized** (1)

| vram | size | subseg |
| --- | ---: | --- |
| `0x00135F60` | 0x100 | ios/mblock |

### src/EnemyInit.c
_text 0/1 (0%) · coal 1/1 · cod 0 · uninsn 208 · data 11/32_

**uncategorized** (1)

| vram | size | subseg |
| --- | ---: | --- |
| `0x001FBC48` | 0x340 | src/EnemyInit |

### src/FileManager.c
_text 0/1 (0%) · coal 0/1 · cod 1 · uninsn 458 · data 76/93_

**uncategorized** (1)

| vram | size | subseg |
| --- | ---: | --- |
| `0x0010EE90` | 0x728 | src/cod/00ECE0 |

