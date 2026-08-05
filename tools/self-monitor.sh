#!/bin/bash
# Periodic dashboard for the matching loop: shows progress totals,
# git status, last commit, and best permuter scores for parked funcs.
# Refreshes every 10 seconds.

INTERVAL=10

if [[ "$1" == "--once" ]]; then
    cols=${COLUMNS:-$(tput cols)}
    rule=$(printf '%*s' "$cols" '' | sed 's/ /─/g')
    # Responsive layout primitive. Compose two already-rendered text blocks
    # side by side — left-padded to the left block's own width, then a
    # ` │ ` vertical separator, then the right block — when they both fit on
    # $cols, else stack them vertically with a rule between. The decision is
    # the REAL combined width vs the REAL terminal width — no magic per-pair
    # breakpoint — so a wide tablet fills its horizontal space and a phone in
    # portrait still reads top-to-bottom. Blocks are ASCII-aligned internally
    # (box-drawing chars only appear in $rule and this separator, never inside
    # a block), so ${#line} width math is correct. The separator is drawn on
    # EVERY row, including blank ones where one panel ran out, so the vertical
    # line stays continuous down the full height of the taller panel.
    sidebyside() {
        local left="$1" right="$2"
        local -a L R
        mapfile -t L <<<"$left"
        mapfile -t R <<<"$right"
        local wa=0 wb=0 ln
        for ln in "${L[@]}"; do (( ${#ln} > wa )) && wa=${#ln}; done
        for ln in "${R[@]}"; do (( ${#ln} > wb )) && wb=${#ln}; done
        # Gutter ` │ ` is 3 display columns wide.
        if (( wa + 3 + wb > cols )); then
            printf '%s\n' "$left"
            echo "$rule"
            printf '%s\n' "$right"
            return
        fi
        local rows=${#L[@]}; (( ${#R[@]} > rows )) && rows=${#R[@]}
        local i
        for (( i = 0; i < rows; i++ )); do
            printf '%-*s │ %s\n' "$wa" "${L[i]-}" "${R[i]-}"
        done
    }

    # Refresh docs/PROGRESS.md from current src/ + yaml + built objects.
    # Done here (not in per-match commits) so the matching loop doesn't
    # carry the ~1s progress-regen cost. Output suppressed; progress.py
    # is a no-op write when content hasn't changed.
    if [[ -x .venv/bin/python ]]; then
        .venv/bin/python tools/progress.py >/dev/null 2>&1 || true
    fi

    echo "$rule"
    # Sweep remaining ACTIONABLE per author scope (top-left of the dashboard).
    # Mirrors tools/sweep_targets.sh --counts. A func is a sweep target iff it
    # still carries an INCLUDE_ASM stub with a real .s and isn't parked under
    # tough_nuts/. actionable (= "fresh") is what a one-pass sweep would really
    # attempt = unmatched − SPILL (a0-spill one-pass MISS class) − PARKED
    # (already attempted+parked in a prior sweep: named in docs/MATCHING_NOTES.md
    # or config/sweep_parked.txt). SPILL is shown as its own column.
    # Captured into a block (not printed) so it can pair with the progress
    # table side by side on a wide terminal.
    _sweep_block=$( {
        echo "Sweep remaining actionable (fresh = unmatched - SPILL - parked):"
        {
            printf 'scope\tactionable\tspill\tparked\n'
            _sw_ta=0; _sw_ts=0; _sw_tp=0
            for _sw_sc in fumi script common sugipon seki omori ito; do
                [[ -d "$_sw_sc" ]] || continue
                _sw_c=$(tools/sweep_targets.sh "$_sw_sc" --counts 2>/dev/null)
                _sw_a=$(printf '%s' "$_sw_c" | grep -oE 'fresh=[0-9]+'  | cut -d= -f2)
                _sw_s=$(printf '%s' "$_sw_c" | grep -oE 'SPILL=[0-9]+'  | cut -d= -f2)
                _sw_p=$(printf '%s' "$_sw_c" | grep -oE 'PARKED=[0-9]+' | cut -d= -f2)
                _sw_a=${_sw_a:-0}; _sw_s=${_sw_s:-0}; _sw_p=${_sw_p:-0}
                _sw_ta=$((_sw_ta + _sw_a)); _sw_ts=$((_sw_ts + _sw_s)); _sw_tp=$((_sw_tp + _sw_p))
                printf '%s\t%d\t%d\t%d\n' "$_sw_sc" "$_sw_a" "$_sw_s" "$_sw_p"
            done
            printf 'TOTAL\t%d\t%d\t%d\n' "$_sw_ta" "$_sw_ts" "$_sw_tp"
        } | column -t -s "$(printf '\t')"
    } )
    # Render the markdown progress table as a fixed-width block. Pull the rows
    # between the `progress:begin` / `progress:end` markers so adding a new
    # section row in tools/progress.py doesn't drift this range. Strip the
    # leading/trailing pipes, drop the markdown separator row (---|---|...),
    # then column-align on `|`.
    _prog_block=$(
        { echo "Progress:"
          sed -n '/<!-- progress:begin -->/,/<!-- progress:end -->/p' docs/PROGRESS.md \
            | sed -E '/<!-- progress:(begin|end) -->/d; s/^\| //; s/ \|$//; /^[- |:]+$/d' \
            | column -t -s '|'; }
    )
    sidebyside "$_sweep_block" "$_prog_block"
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
    # Insn-count shortlists (smallest unmatched funcs / least-remaining TUs).
    if [[ -d "$_NM" ]]; then
        matched=$(find "$_MA" -name '*.s' -printf '%f\n' 2>/dev/null \
                      | sed 's/\.s$//' | sort -u)
        # GENUINE-UNMATCHED filter: a func is a target iff it's still referenced
        # by an INCLUDE_ASM in a tracked .c (named OR func_) and not already in
        # the matchings tree. (tough_nuts/source_tree excluded as parked seeds.)
        included=$(grep -rhoE 'INCLUDE_ASM(_NOAT)?\("[^"]*",[[:space:]]*[A-Za-z_][A-Za-z0-9_]*' \
                       --include=*.c $_ROOTS --exclude-dir=tough_nuts --exclude-dir=source_tree 2>/dev/null \
                       | grep -oE '[A-Za-z_][A-Za-z0-9_]*$' | sort -u)
        # Compute the genuine-unmatched per-function rows ONCE, then render
        # two tables from them: the cheapest individual functions, and the
        # TUs with the least total remaining work. Each row is
        # tab-separated `<paddedsize>\t<fn>\t<tu>\t<N insn>`.
        _sm_rows=$(grep -rH '^nonmatching ' "$_NM" 2>/dev/null \
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
                    # INCLUDE_ASM in tracked source WINS over matchings-presence.
                    # A func still referenced by an INCLUDE_ASM is unmatched BY
                    # DEFINITION, whatever asm/matchings holds. Order matters: the
                    # matchings check exists only to hide stale ORPHANS from a TU
                    # re-layout, but a func that MATCHED and was later reverted to
                    # INCLUDE_ASM also leaves a matchings .s behind (distclean never
                    # prunes asm/), and testing `skip` first silently dropped those
                    # from the shortlist. That hid 3 genuinely-unmatched funcs
                    # (func_00258450, func_00244958, ResetStatic2MotionManager) after
                    # the 2026-08-05 assembler revert — they vanished from the
                    # smallest-unmatched list while still being INCLUDE_ASM.
                    if (!(fn in inc)) next
                    if ((fn in skip) && !(fn in inc)) next
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
            ')
        # Render two tables SIDE BY SIDE: the cheapest individual functions on
        # the left, and the TUs with the least remaining work on the right.
        #   left  = smallest unmatched functions (fn / TU / insn)
        #   right = TUs summed by remaining unmatched instructions, smallest
        #           total first — the TUs closest to fully matched, the natural
        #           "finish this off" shortlist. The `fn` column counts the
        #           still-unmatched functions contributing to that TU's total.
        # Each side is laid out with its own `column -t` and a header line,
        # then handed to sidebyside() which pairs them on a wide terminal and
        # stacks them on a narrow one. Headers stay ASCII so width math is
        # correct regardless of locale.
        _fn_block=$( { echo '10 smallest unmatched funcs (fn / TU / insn):'
            printf '%s\n' "$_sm_rows" | sort -n | sed -n '1,10p' | cut -f2- \
                | column -t -s "$(printf '\t')"; } )
        _tu_block=$( { echo '10 TUs, least remaining work (TU / insn / fns):'
            printf '%s\n' "$_sm_rows" \
                | awk -F'\t' 'NF>=4 { tot[$3]+=$1; cnt[$3]++ }
                              END { for (t in tot) printf "%012d\t%s\t%d insn\t%d fn\n", tot[t], t, tot[t]/4, cnt[t] }' \
                | sort -n | sed -n '1,10p' | cut -f2- \
                | column -t -s "$(printf '\t')"; } )
        sidebyside "$_fn_block" "$_tu_block"
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

    # Footer: last commit beside working-tree status. sidebyside() pairs them
    # on a wide terminal and falls back to stacking (with a rule between) when
    # the combined width — git status lines can be long — would overflow.
    sidebyside "$(git log -1)" "$(git status)"
    echo "$rule"
    exit 0
fi

watch -t -n "$INTERVAL" "$0 --once"
