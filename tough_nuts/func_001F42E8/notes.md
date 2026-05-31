# func_001F42E8 (weapon) — near-miss, jr-delay FP-hazard

WORKING C (rc3, ONLY the cvt placement differs):
  float func_001F42E8(char *self) {
      char *sub = *(char **)(self + 0x15C);
      int *q = *(int **)(sub + 0x800);
      int idx = q[0];
      return (float)D_006124F8[idx].field;   // E36 stride 0x24, field@0xC
  }
Built: lwc1 $f0,12(v1); jr ra; cvt.s.w $f0,$f0 (IN jr delay)
Expected: lwc1 $f0,12(v1); cvt.s.w $f0,$f0; jr ra; nop  (cvt BEFORE jr, nop delay)
ee-gcc fills the jr delay with the FP cvt; ROM keeps it before jr (FP-to-jr hazard).
Tried: named `float f=...; return f;` -> no change. No auto postprocess applies (ninja MISMATCH).
NEXT: needs the jr-delay FP-hazard nop (assembler-quirk class per reference_assembler_versions) —
either a source shape that stops gcc filling the jr delay with cvt, or an assembler-parity postprocess.
Everything else (deref chain, mult-by-0x24, table index, lwc1) is EXACT.
