void func_0010ACC8(float *dst, float *a, float *b, float t)
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}
