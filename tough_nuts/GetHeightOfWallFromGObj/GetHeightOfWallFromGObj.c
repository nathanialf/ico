extern void GetRootMatrixByDObj(int *a0);

void GetHeightOfWallFromGObj(int *a0, int **a1) {
    GetRootMatrixByDObj(a0);
    *(float *)((char *)a0 + 0x4) += *(float *)((char *)a1[0x57] + 0x260);
}
