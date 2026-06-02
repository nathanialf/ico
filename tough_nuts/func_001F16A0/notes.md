# func_001F16A0 — parked

VRAM: 0x001F16A0 (file_off 0x0F16A0)
Asm source: asm/nonmatchings/cod/0F16A0/func_001F16A0.s

## Attempt at 2026-05-31 (resume, clean-C grind to 30-stall)

**Reason parked:** genuine 30-stall (`match_loop next` = park, best=**rc1**).
Real TU is `src/sugiTree.c` (the `cod/0F16A0` .s is a stale orphan).
Seed upgraded from the non-compiling KEEP_LIVE form to a **clean rc1** form.

### Root cause: a deliberately-DEAD value the original keeps via KEEP_LIVE

The function: alloc `buf` (func_0013A0F8, 2 bytes), `*buf = (short)func_00264D60()`,
`return buf`. Plus a dead `if (v < 0) <compute v + 0xFFFF>` whose result the
original puts in `$v0` (the return reg) then UNCONDITIONALLY overwrites with buf:

```
bgez  v1,L        # if v>=0 skip
 sh   v1,0(s0)    # *buf = v  (delay, always)
ori   v0,0xFFFF
addu  v0,v1,v0    # v0 = v + 0xFFFF   <-- DEAD, overwritten below
L: daddu v0,s0,0  # v0 = buf  (both paths) -> return buf
```

ee-gcc 2.9 -O2 DCEs a dead pure computation, so plain
`if (v<0) v += 0xFFFF; return buf;` drops the bias entirely (**rc5** — the
whole bias block missing). The original kept it with `KEEP_LIVE(v+0xFFFF)`
= `asm("":: "r"(x))`, a ZERO-COST barrier that marks the value used without
emitting any instruction. That macro is retired (matching.h is a stub).

### What gets to rc1 (clean) and why rc0 needs a barrier

Storing the bias to a stack local — `if (v<0) local_pad[0] = v + 0xFFFF;` —
keeps it live AND lands it in `$v0` exactly like the original (`addu v0`),
returning buf correctly. The ONLY residual is the extra `sw v0,0(sp)` the
store emits and the original (KEEP_LIVE) lacks → **rc1**.

A memory store is the cheapest pure-C keep-alive, and it always costs one
instruction. There is no zero-cost pure-C "use a value in a register and
discard it" — that is exactly what an `asm("":: "r")` barrier is for.

### ~30 distinct clean hypotheses tried (best rc1, none rc0)

- **rc5 (bias DCE'd):** `if(v<0) v+=0xFFFF`; dead-store-then-overwrite
  (`result=biased; result=buf`); comma `(v,buf)`; algebraic identity
  `buf + biased - biased`; §4.1 store `*buf=v; if(v<0) *buf=biased` (stores
  the wrong value); condition-consumes-bias `(v<0)&&(v+0xFFFF)`.
- **rc1 (returns the bias — wrong fn, but byte-close):** `if(v<0) return
  (short*)(v+0xFFFF); return buf;`; ternary `v<0 ? biased : buf`; §4.1ret
  `ret=buf; if(v<0) ret=biased` (bias lands in s0 not v0). These RETURN the
  bias (extra `beq`/`s0`-vs-`v0`), not the original's discard.
- **rc1 (CORRECT fn — store keep-alive, the seed):** bias stored to
  local_pad[0] / [1] / `*(int*)local_pad` / volatile / temp-then-store /
  short-cast / global D_00633724 / switch / while-break — ALL land the bias
  in v0 correctly, all cost exactly one `sw`. This IS the clean floor.

### To reach rc0

Needs a zero-cost keep-alive (`asm("":: "r"(v + 0xFFFF))`-equivalent). Either
re-allow a minimal KEEP_LIVE for genuinely-dead-value casualties, or the
offline permuter explores from the clean rc1 seed. Per `next`, do NOT spend
interactive permuter tokens — `tools/auto_permute.sh` runs the seed offline.

**TU:** `src/sugiTree.c`

**Seed:** `tough_nuts/func_001F16A0/func_001F16A0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001F16A0, 0x54

glabel func_001F16A0
    /* F16A0 001F16A0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* F16A4 001F16A4 6200063C */  lui        $6, %hi(D_0061A6D8)
    /* F16A8 001F16A8 2097848F */  lw         $4, %gp_rel(D_00632010)($gp) /* gp_rel: (D_00632010) */
    /* F16AC 001F16AC D8A6C624 */  addiu      $6, $6, %lo(D_0061A6D8)
    /* F16B0 001F16B0 1000B0FF */  sd         $16, 0x10($29)
    /* F16B4 001F16B4 02000524 */  addiu      $5, $0, 0x2
    /* F16B8 001F16B8 2000BFFF */  sd         $31, 0x20($29)
    /* F16BC 001F16BC 3EE8040C */  jal        func_0013A0F8
    /* F16C0 001F16C0 0C000724 */   addiu     $7, $0, 0xC
    /* F16C4 001F16C4 5893090C */  jal        func_00264D60
    /* F16C8 001F16C8 2D804000 */   daddu     $16, $2, $0
    /* F16CC 001F16CC 2D184000 */  daddu      $3, $2, $0
    /* F16D0 001F16D0 03006104 */  bgez       $3, .L001F16E0
    /* F16D4 001F16D4 000003A6 */   sh        $3, 0x0($16)
    /* F16D8 001F16D8 FFFF0234 */  ori        $2, $0, 0xFFFF
    /* F16DC 001F16DC 21106200 */  addu       $2, $3, $2
.align 2
  .L001F16E0:
    /* F16E0 001F16E0 2D100002 */  daddu      $2, $16, $0
    /* F16E4 001F16E4 2000BFDF */  ld         $31, 0x20($29)
    /* F16E8 001F16E8 1000B0DF */  ld         $16, 0x10($29)
    /* F16EC 001F16EC 0800E003 */  jr         $31
    /* F16F0 001F16F0 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001F16A0
```

## 2026-06-01 — full procedure re-run, rc1 CONFIRMED (user: leave parked)

Re-ran the complete procedure on the rc1 seed: 30-stall hand grind (~40 distinct
DCE-defeating shapes — all DCE the bias to rc5/11 or store it to rc1/6/7),
`use_old_as` assembler check (no effect — the extra `sw` is gcc-emitted, not an
assembler-fill), and a 600s permuter shot (65k+ iterations, ZERO improvement
below rc1). Conclusively a KEEP_LIVE casualty: rc0 requires re-adding the retired
zero-cost dead-value barrier. User elected to leave it parked at rc1.
