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
| `fumi`     | **uncertain**              | —                                | character/object action: boyact, girl_act, commonact, enemy_act | LOW        |

Functional / shared dirs (not a single person): `common`, `script`, `sound`,
`ios` (cdvd/mcard/pad I/O), `isys` (gobj/object-system infra).

## Caveats — read before relying on this

- **Fumito Ueda is NOT credited as a programmer.** He is Director / Game Design /
  Planner. The dir name `fumi` likely references his given name (**Fumi**to, who
  was famously hands-on with the boy/Yorda character animation that lives in
  `fumi/`), but the *formal* "Characters & Objects Program" credit goes to
  **Jinji Horagai**. So `fumi`'s authorship is the one unresolved mapping — do not
  assert "fumi = Ueda the programmer."
- Raw `strings` hits for "seki" are dominated by the game word 石 *seki* = "stone"
  (`sekizo` = stone statue, `sekika` = petrification), **not** the name. The clean
  source is the `{R}`-formatted credit block, not a substring count.

## What this does and does NOT tell us about the build

- **Build flags are uniform `-O2` across all modules.** An earlier hypothesis that
  `ito/mpeg` was a distinct `-O1` module was **refuted**: `viBufFlush` (a third
  ito/mpeg TU) matches at `-O2` (its non-ascending store order comes from `-O2`
  scheduling once a return-value `addu` interleaves — `-O2` is shape-sensitive,
  not "always ascending"). So the modules differ by **author/style, not compiler
  flags**.
- The lone holdout, `voBufIncCount` (ito/mpeg/mv_vobuf), is reproduced as Ito's
  **hand-written asm** (a trivial counter-reset with an unfilled `jr` delay — a
  human-scheduling signature a -O2 compiler won't produce). See
  `tough_nuts/voBufIncCount/notes.md`.

## Practical use for matching

When you pick up an unmatched function, look at its dir's *already-matched*
siblings for the author's idioms before writing C:

- **seki** — GS/DMA packet building, VU0 (`VU0_LSV`/`VU0_V2OP`) and `QCOPY16`.
- **sugipon** — matrix/quaternion/motion-manager conventions.
- **omori** — camera/brain/AI structures.
- **ito** — `a0->0x15C->0x7F0` deref chains, IPU/movie idioms, occasional hand-asm.
- **fumi** — `a0->0x164->0x678` action-object deref chains, character state machines.
