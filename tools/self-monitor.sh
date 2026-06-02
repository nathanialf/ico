#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, last commit, and best permuter scores for parked funcs.
# Refreshes every 10 seconds.

INTERVAL=10

if [[ "$1" == "--once" ]]; then
    cols=${COLUMNS:-$(tput cols)}
    rule=$(printf '%*s\n' "$cols" '' | tr ' ' -)

    # Refresh docs/PROGRESS.md from current src/ + yaml + built objects.
    # Done here (not in per-match commits) so the matching loop doesn't
    # carry the ~1s progress-regen cost. Output suppressed; progress.py
    # is a no-op write when content hasn't changed.
    if [[ -x .venv/bin/python ]]; then
        .venv/bin/python tools/progress.py >/dev/null 2>&1 || true
    fi

    echo "$rule"
    # Render the markdown table as a fixed-width table. Pull the rows
    # between the `progress:begin` / `progress:end` markers so adding
    # a new section row in tools/progress.py doesn't drift this range.
    # Strip the leading/trailing pipes, drop the markdown separator
    # row (---|---|...), then column-align on `|`.
    sed -n '/<!-- progress:begin -->/,/<!-- progress:end -->/p' docs/PROGRESS.md \
        | sed -E '/<!-- progress:(begin|end) -->/d; s/^\| //; s/ \|$//; /^[- |:]+$/d' \
        | column -t -s '|'
    echo "$rule"

    # Ten smallest unmatched functions (by instruction count), across all
    # claimed TUs that still carry INCLUDE_ASM stubs under
    # asm/nonmatchings/. These are the cheapest remaining matches — the
    # matching loop's natural "grab next" shortlist. Each .s file's
    # `nonmatching <fn>, 0x<size>` header gives the byte size; size/4 is
    # the instruction count (mawk has no strtonum, so hex2dec parses it).
    # Excluded: lone-`nop` alignment artifacts that splat labels as
    # 1-insn "functions" (size < 8 bytes; no real EE function is shorter
    # than a jr + delay slot), and ALREADY-MATCHED functions whose
    # nonmatchings .s is a stale orphan. Parked targets (tough_nuts/<fn>/)
    # are deliberately NOT excluded: a parked func is a near-miss, not a
    # floor (per the 20-iter discipline), so it stays in the cheapest-
    # remaining shortlist as a re-attempt candidate.
    #
    # The orphan case: when a TU is re-laid-out (coalesce / yaml move) the
    # function's asm is regenerated under its NEW TU dir, but the OLD
    # asm/nonmatchings/<old-TU>/<fn>.s is left behind — `build.sh
    # distclean` deliberately never prunes asm/nonmatchings (it's the
    # tracked subtree). Those orphans are untracked and have a sibling
    # under asm/matchings/, so a function present in BOTH trees is matched
    # and its nonmatchings copy is stale. Skip by matchings-presence: it
    # hides only stale orphans (every genuine target — a freshly-split
    # INCLUDE_ASM stub — exists ONLY under nonmatchings). Without this the
    # smallest orphan (e.g. a 2-insn tail-call) sorts to the top and gets
    # handed out as a "match target" that is already done.
    # Version-aware lowest-10. Retail (us) emits to asm/; the aug6 prototype
    # branch to asm/aug6/ and its TUs live in the dev-developer tree. Now that
    # aug6's whole .text is carved per-function, the per-function nonmatchings
    # exist, so the same smallest-unmatched logic applies (named INCLUDE_ASMs,
    # not just func_).
    _sm_version="${VERSION:-}"
    if [[ -z "$_sm_version" ]]; then
        if [[ -f config/ico.us.yaml ]]; then _sm_version=us
        elif [[ -f config/ico.aug6.yaml ]]; then _sm_version=aug6; fi
    fi
    if [[ "$_sm_version" == "us" ]]; then
        _NM="asm/nonmatchings"; _MA="asm/matchings"; _ROOTS="src"
    else
        _NM="asm/${_sm_version}/nonmatchings"; _MA="asm/${_sm_version}/matchings"
        _ROOTS="common fumi sugipon seki omori script ito src ios sound isys"
    fi
    if [[ -d "$_NM" ]]; then
        matched=$(find "$_MA" -name '*.s' -printf '%f\n' 2>/dev/null \
                      | sed 's/\.s$//' | sort -u)
        # GENUINE-UNMATCHED filter: a func is a target iff it's still referenced
        # by an INCLUDE_ASM in a tracked .c (named OR func_) and not already in
        # the matchings tree. (tough_nuts/source_tree excluded as parked seeds.)
        included=$(grep -rhoE 'INCLUDE_ASM(_NOAT)?\("[^"]*",[[:space:]]*[A-Za-z_][A-Za-z0-9_]*' \
                       --include=*.c $_ROOTS --exclude-dir=tough_nuts --exclude-dir=source_tree 2>/dev/null \
                       | grep -oE '[A-Za-z_][A-Za-z0-9_]*$' | sort -u)
        echo "Ten smallest unmatched functions (TU · instructions; matched & nop-pads excluded):"
        grep -rH '^nonmatching ' "$_NM" 2>/dev/null \
            | awk -v matched="$matched" -v included="$included" -v nm="$_NM" -v ver="$_sm_version" '
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
                    # Dead splat padding (extends the size<8 nop-pad skip above
                    # to >=8-byte cases): a "function" whose entire body is nop
                    # plus a relative `b` to a DIFFERENT symbol is not compiled
                    # C — clean C cannot emit a cross-function `b` (ee-gcc tail
                    # calls emit `j`), and a bare-nop entry has no `jr`. These
                    # are nop-fill regions splat mis-labeled as functions (e.g.
                    # func_001AACF4 -> func_001AACE0, a dead 0x20 nop region).
                    # A genuine `for(;;)` self-loop (b to SELF) IS matchable, so
                    # keep those (crossb stays 0); exclude only cross-branch pads.
                    real=0; crossb=0
                    while ((getline line < path) > 0) {
                        if (line !~ /\*\//) continue
                        mn=line; sub(/.*\*\/[[:space:]]*/,"",mn)
                        op=mn; sub(/^[^[:space:]]+[[:space:]]*/,"",op)
                        sub(/[[:space:]].*/,"",mn)
                        if (mn=="" || mn=="nop") continue
                        if (mn=="b") { if (op!=fn) crossb=1; continue }
                        real=1
                    }
                    close(path)
                    if (!real && crossb) next
                    # The matching tools (match_diff/quick_diff) resolve a TU by
                    # its full subseg path on aug6 (e.g. fumi/src/boyact), so emit
                    # the path between the nonmatchings root and the <func>.s, not
                    # just the basename. Retail (us) keeps the proven basename.
                    if (ver != "us") {
                        rel=path; sub("^"nm"/","",rel)
                        nr=split(rel,rp,"/"); tu=""
                        for (k=1;k<nr;k++) tu=(tu==""?rp[k]:tu"/"rp[k])
                    } else {
                        np=split(path,pp,"/"); tu=pp[np-1]
                    }
                    printf "%08d\t%s\t%s\t%d insn\n", size, fn, tu, size/4
                }
            ' | sort -n | head -10 | cut -f2- \
            | column -t -s "$(printf '\t')"
        echo "$rule"
    fi

    # Lowest permuter score per parked function. Decomp-permuter writes
    # candidates to lib/decomp-permuter/runs/<func>/output-<score>-<n>/.
    # Lower score = better; 0 = matched. Source of truth for parked
    # functions is tough_nuts/<func>/ (one subdir per parked function).
    #
    # Temporarily hidden during the coalesce sprint — the dashboard
    # focuses on TU coalesce progress, not per-function matching, until
    # the structural pass is done. Flip this guard to re-enable.
    if false && [[ -d tough_nuts && -d lib/decomp-permuter/runs ]]; then
        # Skip-marked targets (tough_nuts/<func>/.skip) are excluded from
        # the auto-permuter rotation, so don't list them here either —
        # this dashboard exists to show what the permuter is working on.
        skipped=$(find tough_nuts -mindepth 2 -maxdepth 2 -name '.skip' -printf '%h\n' 2>/dev/null | wc -l)
        echo "Permuter scores (tough_nuts; ${skipped} .skip-marked hidden; sorted lowest-score first):"
        # Build "score|func:best" rows, sort by score ascending, then drop
        # the score prefix. Functions with no permuter output sort last
        # (assigned a sentinel beyond any real score). Lower score = better;
        # 0 = matched, so promotable hits surface at the top of the table.
        rows=()
        while IFS= read -r func; do
            [[ -z "$func" ]] && continue
            [[ -f "tough_nuts/$func/.skip" ]] && continue
            runs_dir="lib/decomp-permuter/runs/$func"
            best="-"
            sort_key=999999999
            if [[ -d "$runs_dir" ]]; then
                b=$(find "$runs_dir" -maxdepth 1 -type d -name 'output-*' \
                            -printf '%f\n' 2>/dev/null \
                        | sed -nE 's/^output-(-?[0-9]+).*$/\1/p' \
                        | sort -n | head -1)
                if [[ -n "$b" ]]; then
                    best="$b"
                    sort_key="$b"
                fi
            fi
            rows+=("$(printf '%012d|%s:%s' "$sort_key" "$func" "$best")")
        done < <(find tough_nuts -mindepth 1 -maxdepth 1 -type d \
                      -name 'func_*' -printf '%f\n' 2>/dev/null | sort)
        # Sort rows by their numeric prefix, then strip it.
        cells=()
        while IFS= read -r row; do
            cells+=("${row#*|}")
        done < <(printf '%s\n' "${rows[@]}" | sort -n)
        if (( ${#cells[@]} > 0 )); then
            cellw=0
            for c in "${cells[@]}"; do (( ${#c} > cellw )) && cellw=${#c}; done
            cellw=$((cellw + 2))            # gutter
            ncols=$(( cols / cellw ))
            (( ncols < 1 )) && ncols=1
            i=0
            for c in "${cells[@]}"; do
                printf "%-${cellw}s" "$c"
                i=$((i + 1))
                (( i % ncols == 0 )) && echo
            done
            (( i % ncols != 0 )) && echo
        fi
        echo "$rule"
    fi

    git log -1
    echo "$rule"
    git status
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
