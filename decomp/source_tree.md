# Original ICO source tree (recovered from `__FILE__` strings)

Recovered by scanning `.rodata` of `baserom/baseelf.elf` for path-shaped
strings emitted by the SCE assert macro
(`assertion "%s" failed: file "%s", line %d`). Each path is a literal
`__FILE__` argument that survived stripping because it lives in the
function's emitted rodata, not in `.comment`/`.mdebug`.

**Confidence:** high — these are not guesses. Each filename below is a
verbatim string the compiler emitted into the binary.

**What this is good for:**
- Naming `cod/<offset>` subsegments once they're matched (assertions
  embed `__FILE__`, so a matched function with `assertion "%s" failed`
  in its rodata reveals which TU it belongs to).
- Splitting `cod` into per-file subsegments in `config/ico.us.yaml`
  once we identify enough function/file mappings.
- Sanity-checking that the directory layout we recreate under `src/`
  reflects the original tree.

**What this is *not*:**
- A complete list of files. Files without an `assert(...)` call won't
  appear here (probably most leaf utilities). Header-only files mostly
  don't appear. Inline-included `.c.inc` files appear under their
  including TU.
- A list of *function names*. Only file boundaries.

## Directory layout

Five directories carry source under `__FILE__`. Hyphenated `src/<group>-<file>.c`
names indicate logical subsystems (act, camera, mail) flattened into
filenames rather than subdirectories.

### `src/` — game code (83 files)

```
src/Basic.c              src/DObj.c              src/PObj.c
src/BgAnimation.c        src/StageAnimation.c    src/multiBgaManager.c
src/DisplayList.c        src/DmaPacket.c         src/Packet.c
src/RegistPacket.c       src/Primitive.c         src/Light.c
src/Texture.c            src/layout_texture.c    src/FileManager.c
src/EnemyInit.c          src/charFileManager.c   src/delayFreeManager.c
src/geometryManager.c    src/lodManager.c        src/sceneManager.c
src/motionManager.c      src/motionManager2.c    src/motionOrientManager.c
src/motionViewer.c       src/streamMotionManager.c
src/clothAnimation.c     src/clothTest.c
src/particleEffect.c     src/particleLayout.c
src/a_p_1.c              src/act.c               src/act_bird.c
src/act-env.c            src/act-game.c          src/act-parallel-control.c
src/attackCheckBoundary.c src/attackhit.c
src/box.c                src/boy.c               src/boyact.c
src/cage.c               src/camera-editor.c     src/camera-ico2.c
src/candle.c             src/chain.c
src/commonact.c          src/debug.c
src/ebrain.c             src/enemy.c             src/enemy_act.c
src/enemyParts.c         src/fieldCollision.c    src/fightSound.c
src/flag.c               src/generator.c
src/girl.c               src/girlForceField.c    src/girl_act.c
src/girl_brain_main.c    src/girl_brain_attract.c
src/icoMisc.c            src/item.c              src/itou_boss.c
src/jimaku.c             src/kanban.c
src/mail-add-data.c
src/moveColTest.c
src/pool.c               src/queen.c
src/rope.c               src/rotObject.c
src/spider.c             src/spiderGroupManager.c
src/staffroll.c          src/stormTest.c
src/sugiTree.c           src/switch.c            src/torch.c
src/way_tool.c           src/way_util.c
src/weapon.c             src/worm.c
```

`girl_brain_main.c` includes `girl_brain_main.c.inc`, and
`girl_brain_attract.c` includes `girl_brain_attract.c.inc` — the `.inc`
forms appear as bare strings near the parent and are inline-included
fragments, not standalone TUs.

### `ios/` — I/O system / OS abstraction (7 files)

```
ios/cdvd.c       ios/inflate.c    ios/mblock.c     ios/memory.c
ios/message.c    ios/pad.c        ios/thread.c
```

These wrap the SDK libraries (sceCdvd, sceMc, scePad, sceSif). Some
debug strings tie them to specific subsystems:
- `ios/pad.c` → "PRESSURE SENSE mode", scePadPortOpen
- `ios/thread.c` → "thread table over flow", "thr:can't create thread"
- `ios/cdvd.c` → "wait insert ico disk", "iosCdvdMgrSearchFile"
- `ios/memory.c` → "iosmalloc()", "mem:illegal free area pointer"
- `ios/mblock.c` → memory-card block manager (sees "boy_blk.ico",
  "icon.sys", "BASCUS-97113ico")
- `ios/message.c` → "msg:null message queue" — IPC / message queues
- `ios/inflate.c` → zlib inflate ("incomplete literal tree") — likely
  used to decompress disc-resident assets

### `isys/` — interactive-system / GObj framework (2 files)

```
isys/gobj.c          isys/gobj_process.c
```

GObj is a per-frame game-object scheduler. Debug strings: "isys:null
GObj", "isys:not enough memory for GObj", "gobj dl added",
"GObjLinkDL". The `GOBJ_VAL(gop)` assertion macro found near
`mail-add-data.c` confirms top-level game logic builds on this framework.

### `sound/` — audio (2 files)

```
sound/adpcm_init.c   sound/s_init.c
```

ADPCM playback init + sound subsystem init. References "AdpcmIopBuffAlloc",
"iop sound alloced", "se open", "bgm". IOP-side audio code lives
elsewhere (separate ELF, not in this binary).

### `include/` — public headers (2 confirmed)

```
include/charFileName.h    include/mv_defs.h
```

Almost certainly more headers exist (any header without an `assert()`
won't surface). `charFileName.h` pairs with `src/charFileManager.c` and
`mv_defs.h` is referenced 9× — likely a motion/animation defs header.

## Inferred subsystem groupings

Useful for naming once we start splitting `cod` into per-file subsegments:

- **Player AI:** `boy.c`, `boyact.c`, `girl.c`, `girl_act.c`,
  `girl_brain_main.c`, `girl_brain_attract.c`, `girlForceField.c`,
  `warpGirl.c` (no path prefix recovered)
- **Enemy AI:** `enemy.c`, `enemy_act.c`, `enemyParts.c`, `EnemyInit.c`,
  `ebrain.c`, `itou_boss.c`, `queen.c`, `spider.c`,
  `spiderGroupManager.c`, `worm.c`
- **World objects:** `box.c`, `cage.c`, `candle.c`, `chain.c`, `flag.c`,
  `item.c`, `kanban.c`, `rope.c`, `rotObject.c`, `switch.c`,
  `sugiTree.c`, `torch.c`, `weapon.c`
- **Combat:** `attackhit.c`, `attackCheckBoundary.c`, `fightSound.c`,
  `fieldCollision.c`, `moveColTest.c`
- **Animation:** `BgAnimation.c`, `StageAnimation.c`, `motionManager.c`,
  `motionManager2.c`, `motionOrientManager.c`, `motionViewer.c`,
  `streamMotionManager.c`, `multiBgaManager.c`, `clothAnimation.c`,
  `clothTest.c`, `particleEffect.c`, `particleLayout.c`
- **Render pipeline (PS2-specific):** `DObj.c`, `PObj.c`,
  `DisplayList.c`, `DmaPacket.c`, `Packet.c`, `RegistPacket.c`,
  `Light.c`, `Texture.c`, `Primitive.c`, `Basic.c`, `layout_texture.c`,
  `geometryManager.c`, `lodManager.c`
- **Core/system:** `FileManager.c`, `delayFreeManager.c`, `pool.c`,
  `sceneManager.c`, `debug.c`, `jimaku.c` (subtitles), `staffroll.c`,
  `icoMisc.c`, `commonact.c`
- **Generators / scripting:** `generator.c`, `act.c`, `act-env.c`,
  `act-game.c`, `act-parallel-control.c`, `mail-add-data.c`
- **Misc:** `a_p_1.c` (?), `act_bird.c`, `way_tool.c`, `way_util.c`,
  `stormTest.c`

## Bonus finds

- **`warpGirl.c`** has no recovered directory prefix — likely lives
  under `src/` but was referenced from a hand-written debug `printf`
  (`"warpGirl.c:..."`) rather than `__FILE__`, so the path didn't
  travel with it.
- **`ico2Data/`** — host-filesystem data directory used by
  `src/camera-editor.c` (debug-only camera path saver). Implies a
  development-host workflow distinct from the disc-resident assets.
- **`BASCUS-97113ico`** — memory-card folder name (PS2 retail product
  code prefix `BASCUS` + product `97113ico`). Hardcoded in `ios/mblock.c`.
- **`boy_blk.ico`** — character-data filename, presumably loaded from
  the disc through `src/charFileManager.c` / `include/charFileName.h`.
- **`sekika_boy`**, **`queen_ball_scr`** — Japanese tag-style strings
  near `warpGirl.c`. Likely warp-target identifiers used in the debug
  stage select. (`sekika` 石化 = "petrification".)
- **PsII library tags** in `.data`: `libcdvd 2240`, `libdma 2200`,
  `libipu 2200`, `libmc 2240`, `libmpeg 2200`, `libpad 2200`,
  `libpkt 2200`. Pins SDK version: 2200/2240 era (PS2 SDK ~2001).

## Workflow (analyzers, snapshot, isolation from matching)

The TU-mapping analyzers read asm from `decomp/asm_snapshot/`, never
live `asm/`. The active matching pipeline (auto-permuter / batch-claim
loops) periodically nukes and regenerates `asm/cod/*.s` via
`rm asm/cod/*.s + make setup`; analyzers reading live `asm/` would
produce flaky output. The snapshot insulates them.

Pipeline (run in order; each step is idempotent):

```sh
# When matching is in a quiet window — `find asm/cod -name '*.s' | wc -l`
# is non-zero — capture a stable copy of the asm tree:
.venv/bin/python tools/snapshot_asm.py

# Build the supplementary signal artifacts (each reads the snapshot):
.venv/bin/python tools/find_callgraph.py    # → decomp/callgraph.json
.venv/bin/python tools/find_vtables.py      # → decomp/vtables.json
.venv/bin/python tools/find_boundaries.py   # → decomp/boundaries.json

# Render the TU map (consumes all of the above):
.venv/bin/python tools/identify_tus.py      # → decomp/tu_map.md
```

The snapshot directory (`decomp/asm_snapshot/`) is gitignored.
Re-running analyzers without re-snapshotting is safe — they always see
the same input. Re-snapshot only when you want fresh asm in the map.

## Skeleton tree

The recovered layout is materialized as empty placeholders under
`decomp/source_tree/`, one file per recovered TU plus a `README.md`
per directory describing its subsystem. Generated by
`tools/build_source_tree.py` from `.rodata`; idempotent — re-run after
any further `__FILE__` recovery work.

```sh
.venv/bin/python tools/build_source_tree.py
```

Each placeholder is a single-line C comment recording the original
path and the `.rodata` vma where its `__FILE__` literal lives. Example:

```c
/* placeholder: src/boy.c — __FILE__ anchor at .rodata 0x00618838 */
```

The build does not consume `decomp/source_tree/`. It exists purely as
a planning artifact and a checklist of TUs to claim.

## Mechanical TU mapping (the payoff)

The C standard guarantees `__FILE__` resolves to the same string
literal everywhere within a single TU, and the compiler emits exactly
one copy of it in that TU's `.rodata`. Every assert in a TU loads the
same address. So:

1. The address of `"src/boy.c"` in the final ELF is the **anchor for
   boy.c**.
2. Any `.text` function whose code references that address (via
   `lui+addiu`, the `la` macro, or `%gp_rel(SYM)($gp)` if it landed in
   `.sdata`) belongs to `boy.c`.
3. Adjacent same-anchor functions form a contiguous run of `.text`
   from that TU. Functions with no assert get bracketed by their
   neighbors.

Concrete recipe once we want to act on this:

- For each function in `asm/cod/*.s`, scan instructions for
  `lui $X, %hi(VMA) / addiu $X, %lo(VMA)` (or `gp_rel`) where `VMA`
  is one of the anchors in the skeleton tree.
- Tag each function with the matching filename.
- Sort tagged functions by `.text` address; identify TU boundaries at
  the gaps where the tag changes.
- Untagged functions between two same-tagged anchors belong to that
  TU (the linker concatenates `.o`s in input order).
- Where adjacent TUs disagree, the boundary is somewhere in the gap
  between them — usually at a function boundary, occasionally
  refinable via secondary signals (function-pointer tables in `.data`
  that group same-TU functions, alignment padding, jumptables that
  don't cross TU boundaries).

## Caveats

- TUs without any `assert()` produce no anchor. They surface only as
  the gaps between identified TUs in `.text` ordering.
- Inlined functions assert with the *inliner's* `__FILE__`; helpers
  that got inlined into a different TU are tagged to the inliner.
- `<file>.c.inc` paths (e.g. `girl_brain_main.c.inc`) are inline-
  included fragments, not standalone TUs. They appear near the parent
  but don't get their own placeholder.
- `warpGirl.c` lacks a directory prefix because it was referenced via
  a hand-written `printf("warpGirl.c:...")` rather than `__FILE__`. It
  doesn't appear in the skeleton until we figure out where it lives.
  Likely `src/`.
