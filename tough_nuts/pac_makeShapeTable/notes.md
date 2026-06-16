# pac_makeShapeTable — near-miss rc15 (structure 100% correct)

Returns int. count = ((*(0x2C)&0x0FFFFFFF) - *(0x28)) >> 4. if count==1: zero
fields 0x20/0x24/0x28 (ascending source order), return 0. Else:
pac_makeMaterialTable(count); recompute n; q = (n-1)/div (div=*(0x30));
pac_getTextureInfo(a0,a1,q); pac_makeMaterialTableLine(); head=*(0x20);
*head=0; r=((c&mask)-(int)head)>>4<<4; head[1]=0 (RELOAD); D_0062BF40+=r;
D_0062BF48+=1; return r.

## SOLVED levers
- q zext (dsll32/dsrl32): `unsigned long long q = (n-1)/div` — 32-bit divu
  result widened to 64-bit zero-extends. pac_getTextureInfo 3rd arg = `unsigned
  long long`. (gcc folds the zext unless q is widened to a 64-bit dest.)
- tail reload of *(0x20) for head[1]=0: `volatile int * volatile *pp` forces the
  reload (matches EXP a2). base+0x20 is a DMA list pointer (cf. pac_makeMaterial*).
- count==1 store order: ascending 0x20,0x24,0x28.

## RESIDUAL (rc15, ~1 real instruction): v0/v1 coalescing tiebreak
EXP: head=v0, c=v1, r=v1 with a trailing `daddu v0,v1` (return move).
GOT: head=a1, c=v0, r=v0 (no move). The return value claims v0 in EVERY hand
shape (30+ tried: volatile/non-volatile head, ptr-to-array deref, explicit c
temp, store-order perms, single-return goto, struct members). head never colors
to v0 because gcc reserves v0 for the return chain. Permuter-class (regalloc).

## BREAKTHROUGH (permuter-found lever) — head→v0 cracked, now rc7
The v0/v1 coalescing IS crackable. Two permuter-found levers both put head in v0:
1. **chain** `new_var=(c&mask)-(int)head; (*pp)[1]=(*head=0); r=((unsigned)new_var>>4)<<4;`
   → rc7. head=v0. Residual: the `(*head=0)` value re-reads volatile *head (1 extra
   `lw a2,0(v0)`; stores a2 not $0) + reload hoisted early + return-move early.
   The re-read is INTRINSIC: head→v0 needs the value-dependency of (*pp)[1] on
   *head, and a non-volatile/folded 0 loses the v0 effect.
2. **do-while(0) around r** `*head=0; do{ r=((unsigned)((c&mask)-(int)head)>>4)<<4; }while(0); (*pp)[1]=0;`
   → rc11-13 (rc10 with explicit early `c=*(0x2C)` + D48-first). head=v0, CLEAN
   single reload + $0 store (no re-read), but the do-while PINS srl+sll adjacent;
   EXP interleaves the gp-load between them (`srl; lw D48; sll`). Widening or
   moving the do-while loses head→v0 (only the tight do-while around the full r
   makes r cross-BB so head wins v0 in local-alloc).
RESIDUAL: a scheduling tiebreak (reload/return placement, srl/sll interleave)
on top of head→v0. Permuter (2.9 via compile_c.sh) ran 36k iters from the rc15
seed, best score 280 (=do-while rc11); did not reach rc0. Resume: reseed permuter
from the rc7 chain or rc11 do-while; or find the clean shape giving head→v0 with
natural scheduling.

## STATUS: rc11, RIGHT LENGTH (268), head→v0 — residual is the gp-load interleave
Best matchable = do-while-r (`do{ r=((unsigned)((c&mask)-(int)head)>>4)<<4; }while(0)`)
with explicit early `c = *(int*)(base+0x2C)`. seed: pms_dowr.seed.c. 268 bytes, head→v0.
Residual (5 sites): EXP interleaves the gp-loads with the shifts in ONE BB
(`subu; lw reload; lw D40; srl; lw D48; sll`), but the do-while(0) that forces
head→v0 splits r into its own BB, so the D40-load can't land between srl and sll
(→ D40/D48 register swap a1/a0 + return-move-early cascade). The CHAIN
`(*pp)[1]=(*head=0)` gives head→v0 in ONE BB (correct interleave) but the volatile
re-read makes it 272 (1 long → can't match). So: chain=right-schedule-wrong-length,
do-while=right-length-wrong-schedule. The dev's natural code gives head→v0 in one BB
at 268 with the interleave — a single-BB head→v0 mechanism with NO extra insn that I
have not found. ~95 hand shapes + 2×36k permuter runs (from rc15 plain AND do-while-r
seeds, both plateau ~970-1170, no score 0). Likely the reload is a SPILL (plain
non-volatile head used 3×, spilled for head[1]=0 since v0 holds the return) — but the
plain version colors head→a0, not v0. RESUME: find the single-BB head→v0; or a longer
offline permuter from pms_dowr.seed.c.
