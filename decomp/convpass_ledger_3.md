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
