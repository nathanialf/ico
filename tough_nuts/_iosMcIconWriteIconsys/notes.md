# _iosMcIconWriteIconsys (fumi/ios/mcdata) — parked rc3 (stall=30 + permuter)

h->w[1]=7; *(ll*)a0 &= -2; return iosMsgSend(D_0027D308, a0, 0, -2).
- Union member typing (long long ll; int w[2]) keeps the int store before the
  overlapping ll load (rc14->rc3). int return defeats the void tail-call (jal+frame).
- rc3 residual: ROM reuses the a3(-2) iosMsgSend arg reg for the AND mask; gcc
  materializes -2 twice (t0 for AND, a3 for arg). ~30 distinct const-reuse forms
  (int/long/uint/~1/0xFF.. /register/two-temp/volatile/do-while) all rc3.
- Permuter (base 110): best output-10-1 = rc2 but UB (passes an UNINITIALIZED var
  as the 4th arg, relying on the leftover -2 reg); still has the t0/a3 diff. Broken
  mutation, rejected (cf func_0024E510 swapped-logic). Nothing clean below rc3.
- RESUME: the -2 coalescing is the const-reg-reuse tiebreak class; needs a clean
  form that makes gcc keep -2 in a3 across the AND. Seed = the union rc3 form.
