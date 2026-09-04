# Source layout — per-programmer directories

ICO's source tree is organized **by programmer**, the conventional Japanese-
studio layout where each engineer owns a subsystem. The top-level dirs map to
people; this is useful for matching because **idioms are consistent within one
author's tree** — knowing whose dir a function lives in predicts its struct
offsets, accessor shape, control-flow style, and macro usage.

## Provenance (IP-clean)

This mapping is derived from **public information** — the game's published staff
roll (its ending credits) — cross-referenced with the contents of each directory
and with per-developer asset paths in the ELF (`camdata/<name>.gcm`,
`object/sdf/<name>_test/`). That is the sanctioned "treat published RE / public
credits as references" path (see `docs/LEGAL.md`, CLAUDE.md). **No extracted
credit-string data or any other disc data is committed** — only this analysis.

## Mapping

| dir        | programmer (credit)        | credited role(s)                 | dir contents (corroboration)                                  | confidence |
|------------|----------------------------|----------------------------------|---------------------------------------------------------------|------------|
| `seki`     | Takuya Seki                | Tools / Visual Program           | GS/draw: Light, GsBase, GifPacket, Primitive, Texture, DmaPacket | high     |
| `sugipon`  | Hajime Sugiyama ("Sugipon")| Draw Engine / YORDA A.I. Program | matrixDrive, motionManager, geometryManager, quaternion, a_p_1  | high     |
| `omori`    | Shotaro Omori              | Motion System Program            | camera-*, brain, attackhit, fightSound, generator               | high     |
| `ito`      | Toshihiro Ito              | Scripting                        | queen, **itou_boss/itou_sub/itou_gflag**, mpeg (IPU movie layer) | high     |
| `fumi`     | Fumiaki Hara?              | System Program                   | character/object action: boyact, girl_act, commonact, enemy_act | low        |

Functional / shared dirs (not a single person): `common`, `script`, `sound`,
`ios` (cdvd/mcard/pad I/O), `isys` (gobj/object-system infra).

## Caveats — read before relying on this

- The public-credit candidate for `fumi` is **Fumiaki Hara**, who MobyGames lists
  under System Program for the PlayStation 2 credits:
  <https://www.mobygames.com/game/5158/ico/credits/ps2/>.
  Treat this as a plausible name match, not proof: the `fumi/` directory is
  character/object action-heavy, while Hara's public credit is system-level.
- Raw `strings` hits for "seki" are dominated by the game word 石 *seki* = "stone"
  (`sekizo` = stone statue, `sekika` = petrification), **not** the name. The clean
  source is the `{R}`-formatted credit block, not a substring count.

## Retail vs prototype tree shape

The per-programmer layout above describes the **prototype** (the `aug6`
branch). The two retail builds do **not** preserve those directory boundaries:
their source tree is a collapsed/flattened version of the prototype, with the
per-programmer folders merged, so the `seki`/`sugipon`/`omori`/`ito`/`fumi`
split is not legible from the retail TU layout itself.

That no longer costs anything on `main`. The PAL disc ships its own build
listing, so PAL's TU boundaries, file names and per-file function order are
read directly from it (`tools/gen_pal_symbol_addrs.py`,
`tools/gen_pal_source_tree.py` → local `decomp/pal_source_tree.md`) rather than
inferred. Use the author map below for **idioms**, not for boundaries: the
listing supplies the boundaries.

The historical strategy note ("match the prototype first, back-port to
retail") is spent — both port passes are complete (`decomp/port_ledger_pal.md`,
`decomp/port_ledger_pal_aug6.md`) and the port drivers are retired.

## What this does and does NOT tell us about the build

- **Build flags are uniform `-O2` across all modules.** An earlier hypothesis that
  `ito/mpeg` was a distinct `-O1` module was **refuted**: `viBufFlush` (a third
  ito/mpeg TU) matches at `-O2` (its non-ascending store order comes from `-O2`
  scheduling once a return-value `addu` interleaves — `-O2` is shape-sensitive,
  not "always ascending"). So the modules differ by **author/style, not compiler
  flags**.
- The lone holdout, `voBufIncCount` (`ito/mpeg/mv_vobuf`), is reproduced as
  Ito's **hand-written asm** (a trivial counter-reset with an unfilled `jr`
  delay — a human-scheduling signature a -O2 compiler won't produce).

## Practical use for matching

When you pick up an unmatched function, look at its dir's *already-matched*
siblings for the author's idioms before writing C:

- **seki** — GS/DMA packet building, VU0 (`VU0_LSV`/`VU0_V2OP`) and `QCOPY16`.
- **sugipon** — matrix/quaternion/motion-manager conventions.
- **omori** — camera/brain/AI structures.
- **ito** — IPU/movie idioms, occasional hand-asm.
- **fumi** — character/action state machines (heaviest user of the `0x164`
  actor-state field, but the field itself is engine-wide — see below).

**Deref chains are engine-wide, NOT author idioms.** Two object slots recur
across the whole codebase; attribute the *subsystem* to an author, never the
chain:
- `a0->0x15C->0x7F0` — the DObj→geometry-object accessor, ~25 TUs across
  sugipon/omori/ito/fumi (weapon, torch, boy, rope, enemy, box, spider, chain,
  ebrain, queen, …). Typed form: `GOBJ_SUB(o)->p_7F0->...` (`include/ico/types.h`:
  `GObj`, `Sub15C`=DObj@0x15C, `Obj7F0`=geometry@0x7F0).
- `a0->0x164->...` — an actor/action-state object, 20 TUs across
  sugipon/fumi/omori/script (fumi owns 12 of them but it is not fumi-only).
  `0x164` is not yet typed in `GObj`; recovering it is Item C.

Both `0x7F0` and `0x164` *targets* are POLYMORPHIC per object type — the same
offset is a pointer in one object and a packed `unsigned short` in another
(cage's `0x7F0+0x20` is a `GeoNode*`; spider's is a `ushort`). Only the parent
pointer (`Sub15C.p_7F0`, `GObj+0x164`) is a shared fact; type each TU's view
LOCALLY (as `ropeFix.c` does with `RopeA/RopeB/RopeC`), not as one shared field
map.
