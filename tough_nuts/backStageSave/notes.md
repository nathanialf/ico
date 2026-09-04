# backStageSave — parked (user-requested, not a 30-stall)

**Best: rc162** (seed: `backStageSave.c`, the rc162 source). Parked at user request
mid-grind; NOT a floor — clearly progressing (rc165→162) with known next levers.

## Cracked this session
- **Frame-size root (0x60→0x70):** the disp block has THREE address-taken stack
  buffers (call2-vec, call1-outgoing-copy, call1-zeroed-scratch). gcc coalesces
  them unless their lifetimes overlap. **Fix: compute `w[]` (call2 vec) BEFORE the
  call1 disp block** → distinct slots → frame 0x70. (Seed has this.)
- **disp_memory_partition_bar (0x1ABA60, icoMisc) convention:** reads exactly 5
  register args `(int line, int flags, int val, void *p1, void *p2)` — verified it
  reads only $4-$8, no $9-$11, no incoming stack. Call1 passes an extra 6th 16-byte
  by-value struct (zeroed via memset, 3 floats from `D_002A0A90+0x3862C`
  set, 4th=pad) that disp IGNORES. Call2 passes `p1=&vec`, `p2=sp+0x10`. So disp is
  effectively K&R/unprototyped (call1=6 args, call2=5).

## Remaining diffs at rc162 (regalloc + branch-direction cascade)
1. **regalloc:** built allocates an EXTRA callee reg `s3` and materializes the
   constant `1` there; ROM keeps `1` in `s0`/$16 live across the state-1 calls
   (`addiu $16,$0,1; beq $3,$16,state1`). Want the `1` reused in one callee reg
   (the `pin_shared_const_for_cse` shape, via a reused C variable — no pins).
2. **branch-direction:** ROM dispatches the state machine with `beq` to OUT-OF-LINE
   state bodies (`beq $3,$16,state1` then `beq $3,2,state2` then fall-through
   return). My `if(==1){}else if(==2){}` gives `bne` fall-through. **Next lever:
   rewrite as explicit `goto state1/state2`** so the bodies are out-of-line.

## Toolchain note
Now matchable on the period assembler (ee-as 2.10) — no `la sdata`/gp_rel issues.
quick_diff CFLAGS: `-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -Iinclude`.
