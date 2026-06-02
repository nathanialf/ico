int func_0017D0F8(int *a0)
{
    int *p;
    int v0;
    if (a0 == 0) goto fail;
    p = (int *)a0[0xB];
    if (p == 0) goto fail;
    v0 = p[0xA];
    if (v0 != 0) goto succ;
fail:
    return 0;
succ:
    return 1;
}
