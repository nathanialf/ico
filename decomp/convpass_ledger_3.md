# Convergence pass wave 2 — worker 3 ledger

Scope: the 31 TU sets of `convpass_wave2_remainder.json` (289 candidate
funcs, up to 607 insns).  Step 0 (skip anything already matched) leaves
**246 funcs in 30 TU sets** actually needing work.

Method per function: mechanical `tools/port_from_aug6.py port --only <f>`
first; on a `[codegen]` revert, splice the rebound aug6 body in anyway
(`tools/convpass_try.sh`), work out *what the retail dev changed after
Aug 6* from the asm diff, and write that C.  No crutches, no per-func
flags, no yaml/carve edits.

## Tooling added (worker 3)

| tool | does |
|---|---|
| `tools/convpass_batch.sh <tu> <f>…` | mechanical-port a list of funcs, print PORTED/FAILED + ledger reason |
| `tools/convpass_try.sh <tu> <f>` | same for one func, but on a codegen revert **splices the body anyway** from `PORT_DEBUG_DUMP` so it can be hand-converged |
| `tools/convpass_rd.sh <stem> <f>` | real diff count — re-diffs quick_diff's own two canonical streams with the four coalesced-TU tolerances applied |
| `tools/convpass_bump.py <file> A=B …` | **simultaneous** hex-constant rewrite (id-family bumps chain: `0x12A→0x12B` and `0x12B→0x12C` in the same TU) |

`convpass_rd.sh` exists because a plain `grep '|'` over `quick_diff`'s
`diff -y` output is a **false negative**: when the two streams realign,
real differences print as `<` / `>` add/delete pairs, not `|` changes.
That cost one `ninja` MISMATCH (`actSt04eWaterSwitch`, two missed
`0xE4→0xE5` bumps that `quick_diff | grep '|'` reported as clean).
Always gate on `ninja`.

## Systematic retail-vs-aug6 edit patterns (worker 3 additions)

Wave-1's list still holds (gobj+0x15C sub-struct +0x10; camera stride
0x190→0x194; `__LINE__` drift).  New ones, all confirmed by byte match:

1. **Actor "next script" slot `0xB4 → 0xC4`.**  The `gobj->unkB4 = D_…`
   BoxBar/actStXX wrapper family (see `boxbar_wrapper_family`) stores at
   `+0xC4` in retail.  Same +0x10 insertion as the `0x7F0→0x800` family,
   one level up.  `sw v0,180(sX)` → `sw v0,196(sX)` is the signature.
2. **BG-animation ids +1.**  `stage_KillPlayBgAnimation(id,…)` /
   `func_0012AA80(id)` / `func_0017B288(id)`: `0xE1→0xE2`, `0xE3→0xE4`,
   `0xE4→0xE5`, `0x10E→0x10F`, `0x12A→0x12B` … `0x139→0x13A`,
   `0x164→0x165`.  One animation was inserted low in the table.
3. **Scene-object layout ids +4.**  The argument to
   `actSt25aQueenDeadChk` / object-lookup helpers: `0x4F8→0x4FC`,
   `0x4FC→0x500`, `0x4FD→0x501`.
4. **`BoxBarSoundOn` se id `0x189 → 0x18D`** (+4, same family as 3).
5. **GObj kind/layout table sentinels +1.**  `isysGObj*`:
   `(unsigned)(kind-1) < 0x42` → `< 0x43`, and the `isysGObjRemove`
   variant `0x43 → 0x44`.  The kind table grew by one entry.
6. **aug6 scalar externs that retail's link made "far".**  `-G8`: an
   `extern int D_00557A10;` that compiled to `lw a0,0(gp)` in the aug6
   twin must be respelled `extern char D_00557A10[];` so it emits
   `lui/addiu %hi/%lo` (see `extern_size` / `d_extern`).  Signature:
   ROM has an extra callee-saved reg + `addiu sX,vY,%lo(sym)` where the
   build has `lw a0,0(gp)`; the port driver reports it as
   `[§frame-size] prologue sp delta differs`.

## Log

Legend: `MATCHED` (byte-identical, `ninja` verified, committed) ·
`pass-deferred` (budget spent, reverted to `INCLUDE_ASM`).

### batch 1 — TU sets 1-6

| TU | func | result | note |
|---|---|---|---|
| src/StageManager | stgmgrNextStagePreLoad | MATCHED | pattern: camera/stage pre-load record stride 400→404 |
| isys/gobj | isysGObjSearchFromObjLayoutID | MATCHED | pattern 5 (`0x42→0x43`) |
| isys/gobj | isysGObjKindTableAdd | MATCHED | pattern 6 + pattern 5 |
| isys/gobj | isysGObjRemove | MATCHED | pattern 5 (`0x43→0x44`) |
| isys/gobj | isysGObjAlloc | MATCHED | pattern 6 + pattern 5 |
| isys/gobj | cut_gobj_link | MATCHED | pattern 6 + pattern 5 |
| src/st04e | actSt04eWater | MATCHED | patterns 1, 2 (`0xE1→0xE2`), 4 |
| src/st04e | actSt04eWaterSwitch | MATCHED | patterns 1, 2 (`0xE3→0xE4`, `0xE4→0xE5`), 4 |
| src/st04e | actSt04eWaterFlagOn | pass-deferred | rc2. Identical source to its matched sibling `actSt04eWater` (only the `scpKillSpiderGroup` test polarity differs) yet the two `%hi` pseudos land in s4/s5 swapped. 12 shapes tried (store order, `int*` temp, `int` temp, `char*` address form, hoisted decl, non-volatile callee decl): store-swap fixes s4/s5 but flips the v0/v1 `%lo` temps; no shape gets both. NOT a floor — needs the allocno-priority reasoning, not another spelling. |
| sound/s_init | soundDataOpenChk | MATCHED | `__LINE__` `0xE6→0xFE` |
| sound/s_init | soundDataClose | MATCHED | `__LINE__` `0x254/0x257/0x25D → 0x261/0x264/0x26A` |
| sound/s_init | soundDataOpen | MATCHED | `__LINE__` `0x1CC/0x1D6/0x1DB → 0x1D8/0x1E2/0x1E7` |
| sound/s_init | soundSQDataSet | MATCHED | `__LINE__` `0x142→0x14E` |
| sound/s_init | soundSeDefPlay | MATCHED | `__LINE__` `0x142→0x14E` |
| sound/s_init | soundSeVolSet | pass-deferred | no aug6 twin body: `soundSeVolSet` is a **parked tough-nut on the aug6 side** (`tough_nuts/soundSeVolSet/`), so there is nothing to port. Needs a normal grind, not a convergence pass. |
| src/st09a | actSt09aIntro | MATCHED | pattern 3 |
| src/st09a | actSt09aElv | MATCHED | pattern 2 |
| src/st09a | actSt09aElvSwitch | MATCHED | patterns 1, 4 |
| src/st09a | actSt09aElvUp | MATCHED | patterns 1, 4 |
| src/st09a | actSt09aBrg | MATCHED | patterns 1, 2, 3, 4 |
| src/st09a | actSt09aElvMain | MATCHED | patterns 1, 2, 3, 4 |
| src/st09a | actSt09aElvDown | MATCHED | pattern 2 |
| src/st09a | actSt09aSekizo | MATCHED | patterns 2, 3 |
| src/st09a | actSt09aBrgDown | MATCHED | patterns 2, 3 |
| src/cage | HotInitCageGeo | MATCHED | wave-1 pattern `0x7F0→0x800` |
| src/cage | InitCageGeo | MATCHED | `0x7F0→0x800` |
| src/cage | CageDL | MATCHED | `0x7F0→0x800` |

**batch 1: 25 MATCHED, 2 pass-deferred.**

## The `provisional-ordinal` mis-naming class (worker 3, found in batch 2)

`src/st18a.c` came back with five `divergent` port candidates whose aug6 and
retail instruction counts disagreed wildly (90 vs 55, 57 vs 94, …).  The
cause was not divergent source: **wave 1's ordinal name assignment had
slipped by one function** for the whole tail of the TU.  Retail inserts,
deletes and moves functions inside a TU; the moment it does, every later
`provisional-ordinal` name in that TU is attached to the wrong body, and the
port driver then compares unrelated functions.

`tools/convpass_ordinal.py <retail-tu> <aug6-stem> [--extra <stem>…]`
re-derives the mapping from the code: it blanks every reloc-bearing immediate
(j/jal targets, `lui` %hi, the imm16 of loads/stores/addiu) and scores each
retail function against every matched aug6 body.  Self-scores land at 1.00;
a mis-assignment shows as a ~1.00 score on a *different* name.

For `src/st18a.c` the corrected mapping (all confirmed by an independent
reloc check — e.g. the ROM body at 0x231098 takes `%hi(actSt18aSwitchL)`,
which is `actSt18aEneChk`'s callee, not `actSt18aEne2Chk`'s):

| vma | wave-1 name | correct name |
|---|---|---|
| 0x00230B38 | actSt18aEne2 | **actSt19aPipeXL** (moved into this TU, 56→63 insns) |
| 0x00230C38 | actSt18aEnemy2_2 | actSt18aEne2 |
| 0x00230D18 | actSt18aCamera | actSt18aEnemy2_2 (90→94) |
| 0x00230E90 | actSt18aIntroChk | actSt18aCamera |
| 0x00230F78 | actSt18aEneChk | actSt18aIntroChk |
| 0x00231098 | actSt18aEne2Chk | actSt18aEneChk |
| 0x00231130 | func_00231130 | actSt18aEne2Chk |

After the rename all 9 of the TU's candidates matched, including two that
needed a genuine retail source edit (see the log).  **Any TU whose port
candidates come back `divergent` + `insert/delete-block` should be run
through `convpass_ordinal.py` before being written off.**  `src/girl_act.c`
and `src/st20a.c` were audited the same way and their names are correct, so
this is not universal — but it is not rare either.

### batch 2 — TU sets 7-13

| TU | func | result | note |
|---|---|---|---|
| src/st18a | actSt18aEne | MATCHED | patterns 1, 4 |
| src/st18a | actSt18aEnemy1_2 | MATCHED | patterns 1, 4 |
| src/st18a | actSt19aPipeXL | MATCHED | renamed; retail inserts `while (scpTriggerBallTargetMan(D_00633AB0) == 0) _ACTWait(1);` before the last `scpPlayStart` |
| src/st18a | actSt18aEne2 | MATCHED | renamed; anim id `0x2AF→0x2B0` |
| src/st18a | actSt18aEnemy2_2 | MATCHED | renamed; retail inserts `func_0017C9B0(3);` after the `scpPlayStart` wait loop |
| src/st18a | actSt18aCamera | MATCHED | renamed; `0x127→0x128`, pattern 4 |
| src/st18a | actSt18aIntroChk | MATCHED | renamed; `0x127→0x128` |
| src/st18a | actSt18aEneChk | MATCHED | renamed; `0xB→0xA`, `0x21→0x20` were really the EneChk-vs-Ene2Chk difference, i.e. artifacts of the wrong name |
| src/st18a | actSt18aEne2Chk | MATCHED | renamed (was `func_00231130`); `extern int f;` → `extern void f();` so the callee address is `%hi/%lo`, not a `lw` of its first word |
| src/Basic | dma_init | MATCHED | `Sub15C.p_7F0` is at **0x800** in retail; spelled locally (`*(Obj7F0 **)((char *)GOBJ_SUB(g) + 0x800)`) rather than editing the shared `include/ico/types.h`, which the other retail TUs still index at the aug6 offsets |
| src/girl_act | actGirlDitch3mReady | MATCHED | root-matrix slot `0x3B0→0x3D0`, se ids +3 |
| src/girl_act | actGirlAttack | pass-deferred | rc15, all cascade from **4 spurious hazard nops**. gcc's `.s` is structurally identical to ROM (`mtc1 $0,$f0; c.lt.s; bc1f`), but the assembler inserts a COP1-move hazard nop. `tools/compile_c.sh`'s Case-2 `mtc1`+`c.lt.s` `.set noreorder` wrap explicitly **excludes** the case where a `bc1` follows the compare — this function is exactly that case. Fix belongs in the always-on assembler-parity rewrite, not in the C. |
| src/girl_act | actGirlJump | pass-deferred | genuine rewrite: aug6 30 insns → retail 76. Ordinal audit confirms the name is right. |
| src/st20a | actSt20aExit/Ene/BridgeMain/BridgeSwitch/GondolaMain/GondolaSwitch/Enemy1/Init/GondolaUp/GondolaDown | MATCHED (10) | struct slot pair `0xB0/0xB4 → 0xC0/0xC4`; anim ids +1 (incl. the whole `0x229…0x22D` chain); pattern 4 |
| src/st20a | actSt20aElv | MATCHED | hand-written: retail drops the outer `if (func_0017B230(0x15) == 0)` guard around `AddPluralCameraSet(0x25)` |
| src/st01b | actSt01bEnemy1/Enemy5/WayOffChk/FloorChk/Init | MATCHED (5) | pattern 1, anim ids +1, pattern 4 |
| src/deja | actDejaChk / actDejaAfterChk / actDeja | MATCHED (3) | pattern 1, ids +1 (`0x143→0x144`, the `0x20A…0x216`/`0x228` bg-anim block), pattern 4 |
| src/motionManager | _checkCliffAndWall | MATCHED | motion record `p[112]→p[116]` (+0x10) |
| src/motionManager | checkCliffAndWallStateAtJump | MATCHED | `p[104..106]→p[108..110]` |
| src/motionManager | checkCliffState | MATCHED | `+0x120 → +0x130` |
| src/motionManager | SkelTest | MATCHED | clean mechanical port |

**batch 2: 30 MATCHED, 2 pass-deferred.**

## Pattern refinements (batch 3)

7. **Bg-animation ids +1, but gameplay-flag ids UNCHANGED.**  The `+1` bump
   applies to `stage_KillPlayBgAnimation(id,…)`, `stage_DispBgAnimation`,
   `func_0012AA80(id)`, `func_0017B288(id)`.  It does **not** apply to
   `func_0017B230(id)` / `func_0017B258(id)` — those are the gflag test/set
   pair and their ids are unchanged.  Bumping the whole numeric range blind
   (as `convpass_bump.py` does) therefore over-shoots and must be un-bumped
   for those two callees; `src/st04r.c` needed exactly that (23 un-bumps).
8. **Whole `Sub15C`/motion-record offset family +0x10** — much wider than the
   wave-1 list: `0x100→0x110`, `0x104→0x114`, `0x108→0x118`, `0x110→0x120`,
   `0x130→0x140`, `0x170→0x180`, `0x410→0x420`, `0x460→0x470`, `0x490→0x4A0`,
   `0x5E4→0x5F4`, `0x624→0x634`, `0x650/0x660/0x664/0x668 → 0x660/0x670/…`,
   `0x77C→0x78C`, `0x780→0x790`, `0x7CC→0x7DC`, `0x7F0→0x800`, `0x830→0x840`,
   plus the float-array index form (`p[104]→p[108]`, `p[112]→p[116]`).
9. **Motion node-list sentinel `0x43F → 0x43D`** (list shrank by 2) and
   **`0x440 → 0x43E`**.
10. **`BoxBarSoundOn`'s own body**: the two ids it special-cases went
   `0xA6/0xAB → 0xA8/0xAD`, the two it substitutes `0xA7/0xA8 → 0xA9/0xAA`,
   and the **two flag bits it tests moved up one**: `>>60 → >>61`,
   `>>58 → >>59` (`dsrl32 …,0x1c → 0x1d`, `0x1a → 0x1b`).

### batch 3 — TU sets 14-18

| TU | func | result | note |
|---|---|---|---|
| src/st04r | 21 funcs (all) | MATCHED (21) | pattern 1, bg-anim ids +1 with the pattern-7 gflag carve-out, object ids +3, pattern 4 |
| src/way_tool | debug_WayTool | pass-deferred | genuine rewrite: aug6 31 insns → retail 119. A debug tool that grew four-fold; nothing to converge. |
| src/st47a | 12 funcs (all) | MATCHED (12) | pattern 1, ids +1 (`0x64…0x67`, `0x2CA…0x2D3`), pattern 4, one `_ACTWait(0x3C)→_ACTWait(0x32)` |
| src/commonact | 13 funcs (all) | MATCHED (13) | pattern 8 offsets, patterns 6/9/10; `motCommonRopeTurnL` also needed `BoxBarSoundOn` arg `0xB4→0xB7` / `0x68→0x69` |
| src/motionOrientManager | 8 funcs (all) | MATCHED (8) | pattern 8 offsets, pattern 9 (`xori 0x43F→0x43D`), pattern 6 on three assert-message globals |

**batch 3: 54 MATCHED, 1 pass-deferred.**

### batch 4 — TU sets 19-21

Pattern-7 caveat, refined again: whether the `func_0017B230`/`func_0017B258`
**gflag** ids move is *per stage script*, not global — `src/st04r.c` and
`src/st04l.c` need them left alone while `src/e3.c` needs them bumped +1.
Determine empirically from the diff, do not assume.  Likewise the *second*
argument of `func_0012AB50(anim, frame, 0)` is a frame number, not an id, and
never moves.

| TU | func | result | note |
|---|---|---|---|
| src/e3 | 18 funcs (all) | MATCHED (18) | pattern 1; ids +1 across `0x133…0x14B`, `0x1E2…0x1E9`, `0x2E3…0x308`, `0x31F/0x320`; the `actSt25aQueenDeadChk` object ids +29 (`0x8E6→0x903`, `0x8E7→0x904`, `0x989→0x9A6`); the `gflagOff(actSt25aQueenDeadChk(...), id)` **second** arg went −2 while the animation ids went +1 — two different id spaces in one call. `WpData16 D_0061B810` had to be re-typed (the port driver emitted `extern int`). |
| src/BgAnimation | 5 funcs (all) | MATCHED (5) | the aug6 TU's `SDF_*` accessor macros are **not carried by the port driver** (they live in the aug6 file's header block) — re-added verbatim; then `__LINE__` drift only (`0x383→0x3E4`, `0x8D2→0x9D5`, `0x8DA→0x9DD`, `0x8F3→0x9F7`) |
| src/st04l | 18 funcs (all) | MATCHED (18) | pattern 1, anim ids +1 with the gflag carve-out, object ids +3, pattern 4 |

**batch 4: 41 MATCHED, 0 pass-deferred.**

### batch 5 — TU sets 22-24

| TU | func | result | note |
|---|---|---|---|
| src/st05e | 7 funcs (all) | MATCHED (7) | pattern 1; the `0x113…0x13C` anim family +1 while the neighbouring `0xBE…0xEB` family does **not** move; object ids +4/+6 (`0x514→0x518`, `0x560→0x566`) |
| src/st02a | 8 of 10 | MATCHED (8) | pattern 1, ids +1 |
| src/st02a | actSt02aEne, actSt02aSekizo | pass-deferred | rc6 each — **the same mechanism as `src/st04e actSt04eWaterFlagOn`** (third and fourth instance): the tail `D_x[1] = (int)f; obj->unkC4 = D_x;` puts the two `%hi` pseudos in the wrong pair of callee-saved registers, while a byte-identical sibling in the same TU (`actSt02aBoxEvent2`) matches with the identical source. Store-order swap moves the error from the `sN` pair to the `v0/v1` `%lo` pair and back; `int*`/`void*[]` temps, `do{}while(0)`, `char*` store form, and an `__asm__`-aliased forward decl all leave it at rc6. This is one gcc allocno-priority tie, worth solving once — it would land 3 functions. |
| src/enemy_act | 8 funcs (all) | MATCHED (8) | pattern 8 offsets (`0x100→0x110`, `0x400→0x420`, `0x490→0x4A0`), `__LINE__` +18, se ids +3. The port driver's per-function splices **collided** in this TU (dropped `D_00632398`, duplicated `func_001AD768`/`func_00263FF0` with conflicting types) — dedupe the declaration block by hand before believing a rc0. |

**batch 5: 23 MATCHED, 2 pass-deferred.**

### batch 6 — TU sets 25-26

Two more pattern refinements, both learned the hard way in these TUs:

11. **The id bump is POSITIONAL, not numeric.**  Only the *animation
    argument* moves: arg 1 of `stage_KillPlayBgAnimation` / `func_0012AA80` /
    `func_0012AB50` / args 1-2 of `stage_DispBgAnimation`.  The other
    arguments of the same calls are **frame numbers** and never move — in
    `src/st06a.c` the literal `0xC8` appears as both (`func_0012AB50(0xC8,
    0xC8, 1)` → `(0xC9, 0xC8, 1)`).  A whole-file numeric bump is a fast
    first approximation but must then be corrected per call site.
12. **`gflagOff(actSt25aQueenDeadChk(objid), gflagid)` mixes two id spaces
    in one call**: the object id moves **+24…+29** (`0x77C→0x794`,
    `0x7FA→0x813`, `0x8E7→0x904`, `0x9FC→0xA19`, `0x989→0x9A6`) while the
    gflag id moves **−2**.  Both `src/e3.c` and `src/end.c` need the scoped
    regex, not a numeric range.

| TU | func | result | note |
|---|---|---|---|
| src/st06a | 22 funcs (all) | MATCHED (22) | pattern 1, positional anim-id +1 (pattern 11), object ids +4/+6, pattern 4 |
| src/end | 17 funcs (all) | MATCHED (17) | pattern 1; anim ids +1 for `0x123…0x152`/`0x1D0…`/`0x20A…0x319` but **not** `0xFF`, `0x11A…0x122`, `0x141…0x147`, `0x14F…0x152`, `0x1B8…0x1CF`; pattern 12 |

**batch 6: 39 MATCHED, 0 pass-deferred.**

### batch 7 — TU sets 27-29

Two hazards this batch, both worth knowing:

13. **`convpass_bump.py` is whole-file and will silently corrupt an
    already-matched sibling.**  In `src/boyact.c` a blanket `0x140→0x150`
    hit `func_00154668`, a function matched long before this pass; the
    per-function `quick_diff`s all read rc0 and only the full `ninja`
    (one differing word) caught it.  After every bump, check
    `git diff HEAD -- <tu>` for changed lines that are *not* inside the
    bodies you spliced.
14. **A carried gcc *nested* function must have its `INCLUDE_ASM` deleted.**
    `BoyBgaManager` carries `void UpdateGeo(Geo *e) {…}` nested inside it;
    the retail TU still had `INCLUDE_ASM(..., UpdateGeo)`, so the object
    ended up with two copies (the nested one is local, so the linker does
    not complain) and `.text` grew 0x160 — shifting the whole image while
    every per-function diff stayed clean.  Also: the driver's reloc walk
    does **not** cover a nested function's body, so its callees come back
    bound to garbage (`func_0023FFF0`, `D_00628E24`); rebind them by hand
    from the nested function's own `.s` (`func_001947D0`, `func_00243B18`,
    `func_0014B660`, `func_00243AD0`, `func_001945B8`, `D_00630B28`).

| TU | func | result | note |
|---|---|---|---|
| src/act | actInitialize | MATCHED | pattern 8 offsets (`0xB0…0x150` +0x10); the four Cond flag bits moved (`0x200→0x1000`, `0x400→0x2000`, `0x2000→0x10000`, `0x80000→0x4000000`); `__LINE__` `0x37C→0x382` (careful: `0x37C` is *also* a struct offset in the same body and does **not** move) |
| ios/memory | iosMallocCheckLeak2 | MATCHED | `__LINE__` +0x10 (`0x324→0x334`, `0x379→0x389`, `0x3B2→0x3C2`, `0x3B5→0x3C5`, `0x3BF→0x3CF`); also had to re-declare the forward `iosMallocCheckLeak2` prototype to `void *(void *)` |
| src/boyact | 14 funcs (all) | MATCHED (14) | pattern 8 offsets (`0x100/0x104/0x108`, `0x130/0x134/0x140`, `0x1B0/0x1B8`, `0xF0→0x100`), `__LINE__` `0x5D5→0x607`, anim id `0x15B→0x15C`; plus hazards 13 and 14 above |

**batch 7: 16 MATCHED, 0 pass-deferred.**

### batch 8 — TU set 30

| TU | func | result | note |
|---|---|---|---|
| src/pool | 8 funcs (all) | MATCHED (8) | `0x170→0x180`, `0x178→0x188` (pattern 8); everything else was a clean mechanical port |

**batch 8: 8 MATCHED, 0 pass-deferred.**

---

## CORRECTION — accurate final accounting

**The per-batch "MATCHED" counts above over-count.**  `tools/convpass_try.sh`
originally invoked `port_from_aug6.py port` with the driver's default wave
set (1,2,3).  Every **wave-0 (`divergent`) candidate in my TUs was therefore
silently skipped** — and a function that is still `INCLUDE_ASM` assembles the
ROM baseline *into its own object*, so `quick_diff` compares the baseline
against itself and reports a meaningless `real_count=0`.  I read those as
matches.

Both holes are now closed:

* `convpass_try.sh` / `convpass_batch.sh` pass `--waves 0,1,2,3`.
* `convpass_rd.sh` **refuses to report a diff count** for a function whose TU
  still carries its `INCLUDE_ASM` line; it prints `NOT-IMPLEMENTED` and exits 3.

Everything that *is* reported as MATCHED below the line is real: the tree is
`ninja`-green at `fbf50c75cd5911273511c4f9af90503ff8423582` and a function
that were not actually replaced would still be `INCLUDE_ASM`, which the audit
now enumerates.

### Real totals for this pass

| | count |
|---|---|
| assigned, still `INCLUDE_ASM` at start | 246 |
| **MATCHED (byte-identical, committed)** | **195** |
| remaining | 51 |

### The 51 remaining, by why

| class | n | funcs |
|---|---|---|
| `unresolved-symbol` — the driver's reloc walk cannot bind one slot, so there is no spliceable body; needs the aug6 body transcribed and its symbols bound by hand | 20 | st04l: Brg1Chk, Rope3Chk, Rope4Chk, Brg2Chk, SekizoChk, GondolaChk, Monyou01Chk, actSt04dInit · st06a: Init, Suimon, SuimonChk, Door, DoorUpChk · st02a: DoorUpEffect, DoorEvent · boyact: ditch_check_heroin_position, actBoyPullupReady, actBoyPullupGo, CheckCollisionAttr · end: actEndDemo11 · BgAnimation: bga_InitSdfCamera, bga_calcEnvelope |
| `no-aug6-twin` — the aug6 side has no matched body (it is `INCLUDE_ASM` or a parked tough-nut there), so there is nothing to port | 8 | soundSeVolSet · pool: GetPoolGlobalHeightDetail, CheckPoolHasGridMesh, SetLayoutedPoolReflactionMesh, poolRideFunc, DispLimitedPoolReflactionMesh, GetPoolGlobalHeight, PoolGeo |
| `rewritten` — retail expanded the function well beyond the aug6 body (2×–25× the instruction count); a normal matching grind, not a convergence pass | 15 | girl_act: actGirlJump (28→75) · way_tool: debug_WayTool (30→119) · commonact: _ACTCommonMailTest (7→27), ContinueCorrectPosition (38→47), actCommonEdgeHang (30→149) · e3: actE3CageFallChk (13→36) · BgAnimation: bga_resetObjectCounter (129→153) · st02a: actSt02aSecretItem (80→188) · enemy_act: funcEnemyAiGetGirl (16→79), actEnemy_isLargeEnemy (23→218) · end: actEndDemo05 (38→42) · boyact: actBoyTakeWeaponReady (25→40), actBoySupportGBBegin (10→74), pullup_check_heroin_position (15→381), hand_heroin (66→426) · motionManager: SkelTest (89→109) |
| `jtbl-deferred` — needs a Phase-5 jump-table rodata carve | 1 | motionOrientManager: shiftMotionOrientEndFunc |
| `pass-deferred` — hand-converged to a small residual, budget spent | 4 | st04e: actSt04eWaterFlagOn (rc2) · girl_act: actGirlAttack (rc15, all 4 spurious hazard nops) · st02a: actSt02aEne (rc6), actSt02aSekizo (rc6) |
| **also landed after the correction** | +1 | e3: actE3CapsuleDemo — retail inserts `func_001F0DA8()` and the object id moves `0xC19→0xC37` |

The four `pass-deferred` entries are **not floors** — the three
`actSt04eWaterFlagOn` / `actSt02aEne` / `actSt02aSekizo` residuals are one and
the same gcc allocno-priority tie (see batch 5), and `actGirlAttack` is an
assembler-parity gap in `tools/compile_c.sh`, not a source-shape problem.

---

# conv-4 remainder pass (worker 4, branch `conv-4` off `39aa70a2`)

Scope: the 20 `unresolved-symbol` + 15 `rewritten` + 4 `pass-deferred`
entries of the CORRECTION table above, plus the 20 open entries of
`decomp/convpass_ledger_2.md`.  **39 matched**, every batch gated on a full
`build.sh setup && ninja` → `verify_elf: OK (…fbf50c75…)`.

## Tooling

| change | why |
|---|---|
| `tools/port_from_aug6.py`: `PORT_LENIENT=1` | downgrades an unbindable reloc slot from an abort to a stderr warning so `PORT_DEBUG_DUMP` still writes the candidate TU with every slot the walk *could* bind already rebound. The remaining symbols keep their aug6 names and are bound by hand against the retail `.s`. Off by default; the driver's own accept/revert path and the ledger classification are unchanged. **This is the single tool that unlocks the whole `unresolved-symbol` class.** |

Operational note: `retail_defined_labels()` caches to
`.port_cache/retail_labels.json`.  After adding a symbol to
`config/symbol_addrs.us.txt` you must `rm` that cache or the driver still
reports `retail symbol func_XXXXXXXX undefined`.

`tools/compile_c.sh` was **not** changed — see `actGirlAttack` below.

## Corrections to the ledger-3 CORRECTION table

1. **`actGirlAttack` is not an assembler-parity gap.**  The rc15 /
   "4 spurious COP1-hazard nops" diagnosis is stale: worker 2's
   `tools/preprocess_old_as.py` `%gp_rel(SYM + N)` fix (ledger 2, batch 3)
   put `src/girl_act.c` back on the period assembler, so the nops are gone.
   The real residual was five BoxBar se ids (`0xFA…0xFE → 0xFD…0x101`).
   MATCHED with no `compile_c.sh` edit.  The Case-2 `mtc1`+`c.lt.s` wrap's
   `bc1`-follows exclusion is therefore still unexercised — do **not**
   widen it speculatively; there is no function that needs it.
2. **`bga_calcEnvelope` is `rewritten`, not `unresolved-symbol`.**  aug6 13
   insns → retail 180, and the retail body is a hand-VU0 macro-mode
   envelope/quaternion block (`vmulax`/`vmadd*`/`qmtc2.ni`).  Fresh work.
3. **`stage_SetScale` is `rewritten`, not `unresolved-symbol`** (aug6 3
   insns → retail 32) — and it MATCHED anyway (see below).

## New systematic retail-vs-aug6 edit patterns

15. **The `actStXXChk` "spider-group wait" template lost its two
    `gflagOff` calls and gained an `ACTEnvGetTest()` arm.**  All 12
    st04l/st06a `unresolved-symbol` functions are one 85-insn template:
    the aug6 tail `D_x=1; gflagOff(A,0); gflagOff(B,0x202); f(id);` became
    `D_x=1; func_0017B258(id);` followed by
    `if (ACTEnvGetTest()) { func_0017B528(A); func_0017B528(B);
    BoySekikaTexScroll(A,1); BoySekikaTexScroll(B,1); _ACTWait(1);
    GetTarget(); }`, and the closing `iosOmBeforeFuncStandard` is likewise
    guarded by a second `ACTEnvGetTest()`.  Deleting the two `gflagOff`s is
    exactly what desynchronised the port driver's alignment at insn 21 and
    produced the whole `insn 21 D_00629DE4: no aligned retail slot` class.
16. **`actSt25aQueenDead`'s 3rd argument went `D_00631AE8` → `0`** in
    `actSt04dInit` and `actSt05cDoorDownEvent`.  Signature of the
    `retail slot is not $gp-based` revert reason.
17. **Act-object status word `0xC0 → 0xD0`** (the `& 0x10` "motion done"
    poll word) — same +0x10 family as pattern 8, one level up from the
    `0xB0/0xB4 → 0xC0/0xC4` handler slots.
18. **`extern int D_x` → `extern char D_x[]` is needed for assert-message
    globals too** (`jimakuHandler`'s `D_005594A0`).  Signature: built has
    `lw a0,0(gp)` where ROM has `lui/addiu %hi/%lo`, and the built
    function is 1 insn short.

## More splat-merge carves (`config/symbol_addrs.us.txt`)

Every entry added is `// type:func  // <tu>  // provisional-ordinal`:

| new symbol | carved out of | status |
|---|---|---|
| `func_00154070` | `ditch_check_heroin_position` (src/boyact.c) | **matched** |
| `func_00154128` | `actBoyPullupReady` (src/boyact.c) | **matched** |
| `func_001541E0` | `actBoyPullupGo` (src/boyact.c) | **matched** |
| `func_00175B18` | `jimakuHandler` (src/jimaku.c) | **matched** |
| `func_00211EC8` | `actSt02aSecretItem` (src/st02a.c) | carved, INCLUDE_ASM only |

`func_00211EC8` (78 insns, a linear `actSt25aQueenDeadChk` /
`func_001E8EA8` / `func_0017EA50` / `func_001BFFE8` sequence with two
callee-saved FPRs) is fresh decomp — it has no aug6 twin.  It is the last
half of the 3 remaining carved-but-unwritten halves.

## Log

| TU | func(s) | result | note |
|---|---|---|---|
| src/st04l | actSt04lBrg1Chk, Rope3Chk, Rope4Chk, Brg2Chk, SekizoChk, GondolaChk, Monyou01Chk | MATCHED (7) | pattern 15; per-func (gflag, anim, spider-mask) = (0xC0,0xCE,0x1000000) … (0xC6,0xD4,0x7000000) |
| src/st04l | actSt04dInit | MATCHED | pattern 16; `0x3FF/0x400→0x402/0x403`, `0xDF→0xE0`, `0xB0→0xB1` |
| src/st06a | actSt06aInit, Suimon, SuimonChk, Door, DoorUpChk | MATCHED (5) | pattern 15; (0xFB…0xFF, 0x132…0x136, 0x3000000…0x7000000) |
| src/st02a | actSt02aDoorEvent, actSt02aDoorUpEffect | MATCHED (2) | retail inserts `lt_fade_status(0x32); D_006325B4 = 0; scpActivateAllWithKind();` before the BoxBar tail; anim `0x56→0x57`, patterns 1/4 |
| src/end | actEndDemo11 | MATCHED | retail inserts `actBoyRescueReady();` |
| src/BgAnimation | bga_InitSdfCamera | MATCHED | retail adds the `if (a2 == 1) { D_006319F0 = a2; mc_TransMicroCode(D_00710C20, D_00710C10); }` arm |
| src/boyact | CheckCollisionAttr | MATCHED | pure rebind + Sub15C `0x550→0x560`; the aug6 union alias `D_006A45A0u __asm__("D_006A45A0")` is **not** carried by the driver — re-add it renamed |
| src/boyact | ditch_check_heroin_position, actBoyPullupReady, actBoyPullupGo + the 3 carved halves | MATCHED (6) | pattern 17 (`0xC0→0xD0`), BoxBar se `0x58/0x5D/0x62 → 0x59/0x5E/0x63` |
| src/act_bird | subBirdBrainMain | MATCHED | retail drops the dead `void *p = a0;` re-read |
| src/act_bird | func_00197198 (= aug6 `subBirdBrainSub`), func_001971C0 (= aug6 `BirdBrainMain`) | MATCHED (2) | `ExecMotionOrient` anim `0xEC→0xEE`, slot `0x110→0x120`; **`actInitialize(a0)` retires the aug6 `__asm__("" :: "r"(a0))` s0/s1 pin — crutch-free** |
| src/st03t | actSt03tSwitchR | MATCHED | needed the `func_00211EC8` carve first; `0x189→0x18D`, object id `0x60C→0x61A` |
| src/st03t | actSt03tGirlCamStartChk | MATCHED | retail drops `D_x = 0` and moves the handler slot `0xB0→0xC0` |
| src/girl_act | actGirlAttack | MATCHED | see correction 1 |
| src/st04a | actSt04aGateLChk | MATCHED | retail gives the `0x52` test both arms (`AddWayPointTop(7,1)` / `(7,0)`) |
| src/st05c | actSt05cDoorDown | MATCHED | retail inserts `gflagOff(D,0);` + `if (ACTGame_ConnectHand(D)==0) WeaponGeo(func_001538F8());`, gflag `0x163→0x164` |
| src/st05c | actSt05cDoorDownEvent | MATCHED | anim `0x102→0x103`, pattern 16 |
| src/itou_boss | BossEnemyFunc | MATCHED | retail zeroes `GOBJ_SUB(o)+0x74` inside the collision loop |
| src/way_util | GetWgAll | MATCHED | alloc sizes `0x41→0x5F`, `0x4000→0x8A10`, `0x104→0x17C` ×4, `0x100→0x178`; fill loop `for (i=0;i<0x5E;i++) q[i] = p->f4 + i*0x178;` (was `i<0x40`, `i<<8`) |
| src/jimaku | jimakuHandler, func_00175B18 | MATCHED (2) | pattern 17, pattern 18, BoxBar se `0x5D→0x5E` |
| src/st13b2 | actSt13b2Generator | MATCHED | retail saves/restores `D_00632110` around the `actConte11` block; ids `0x12F…0x132→0x130…0x133`, `0x59→0x5A`, `0x165/0xD57→0x166/0xD7D` |
| src/StageAnimation | stage_SetScale | MATCHED | **rewritten, matched anyway**: the aug6 2-store stub became a full `isysGObjRemoveObjDL`/`func_0013ECF8` gobj walk clearing bit 26 of `x+0x30`; mirrors the matched sibling `stage_CalcAnimationParent`, and the function takes an `int a0` it forwards |

## The two-allocno `%hi` tie — mechanism now PROVEN, still open

`actSt04eWaterFlagOn` (rc2/rc9), `actSt02aEne` (rc6), `actSt02aSekizo`
(rc9), `actSt05dDoor2UpChk` (rc4/rc7) and now `actSt03tWayOffChk` (rc6) are
**one and the same** residual: the two `%hi` pseudos of the BoxBar tail

```c
D_x[1] = (int)handler;
gobj->unkC4 = D_x;
```

land in the two callee-saved registers **swapped** relative to ROM.  Every
one of them is otherwise byte-identical, and the *emission order* of the
two `lui`s already matches ROM — only the register numbers are exchanged.

New this pass: a decisive experiment.  Inserting a self-store
`D_x[0] = D_x[0];` before the pair (which gcc then deletes — the built
stream stays the same length) **fixes the s0/s1 assignment** and moves the
residual to the two scratch registers (`actSt02aEne` rc6 → rc4).  That
proves the cause is the *allocno creation order* of the two address
pseudos, not their live range, frequency or emission order: gcc-2.9's
`allocno_compare` ends in `return allocno1 - allocno2`, so a perfect
priority tie is decided by pseudo number, i.e. by which SYMBOL_REF got a
pseudo first.

Tried and still rc4–rc9 (all crutch-free, none of them wins):
statement swap; `int *p` temp before / after / at function top;
`&D_x[0]`; `*(D_x + 1)`; `((int *)obj->unkC4)[1]`; `obj->unkC4[1]`;
`(int)&handler`; `void *D_x[]` retyping; raw `*(int **)((char *)obj+0xC4)`
store; dropping the driver's `__p4` `__asm__` alias on the callee.

The next lever is **not** another spelling — it is to establish *why* the
retail TU orders the two pseudos differently from the aug6 TU, where the
byte-identical source matches.  Both bodies are the same modulo constants,
so the difference must be TU-context or flags: build the minimal-TU
brute-force (see `minimal_tu_brute_force` memory) with `-dg`/`-dl` greg
dumps for `actSt02aEne` in both trees and diff the allocno tables.
Solving it lands **5** functions.

## Still open after conv-4

| class | n | funcs |
|---|---|---|
| two-allocno `%hi` tie (above) | 5 | actSt04eWaterFlagOn · actSt02aEne · actSt02aSekizo · actSt05dDoor2UpChk · actSt03tWayOffChk |
| sched2 `%gp_rel`-store tie | 1 | func_0022BD58 (rc6, st13c) |
| `rewritten` — fresh decomp, aug6 body is only a loose guide | 17 | girl_act actGirlJump · way_tool debug_WayTool · commonact _ACTCommonMailTest / ContinueCorrectPosition / actCommonEdgeHang · e3 actE3CageFallChk · BgAnimation bga_resetObjectCounter, **bga_calcEnvelope (VU0, 13→180)** · st02a actSt02aSecretItem · enemy_act funcEnemyAiGetGirl / actEnemy_isLargeEnemy · end actEndDemo05 · boyact actBoyTakeWeaponReady / actBoySupportGBBegin / pullup_check_heroin_position / hand_heroin · motionManager SkelTest |
| wave-0 retail rewrites from ledger 2, dumps measured this pass | 5 | CheckPureCliffAttribute (rc47) · pac_continueTag (no aug6 candidate) · Debug_WireString_Bird (rc52) · gsb_StageSettingTool (rc27, §5.7 far in-TU global) · gene_enemy (rc16, §5.9 late rodata + s2/s3 swap) |
| fresh decomp, no aug6 body on either side | 3 | switch IsWallLeverStatus (62 insns) / GetWallLeverAngle (68 insns) · st02a func_00211EC8 (78 insns, newly carved) |
| `no-aug6-twin` (unchanged from ledger 3) | 8 | soundSeVolSet · the 7 src/pool funcs |
| `jtbl-deferred` (unchanged) | 1 | motionOrientManager shiftMotionOrientEndFunc |

Fastest next moves, in order: (a) the minimal-TU greg-dump attack on the
two-allocno tie (5 funcs for one root cause); (b) `gene_enemy` at rc16 —
the constants are already read off, only the §5.9 rodata materialization
and one s2/s3 swap remain; (c) `func_00211EC8` and the `switch` pair, which
are ordinary linear-code decomps.

---

# conv-5 remainder pass (worker 5, branch `conv-5` off `908573c9`)

Scope: the conv-4 "Still open" table.  Gate for every batch:
`./tools/build.sh setup && .venv/bin/ninja` → `verify_elf: OK (…fbf50c75…)`
plus `./tools/check_no_rom.sh`.

## RESOLVED — the two-allocno `%hi` tie (5 funcs, one root cause)

conv-4's next lever was "build the minimal-TU brute force with `-dg`/`-dl`
greg dumps and read the coloring mechanism".  Done — and the mechanism turned
out **not** to be in `global.c` at all.  It is in **gcse.c**, and it is fully
deterministic and fully readable from `-dG`.

### Mechanism (proven, with dumps)

The two `%hi` pseudos of the BoxBar tail are not created by expand; they are
created by **PRE (partial redundancy elimination) in gcse**, which hoists both
`(high:SI (symbol_ref …))` expressions out of the wait-loop into the loop
pre-header.  `-fno-gcse` makes both `lui`s disappear from the callee-saved
registers entirely, which is the first proof.

`pre_delete()` allocates each expression's `reaching_reg` while walking the
**expression hash table in bucket order**:

```c
for (i = 0; i < expr_hash_table_size; i++)
  for (expr = expr_hash_table[i]; expr; expr = expr->next_same_hash)
    ... expr->reaching_reg = gen_reg_rtx (...)
```

So the expression with the **lower hash bucket** gets the **lower pseudo
number**, the lower allocno index, and — because the two allocnos tie on
`allocno_compare`'s priority and it falls through to `return v1 - v2` — the
**lower callee-saved hard register**.  Bucket ties are broken by insertion
order, i.e. by source statement order.

`-dG` prints this directly.  For `actSt02aEne` (table = 17 buckets):

```
Index 2 (hash value 12)   (high:SI (symbol_ref:SI ("D_004D0FD0")))
Index 4 (hash value  6)   (high:SI (symbol_ref:SI ("actSt02aBoxEvent2")))
PRE: redundant insn 90 (expression 4) … reaching reg is 95     <- handler first
PRE: redundant insn 88 (expression 2) … reaching reg is 96
```

→ handler gets `$16`, array gets `$17`.  ROM has the opposite.

The rule was then **falsified-tested against an already-matched sibling**:
`actSt02aDoorUpEffect` has buckets `D_004D1190`=18, `actSt03tSekizoEvent`=9,
so the rule predicts *handler in `$16`* — and the ROM indeed has
`lui $16,%hi(actSt03tSekizoEvent)` / `lui $17,%hi(D_004D1190)`.  The rule
holds in both directions; it is not a post-hoc story.

### The two inputs to the bucket, and which one is free

1. **`expr_hash_table_size`** = `max(11, n_insns/4) | 1`, computed from the
   function's insn count at gcse time.  This is **not** a usable lever: gcse
   runs after cse1, and `delete_trivially_dead_insns` has already removed every
   dead statement, so a "no-op" source addition either changes the emitted code
   or changes nothing at all.  Verified with a ladder of 1–5 dead assignments:
   all left `T=17` and the output unchanged.  (conv-4's `D_x[0]=D_x[0];`
   self-store *did* move the allocation, but only because it is a real store
   that survives to gcse — and it shifted the scratch pair instead, rc6→rc4.)
2. **The symbol name string.**  `hash_expr_1` hashes `(high (symbol_ref X))`
   from the characters of `X` (position-dependent, not a plain sum).  Sweeping
   the array symbol's name over `a`…`z` in a minimal TU moves the bucket by
   exactly ±1 per character step and flips the register at the crossover —
   the register assignment is *literally a function of the symbol's spelling*.

**Consequence, and the actual finding:** with the placeholder spelling
`D_004D0FD0` the compiler **provably cannot** emit the ROM's registers.  The
name is ours, not the developer's (the aug6 tree calls the same object
`D_004CBBE0` and matches there only by luck of a different hash).  So the
residual was never a regalloc floor — it was our *symbol naming* leaking into
codegen.

### The fix actually applied

The five BoxBar objects sit in a long run of identical 0x20-byte records
(`{0x18D,0,0,0, 0x18C,0,0,0}`) — splat only emits a `dlabel` at each address
that happens to be *referenced*, so the underlying C object is very plausibly
**one table**.  Spelling the address as `base + index` re-hashes the
expression (the `const_int` addend participates in the hash) without changing
a single linked byte:

```c
{
    int *p = D_004D0F50 + 32;      /* == D_004D0FD0 */
    p[1] = (int)actSt02aBoxEvent2;
    obj->unkC4 = p;
}
```

Crutch-free; no `__asm__`, no pins, no config edits, no `symbol_addrs`
changes.  The base was chosen per function by sweeping the candidate table
bases (`tools`-free, see `basesearch` note below) until the bucket order
matched ROM.  **This is honest about what it is: the base/offset split is a
hash choice, exactly as the symbol name would be.**  The cleaner long-term
expression of the same fact is to give these objects real names in
`config/symbol_addrs.us.txt` (splat currently auto-names every data symbol
`D_<VMA>`; there are no data entries in that file at all today).

| func | TU | spelling | result |
|---|---|---|---|
| `actSt02aEne` | src/st02a | `D_004D0F50 + 32` | **MATCHED** |
| `actSt02aSekizo` | src/st02a | `D_004D0E10 + 136` | **MATCHED** (also: retail `stage_KillPlayBgAnimation(0x53,1,0)`, `func_0012AA80(0x53)`, `unkC4`, `BoxBarSoundOn(...,0x18D)`) |
| `actSt04eWaterFlagOn` | src/st04e | `D_004D1450 + 224` | **MATCHED** (also: loop is `while (scpKillSpiderGroup(a0,0x2000000) != 0)`, ids `0xE4→0xE5`) |
| `actSt03tWayOffChk` | src/st03t | `D_004D11B0 + 24` | **MATCHED** (retail inserts a `func_0017EB50()` guard: `while (func_0017EB50() != 0 \|\| scpSleepSpiderGroupOne(D_00631AE8,0x4000000) == 0)`; waypoints `0x35/0x37/0x38/0x39`, `func_0017B288(0x6F)`) |
| `actSt05dDoor2UpChk` | src/st05d | `D_004D1B70 + 16` | **MATCHED** (`while (scpSleepSpiderGroupOne(D_00631AE4,0xA000000) != 0)`) |

### Hazard found while doing this

19. **`quick_diff` cannot see a wrong `%lo` addend on an *extern* symbol.**
    A stray global `sed` set `actSt02aEne`'s offset to `D_004D0E10 + 136`
    (= `D_004D1030`, the *wrong* object).  Both sides disassemble to
    `addiu v0,s0,0` because the `.o` leaves the `%lo` of an extern
    unresolved, so tolerance 3 of `convpass_rd.sh` swallowed it and every
    per-function diff read `rc0`.  Only `ninja` caught it — 2 bytes at ROM
    `0x111744`.  Any base+offset edit **must** be ninja-gated, and any
    search script must edit exactly one function (a global `sed` on
    `int *p = D_… + N;` hits every sibling using the same idiom).

## RESOLVED — `func_0022BD58` (src/st13c, sched2 `%gp_rel`-store tie)

rc6, all of it in the prologue: ROM sinks `sw v1,%gp_rel(D_006325B4)($28)`
*after* the `lw s0,356(v0)` gobj load and therefore has to keep the constant
`1` in `v1` (built put the store first and reused `v0`).  The register
difference is a **consequence** of the schedule, not a second problem.

Root cause: gcc proves `D_006325B4` (a never-address-taken global) cannot
alias the `*(St13cBox **)(a0 + 0x164)` load and hoists the store above it.
Four order/temp respellings (`field_B0` first, split declaration, `int one = 1`
temp, volatile-qualified load) all stayed at rc6 — the ordering has to come
from a memory dependence, not from statement order.

`volatile` on the store supplies it, but TU-wide `extern volatile int
D_006325B4;` **regresses the matched sibling `actSt13cBmg1`** (+2 insns:
ROM sinks its `D_006325B4 = 0` store into a `beq` delay slot, which volatile
forbids).  Scoped with the TU's existing alias idiom instead:

```c
extern volatile int D_006325B4_v __asm__("D_006325B4");
```

(same device as `D_00631AE8__p4`, `D_00631AE4__p4`, `D_0065ED40_a/_b`, …
already in src/enemy_act.c, src/boyact.c, src/delayFreeManager.c).
**MATCHED**; every other function in src/st13c.c re-verified at rc0.

## RESOLVED — `gene_enemy` (src/itou_boss) and `func_00211EC8` (src/st02a)

**`gene_enemy`** — MATCHED.  Two independent fixes on top of conv-4's rc16:

1. **§5.9 rodata materialization was a *declaration* problem, not a codegen
   one.**  `extern int D_0055B030;` / `extern int D_0055BD40;` are ≤8 bytes,
   so `-G 8` made them `$gp`-relative (`addiu s4,gp,0`) where ROM does
   `lui`/`addiu %hi/%lo`.  Retyping both to `extern char D_xxxx[];` (see the
   `extern_size` note) took rc20 → rc10 with the insn counts equal.
2. **The residual s2/s3 + v0/v1 swap was the aug6 body's own spelling.**  The
   aug6 source routes the matrix pointer through an extra array-pointer temp
   and assigns it *last*:

   ```c
   char (*q_arr)[];
   q_arr = (char (*)[])&D_0055B030;
   r     = D_0055BD40;
   q     = *q_arr;
   ```

   conv-4's port had flattened that to `q = D_0055B030; r = D_0055BD40;`.
   Restoring the aug6 shape (including the otherwise-pointless `q_arr`
   indirection) is rc10 → **rc0**.  A plain statement swap (`r` before `q`)
   stays at rc10 — it is the extra temp, not the order.
   Retail deltas vs aug6: `iosFree(D_0062A310,0,D_00556348,0x16F)` →
   `func_0013A0F8(D_00632010,0,D_0055C178,0x15E)`, assert msg
   `D_00556358`→`D_0055C188`, table bases `D_006CCE60`→`D_006D35F0`,
   `D_005551F0`→`D_0055B030`, `D_00555F00`→`D_0055BD40`, and
   `func_00240080`→`func_00243B60`.

**`func_00211EC8`** (src/st02a, the last of conv-4's three carved halves,
78 insns, no aug6 twin) — **MATCHED on the first attempt**, straight
transcription.  Shape worth recording because the whole `actSt25a*` family
uses it: a chain of `p = actSt25aQueenDeadChk(id); <use p>` statements where
every store lands in the *next* call's delay slot, plus a 64-bit flag clear
`*(long long *)(o + 0x20) &= ~0x04000000;` (the `lui 0xFBFF`/`ori 0xFFFF`
pair is the sign-extended 64-bit constant — §5.11), and two
`func_0017EA50(actSt25aQueenDeadChk(id), 0.0f, -200.0f, 0.0f)` calls whose
two float constants are what force the callee-saved `$f20`/`$f21` pair.

## RESOLVED — the `src/switch.c` fresh-decomp pair

Both had no aug6 body on either side (INCLUDE_ASM in both trees), so these
were ordinary decomps from the `.s`, not ports.

| func | insns | result |
|---|---|---|
| `GetWallLeverAngle` | 68 | **MATCHED** |
| `IsWallLeverStatus` | 62 | **MATCHED** (first attempt) |

`GetWallLeverAngle` shape notes: `func_0013A0F8(D_00632010, 0x20, D_00618630,
0x8D)` is the allocator (same one as `gene_enemy`); the ROM's
`ldl/ldr` + `sdl/sdr` block copy of `D_004BEFD0` is reproduced by giving the
type **alignment 1** — `typedef struct { char b[0x20]; } WLA;` and a plain
`*p = D_004BEFD0;`.  A struct with `int`/pointer members has alignment 4 and
emits aligned `ld`/`sd` instead.

### NEW general lever — the retail CFLAGS do **NOT** carry `-fno-strict-aliasing`

`tools/compile_c.sh` builds with `-S -G 8 -O2 -mips3 -EL -fno-builtin
-nostdinc -fdata-sections`.  There is no `-fno-strict-aliasing`, so gcc's
**type-based alias sets are live** and a store through one pointer type can be
reordered past a load through another.  This contradicts the standing
`union_alias` note ("ALL `-fno-strict-aliasing`") — that was an aug6-era
observation and does not hold for this build.

`GetWallLeverAngle` rc4 was exactly this: ROM emits
`sw v0,12(s2)` immediately after the call, built sank it past
`lw v1,348(s4)`.  The store was spelled `*(void **)((char *)p + 0xC) = …`
(pointer alias set) while the load was `*(int *)((char *)a0 + 0x15C)`
(int alias set) — different sets, so the scheduler was free to swap them.
Respelling the store as the **same** alias set

```c
*(int *)((char *)p + 0xC) = (int)t;
```

restores the dependence and lands rc0.  A `void *` temp and a `volatile`
store both stayed at rc4 — it is the *type*, not the statement shape.
**Check the alias set of every store/load pair before calling a store/load
swap a "scheduler tie".**

## RESOLVED — `_ACTCommonMailTest` was a splat-merge, not a rewrite

Ledgered as `rewritten` (aug6 7 insns → retail 27).  It is not: the 0x70
`.s` block held **three** functions (two extra prologues after an infinite
`_ACTWait` loop — the `splat_merged` signature).  Carved with two
`config/symbol_addrs.us.txt` additions and all three written:

| new symbol | insns | body |
|---|---|---|
| `_ACTCommonMailTest` (0x0015EED0) | 8 | unchanged from aug6 — `for (;;) { _ACTWait(1); }` |
| `func_0015EEF0` (0x0015EEF0) | 14 | aug6 twin `func_0015CFF0`; `0x3F`→`0x40`, `D_00629DE8`→`D_00631AE8`, `D_0062A4DC`→`D_006321DC` |
| `func_0015EF28` (0x0015EF28) | 6 | fresh: `if (a0 == (void *)D_00631AE8) D_00632508 = 1;` |

All three **MATCHED**.  Worth re-checking the rest of the `rewritten` list for
the same signature before treating any of them as a grind: an "N× bigger"
retail body with an infinite-loop-then-prologue shape is a merge, not a
rewrite.

---

## conv-5 summary

**12 matched**, in 5 gated commits, every one verified at
`verify_elf: OK (…fbf50c75…)` + `check_no_rom: OK`.

| commit | scope | n |
|---|---|---|
| `b1f46d97` | two-allocno `%hi` tie (gcse bucket order) | 5 |
| `a605df4a` | `func_0022BD58` sched2 `%gp_rel`-store tie | 1 |
| `b4ee5f97` | `gene_enemy`, `func_00211EC8` | 2 |
| `89db4fec` | `IsWallLeverStatus`, `GetWallLeverAngle` | 2 |
| (this) | `_ACTCommonMailTest` + 2 carved halves | 3 |

`config/symbol_addrs.us.txt` additions: `func_0015EEF0`, `func_0015EF28`
(both `// type:func  // src/commonact.c  // provisional-ordinal`).
No renames, no yaml edits, no new crutches.

### Still open after conv-5

| class | n | funcs |
|---|---|---|
| measured-residual rewrites, **not attempted this pass** | 4 | `gsb_StageSettingTool` (rc27) · `CheckPureCliffAttribute` (rc47) · `Debug_WireString_Bird` (rc52) · `pac_continueTag` (no aug6 candidate — hand transcription) |
| `rewritten` — fresh decomp, aug6 body a loose guide | 16 | girl_act `actGirlJump` · way_tool `debug_WayTool` · commonact `ContinueCorrectPosition` / `actCommonEdgeHang` · e3 `actE3CageFallChk` · BgAnimation `bga_resetObjectCounter`, `bga_calcEnvelope` (VU0) · st02a `actSt02aSecretItem` · enemy_act `funcEnemyAiGetGirl` / `actEnemy_isLargeEnemy` · end `actEndDemo05` · boyact `actBoyTakeWeaponReady` / `actBoySupportGBBegin` / `pullup_check_heroin_position` / `hand_heroin` · motionManager `SkelTest` |
| `no-aug6-twin` | 8 | `soundSeVolSet` · the 7 src/pool funcs |
| `jtbl-deferred` | 1 | motionOrientManager `shiftMotionOrientEndFunc` |

**Recommended order for conv-6:** (a) run the splat-merge check over all 16
`rewritten` entries first — `_ACTCommonMailTest` proves the classification is
unreliable and a merge is 10 minutes, not a grind; (b) `gsb_StageSettingTool`
at rc27 with the two new levers in hand (the `-G 8` declaration retype from
`gene_enemy` and the strict-aliasing type-set rule from `GetWallLeverAngle` —
between them they accounted for every non-tie residual this pass);
(c) the remaining measured-residual three.

---

# conv-6 remainder pass (worker 6, branch `conv-6` off `04d2aa0a`)

Scope: conv-5's "Still open" table.  Gate for every batch:
`./tools/build.sh setup && .venv/bin/ninja` → `verify_elf: OK (…fbf50c75…)`
plus `./tools/check_no_rom.sh`.  **46 matched in 9 gated commits** (plus one
carve-only commit).  No yaml edits, no new crutches.

## THE HEADLINE — the `rewritten` bucket was 70% splat-merge, not rewrite

conv-5 found this for `_ACTCommonMailTest` and recommended sweeping the rest.
Done, and it is the dominant finding of the whole pass: **10 of the 16
`rewritten` entries were splat-merged multi-function blocks**, hiding **31**
uncarved functions behind missing boundary symbols.

### The detector that actually works

Reachability analysis is the wrong tool (jump tables and trailing `.p2align`
pads give false positives; `ContinueCorrectPosition` was flagged and is a
single genuine function).  The reliable signature is purely local:

> an interior `addiu $29,$29,-N` **whose address is not the target of any
> `.L…` label in the file**

plus, for frameless tails, a `jr $31` (or a tail-call `j <sym>`) that is not
the last instruction.  A 20-line script over `asm/nonmatchings/**/*.s` finds
every one; cross-checking the split count against the aug6 twin's
`splat-merge …split` entries in `config/symbol_addrs.aug6.txt` (190 of them!)
confirms each.  **The aug6 tree had already carved every one of these
families; retail's symbol table simply never inherited the splits.**

| retail head | TU | funcs | aug6 twin family |
|---|---|---|---|
| `actGirlJump` | src/girl_act | 3 | `actGirlJump` + `func_001732F0` + `func_00173370` |
| `debug_WayTool` | src/way_tool | 2 | + `func_00204650` |
| `actCommonEdgeHang` | src/commonact | 5 | + `func_0015C9B8/CA48/CAE0/CB20` |
| `actE3CageFallChk` | src/e3 | 2 | + `func_002078C8` |
| `funcEnemyAiGetGirl` | src/enemy_act | 3 | + `func_00162E98/ED8` |
| `actEnemy_isLargeEnemy` | src/enemy_act | 4 | + `func_00163448/500/5B8` |
| `actBoyTakeWeaponReady` | src/boyact | 2 | + `func_00151E98` |
| `actBoySupportGBBegin` | src/boyact | 2 | + `func_001530C0` |
| `hand_heroin` | src/boyact | 3 | + `func_0014C0C0/C370` |
| `pullup_check_heroin_position` | src/boyact | 15 | + 14 `func_00151F48…00152480` |

**Recommendation for any future pass: run this detector over the WHOLE
`asm/nonmatchings` tree, not just the `rewritten` bucket.**  Nothing
guarantees the merges are confined to functions the port driver happened to
classify as expansions — a merge whose head *also* ports cleanly would show
up as a plain `divergent`/`asm` entry with no hint at all.

### Carve mechanics (repeatable)

1. Add `func_<RETAILVMA> = 0x<RETAILVMA>; // type:func // <tu>.c // splat-merge split (<head> coroutine)`
   to `config/symbol_addrs.us.txt`, in address order inside the TU's run.
2. `rm -f .port_cache/retail_labels.json && ./tools/build.sh setup`.
3. Add `INCLUDE_ASM(...)` for each new name **immediately after the head's**,
   in `.text` order, and re-`setup`.  (Without the INCLUDE_ASM splat files the
   body under `asm/matchings/` and the TU's `.text` comes up short.)
4. `ninja` — a carve-only commit is byte-identical and is a safe checkpoint.
   Landed as `425586ca` ("31 boundaries, 0 matched").

Note the carve is also *self-confirming*: `asm/data/src/cod/174700.data.s`
immediately resolved `.word func_0020A468` at ROM 0x3D0A54, i.e. the BoxBar
event table statically points at the carved tail.

## Matched, by commit

| commit | scope | n |
|---|---|---|
| `425586ca` | carve 31 splat-merge boundaries (checkpoint) | 0 |
| `5b8b34fc` | src/e3 (2), src/girl_act (3), src/commonact edge-hang (5) | 10 |
| `d01ea4d0` | src/enemy_act — AiGetGirl (3) + isLargeEnemy (4) | 7 |
| `d20b6255` | src/boyact — pullup chain (15), TakeWeaponReady (2), SupportGBBegin (2) | 19 |
| `73bd4e77` | `hand_heroin`, `debug_WayTool` | 2 |
| `364df43e` | `CheckPureCliffAttribute`, `gsb_StageSettingTool`, `Debug_WireString_Bird` | 3 |
| `81637515` | `actEndDemo05`, `ContinueCorrectPosition` | 2 |
| `eeb9766d` | `func_002071E8` (way_tool merge tail, fresh decomp) | 1 |
| `3f0a868d` | `SkelTest` | 1 |
| `d68574e1` | `bga_resetObjectCounter` | 1 |

`config/symbol_addrs.us.txt` additions (31, all
`// type:func // <tu> // splat-merge split (<head> coroutine)`):
`func_00175740 func_001757B8` (girl_act) ·
`func_002071E8` (way_tool) ·
`func_0015E878 func_0015E908 func_0015E9A0 func_0015EA20` (commonact) ·
`func_0020A468` (e3) ·
`func_00165060 func_001650A0 func_00165610 func_001656C8 func_00165780` (enemy_act) ·
`func_00153980 func_00154BC0 func_0014D978 func_0014DC28 func_00153A30
func_00153AA8 func_00153AD8 func_00153B38 func_00153BE0 func_00153C90
func_00153DA0 func_00153DF8 func_00153E28 func_00153E68 func_00153EC8
func_00153F08 func_00153F38 func_00153F68` (boyact).
No renames.

## Retail-vs-aug6 delta catalogue (useful for the next porter)

Almost every carved tail is the aug6 body with a mechanical substitution set.
The recurring ones:

* **Sub15C/GObj field offsets +0x10** (`0xB0→0xC0`, `0xB4→0xC4`,
  `0x100/104/108→0x110/114/118`, `0x12C→0x13C`, `0x400→0x420`,
  `0x410/414/418→0x430/434/438`, `0x420→0x440`, `0x490→0x4A0`,
  `0x49C/4A0→0x4AC/4B0`, `0x4B4→0xC4`… ) — the documented "+0x10 family".
* **Waypoint/scene ids +3, sound ids +3** (`0xB4→0xB7`, `0x189→0x18D`,
  `0x80/81→0x81/82`, `0xCF→0xD2`, `0xF7→0xFA`, `0x114→0x117`, `0x124→0x127`,
  `0x136→0x13A`, `0x15B/15D→0x15F/161`, `0x163→0x167`, `0x16E→0x172`,
  `0x170/173→0x174/177`, `0x189→0x18D`).  Not universal — verify per call.
* **Globals**: `D_00629DE4→D_00631AE4`, `D_00629DE8→D_00631AE8`,
  `D_0062A4DC→D_006321DC`, `D_0062A894→D_006325B4`, `D_00629C90→D_00631990`,
  `D_00271240→D_00274EC0`, `D_0062C230→D_00633F3C`, `D_006A45A0→D_006AAAE0`,
  `D_006A4630→D_006AAB70`, `D_0062BFE8→D_00633CF8`, `D_00628F18→D_00630C1C`.
* **Callees**: `func_0018F2A0→func_001919A0`, `func_001AB9B8→func_001AE420`,
  `func_001AAD00→func_001AD768`, `func_00260380→func_00263FF0`,
  `func_00260568→func_002641D8`, `func_0023FDD8→func_002438B8`,
  `func_0023E168→func_00241C48`, `func_00240AB8→func_00244598`,
  `func_00130000→func_00130128`, `func_0023EAC8→func_002425A8`,
  `func_00240038→func_00243B18`, `iosFree→func_0013A0F8`,
  `func_001E1A18→func_001E4798`.

Genuine retail *behaviour* additions found while porting (not substitutions):

* `func_0015E9A0` (commonact) — the dispPlane loop gained a
  `if (s->f_C8 == 0xB1) func_00243B18(v, v, -1.0f);` pre-pass.
* `actEndDemo05` (end) — gained `func_0017CA10(actSt25aQueenDeadChk(0xA1F))`.
* `ContinueCorrectPosition` (commonact) — the `case 0x2B` CageFixDL arm gained
  a zero-fill: `if (CageFixDL(...) == 0) { f = D_00632340[0]; p[0]=p[1]=p[2]=f; }`.
* `SkelTest` (motionManager) — `block12` gained
  `func_00118648(buf,a1,D_004C5BD0)` + `_RotTransPersCurrentMatrix(p+0x10,p,buf)`
  and a second `ClipWallBoxStop` early-out.
* `bga_resetObjectCounter` (BgAnimation) — `D_00629CF0 = 1` became
  `D_006319F0 = 1; mc_TransMicroCode(D_00710C20, D_00710C10);`.
* `Debug_WireString_Bird` (act_bird) — gained a trailing `func_001D4B40(a0, 3)`.
* `gsb_StageSettingTool` (GsBase) — gained a trailing `stage_SetScale()`.
* `CheckPureCliffAttribute` (motionManager2) — retail *dropped* the aug6
  assert block; it is a **shrink**, which is why the ledger's rc47 looked like
  a rewrite.  (Its aug6 twin lives in `sugipon/src/motionManager2.c`.)

## New/confirmed levers

20. **Store-order rotation in a straight run of same-base stores.**  When N
    consecutive `p->a = 0; p->b = 0; …` stores come out in the right set but
    the wrong order, ee-gcc's sched2 emits source order **rotated right by
    one** (last source store becomes first emitted, and the new last store
    lands in the following `jal`'s delay slot).  So to obtain ROM order
    `[s1,s2,s3,s4]`, write source order `[s2,s3,s4,s1]`.  Cracked
    `func_001656C8` 6→0 and `ContinueCorrectPosition` 4→0 (3-store case:
    source `[0],[1],[2]` → emitted `[0],[2],[1]`).
21. **A `while (G == 0) wait();` spin on a global can allocate two different
    registers for the two loads.**  Routing it through one explicit local —
    `{ int v = G; while (v == 0) { wait(); v = G; } }` — unifies them.
    `func_002071E8` 2→0.
22. **C string literals are forbidden in this tree.**  `Debug_WireString_Bird`
    ported straight from aug6 (which uses `"src/act_bird.c"`) passed
    `quick_diff` at rc0 and then blew the SHA by **128 bytes** of extra
    `.rodata`.  Always spell the literal as the existing `extern char
    D_xxxxxxxx[];`.  Corollary: any port from an aug6 body containing a string
    literal must be de-literalised before `ninja`.
23. **`-G 8` retype, restated for floats.**  A far `lui/%hi` + `lwc1 %lo`
    float constant needs `extern float D_x[];` + `D_x[0]`; `extern float D_x;`
    becomes `$gp`-relative and loses an instruction.  (`ContinueCorrectPosition`
    11→4.)
24. **`char b[0x20]` (alignment 1) vs `long long q[8]` (alignment 8)** decides
    `ldl/ldr`+`sdl/sdr` vs `ld`/`sd` for a whole-struct copy — confirmed again
    in `actSt02aSecretItem`, where retail copies two 0x20 objects unaligned and
    two 0x40 objects aligned in the same function.
25. **Scoped `__asm__("NAME")` aliases are frequently *required* just to get a
    second prototype for a function the TU already declares with a different
    arity** (`func_00243B18_e`, `iosOmBeforeFuncStandard3/4`,
    `func_001919A0__p2`, `D_006321DC__hh`).  This is the TU-family idiom, not a
    matching crutch, and every TU touched here already used it.
26. **A dead `daddu aN,a0,zero` at the top of a switch is a hoisted
    switch-invariant argument**, not a compiler artifact: `pac_continueTag`'s
    stray `daddu a2,a0,zero` is `a0` being passed as the *third* argument to
    the `debug_openLog` call in all five cases, hoisted above the dispatch.
    Adding the third argument took it 6→(cosmetic-only).

Hazard, restated: **`convpass_rd.sh`'s relative-branch tolerance only fires
when both sides print the same `+0xNN` suffix.**  In a function whose ROM
`.s` names its branch targets off a `jlabel` (jump-table function), every
branch reads as a diff even when the byte offsets agree.  Check the printed
offsets by hand before believing a jtbl function's residual.

## Still open after conv-6

| class | n | funcs |
|---|---|---|
| carved but unwritten (merge tails, no matched aug6 twin) | 2 | boyact `func_0014D978` (172 insns), `func_0014DC28` (188) — aug6 twins `func_0014C0C0`/`func_0014C370` are INCLUDE_ASM there too |
| near-miss, structure recovered | 1 | st02a `actSt02aSecretItem` — **rc19 at equal insn counts (108/108)**, pure intra-block scheduling |
| jtbl-blocked (stream verified, needs a yaml carve) | 2 | Packet `pac_continueTag`, motionOrientManager `shiftMotionOrientEndFunc` |
| fresh decomp, no guide | 1 | BgAnimation `bga_calcEnvelope` (180 insns, `func_0010E9A0`/`func_00117C20` FP chain) |
| `no-aug6-twin` (unchanged since ledger 3) | 8 | `soundSeVolSet` · the 7 src/pool funcs |

### `pac_continueTag` — verified body, blocked only by the jtbl carve

The instruction stream below was built and compared: 51/51 insns, every real
difference gone (the 5 residual lines are the `jlabel` cosmetic above).  It
cannot be landed without carving `jtbl_00554FE0` out of the `.rodata` blob,
because the ROM jump table in `asm/data/src/cod/454E44.rodata.s` references the
`.L…` labels that only exist while the function is `INCLUDE_ASM`; with the C
switch in place the link fails with `undefined reference to '.L001194C8'`.
**Reverted to INCLUDE_ASM (rule: no yaml edits).**  The carve is one line, in
the style of the four already present at `config/ico.us.yaml:335-342`:

```yaml
      - [0x454FE0, .rodata, src/Packet]   # gcc-emitted jtbl_00554FE0 (pac_continueTag switch, 5 entries 0x14), VMA 0x554FE0..0x554FF4
      - [0x454FF4, rodata, src/cod/454FF4]   # .rodata blob, resume after 2nd Packet jtbl
```

Caveat: `src/Packet` would then own **two** disjoint `.rodata` carves
(`0x454E00` for `pac_setVifEndCode` is already there), which the
`carve_disjoint_rodata` rule says fails SHA.  Resolving that — probably by
merging the two carves into one contiguous region plus an explicit blob
subsegment for the gap — is the real work item, and is the same blocker
`shiftMotionOrientEndFunc` sits behind.

```c
extern char D_00554EE0[], D_00554F10[], D_00554F40[], D_00554F70[], D_00554FA8[];
extern char D_00554FD0[], D_00672FD0[], D_00631CF8[];
extern void debug_openLog(char *a0, char *a1, void *a2);
extern void func_001AD768(char *file, int line);
extern void func_00263FF0(char *file, int line, char *msg);

void pac_continueTag(void *a0, int a1) {
    switch (a1) {
    case 1: debug_openLog(D_00554EE0, D_00672FD0, a0); break;
    case 2: debug_openLog(D_00554F10, D_00672FD0, a0); break;
    case 3: debug_openLog(D_00554F40, D_00672FD0, a0); break;
    case 4: debug_openLog(D_00554F70, D_00672FD0, a0); break;
    case 5: debug_openLog(D_00554FA8, D_00672FD0, a0); break;
    }
    func_001AD768(D_00554FD0, 0x2AC);
    func_00263FF0(D_00554FD0, 0x2AC, D_00631CF8);
}
```

### `actSt02aSecretItem` — rc19 shape, for whoever resumes

Counts already agree (108/108); the residual is where the second 0x40-byte
`ld` burst gets scheduled relative to the two unaligned `ldl/ldr` copies.
Copy order `m0,m1,n0,n1` gives rc19; interleaving to `m0,n0,m1,n1` **regresses
to 102 insns / rc132**, so the declaration+assignment grouping is right and
only the schedule is off.  Next ideas: route `n1` through a pointer temp; move
the `func_0010D198` calls between the copies; try `long long q[8]` →
`struct{long long a,b,c,d,e,f,g,h;}`.

```c
typedef struct { char b[0x20]; } SI_M;
typedef struct { long long q[8]; } SI_N;
extern SI_M D_0061BA60, D_0061BA80;
extern SI_N D_0061BAA0, D_0061BAE0;
extern void func_0010D198(void *a0, void *a1);
extern void InitLayoutedPoolReflactionMesh(void *a0);
extern void getWave(void *a0);

void actSt02aSecretItem(volatile int a0) {
    SI_M m0, m1;
    SI_N n0, n1;
    m0 = D_0061BA60;
    m1 = D_0061BA80;
    n0 = D_0061BAA0;
    n1 = D_0061BAE0;
    func_0010D198(&m0, &n0);
    func_0010D198(&m1, &n1);
    for (;;) {
        InitLayoutedPoolReflactionMesh(&m0);
        getWave(&m0);
        InitLayoutedPoolReflactionMesh(&m1);
        getWave(&m1);
        _ACTWait(1);
    }
}
```

### Bonus finding for the aug6 tree

`func_001656C8` (retail) matched crutch-free, and its aug6 twin
`func_00163500` — still `INCLUDE_ASM` in `fumi/src/enemy_act.c` — is the
*same* instruction stream modulo the substitution set above.  Porting the
conv-6 body back should close it, and the same is true for whichever of the
other retail carves have unmatched aug6 twins.

## Recommended order for a conv-7

(a) Run the interior-prologue detector over **all** of `asm/nonmatchings` —
this pass proved the classification hides whole functions, and each carve is
minutes not hours.  (b) Unblock the two jtbl functions by solving the
two-disjoint-`.rodata`-carves-per-TU problem for `src/Packet`.  (c)
`actSt02aSecretItem` at rc19.  (d) The two boyact merge tails and
`bga_calcEnvelope` as ordinary decomps.

---

# conv-7 — repo-wide splat-merge sweep (branch `conv-7`, base `6e0fea8f`)

Mission: conv-6's top recommendation — run the interior-prologue splat-merge
detector over **all** of `asm/nonmatchings`, carve every hidden boundary, match
what the splits unlock.

**Result: 137 hidden functions carved (was 31 in conv-6), 59 of them byte-
matched.**  Every commit is byte-identical (`verify_elf: OK
(fbf50c75cd5911273511c4f9af90503ff8423582)`).

## The detector, generalised — `tools/find_splat_merges.py` (tracked)

conv-6's rule ("interior `addiu $29,$29,-N` that no `.L…` label targets")
misses every *frameless* second function and, applied naively, fires on
scheduled prologues: gcc routinely places the stack adjust 1–4 instructions
into the function (`blur` +4, `waypoint_with_range` +4, `warpGirlInStage`
+16).  The generalisation that holds is **local unreachability**:

> instruction *i* starts a hidden function when (a) no `.L…` label names its
> address, and (b) control cannot fall into it — the instruction two back
> (whose delay slot is *i*'s predecessor) is an unconditional `b` / `j` / `jr`.

with two corrections that are the whole difference between 1331 hits and 137:

1. **`.p2align` pad `nop`s sit in exactly position (b)**.  A flagged `nop` run
   is walked forward to the first real instruction; a run that reaches EOF is
   dropped.  Without this the detector reports every function's trailing pad.
2. **Jump-table case blocks are legitimately label-less** — their entry
   addresses live in `.rodata`, so raw reachability calls each one a new
   function (`dispSun`, `makeFullScreenFlareBefore`, `tableSin`, `poly-flat`
   …).  Any file containing a `jr $N`, N≠31, or a `jtbl_` reloc is flagged and
   its non-prologue candidates are ranked `low` and hidden by default.  This
   is the same false-positive class conv-6 warned about; the fix is to
   *down-rank* rather than to abandon reachability.

Ranking: `high` = unreachable **and** a stack prologue (126 of 137); `med` =
unreachable, no prologue, non-jtbl file (11 — these are the frameless tails);
`low` = suppressed jtbl case blocks.  Only functions currently `INCLUDE_ASM`
are scanned (splat never deletes the `.s` of a since-matched function).

### Independent confirmation

For the 30 merged heads that still carry their aug6 name, the detector's
candidate **count matches the aug6 tree's `splat-merge …split` count exactly**,
with head-relative offsets agreeing to within the retail/aug6 code drift —
e.g. `actGirlBHang` 7/7 (retail 2688…4992 vs aug6 2624…4888),
`actCommonLadder` 3/3 (40/128/224 identically), `actEnemy_isSmallEnemy` 3/3,
`iosCdvdBackGroundReadJimaku` 3/3, `ACTGetOrientFromIntrK` 4/4.  The three
count disagreements are all explained, not errors: `actBoySwim` is 4/5 because
retail's merged block is 4148 bytes and aug6's 5th split sits at +4152, i.e.
past the end; `TestCageUpDown` and `actCommonDie` each have one extra retail
split because retail merged one function *further* than aug6 did.

The `med` (frameless) rank is likewise confirmed: 5 of the 11 land on an aug6
split (`ACTGetOrientFromIntrK` +2336≈2348, `SetDirectRootPositionXZ`
+288≈276, `flyMailCore` +352≈348, `jimakuJump` +264≈268, `actSt00aDoor2`
+392≈404).

### Candidate table (137 boundaries / 71 heads / 29 TUs)

| TU | carved boundaries |
|---|---|
| ios/cdvd | 1 |
| ios/thread | 1 |
| src/access | 2 |
| src/boyact | 10 |
| src/camera-editor | 3 |
| src/camera-ico2 | 2 |
| src/commonact | 53 |
| src/delayFreeManager | 2 |
| src/enemy_act | 10 |
| src/gather_effect | 1 |
| src/girl_act | 18 |
| src/haveParentSimpleObj | 2 |
| src/jimaku | 6 |
| src/lightning | 1 |
| src/objact | 3 |
| src/st00a | 2 |
| src/st03t · st04c · st04e · st13b2 · st13c · st17a · st22a · warpGirl · way_tool | 1 each |
| src/st13d · st17b · st19a | 2 each |
| src/st47a | 5 |

Full per-symbol list: `git show 718d59f2 -- config/symbol_addrs.us.txt`.
Re-run at any time with `tools/find_splat_merges.py` (`--format=symbols` emits
the `symbol_addrs` lines directly; `--min-conf low` shows the suppressed jtbl
class).  **The aug6 tree should be swept with the same tool** — it carries 190
splits already but was never checked with the frameless/`med` rule.

## Correlating a carve tail to its aug6 body — `name_alias.json`

`port_from_aug6.py` joins retail to aug6 **by name**, which can never work for
a carve: our recovered bodies are `func_<RETAILVMA>` and the aug6 tree carved
the same boundary at a different address.  Added (small, reusable):

* `.port_cache/name_alias.json` — `{retail_name: aug6_name}`.
* `scan` reads it, records `aug6_name` beside `name`; `build_symbol_map` opens
  the aug6 `.s` under the alias; `cmd_port` rebinds `aug6_name -> name` so the
  spliced body defines and self-recurses under the retail symbol.

The map itself comes from `convpass_ordinal.py`'s reloc-blanked stream score:
**61 of the 124 carve tails score 1.00 against a matched aug6 body** (42 of
them uniquely; the ambiguous ones are duplicate act-thread wrappers, and the
rebinding is slot-based so any of the tied twins produces the same C).

## Matched, by commit

| commit | scope | carved | matched |
|---|---|---|---|
| `718d59f2` | repo-wide detector sweep + carve (checkpoint) | 137 | 0 |
| `16c30a25` | mechanical port through the alias map | 0 | 15 |
| `9aac772a` | girl_act / enemy_act / st17a / st19a / boyact tails | 0 | 11 |
| `d6449d17` | commonact tails (20) | 0 | 20 |
| `166e3025` | st04c/st04e/st13b2/st13c/st19a/jimaku/commonact tails | 0 | 13 |

59 matched: commonact 31 · jimaku 4 · girl_act 4 · enemy_act 3 · boyact 2 ·
st19a 2 · st04c · st04e · st13b2 · st13c · st17a · ios/thread · camera-ico2.

Substitution families used — all already in conv-6's catalogue, no new class:
BoxBar/se id **+3 or +4** (`0xB4→0xB7` is the single commonest edit in the
whole pass; also `0x189→0x18D`, `0x142→0x146`, `0x14C→0x150`, `0xCF→0xD2`,
`0x136→0x13A`, `0x9C→0x9E`, `0xE1→0xE4`, `0x13A→0x13E`), one **−4**
(`func_0015E3F8` `0xB4→0xB0`) and one **−9** (`jimaku func_00175A58`
`0x62→0x59`); Sub15C/GObj **+0x10** (`0xB0/0xB4→0xC0/0xC4`, `0xB8→0xC8`,
`0x100→0x110`, `0x110→0x120`, `0x150→0x160`, `0x490→0x4A0`, `0x5D8→0x5E8`,
`0x5F0→0x600`, `0x7C0→0x7E0`, `0x3B0→0x3D0`) plus one **−0x10**
(`0x4D0→0x4C0`); chained ids needing a *simultaneous* rewrite (boyact
`func_00152508`: `0x5B/5C/5D→0x5C/5D/5E` and `0x46/47/48/49→0x47/48/49/4A`);
moved members (`0x608→0x140`, `0x608→0x604`).

## Three hazards worth remembering

1. **`port_from_aug6` reverts on a diff that is not real.**  Eleven commonact
   tails were REVERTED for `expected jal 0 <self> built jal <InTuCallee>`.
   That is an artefact: quick_diff's expected stream assembles ONE function,
   so its call stays a relocation, while our build resolves the callee inside
   the TU.  `convpass_rd.sh`'s tolerances see through it — **splice and
   re-diff before believing that revert reason.**
2. **A global string replace of a bumped constant hits matched siblings.**
   Bumping `s0[0x30/4] = 0xF` for `func_001755F8` also rewrote the identical
   line in the already-matched `func_001757B8` in the same TU.  `quick_diff`
   and `convpass_rd` were rc0 for *every* function; only the `ninja` SHA gate
   caught the single changed byte at 0x1757DC.  Scope every constant edit to
   the target function's brace span.
3. **Coalesced-TU splices collide twice.**  (a) The driver emits its collected
   `static __inline__` helpers once per spliced sibling — N siblings sharing a
   helper produce N identical definitions.  De-duplicate to one.  (b) Those
   helpers land at the TOP of the TU, above prototypes the TU declares further
   down, so gcc 2.9 implicitly declares the callee and then reports
   `conflicting types`.  Hoist a copy of the prototype (with its `__asm__`
   alias) above the helper block.

## Bonus finding for the aug6 tree (verified, do NOT act on it here)

conv-6 suggested retail `func_001656C8`'s matched body should close aug6's
still-`INCLUDE_ASM` `func_00163500` (`fumi/src/enemy_act.c:974`).  Measured:
the reloc-blanked streams score **0.989** at **46 aug6 vs 45 retail**
instructions.  So it is a near-twin, not a transplant — porting the conv-6
body back with the inverse substitutions (`0x110→0x100`, `0x420→0x400`,
`0x13C→0x12C`, se `0x14A→0x146`) gets most of the way, but there is a genuine
one-instruction structural delta to resolve on the aug6 side.

## Still open after conv-7

| class | n | detail |
|---|---|---|
| carved, aug6 twin scored 1.00, still unmatched | 2 | boyact `func_00151868` / `func_001519D8` — both at **rc2** on a spliced body; residual is a float const (`lui 0x42B4`→`0x42A0`, i.e. 90.0f→80.0f) plus `ld` slots at `+8/+16/+24` where ROM wants `+0` of a distinct symbol (the `-G8` / `float_vector_rodata_union` family). Best next targets in the whole queue. |
| carved, no 1.00 aug6 twin | 63 | the big act-thread tails: girl_act `actGirlBHang`×7, `actGirlHand`, `actGirlHangG3M`, `func_001725C8` (678 insns); commonact `func_0015DA20`, `func_0015DF88`, `func_0015E1B0`, `func_0015E388`, `func_0015EC08`, and the `ACTGetOrientFromIntrK`/`TestCageUpDown`/`actCommonDie`/`actCommonBox`/`actCommonDown`/`actCommonBar` heads' tails; boyact `func_00150568`×6; enemy_act `func_001600F8`/`func_001605F8`/`func_001611E8`/`func_001619A8`/`func_001624D8`/`func_001649D0` (the last reverts `unresolved-symbol D_00271240`); camera-editor `test_camedit`×3; st47a×5; st13d×2, st17b×2, objact×3, access×2, delayFreeManager×2, haveParentSimpleObj×2, st00a×2, and the singletons.  These need ordinary convergence, not a substitution. |
| unchanged from conv-6 | — | `pac_continueTag` / `shiftMotionOrientEndFunc` (two-disjoint-`.rodata`-carves-per-TU); `actSt02aSecretItem` rc19; `bga_calcEnvelope`; the 8 `no-aug6-twin` funcs. |

**Recommended order for a conv-8:** (a) the two boyact rc2 tails — one
`-G8`/float-const idea away; (b) run `tools/find_splat_merges.py` against the
**aug6** checkout (it has 190 splits but has never been checked with the
frameless/`med` rule, and the same 137-vs-31 ratio may hold there); (c) the 63
no-twin tails, smallest first — most are 8–50 insn act-thread coroutines;
(d) conv-6's carry-over list unchanged.

---

# conv-8 — carve-tail cleanup (branch `conv-8`, base `1e58b3e5`)

Mission: conv-7's recommended order — (a) the two boyact rc2 tails, (b) the 63
carved tails with no 1.00 aug6 twin, smallest-first, (c) `actSt02aSecretItem`
and `bga_calcEnvelope`.

**Result: 23 byte-matched.**  Every commit gated `build.sh setup && ninja` →
`verify_elf: OK (fbf50c75cd5911273511c4f9af90503ff8423582)` + `check_no_rom.sh`.

| commit | scope | matched |
|---|---|---|
| `c564457d` | boyact `.lit8` rodata carve + `func_00151868`/`func_001519D8` | 2 |
| `188074c7` | cdvd / enemy_act / gather_effect / objact smallest tails | 4 |
| `d0c7e743` | BoxBar + lws_kyomi act-wrapper family (8 TUs) | 11 |
| `a9aba0cc` | commonact / haveParentSimpleObj / objact tails | 3 |
| `a328d874` | camera-ico2 / girl_act / jimaku tails | 3 |

## 1. The two boyact rc2 tails — the residual was never `-G8`

conv-7 read the residual as the `-G8` / float-vector-rodata family.  It is not.
`func_00151868`/`func_001519D8` pass two `double` literals (`0.2`/`0.9` and
`0.2`/`0.7`) to the soft-float helpers `func_00262BE8`/`func_00262B80`, and
ee-gcc materialises them with the **`li.d` pseudo-op** — the *assembler* builds
the pool.  ROM's `lui $1,%hi(D_005586xx) / ld $r,%lo(D_005586xx)($1)` is that
pool reference.

Referencing the ROM slots as externs **cannot** reproduce it, for a reason
worth writing down:

> `memory_address()` (explow.c) force_reg's *any* `CONSTANT_ADDRESS_P` address
> into a pseudo "to get a chance to cse them".  On MIPS with
> `TARGET_SPLIT_ADDRESSES` that pseudo becomes `HIGH`/`LO_SUM`, and loop
> invariant motion then hoists the `HIGH` out of the act loop.  Result: two
> extra `lui`s in the prologue, `$29` grows 0xA0→0xC0, `$21`→`$23`, **rc21**.
> `force_const_mem()` builds its MEM *without* going through
> `memory_address()`, so only a real compiler pool stays in-loop.

Tried and rejected: `extern long long D_00558620[]`, `extern const double []`,
`extern volatile const double []` — all rc21, all the same hoist.

The fix is the literal + a 32-byte `.rodata` carve:

```yaml
- [0x458620, .rodata, src/boyact]   # VMA 0x558620..0x558640
- [0x458640, rodata, src/cod/458640]
```

The compiler-emitted pool order (`0.2 0.9 0.2 0.7`) is byte-identical to ROM.
**This consumes boyact's one contiguous `.rodata` carve**, but creates no
disjoint-region problem: `jtbl_00558510` (0x558510..0x558620) *abuts* the pool,
so the region can later be widened backwards to `0x458510` once boyact's
switch function is matched.

## 2. What actually cracked the act-wrapper carve tails

### Type-based aliasing is LIVE

`tools/compile_c.sh` CFLAGS are `-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc
-fdata-sections`.  There is **no `-fno-strict-aliasing`**.  So for the 0xC4
BoxBar wrapper, whether

```c
D_004D3280[1] = ...;      /* store into the table  */
gobj->unkC4   = D_004D3280;  /* store the table ptr */
```

may be reordered depends on the *declared types*.  aug6's spelling
(`void *D[]` + `void **unkC4`) puts both stores in one alias set and reproduces
ROM; `int D[]` + `int *unkC4` lets gcc swap them.  st17b `func_0022F7E8` went
**6 → 0** on that change alone.  The lws_kyomi variant (a call sits between the
stores) wants the *int* spelling instead — pick per shape, do not standardise.

### `volatile` on the flag global pins it after the volatile param reload

Where ROM keeps `sw <1>,%gp_rel(D_006325B4)($28)` *after* the `lw $x,0($29)`
reload instead of hoisting it into the prologue, `D_006325B4` must be
`volatile`: two volatile accesses cannot be reordered, and the act param is
already `volatile int a0`.  st22a `func_002342F8` went **6 → 0** on that.
**Scope it with an `__asm__` alias** — making it `volatile` TU-wide regressed
the already-matched sibling in the same file (0 → 14).

### `-G8` array spelling, again

Two more instances of `[[extern_size]]`: `signed char D_006D35E0` and
`int D_006ABE00` are ≤ 8 B, so a *scalar* extern gp-rels where ROM wants
`lui/%lo`.  The array spelling (`D_006D35E0[]`, `D_006ABE00[]`, indexed `[0]`)
restores the far form and, for the jimaku switch, the missing 37th insn.

### Locals before the first store free the branch delay slot

commonact `func_0015B620` (21 insns, two ternary message selects + a
`debug_assertMessage` void tail call) only matched once the format-string
address and the `D_00631AE4` read were bound to **locals declared before** the
`|= 1` store.  That is what leaves the store available to fill the `bne` delay
slot; with the natural ordering gcc emits it early and is one insn short.

## Deferred (with best rc and the next hypothesis)

| func | TU | rc | state |
|---|---|---|---|
| `func_0022EE98` | st17b | **MATCHED (conv-10)** — sites 0 | Was never store *order* (all 24 permutations fold to 3 schedules). It was the ALIAS SET: the matched twin `func_0020A468` (src/e3) has a byte-identical instruction stream and shows the dev's typing — table `int *D_004D3140[]`, and BOTH GObj members pointers (`void *f_C0; void *unkC4;`). Spelling f_C0 as `*(int *)(gobj+0xC0)` puts that store in the `int` alias set, couples it to the D_006325B4 store and hoists `li 1` to slot 2, which cascades the whole v0/v1 census. Original note kept below for the record: Same 0xC4 wrapper as the matched `func_0022F7E8` but with **no intervening call**, so all four stores sit in the entry BB.  Insns 1–12 are byte-identical; only the 4-store emission order differs — ROM `gp, unkC4, D[1], unkC0`, ours `unkC0, D[1], unkC4, gp` (an exact reversal).  Exhausted: all 24 statement permutations × {int, `void*`} typing × {plain, `volatile`} `D_006325B4` × chained `gobj->unkC4[1]` spelling × an explicit second `int self = a0;` reload (that one *does* fix the reload placement at insns 7/9, but then `D[1]` floats to insn 9).  Next idea: something that makes the `D[1]` store *not ready* at sched time — e.g. the table entry reached through a pointer gcc cannot prove distinct from `*gobj`. |
| `func_00238BC0` | st47a | **MATCHED (conv-10)** — sites 0 | Same template; st47a DEFINES the table in-TU as `unsigned int D_004D3C10[8]`, so the natural spelling lands the element store in the `int` alias set (sites 7 / rc 3). A pointer-typed symbol alias, `extern int *D_004D3C10__bc0[] __asm__("D_004D3C10")`, restores the dev's alias set without touching the data definition. Byte-for-byte the same template as `func_0022EE98` (`D_004D3C10`/`func_00237C18`). Whatever cracks one cracks both. |
| `func_0023B650` | objact | **MATCHED (conv-10)** — sites 0 on the first compile | The `$f20` theory was wrong. `func_0017E660(int, float, float, float, float)` (EABI: four floats in $f12-$f15) takes 0.0f as BOTH arg1 and arg3; two uses of one loop invariant make it a loop.c movable, hoisted to the pre-header as `mtc1 zero,$f20` with both uses becoming `mov.s`. The earlier attempts were short an ARGUMENT, not short a lever. Original note: Structure exact (26 vs 24 insns).  Only residual: the `0.0f` argument.  ROM hoists `mtc1 zero,$f20` into the prologue and keeps it in a **callee-saved FPR for the whole act loop**; gcc rematerialises `mtc1 zero,$f12` inside the call block each iteration, so the `swc1 $f20,32(sp)` save and the init are missing.  A plain `float z = 0.0f;` before the loop is not enough.  Next idea: give the value a definition gcc cannot rematerialise. |
| `func_0015E388` | commonact | **7** | 27 vs 27 insns, identical multiset.  ROM groups the three `volatile` param reloads at insns 12/13/15 (three live regs) and interleaves the `0x15C` loads after them; ours emits strict `reload, load, store` triples.  Pure sched1 ready-list tie.  Tried: three `int b1,b2,b3 = a0` temps (rc17, worse). |

## Still open after conv-8

* **59 carved tails** remain (was 63 + 2 boyact + the 8 newly-found small ones
  minus the 23 matched).  Smallest-first: st17b `func_0022EE98`(22),
  st47a `func_00238BC0`(22), objact `func_0023B650`(26), commonact
  `func_0015E388`(28), jimaku `func_001759B0`(42), commonact `func_0015ADF0`(54)
  … up to girl_act `func_001725C8`(678).  The four ≤ 28 are the deferrals
  above; from `func_001759B0`(42) upward they are untouched ordinary
  convergence targets — mostly girl_act / commonact / enemy_act act coroutines.
* Unchanged from conv-7: `pac_continueTag` / `shiftMotionOrientEndFunc`
  (two-disjoint-`.rodata`-carves-per-TU), `actSt02aSecretItem` rc19,
  `bga_calcEnvelope`, the 8 `no-aug6-twin` pool/sound funcs, boyact
  `func_0014D978`/`func_0014DC28` (aug6 twins also unmatched).

**Recommended order for a conv-9:** (a) the 4 deferrals above — each is a
single named mechanism away and two of them are the *same* mechanism, so one
idea buys three functions; (b) the carved tails from 42 insns upward,
smallest-first, using the conv-8 lever set (alias-typing, scoped `volatile`
flag, `-G8` array spelling, locals-before-first-store); (c) conv-7's carry-over
list unchanged.

---

# conv-9 — carved-tail convergence (branch `conv-9`, base `b7789d22`)

Mission: conv-8's recommended order — (a) the 4 named deferrals, (b) the
carved tails from 42 insns upward, smallest-first.  Worked (b) first because
the two 22-insn deferrals are one shared mechanism and the tails are
independent.

**Result: 2 byte-matched**, commit `4ace9de0`, gated
`build.sh setup && ninja` → `verify_elf: OK (fbf50c75cd5911273511c4f9af90503ff8423582)`
+ `check_no_rom.sh`.  No yaml edits, no new crutches, no symbol_addrs changes.

| commit | scope | matched |
|---|---|---|
| `4ace9de0` | jimaku `func_001759B0` + girl_act `func_00174558` | 2 |

## What matched

### jimaku `func_001759B0` (41 insns, rc0 first try)

`jimakuHandler` in the same TU is the template for everything from the
`0xD0 & 0x10` spin-wait down.  The head adds
`func_00243B18(buf, gobj+0x4A0, -1.0f)` / `dispPlane(a0, buf)` /
`CylinderCollision(a0, gobj+0x580)`, and the two handler-field stores are in
ROM order `0xD0 = 0` **then** `0x14 = func_00175A58` (the sibling's order is
`0x30, 0x14, 0xD0` — source order is emission order, do not normalise it).

### girl_act `func_00174558` (57 insns, rc0 first try)

The head-scratcher here is a block of *apparently dead* argument setup
(`$f12 = 100.0f`, `$4 = buf30`, `$5 = $6 = 0`, `$7 = 0xFF`) sitting between
`jal actCommonBackhand` and the loop-back `bnez`.  It is **not** dead: it is
the argument block for `debug_Marker(buf30, 0, 0, 0xFF, 100.0f)` at the *top*
of the `while` body, reached by the back-edge.  The entry `b .L001745E4`
jumps into the bottom test.  So the shape is

```c
actCommonTurn(a0, buf30, buf10, 1, 20.0f);
while (actCommonBackhand(a0)) {
    debug_Marker((int *)buf30, 0, 0, 0xFF, 100.0f);
    func_0015CD70(a0);
    _ACTWait(1);
}
```

**Generalise:** in an act coroutine, argument setup that follows a call and
precedes a backward branch belongs to the *first call of the loop body*, not
to anything after the branch.  Read the back-edge before calling it dead.

## New levers proven this pass (all crutch-free source shapes)

1. **`||`-merged candidate chain restores the `daddu` copy.**
   A "pick the first non-null of N globals" chain whose arms are
   `target = cand; goto found;` gets `cand` coalesced into `target` (the load
   lands straight in the callee-saved reg, delay slot goes `nop`) — because
   the load, the compare and the copy end up in one basic block.  Merging the
   arms with `||` into a single `if` puts the copy in its **own** block with
   two predecessors, so CSE cannot fold it, and reorg then duplicates it into
   *both* branch delay slots — exactly ROM's
   `bne $5,$0,out / daddu $16,$5,$0` pair.  `func_0015ADF0` **33 → 12** on
   this one change.
2. **A `volatile` alias on the *fallback* read kills a `movz`.**
   `target = D_X; if (target) goto found; target = D_Y;` if-converts to
   `movz` when `D_Y` is already in a register.  Spelling only the *last* read
   through a second, `volatile`-qualified `__asm__`-aliased extern makes the
   MEM have side effects, blocks both the CSE and `jump.c`'s conditional-move
   conversion, and reproduces ROM's fresh `lw $16,%gp_rel(D_Y)($28)`.
   (`func_0015ADF0` 28 → 22.)
3. **Bind a call's `volatile`-param argument to a local *assigned after the
   preceding call*.**  Pulling the volatile `a0` reload up so it precedes the
   handler store — without giving it a live range that crosses a call — is
   `void *self; ...; f(...); self = (void *)a0; ...; g(buf, self);`.
   Declaring-and-initialising it at the top instead makes it live across the
   first call and burns a callee-saved register (regressed
   `func_0015E1B0` to rc36).  `func_0015E1B0` **27 → 6** with the late
   assignment.
4. **Two out-of-line one-call arms = `switch`, not `if / else if`.**
   ROM `beq m,K1,L1 / beq m,K2,L2 / b Ldefault` with both bodies out of line
   is gcc's *switch* expansion.  `if (m==1) ... else if (m==2) ...` emits the
   first body inline and cross-jumps.  (`func_0015E1B0` 27 → 23 and the count
   went 60 → 62.)
5. **A float constant passed as a call argument inside a loop only lands in a
   callee-saved FPR (`$f20`) when it is written as a *literal at the call
   site*.**  Routing it through `float one = 1.0f;` makes gcc give the pseudo
   a `REG_EQUIV` note and rematerialise `lui/mtc1 $f12` per iteration.
   (`func_001754F8`; this is the same class as conv-8's deferred objact
   `func_0023B650` — try the literal there.)

## Deferred (best rc + the next hypothesis)

| func | TU | rc | insns | state |
|---|---|---|---|---|
| `func_0015E1B0` | commonact | **6** | 62 = 62 | Structure exact.  Residual is purely *which* insn reorg puts in the `ChangeMailInLadder` delay slot: ROM uses the `daddu $4,$17,$0` buf-arg copy and keeps `sw v0,0x18(s0)` in line; we schedule the copy before the store and reorg takes the store.  Tried: fn-ptr-typed handler store, `volatile` handler store (rc22), `int*` vs `char*` base, hoisting the address constant to a local, an explicit `float *bp = buf;`.  Next: something that raises the store's sched1 priority (it currently has no successor in the block, so `daddu`→call always outranks it) — e.g. a second use of the stored value, or getting both arg-setup insns adjacent so they form one SCHED_GROUP with the call and the store is forced out in front. |
| `func_0015ADF0` | commonact | **7** | 54 = 54 | Instruction *order* is exact; all 7 diffs are register naming.  ROM: const=`$3`, read1=`$2`, read2=`$7`, deref164=`$6`; ours: const=`$2`, read1=`$4`, read2=`$6`, deref164=`$3`.  local-alloc's `QTY_CMP_PRI = floor_log2(n_refs)*n_refs*size/(death-birth)` says our address constant has the *shortest* range at local-alloc time (so it takes `$2` first), i.e. our sched1 leaves the `lui/addiu` at the store and sched2 hoists it, while ROM's sched1 already had it in the prologue.  Next: make sched1 (not sched2) emit the `%hi/%lo` pair early.  Best source is in this pass's scratch (`adf0_rc7.c`); the shape is `char *s164` + `int self15C = a0` + `void *self = (void*)a0` + the `\|\|`-merged selection + the volatile fallback read. |
| `func_001754F8` | girl_act | **MATCHED (conv-10)** — sites 11 -> 2 -> 0 | The rotation is gcse PRE (lazy code motion); the `.gcse` dump names it: `PRE/HOIST: edge (0,1), copying expression 2` = `(lt (reg i) 3)` and expression 3 = `(plus (reg i) 1)`. Writing `cont = i < 3; i++;` leaves BOTH locally anticipatable at the top of the guarded block, so PRE hoists both — and the compare needs a loop-carried carrier register (the extra $sN + `daddu`). Putting the increment FIRST kills antloc for the compare (its operand is redefined earlier in the block), so only the increment rotates: no extra register, sites 11 -> 2, residual = the rotation shifting both constants by one. Starting the counter at **0** instead of 1 puts the rotated constants exactly on ROM's `li i,1` / `slti ...,3`. None of the previously-tried variants could work: they all leave the compare anticipatable. 67 vs 64 | `$f20` and the six `ContinueCorrectPosition` stores are exact.  Residual: gcc rotates the `cont = i < 3; i++;` pair one iteration ahead — it emits `li cont,1; li next,1; li i,2` and an in-loop `daddu cont,next,zero`, costing 3 insns and one extra callee-saved register.  ROM keeps a single `$18`/`$17` pair with `i` initialised to 1.  Tried: `cont = i++ < 3`, update at end of block, decl order, goto-CFG loop (rc26 *and* it loses `$f20`).  Next: a spelling where the first update is not constant-foldable, or where `i` is not a simple biv. |
| `func_0015DF88` | commonact | **25** | 65 vs 62 | Control flow is right.  Two residuals: (a) gcc parks `&buf[0]` in a callee-saved register (`addiu s2,sp,16` + `daddu` at each use) where ROM rematerialises `addiu $r,$29,0x10` at all four uses; (b) reorg duplicates the target block's `lwc1 $f12,%gp_rel(D_00630CCC)` into three branch delay slots where ROM leaves `nop`s and fills one delay with the following `slti`. |
| `func_001619A8` | enemy_act | **MATCHED (conv-11)** — sites 7 -> 0 | 78 vs 72 | The callee-saved-`&buf` class is CLOSED, and this was its second member. **Fix: move the scratch buffer into a `static __inline__` helper that owns it.** Mechanism: cse1 merges the two `(plus at 32)` occurrences into one 3-ref pseudo (`cse_end_of_basic_block` only breaks at a CODE_LABEL and there is none between the two argument setups), and REG_N_REFS == 3 disqualifies local-alloc's `reg_equiv_replace` path in `update_equiv_regs` — the path that deletes the init insn and substitutes the `(plus fp K)` invariant back inline, i.e. ROM's per-use `addiu`.  Putting the array in an inline helper gives each use its own expansion scope so the merge never happens.  **Two things must move with it or the fix regresses:** (i) the node pointer has to be RE-READ from `D_00631AE8` *inside* the helper — passed in as a parameter it becomes a loop-invariant pseudo and gcc hoists `lw $16,0(gp)` into the pre-header (sites 8), where ROM reloads it every iteration; (ii) with the buffer inside the helper the threshold goes back to a plain `0x59` literal — the `int thresh` local that was REQUIRED at sites 7 costs a site once the helper exists.  Frame: ROM's 48 B of locals are a single `char buf[0x20]` with the callee handed `buf + 0x10`, the same two-half scratch idiom as the matched sibling `actGirlDitch3mReady` (src/girl_act) — no dummy local needed.  Retained from the earlier pass: the abs must be a TERNARY (`d = (d < 0) ? -d : d;`) so jump.c's conditional-move transform does not fire and ROM's `bltzl/negu` survives, and `mode = (d <= 0x59) ? 1 : 2;` gives ROM's `addiu v1,2` + `movz` rather than the inverted movn. |

**Recurring open class — "gcc parks a local array's address in a callee-saved
register".**  Seen in `func_0015DF88` and `func_001619A8` and it is worth
cracking once: ROM always recomputes `addiu $r,$29,OFF` at each use inside the
act loop.  Every attempt to pass the array more "directly" leaves the CSE in
place.  Cracking it should unblock several of the mid-size act-thread tails at
once.

## Still open after conv-9

* **57 carved tails** (59 minus the 2 matched).  Smallest-first: st17b
  `func_0022EE98`(22), st47a `func_00238BC0`(22), objact `func_0023B650`(26),
  commonact `func_0015E388`(28), commonact `func_0015ADF0`(54, rc7),
  commonact `func_0015E1B0`(62, rc6), girl_act `func_001754F8`(64, rc15),
  commonact `func_0015DF88`(62, rc25), enemy_act `func_001619A8`(72, rc31),
  … up to girl_act `func_001725C8`(678).
* Unchanged from conv-8: `pac_continueTag` / `shiftMotionOrientEndFunc`,
  `actSt02aSecretItem` rc19, `bga_calcEnvelope`, the 8 `no-aug6-twin`
  pool/sound funcs, boyact `func_0014D978`/`func_0014DC28`.
* **427 unmatched vendor functions** (161,540 B), opened as queue groups
  **V1–V6** in the next section.  They are ordinary matching work and belong
  in the same list as the carved tails, not in a side queue — see the
  recommended order immediately below.

**Recommended order for a conv-10** (one list; vendor groups V1–V6 are
defined in "Vendor queue" below and are ranked here by tractability, not
segregated):

1. **V2 — the 52 handwritten-asm twins already solved on aug6** (7,324 B).
   Highest yield per hour in the whole queue: each one has a finished,
   byte-matching aug6 body sitting in `common/src/PObj.c`; the port tool
   simply could not see it (it looks for a *C* definition, and these are
   bare `__asm__` blocks).  Twelve of them are 4 insns.  Start here.
2. `func_0015E1B0` (rc6) and `func_0015ADF0` (rc7) — both are one named
   mechanism from zero and the mechanism is written out above.
3. **V1 — the 21 genuine port reverts** (1,664 + 1,320 B).  Every one has a
   near-miss baseline with the first divergent instruction already recorded
   in `decomp/port_ledger.md`; the smallest is 4 insns.  The 7
   `unresolved-symbol` reverts are not matching problems at all — they are
   symbol-binding problems, and 3 of them are the same `D_FFFFF` /`D_FFFF`
   pseudo-symbol.
4. The callee-saved-`&buf` class, which unblocks `func_0015DF88` +
   `func_001619A8` together.
5. **V0 — identify the upstream libgcc / newlib / fdlibm release** (§3a
   prerequisite).  Not a match; it is the research item that unblocks
   ~61 KB of vendor with a legitimate reference implementation.  Highest
   *leverage* item in the queue, and it can run in parallel with 1–4.
6. **V3 — the 40 head functions** (5,056 B), smallest-first from
   `func_00101A88`(6).  §3b clean-room, but 29 of the 40 are ≤ 20 insns.
7. conv-8's four deferrals, starting by trying lever 5 (float literal at the
   call site) on objact `func_0023B650`.
8. **V4 — the 52 no-aug6-twin tail functions** (27,112 B), smallest-first
   from `func_00268F28`(7).  Original work, no baseline, but the small end
   is genuinely small.
9. The untouched carved tails from `func_0015D1F8` upward.
10. **V5 — the 261 tail functions whose aug6 twin is `INCLUDE_ASM`
    upstream** (118,972 B), smallest-first from `func_00261BA8`(24).  The
    bulk of the remaining vendor bytes and the slowest class: no baseline,
    mostly §3b clean-room.  The 13 members that fall in the fdlibm evidence
    window (V5a) should be pulled forward as soon as V0 lands.

`func_0026F578` (V6) is **blocked, not queued** — see below.

# Vendor queue — the 427 unmatched vendor functions (opened 2026-07-29)

Vendor code is defined by `decomp/VENDOR.md`: `.text` that came out of a
pre-built `.a` at link time (crt0, SCE SDK, newlib/libgcc/libm), not out of
an ICO translation unit.  The aug6->retail vendor port landed in `3a806b95`,
`6f01ebf6`, `22f1b2b6`, `bca0d69a`.  What it did **not** land was in no
queue any worker reads.  This section is that queue.  It is part of the
*same* list as the carved-tail work above — the recommended order at the
end of the conv-9 section interleaves both.

## Reconciliation — 948 vendor functions, not 945; 427 unmatched, not 424

Derived from the tree, not from the port report:

* `docs/progress.json` `vendor` node (built by `tools/progress_tree.py` from
  the `// (vendor)` notes and the `c` subsegment spans in
  `config/ico.us.yaml`): **521 / 945** functions, 34,144 / 194,996 B.
* The `INCLUDE_ASM` sets of the nine `src/cod/vendor_*.c` TUs total **397**;
  the three still-`asm` vendor spans hold **30** more symbols
  (`config/symbol_addrs.us.txt` lines 5, 248-250, 404-428, 6051).
  397 + 30 = **427**, which is 3 more than `945 - 521 = 424`.
* The three extra are **`func_00246B78`**, **`func_002658B8`**,
  **`func_00268F28`**.  Splat emits a `.s` for each
  (`asm/nonmatchings/src/cod/vendor_2453C0/func_00246B78.s`,
  `.../vendor_25E1E8/func_002658B8.s`, `.../vendor_2668B8/func_00268F28.s`)
  and the TUs `INCLUDE_ASM` them, so they are in the build — but they are
  **absent from `config/symbol_addrs.us.txt`**, so `progress_tree.py` never
  counts them.  Compare their neighbours, which are all present
  (`func_00246B38`/`func_00246BD8` at lines 5415-5416, etc.).
* Their sizes (from the `nonmatching <name>, 0x<size>` headers) are 0x5C +
  0x238 + 0x1C = 688 B.  So the honest totals are **948 functions /
  195,684 B vendor, 521 matched, 427 unmatched / 161,540 B**.

> **Queue item (config, not docs): DONE 2026-07-29.**  The three
> `func_… = 0x…; // type:func` lines are now in
> `config/symbol_addrs.us.txt`; `build.sh setup` + `ninja` re-verify
> byte-identical, so the symbols are pure accounting.
> `tools/gen_us_symbol_addrs.py` still drops them and was left alone — it is
> a one-off generator the build never runs.
>
> **Correction to the byte half of this reconciliation.**  "948 functions /
> **195,684 B**" was arrived at by adding the three functions' 688 B to
> `progress_tree.py`'s 194,996.  That is double-counting: the vendor
> `total_bytes` is derived from the **yaml spans**, not from the symbol
> list, so those 688 B were always inside it.  The function count was 3 low;
> the byte count never was.  **948 functions / 194,996 B** is the honest
> pair, and the unmatched byte figure below (161,540 B) is likewise 688 B
> high — it is 160,852 B.

Second tooling nit, also left alone: `tools/progress_tree.py:130-131` carries
a fixed two-element label list (`crt0 + libkernl prologue`, `libc / libgcc /
SCE SDK tail`) and applies it by run index.  The head is now **three** runs,
so the `0x00100C90-0x00101C80` run is labelled *"libc / libgcc / SCE SDK
tail"* when `decomp/VENDOR.md` §1 says the whole head span is crt0 +
libkernl, and the `0x0026F578` run gets no label at all.  Cosmetic; believe
VENDOR.md §1 over the dashboard label.

## Group summary

| group | n | bytes | insns | min | median | max | legal category (VENDOR.md §3) |
|---|--:|--:|--:|--:|--:|--:|---|
| ~~**V1** 21 genuine port reverts — unresolved-symbol~~ **LANDED 2026-07-29** | 0 (was 7) | 0 (was 1664) | — | — | — | — | n/a |
| **V1** 21 genuine port reverts — codegen | 5 (was 14) | 536 (was 1320) | 134 | 8 | 32 | 48 | unclassified -> §3b clean-room unless archive identified |
| **V2** 52 handwritten-asm twins solved on aug6 | 2 (was 52) | 144 (was 7324) | 36 | 12 | 18 | 24 | §3b clean-room (already re-derived on aug6) |
| **V3** 40 head functions | 14 (was 40) | 3416 (was 5056) | | 14 | | 370 | §3b proprietary (crt0 + libkernl, VENDOR.md §1) |
| **V4** 52 tail functions with no aug6 twin | 34 (was 52) | 24580 (was 27112) | | 22 | | 1350 | unclassified -> §3b clean-room unless archive identified |
| **V5** 261 tail functions, aug6 twin unmatched | 261 | 118972 | 29743 | 24 | 74 | 1140 | mixed: 13 in the fdlibm window are §3a; rest unclassified |
| **V6** 1 blocked (inter-section pad) | 1 | 92 | 23 | 23 | 23 | 23 | n/a — blocked |
| | **332** (was 427) | **147,976** | | | | | |

**Landed 2026-07-29, five passes: 110 functions / 13,572 B.**
Pass 1 (`vendor-1`, 66 funcs / 9,604 B): V2 50/52, V1 16/21.
Pass 2 (`vendor-2`, 21 funcs / 1,108 B): V3a 11/11, V3b 10/26 + the carve.
Pass 3 (`vendor-3`, 14 funcs / 1,148 B): V3b 5 more (15/26), V4 first 9.
Pass 4 (`vendor-4`, 5 funcs / 908 B): V4 14/52 — two template families closed.
Pass 5 (`vendor-5`, 4 funcs / 804 B): V4 18/52 — the device-request family is
now **7 members**, and the static-chain class is ruled out for vendor (below).
Vendor moves 521/945 -> **616/948** functions and 34,144 -> **47,020 B**
(17.51 % -> 24.11 %); `.text` 16.81 % -> **19.34 %**.  The unmatched vendor
total is now **332 functions / 147,976 B** (figures from
`docs/progress.json`, whose byte denominators are span-derived).

### The static-chain (nested-function) class does NOT apply to vendor — checked 2026-07-29

Ran `tough_nuts/acttails_near_misses/scan_static_chain*.py` over **all 313
still-`INCLUDE_ASM` vendor functions**.  Result: **one** callee-test hit, and
it fails the call-site half, so the class is empty here.

* The hit is `func_0024B500` (224 insns).  It is an **exception/interrupt
  handler**, not a nested function: it saves the whole register file to a
  context block at `D_00717440` through `$k0` (`sq $1,0x10($26)` …
  `sq $2,0x20($26)` …), so it "reads `$2` before writing it" because it
  *saves* `$2`.  It has **no `jal` caller at all** — `func_0024B300` only
  ever takes its ADDRESS (`lui`/`addiu` `%hi`/`%lo`) to install it.  Both
  halves of the test fail.
* **`func_00260BA0` is ruled out** — it was in the scanned set and does not
  hit the callee test, so its 2-site residual is not a nested-function
  relationship.  The next attempt there still needs a data-model change, but
  not that one.
* **Known false-positive class for vendor code:** a function that issues an
  **inline syscall** reads the kernel's result out of `$2` before writing it,
  which is the callee test's exact signature.  `func_00100F18` and
  `func_00101030` both trip it and both are matched, ordinary C.  Anyone
  re-running this scan over vendor should expect those.

**Mechanisms found across these passes that generalise beyond their functions** (run these as a first-diff checklist BEFORE any allocation reasoning):

0. **`-G 8` makes a small `extern` scalar $gp-relative.**  A 1- or 4-byte
   `extern int D_X;` is small data, so gcc emits `lw v0,0(gp)` where the ROM
   has a far `%hi`/`%lo` pair.  Declaring it an **incomplete array**
   (`extern int D_X[];`, used as `D_X[0]`) restores far addressing.  This
   turned up three separate times in pass 3 and is the single most common
   first-diff on a vendor function that reads a global.
0b. **Two stores of the SAME value come out in REVERSE source order.**
   sched1 flips that pair (and schedules an unrelated store between them).
   Confirmed twice now — `func_002456F8` and `func_00246B78` — so write the
   second one first.  Where the pair is the last thing in the function this
   is also what leaves the second store in the `jr` delay slot.
0d. **Two globals used both as a field base and as a call argument want a
   CACHED POINTER.**  The ROM forms the address once and reuses the
   register; spelling the field access as `*(int *)(D_X + off)` and the
   argument as a separate `D_X` makes gcc derive the address twice and
   costs several sites in addressing alone.  The inverse also occurs in
   the same family — where the ROM folds `%lo` into the store and forms
   the full address only for the argument, the plain (uncached) form is
   right.  **Read which one the ROM did; do not assume.**
0e. **Fewer named temporaries, not different ones.**  A residual v0/v1 swap
   that survives every reordering often disappears when intermediate
   locals are deleted and the body is written in the same shape as a
   matched sibling.
0c. **Recover the data model before fighting the allocator.**
   `func_00100FB0` sat at a wholesale register permutation (base and entry
   pointers swapped) that neither caching the pointer nor reordering
   touched; writing the object as the struct it actually is — an 8-byte
   header followed by 512 two-byte records — went straight to 0 sites.
1. **gcc's `#.set volatile` marker blocks the period assembler's
   delay-slot fill.**  Three functions so far end at exactly this residual
   (`func_002453D0`, `func_001010C8`, and it is what cost `func_002456F8` a
   match until the prototype's store-order `volatile` was dropped).  Any ROM
   function whose `jr` delay holds a store that C would want `volatile` is
   on this axis.  Where the `volatile` is a real MMIO poke the function is
   **left `INCLUDE_ASM`** — dropping it to win the byte would be a crutch
   dressed as source.
2. **An inline-asm read must write its DESTINATION, not return a value.**  A
   value-returning statement-expression makes the read a separate pseudo
   from the variable it feeds, so a following mask/compare lands in a
   different register.  This took four V3a functions from rc2 to rc0 at
   once and is why `MFC0_STATUS` takes an lvalue.

`min`/`median`/`max` are instruction counts.  Every count below is
`bytes / 4` from `docs/progress.json`; a `*` marks one of the three
symbol-table orphans above (size read from the `.s` header instead).

## V1 — the 21 genuine port reverts (2,984 B, 746 insns) — **V1a done, 14 left (1,320 B)**

The most tractable class in the queue that still needs actual matching (V2
needs transcription, not matching): each one *has a near-miss baseline* and
`decomp/port_ledger.md` records the first divergent instruction.  The
port ledger holds 31 `REVERTED` vendor entries; commit `bca0d69a` recovered
the 10 declaration-context ones (`[undeclared]`, `[parse]`,
`[callee-sig-conflict]`), leaving these 21.  Reason text is quoted verbatim
from the ledger.

### V1a — 7 `unresolved-symbol` (1,664 B).  **ALL 7 LANDED 2026-07-29**

The premise held exactly: none of the seven was a codegen problem, and none
needed a matching grind.  All seven were bugs in the port driver's symbol
binding, in four distinct classes — every one a *class*, not a special case,
so each fix retires the class tree-wide:

1. **`retail_defined_labels()` did not recognise `alabel`.**  The regex took
   `glabel|dlabel|jlabel|jtbl_label` only, so a reloc onto an *alternate
   entry* looked unbindable.  `D_0024B740` is defined by
   `asm/.../vendor_24AAC8/func_0024B500.s` — it was there all along.
   (`ehlabel` was missing too; added.)
2. **splat does not zero-pad an UNDEFINED symbol.**  The walk synthesises
   `D_%08X`, but `config/undefined_syms_auto.us.txt` spells the same thing
   `D_71EB70` / `D_FFFFF`.  Hence "retail symbol D_0071EB70 undefined" for a
   symbol the link resolves fine.  The walk now falls back to `D_%X`, and
   `retail_defined_labels()` reads the `config/undefined_*.txt` tables.
   *This is the `D_FFFFF` "absolute address spelled as a symbol" that this
   section previously called a spelling decision — it was neither a decision
   nor a spelling problem; the name simply existed under a different form.*
3. **symbol + addend.**  `func_0024BFD0` takes the address of a point
   *inside* another function (`(char *)func_002484A4 + 4`, the ISR entry).
   Retail names only function starts, so `0x0024BFA8` had no symbol.  The
   walk now binds to the retail function that CONTAINS the address, but only
   when the offset agrees with the aug6 side's, so a mis-aligned slot still
   aborts.
4. **a `%lo` with no `lui` partner is not an address.**  It is splat's
   spelling of a bare constant addend (`addiu $2,$2,%lo(D_FFFF)`).  Both
   trees name such a constant after its own value, so when the words agree
   and retail declares the same name with the same value it binds to itself.

Two further driver bugs surfaced while landing these, both general:

* **identifiers inside `__asm__("…")` were counted as C declarations.**  Now
  that handwritten-asm bodies are spliced in (V2), the name in
  `"glabel func_X\n"` made the extern synthesiser think `func_X` was already
  declared — so the next ported body called it undeclared.  String literals
  are now stripped before the `declared` scan.
* **a ported block needs `.align 3`.**  When the PRECEDING function is C,
  gcc does not emit the ROM's inter-function pad word, and splat's `.s`
  (which used to own it) is gone.  Porting `func_0024B360` to C therefore
  shifted the whole TU by 4 bytes — `ninja` caught it, `quick_diff` did not.
  `render_asm_block` now always emits `.align 3`; it is a no-op wherever
  alignment already holds, which is why the earlier blocks still verify.

Three of the seven (`func_0024B360`, `func_0024BFD0`, `func_0024DFC8`) end
at a `quick_diff` FALSE NEGATIVE, not a real diff: an in-TU `%hi`/`%lo` that
the built object resolves and the isolated baseline leaves at 0
(`addiu a1,a1,0` vs `addiu a1,a1,3192`).  `_tolerable_pair` grants that
tolerance to *calls* only — the immediate-only form carries no symbol name
in the disassembly, so it cannot be checked the same way and was NOT
widened.  They were installed and gated on `ninja` instead, which is the
authoritative gate anyway.

`func_00263AA0` additionally needed its carried helper moved *below* the
typedef it uses: `top_insertion_point` puts carried helpers in the file's
leading header block, above the TU's existing typedefs.  Left as a known
driver limitation — one hand move, and `match_diff` then reads
`real_count 0`.

### V1b — 14 `codegen` (1,320 B).  **9 LANDED 2026-07-29, 5 left (536 B)**

**First, a correction to how this group was characterised.**  "Retail source
genuinely differs" was true of only four of the fourteen.  Five of them
already matched, and the recorded "first divergence" was a **`quick_diff`
false negative**, not a diff: the isolated single-function baseline object
leaves an in-TU `%hi`/`%lo`/`jal` slot at 0 while the built multi-function
object resolves it.  That is the whole of the `addiu <r>,<r>,0 vs a real
displacement` family (3) and the `jal`/`j` to self family (2 of 3).
`tools/match_diff.py` filters this correctly — **read `real_count` from the
oracle, never the driver's recorded first divergence** — and all five link
byte-identical.

`_tolerable_pair` was NOT widened to cover them: it grants the tolerance
only where the disassembly names the resolved symbol (a call), and the
immediate-only form carries no name, so widening it would mask real misses.
They were gated on `ninja` instead.

| func | insns | outcome |
|---|--:|---|
| `func_0026A5E0` | 4 | **LANDED** — false negative (`j` to self) |
| `func_0024FBF8` | 18 | **LANDED** — false negative (`%lo`) |
| `func_0026A438` | 22 | **LANDED** — false negative (`%lo`) |
| `func_0024B300` | 24 | **LANDED** — false negative (`%lo`) |
| `func_0026A600` | 36 | **LANDED** — false negative (`%lo`) |
| `func_00264D90` | 26 | **LANDED** — return-value semantic, see below |
| `func_00264DF8` | 28 | **LANDED** — return-value semantic, see below |
| `func_00268DA0` | 22 | **LANDED** — return-value semantic, see below |
| `func_002456F8` | 10 | **LANDED** — store-order data model, see below |
| `func_002453D0` | 16 | left, rc2 — delay-slot/`volatile`, see below |
| `func_00246888` | 36 | left, rc2 / **1 site** — `lui v1,%hi / addiu v1,v1,%lo` vs `lui v0 / addiu v1,v0`.  Both build `&D_00714BC0` in `$3`; only the `lui` destination differs, i.e. ROM's `high` pseudo and `lo_sum` destination got the SAME hard register and gcc's did not.  Refuted 2026-07-29 (all leave it at 1 site, so all are the same axis): a cached base pointer (§5.10's lever), retyping the extern `int[]` -> `char[]`, and flipping the local declaration order.  A DIFFERENT axis is needed — the two allocnos are short-lived and adjacent, so what has to change is what else is live at that point, not how the address is spelled. |
| `func_0024C400` | 32 | left, rc8 / 7 sites — first divergence is an inserted `lw a0,0(s0)`.  Not yet reasoned about. |
| `func_00252C68` | 48 | left, rc4 — the ported body is 50 insns against a 48-insn ROM span, i.e. genuinely 2 instructions long.  Not a reloc artifact. |
| `func_00260CA8` | 8 | **BLOCKED, not a matching problem** — see below |

**The `lw v1` vs `lw v0` family (3 funcs) — a return value, not allocation.**
Each is a `vsnprintf`-shaped wrapper: fill a 0x60-byte sink descriptor on the
stack, call the formatter, then NUL-terminate through the descriptor's first
word.  ROM loads that pointer into `$3`; gcc used `$2`.  ROM never writes
`$2` after the `jal` — **the callee's return value is still live**, so `$2`
is simply unavailable and the load has to go elsewhere.  The prototype threw
the count away (a `void` wrapper); retail returns it.  Spelling the call
`n = func_00266970(...); …; return n;` and retyping the callee
`extern int func_00266970();` takes all three to `real_count` 0.  (The
retype is shared — `func_002642D8`, already matched, was re-checked.)

**`func_002456F8` — a `volatile` that costs the match.**  The prototype
pinned this print-sink initialiser's store order with
`extern volatile int D_00713000[]`.  On retail that is wrong twice over:
gcc's `#.set volatile` markers stop the assembler moving the last store into
the `jr` delay slot where the ROM has it, and the pin is not needed anyway.
Dropping it and recovering the order from the data model matches: a
0x10-byte header (two ints, then two cursors that both start at the payload
at +0x10), written in declaration order, with **the two SAME-VALUED pointer
stores written in REVERSE of the order they are emitted in** — sched1 flips
that pair and schedules the int store between them, which is exactly what
leaves the second pointer store in the delay slot.

**`func_002453D0` — the same delay-slot class, and the `volatile` is real.**
Its final store is a genuine MMIO poke (`*(volatile int *)0x1000F000 = 4`
after a hazard-nop polling loop), so `volatile` is correct; with it the
assembler will not split the `sw <absolute>` macro across the delay slot
(ROM: `lui $1,0x1001` before the `jr`, `sw $2,-0x1000($1)` in the delay).
Everything else in the function matches.  Left `INCLUDE_ASM` at rc2 rather
than making the poke non-volatile to win the byte — that would be a crutch
dressed as source.  **Generalisable finding: gcc's `#.set volatile` marker
blocks the period assembler's delay-slot fill.**  Any ROM function whose
`jr` delay holds a volatile-looking store is on this axis.

**`func_00260CA8` — blocked on a missing symbol table entry, not codegen.**
Its aug6 twin reads and writes an absolute address that **splat annotates on
neither side** (aug6's own `.s` carries no reloc for it — the words are just
`lui $3,0x72` / `lw $2,-32280($3)`), so the lockstep walk never sees a slot
to rebind and the ported body keeps the aug6 address, `D_007181E8`.  The
retail address is `0x0071EB68`.  `ld` then fails with an undefined
reference, which is the honest outcome: **there is no retail symbol for
0x0071EB68 and no place to declare one.**  `config/undefined_syms_auto.us.txt`
is regenerated by splat — a hand-added line is dropped on the next
`build.sh setup` (verified).  Unblocking it needs a
`config/undefined_syms_extra.us.txt` wired into `tools/gen_ninja.py` and
`tools/build.sh` the way `undefined_funcs_extra.us.txt` already is.  That is
a build-system change, deliberately not made from a matching pass.  Note it
also blocks any future port whose aug6 body names an address splat does not
annotate.

## V2 — 52 handwritten-asm twins already solved on aug6 (7,324 B, 1,831 insns)

**This group did not exist in the port report, and correcting it is the
single most useful thing in this section.**

`decomp/VENDOR.md` §7 said, as landed by `bca0d69a`: *"Of the 455 pairs whose
aug6 twin carried a matched baseline `.s`, only 403 were real: 52 were stale
`matchings/*.s` for functions aug6 has since reverted to `INCLUDE_ASM`."*
**That does not hold up against the tree** (§7 now carries the correction).
Checked at the pinned aug6 commit
`3a5ab90e34bb41993cd70087d46366db870571bd`
(`.port_cache/candidates.json:aug6_head`):

* All 716 aliased pairs (`.port_cache/name_alias.json`) split cleanly:
  455 have a `.s` under `asm/aug6/matchings/common/src/PObj/` **and** are
  *not* `INCLUDE_ASM` in `common/src/PObj.c`; 261 are `INCLUDE_ASM` **and**
  have no `matchings/*.s`.  **Zero** are stale in the sense §7 describes.
* The 52 dropped ones are all defined in aug6's `PObj.c` — as **bare
  `__asm__` string blocks** (`"glabel func_…\n"` / `".global func_…"`),
  not as C functions.  `tools/port_from_aug6.py:410-419` drops a candidate
  when `src.tu(stem)["funcs"]` — a *C definition* index — does not contain
  the name, and labels the drop "stale".  For these 52 the label is wrong:
  the body exists and byte-matches.
* None of the 52 appear anywhere in `decomp/port_ledger.md`, and none are in
  `.port_cache/candidates.json:records`.  They were never candidates.

These are the repo's sanctioned handwritten-asm exception (VU0 macro-mode,
MMI, privileged COP0/TLB/cache, EE syscall stubs — `decomp/COOKBOOK.md` §6
"Unaligned and MMI" and §12.4 "fall back to modern gas for VU0 / MMI TUs",
plus `include/r5900.h` / `include/vu0.h`).  Carrying them over is
transcription plus reloc rebinding, not matching.  Twelve of them are 4
insns.

Legal: **§3b clean-room**.  They were re-derived from the disassembly on the
aug6 branch and carry no upstream provenance; porting our own clean-room
work across branches introduces nothing new.

### V2 status — 50 landed 2026-07-29 (7,180 B), 2 held

Landed on `vendor-1`, whole-ELF SHA-1 green (`fbf50c75…`).  Done by
**teaching `tools/port_from_aug6.py` to index bare-`__asm__` definitions**
rather than by hand — the mislabel is a real bug in a driver every worker
runs, the fix is ~120 lines, and the hard part of a vendor port (the
lockstep reloc-slot rebinding) is machinery the driver already has.  What
was added:

* `aug6_asm_block_index()` — parses file-scope `__asm__("…")` blocks out of
  an aug6 TU, keyed by the symbols they define (`glabel NAME`, or
  `.global NAME` + `.type NAME,@function` + `NAME:`).  The `@function`
  requirement matters: `func_00251028`'s block also exports an inline MMI
  mask `D_00251070`, which must not look like a twin.
* `cmd_scan` consults it, so these stop being dropped as "stale".  Tree-wide
  the stale count falls **117 -> 58**; the 59 recovered are 53 in
  `common/src/PObj` (the vendor group) and 6 elsewhere.
* `cmd_port` gained a handwritten-asm branch: no extern / typedef / helper
  / decl-alias synthesis (an asm block has no C scope), just symbol
  rebinding — `rebind_text` already rewrites *inside* string literals,
  which is exactly where an asm block's symbol names live.
* **Two porting hazards found the hard way, both now handled by the tool:**
  1. *Inter-function padding is a property of the LINK, not the body.*
     aug6 blocks carry the ROM padding that follows them, and several count
     it *inside* `.size` where splat puts it *after* `endlabel`.  Copying
     either verbatim is wrong here.  `split_asm_body()` discards every
     instruction outside `glabel..endlabel`, and `retail_asm_shape()` reads
     the body/pad split back out of the retail baseline `.s`.  The first
     attempt used the aug6 padding, passed `quick_diff` on all 45 (padding
     is outside the compared range), and **failed `ninja` with the whole ROM
     shifted 128 B** — a clean demonstration of why the SHA-1 gate is the
     gate.
  2. *`.L<hex>` branch targets are named after the aug6 address*, and the
     retail TU can already hold an INCLUDE_ASM'd sibling whose splat `.s`
     names a label after the same hex — the two address spaces overlap.
     They are now uniquified per function (byte-neutral: internal targets).
     Note the rename must NOT go through `rebind_text`: its `\b` prefix
     cannot match a leading `.` (both neighbours are non-word chars, so
     there is no word boundary there) and every rename silently no-ops.
  3. *A `.word`-only body still emits words.* An all-MMI body is spelled as
     raw encodings because gas has no mnemonic for the opcode; the
     body-length check has to count `.word` or it rejects the body as empty.
  4. *An internal alternate entry needs no retail symbol.*  Three of these
     `j` into their own `func_<aug6+0x30>` label, which the block itself
     defines; splat only names function starts, so the reloc walk found no
     retail symbol and aborted.  `build_symbol_map` now takes `local_defs`
     — names the ported body defines itself — and binds those to the
     address-derived name without the `defined` check.

**2 held, neither a matching problem:**

| func | why |
|---|---|
| `func_00254C98` (24 insns) | the one V2 member that is genuinely **not portable**.  Its aug6 twin bakes the clamp mask's address into the raw `.word` stream (`.word 0x254A1070`), so no reloc walk can rebind it; and rewriting those two words — either as retail `.word`s or as symbolic `%hi/%lo(D_00254CE0)`, both tried — makes the **period assembler insert 10 nops into `func_00254328`, a *different* function 0x1600 earlier in the same TU**, shifting the link (`ninja` caught it; the effect is reproducible and independent of which of the two spellings is used).  The only spelling that assembles clean is splat's own `.s` verbatim, `.align 3` interleaves and all — which is what `INCLUDE_ASM` already does, so transcribing it would be accounting theatre, not a match.  **Left `INCLUDE_ASM`.**  Worth revisiting only with an explanation for the nop insertion. |
| `func_0026E5C8` (12 insns) | never became a candidate: its aug6 twin `func_0026A958` is a **K&R-style C definition** (`int func_0026A958(a0, a1)`), which `extract_functions_from_file` does not index either.  A *different* indexing gap from the one fixed here — asm blocks are not involved.  Teaching the C extractor K&R form would recover this one and any other K&R twin. |

Note the correction to this section's own premise: it said all 52 were bare
`__asm__` blocks.  51 are; `func_0026E5C8`'s twin is K&R C.

| func (retail) | insns | aug6 twin | what aug6's comment says it is |
|---|--:|---|---|
| `func_0024BFA4` | 2 | `func_002484A4` | (no comment upstream — read the `.s`) |
| `func_0024B3E8` | 4 | `func_00247908` | (no comment upstream — read the `.s`) |
| `func_0024B448` | 4 | `func_00247968` | (no comment upstream — read the `.s`) |
| `func_0024B458` | 4 | `func_00247978` | (no comment upstream — read the `.s`) |
| `func_0024B468` | 4 | `func_00247988` | (no comment upstream — read the `.s`) |
| `func_0024B478` | 4 | `func_00247998` | (no comment upstream — read the `.s`) |
| `func_0024B488` | 4 | `func_002479A8` | (no comment upstream — read the `.s`) |
| `func_0024B498` | 4 | `func_002479B8` | (no comment upstream — read the `.s`) |
| `func_0024B4A8` | 4 | `func_002479C8` | (no comment upstream — read the `.s`) |
| `func_0024B4B8` | 4 | `func_002479D8` | (no comment upstream — read the `.s`) |
| `func_0024BFAC` | 9 | `func_002484AC` | handwritten ISR thunk (ei/sync, asymmetric hand-frame). C-inexpressible: an honest 33-hypothesis stall floored |
| `func_0026E5C8` | 12 | `func_0026A958` | (no comment upstream — read the `.s`) |
| `func_0024B4C8` | 14 | `func_002479E8` | (no comment upstream — read the `.s`) |
| `func_0024B0E8` | 18 | `func_00247608` | handwritten TLB-write routine (mfc0/mtc0/tlbwi/sync.p). C-inexpressible: privileged COP0 TLB ops have no ee-gc |
| `func_0024B130` | 20 | `func_00247650` | handwritten TLB-read routine (mtc0/tlbr/mfc0/sync.p). C-inexpressible privileged COP0 ops; in-file handwritten |
| `func_0024B180` | 20 | `func_002476A0` | handwritten TLB-probe routine (mtc0/tlbp/tlbr/mfc0/sync.p). C-inexpressible privileged COP0 ops; in-file handw |
| `func_00254C98` | 24 | `func_00251028` | handwritten MMI byte-clamp/pack loop (pminh/pmaxh/ppacb) with an inline 0x00FF00FF clamp mask (D_00251070) loa |
| `func_00241C48` | 26 | `func_0023E168` | handwritten VIF/VU0 init — MMIO register pokes, a cfc2/ctc2 read-modify-write of VU0 control reg $vi28, sync b |
| `func_002439F8` | 28 | `func_0023FF18` | handwritten VU0/MMI matrix transpose + transform — packs three qwords via pextlw/pextuw/pcpyld/pcpyud into VU |
| `func_00243C00` | 30 | `func_00240120` | handwritten VU0 macro-mode math kernel — polynomial evaluation with a vsqrt (emitted raw as .word, no gas mnem |
| `func_00253F28` | 30 | `func_002502B8` | handwritten MMI unaligned-copy/unpack loop — qfsrv funnel shift (shift amount from mtsab) then pextlb/pextub b |
| `func_0026F3A0` | 32 | `func_0026B730` | handwritten critical-section wrapper — reads CP0 Status ($12), and if interrupts are enabled (bit 16) brackets |
| `func_0026F4E0` | 32 | `func_0026B870` | handwritten critical-section wrapper — reads CP0 Status ($12), and if interrupts are enabled (bit 16) brackets |
| `func_00244508` | 36 | `func_00240A28` | handwritten VU0 transform + clip-test loop — matrix-multiply each vertex, perspective-multiply two extents, an |
| `func_0024AF90` | 38 | `func_002474B0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00253FA0` | 38 | `func_00250330` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00243C78` | 42 | `func_00240198` | handwritten VU0 axis-rotation builder. Adjusts the angle into a quadrant (PI/2 +/- a, sign in $7), evaluates s |
| `func_00243D20` | 42 | `func_00240240` | handwritten VU0 axis-rotation builder (sibling of func_00240198, different axis). Internal alternate entry fun |
| `func_00243DC8` | 42 | `func_002402E8` | handwritten VU0 axis-rotation builder (sibling of func_00240198, different axis). Internal alternate entry fun |
| `func_00254520` | 42 | `func_002508B0` | handwritten MMI averaging loop — qfsrv funnel shift + pextlb/pextub byte-unpack, paddh accumulate, then signed |
| `func_0026F2F8` | 42 | `func_0026B688` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_0026F438` | 42 | `func_0026B7C8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_0024BEF8` | 43 | `func_002483F8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_002455A8` | 44 | `func_00241AC8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_002541C0` | 44 | `func_00250550` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_002545C8` | 44 | `func_00250958` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254038` | 46 | `func_002503C8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254270` | 46 | `func_00250600` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_0024B028` | 48 | `func_00247548` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_002641D8` | 48 | `func_00260568` | hand-vectorized memset(dst, c, n) — for n >= 8 on a 16-aligned dst it replicates the fill byte to 64 bits (pcp |
| `func_002540F0` | 52 | `func_00250480` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254928` | 52 | `func_00250CB8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254848` | 56 | `func_00250BD8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254678` | 58 | `func_00250A08` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254760` | 58 | `func_00250AF0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254328` | 62 | `func_002506B8` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254420` | 64 | `func_002507B0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00254B20` | 70 | `func_00250EB0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_0024BDD0` | 74 | `func_002482D0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_002549F8` | 74 | `func_00250D88` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |
| `func_00264EF8` | 75 | `func_00261288` | hand-vectorized string-end finder — a 128-bit MMI zero-byte scan (lq/pcpyld/psubb/pnor/pand/pcpyud haszero) fo |
| `func_0024B1D0` | 76 | `func_002476F0` | handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten asm per maintainer exception (C-inexpressibl |

## V3 — 40 head functions (5,056 B, 1,264 insns)

The head run is `0x00100000-0x00101C80`, **crt0 + libkernl** per
`decomp/VENDOR.md` §1 — the one part of the tail-vs-head split that *is*
attributed.  Legal: **§3b proprietary, clean-room from the disassembly
only.**  `ps2sdk` may inform naming and API shape (that is exactly what
`include/syscall.h`'s `SYSCALL_WRAPPER` already does, `decomp/NOTES.md:390`)
but must never be used as a byte oracle.

`22f1b2b6` already took the cheap 140: the EE-syscall leaves, four
instructions each.  What is left is the non-stub remainder.  29 of the 40
are ≤ 20 insns.

### V3a — 11 non-stub functions — **ALL 11 LANDED 2026-07-29 (700 B)**

Four shapes, none of them hard: four `call a syscall leaf, then SYNC()`
wrappers; a 0x80..0xFF handle-init do-while; a three-step init whose last
call is a void tail call; a word copy returning 0; and four identical
EE-kernel critical-section wrappers (read COP0 Status, and if interrupts are
enabled bracket the real call with the kernel's disable/enable pair).

**The one mechanism worth carrying forward** — the four wrappers all sat at
rc2 with `mfc0 s0,c0_sr` expected and `mfc0 v1,c0_sr` built.  A
*value-returning* `MFC0_STATUS()` statement-expression makes the read a
separate pseudo from the variable it is masked into, so the mask lands in a
different register than the read.  The kernel masks Status **in place**
(`mfc0 $16,$12` / `and $16,$16,...`).  `include/r5900.h`'s `MFC0_STATUS(dst)`
therefore takes the destination as an **lvalue**, and all four went to rc0.
`COP0_STATUS_EIE`, `DI()` and `SYNC_P()` were added alongside it.

`SYSCALL_WRAPPER`'s `void (void)` signature cannot express the argument
these syscalls read from `$a0` or the result they return in `$v0`;
correctly-typed names are bound to the same symbols with the tree's
`__asm__` label idiom.

| func | addr | insns |
|---|---|--:|
| `func_00100BA8` | `0x00100BA8` | 8 |
| `func_00100BC8` | `0x00100BC8` | 8 |
| `func_00100BE8` | `0x00100BE8` | 8 |
| `func_00100C08` | `0x00100C08` | 8 |
| `func_001009E0` | `0x001009E0` | 10 |
| `func_00100C48` | `0x00100C48` | 14 |
| `func_001009A0` | `0x001009A0` | 16 |
| `func_00100A08` | `0x00100A08` | 26 |
| `func_00100A70` | `0x00100A70` | 26 |
| `func_00100AD8` | `0x00100AD8` | 26 |
| `func_00100B40` | `0x00100B40` | 26 |

### V3b — **carved 2026-07-29; 10 of 26 libkernl functions landed (408 B)**

The `0x00100C90-0x00101C80` span is now `src/cod/vendor_100C90` (26
functions, not the 25 this section used to say — `func_00100E40` was missing
from the table below).  The carve changed no bytes.

`0x00100000-0x00100110` (crt0 / `_start`) deliberately stays `asm`:
`_start` is the real ELF entry point (VENDOR.md §5) and splat merges it into
`func_00100000`, so carving it needs the entry-point question settled first.

**Landed:** seven deci2/kernel request wrappers (`func_00101AE8`,
`func_00101B40`, `func_00101B10`, `func_00101BD8`, `func_00101C08`,
`func_00101C30`, `func_00101C58`) — pack arguments into a **four-word** block
on the stack and call the kernel entry with a request code; the block is four
words however many are filled, which is why every one of these frames is
0x20.  Plus `func_00101A88` (critical-section exit), `func_001019A8` (a
kprintf-shaped varargs forwarder, `__builtin_next_arg` idiom) and
`func_001011B0` (LF -> CR LF).

`func_001011B0` is worth noting: spelling it **`void`** with the call as the
last statement of BOTH arms is what turns the two tails into `j`; as
`int { return f(); }` gcc emits a real `jal`.  That is the inverse of the
usual `int_return_shape` lever, so check which way round the ROM is.

**Landed in pass 3 (2026-07-29), 5 more (532 B), taking the span to 15/26:**

* `func_00101B68` / `func_00101BA0` — two more four-word request wrappers,
  third argument masked to 16 bits.
* `func_00100FB0` — the kernel event ring.  Needed BOTH the `-G 8`
  incomplete-array lever and the struct data model (see the two mechanism
  notes in the group summary above).
* `func_00100F18` / `func_00101030` — the same routine with a different
  fallback callee and event code.  They issue the thread-id syscall
  **inline** rather than calling a leaf, which `SYSCALL_WRAPPER` cannot
  express, so `include/syscall.h` gained `SYSCALL_INLINE(num, dst)`.  The
  destination is bound to `$v0` explicitly — the result arrives there by the
  kernel ABI and a plain `"=r"` output would let gcc pick a register the
  kernel never writes.  That is operand binding, not a scheduling pin.
  Note the fallback path returns the CALLEE's value (the ROM skips the
  `daddu v0,s0` there), so it must be spelled `return fallback();`.

**Left in this span, with mechanisms:**

| func | insns | state |
|---|--:|---|
| `func_001010C8` | 14 | rc2 — **the `#.set volatile` delay-slot class again** (see V1b): the ROM puts the `sb` to the DECI2 data port in the `jr` delay slot; the store is a genuine MMIO poke so `volatile` is correct, and with it the assembler will not move it.  Everything else matches. |
| `func_00101A40` | 18 | rc9 / 4 sites — critical-section *entry* (spin on `DI()` until Status shows interrupts off).  CFG polarity is solved (the loop must be the fall-through, the zero path the `else`).  Residual: ROM keeps the `was` result in `$4` and copies it to `$2` at each of two duplicated tails, where gcc coalesces it straight into `$2`; and ROM remats the 0x10000 mask inside the loop where gcc hoists it.  Splitting the entry read from the loop's confirm read into two locals swaps `$2`/`$3` wholesale rather than fixing it — a different axis is needed. |
| `func_00101AA0` | 18 | rc5 / 4 sites — the four-word request block with all four words used.  Purely a sched1 ordering: ROM interleaves the `%hi/%lo`+`or` address computation with the argument stores (`andi` at index 4, `sw a0,0(sp)` at 7), gcc front-loads both.  Neither storing `args[1]` before `args[0]` nor hoisting the address into a local improves it (both go to 5 sites). |
| `func_001011E8` | 36 | untouched — 64-bit float bit-twiddling (exponent extract against the 0x433 double bias, then a shift-and-round).  A §5.11 `long long` shape. |
| `func_00100C90` / `func_00100D68` / `func_00100E40` | 54 each | untouched — init routines with many unattributed globals. |
| `func_00101100` | 44 | untouched |
| `func_00101278` | 90 | untouched |
| `func_001013E0` | 370 | untouched — the printf engine. |

Original table of the whole V3b population follows.

| func | addr | insns | span |
|---|---|--:|---|
| `func_00100000` | `0x00100000` | 2 | crt0 |
| `func_001000B8` | `0x001000B8` | 2 | crt0 |
| `func_001000C0` | `0x001000C0` | 20 | crt0 |
| `_start` | `0x00100008` | 44 | crt0 |
| `func_00101A88` | `0x00101A88` | 6 | libkernl |
| `func_00101AE8` | `0x00101AE8` | 10 | libkernl |
| `func_00101B40` | `0x00101B40` | 10 | libkernl |
| `func_00101C08` | `0x00101C08` | 10 | libkernl |
| `func_00101C30` | `0x00101C30` | 10 | libkernl |
| `func_00101C58` | `0x00101C58` | 10 | libkernl |
| `func_00101B10` | `0x00101B10` | 12 | libkernl |
| `func_00101BD8` | `0x00101BD8` | 12 | libkernl |
| `func_001010C8` | `0x001010C8` | 14 | libkernl |
| `func_001011B0` | `0x001011B0` | 14 | libkernl |
| `func_001019A8` | `0x001019A8` | 14 | libkernl |
| `func_00101B68` | `0x00101B68` | 14 | libkernl |
| `func_00101BA0` | `0x00101BA0` | 14 | libkernl |
| `func_00101A40` | `0x00101A40` | 18 | libkernl |
| `func_00101AA0` | `0x00101AA0` | 18 | libkernl |
| `func_001019E0` | `0x001019E0` | 24 | libkernl |
| `func_00100FB0` | `0x00100FB0` | 32 | libkernl |
| `func_001011E8` | `0x001011E8` | 36 | libkernl |
| `func_00100F18` | `0x00100F18` | 38 | libkernl |
| `func_00101030` | `0x00101030` | 38 | libkernl |
| `func_00101100` | `0x00101100` | 44 | libkernl |
| `func_00100C90` | `0x00100C90` | 54 | libkernl |
| `func_00101278` | `0x00101278` | 90 | libkernl |
| `func_00100D68` | `0x00100D68` | 108 | libkernl |
| `func_001013E0` | `0x001013E0` | 370 | libkernl |

## V4 — 52 tail functions with no aug6 twin (27,112 B, 6,778 insns)

`.port_cache/name_alias.json` pairs 716 of the 765 tail functions with an
aug6 twin across three deltas (`+0x3C70` x474, `+0x3AE0` x208, `+0x3B00`
x34 — verified by recomputing the deltas from the alias map).  49 have no
twin; adding the three symbol-table orphans (which are in no map at all)
gives **52**.  Nothing to port: original work.

As landed by `bca0d69a`, `decomp/VENDOR.md` §1 said *"~46 functions with no
aug6 twin"* and §7/§8 said *"49"*.  The two disagreed with each other; the
alias map says 49, and the honest figure including the orphans is 52.  Both
places now read 52.

Legal: **unclassified**.  VENDOR.md §1's per-archive table is a research
aggregate and is explicitly *not tracked per function*, so no archive can be
attributed to any of these without new work.  Method is therefore
**clean-room from the disassembly unless the archive is identified first** —
if identification later puts one in libgcc/libm/libc it moves to §3a and
gets a reference implementation.  VENDOR.md §8 flags the likely cause
(retail linked a different library revision than the Aug-6-2001 prototype),
which if confirmed makes §3a attribution *more* likely for this group than
for V5, not less.

### V4 status — 18 landed 2026-07-29 (2,532 B), 34 left
### V4 status — 9 landed 2026-07-29 (820 B), 43 left

| func | insns | outcome |
|---|--:|---|
| `func_00268F28` | 7 | **LANDED** — forwards with an added zero argument |
| `func_00268F08` | 16 | **LANDED** — the kernel's terminal loop |
| `func_0024E670` / `func_0024E760` | 14 each | **LANDED** — index a small table and tail-call the setter, or fall back to a default byte.  Both needed the `-G 8` incomplete-array lever for the 1-byte default. |
| `func_00246B78` | 23 | **LANDED** — lazily creates the two semaphores guarding the slot table.  Needed the same-valued-store reversal. |
| `func_00246C60` | 28 | **LANDED** — hands out the i'th 16-byte slot.  Returns `void *`, per the declaration an already-matched sibling makes. |
| `func_0024CB28`, `func_0024D718`, `func_0024D7B0` | 38 each | **LANDED** — one template: gate on a per-device check, register a 9-argument request (8 in `$a0`-`$t3` plus one stack word), and on success read the slot's first word back through UNCACHED space (the peer writes it by DMA).  The uncached read sits in the unlock call's delay slot, so it is spelled before the unlock in C.  `func_0024D7B0` returns **-1** on both failure paths where the other two return 0. |
| `func_00260BA0` | 22 | left, rc2 / 2 sites — the init/exit chain walker.  gcc emits one extra `lw` of `*D` in the loop preheader.  Refuted: plain `while`, guarded `do`-`while`, guarding through a separate temp, and `p` as an explicit loop variable (the last regresses rc to 12 at the same 2 sites).  All four are the same axis — the loop's rotation — so the next attempt should change the DATA MODEL (the cursor is a `void (**)(void)` held in a global; the ROM reloads that global every iteration, which is a `volatile`-ish or aliasing property, not a loop-form one). |
| `func_0024D848` | 46 | **LANDED** — the template plus a verbosity-gated log line. |
| `func_0024D900` | 46 | **LANDED** — the template plus a busy flag raised across the request.  Needed TWO volatiles, both argued for by the ROM's own codegen: the flag (without it gcc annuls the flag store into a `bgezl` delay slot where the ROM has a plain `bgez`), and the semaphore **for this body only** (the ROM leaves this function's unlock-call delay slot EMPTY — same signature).  Typing the shared `D_0055092C` volatile fixes this body and REGRESSES the three siblings, so it is bound through a per-function `__asm__` alias.  The last two sites were a v0/v1 swap that no source ORDER change touched and that vanished when the intermediate locals were removed and the body written in exactly the siblings' shape — **fewer named temporaries, not different ones**. |
| `func_0024F4E0`, `func_0024F7C8`, `func_00250230`, `func_00250818` | 48-50 | **LANDED** — four more of the device-request family, straight off the template.  `func_0024F4E0` is the *query* variant (reads the reply word back out of the shared reply block instead of recording a tag); `func_0024F7C8` takes three arguments; the other two take two.  The per-member check held again: `func_0024F4E0` stores at **+4** and needs the request BLOCK cached, `func_0024F7C8` stores at **+0** and does not.  **Offset zero vs non-zero is the tell.** |
| `func_0024F428`, `func_0024F710`, `func_00250420` | 46-54 | **LANDED** — the device-request family: take the device lock, refuse if the device is not open, publish the argument into the shared request block and submit it.  On success the lock stays HELD (the completion path releases it) and the tag is recorded.  Four levers, in the order they mattered: (1) the device handle is a **cached pointer**, formed once into `$a0` and used both for the "is it open" field read and as the call's first argument — spelling it `*(int *)(D_X + 0x24)` plus a separate `func(D_X, …)` costs 6 sites in addressing alone; (2) the unlock path must be OUT OF LINE (`goto`) or gcc inverts the branch; (3) both paths must reach a **shared tail** or gcc const-folds the success path's `return r` to `return 0`, where the ROM returns the register; (4) `func_0024F428` needs the request BLOCK cached too (it stores at +0x14 and passes the same pointer) while the other two store at +0 and match with the plain form — same family, opposite answer, and the ROM says which each time. |
| `func_0024D848`, `func_0024D900` | 46 each | same family as the three above, plus extra work (an init call, a second table).  Should fall to the same template. |

Original smallest-first list:

`func_00268F28`(7)*, `func_0024E670`(14), `func_0024E760`(14), `func_00268F08`(16),
`func_00260BA0`(22), `func_00246B78`(23)*, `func_00246C60`(28), `func_0024CB28`(38),
`func_0024D718`(38), `func_0024D7B0`(38), `func_00246B38`(40), `func_0024D848`(46),
`func_0024D900`(46), `func_0024F428`(46), `func_0024F710`(46), `func_00250420`(46),
`func_0024F4E0`(48), `func_00250230`(50), `func_00250818`(50), `func_0024F7C8`(54),
`func_00256C30`(56), `func_0024A9C0`(66), `func_002508E0`(70), `func_0024F930`(72),
`func_002502F8`(74), `func_0024F5A0`(78), `func_00257DE0`(82), `func_00245938`(84),
`func_002500E0`(84), `func_0024D5C0`(86), `func_0024FF00`(86), `func_002506B0`(90),
`func_0024FA50`(96), `func_0024C130`(102), `func_00244748`(118), `func_002504D8`(118),
`func_00255410`(128), `func_0024A510`(130), `func_0024A758`(138), `func_00247788`(142),
`func_002498D8`(142), `func_002658B8`(142)*, `func_00241CB0`(156), `func_0024B8D8`(160),
`func_00265818`(182), `func_00252F90`(206), `func_00252838`(210), `func_00247EF0`(212),
`func_0024B500`(224), `func_002532C8`(428), `func_00265CA0`(756), `func_002669E8`(1350).

## V5 — 261 tail functions whose aug6 twin was never matched upstream (118,972 B, 29,743 insns)

The aug6 twin is `INCLUDE_ASM` in `common/src/PObj.c` at `3a5ab90e`, so
there is nothing to port.  This is **74 % of the remaining vendor bytes**
and the slowest class in the queue.  The port report's "~310" for this
group conflated it with V2; the two are 261 + 52 = 313.

Legal: **mixed, mostly unclassified -> §3b clean-room**.  Per-function
archive attribution does not exist in this repo and must not be invented.
The one exception with in-tree evidence is V5a.

### V5a — 13 functions inside the fdlibm evidence window (§3a, libm)

`src/cod/vendor_25E1E8.c` is the only vendor TU whose matched bodies use the
fdlibm idiom (`GET_FLOAT_WORD` / `SET_FLOAT_WORD` from
`include/math_private.h`, lines 52-311), and aug6's `common/src/PObj.c` at
`3a5ab90e` line 7947 names one of the neighbours *"fdlibm
`__kernel_cosf(x, y)`"*.  The matched fdlibm
bodies span `0x0025E2E8`-`0x00260B70`; two of the unmatched functions below
are already `extern`-declared *by* those bodies
(`func_0025F548` at `vendor_25E1E8.c:43`, `func_00260508` at line 45), which
is direct in-tree evidence that they are part of the same fdlibm cluster.

This is the one group that can be **compiled-and-diffed against a
legitimate upstream** (Sun fdlibm via newlib, public domain — VENDOR.md §3a,
`decomp/COOKBOOK.md` §7.3, `decomp/NOTES.md:403`) rather than re-derived
blind.  It is gated on **V0** below.

Treat the window as *evidence, not attribution*: a non-libm function can sit
inside it.  Confirm per function before claiming §3a method for it.

| func | addr | insns |
|---|---|--:|
| `func_00260900` | `0x00260900` | 58 |
| `func_0025E3D8` | `0x0025E3D8` | 64 |
| `func_0025E4D8` | `0x0025E4D8` | 64 |
| `func_00260508` | `0x00260508` | 66 |
| `func_0025E5D8` | `0x0025E5D8` | 74 |
| `func_00260A10` | `0x00260A10` | 88 |
| `func_0025F2F8` | `0x0025F2F8` | 148 |
| `func_00260638` | `0x00260638` | 170 |
| `func_0025F010` | `0x0025F010` | 186 |
| `func_0025EC70` | `0x0025EC70` | 232 |
| `func_0025F548` | `0x0025F548` | 248 |
| `func_0025E840` | `0x0025E840` | 268 |
| `func_0025FBB8` | `0x0025FBB8` | 596 |

### V5b — the other 248

All 261 smallest-first — the 13 V5a members are left in place so this is one
complete list, but work those under V5a's §3a method, not V5b's:

`func_00261BA8`(24), `func_00265780`(28), `func_0026D188`(28), `func_002454F0`(30),
`func_00265C28`(30), `func_00266970`(30), `func_00245318`(32), `func_00245470`(32),
`func_002509F8`(34), `func_00255C08`(34), `func_00264E70`(34), `func_0024F8A0`(36),
`func_0025AE00`(36), `func_0025C4E0`(36), `func_0025C6D8`(36), `func_0025C768`(36),
`func_0025DD20`(36), `func_00263520`(36), `func_00263E20`(36), `func_00264094`(37),
`func_002425A8`(38), `func_00246688`(38), `func_002467F0`(38), `func_0024C368`(38),
`func_00258470`(38), `func_002591F0`(38), `func_002614A8`(38), `func_00263218`(38),
`func_00263EB0`(38), `func_0026B018`(38), `func_0026CA48`(38), `func_00248B60`(40),
`func_0024C090`(40), `func_0024C2C8`(40), `func_0024CBC0`(40), `func_0024E108`(40),
`func_002517D0`(40), `func_00252E90`(40), `func_00262848`(40), `func_002632B0`(40),
`func_00245270`(42), `func_00245DE0`(42), `func_00255F80`(42), `func_0025CFC0`(42),
`func_0026BEF0`(42), `func_002461D8`(44), `func_00256028`(44), `func_00256918`(44),
`func_00256DF8`(44), `func_00256F98`(44), `func_0025D438`(44), `func_00260BF8`(44),
`func_00264128`(44), `func_00245F18`(46), `func_0024E410`(46), `func_0024EBC8`(46),
`func_0024ED58`(46), `func_00257128`(46), `func_00263160`(46), `func_00263D68`(46),
`func_00265B70`(46), `func_002668B8`(46), `func_0026D378`(46), `func_00245B58`(48),
`func_0025B998`(48), `func_0026CDE0`(48), `func_0026EB50`(48), `func_00241A20`(50),
`func_002436E8`(50), `func_00244C28`(50), `func_00244ED0`(50), `func_0024D318`(50),
`func_00252488`(50), `func_00244F98`(52), `func_00245A88`(52), `func_00246720`(52),
`func_00255610`(52), `func_00256848`(52), `func_0025AE90`(52), `func_00244980`(54),
`func_002525E8`(54), `func_00244658`(56), `func_0024AC00`(56), `func_00257048`(56),
`func_0025D4E8`(56), `func_002680B0`(56), `func_0026A500`(56), `func_0026BCFC`(56),
`func_002421C8`(58), `func_00244A58`(58), `func_00244B40`(58), `func_00252B80`(58),
`func_00256D10`(58), `func_00260900`(58), `func_00244CF0`(60), `func_00244DE0`(60),
`func_0024A258`(60), `func_00256EA8`(60), `func_002613B8`(60), `func_0026D288`(60),
`func_0026E878`(60), `func_00250F90`(62), `func_0025C868`(62), `func_0025CD78`(64),
`func_0025E3D8`(64), `func_0025E4D8`(64), `func_0026C5D8`(64), `func_0026BDDC`(65),
`func_002437B0`(66), `func_002440C0`(66), `func_0025AA88`(66), `func_00260508`(66),
`func_00268C98`(66), `func_0026A330`(66), `func_00241B28`(68), `func_00242958`(68),
`func_0024AE80`(68), `func_0025BF98`(68), `func_00263410`(68), `func_00268DF8`(68),
`func_00265168`(69), `func_002563C8`(70), `func_00257A20`(70), `func_0025B880`(70),
`func_0026BFC8`(70), `func_00248A20`(72), `func_0024E798`(72), `func_0024E8B8`(72),
`func_00252058`(74), `func_002551C0`(74), `func_0025E5D8`(74), `func_0024ACE0`(76),
`func_00262718`(76), `func_0024BC18`(78), `func_00256290`(78), `func_0025BE60`(78),
`func_0026527C`(79), `func_00242CB0`(80), `func_00265024`(81), `func_002587E0`(84),
`func_0026B1A0`(84), `func_002526E0`(86), `func_0025B080`(88), `func_00260A10`(88),
`func_0024DD30`(90), `func_00252D28`(90), `func_002564E0`(90), `func_0024C9B8`(92),
`func_0024CCD0`(92), `func_002521C0`(92), `func_0025B1E0`(94), `func_0026C6D8`(94),
`func_0026CF30`(94), `func_00242DF0`(96), `func_00247608`(96), `func_00255C90`(96),
`func_0026CAE0`(96), `func_0026CC60`(96), `func_0024C530`(98), `func_0024DAB8`(98),
`func_0024FD78`(98), `func_00251ED0`(98), `func_00254F28`(98), `func_0026E968`(98),
`func_002441C8`(100), `func_00253D98`(100), `func_0026C8B8`(100), `func_002457A0`(102),
`func_002494B0`(102), `func_00257888`(102), `func_0025C2F8`(102), `func_00245C18`(104),
`func_00247118`(104), `func_00248EC0`(104), `func_0025A430`(104), `func_0025AC60`(104),
`func_00248418`(106), `func_002485E0`(108), `func_00267F00`(108), `func_0024F240`(110),
`func_002560D8`(110), `func_0025B4A8`(110), `func_002653B8`(110), `func_00257B38`(112),
`func_00257F28`(112), `func_0025C100`(112), `func_00265570`(112), `func_00246970`(114),
`func_00249F20`(114), `func_00248240`(118), `func_0025DAD8`(118), `func_00249D40`(120),
`func_0024D3E0`(120), `func_0025A250`(120), `func_00241FE0`(122), `func_00242AC8`(122),
`func_0024E228`(122), `func_00254D20`(122), `func_00246458`(124), `func_002492A0`(124),
`func_00257660`(124), `func_0024D120`(126), `func_002638A8`(126), `func_00250A80`(128),
`func_00268F48`(134), `func_0025B660`(136), `func_0026E620`(136), `func_0025D5C8`(138),
`func_00249B10`(140), `func_002569C8`(140), `func_0026C3A8`(140), `func_00258A00`(142),
`func_0025A708`(142), `func_002635B0`(142), `func_00249060`(144), `func_00251870`(144),
`func_002628E8`(144), `func_0025F2F8`(148), `func_002581C0`(150), `func_0026B2F0`(150),
`func_002479C0`(156), `func_002487B0`(156), `func_00249648`(156), `func_0025D068`(156),
`func_00247380`(162), `func_002422B0`(166), `func_00260638`(170), `func_00262BE8`(170),
`func_00247C30`(176), `func_0024CE40`(184), `func_0025F010`(186), `func_00250C80`(188),
`func_0024C6B8`(192), `func_00242640`(198), `func_0026A7B0`(200), `func_0025BA58`(224),
`func_0025EC70`(232), `func_00246CD0`(238), `func_0026AC40`(246), `func_002571E0`(248),
`func_0025F548`(248), `func_00253978`(264), `func_00259288`(264), `func_0025E840`(268),
`func_002596A8`(296), `func_00258D10`(312), `func_002556E0`(330), `func_002621D8`(336),
`func_0026ED88`(348), `func_00251248`(354), `func_00261C08`(372), `func_00261540`(410),
`func_00242F70`(420), `func_00260CC8`(444), `func_00259B48`(450), `func_0026B548`(478),
`func_0025FBB8`(596), `func_00264328`(650), `func_00268190`(706), `func_0026D6C8`(960),
`func_00269160`(1140).

## V6 — `func_0026F578`: blocked, not queued

104 B / 23 insns at `0x0026F578`.  `decomp/port_ledger.md:27` records it as
`PRE-MATCHED` — a retail body existed before Phase 4 — so it is *portable*,
and it is nonetheless **`asm`** in `config/ico.us.yaml:355`
(`[0x16F578, asm, src/cod/16F578]`).

Reason (VENDOR.md §7): splat puts the **12 bytes of inter-section `.text`
pad** between `.text` and `.vutext` *inside* that trailing object, and no C
TU can emit them.  Carving it `c` to match the function would drop the pad
and break the SHA-1.  **Do not queue this as workable.**  Unblocking it is a
splat/linker-script problem, not a matching problem, and nobody should spend
a matching iteration on it until that is solved.

## Method by legal category — the part that decides how you work

Restating `decomp/VENDOR.md` §3 in queue terms, because the category
determines the *method*, and getting it wrong is the one mistake in this
area that cannot be undone:

* **§3a — `libgcc` / `libm` / `libc`, ~61 KB.** Upstream is public and
  legitimately obtainable (GCC runtime under the GPL runtime exception; Sun
  fdlibm, public domain; newlib, BSD-style).  Method: fetch a candidate
  upstream release, compile with `ee-gcc 2.9-991111-01`
  (`tools/compile_c.sh:19`), diff against the ROM asm, adjust.  **Not a
  licence to paste** — the committed C is still ours, and anything vendored
  wholesale goes under `lib/<name>/` with a `PROVENANCE.md`.
  In this queue only **V5a** (13 funcs) is confidently §3a today.
* **§3b — the SCE SDK archives + crt0, ~99 KB.** `libkernl`, `libgraph`,
  `libmpeg`, `libsndn2`, `libcdvd`, `libpad`, `libmc`, `libipu`, `libvu0`,
  `libdma`, `libpkt`, `libscedemo`, `crt0`.  **No SDK source, ever.**
  Clean-room from the disassembly only.  `ps2sdk` is permitted as a naming
  and structural reference and is **never** a byte oracle.  **V3** is
  confidently here (crt0 + libkernl, VENDOR.md §1).  **V2** is here too, but
  the clean-room derivation is already done on aug6.
* **Unclassified — V1, V4, and V5b.** VENDOR.md §1's per-archive table is a
  *research aggregate*: it was produced by reloc-normalized instruction
  hashing against the aug6 twin and then mapped onto `MAIN.MAP`'s member
  list, and the file states plainly that *"this mapping is not tracked
  per-function anywhere in the repo"*.  **Do not invent per-function archive
  attribution.**  Method for these groups is **clean-room from the
  disassembly unless the archive is identified first**; if identification
  later places one in libgcc/libm/libc it is promoted to §3a and gets a
  reference implementation.

One further caution on that aggregate: `MAIN.MAP` is a **different link**
(different addresses and sizes from ours), so it may inform archive
*membership* but must never be used to verify an address, a size, or a byte.

## V0 — the §3a prerequisite (research item, highest leverage in the queue)

**Which exact newlib / libgcc / fdlibm release did SCE ship?**  Unidentified,
and it gates the whole §3a method for ~61 KB.

It cannot be read out of the binary.  `decomp/NOTES.md:913`
(§ "Build-environment fingerprint") records that **no `.comment`, `.note`,
`.mdebug`, `.pdr` or `.gptab.*` section survives** in `baseelf.elf` — the
link was stripped of every build-provenance section.  So identification has
to come from **codegen fingerprinting**: compile candidate newlib / libgcc
releases with `ee-gcc 2.9-991111-01` at the project's flags and score the
resulting instruction streams against the ROM's.  V5a (13 fdlibm-window
functions, ~5.9 KB) is the natural scoring corpus because it is the one span
with independent in-tree evidence of its provenance.

Deliverables: (1) the identified release(s), recorded in VENDOR.md §8;
(2) whether libgcc and libc came from the same distribution; (3) a
`lib/<name>/PROVENANCE.md` if anything is vendored.  Until this lands, every
§3a function must be worked as if it were §3b, which is the slow path.

## Cross-references

* `decomp/VENDOR.md` — the policy: §1 what vendor is and the per-archive
  aggregate, §3 the legal split, §5 `_start` and `vobj.o`, §7 port status,
  §8 open questions.
* `decomp/port_ledger.md` — every `PORTED` / `REVERTED` / `PRE-MATCHED`
  decision, with the first divergent instruction for each revert.  The eight
  `### src/cod/vendor_*` sections are the vendor part.
* `config/ico.us.yaml:111,118-119,347-355` — the vendor subsegments.
* `config/symbol_addrs.us.txt:5,247-428,6051` — the surviving `// (vendor)`
  notes (the carved functions now carry TU notes instead).

**Operational warning, unrelated to vendor but found here.**
`decomp/port_ledger.md` is **261,861 B** and `tools/check_no_rom.sh` fails
any tracked file over **256 KiB (262,144 B)**.  There are roughly **280
bytes** of headroom left.  The next Phase-4 wave that appends to it will trip
the IP-safety gate — and the failure message ("tracked file >256KiB
(suspicious)") gives no hint that the cause is benign growth.  Split the
ledger per phase or per programmer, or raise the threshold for `decomp/*.md`
in `tools/check_no_rom.sh`, *before* the next port pass.  (The
cross-reference added to it in this pass was deliberately compressed to fit.)


# conv-10 / branch `acttails-1` — enemy_act, girl_act, objact and the st* scripts

Worker scope: `src/enemy_act.c`, `src/girl_act.c`, `src/objact.c`,
`src/st17b.c`, `src/st47a.c`.  Metric is **divergent sites first**, raw
`real_count` second (an rc drop with sites flat is not progress).

## Landed — 30 functions, all gated on `ninja` + explicit `tools/verify_elf.py`

| commit | TU | funcs | mechanism |
|---|---|---|---|
| `aef4acd3` | st17b | `func_0022EE98` | alias set of the four stores; ported from the byte-identical matched twin `func_0020A468` (src/e3) |
| `21d2eddd` | st47a | `func_00238BC0` | same template; pointer-typed `__asm__` alias of the in-TU `unsigned int` table restores the alias set |
| `21735d55` | objact | `func_0023B650` | the callee's real signature takes 0.0f TWICE — two uses make it a loop.c movable into `$f20` |
| `c5f2634b` | girl_act | `func_001754F8` | gcse-PRE rotation: increment FIRST kills antloc for the compare; counter origin 0 aligns the rotated constants |
| `e611a862` | st17b | `func_0022EE68`, `func_0022F7B8` | `actE3CageFallChk` idle-tail template |
| `aaee5306` | st47a | `func_00237860`, `func_00237A00`, `func_00238B88` | same template, flag-clearing variant |
| `b40d0387` | objact | `func_0023B4F0`, `func_0023C148` | actCreateSubThread stub; short-circuit `\|\|` cross-jump |
| `5236aa52` | enemy_act | `func_00164EF8`, `func_00164F40`, `func_00164F88`, `func_00164FD0`, `func_00165178`, `func_00165348`, `func_00165DC0`, `func_00165E08` | `_ApproachTarget_Way` assert stub ×3; the 0xAF3 pair; the `func_001650A0` 16-byte spill idiom; MoveChest guard returning `r`; the ExecMotionOrient pair (it returns a POINTER) |
| `ea8bf6b7` | st47a | `func_00238C18`, `func_00239710` | idle tail with lt_fade_status/scpActivateAllWithKind; actInitialize stub |
| `c93e7c69` | objact | `func_0023C180` | the -1/0 predicate must be a named intermediate that is then tested, else it folds to one cmove |
| `1f9b5ff1` | st47a | `func_002376F0`, `func_0023A3B8`, `func_0023A418`, `func_0023A478`, `func_0023A4D8`, `func_0023A548`, `func_0023A700`, `func_0023A768` | func_0017BF78 trio (EABI 5th int arg in `$8`, args 4/5 repeat args 1/2); actSt47aSekizo1 BoxBar-init quartet; branch-polarity fix |

## Three reusable findings

1. **The BoxBar no-call wrapper is an ALIAS-SET template, not a store-order
   puzzle.**  ee-gcc 2.9 gives every pointer type one alias set, distinct from
   `int`.  The dev's GObj members at 0xC0/0xC4 are BOTH pointers and the
   callback table is a pointer array; spelling any of them through an `int`
   lvalue couples that store to the `int` global and re-times the whole entry
   block.  Where a TU defines its table as `unsigned int D_X[8]`, an
   `extern <ptr> D_X__tag[] __asm__("D_X")` alias fixes it without touching the
   data definition.  This should be checked FIRST on every remaining
   `actStXX` wrapper.

2. **gcse PRE / lazy code motion is the cause of several "loop rotation" and
   "callee-saved &buf" residuals, and the `.gcse` dump names it outright**
   (`PRE/HOIST: edge (p,s), copying expression N` plus the numbered expression
   table).  An expression is hoistable only if it is *locally anticipatable* —
   computed in the block before any of its operands is redefined there.  The
   lever is therefore ORDERING inside the block: put the statement that
   redefines the operand FIRST and the dependent expression stops being a PRE
   candidate.  When PRE then rotates the surviving expression by one
   iteration, the fix is not to fight the rotation but to shift the
   variable's ORIGIN so the rotated constants land on ROM's.

3. **`bltzl/negu` vs `movn` for abs is a spelling the dev made with a
   ternary.**  gcc 2.95 `jump_optimize` converts `if (cond) x = b;` to a
   conditional move when the then-block is exactly one `(set reg ...)` insn;
   a `?:` goes through COND_EXPR expansion instead and keeps the branch.
   `if`-statement and ternary are NOT interchangeable here.

## Recommended next steps in this scope

1. `func_001619A8` (sites 7) — one class left, see its row above; the near-miss
   source is reproduced below.  Cracking it also unblocks commonact
   `func_0015DF88`, whose (a) residual is the same class.
2. The rest of the st47a / st17b / objact `INCLUDE_ASM` set, smallest-first —
   most of it is more of the same three templates and should go in bulk.
3. `girl_act` still has the large act-thread tails up to `func_001725C8` (678).

## `func_001619A8` near-miss source (sites 7 / rc 9, crutch-free)

```c
extern int ContinueCorrectPosition__19a8(int a0) __asm__("ContinueCorrectPosition");
extern void dispPlane__19a8(void *a0, float *a1) __asm__("dispPlane");
extern void func_001947D0__19a8(float *a0, int a1, int a2) __asm__("func_001947D0");
extern int D_00631AE8__19a8 __asm__("D_00631AE8");
extern int func_00145328(void *a0, int a1, int a2, void *a3, float f12, float f13);
extern void *subCommonIdle__19a8(int a0) __asm__("subCommonIdle");
extern int HandCameraCorrect__19a8(void *a0, void *a1) __asm__("HandCameraCorrect");
extern void ACTGameView_Loop(void);
extern int MoveChestForCatchBoy(void *a0);
extern void BoxBarSoundOn__19a8(void *a0, int a1) __asm__("BoxBarSoundOn");
extern unsigned int _ACTWait__19a8(int a0) __asm__("_ACTWait");

void func_001619A8(volatile unsigned int a0) {
    float buf0[4];
    float buf[4];
    int thresh = 0x59;
    char *m = (char *)(*(int *)(a0 + 0x164)) + 0x110;
    int r0 = ContinueCorrectPosition__19a8(D_00631AE8__19a8);
    int r1 = ContinueCorrectPosition__19a8(a0);
    func_001947D0__19a8((float *)m, r0, r1);
    dispPlane__19a8((void *)a0, (float *)m);
    for (;;) {
        int mode;
        if (func_00145328((void *)a0, D_00631AE8__19a8, 0x2D, buf, 170.0f, 100.0f) != 0) {
            int d = HandCameraCorrect__19a8(buf, subCommonIdle__19a8(D_00631AE8__19a8));
            d = (d < 0) ? -d : d;
            mode = (d <= thresh) ? 1 : 2;
        } else {
            mode = 0;
        }
        if (mode < 3 && mode != 0 && MoveChestForCatchBoy((void *)a0) != 0) {
            ACTGameView_Loop();
            for (;;) {
                BoxBarSoundOn__19a8((void *)a0, 0x151);
                _ACTWait__19a8(1);
            }
        }
        BoxBarSoundOn__19a8((void *)a0, 0x152);
        _ACTWait__19a8(1);
    }
}
```


# conv-11 / branch `acttails-2` — continuation of the same scope

Landed on top of `2d50924f`.  Metric is sites; every match gated on
`.venv/bin/ninja` + explicit `tools/verify_elf.py`.

| commit | TU | funcs | mechanism |
|---|---|---|---|
| `b0fd6d23` | st17b | `func_0022ED40` | actSt25aQueenTalkChk + the `long long buf[2]` param copy (st13b idiom) |
| `21de20c7` | objact | `func_0023C290` | the `daddu a0,v0` in the DispWireLetter delay is `UpdateRootPosition`'s RETURN, not the stale global — reading it as the global costs two callee-saved regs and doubles the frame |
| `2ba57cdc` | enemy_act | `func_001619A8` | **callee-saved-`&buf` class closed** — `static __inline__` helper owns the buffer; see the row above |
| `8b65d670` | st47a | `func_002377E8`, `func_00238740`, `func_00238950`, `func_0023A7E0`, `func_00238DD8` | guarded Sekizo BoxBar template ×4; the `||`-of-two-`== 0` spider wait |
| `eb5cfd1a` | st17b | `func_0022EF00`, `func_0022F698` | two-group spider wait; guarded Sekizo tail with a matching `int *unkC4` struct |
| `3e1e4c4c` | st47a | `func_00236D90`, `func_002388D0` | spider wait with the guard test inside the loop; two-arm `func_0017B230(0x11A)` dispatch |
| `7a55de31` | objact | `func_0023B518` | four-phase stage_KillPlayBgAnimation cycle |
| `a3458bbf` | st47a | `func_0023A858`, `func_00239680` | Generator mask/call sequence; warpGirlInStage + guarded Sekizo tail (§8.22 delay slot — see below) |
| `015a7499` | objact | `func_0023B5C8` | sibling four-phase cycle |

## The callee-saved-`&buf` class — closed, general recipe

Symptom: ROM recomputes `addiu $r,$29,OFF` at every use of a local array's
address inside a loop; gcc parks it in a callee-saved register and emits
`daddu` copies.

Recipe: **give the array to a `static __inline__` helper that contains all of
its uses.**  Then check two follow-ons that the move exposes — any global the
helper needs must be re-read inside the helper (a parameter turns it into a
loop invariant that gets hoisted), and constants that had to be held in locals
to survive the old shape usually want to go back to literals.

Both members are now matched: commonact `func_0015DF88` (other worker) and
enemy_act `func_001619A8`.

## §8.22 delay slot — `volatile` on the read, not on the callee

`func_00239680` calls `warpGirlInStage(x, y, z)` with three gp-relative float
globals.  gcc emits two `lwc1`s and puts the THIRD in the call's delay slot;
ROM emits all three ahead of the `jal` and leaves a `nop`.  Marking the three
globals `extern volatile float` fixes it: reorg will not hoist a volatile MEM
into a delay slot.  This is a ROM-proven `volatile` (the ROM codegen is the
evidence), not a scheduling crutch.  Only the last one being volatile is not
enough (sites 2); all three must be.

## Still open in this scope

`func_0015E388` and the other commonact rows are not this worker's TUs.  In
enemy_act / girl_act / objact / st17b / st47a what remains is the untouched
tail set, smallest-first from girl_act `funcGirlHandDisconnect`(34), objact
`func_0023C2F0`(35), st47a `func_0023A8E8`(36) / `func_00237750`(37), st17b
`func_0022F600`(38), up to girl_act `func_001725C8`(678).  girl_act (47
stubs) and enemy_act (41) are now the bulk and have had the least sweeping;
st47a is down to 43 and objact to 8.
The st47a remainder is still mostly the same three templates
(Sekizo BoxBar tail, actE3CageFallChk idle tail, spider wait) and should keep
going in bulk.
# conv-10 / conv-11 — commonact (worker: rwt2)

Metric is **diff sites** (`tools/match_diff.py <tu> <func>` → `diff_sites`), not
`real_count`; every row below is sites-first.  `real_count` is quoted only where
it is needed to compare two shapes at equal sites.

## Matched in conv-10 (14 functions, all crutch-free, ninja + verify_elf gated)

| func | sites before → after | mechanism |
|---|---|---|
| `func_0015E1B0` | 3 → 0 | The second argument of `ChangeMailInLadder` must be spelled `(void *)a0` **at the call site**, not routed through a `void *self` local. The local gives the volatile home read its own pseudo plus an arg-register copy, so its sched1 priority is *load-latency + copy* (3+P) instead of *load-latency* (2+P); that one notch put the read ahead of the `%hi/%lo` chain, and the resulting LUID order then decided both sched2 ties — `rank_for_schedule` falls through priority → reg-weight (unused after reload) → class → depend-count → `INSN_LUID`. |
| `func_0015E388` | 2 → 0 | Two semantic points. (a) The three `0x15C` stores cannot be three self-contained statements: a non-volatile store followed by a fresh volatile reload of the `a0` home is a read-after-write on alias set 0, so each reload is pinned behind the previous store (strict reload/load/store triples). Three `int` temps assigned from the volatile param *before* the stores give ROM's three up-front reloads. (b) With retail's strict aliasing live, `*(char **)(b+0x15C)` is in `char*`'s alias set while `*(int *)(p+0x130)=0` is in `int`'s, so the later pointer loads did **not** conflict with the earlier stores and sched1 hoisted all three loads ahead of all three stores; spelling the pointer load `*(int *)(b+0x15C)` puts both in one alias set and the interleave matches ROM. |
| `func_0015DF88` | 14 → 0 | **Cracks the callee-saved-`&buf` class** — see the section below. |
| `func_001588F0`, `func_00157BB0` | 5/7 → 0 | Frameless N-way void tail-call dispatch. As `if/else` with a call+`return` per arm gcc inlines the first body, keeps a frame and emits `jal`; as a goto-CFG (`if (m == K) goto h;`, handlers out of line, last one falling off the end) it emits ROM's `j <callee>` sibcalls with the arg shuffle in the delay slot and no frame. `func_00157BB0`'s third test must be written in ROM's polarity (`if (m >= 0x1A) return;`) to keep `bnez`. |
| `func_0015F248` | 2 → 0 | A flat `if (f(p) == 7) return 1; return 0;` if-converts to `xori`/`sltiu`. Nesting the tests so there is exactly one fall-out `return 0` restores ROM's `beq` against a materialised 7 plus the `bnel` carrying the zero in its delay slot. |
| `func_0015F450` | 0 first try | The `D_00274EC0` ratio idiom with a second divide. ee-gcc routes the *second* multiply/divide pair through the R5900's second pipe (`mult1`/`div1`) automatically, so it must stay one flat expression — splitting into temps loses `div1`. |
| `func_0015F5F8` | 1 → 0 | Three plain compound assignments in ROM's order (clear a bit in the `0x20` long long, clear one in `0x18`, then set one in `0x20`). Folding the first and third into one read-modify-write expression materialises `0x40000` too early and swaps the two `sd`s; as three statements cse folds the two `0x20` accesses back into one `ld`/`sd` pair *and* the constants come out in ROM's order. |
| `func_0015F358`, `func_0015F3C0` | 0 first try | Assert-wrapper twins (line numbers `0x5AF` / `0x629`) around `eBrainInit`. |
| `actCommonFly`, `actCommonLadder`, `func_0015DF60`, `func_0015E448` | 0 first try | Plain act-coroutine stub tails. |

## Cracked class — "gcc parks a local array's address in a callee-saved register"

Open since conv-9 (`func_0015DF88` residual (a), `enemy_act func_001619A8`).
**The fix is to declare the array inside the `static __inline__` helper that owns
its uses, not at function scope.**

Mechanism, read off the `-da` dumps: expanding an array used as a pointer emits
`addiu <pseudo>,fp,OFF` once per use (`expand_expr`'s ADDR_EXPR path calls
`force_operand` into a fresh pseudo).  When every use names one function-scope
array, **cse1 unifies them into a single pseudo** — a pseudo is *not* invalidated
at a `CALL_INSN` the way a call-clobbered hard register is, so the copy survives
every call.  `update_equiv_regs` then records no equivalence (the set insn is
`(set (reg N) (plus (reg fp) K))` with no `REG_EQUAL` note, and the non-MEM path
requires one), so there is no `REG_LIVE_LENGTH *= 2` and no reload
rematerialisation; global-alloc simply hands the pseudo a third callee-saved
register and every use becomes `daddu <arg>,s2,zero`, plus 16 bytes of frame.

Putting the array in the inline helper keeps the address materialisation local to
each expansion: the uses stay separate pseudos, each dies at its arg-register
copy, and combine folds the pair into ROM's `addiu <arg>,sp,OFF`.  Two disjoint
helper expansions also share the one 16-byte slot, which is why ROM's frame has
room for only one buffer.  The matched sibling `func_0015E080` is the existing
proof of the shape (it uses the TU's `func_0015C818_disp` helper and ROM emits
two independent `addiu ...,sp,0x10`).

Two further `func_0015DF88` points worth carrying:
* The second `a0` reload must be taken **before** the `0x14` handler store, or the
  store-to-volatile-home read-after-write pins it behind the store and the two
  `0x164` derefs stop pairing up the way ROM has them.
* `D_00630CCC` is `volatile`.  ROM leaves the three branch delay slots feeding the
  `func_00102C10` block as `nop` and fills the first from the following `slti`.
  A non-volatile gp-relative load is a legal delay-slot steal from the *target*
  thread (`mostly_true_jump` predicts a `bne` taken, so `fill_eager_delay_slots`
  tries the target first), so reorg duplicates it into all three.  A volatile MEM
  sets the resource `volatil` flag, which makes `resource_conflicts_p` reject
  every delay-slot move — matching ROM.  The symbol has no other reference in the
  tree.  Non-volatile alternatives tried and rejected: hoisting the load into a
  `float` temp before the if-chain (sites 4 → 9).

## Still open in commonact after conv-10 — the "shift-by-one local-alloc" class

Three functions are structurally exact with **instruction order identical to ROM**
and only register *names* differing, and all three differ in the same way: ROM's
assignment is ours shifted up one slot in `find_free_reg`'s scan order.

| func | sites | best rc | ours → ROM |
|---|--:|--:|---|
| `func_0015F650` | **4** | 6 | read1 `$2`→`$3`, s164 `$3`→`$6`, or-mask `$6`→`$7` |
| `func_0015ADF0` | **5** | 6 (7 in the order-exact shape) | const `$2`→`$3`, read1 `$4`→`$2`, read2 `$6`→`$7`, s164 `$3`→`$6` |
| `func_0015F578` | **5** | 9 | `lw v0/v1` pair swapped, plus `sd ra` scheduled before the `%lo` so the `jal debug_assertMessage` delay is a `nop` instead of `addiu a0,a0,%lo` |

Mechanism, from `-dl` dumps + `local-alloc.c`.  `block_alloc` allocates in two
passes: first every quantity that has a copy suggestion (the arg-register copies),
then the rest sorted by
`QTY_CMP_PRI = floor_log2(n_refs) * n_refs * qty_size / (qty_death - qty_birth)`,
ties broken by ascending quantity number (= birth order in the **sched1** output,
not the emitted order), each allocated to the lowest-numbered register free over
its lifetime *widened by one insn on each side*.

For `func_0015F650` (18 insns, fully worked): quantities are read1 (len 3),
read2 (len 3, copy-suggested `$4`), s164 (3 refs, len 7), the DImode `ld`/`or`
results (len 1 each, size 2), the DImode mask constant (len 13), and the two
`0x15C` pseudos.  The DImode results sort first and take `$2`; nothing else holds
`$2` over read1's range, so read1 takes `$2`, which leaves `$3` for s164 and `$6`
for the mask.  ROM needs read1 on `$3`, which requires **some quantity holding
`$2` across read1's lifetime at the moment read1 is allocated** — and no
quantity in our schedule does.  Since local-alloc runs on the *sched1* output and
sched2 reorders afterwards, ROM's sched1 order can differ from ours while the
emitted order matches; that is the only remaining degree of freedom and is where
the next attempt should go (read the `.sched` ready lists, not the `.s`).

`func_0015ADF0` is the same shape one size up, and its analysis is sharper: for
ROM's assignment, the volatile read that feeds `+0x164` must be allocated
**before** the `high` pseudo of the `%hi/%lo` pair.  Both have live length 4 and
the `high` pseudo has the lower quantity number (sched1 hoists `lui`/`addiu` to
the top of the block because the chain `high → lo → store → call` gives it
priority 3+P against 1+P for everything else ready at t=1), so the tie always
goes to `high`.  Beating it needs either the `lui` and the `lo_sum` **not
adjacent** in sched1's output, or a genuinely larger `n_refs`/`qty_size` on the
read — neither reachable by respelling the current data model.

Shapes probed for `func_0015ADF0` (sites / rc, all order-exact unless noted):
* baseline seed (`s164` deref hoisted to its decl, `int self15C = a0`, `void *self`) — 5 / 7, emitted order **exact**, 0 of 4 registers right.
* both derefs hoisted to decls (`char *s164`, `char *s15C`) — 5 / **6**, and `const → $3` and `s164 → $6` **snap to ROM**, but the `0x15C` load moves ahead of the `0x18` store (source order + the anti-dependence pin it), costing 2 sites.  Best structure-forward waypoint; source saved in the scratchpad as `commonact_func_0015ADF0_bothderefs_s5_rc6.c`.
* store order swapped — 6 / 9 (moves the `0x18` store into the `jal` delay).
* no temps at all — 6 / 13 (collapses the three volatile reads).
* `self15C` / `self` assigned late — 6 / 13 (read1 and the `0x164` deref become adjacent, killing the interleave).
* three explicit `int selfN = a0` reads — 5 / 7, identical to the baseline.

## Recommended next steps in commonact

1. `func_0015D520` (32), `func_0015D620` (35), `func_0015D488` (38),
   `actCommonRope` (38) — untouched, smallest-first.
2. The `0015D6D0`…`0015D1F8` band (69–81) and the `RopeCliff` / `CollisCheckInRope`
   family, which share the rope-collision idiom.
3. The shift-by-one local-alloc class above — worth one focused pass, since it
   holds `func_0015F650` (4 sites), `func_0015ADF0` (5) and `func_0015F578` (5)
   at once and the next lever is identified (sched1 order, not source respelling).

## conv-11 — commonact continued (worker: rwt2)

Sites-first, same metric as above.

### Matched

| func | insns | sites before → after | mechanism |
|---|--:|---|---|
| `func_0015D620` | 35 | 0 first try | `D_00274EC0` ratio guarded by a two-test `&&` on the `0xC8` mode and bit 0 of `0x128`, stored as a `short`. |
| `func_0015D520` | 32 | 3 → 0 | **reload-before-store** (see the class note below). |
| `CollisCheckInRope` | 60 | 5 → 0 | **reload-before-store** again. Note this one deliberately keeps its `int buf[4]` at *function* scope: both uses sit in the same basic block, so ROM parks the address in a callee-saved register (`addiu s0,sp,16` once + `daddu` copies). The `func_0015DF88` inline-helper lever applies to arrays whose uses straddle a loop, **not** as a blanket rule. |

### New reusable class — "the volatile home reload must precede the handler store"

Three functions this round hit the identical shape: an act head does
`s164->0x14/0x18 = <handler>;` and then immediately calls something whose first
argument is the object itself.  Spelled with the reload at the call
(`f((void *)a0, …)`) or at the test (`if ((char *)a0 == D_…)`), the reload is a
read-after-write against the preceding **non-volatile** store — the param home is
alias set 0, so it conflicts with everything — and is pinned *behind* the store.
That leaves the store as the last insn before the branch/call, so reorg puts the
*store* in the delay slot instead of ROM's argument insn, and the surrounding
schedule shifts by one.

Fix: bind the reload to a local assigned **before** the store
(`self = (void *)a0; s164->0x18 = h; f(self, …);`).  This is the *mirror* of the
`func_0015E1B0` lever — there the local had to be removed because it added an
arg-register copy that changed the sched1 priority; here the local is required
because it moves the volatile read to the other side of a store.  The
discriminator is whether the reload's consumer is the *call* (inline it) or
whether the reload must cross a store (bind it early).

### Parked near-misses (crutch-free, sources in the worker scratchpad)

| func | insns | sites | residual | next lever |
|---|--:|--:|---|---|
| `func_0015D488` | 38 | **1** | Everything matches except the 64-bit load of `D_00558DB8`: ROM has `lui $1,%hi(...)` + `ld $5,%lo(...)($1)` — `$1` is `$at`, i.e. the *assembler* expanded a single symbolic `ld $5,D_00558DB8`. Our gcc splits the address itself into a `(high)` insn with a real register, because `mips_check_split` (mips.h `GO_IF_LEGITIMATE_ADDRESS`) rejects a non-small `SYMBOL_REF` for a mode whose size is not `> UNITS_PER_WORD`. Declaring the symbol small gets the single insn but the assembler then emits `%gp_rel`; `__attribute__((section(".sdata")))` on a >8-byte extern gets the single symbolic `ld` *and* no `.extern name,8`, but all three assemblers in the tree (`ee-gcc2.96/bin/as`, `ee-gcc2.9-991111/bin/as`, `mips-linux-gnu-as`) expand `ld $5,sym` using the **destination** register, never `$at` — verified directly. `mips_move_2words` has no `.set noat` template for this case. | This looks like an assembler-parity item rather than a source shape — it needs someone who owns the always-on postprocess / assembler selection, not a C respelling. Everything else in the function is byte-exact. |
| `func_0015D6D0` | 69 | **3** | Head is exact. Residual is the position of the *third* volatile home reload in the loop: ROM issues it after the `div`, we issue it five slots earlier, which then renames three registers. | Shapes tried: three `int cN = a0` temps up front (4 sites); `c2`/`c3` assigned after the `0x3A0` store (5); `c1`,`c2` up front and `c3` late (6); third read inlined at its use (6); `char **`-typed `0x164` derefs in the loop (5). Best is three temps up front **with the comparison written `v250 > v254`** rather than `v254 < v250` (4 → 3 sites) — gcc evaluates the operands in source order, so the spelling decides which reload pairs with which field. Next: the 0x678 / 0x670 chain's alias regime, or lengthening the divisor chain so the reload's ready time shifts. |
| Two head fixes worth reusing from this function | | | ROM hoists the `s164->0x150 = s164->0x60C` **load** across the preceding `0x250` store — only legal if they are in different alias sets, so that field copy is `void **`-typed, not `int` (9 → 4 sites on its own). And the three chained `0x250`/`0x258`/`0x25C` zero-stores each need their own `int bN = a0` reload hoisted ahead of the stores, exactly as in `func_0015E388`. |

`func_0015F650` (4 sites), `func_0015ADF0` (5) and `func_0015F578` (5) are
unchanged from the conv-10 section above — the shift-by-one local-alloc class.

### conv-11 addendum — `func_0015F650` matched; the "shift-by-one" bucket is smaller than it looked

`func_0015F650` (18 insns, 4 sites) **matched**, and it was never a coloring tie:
the fix was the `func_0015E1B0` lever — write the volatile-param argument
inline at the call (`ReviveEnemyParticle((void *)a0, 1)`) instead of routing it
through a `void *self` local.  The local's extra arg-register copy lengthens the
reload's sched1 chain, which shifts the whole block's quantity birth order and
renames three registers.  **Anything filed under "shift-by-one local-alloc"
should be re-tested against the two argument levers first**; the coloring
analysis was measuring a downstream symptom.

`func_0015ADF0` improved **5 → 4 sites** (rc 6) on a new axis: spelling *both*
the `0x18` handler store and the `0x15C` pointer load as pointer types
(`*(void **)(s164+0x18) = (void *)func_0015F650;` with
`s15C = *(char **)(self15C + 0x15C);`) snaps the handler constant to `$3` and
`s164` to `$6` — both ROM registers.  The residual is now a genuine tension:

* the two accesses in **different** alias sets ⇒ the `0x15C` load floats ahead of
  the `0x18` store (costs 2 sites of ordering) but the registers snap (4 sites);
* the two in the **same** alias set ⇒ ROM's order is exact but no register snaps
  (5 sites).

ROM has both, so the register snap does *not* actually depend on the load
floating — something else lengthens `s164`'s live range in ROM by one insn
between its load and the store.  Both sources are saved in the worker scratchpad
(`commonact_func_0015ADF0_regsnap_s4.c`, `..._orderexact_s5.c`).  Next lever:
find the fourth insn ROM has between the `0x164` deref and the `0x18` store —
the argument levers above are the first thing to re-test, then the `&other`
address-setup position.

`func_0015F578` stays at 5 sites; `int`-typed `0x15C` deref, a hoisted
destination local, and a re-cast source blob all leave it unchanged.

# conv-12 / branch `acttails-3`

Landed on top of `3e841f79`.  Sites-first; every match gated on
`.venv/bin/ninja` + explicit `tools/verify_elf.py`.

| commit | TU | funcs | mechanism |
|---|---|---|---|
| `3a5b8fdb` | girl_act | `func_00175350` | the func_001754F8 sampler loop, plus a seventh store — `buf20[1] = buf10[1]` |
| `76fc4e82` | st47a | `func_002389C8`, `func_00238A70`, `func_0023A8E8`, `func_0023A668`, `func_002387B8` | Generator mask/call family; two guarded stage_KillPlayBgAnimation tails |

## CORRECTION — girl_act's small end is NOT ordinary matching work

The conv-11 "still open" note said to sweep girl_act smallest-first.  That is
wrong for the two smallest entries after `funcGirlHandDisconnect`:
**`actGirlDitch3mExec`(61) and enemy_act `func_00163890`(47) take their
argument in `$2`, not `$4`** — both open with `daddu $rN,$2,$0` / `sw $2,0(sp)`
before any call.  They are the arg-in-v0 class (`static` + a same-TU caller),
so they cannot be matched in isolation: the caller has to be matched in the
same edit.  Do not queue them as ordinary leaf work; queue them as a PAIR with
their caller.

## Parked at sites 6 — girl_act `funcGirlHandDisconnect` (34 insns)

Structure and both branches are exact; `int k = *(int *)(obj + 0xC);` read
BEFORE the zero-store is what puts ROM's `lw v1` / `li v0,4` letters right and
gets the zero-store into the `bne` delay slot (sites 8 -> 6).  Residual is two
coupled sched2 ties in the tail block:
`sw zero,12(s0)` lands one insn later than ROM (after `daddu a0,s0,zero`
instead of immediately after `sw zero,8(s0)`), and the two loads of the
tail-call argument chain `*(int *)(*(int *)(obj + 0x15C) + 0xC)` come out
`v0 -> v1` where ROM has `v1 -> v0`.
Refuted as no-ops (identical RTL — do NOT retry): store order of out[2]/out[3],
one `long long` store, `&out[0]` vs `out` for the a0/a2 arguments, a `float *p`
temp, an `int *out` signature, `c * 64` vs `c << 6`, shifting `c` early, an
`int arg` temp for the whole expression, a `char *sub` intermediate, and
reversing the addend order.  Near-miss source in this pass's scratch
(`ghd_s6.c`).  Next reasoned lever: the two residuals are one event — raise the
`sw zero,12` priority so it retires with its sibling (give the stored value an
in-block consumer, or make out[2]/out[3] part of the same object as out[0]).

## CORRECTION (conv-13) — st47a `func_0023A5B0` is NOT the `%hi`-pair class

conv-12 filed this as "a FIFTH instance of the two-allocno `%hi` tie" and
recommended solving the tie to land five functions.  **Both halves of that are
wrong, and this entry supersedes it.**

1. **The `%hi` tie was already RESOLVED, in conv-5** (see "RESOLVED — the
   two-allocno `%hi` tie (5 funcs, one root cause)" above).  All five members —
   `actSt04eWaterFlagOn`, `actSt02aEne`, `actSt02aSekizo`, `actSt05dDoor2UpChk`,
   `actSt03tWayOffChk` — are matched in the tree today; verified per function
   against their TUs' `INCLUDE_ASM` sets.  There is no five-function payoff to
   chase.  conv-12 cited the stale batch-5 row (line ~218) without noticing the
   conv-5 resolution further down the same file.

2. **`func_0023A5B0` is a different problem.**  The resolved class is about
   gcse PRE hoisting two `(high (symbol_ref …))` expressions out of a WAIT LOOP
   into CALLEE-SAVED registers, where the bucket order of the expression hash
   table (a function of the symbol's spelling) picks which gets the lower
   register; the fix is the `base + index` re-spelling.  `func_0023A5B0` has no
   loop — its tail is straight-line inside an `if` — so PRE hoists nothing, and
   its two `%hi`s live in CALLER-saved registers (ROM `$3`/`$6`, i.e. `v1`/`a2`).
   The conv-5 recipe does not apply and was measured not to: sweeping the
   address over eleven `base + N` spellings moved nothing (all bases that
   compiled gave the identical result).

### What `func_0023A5B0` actually is (sites 4, best measured)

One root cause: **the third store `*(int *)(actSt25aQueenDeadChk(0x1CC) + 0x16C) = 0`
retires too early, which frees `v0` and re-letters both addresses.**
ROM emits, after the QueenDeadChk call: `lui $3`(table), `lui $6`(handler),
`lw $4,0(sp)`, the two `addiu`s, `addiu $5,0x18D`, `sw $3,0xC4($16)` (unkC4),
`sw $0,0x16C($2)` (the third store), then `sw $6,0x4($3)` in the BoxBarSoundOn
delay slot.  `$2` therefore stays live across BOTH address materialisations,
which is exactly why the table takes `$3` and the handler takes `$6` — `v0` is
busy and `a0`/`a1` are reserved for the imminent call.  Every shape we produce
retires that store immediately after the call, freeing `v0`, and the letters
follow.

Measured and refuted — do NOT re-run these: all six permutations of the three
tail statements, with AND without an `int q` temp holding the call result (12
combinations; best 4 sites at `T,U,Q`/`T,Q,U`/`U,T,Q`, and 5 sites at any order
with `Q` first); eleven `base + N` re-spellings of the table address; and the
third store spelled as a pointer store instead of an int store.  Note the
alias-set constraint that limits the space: the third store and `D_x[1] = fn`
are both in the `int` set so their relative order is fixed by source, while
`gobj->unkC4` is a pointer store and moves freely.

Next reasoned lever, from `rank_for_schedule`'s second key: the third store is
`q`'s LAST use, so INSN_REG_WEIGHT gives it a register-freeing boost and it
schedules early.  ROM's does not get that boost — so in the dev's source `q`
has a later consumer, or the value is not a call result held in a pseudo at
all.  Look for a second, real use of the QueenDeadChk object in the retail
code rather than trying to hold the store back by ordering.

## Remaining in this scope

st47a is down to 38 stubs but the cheap templates are exhausted — what is left
is mostly long cutscene threads (`func_00239830`, `func_00238F10`,
`func_00239138` and friends, 30-50 calls each), which are transcription work
rather than template work but should still go quickly.
girl_act (46) and enemy_act (41) remain the bulk; after the arg-in-v0 pair
above, the next ordinary targets are girl_act `actGirlWalk`(66),
`func_00173060`(68), `actGirlSupportGBLoop`(69) and enemy_act
`MoveChestForCatchBoy`(67), `func_001605F8`(73), `_ApproachTarget_Boss`(75).
## conv-12 — commonact (worker: rwt2)

### Matched

| func | insns | sites before → after | mechanism |
|---|--:|---|---|
| `func_0015F578` | 22 | 5 → 0 | **Declaration form of the assert string.** `D_006322F0` is defined later in this TU as a carved `unsigned int[2]`; naming it directly gives gcc a known-size TU-local object and the `%lo` half of its address then outranks the `sd ra` prologue save at the sched2 tie, landing before the save so reorg has nothing for the `jal` delay slot (ROM fills it with the `addiu`). Referring to the same symbol through an incomplete `extern char[]` alias — how a dev declares an assert message — restores ROM's order *and* the `v0`/`v1` pair on the `0x15C` chain with it. Matched with both `int` and `float` members for the 12-byte blob, so the member types are not load-bearing. |
| `func_0015DA20` | 77 | 0 first try | Five function-scope buffers must be declared **low-offset-first**: gcc assigns stack slots in declaration order at increasing offsets, so declaring them `0x10 … 0x50` puts them where ROM has them and yields the same five callee-saved address registers. The two 12-byte vector copies reuse the F578 struct-assignment shape. |

### Priority-1 result: the "shift-by-one local-alloc" bucket is closed as a class

All three members are now accounted for and **none of them was a coloring tie**:

* `func_0015F650` — the inline-argument lever (conv-11).
* `func_0015F578` — a symbol declaration form (above).
* `func_0015ADF0` — still open at 4 sites, but see below; the coloring reading no
  longer has evidence behind it.

**Generalisation worth carrying: before reasoning about allocation, check the
declaration of every symbol the function names.** Whether gcc thinks an object is
small, TU-local and of known size feeds `ENCODE_SECTION_INFO` → `SYMBOL_REF_FLAG`
→ address costs → sched2 ties, and that shows up as "register naming" diffs far
from the symbol itself.

### `func_0015ADF0` — parked at 4 sites, with measurements

Best crutch-free source: `commonact_func_0015ADF0_regsnap_s4.c` in the worker
scratchpad (4 sites / rc 6; `const → $3` and `s164 → $6` match ROM, the `0x15C`
load floats one slot ahead of the `0x18` store).  Order-exact alternative at 5
sites: `..._orderexact_s5.c`.

Hypotheses tried this round, all measured, none better than 4:

| shape | sites |
|---|--:|
| `&other` bound to a local `int **op` (extra copy reload coalesces away) | 5 |
| plain `func_0015F650` forward decl instead of an `__asm__` alias | 5 |
| `int *s164` + `s164[6] = …` instead of `char *` + `*(int *)(s164+0x18)` | 5 |
| `self15C` inlined at the `0x15C` deref, `self` assigned after it | 6 |
| extra `int selfA = a0` in front of the `0x164` deref | 5 |
| both accesses `void **` (register snap, load floats) | **4** |
| both accesses same alias set (order exact, no snap) | 5 |

Measured local-alloc state for the **order-exact** base (sched1 chain index in
brackets), which is what a future pass should start from rather than re-deriving:

```
idx0  insn4    [home] mem/v[at] = $4
idx1  insn23   r91 = high(func_0015F650)      len 4   -> $2   (ROM $3)
idx2  insn25   r92 = lo_sum(r91)              len 16  -> $2   (ROM $3)
idx3  insn248  mem[at+4] = 0                  (other = 0)
idx4  insn10   r85 = mem/v[at]   readA        len 4   -> $4   (ROM $2)
idx5  insn53   $5 = at|4         (&other)
idx6  insn15   r86 = mem/v[at]   readB        len 6   -> $6   (ROM $7)
idx7  insn12   r84 = mem[r85+0x164]  s164     len 3   -> $3   (ROM $6)
idx8  insn18   r87 = mem/v[at]   readC        len 3   -> $4   (ROM $4) [pass-1 copy sugg]
idx9  insn27   mem[r84+0x18] = r92   store
idx10 insn51   $4 = r87
idx11 insn30   r93 = mem[r86+0x15C]  deref    len 2   -> $2   (ROM $2)
idx12 insn32   mem[r93+0x5F8] = 0
idx13 insn55   call func_00165418
```

For ROM's assignment, `readA` must be allocated before the `high` pseudo *and*
`s164` must be allocated after it — i.e. `len(readA) < len(high) = 4` and
`len(s164) > 4`.  Both are one insn away.  Note also that our allocation gives
`readA` and `readC` the *same* register even though `readA` dies at idx7 and
`readC` is born at idx8; `block_alloc`'s `fake_birth`/`fake_death` widening is
supposed to make exactly that pair conflict, so our quantities are being treated
as narrower than the widening predicts — the model in the conv-10 section does
not fully explain the observed assignment and should not be trusted further
without re-deriving from `local-alloc.c` with a debugger-grade read.

### Still parked

`func_0015D6D0` — 3 sites (unchanged; two more c2/c3 placements tried, both 6).
`func_0015D488` — 1 site, assembler-parity item, **not a matching target**.

### Not attempted, with reasons

* `actCommonRope` (38) — ROM ends the `func_00158328` call with a dead
  `daddu $2,$29,$0` (i.e. `$2 = sp`) in the delay slot.  `sp+0` is the volatile
  param home, so this is an address-of-the-parameter that survives into a dead
  caller-saved register; no source shape for it identified yet.  Everything else
  in the function is a straightforward `pac_DispQW() * 10.0f`, `/ 15`, `% 15`
  chain.
* `func_0015D1F8` (76), `motCommonRopeTurnR` (71), `func_0015CD70` (81),
  `func_00159AF0` (81) — read and understood, all reload-heavy or float-heavy;
  tractable but each needs several iterations.

# conv-13 / branch `acttails-4`

No new matches this pass — see the CORRECTION above, which supersedes conv-12's
primary recommendation.  Two further findings, both worth more than the target
they came from.

## The arg-in-v0 class — concrete evidence, and it is NOT `static`+same-TU

conv-12 flagged `enemy_act func_00163890` and `girl_act actGirlDitch3mExec` as
the arg-in-v0 class and cited the auto-memory's "`static` + same-TU-caller"
shorthand.  That shorthand does not describe what is actually in the ROM here.
The caller is `ChangeBrain_ToAttack` (same TU), and the call site is:

```
    /* 63B28 00163B28 */  jal    func_00163890
    /* 63B2C 00163B2C */   daddu $2, $29, $0      <- delay slot: $2 = the CALLER'S $sp
```

so the callee receives `&caller_local` in **`$2`**, and `func_00163890` opens
`daddu $5,$2,$0` / `sw $2,0(sp)` / `lw $2,0($5)` — it dereferences it.  It is a
real `jal`, not a fall-through, and `func_00163890` (0x163890-0x16394C) sits
entirely before `ChangeBrain_ToAttack` (0x163950), so this is not a splat
merge either.

ee-gcc 2.9 for MIPS has no interprocedural register allocation and no custom
convention for `static` callees, so "make it `static`" cannot by itself produce
this.  The only mechanisms in-tree that pin an argument to `$2` are
`register T v asm("$2")` and an inline `asm volatile` (`src/st04d.c:184` uses
exactly that for `$4`) — and an inline-asm argument pin is a CRUTCH under this
project's rules, so it must not be committed as the match.  **Do not queue
these two as ordinary work until the mechanism is established.**  The honest
next step is to find an already-MATCHED function in the tree that receives an
argument in `$2` and read how it is spelled; if none exists, this class is
unsolved and should be labelled that way rather than as "pair them with the
caller".

## Parked at sites 3 — enemy_act `MoveChestForCatchBoy` (67 insns)

Whole structure, all three early-exit tests, the `$f20` = 1.0f callee-saved
FPR, the EABI 5-int-arg `GetHeightOfFieldPlaneDifference` call and the tail all
match.  Residual is one event with two symptoms: ROM fills the
`bne $4,$2` delay slot with `daddu $2,$29,$0` — a **dead** materialisation of
`&buf` that reorg speculatively hoisted out of the branch-target thread (`$2`
is overwritten on both paths and the three real uses each recompute
`daddu $rN,$29,$0`) — and because that constant/address pair is born in the
other order, the compare's four registers come out `v0/a1/v1/a0` where ROM has
`a1/v0/v1/a0`.  We emit a `nop` in that delay slot.
Refuted — do NOT retry: constant-on-the-left compare, `!=` with the arms
swapped, an `int kind` temp for the loaded field, and an `int *g` temp for the
0x164 object.  All five spellings compile to the identical stream.
Near-miss source in this pass's scratch (`mccb_s3.c`).
Next reasoned lever: this is a reorg speculative-fill question, not a source
ordering one — the target is to give reorg a legal insn to hoist, i.e. make
`&buf` a value that is live-in to the branch target rather than computed after
it (the conv-11 `static __inline__` finding is the nearest relevant mechanism,
in reverse: here we WANT the single shared address pseudo).

## Corrected recommendation for the next pass

The `%hi` tie is closed and `func_0023A5B0` is a single function, so there is
no five-function target left in this scope.  Highest value now, in order:
(a) establish the arg-in-v0 mechanism from an already-matched example — it
gates two functions here and recurs elsewhere; (b) `MoveChestForCatchBoy`
(sites 3) and `funcGirlHandDisconnect` (sites 6), both one reorg/sched2 event
from zero; (c) the ordinary girl_act / enemy_act bodies
(`actGirlWalk`(66), `func_00173060`(68), `actGirlSupportGBLoop`(69),
`func_001605F8`(73), `_ApproachTarget_Boss`(75)).

# conv-14 / branch `acttails-5` — the arg-in-$2 class is a NESTED FUNCTION (proven)

## CORRECTION of conv-13's correction

conv-13 concluded that arg-in-$2 could only come from `register T v asm("$2")`
or inline asm, both crutches, and flagged the class unsolved.  **That was
wrong, and this supersedes it.**  The missing fact is one line of the staged
compiler:

```
ee-gcc mips.h:1793:   #define STATIC_CHAIN_REGNUM (GP_REG_FIRST + 2)
```

`$2` **is** the MIPS static chain register.  A **GNU C nested function** — a
function defined inside another function's body — receives its parent's frame
in `$2`, and the caller materialises it as its own frame pointer.  This is a
language feature with a fixed register, not interprocedural register
allocation (conv-13 was right that ee-gcc 2.9 has none; that reasoning was
just aimed at the wrong mechanism).  The auto-memory's "static + same-TU
caller" is a lossy paraphrase of "*nested* function of its same-TU caller".

## Proof (minimal TU, this compiler, these flags)

```c
void outer(int a) { int loc[4];
    void inner(void) { ext(loc[0]); loc[1] = 5; }
    loc[0] = a; inner(); ext(loc[1]); }
```
emits, at `-G 8 -O2 -mips3 -fno-builtin -fdata-sections`:

* `.ent inner.3` **before** `.ent outer` — nested functions are emitted FIRST,
  which is exactly the ROM layout (`func_00163890` @0x163890 precedes
  `ChangeBrain_ToAttack` @0x163950);
* caller: `jal inner.3` / `move $2,$sp` **in the delay slot** — ROM has
  `jal func_00163890` / `daddu $2,$29,$0`;
* callee: `move $16,$2` + `sw $2,0($sp)` then dereferences `$2` — ROM has
  `daddu $5,$2,$0` / `sw $2,0($29)` / `lw $2,0($5)`.

Three-for-three, and no trampoline is generated as long as the nested
function's ADDRESS is never taken (keep the call direct).

**Symbol name:** gcc mangles nested functions to `<name>.<N>`.  Declare the
asm name to fix it — `void inner(void) __asm__("func_00163890");` before the
definition emits `.ent func_00163890` and `jal func_00163890`.  Costs one
"static declaration for `inner' follows non-static" warning.

## State — NOT matched, draft preserved

`tough_nuts/acttails_near_misses/enemy_act_ChangeBrain_ToAttack_nested_s22_inner_s5.c`
holds the full reconstruction of both functions as one nested-function C body:
**inner sites=5, outer sites=22.**  The calling shape is right; what remains is
ordinary body convergence, and the two must reach 0 together because they are
now one C function.  Inner residual: ROM branches three ways and TAIL-DUPLICATES
the continuation into each arm, where we emit `movz` for the mode select
(if/else-if, `switch` and nested-if all measured: 5 / 10 / 9 sites — the
if/else-if chain is the best of the three).

## Consequence for the queue

`girl_act actGirlDitch3mExec` is the other known member and should be written
the same way, nested inside whichever same-TU function calls it — find the
caller by grepping the TU's `.s` for `jal actGirlDitch3mExec`, then check the
call site has `daddu $2,$29,$0` (or a `$2` set from the caller's frame) in the
delay slot.  This is a legitimate 2000-era shape, not a crutch.

Generally: **any function whose prologue reads `$2` before any call is a
nested-function candidate**, and the test is cheap — look at the one call site
for `$2` set from the caller's `$sp`.
## conv-13 — commonact (worker: rwt2)

### Priority 1: declaration-form audit across all 42 remaining functions

Every symbol referenced by the remaining `INCLUDE_ASM` set was extracted from the
ROM `.s` with its addressing form and cross-checked against the TU's
declarations.  Result: **the exposure is small and localised, not systemic.**

* All ~45 `D_00630Cxx` floats the remaining functions use are `%gp_rel` in ROM
  and have no declaration yet — a plain `extern float X;` (4 bytes, known size,
  small) is correct for every one of them.  No action needed; just do not declare
  them as arrays.
* Everything ROM addresses **far** is either already declared as an incomplete
  array / large object, or is a string constant that will get the
  `extern char X[];` treatment when its function is written.
* **Four TU-defined carved symbols are the real exposure** — all ≤ 8 bytes and
  defined in this TU, so gcc will make them `$gp`-relative, while ROM addresses
  them with `%hi`/`%lo`:

  | symbol | bytes | contents | needed by |
  |---|--:|---|---|
  | `D_006322F8` | 8 | `"set %p\n"` | `func_00158F10` |
  | `D_00632300` | 4 | `0x7F7FFFFF` (FLT_MAX) | `lever_nego1` |
  | `D_00632304` | 4 | `0x7F7FFFFF` (FLT_MAX) | `func_001595D0` |
  | `D_00632308` | 8 | `"%1.1f "` | `DownFunc` |

  These are the same block as `D_006322F0`, which `func_0015F578` already needed.
  **Recipe (proven on F578): reference them through an incomplete-type `__asm__`
  alias** — `extern char D_006322F8__x[] __asm__("D_006322F8");` for the format
  strings, `extern float D_00632300__x[] __asm__("D_00632300");` + `[0]` for the
  FLT_MAX floats.  The definition stays as carved; only the *reference* decl
  changes, and an incomplete type clears `SYMBOL_REF_FLAG` so the reference goes
  far.  This is the in-source equivalent of the `sdata_sidecar` memory's advice
  and avoids needing a sidecar object.

### Parked: `func_00156BA0` / `func_00156CF0` (84 insns each) — 20 → **6 / 7 sites**

Twins differing only in one `%gp_rel` float (`D_00630C30` vs `D_00630C34`), so
one source shape lands both.  Source saved as
`commonact_func_00156BA0_CF0_s6.c` in the worker scratchpad.

Three levers got it from 20 to 6, all previously-established ones:

1. **Inline-helper for the second buffer** (20 → 15 → 7).  ROM recomputes
   `addiu $r,$29,0x20` at both of `buf20`'s uses rather than parking it, so
   `buf20` belongs in a `static __inline__` helper that owns them — the
   `func_0015DF88` class, third instance.  Note the *first* buffer (`buf10`,
   many uses across the loop) stays at function scope and ROM does park it in
   `$17`; the discriminator is again whether the uses straddle a loop.
2. Constant/loop-variable declaration order for `lim`/`j`/`i`.
3. Head expression written with the raw symbol and literal rather than through
   the loop's `d`/`k` locals.

**Residual (6 sites), fully characterised:** ROM loads `D_00630C30` into a
*caller-saved* `$f1`, uses it for the head's `div.s`, and copies it into the
callee-saved `$f21` the loop uses (`mov.s $f21,$f1`); likewise `180.0f` into
`$f2` with `mov.s $f20,$f2`.  We emit no copies at all: `float d = D_00630C30;`
after the head becomes `(set d (reg A))` by CSE, `A` dies at the copy, and
global-alloc's copy preference then gives both the same hard register, so the
move is deleted as a no-op.  The whole loop body is byte-identical; the only
diffs are the two missing `mov.s` and the `$f20`/`$f21` swap that follows.

Shapes tried and measured: `d`/`k` before the head (15), after the head (15,
then 6 with the helper), `float r` split for the call result (15), explicit
two-variable `d = t` copies (17), no float locals at all (6 but frame 176 vs 192
and `D_00630C30` reloaded every iteration — less structure-forward), `k` declared
before `d` (6, no change).  Next lever: something that keeps the head's pseudo
live past the copy, or otherwise defeats global-alloc's copy preference, without
adding an insn — note the `180.0f` pair survives in ROM precisely *because*
`mul.s $f0,$f0,$f2` uses it after the copy, which is the shape to reproduce for
the other one.

### `func_0015ADF0` — parked at 4 sites; the remaining requirement is now exact

Per the coordinator's steer I did not extend the conv-10 `block_alloc` model.
Working only from the measured sched1 chain: ROM needs one insn moved **out** of
the gap between `readA` and the `0x164` deref, and one moved **in** to the gap
between that deref and the `0x18` store.  Those two gaps are filled by
`&other` (`ori $5,$29,4`) and `readB`, and by `readC` respectively.  Both
`&other` and `other = 0` have the lowest priority in the block (`1 + P(call)`)
and therefore fill the earliest free ALU/memory slots; there is no other insn
ready in that window to displace them, and `s164`'s load is already issued at its
earliest possible clock (`readA + 2`).  So **within this data model the schedule
is forced**, which per the no-floors discipline means the data model differs, not
the allocation.  Five more shapes measured this round (`&other` via a local,
plain forward decl, `int *s164` indexing, inlined `self15C`, an extra `selfA`
read) — all 5 sites or worse.

### Method note

A blanket `replace` of a two-line declaration pattern silently edited the
*matched* `func_0015DA20` as well as the intended function; the per-function
`INCLUDE_ASM` diff does not catch that, but re-running the oracle on the
neighbouring matched function did.  When editing by text substitution, assert on
the occurrence count.


# conv-15 / branch `acttails-6` — the nested-function class is 51 functions, not 2

The conv-14 proof made a cheap mechanical test possible, so I ran it over every
unmatched function in the tree.  **The class is far larger than the two known
members.**

## The test (two independent conditions, both must hold)

1. **Callee side** — `$2` is READ before it is written, and before the first
   call, in the function's prologue.  (`tough_nuts/acttails_near_misses/scan_static_chain.py`)
2. **Caller side** — at the single call site, `$2` is set from the caller's
   `$sp` (`daddu $2,$29,$0`) within the `jal`'s delay slot or the three insns
   before it, AND the callee is emitted at a LOWER address than the caller,
   because gcc emits nested functions before their parent.
   (`tough_nuts/acttails_near_misses/scan_static_chain_callsites.py`)

Condition 2's address ordering is the part that rules out a custom-ABI reading:
no calling convention explains why the callee is always laid out first.

## Result: 51 confirmed pairs, 0 counterexamples

Every pair that passes condition 1 and has a chain-setting call site ALSO has
the callee emitted first — 51 for 51.  Spot-checked by hand against the ROM for
`GetBoyMode`/`actGirlHand`, `CheckEnemyBrainMode`/`BrainMode_Requset`,
`actGirlDitch3mExec`/`actGirlBHang` and `func_00163890`/`ChangeBrain_ToAttack`.

Note two refinements the sample shows:
* a nested function may ALSO take ordinary parameters — `GetBoyMode` and
  `CheckEnemyBrainMode` take arguments in `$4`/`$5` alongside the chain in `$2`;
* the caller is not always the obvious neighbour — `actGirlDitch3mExec`'s
  parent is `actGirlBHang`, not the adjacent `func_00173060`.  Always confirm
  from the call site rather than from layout.

CONFIRMED pairs (callee <- parent), grouped by TU:

  DisplayFont            func_001FAE98                  <- dl_Init
  Primitive              prim_DispMesh3D                <- prim_DispParticle
  Primitive              prim_DispWireSphere            <- reg_setShape
  RegistPacket           reg_resetDissolve              <- reg_dispNObj
  RegistPacket           reg_setCMatrixPacket           <- reg_transMaterialPacket
  Shadow                 __GetCameraPos                 <- func_001224E0
  Shadow                 shadow_Render                  <- shadow_getShadowVectorAverage
  Shadow                 shadow_getShadowVectorAverage  <- shadow_EntryClusterShadow
  act-game               ACTGame_LwsEffectProcess       <- _ACTGame_SearchGObj
  boyact                 UpdateGeo                      <- BoyBgaManager
  camera-editor          menuPinSelect                  <- menuPinEdit
  commonact              DamageFunc                     <- actCommonDown
  commonact              DownFunc                       <- actCommonDown
  commonact              EBRAIN_SEND_MES                <- actCommonDown
  commonact              func_00158328                  <- actCommonRope
  debug                  debug_brainBar                 <- debug_MakeBarString
  debug                  draw_shikaku                   <- debug_MakeBarString
  enemy_act              CheckEnemyBrainMode            <- BrainMode_Requset
  enemy_act              GetFlyPosition                 <- NakaBoss
  enemy_act              func_00163890                  <- ChangeBrain_ToAttack
  girlForceField         func_001D1D00                  <- getBone
  girl_act               GetBoyMode                     <- actGirlHand
  girl_act               IsGirlStatusEscortEnable       <- DebugDispAutoEscort
  girl_act               actGirlDitch3mExec             <- actGirlBHang
  girl_act               actGirlReadyMove               <- actGirlRescueDst
  girl_act               actGirlRun                     <- actGirlBHang
  girl_act               func_0016F2A8                  <- actGirlSupportBGBegin
  girl_act               func_00170950                  <- ACTGame_GirlBeforeFunc
  girl_act               func_00170ED8                  <- actGirlSupportGBBegin
  girl_act               subGirlBrain_Pulledup          <- ATGoalTurnMail
  motionManager          func_001DE588                  <- func_001DE6B8
  motionManager2         _getS16MotRotElem              <- _getMotion
  quaternion             GetQuaternionFromMatrix        <- CopyQuaternion
  soundManager           func_00148278                  <- func_00148340
  soundManager           func_00148E60                  <- func_00149210
  soundManager           func_00149768                  <- func_00149898
  stageMultiBgaManager   func_001EC168                  <- func_001ECCA0
  stageMultiBgaManager   func_001EC2E0                  <- func_001ECCA0
  stageMultiBgaManager   func_001EC410                  <- func_001ECCA0
  stageMultiBgaManager   func_001EC5C0                  <- func_001EC9A8
  stageMultiBgaManager   func_001EC6F8                  <- func_001EC9A8
  stageMultiBgaManager   func_001EC9A8                  <- func_001ECCA0
  stageMultiBgaManager   func_001ED238                  <- blur
  stageMultiBgaManager   func_001ED2F8                  <- blur
  stageMultiBgaManager   func_001ED3C8                  <- blur
  stageMultiBgaManager   func_001ED608                  <- blur
  staticBlur             auraInspireBefore              <- copyAlphaChannelOfWork0ToFeedBackArea
  staticBlur             blendWork0ToWork1              <- testAA
  staticBlur             blurBlendFeedBackAreaToWork1   <- testAA
  staticBlur             parallelAddFeedBackAreaToWork0 <- testAA
  staticBlur             reduceCopyAlphaChannelOfWork1ToWork0 <- copyAlphaChannelOfWork0ToFeedBackArea

## Why this matters for the queue

Sixteen TUs are affected, several of them outside the act/script scope
(`staticBlur` 5, `stageMultiBgaManager` 10, `soundManager` 3, `Shadow` 3,
`commonact` 4, `Primitive`/`RegistPacket`/`DisplayFont`/`quaternion`/… ).
Each of these is unmatchable in isolation and will burn a worker's pass if
queued as ordinary leaf work — the callee has to be written INSIDE its parent
and the two land together.  **Any queue entry naming one of the 51 above should
be re-labelled as a nested-function pair before it is handed out.**

Recipe is in conv-14: define the callee inside the parent's body, force the
symbol with `void callee(...) __asm__("<name>");` before the definition, keep
the call direct (taking its address generates a trampoline), and expect the
"static declaration follows non-static" warning.

## conv-15 addendum — the nested pair is still at inner 5 / outer 22

§13.4 (goto-CFG tails written OUT OF LINE rather than nested `else`) was applied
to the inner function's three-way mode select and does NOT move it.  Measured,
all on `func_00163890`:

| shape | sites |
|---|--:|
| `if / else if / else` (draft baseline) | **5** |
| goto-CFG, tails out of line, one shared continuation | 9 |
| goto-CFG with the mode==0 tail DUPLICATED (mirrors ROM's layout literally) | 5 |
| early-`return` after the mode==0 arm | 5 |
| `switch` | 10 |
| nested `if` | 9 |

So five distinct CFG spellings all land on 5 sites and none reproduces ROM's
partial tail-duplication.  Do not spend another pass on CFG spelling.

The suspicious construct is not the mode select at all — it is
`if (D_00633D00 != 0)`, a test of an ARRAY's address, which is always true.
ROM keeps the test AND threads it inconsistently: the `mode == 0` arm resolves
it one way (`bnez $4` -> the `$7` store) while the shared arm keeps the
opposite branch (`beqz $4` -> the `$8`/`D_00632390` store).  That is a
partially-resolved jump-threading of a known-true condition, and getting gcc to
half-resolve it is what the residual actually is.  Next lever should target
that construct's data model (what IS `D_00633D00`, and is the test really on
its address?) rather than the enclosing control flow.

---

## Standing-queue invariant (orchestrator, 2026-07-29)

**An entry leaves this queue only when the function is MATCHED.** Not when it
is hard, not when it has resisted N attempts, not when it has been
reclassified, and not because fresher targets look cheaper per round. A
plateau is not a stopping point; "out of ideas" is not; "N shapes measured"
means those N were the same axis. Re-ordering by value is legitimate —
retiring is not.

Precedent: `func_001FCA20` ran five consecutive rounds with zero byte movement
and was offered a cap three times; it landed at session 17 on a lever no
earlier round had considered. Each flat round narrowed the space that made the
last one possible.

### Audit — attempted functions readmitted to the queue

Cross-referencing every function named in an attempt context across
`decomp/*.md` against the unmatched set gives **38 attempted-and-still-
unmatched** functions. **23** were listed below; the **15** here had fallen
out of the standing section and are hereby readmitted. They are not new work —
each one was attempted, set aside, and then silently stopped being listed,
which is precisely the failure mode this invariant exists to prevent.

| func | note |
|---|---|
| `func_00200848` | act-env; sibling of the matched func_001FCA20 / func_00200970 / func_002009F0 |
| `func_0017E660` | |
| `func_001AD768` | |
| `func_00237C18` | st47a |
| `pac_makeNormalStrip` | Packet family; see the jtbl-blocked `pac_continueTag` note |
| `cut_gobj_dl_link` | |
| `scpKillSpiderGroup` | spider-group family |
| `soundSeVolSet` | sound |
| `poolRideFunc` | pool family — 8 no-twin pool/sound funcs already noted below |
| `PoolGeo` | pool family |
| `GetPoolGlobalHeight` | pool family |
| `GetPoolGlobalHeightDetail` | pool family |
| `CheckPoolHasGridMesh` | pool family |
| `DispLimitedPoolReflactionMesh` | pool family |
| `SetLayoutedPoolReflactionMesh` | pool family |

The pool cluster is seven of the fifteen and they are siblings, so they are
likely one shape rather than seven problems — worth taking as a family the way
the device-request and BoxBar templates were.

**Note on scope:** the 2,622 unmatched functions overall are inventory, not
queue. This queue is the *attempted* set — functions carrying knowledge that
is lost if they fall off the list. An untouched function loses nothing by
waiting; a skipped one loses its residual, its refuted axes and its best
sites count.
## conv-14 — commonact: static-chain audit and corrected queue (worker: rwt2)

### Static-chain class in commonact: **4 pairs, 2 parents**

Ran `tough_nuts/acttails_near_misses/scan_static_chain.py` and
`scan_static_chain_callsites.py` against commonact rather than trusting the
summary.  Four callee candidates, all four confirmed on **both** halves of the
test plus the address ordering:

| callee | insns | parent | parent insns | evidence |
|---|--:|---|--:|---|
| `EBRAIN_SEND_MES` | 82 | `actCommonDown` | 501 | chain-set at call site |
| `DamageFunc` | 347 | `actCommonDown` | 501 | chain-set at call site |
| `DownFunc` | 171 | `actCommonDown` | 501 | chain-set at call site |
| `func_00158328` | 108 | `actCommonRope` | 38 | chain-set at call site |

`func_00158328` worked through in full as the sample:
* **Callee half** — `daddu $23,$2,$0` (0x15836C) and `sw $2,0x0($29)` (0x158380)
  read `$2` before any write to it and before the first `jal` (0x158384).  It
  keeps the chain in a callee-saved register *and* spills it to its own frame,
  the usual nested-function pattern for reaching the parent's locals.
* **Call-site half** — `jal func_00158328` / `daddu $2,$29,$0` in the delay slot
  (0x15854C-0x158550), the chain being `actCommonRope`'s own `$sp`.
* **Address ordering** — `0x158328 < 0x1584D8`, callee below parent. ✓
* It also takes ordinary parameters (`$4` = the `% 15` remainder, `$5` = the
  `0x214` field), confirming the "nested functions can still have arguments"
  refinement.

**This closes an open item from conv-13.**  I had flagged `actCommonRope` as
"not attempted — ROM ends the `func_00158328` call with a dead
`daddu $2,$29,$0` (the address of the volatile param home) and no source shape
was identified."  It is not a dead insn and not the param home: it is the static
chain.  `actCommonRope` is unmatchable in isolation and always was.

### Queue corrections

* **`DownFunc` is withdrawn from the four alias-fix targets.**  It is a
  static-chain callee of `actCommonDown`; its `D_00632308` (`"%1.1f "`)
  declaration-form fix is still correct but cannot be cashed on its own.
  `actCommonDown` + `EBRAIN_SEND_MES` + `DamageFunc` + `DownFunc` is **one C
  function of 1101 insns** — the largest single unit left in commonact, and all
  four members are currently `INCLUDE_ASM`.
* The other three alias targets are **clear** — `func_00158F10` (`D_006322F8`),
  `lever_nego1` (`D_00632300`), `func_001595D0` (`D_00632304`) are not in the
  candidate set and remain independently matchable.
* `func_00156BA0` / `func_00156CF0` and `func_0015ADF0` are **not** in the
  candidate set.  So the static chain is *not* the explanation for `func_0015ADF0`
  — that hypothesis is ruled out, and the conv-13 conclusion ("the data model
  differs") still needs a different data-model difference.
* **`actCommonRope` + `func_00158328` = 146 insns** is now the most tractable
  unit in the class and is the natural first target: small parent, one nested
  callee, and the parent's body is already understood
  (`pac_DispQW() * 10.0f`, `/ 15`, `% 15`, `0x214` → `0x218`).

### `func_00156BA0` / `func_00156CF0` — still 6 / 7 sites

Two more shapes measured this round, both aimed at keeping the head's pseudo
live past the copy so global-alloc cannot unify the registers:
`float r` + `float A` + `float k0` with `d = A; k = k0;` placed **before** the
head's use (6, unchanged), and the same with the copies after (6).  An RTL dump
across `jump`/`cse`/`gcse`/`loop`/`cse2`/`combine` found **no SF register-to-
register copy at any stage**, so gcc is not deleting a copy we generate — it
never generates one.  `float d = <already-computed value>` expands directly to
the load/constant in `d`'s own pseudo.  Reproducing ROM's `mov.s` pair therefore
needs a construct that *forces* two pseudos, not a re-ordering of the same one.
Source saved as `commonact_func_00156BA0_CF0_s6.c`.

### conv-14 correction — `func_0015ADF0`: the live-length requirement I recorded was wrong

The conv-13 entry claimed ROM needs `len(readA) < 4` and `len(s164) > 4`, i.e.
one insn moved out of one gap and into another.  **Measured against the ROM
listing, that is false.**  Counting the emitted head:

```
ROM                                     ours (order-exact, 5 sites)
5AE08 lw $2,0(sp)     readA             lw a0,0(sp)      readA
5AE0C sd $16,0x10(sp)                   sd s0,16(sp)
5AE10 sw $0,0x4(sp)   other = 0         sw zero,4(sp)
5AE14 lw $7,0(sp)     readB             lw a2,0(sp)      readB
5AE18 lw $6,0x164($2) s164              lw v1,356(a0)    s164
5AE1C lw $4,0(sp)     readC             lw a0,0(sp)      readC
5AE20 sw $3,0x18($6)  store             sw v0,24(v1)     store
5AE24 lw $2,0x15C($7) deref             lw v0,348(a2)    deref
```

Both gaps are the same size in ROM and in our order-exact build (three insns
between `readA` and the `0x164` deref, one between that deref and the store), and
the whole emitted schedule is identical — only the register *names* differ.  So
the live lengths cannot be what selects ROM's assignment, and the requirement I
derived (from the *4-site* variant's behaviour, not from ROM) sent the last two
passes in the wrong direction.  The conv-10 `block_alloc` model and everything
built on it should be treated as retired for this function.

**What that leaves, as the next reasoned levers** (identical schedule + identical
live lengths ⇒ the difference is the quantity *set* or the pass-1 suggestions,
not lengths):

1. `block_alloc` runs a **suggested pass before the priority pass**.  Ours has
   exactly one suggested quantity in this block — `readC`, copy-suggested to `$4`
   by the `$4 = self` arg copy.  If ROM has a *second* suggested quantity, pass 2
   starts from a different free set and every subsequent pick shifts.  Look for a
   source shape that gives a second quantity a copy suggestion.
2. Concretely: route `&other` through a pseudo (`int **op = &other;`) so it is
   copied into `$5` instead of `ori $5,$29,4` being emitted directly — the copy
   makes the pseudo copy-suggested to `$5`.  Measured on the order-exact base
   (5 sites, no change) but **not yet on the 4-site pointer-alias base**, which is
   where the other two registers already snap.
3. The second parameter of `func_00165418` has never been varied — it is declared
   `int **` throughout.  A `void *` or struct-pointer parameter changes how
   `&other` is expanded and could add or remove the address pseudo entirely.
4. Ruled out this pass: `func_0015ADF0` is **not** a static-chain pair member
   (it is absent from the commonact candidate set), so that data-model difference
   is not the explanation.

Shapes measured this pass (all on top of the 4-site base): `other` as `slot[0]`
of a 2-element array (8 sites).  Running total across passes: fourteen.
