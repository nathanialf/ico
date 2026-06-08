void SetRootBaseQuaternion(int *self, int *other)
{
    func_00104D20();
    MatrixDrive_TurnXObjectMatrixYZ(func_00105078(), (char *)self + 0x20);
    func_0010E300(other);
    MatrixDrive_TurnXObjectMatrixYZ((void *)self[0xC/4], func_00105078());
    func_00105068();
    func_0010E148((void *)self[0x10/4], (char *)self + 0x60, other);
}
