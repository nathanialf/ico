void ACTAdjustPlane(int *self)
{
    int buf[4];
    func_00240038(buf, (int)((char *)self[0x164 / 4] + 0x4A0), -1.0f);
    dispPlane((int)self, buf);
}
