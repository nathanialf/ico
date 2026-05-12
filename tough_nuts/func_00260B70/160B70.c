/* src/cod/160B70.c — func_00260B70 */

float func_00260B70(float a, float b)
{
    union { float f; int i; } ua;
    union { float f; int i; } ub;
    union { float f; int i; } ur;
    ua.f = a;
    ub.f = b;
    ur.i = (ua.i & 0x7FFFFFFF) | (ub.i & 0x80000000);
    return ur.f;
}
