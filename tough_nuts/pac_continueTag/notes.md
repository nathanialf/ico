# pac_continueTag — part of a WHOLE-TU effort, not a standalone park

DO NOT treat this as an isolated resume. pac_continueTag's C is already recovered
and byte-exact (rc1 was only the jtbl `%lo` placement reloc). It must be matched
LAST, after the rest of seki/src/Packet.c is C and the `.rodata` region is
contiguous.

**Full picture + recovered C + commit strategy + build facts:**
see  `tough_nuts/Packet_full_match_handoff.md`

Goal: relentlessly match ALL of seki/src/Packet.c. Do NOT park any Packet function.
