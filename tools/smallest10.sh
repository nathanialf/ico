#!/bin/bash
# Persistent standalone version of self-monitor's "ten smallest unmatched
# functions" shortlist. Same selection logic (size>=8, matched-orphan
# exclusion, live-INCLUDE_ASM intersection, parked included), but runnable
# on demand without the watch/dashboard. Emits TAB-separated:
#   func<TAB>tu<TAB>size_bytes<TAB>insns
# sorted smallest-first. Pass an integer arg to change the count (default 10).
set -euo pipefail
cd "$(dirname "$0")/.."

N="${1:-10}"

[[ -d asm/nonmatchings ]] || { echo "no asm/nonmatchings" >&2; exit 1; }

matched=$(find asm/matchings -name 'func_*.s' -printf '%f\n' 2>/dev/null \
              | sed 's/\.s$//' | sort -u)
included=$(grep -rhoE 'INCLUDE_ASM(_NOAT)?\("[^"]*",[[:space:]]*func_[0-9A-Fa-f]+' \
               --include=*.c src/ --exclude-dir=tough_nuts --exclude-dir=source_tree 2>/dev/null \
               | grep -oE 'func_[0-9A-Fa-f]+$' | sort -u)

grep -rH '^nonmatching ' asm/nonmatchings 2>/dev/null \
    | awk -v matched="$matched" -v included="$included" '
        function hex2dec(s,   i,c,v,r) {
            sub(/^0[xX]/, "", s); r=0
            for (i=1;i<=length(s);i++) {
                c=tolower(substr(s,i,1))
                if (c>="0"&&c<="9") v=c+0; else v=index("abcdef",c)+9
                r=r*16+v
            }
            return r
        }
        BEGIN {
            m=split(matched,q,"\n")
            for (i=1;i<=m;i++) if (q[i]!="") skip[q[i]]=1
            n=split(included,r,"\n")
            for (i=1;i<=n;i++) if (r[i]!="") inc[r[i]]=1
        }
        {
            ci=index($0,":nonmatching "); path=substr($0,1,ci-1)
            rest=substr($0,ci+13); comma=index(rest,",")
            fn=substr(rest,1,comma-1)
            if (fn in skip) next
            if (!(fn in inc)) next
            size=hex2dec(substr(rest,comma+2))
            if (size < 8) next
            np=split(path,pp,"/"); tu=pp[np-1]
            printf "%08d\t%s\t%s\t%d\n", size, fn, tu, size/4
        }
    ' | sort -n | head -"$N" | awk -F'\t' '{printf "%s\t%s\t%d\t%d\n", $2, $3, $1, $4}'
