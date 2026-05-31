# func_0012FCE0 (Texture) — near-miss, find-bit-position loop, entry-compare encoding

Semantics: ret=-1; if(a0<=1) ret=0; else find smallest i in [1,11) with (1<<i)>=a0 -> ret=i (else -1).
BEST C (loop body + bnel + tail EXACT):
  int func_0012FCE0(int a0){ int ret=-1; if(1<a0){ for(i=1;i<11;i++) if((1<<i)>=a0){ret=i;break;} } else ret=0; return ret; }
Loop matches: slti i<11; sllv 1<<i; slt; bnel loop(i++ in delay); daddu ret=i; tail daddu v0,a1.
ONLY diff: ENTRY compare. Expected `addiu v0,1; slt v0,v0,a0; bnez ->loop-start` (1<a0, 1 materialized, branch TO body).
Built `slti a0,2; bne ->else` (folded immediate, branch TO else). Same condition, opposite branch + slti-vs-slt.
Tried: if/else (slti, branch-to-else), two-return (double compare), `i+1<a0` (slt but DOUBLE compare).
gcc folds literal `1<a0`->slti when branching to adjacent else; uses `slt 1,a0` when branching forward to loop-start.
NEXT: force gcc to branch to the loop-start (body) on (1<a0) keeping 1 in a reg; or permuter.
