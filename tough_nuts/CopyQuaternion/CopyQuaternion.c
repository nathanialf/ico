/* sugipon/src/quaternion.c — CopyQuaternion parked seed (rc1).
   buf-transpose then quaternion-extract. Residual rc1: ROM emits an extra
   `daddu v0,sp` (&buf) before GetQuaternionFromMatrix — that function reads a
   HIDDEN input arg in $2/v0 (sw $2,0(sp) early; also writes via $6/a2). Standard
   C cannot pass an arg in v0, so no clean-C form produces it. Non-standard ABI.
   Apply + match_loop.py reset. */
extern void func_00118AF0(void *a0, void *a1);
extern void GetQuaternionFromMatrix(void *a0, void *a1);

void CopyQuaternion(void *a0, void *a1) {
    char buf[0x40];
    func_00118AF0(buf, a1);
    GetQuaternionFromMatrix(a0, buf);
}
