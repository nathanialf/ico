extern void sceVu0Normalize(int *buf, int *buf2);
extern void atan2f(float a, float b);

void _GetDirection(int *self)
{
    float buf[4];
    buf[1] = 0.0f;
    buf[0] = *(float *)&self[0];
    buf[2] = *(float *)&self[2];
    sceVu0Normalize((int *)buf, (int *)buf);
    atan2f(buf[0], buf[2]);
}
