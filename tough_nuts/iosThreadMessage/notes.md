# Init_Player — parked (rc2, fumi/ios/thread)
Struct-of-fnptr filler. rc12->9->8->5 (hand) -> rc2 (permuter: f0 store after if/else).
Residual rc2 = same-TU %hi sharing: gcc emits ONE %hi base + addiu +offset for
iosThreadStart/Stop/Init (all in thread.c) while ROM uses per-symbol %hi/%lo relocs.
Different instruction bytes (ninja sha1 mismatch). Registers/structure otherwise match.
Re-attack: make gcc emit separate %hi per symbol (treat as external?), or permuter again.

## Resolution (b) — permuter-exhausted (stall=30, permuter ran)
Best hand form rc5 (differ). Permuter improved the .o-level differ to rc2 (f0 store
moved after if/else) BUT that does NOT link — ninja sha1 mismatch (8f4e8444 vs gate
2b4d7de4). The rc2 .o-differ is an isolation artifact (in-TU symbol relocs for
iosThreadStart/Stop/Init resolve differently pre-link). By the TRUE (ninja) measure
no output beats the parked INCLUDE_ASM. CAUTION on resume: match_loop differ-rc is
unreliable here (counts in-TU reloc resolution); gate on NINJA, not diff --dry.
