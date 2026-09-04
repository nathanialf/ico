void debug_Marker(int *self, int *a1, int *a2, int *a3, float t)
{
    int buf[4];
    sceVu0ScaleVector(buf, self, -1.0f);
    debug_Arrow(buf, a1, a2, a3, t, 0.0f);
}
