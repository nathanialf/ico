/* sugipon/src/matrixDrive.c — MatrixDrive_GetTurnXAngleYZ parked seed (rc7).
   FRESH near-miss 2026-06-08. Structure CORRECT: save the qword at obj+0x30 to a
   stack temp, call func_002400F8(a0), restore obj+0x30. Residual rc7 = three
   regalloc/addressing/scheduling micro-diffs:
     (1) ROM `addiu s0,a0,0x30` (materialize the pointer) vs gcc `daddu s0,a0` +
         48-byte displacement on the lq/sq;
     (2) ROM scratch qword reg = a2 vs gcc v0;
     (3) ROM leaves the jal delay slot a nop and emits the stack-save `sq` AFTER
         the call; gcc fills the delay with the `sq`.
   ~30 distinct shapes (ptr/array/struct-member/deref; char*/void*/long arg;
   scalar/array tmp) all rc7. mode(TI) qword => the permuter strips TI (cf.
   func_00118E38) and can't fairly explore the lq/sq coloring.
   Apply this func in place of the INCLUDE_ASM stub (it sits BETWEEN the VU0-asm
   block above and MatrixDrive_GetTurnYAngleXZ below — do NOT delete siblings!),
   then: match_loop.py reset MatrixDrive_GetTurnXAngleYZ --reason "resume". */
typedef int Qw128 __attribute__((mode(TI)));
typedef struct { char pad[0x30]; Qw128 q; } MatDrive;
extern void func_002400F8(void *);

void MatrixDrive_GetTurnXAngleYZ(MatDrive *a0) {
    Qw128 tmp[1];
    tmp[0] = a0->q;
    func_002400F8(a0);
    a0->q = tmp[0];
}
