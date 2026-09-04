void func_001FE1D0(void *a0, void *a1)
{
    int *sub;
    void *player = (void *)D_00629DE4;
    /* buf is a vec4 filled by two 64-bit copies and then used as floats. The
     * union types it as both so its long-long fill may-aliases the float obj
     * vec copies below — keeping the dev's store order (fill before copy) that
     * strict aliasing would otherwise reorder — instead of -fno-strict-aliasing. */
    union { long long d[2]; float f[4]; } buf;
    buf.d[0] = *(long long *)&D_006138D0[0];
    buf.d[1] = *(long long *)&D_006138D0[2];
    sub = *(int **)((char *)a0 + 0x164);
    *(float *)((char *)sub + 0x550) = *(float *)((char *)sub + 0x4A0);
    *(float *)((char *)sub + 0x554) = *(float *)((char *)sub + 0x4A4);
    *(float *)((char *)sub + 0x558) = *(float *)((char *)sub + 0x4A8);
    if (a0 == player) {
        buf.f[0] = -buf.f[0];
    }
    {
        int arg1 = ((GObj *)a1)->p_15C->f_C;
        buf.f[3] = 1.0f;
        sceVu0ApplyMatrix((char *)sub + 0x5A0, arg1, buf.f);
    }
}
