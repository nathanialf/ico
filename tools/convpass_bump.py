#!/usr/bin/env python3
"""convpass wave-2 helper (worker 3).

Simultaneous constant rewrite for the retail-vs-aug6 "id family bumped"
patterns.  Chains like 0x12A->0x12B, 0x12B->0x12C must be applied in one
pass or they cascade; this does that.

    convpass_bump.py <file> 0x12A=0x12B 0x12B=0x12C ...
    convpass_bump.py <file> --skip 'a0 + 0x164' 0x164=0x165

--skip PAT protects any occurrence whose surrounding 24 chars contain PAT
(e.g. struct-offset uses of a value that is also an id).
"""
import re
import sys

def main() -> int:
    args = sys.argv[1:]
    path = args.pop(0)
    skips = []
    pairs = {}
    while args:
        a = args.pop(0)
        if a == "--skip":
            skips.append(args.pop(0))
        else:
            k, v = a.split("=")
            pairs[k.lower()] = v
    src = open(path).read()
    pat = re.compile(r"\b(?:%s)\b" % "|".join(re.escape(k) for k in pairs), re.I)

    def sub(m):
        ctx = src[max(0, m.start() - 24):m.end() + 24]
        if any(s in ctx for s in skips):
            return m.group(0)
        return pairs[m.group(0).lower()]

    out, n = pat.subn(sub, src)
    open(path, "w").write(out)
    print("%s: %d substitutions" % (path, n))
    return 0

if __name__ == "__main__":
    sys.exit(main())
