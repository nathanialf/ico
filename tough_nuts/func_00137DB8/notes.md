# func_00137DB8 (fumi/ios/mcdata) — parked rc3 (stall=30 + permuter) (b)

TWIN of _iosMcIconWriteIconsys (writes 8 not 7). Same shape:
  h->w[1]=8; *(ll*)a0 &= -2; return iosMsgSend(D_0027D308, a0, 0, -2);
- union {long long ll; int w[2];} keeps the int store before the overlapping ll
  load; int return defeats the void tail-call (jal+frame). -> rc3.
- rc3 residual = the -2 register-coalescing tiebreak: ROM reuses the a3 (iosMsgSend
  4th-arg) reg for the AND mask; gcc materializes -2 twice (t0 for AND, a3 for arg).
  ~30 forms incl long-long arg all rc3. Permuter (base 110): only score-100 outputs
  = rc5 (worse, anti-correlated); nothing below rc3.
- SIBLINGS func_00137E00 / func_00137ED8 / func_00137F20 are the SAME family (same
  -2 floor, only the w[1] constant + msg constants differ) — apply the union+int-
  return seed, they'll park rc3 unless a clean -2-reuse lever is found.
