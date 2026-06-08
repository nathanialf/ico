int func_00138100(int *a0, int a1)
{
    iosMcHandlerWrite(a0, a1, 0x63FC);
    D_00274EEC_a[0] = ((Elem_001383F8 *) D_0027CFE0)[a0[0x8 / 4]].f140;
    soundAllocIopHeap(((Elem_001383F8 *) D_0027CFE0)[a0[0x8 / 4]].f144);
    {
        int i = a0[0x8 / 4];
        int v = ((Elem_001383F8 *) D_0027CFE0)[i].f148;
        *(Blk40_001383F8 *) D_0027D500 =
            *(Blk40_001383F8 *) (D_0027CFE0 + 0x14C + i * 0x18C);
        D_0062A410 = v;
    }
    return a0[0x10 / 4];
}
