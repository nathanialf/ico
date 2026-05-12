/* src/cod/160900_2609E8.c — func_002609E8 (isnan via bit-twiddle) */

int func_002609E8(float f)
{
    union { float f; int i; } u;
    u.f = f;
    return (int)((unsigned int)(0x7F800000 - (u.i & 0x7FFFFFFF)) >> 31);
}
