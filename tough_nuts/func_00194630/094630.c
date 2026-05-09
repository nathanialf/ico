extern void func_00243978(int *buf, int *buf2);
extern void func_0025E5D8(float a, float b);

void func_00194630(int *self)
{
    float buf[4];
    buf[0] = *(float *)&self[0];
    *(int *)&buf[1] = 0;
    buf[2] = *(float *)&self[0x8 / 4];
    func_00243978((int *)buf, (int *)buf);
    func_0025E5D8(buf[0], buf[2]);
}
