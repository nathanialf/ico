#!/usr/bin/env python3
"""Rebuild the VENDOR half of `.port_cache/name_alias.json`.

`tools/port_from_aug6.py` joins a retail function to its aug6 twin BY NAME.
That works everywhere the two trees carved the same boundary at the same
address — but the vendor tail did not: retail's vendor run sits at a
different offset from the prototype's, so `func_<RETAILVMA>` can never equal
`func_<AUG6VMA>`.  The driver's `.port_cache/name_alias.json` hook supplies
the correlation, and without it **not one vendor function is even a port
candidate**.

That file is gitignored, and until now nothing in the tree rebuilt the
vendor entries — so every fresh worktree silently lost them and a vendor
pass looked like it had no work to do.  This script is that missing step.

Method (this is not a heuristic join): `decomp/VENDOR.md` §7 records that an
order-preserving alignment of reloc-normalized instruction streams pairs the
retail tail against the aug6 twin across exactly THREE constant deltas.  For
each retail function in the tail run we try each delta, and accept a pairing
only when the aug6 twin has a matched baseline `.s` AND the two trimmed
instruction streams are non-divergent under the driver's own classifier.
Unmatched twins are deliberately NOT emitted: there is nothing to port from
them, and a name-only pairing would just be a guess in a cache other tools
trust.

Everything the driver does downstream — the lockstep reloc-slot walk, the
per-function `quick_diff`, the full `ninja` SHA-1 — re-verifies the pairing,
so a wrong alias fails closed rather than landing bad bytes.

Usage:
    .venv/bin/python tools/gen_vendor_alias.py [--check]

Non-vendor entries in the file (the splat-merge carves scored by
tools/convpass_ordinal.py) are preserved untouched.  `--check` reports what
would change and exits non-zero if anything would, without writing.
"""
import argparse
import json
import os
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
os.environ.setdefault("PORT_AUG6_ROOT", "/primary/dev/ico")
import port_from_aug6 as P  # noqa: E402

# The three deltas of decomp/VENDOR.md §7. NOT a search range — the vendor
# tail is three contiguous library runs, each shifted by one constant.
DELTAS = (0x3C70, 0x3AE0, 0x3B00)

# The vendor tail run (decomp/VENDOR.md §1). The head run has no aug6 twin
# to align against and is not aliased.
TAIL_LO, TAIL_HI = 0x002418A0, 0x0026F5E0


def build():
    syms = P.load_retail_symbols()
    funcs = sorted((e for e in syms if e["type"] == "func"),
                   key=lambda e: e["vma"])
    vmas = [e["vma"] for e in funcs] + [P.TEXT_VMA + P.TEXT_SZ]
    blob = P.ROM.read_bytes()
    aug6 = P.aug6_matchings_index()

    words_cache = {}

    def aug6_words(name, rec):
        if name not in words_cache:
            srec = P.parse_aug6_s(P.AUG6_ROOT / rec["file"])[name]
            words_cache[name] = P.trim([w for w, _, _ in srec["insns"]])
        return words_cache[name]

    alias, verdicts = {}, Counter()
    for i, e in enumerate(funcs):
        vma = e["vma"]
        if not (TAIL_LO <= vma < TAIL_HI):
            continue
        n = vmas[i + 1] - vma
        off = vma - P.TEXT_VMA
        r_words = P.trim(list(struct.unpack("<%dI" % (n // 4),
                                            blob[off:off + n])))
        if not r_words:
            continue
        best = None
        for d in DELTAS:
            aname = "func_%08X" % (vma - d)
            arec = aug6.get(aname)
            if arec is None:
                continue                      # no matched baseline to port
            a_words = aug6_words(aname, arec)
            if not a_words:
                continue
            res = P.analyze(a_words, r_words)
            verdict = P.verdict_of(res)
            if verdict == "divergent":
                continue
            # prefer the closest stream, then an exact length agreement
            score = (-res["diff_count"], len(a_words) == len(r_words))
            if best is None or score > best[0]:
                best = (score, aname, verdict)
        if best:
            alias[e["name"]] = best[1]
            verdicts[best[2]] += 1
    return alias, verdicts


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true",
                    help="report drift and exit non-zero; do not write")
    args = ap.parse_args()

    alias, verdicts = build()
    print("verified vendor pairs: %d  %s" % (len(alias), dict(verdicts)),
          file=sys.stderr)
    deltas = Counter(int(k[5:], 16) - int(v[5:], 16) for k, v in alias.items())
    print("deltas: %s" % {hex(k): v for k, v in sorted(deltas.items())},
          file=sys.stderr)

    f = P.CACHE / "name_alias.json"
    cur = json.loads(f.read_text()) if f.exists() else {}
    kept = {k: v for k, v in cur.items()
            if not (TAIL_LO <= int(k[5:], 16) < TAIL_HI)} \
        if all(k.startswith("func_") for k in cur) else dict(cur)
    merged = dict(kept)
    merged.update(alias)

    if args.check:
        if merged != cur:
            added = set(merged) - set(cur)
            removed = set(cur) - set(merged)
            changed = {k for k in set(merged) & set(cur) if merged[k] != cur[k]}
            print("DRIFT: +%d -%d ~%d" % (len(added), len(removed), len(changed)),
                  file=sys.stderr)
            return 1
        print("up to date", file=sys.stderr)
        return 0

    f.parent.mkdir(parents=True, exist_ok=True)
    f.write_text(json.dumps(merged, indent=0))
    print("wrote %s (%d entries, %d non-vendor preserved)"
          % (f, len(merged), len(kept)), file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
