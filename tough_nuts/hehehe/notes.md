# hehehe — parked at rc2 (sugipon/src/act_a_p_1)

VRAM 0x001B7858, 128 insns, 0x1FC. Actor AI state-machine dispatcher.

## Status: rc2, full developer structure recovered (126/128 instrs match).

Parked mid-session (user-directed end, stall 7/30 — NOT a stall-gated park).
Resume: apply `hehehe.c` seed (+ move DeadProc/D_004BA160 typedef to TU top),
`match_loop.py reset hehehe --reason "resume rc2"`, then attack the ONE residual.

## What it does
`geo = (*(self+0x15C))->0x7F0` (AP1Geo, the GOBJ_SUB->Obj7F0 chain). `st = geo->f_8`.
switch(st): 5->set geo->8=4; 4->set geo->8=6; 6->self->0x16C=0; 7->nop;
default(0-3,>=8)-> if(geo->0x274<10){geo->0x274++; walkAI(self); st=reload}
                   geo->8 = D_004BA160[st]._4(self);  // fnptr at offset 4, not .fp(0)
                   wrap-counter: c=g2->0x270+1; g2->0x270=c; if(c>=0x21) g2->0x270=0;
Common tail: standAI, updateMatrix, func_00105078, func_001189F8(r,sub->0xC,&D_004BA1A0),
func_001CCBC0(geo->0x19C, r2, 1.0f), if(geo->0x4){ matrix drives + 2nd func_001189F8 },
then assert: diff = sub->0x54 - (sub->0xC)->0x34; range-check vs D_00629424(neg)/
D_00629428(pos); out of range -> sub->0x5E8=0x800; tail-call debug_assertMessage(&D_00610EA0).
hehehe is VOID (the assert is a `j` sibling-tail-call).

## Levers that cracked 34->2 (all in the seed)
- switch reorder: default-first, case 6 LAST (fall-through to tail) -> matched block layout (34->21).
- wrap-counter `if(c>=0x21)` inverse-if -> correct branch sense (21->17).
- store-then-overwrite (`g2->0x270=c; if(c>=0x21) g2->0x270=0`) -> `bne` not `bnel` (17->16).
- inline the TOP self->0x15C->0x7F0 chain (no named top var) -> killed block-0 const-5/ptr
  coloring tie (16->12).
- inline single-use self->0x15C reloads into call args -> reload lands in jal delay,
  reuses dead geo reg s0 (12->7).
- int-typed `(char*)*(int*)(self+0x15C)` in the wrap block -> may-aliases the int store
  to geo->8, keeps store BEFORE reload (7->5).
- `*(volatile float*)&D_00629424/8` on BOTH thresholds -> blocks dbr from speculating
  the lwc1 into the bc1f delay slot (5->2).  [[fp_load_delay_volatile_vs_int_store]]

## The residual (rc2): ONE register, permuter-class
block 18: `lw v1,0x4(s0)` (ROM) vs `lw v0,0x4(s0)` (built) for `geo->f_4` (the
`if (geo->f_4 != 0)` test) + the dependent `beql`. EVERY other instruction is
byte-identical. ROM coalesces geo->f_4 into v1 so the beql-delay `sub` reload
(also v1) recycles it; gcc local-alloc picks v0 (default, no copy-hint available).
A free-choice v0/v1 tie with no clean-C copy to steer it.

Tried (all no-op on this reg): in-condition assign `(f4=geo->f_4)`, `((int*)geo)[1]`
array-index, ptr-to-array `(*(char(*)[])...)`, decl reorder (p<st), int-typed assert-p
load, upstream temp for func_001CCBC0 a1, dev-authentic `fp` temp, goto-CFG for the if,
neg-into-temp before the cmp.

CLASS = func_001FB768 / DispCollisionPC twin (single-register coalescing tie). The
analog cracked ONLY when the permuter found a `(new_var2 = new_var)` non-coalescing
copy that clean C can't naturally express. Next on a real resume: reach the stall=30
gate by hand (genuinely-distinct shapes only) then seed the permuter with this rc2.
