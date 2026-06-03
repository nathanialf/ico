float func_0025CC70(float a0) {
    union { float f; int i; } u;
    u.f = a0;
    u.i &= 0x7FFFFFFF;
    return u.f;
}
