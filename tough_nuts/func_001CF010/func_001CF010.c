/* func_001CF010 seed — best clean real_count=9. Residual: gcc copies the
   iosFree return value v0->a0 (then geo chain grabs v1, hoisting); ROM copies
   v0->v1 and reuses v1 for both the alloc stores AND the geo chain (p_830),
   with self->p_15C in a0. The v0->vN copy-target is invariant to chain typing,
   expr form, decl order, buf reuse, ptr-to-array, store reorder (31 hyps).
   Retail sibling func_001D1C78 only matched with REG("$3")/MATERIALIZE crutches
   (now forbidden). Permuter-class: alloc-result copy-target tie (cf func_001FB768
   new_var). See notes.md. */
extern int D_0062A310;
extern int *iosFree(int heap, int size, const char *file, int line);

int *func_001CF010(GObj *self, int *src) {
    int *ret = iosFree(D_0062A310, 0xC, "src/girlForceField.c", 0x17);
    float val = *(float *)((char *)src + 0x28);
    float one = 1.0f;
    int *p = ret;
    *(float *)((char *)p + 0x0) = val;
    *(int *)((char *)p + 0x8) = 0;
    val = one / val;
    *(float *)((char *)p + 0x4) = val;
    p = (int *)self->p_15C->p_830;
    *(volatile float *)((char *)p + 0x20) = one;
    *(volatile float *)((char *)p + 0x28) = one;
    *(volatile float *)((char *)p + 0x24) = one;
    return ret;
}
