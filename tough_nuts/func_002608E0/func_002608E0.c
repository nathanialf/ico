float func_002608E0(float x)
{
    union { float f; int i; } u;
    u.f = x;
    u.i &= 0x7FFFFFFF;
    return u.f;
}
