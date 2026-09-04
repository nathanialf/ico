void SetRootBaseQuaternion(int *self, int *other)
{
    func_00104D20();
    CopyMatrix(func_00105078(), (char *)self + 0x20);
    MultiMatrixByQuaternion(other);
    CopyMatrix((void *)self[0xC/4], func_00105078());
    MatrixDrive_PopMatrix();
    MultiQuaternion((void *)self[0x10/4], (char *)self + 0x60, other);
}
