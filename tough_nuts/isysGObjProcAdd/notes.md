# isysGObjProcAdd (fumi/isys/gobj_process) — parked at rc3, permuter-class

Linked-list UNLINK (next@0x8=self[2], prev@0xC=self[3], owner@0x4=self[1],
owner head@0x2C=owner[0xB], tail@0x30=owner[0xC]). Guard self==0 → tail-call
debug_assertMessage(D_00551F18). Unlink via the gobj_dl goto idiom (matches
the first 0x4C bytes exactly). Then head/tail update on the per-owner list.

## Residual (rc3, +0xB seed)
Head/tail section only. Original keeps manager (owner) in $3 for the head
check (offset 0x2C) AND a PLAIN COPY of manager in $5 (`daddu $5,$3`, filling
the bne delay) for the tail check (offset 0x30).

- Baseline `owner=self[1]; owner[0xB]; owner[0xC]` → gcc COALESCES to one reg
  ($3) for both → `bnel` (annul-prefetch), NO $5 copy. rc4.
- `owner=self[1]+0xB; owner[0]; owner[1]` → forces a distinct pseudo
  (manager+0x2C) → gives the `bne` structure (matches branch!) but the
  0x2C offset is FOLDED into the base (`addiu a1,v1,0x2C` + `lw 0x4(a1)`)
  instead of a plain copy + 0x30 offset. rc3 — the 3 diffs are exactly:
  delay daddu-vs-addiu, tail load/store offset 0x30-vs-0x4.

## Tried (~50 distinct hand shapes, all >=3)
struct-typed, int* word-index, inline-twice (double load rc9), owner early,
ptr-to-array deref, re-read self[1] (reload not copy), char* byte offsets,
int-temp self, natural-if unlink (rc12), void-launder, +0xC mirror, two
owner vars (coalesced), +0xB family (rc3 floor). The split-with-plain-copy
($5=manager, no fold) is a coalescer/regalloc artifact not reachable by the
shapes above — permuter territory (cf. permuter_cracks_reorg_tail, §3.3).

## Resume
Seed = the +0xB rc3 form above (has the matching `bne`). Permuter should
perturb the tail-base register to a plain manager copy. Re-attack: get
$5=manager (offset 0x30 kept) instead of manager+0x2C.

## Permuter shot (this session) — fair, beat nothing
tools/permute_run.sh runs in aug6 mode → delegates per-iteration builds to
tools/compile_c.sh = ee-gcc **2.9-991111** (correct compiler; the "2.96" in
the script header is stale retail docs). 5 min, no score-0. Best candidate
(permuter score 140 vs base 210 — `new_var=self`) harvests to **rc8** under
match_diff — the permuter's score is NOT reloc-normalized real_count, so a
lower score can be a worse real match; always harvest by ninja/match_diff.
Hand rc3 stays best → (b). Resume: give it a longer run, or hand-crack the
$5=manager plain-copy.
