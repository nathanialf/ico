# func_00191D70 (fightSound, sound-update state machine) — analyzed, NOT matched

VRAM 0x00191D70, 0x1E0 (120 insns). asm/nonmatchings/src/fightSound/func_00191D70.s

## Status: full CFG traced & verified CORRECT; best draft = 53 diffs

The control-flow graph matches the original exactly (goto-CFG-mirror C).
Globals: D_006D0D20[] ([0]=handle from func_00143CD0, [1]=volume clamped
0..0x1800, [2]=func_00141C28 target, [5]/0x14=flag), gp_rel
D_00632780(mode==1?), D_00632788(state, word-stored via *(int*)), D_00632784
(out: set 1 or 2), D_00631AE4/D_00631AE8/D_00632F7C (config bools),
D_00274EC0 struct (+0x14, +0x18). Calls func_00143CD0(&buf, buf=0x110001),
func_0014B2F0(cfg, 0xF|9), func_00141C28(&D_006D0D20[2],2,1,2,0),
func_00140B60(handle, vol). Uses movn (flag = r?1:flag), movz
(amt = mode==1?0x400:0x60), a bnel-annulled `D_00632788=0` delay.

## THE BLOCKER (53 diffs, mostly ONE cascade)

Original keeps `%hi(D_00274EC0)` in a callee-saved reg **$s4** (frame 0x70,
6 saves) and rematerializes the full address (`addiu $reg,$s4,%lo`) per use.
ee-gcc instead caches the FULL address in one reg (frame 0x60, 5 saves, no
$s4) -> the -0x10 frame diff cascades through every stack offset & branch
target = the bulk of the 53. Neither caching `char *st` nor inlining
`(char*)&D_00274EC0` per use triggers the high-part hoist (candle's
merge-point trick does NOT apply — here it is used across calls in multiple
blocks). Also: the literal `1` lives in $s2 ($18) across the func_0014B2F0
call (beq + movn) in the original; mine puts it in $s0.

NEXT: find how to force ee-gcc to keep a far symbol's %hi in a callee-saved
reg across calls (high-part hoisting) — cousin of [[asm_label_alias_far_sdata]]
/ [[eager_rodata_materialize]]. Once $s4 appears the frame cascade collapses;
then permuter for the residual. This is "state-machine soup" (CLAUDE.md):
a dedicated session, not a rushed batch.
