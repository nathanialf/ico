# Vendor code policy — what it is, how it is accounted, what may be used to match it

*Written 2026-07-28. Treat the POLICY here (§0, §2, §3, §4, §6) as canonical
and target-neutral — it binds on every branch.*

*The NUMBERS and representation in §1, §5 and §7 were measured on the USA
retail tree (now the `ntsc` branch) and its aug6 port. On `main` (PAL retail)
vendor is represented natively: `config/ico.pal.yaml` carries **18
`src/cod/vendor_<VMA>` spans**, each one an archive member run named from the
PAL disc's own `MAIN.MAP` (e.g. `vendor_2788D8` = libm.a 21/21,
`vendor_27E5E0` = libc.a 116/118), and `config/symbol_addrs.pal.txt` carries
967 `// (vendor)` notes. Re-measure before quoting any figure below on this
branch.*

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

On the USA tree the two runs were one `asm` blob each in `config/ico.us.yaml`
(yaml offsets are ROM offsets = VMA − 0x100000), with `// (vendor)` notes
emitted into `config/symbol_addrs.us.txt` by that branch's
`gen_us_symbol_addrs.py`.

On `main` the same two runs are 18 per-archive-member spans in
`config/ico.pal.yaml` (`src/cod/vendor_<VMA>`), and the `// (vendor)` notes in
`config/symbol_addrs.pal.txt` are emitted by `tools/gen_pal_symbol_addrs.py`
from the disc's `MAIN.MAP` member list — so PAL knows which archive each
function came from, which the USA cut could only infer by hashing.

---

## 2. The de-facto policy: vendor code **is** matched, clean-room

A stale YAML comment on the `aug6` branch still says *"crt0 + libkernl
(vendor, not matched)"*. It is wrong: the `aug6` branch had already landed
**478 vendor functions / 46,808 bytes**, spanning every archive in the table
above.

Those matches live inside `common/src/PObj.c`, because aug6's final `.text`
subsegment is an uncarved `common/src/PObj` blob that swallows the whole
vendor tail. That representation **attributes ~46 KB of SDK and libc code to a
game TU**, which is dishonest accounting.

The rule that came out of it and still binds: **vendor code lives in
vendor-named TUs, never folded into a game TU.** `main` satisfies it by
construction — the 18 `src/cod/vendor_<VMA>` spans are named per archive
member.

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
- **libc** — newlib, BSD-style licence. **Snapshot pinned 2026-09-04 to
  newlib 1.8.2** (released 2000-01) from the PAL disc's own listing
  (`baserom/pal/SRCFILE.TXT`, per-instruction `file:line` rows under
  `/usr/local/sce/ee/gcc/build/ee/newlib/`): the highest cited line in
  `vfprintf.c` is 918, which exceeds 1.8.1's 917-line file; the highest cited
  line in `dtoa.c` is 854, which exceeds 1.9.0's 853-line file; both fit
  1.8.2 (939 / 854 lines), as do `vfscanf.c` (905 cited, 905 in 1.8.2) and
  `mallocr.c` (`_malloc_r`'s first instruction cites line 2311; `mALLOc` is
  defined at 2296 in 1.8.2 vs 2265 in 1.8.1). Start public-source matching
  from the 1.8.2 tarball (sourceware.org/pub/newlib/newlib-1.8.2.tar.gz).

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
`config/symbol_addrs.<ver>.txt` so the dashboard stops counting it as a
note-less symbol. It is crt0, i.e. §3b proprietary — not game code, and not
something to match casually.

**`ico2000.a(vobj.o)` — ~400 B of real game code on the vendor side.** The
USA symbol generator's own docstring admitted this (that script lived on the
`ntsc` branch; PAL takes the member boundaries from `MAIN.MAP` instead): the
vendor cut was
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
  merely-missing note (resolved from the `c` subsegment spans in
  `config/ico.<ver>.yaml`), 5 were the VU1 microprograms, and 1 was `_start`.
  A symbol with neither a TU note nor a `(vendor)` note now lands in an
  explicit `(unassigned)` group that should always be empty.
- **`.vutext` is counted separately from `.text`.** The five VU1
  microprograms are `hasm` subsegments in a different ELF section of
  `config/ico.<ver>.yaml`; `tools/progress.py` has always reported
  `.vutext` 100 % matched. They now get their own `.vutext` group so their
  20,704 bytes cannot inflate a `.text` roll-up. `totals.sections` reports
  both sections; `totals.matched_bytes` / `total_bytes` remain `.text` only.

---

## 7. Status

Vendor accounting is per-branch; there is no cross-branch vendor total.

- **`main` (PAL).** The two runs are carved into 18 `src/cod/vendor_<VMA>`
  spans in `config/ico.pal.yaml`, one per archive member, each comment
  carrying the member name and how many of its functions `MAIN.MAP` accounts
  for (e.g. `vendor_25E188` = libdma.a 16/16, `vendor_272338` = libipu.a
  4/70). Live matched counts: the dashboard linked from `README.md`; what was
  ported in and what was reverted: `decomp/port_ledger_pal.md` and
  `decomp/port_ledger_pal_aug6.md`.
- **`ntsc` / `aug6`.** Their vendor status, the aug6→retail vendor port and
  its V0–V6 queue are history now; the write-up is in
  `decomp/ARCHIVE_retired_notes.md` (it depended on `convpass_ledger_3.md`,
  `port_ledger.md` and `port_from_aug6.py`, none of which exist any more).

The durable results of that port, restated because they are still true:

- **Head leaves are clean-room from the ROM.** The 140 EE-syscall head leaves
  were matched from the ROM's own four instructions via `include/syscall.h`'s
  `SYSCALL_WRAPPER`. ps2sdk's `SYSCALL_SPECIAL` is credited as a *structural*
  model only, per §3b; no SDK source was consulted and none is needed — the
  body is `addiu $3,$0,N / syscall 0 / jr $31 / nop`.
- **Handwritten-asm vendor leaves are the most tractable class** (VU0
  macro-mode, MMI, privileged COP0/TLB/cache, syscall stubs): they are
  byte-exact by construction from the ROM's own instructions.
- **§3b (proprietary SCE SDK) bodies are clean-room-from-disassembly only.**
  That is most of what remains unmatched on the vendor side, on every branch.

## 8. Open questions

- **Which exact newlib / GCC release did SCE ship? — ANSWERED 2026-09-04 by
  the PAL disc listing.** libgcc / libc / libm come from
  `gcc-lib/ee/2.9-ee-991111-01`, i.e. the same compiler the build already
  uses, and the newlib snapshot is **1.8.2**: the listing's line citations
  place `vfprintf.c` at 918 lines (> 1.8.1's 917) and `dtoa.c` at 854 (>
  1.9.0's 853). That was the prerequisite for any §3a work — the upstream
  sources are now identifiable and legitimately obtainable. (It was *not*
  answerable from the binary alone: no `.comment`, `.note`, `.mdebug`, `.pdr`
  or `.gptab.*` section survives — see `decomp/NOTES.md` "Build-environment
  fingerprint".)
- **Tail functions with no prototype twin.** On the USA tree 52 of them had
  no aug6 counterpart. Either the retail link pulled a different library
  revision than the Aug-6-2001 prototype did, or they are retail-side inlining
  artifacts. Unresolved, and worth re-asking on PAL now that `MAIN.MAP` names
  each member.
- **Does the head run contain anything but crt0 + libkernl?** The 180-function
  head has not been attributed member-by-member with the same rigour as the
  tail.
