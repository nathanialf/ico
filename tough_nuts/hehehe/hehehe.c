/* hehehe @ 0x001B7858 (sugipon/src/act_a_p_1) — rc2 seed.
 * Apply by replacing the `INCLUDE_ASM(..., hehehe);` line in
 * sugipon/src/act_a_p_1.c with the externs + function below, and move the
 * `DeadProc`/`D_004BA160` typedef+extern to the top of the TU (it currently
 * lives just above SetAP1DeadStatus; hehehe precedes it). See notes.md. */

extern void standAI(char *a0);
extern void updateMatrix(char *a0);
extern void *func_00105078(void);
extern void _MulMatrix(void *a0, void *a1, void *a2);
extern void func_001CCBC0(void *a0, void *a1, float a2);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_RotMatrixZ(int a0);
extern void MatrixDrive_RotMatrixX(int a0);
extern void debug_StdPrintfDummy(char *msg);
extern char D_004BA1A0[];
extern char D_004BA220[];
extern char D_00610EA0[];
extern float D_00629424;
extern float D_00629428;

void hehehe(char *self)
{
    char *geo = *(char **)(*(char **)(self + 0x15C) + 0x7F0);
    int st = *(int *)(geo + 0x8);
    int (*fp)(char *);
    char *p;
    float diff;

    switch (st) {
    default:
        if (*(int *)(geo + 0x274) < 0xA) {
            *(int *)(geo + 0x274) = *(int *)(geo + 0x274) + 1;
            walkAI(self);
            st = *(int *)(geo + 0x8);
        }
        fp = (int (*)(char *))D_004BA160[st]._4;
        *(int *)(geo + 0x8) = fp(self);
        {
            /* int-typed self->0x15C load may-aliases the int store to geo->8
             * above -> keeps the store BEFORE this reload (block-8 fix). */
            char *g2 = *(char **)((char *)*(int *)(self + 0x15C) + 0x7F0);
            int c = *(int *)(g2 + 0x270) + 1;
            *(int *)(g2 + 0x270) = c;       /* store-then-overwrite -> bne (not bnel) */
            if (c >= 0x21)
                *(int *)(g2 + 0x270) = 0;
        }
        break;
    case 5:
        *(int *)(geo + 0x8) = 4;
        break;
    case 4:
        *(int *)(geo + 0x8) = 6;
        break;
    case 7:
        break;
    case 6:                                 /* case 6 LAST -> falls through to tail */
        *(int *)(self + 0x16C) = 0;
        break;
    }

    standAI(self);
    updateMatrix(self);
    _MulMatrix(func_00105078(), *(char **)(*(char **)(self + 0x15C) + 0xC), D_004BA1A0);
    func_001CCBC0(*(char **)(geo + 0x19C), func_00105078(), 1.0f);
    if (*(int *)(geo + 0x4) != 0) {
        CopyMatrix(func_00105078(), *(char **)(*(char **)(self + 0x15C) + 0xC));
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        _MulMatrix(*(char **)(*(char **)(self + 0x15C) + 0xC), func_00105078(), D_004BA220);
    }
    p = *(char **)(self + 0x15C);
    diff = *(float *)(p + 0x54) - *(float *)(*(char **)(p + 0xC) + 0x34);
    /* volatile thresholds block dbr from speculating the lwc1 into the bc1f
     * delay slot (block-25 fix). */
    if (diff < 0.0f) {
        if (*(volatile float *)&D_00629424 < -diff)
            goto bad;
    } else {
        if (*(volatile float *)&D_00629428 < diff)
            goto bad;
    }
    return;
bad:
    *(int *)(p + 0x5E8) = 0x800;
    debug_StdPrintfDummy(D_00610EA0);
}
