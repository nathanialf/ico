# CopyQuaternion — parked (b) rc1

VRAM 0x0010DB88. Local-buffer wrapper (like _ACTMotDirSmzDirect / MatrixDrive):
a0 saved in s0; func_00118AF0(local, a1) fills a 0x40 stack buffer (sp+0);
GetQuaternionFromMatrix(a0, local) reads it.

## Pass 2 (2026-06-08): empty seed -> rc1
Best clean form (void, no return) misses ONE insn: ROM emits `daddu v0,sp`
(redundant &local into v0) BEFORE the GetQ call. `return local` adds v0=sp but
at the END (rc2, wrong position). Permuter (180s, no mode-TI) found NO rc0.
RESUME: the v0=sp-before-GetQ is a regalloc artifact — try func_00118AF0 returning
void* (the buffer) reused as GetQ's arg + returned; or a 3rd local materialization.
