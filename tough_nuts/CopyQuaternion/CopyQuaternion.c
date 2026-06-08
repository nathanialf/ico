/* sugipon/src/quaternion.c — CopyQuaternion parked seed (rc1).
   Local-buffer wrapper (like _ACTMotDirSmzDirect). func_00118AF0(local, a1)
   fills a 0x40 stack buffer, GetQuaternionFromMatrix(a0, local) reads it.
   Residual rc1: ROM has an extra `daddu v0,sp` (redundant &local into v0) BEFORE
   the GetQ call; gcc omits it (void) or emits it at the wrong spot (return local
   -> v0=sp at end, rc2). Permuter target (no mode-TI). */
extern void func_00118AF0(void *a0, void *a1);
extern void GetQuaternionFromMatrix(void *a0, void *a1);

void CopyQuaternion(void *a0, void *a1) {
    char local[0x40];
    func_00118AF0(local, a1);
    GetQuaternionFromMatrix(a0, local);
}
