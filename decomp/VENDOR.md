# Vendor code policy — what it is, how it is accounted, what may be used to match it

*Written 2026-07-28 on `retail-v2`. Before this file there was no written
vendor policy anywhere in either tree — only a stale YAML comment
(`config/ico.aug6.yaml:99`) and two fdlibm-specific asides
(`decomp/NOTES.md:390,403`, `decomp/COOKBOOK.md:855`). Treat this file as
the canonical statement.*

---

## 0. Forbidden inputs — restated in full, on purpose

`docs/LEGAL.md` is the project's legal document, but it is **untracked in
git and physically absent from this branch's worktree** (removed from the
index by commit `ec04c17f`, "Untrack cross-target knowledge docs"). Anyone
working the retail target in isolation therefore has no legal doc in front
of them, on a question that is *entirely* about permitted inputs. So the
operative rules are restated here rather than cited:

**Never usable as an input to this project, even indirectly:**

- Leaked SDKs — Sony Pro-DG, internal Sony tools, debug PS2 firmware.
- Leaked source code from any party.
- Leaked *source* or leaked *SDKs* of ICO or related Team Ico titles,
  full stop, regardless of how obtained.
- Paid asset extractors that bundle game data.
- The disc image, the extracted ELF, or asset bytes, committed in whole or
  in part, in any encoding.
- Symbol / MAP / debug *tables* copied verbatim or in bulk out of the
  binary, the disc, or any leaked development material.

**Permitted as references, on academic-paper terms** (read, internalize,
re-derive from the disassembly; never paste code, comments, or symbol
names verbatim):

- Published public RE writeups: conference talks, blog posts, articles,
  public Ghidra projects with explicit non-leaked provenance, academic
  papers on the EE/R5900.
- Open community SDKs — the [`ps2dev`](https://github.com/ps2dev) family
  (ps2sdk, ps2toolchain, ps2-packer), themselves clean-room and openly
  licensed. Vendoring goes under `lib/<name>/` with a `PROVENANCE.md`.
- Individual *facts* observed by reverse-engineering a copy you legally
  own: function/symbol names, struct offsets, strides, `__FILE__` strings.

If you have ever read forbidden material, disclose it on your first PR.

---

## 1. What "vendor" means here

Vendor code is **`.text` that came out of a pre-built `.a` archive at link
time, not out of an ICO translation unit.** The ICO game code itself is
`ico2000.a`; everything else the linker pulled in — crt0, the SCE SDK
libraries, newlib, libgcc — is vendor.

In link order the vendor archives **bracket** the game code, so vendor
occupies exactly two address runs in the retail ELF:

| Run | Span (VMA) | Funcs | Bytes | Contents |
|-----|-----------|-------|-------|----------|
| head | `0x00100000`–`0x00101C80` | 180 | 7,296 | crt0 + libkernl (klib / initsys / intr / thread / kprintf / diei / deci2) |
| tail | `0x002418A0`–`0x0026F5D4` | 765 | 187,700 | the library tail, broken down below |
| | | **945** | **194,996** | **12.96 % of `.text`** |

(Byte figures measured by `tools/progress_tree.py` on 2026-07-28; the head
run includes `_start`, see §5.)

### Tail breakdown

Attributed by reloc-normalized instruction hashing against the Aug-6-2001
prototype twin, then mapped onto `MAIN.MAP`'s member list. **This mapping is
not tracked per-function anywhere in the repo** — it is recorded here as a
research result, and the dashboard deliberately does not pretend to a
per-function archive attribution it does not have.

| Archive | Funcs | | Archive | Funcs |
|---------|------:|-|---------|------:|
| libkernl | 138 | | libcdvd | 29 |
| libmpeg | 127 | | libpad | 26 |
| libc (newlib) | 111 | | libm (fdlibm) | 21 |
| libsndn2 | 97 | | libdma | 18 |
| libgcc | 40 | | libmc | 14 |
| libvu0 | 39 | | libipu | 12 |
| libgraph | 30 | | libpkt | 9 |
| | | | libscedemo | 5 |

Plus `ico2000.a(vobj.o)` (~400 B of *real game code* — see §5) and 52
functions with no aug6 twin (§7, queue group V4).

(The `945` / `194,996` figures in the table above are what
`tools/progress_tree.py` counts and are 3 functions / 688 B low — see the
denominator caveat at the top of §7.)

### How the two runs are represented

- `config/ico.us.yaml:105` — `[0x000000, asm, src/cod/000000]`, the head blob.
- `config/ico.us.yaml:322` — `[0x1418A0, asm, src/cod/1418A0]`, the tail blob.
  (yaml offsets are ROM offsets = VMA − 0x100000.)
- `config/symbol_addrs.us.txt` — every vendor function carries a
  `// (vendor)` note, emitted under `// ---- (vendor)` section headers at
  lines 245 and 5268 by `tools/gen_us_symbol_addrs.py`
  (`VENDOR = "(vendor)"`, and the cut logic in `cut_vendor_tail()`).

---

## 2. The de-facto policy: vendor code **is** matched, clean-room

`config/ico.aug6.yaml:99` still says *"crt0 + libkernl (vendor, not
matched)"*. **That comment is stale.** The `main` (aug6 prototype) branch
has already landed **478 vendor functions / 46,808 bytes**, spanning every
archive in the table above.

Those matches live inside `common/src/PObj.c`, because aug6's final `.text`
subsegment is an uncarved `common/src/PObj` blob that swallows the whole
vendor tail (`config/ico.aug6.yaml:317`). Measured on the aug6 tree, that
blob is 484/775 functions and 47,400/190,692 bytes matched; subtract the
handful of genuine `PObj.o` functions at its head and the vendor share is
the 478 / 46,808 above.

So aug6's representation **attributes ~46 KB of SDK and libc code to a game
TU**. Retail's two `src/cod/*` blobs keep vendor separate from every game
TU. **Retail's representation is the more honest one** and should be
preserved: when aug6's vendor matches are ported over here, they belong in
vendor-named TUs carved out of `src/cod/*`, not folded into `src/PObj.c`.

---

## 3. The legal split — the operative part

Vendor is not one legal category. It is two, and they have opposite rules.

### 3a. Public, legitimately obtainable source — ≈ 61 KB

`libgcc`, `libm`, `libc`. Upstream for all three is public and freely
redistributable:

- **libgcc** — GPL with the runtime exception. The matching compiler is
  settled: `ee-gcc 2.9-991111-01`, a Sony fork of GCC 2.9 dated 1999-11-11
  (`decomp/NOTES.md` §"Compiler fingerprint (resolved)";
  `tools/compile_c.sh:19` points at `tools/cc/ee-gcc2.9-991111`). A GCC
  2.95-era base has already been fetched for other work.
- **libm** — Sun's fdlibm, reached via newlib. Public domain. This is
  already the sanctioned path in this repo: `decomp/COOKBOOK.md` §7.3 and
  `include/math_private.h` re-derive `GET_FLOAT_WORD` / `SET_FLOAT_WORD`
  "clean-room from the PUBLIC-DOMAIN fdlibm reference (freely published;
  treat like a public paper — NOT the proprietary PS2 SDK or any leaked
  source)". `decomp/NOTES.md:403` records the same.
- **libc** — newlib, BSD-style licence.

**Method for this half:** obtain the upstream source, compile it with the
identified compiler and flags, diff against the ROM asm, and adjust. This is
ordinary matching work with a legitimate reference implementation available.
It is *not* a licence to paste: the committed C must still be ours, and
upstream files that are vendored wholesale go under `lib/<name>/` with a
`PROVENANCE.md` per `docs/LEGAL.md`.

### 3b. Proprietary SCE SDK — ≈ 99 KB

`libkernl`, `libgraph`, `libmpeg`, `libsndn2`, `libcdvd`, `libpad`,
`libmc`, `libipu`, `libvu0`, `libdma`, `libpkt`, `libscedemo`, and `crt0`.

**No SDK source may be used. Ever.** Sony Pro-DG and Sony internal tools are
named explicitly in the forbidden-inputs list (§0). There is no legitimate
public source for these libraries. They are matched **clean-room from the
disassembly only**.

`ps2sdk` is permitted as a *naming and structural* reference — it is open,
clean-room, community work — but it is **a different implementation and must
never be used as a byte oracle.** Do not try to make ps2sdk code assemble to
the ROM's bytes; re-derive from the disassembly and let ps2sdk inform naming
and API shape only. The existing use of it in this repo is exactly that:
`include/syscall.h`'s `SYSCALL_WRAPPER(name, num)` is "modeled on ps2sdk's
`ee/kernel/src/kernel.S` `SYSCALL_SPECIAL` macro" (`decomp/NOTES.md:390`).

**The cheap exception:** `libkernl(klib.o)`'s ~136 syscall stubs are about
four instructions each and are already covered by that macro. They are the
one bulk-matchable region of the proprietary half.

---

## 4. Why this changes no bytes, and what it does change

These bytes are **already inside the SHA-1 gate.** Both `src/cod/*` blobs
are `asm` subsegments: splat emits the ROM's own instructions, the assembler
reproduces them, and the link is byte-identical today. Matching vendor code
adds **zero correctness** — it moves bytes from *passthrough asm* to
*decompiled C*.

What it does change is the ceiling. Genuine vendor is **12.96 % of `.text`**,
so a branch that refuses to touch vendor code caps out at **≈ 87 %**.
That is the whole argument for doing it, and it should be weighed against
the fact that ~99 KB of it (§3b) is proprietary-clean-room work with no
reference implementation, which is the slowest kind of matching there is.

---

## 5. Two things sitting on the wrong side of the cut — documented, not reclassified

**`_start` (`0x00100008`).** The real ELF entry point (confirmed via
`readelf -h`). It sits *inside* the crt0 head run, 8 bytes past
`func_00100000`. As of 2026-07-28 it carries a `// (vendor)` note in
`config/symbol_addrs.us.txt:2` so the dashboard stops counting it as a
note-less symbol. It is crt0, i.e. §3b proprietary — not game code, and not
something to match casually.

**`ico2000.a(vobj.o)` — ~400 B of real game code on the vendor side.** The
symbol generator's own docstring admits this
(`tools/gen_us_symbol_addrs.py`, `cut_vendor_tail()`): the vendor cut is
placed at the last retail function with positive game-code evidence (its own
`__FILE__` anchor, or a twin carrying a TRFILE-derived name), and `vobj.o` is
the one `ico2000.a` member with neither. So it falls on the vendor side.
The docstring's words: *"Flagged here, not silently claimed."* Same posture
here — it is game code, it is counted as vendor, and nobody should
re-attribute it until there is evidence to place it, not a hunch.

---

## 6. How the dashboard accounts for it

`tools/progress_tree.py` reads the `// (vendor)` notes and groups those
functions under a **`vendor`** node, split into the two address runs of §1,
carrying this note:

> Library archive members linked from pre-built .a files (crt0, SCE SDK,
> newlib/libgcc) — not ICO source. These bytes are already inside the SHA-1
> gate, satisfied by assembled ROM asm.

Related accounting rules the same script now enforces:

- **`(unassigned)` is a bug bucket, not a category.** Before 2026-07-28 any
  symbol without a `// <path>.c` note fell through to `vendor` and was
  displayed as `(unassigned)` — a label that appears nowhere in the repo's
  data. 78 symbols were landing there, of which 72 were game code with a
  merely-missing note (now resolved from the `c` subsegment spans in
  `config/ico.us.yaml`), 5 were the VU1 microprograms, and 1 was `_start`.
  A symbol with neither a TU note nor a `(vendor)` note now lands in an
  explicit `(unassigned)` group that should always be empty.
- **`.vutext` is counted separately from `.text`.** The five VU1
  microprograms are `hasm` subsegments in a different ELF section
  (`config/ico.us.yaml:325-329`); `tools/progress.py` has always reported
  `.vutext` 100 % matched. They now get their own `.vutext` group so their
  20,704 bytes cannot inflate a `.text` roll-up. `totals.sections` reports
  both sections; `totals.matched_bytes` / `total_bytes` remain `.text` only.

---

## 7. Status — the aug6 vendor port (landed 2026-07-28)

**▶ The 427 unmatched vendor functions are enumerated and queued in
`decomp/convpass_ledger_3.md`, section "Vendor queue — the 427 unmatched
vendor functions" (groups V0–V6), and are ranked against the game-code
targets in that file's "Recommended order for a conv-10". That is the
standing queue; this section is the status summary that feeds it.**

`521 / 945` vendor functions and `34,144 / 194,996` bytes (17.51 %) are
decompiled. `.text` overall moved `14.49 % -> 16.81 %` (217,992 -> 252,996 B).

**Caveat on the denominator (found 2026-07-29).** `945` is what
`tools/progress_tree.py` counts, and it is 3 low. `func_00246B78`,
`func_002658B8` and `func_00268F28` are real functions — splat emits a `.s`
for each and the carved TUs `INCLUDE_ASM` them — but they are **missing from
`config/symbol_addrs.us.txt`**, so the dashboard never sees them. The honest
figures are **948 functions / 195,684 B, 521 matched, 427 unmatched /
161,540 B**. Fixing the symbol table is a queue item (see the ledger's
"Reconciliation" heading), deliberately not done in the docs-only pass that
found it.

### Representation

Both blobs are carved (`config/ico.us.yaml`), 9 `c` TUs under `src/cod/`:

| TU | funcs | bytes |
|---|---|---|
| `vendor_100110` (head, syscall leaves) | 140/151 | 2,240/2,944 |
| `vendor_2418A0` | 60/96 | 3,696/15,136 |
| `vendor_2453C0` | 46/96 | 3,688/22,280 |
| `vendor_24AAC8` | 37/96 | 2,824/16,144 |
| `vendor_24E9D8` | 58/96 | 4,504/17,232 |
| `vendor_252D28` | 38/96 | 3,592/24,472 |
| `vendor_258CC0` | 61/96 | 6,048/21,800 |
| `vendor_25E1E8` | 39/96 | 3,796/34,512 |
| `vendor_2668B8` | 42/92 | 3,756/36,032 |

Boundaries are 8-byte-aligned function starts — every `.text` object in this
link has alignment 8, so an unaligned split inserts pad and breaks the SHA-1.
Three spans stay `asm` on purpose: `0x00100000-0x00100110` (crt0 / `_start`),
`0x00100C90-0x00101C80` (the rest of libkernl), and `0x0026F578-0x0026F5E0`
(the last vendor function *plus* the 12 bytes of inter-section `.text` pad —
splat puts the pad inside that object and no C TU can emit it, so matching
that one 104-byte function would cost the pad).

### Correspondence — there is no single aug6->retail delta

(A "+0x16C8 constant delta" was in circulation when this port started. It is
wrong; it is not written anywhere in this file, and it should not be.)

Order-preserving alignment of reloc-normalized instruction streams (aug6's
own splat `.s` for `common/src/PObj` against the retail words lifted from
`baseelf.rom`) pairs **716 of 765** tail functions across **three** deltas:
`+0x3C70` (474), `+0x3AE0` (208), `+0x3B00` (34). 49 have no twin at all.
The pairing is handed to `tools/port_from_aug6.py` via its existing
`.port_cache/name_alias.json` hook, so vendor bodies get the same lockstep
reloc-slot rebinding and per-function gate as every other Phase-4 port.

Of the 455 pairs whose aug6 twin carried a matched baseline `.s`, the port's
`scan` kept **403** and dropped 52. So the portable population was 403, and
371 + 10 hand-recovered = 381 landed; one more (`func_0026F578`) is portable
but blocked by the pad above.

**Correction (2026-07-29): the 52 dropped pairs are not stale.** This section
originally said they were "stale `matchings/*.s` for functions aug6 has since
reverted to `INCLUDE_ASM`". Re-checked at the pinned aug6 commit
`3a5ab90e34bb41993cd70087d46366db870571bd`, that is false: all 716 aliased
pairs split cleanly into 455 (matched `.s` present *and* a body in
`common/src/PObj.c`) and 261 (`INCLUDE_ASM` *and* no `.s`) — zero stale.
The 52 are functions aug6 **matched as bare `__asm__` blocks** (VU0
macro-mode, MMI, privileged COP0/TLB/cache, EE syscall stubs), and
`tools/port_from_aug6.py:410-419` only indexes *C* definitions, so it did not
see them and labelled the drop "stale". They are the most tractable group in
the whole vendor queue (group **V2**, 52 funcs / 7,324 B, twelve of them 4
insns) — a finished byte-matching body already exists upstream for every one.

### What is left, and why

Counts below are the reconciled ones (427 total, from the 948-function
denominator). Each group is enumerated **by name, with sizes** in the
`decomp/convpass_ledger_3.md` vendor queue; the group tags are that queue's.

- **V1 — 21 genuine reverts** (2,984 B; `decomp/port_ledger.md` has each one,
  with the first divergent instruction). 7 `unresolved-symbol` — the reloc
  walk cannot bind an aug6 slot to a retail symbol (`D_FFFFF`, `D_00247C40`,
  `D_7181F0`, ...), usually because the aug6 side spelled an absolute address
  as a symbol. 14 `codegen` — the retail source genuinely differs from the
  prototype's (`§regalloc-swap`, a `jr ra` where the built object stores,
  `addiu s0,s0,0` vs a real displacement). These need normal matching work,
  not porting. Most tractable class after V2, because a near-miss baseline
  exists.
- **V2 — 52 handwritten-asm twins already solved on aug6** (7,324 B). See the
  correction above. Start here.
- **V5 — 261 tail functions whose aug6 twin was never matched upstream**
  (118,972 B). Nothing to port. Mostly §3b proprietary SCE SDK, i.e.
  clean-room-from-disassembly only. (The figure "~310" that stood here
  conflated this group with V2; the two are 261 + 52 = 313.)
- **V4 — 52 tail functions with no aug6 twin** (27,112 B; 49 by the alias map
  plus the 3 symbol-table orphans) and **V3 — the 40 head functions**
  (5,056 B: 11 non-stub libkernl functions inside the carved head TU, plus 29
  in the two still-`asm` head spans). Original work on both counts.
- **V6 — `func_0026F578`**: portable but structurally blocked by the 12 B of
  inter-section `.text` pad splat places inside that object. Flagged as
  blocked, **not** queued as workable.
- **V0 — identify the upstream libgcc / newlib / fdlibm release** (§8). Not a
  match, but it is the prerequisite that unblocks ~61 KB of §3a work, and it
  is the highest-leverage item in the queue.

### Clean-room note for the head

The 140 head leaves were matched from the ROM's own four instructions via
`include/syscall.h`'s `SYSCALL_WRAPPER`, restored from this repo's history
(`398ac05e`). ps2sdk's `SYSCALL_SPECIAL` is credited as a *structural* model
only, per §3b. No SDK source was consulted, and none is needed: the body is
`addiu $3,$0,N / syscall 0 / jr $31 / nop` with nothing else in it. Nothing in
§3a (libgcc / libm / libc upstream fetching) was attempted — this pass ported
aug6's existing clean-room work only.

## 8. Open questions

- **Which exact newlib / GCC release did SCE ship?** Not answerable from the
  binary: `decomp/NOTES.md` §"Build-environment fingerprint" records that no
  `.comment`, `.note`, `.mdebug`, `.pdr` or `.gptab.*` section survives in
  `baseelf.elf`. Any answer has to come from codegen fingerprinting against
  candidate newlib/libgcc releases compiled with `ee-gcc 2.9-991111-01`.
  This is the first concrete task for anyone starting §3a — queued as **V0**,
  with the 13 fdlibm-window functions (**V5a**) named as the scoring corpus.
- **The 52 tail functions with no aug6 twin** (§7's V4; 49 by the alias map
  plus the 3 symbol-table orphans — the "~46" that stood here was wrong on
  both counts). Either the retail link pulled a different library revision
  than the Aug-6-2001 prototype did, or they are retail-side inlining
  artifacts. Unresolved.
- **Does the head run contain anything but crt0 + libkernl?** The 180-function
  head has not been attributed member-by-member with the same rigour as the
  tail.
