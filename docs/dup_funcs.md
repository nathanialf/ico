# Byte-identical func_* duplicates

Candidate list for matching sessions: every group below is two or more
functions whose `.text` bytes are bitwise identical, with at least one
member still unmatched. A single C source body that matches one will
match every other member of its group.

- Generated: 2026-05-18 (read from `baserom/baseelf.elf` + `build/ico.elf`)
- Regenerate: `nm --defined-only -S build/ico.elf > /tmp/nm.txt && python3 tools/find_dup_funcs.py > docs/dup_funcs.md.raw`
- Reproducer: `tools/find_dup_funcs.py`

## Classification key

| Tag | Meaning                                                       |
| --- | ------------------------------------------------------------- |
| **U** | Unmatched — `.s` exists in `asm/` outside `asm/matchings/`. |
| **M** | Matched-snapshot — `.s` only under `asm/matchings/`; the C body already exists in `src/`. |
| **?** | Fully matched, no asm snapshot kept.                        |

## Headline numbers

| Metric                                                | Count   |
| ----------------------------------------------------- | ------: |
| Total `func_*` symbols (from `nm` on `build/ico.elf`) | 9 997   |
| Unmatched names                                       | 4 396   |
| Matched-snapshot names                                | 2 103   |
| Byte-duplicate groups overall (size ≥ 2)              |    69   |
| Groups with ≥ 1 unmatched member                      |    29   |
| ↳ non-stub (size > 0x10)                              |    26   |
| ↳ stub (size ≤ 0x10)                                  |     3   |

**Negative result worth noting:** no unmatched duplicate has a
fully-matched twin. Every byte-twin of every unmatched function is
itself unmatched (one 12-byte exception, listed below). So this is a
"write one body, get N matches" lever, not a "copy a matched C body
across" lever.

## Quick picks

Cross-TU duplicates have the highest leverage — same logic appears in two
different translation units, so matching one folds into both as soon as
the second TU's surrounding C exists.

| Size  | Addresses                       | TUs                                                |
| ----: | ------------------------------- | -------------------------------------------------- |
| 228 B | `0011EE88` ↔ `001219A8`         | RegistPacket (active C TU) ↔ cod/01FF60 (bucket)   |
| 148 B | `0023E298` ↔ `0023E368`         | cod/13E294 ↔ cod/13E368                            |
| 120 B | `0013B7E0` ↔ `00203C40`         | cod/03B7E0 ↔ cod/103C40                            |
|  96 B | `0013C538` ↔ `0013CF80`         | cod/03C538 ↔ cod/03CF80                            |
|  68 B | `00265B28` ↔ `00266870`         | cod/165B28 ↔ cod/166870                            |
|  52 B | `0017B0D8` ↔ `00205048`         | cod/07AA04 ↔ cod/105048                            |
|  40 B | `0015F428` ↔ `0015F5D0`         | cod/05F358 ↔ cod/05F5D0                            |

The 228 B `0011EE88`/`001219A8` pair is the strongest candidate: an
active C TU (`src/RegistPacket.c`) already exists for one side, so a
match there both progresses RegistPacket and pre-positions the cod
bucket twin for instant credit once that TU starts.

## All non-stub groups (size > 0x10)

Sorted by descending size. Same-TU pairs (both members in one `asm/.s`)
typically mean two adjacent functions in the same actor; cross-TU pairs
are noted explicitly.

| Size (B) |  n | Members (addr, location)                                                                                                                |
| -------: | -: | --------------------------------------------------------------------------------------------------------------------------------------- |
|    264   |  2 | [U] `00138510` `asm/src/cod/0383F8.s` · [U] `00138618` `asm/src/cod/0383F8.s`                                                           |
|    228   |  2 | [U] `0011EE88` `asm/nonmatchings/src/RegistPacket/func_0011EE88.s` · [U] `001219A8` `asm/src/cod/01FF60.s`   ← cross-TU                  |
|    176   |  2 | [U] `0020A0A0` `asm/src/cod/109F58.s` · [U] `0020A150` `asm/src/cod/109F58.s`                                                           |
|    164   |  2 | [U] `002389C8` `asm/src/cod/137C18.s` · [U] `00238A70` `asm/src/cod/137C18.s`                                                           |
|    156   |  2 | [U] `00218BB8` `asm/src/cod/118A20.s` · [U] `00218C58` `asm/src/cod/118A20.s`                                                           |
|    156   |  2 | [U] `0022A680` `asm/src/cod/12A0A0.s` · [U] `0022A720` `asm/src/cod/12A0A0.s`                                                           |
|    148   |  2 | [U] `0023E298` `asm/src/cod/13E294.s` · [U] `0023E368` `asm/src/cod/13E368.s`   ← cross-TU                                              |
|    144   |  2 | [U] `002125D8` `asm/src/cod/1117D0.s` · [U] `00212668` `asm/src/cod/1117D0.s`                                                           |
|    144   |  2 | [U] `00219358` `asm/src/cod/118E90.s` · [U] `002193E8` `asm/src/cod/118E90.s`                                                           |
|    144   |  2 | [U] `0022B480` `asm/src/cod/12A0A0.s` · [U] `0022B510` `asm/src/cod/12A0A0.s`                                                           |
|    144   |  2 | [U] `0023A858` `asm/src/cod/139830.s` · [U] `0023A8E8` `asm/src/cod/139830.s`                                                           |
|    124   |  2 | [U] `001BC438` `asm/src/cod/0BC0B8.s` · [U] `001BC7F0` `asm/src/cod/0BC0B8.s`                                                           |
|    120   |  2 | [U] `0013B7E0` `asm/src/cod/03B7E0.s` · [U] `00203C40` `asm/src/cod/103C40.s`   ← cross-TU                                              |
|    120   |  2 | [U] `001F40D8` `asm/nonmatchings/src/weapon/func_001F40D8.s` · [U] `001F4150` `asm/nonmatchings/src/weapon/func_001F4150.s`             |
|    108   |  2 | [U] `001A6A30` `asm/src/cod/0A43F8.s` · [U] `001A6AA0` `asm/src/cod/0A43F8.s`                                                           |
|    104   |  2 | [U] `0013F1F8` `asm/src/cod/03F1F8.s` · [U] `0013F260` `asm/src/cod/03F1F8.s`                                                           |
|    100   |  2 | [U] `00258690` `asm/src/cod/158624.s` · [U] `00258998` `asm/src/cod/158624.s`                                                           |
|     96   |  2 | [U] `0013C538` `asm/src/cod/03C538.s` · [U] `0013CF80` `asm/src/cod/03CF80.s`   ← cross-TU                                              |
|     88   |  2 | [U] `0010F5D8` `asm/src/cod/00F5D4.s` · [U] `0010F710` `asm/src/cod/00F5D4.s`                                                           |
|     84   |  2 | [U] `001FC220` `asm/src/cod/0FC1A0.s` · [U] `001FC278` `asm/src/cod/0FC1A0.s`                                                           |
|     84   |  2 | [U] `00205808` `asm/src/cod/1056A4.s` · [U] `00205948` `asm/src/cod/1056A4.s`                                                           |
|     84   |  2 | [U] `00205860` `asm/src/cod/1056A4.s` · [U] `002059A0` `asm/src/cod/1056A4.s`                                                           |
|     68   |  2 | [U] `00265B28` `asm/src/cod/165B28.s` · [U] `00266870` `asm/src/cod/166870.s`   ← cross-TU                                              |
|     60   |  2 | [U] `00118F58` `asm/cod/018AB4.s`     · [U] `00118F98` `asm/cod/018AB4.s`                                                               |
|     52   |  2 | [U] `0017B0D8` `asm/cod/07AA04.s`     · [U] `00205048` `asm/cod/105048.s`       ← cross-TU                                              |
|     40   |  2 | [U] `0015F428` `asm/cod/05F358.s`     · [U] `0015F5D0` `asm/cod/05F5D0.s`       ← cross-TU                                              |

## Stub groups (size ≤ 0x10)

| Size (B) |   n | Note                                                                                       |
| -------: | --: | ------------------------------------------------------------------------------------------ |
|       12 |   2 | [U] `func_00251DD0` · **[M]** `func_00251DE0` — the only group with a matched twin. Read `src/cod/151DE0.c`; its 12-byte body should transplant to `0x251DD0`. |
|        4 | 632 | Single `nop` "functions" — almost entirely alignment padding promoted to symbols. Not target material. |
|        4 |   6 | Sequential `0x137F88`–`0x1380F0` `nop` group — probably vtable/jump-table holes.            |

## Out of scope

Strict byte-identity will miss:

- Functions that differ only in immediate operands (e.g. same shape, different constant).
- Functions that differ only in `%hi`/`%lo` relocations or `%gp_rel` offsets.
- Functions that load/store different globals through identical instruction shapes.

A natural follow-up is a **shape-normalized pass**: mask the low 16 bits
of every `lui`/`addiu`/`lw`/`sw`/`jal`/`j` before hashing. That would
surface the "macro expansion" tier — funcs that differ only in which
constant or global they touch. Not yet implemented.

## Big stub clusters already cleared

For context: an earlier prefix of this analysis found a 77-member cluster
of identical 16-byte stubs, a 54-member cluster of 8-byte stubs, and an
8-member cluster — those are now **all matched** (every member sits in
`asm/matchings/`). They no longer appear in the actionable list, which
is good — it means previous matching sweeps already covered the trivial
stub buckets.
