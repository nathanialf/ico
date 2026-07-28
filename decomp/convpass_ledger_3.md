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
