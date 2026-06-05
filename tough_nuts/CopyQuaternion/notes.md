# CopyQuaternion — parked (rc1, sugipon/src/quaternion)
2-call: func_00118AF0(buf, a1) transpose; GetQuaternionFromMatrix(a0, buf).
Residual rc1 = a missing `daddu v0,sp` (&buf) before the 2nd call. GetQuaternionFromMatrix
reads $2/v0 as a HIDDEN input arg (confirmed: sw $2,0(sp) at its start, no prior $2 set;
ends writing via $6/a2). Standard C/gcc never passes an arg in v0 → not clean-C-expressible.
~25 hand forms (buffer sizes/types, struct-return slot 0x8/0x10/0x20/0x40, func ret void*,
ptr temps, a2 passthrough) all rc1+. Likely permuter-exhausted; resume candidate for the
raw-__asm__ fallback (mirror INCLUDE_ASM) if permuter can't synthesize the v0 setup.
