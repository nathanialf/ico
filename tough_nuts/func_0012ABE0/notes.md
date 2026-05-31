# func_0012ABE0 (StageAnimation) — near-miss rc8, simple-body search loop bnel-vs-bne

WORKING C (structure correct, idiom from matched sibling func_0012AD40):
  void func_0012ABE0(int key, int a1) {
      int count = *(volatile int *)&D_00633C54;   // volatile forces the reload
      int i = 0;
      char *e = (char *)D_00674058;                // stride 0x290 pointer-walk
      if (count <= 0) return;
      do {
          int *entry1 = *(int **)(e + 0x280);
          if (key == entry1[0x58 / 4]) {
              entry1[0x50 / 4] = a1;
              count = *(volatile int *)&D_00633C54; // reload on match (alias)
          }
          i++; e += 0x290;
      } while (i < count);
  }
DIFF (rc8): expected `bne a0,v0,skip; addiu i(delay-SHARED)`; built `bnel ...; addiu i(delay)` + DUP i++
in the match path. Also count/i in swapped a2/a3 (cascade of the bnel).
ROOT: the SIMPLE store body (vs sibling func_0012AD40's CALLS) makes gcc's reorg ANNUL (bnel) + duplicate i++.
Sibling matched with bne BECAUSE its call-body blocks the annul. Tried: count-first/i-first decl (no change).
NEXT: force bne (no-annul) on the simple-body loop — gcc body-dependent reorg heuristic; or permuter.
Idiom itself (volatile count + reload-on-match + pointer-walk do-while) is CORRECT.
