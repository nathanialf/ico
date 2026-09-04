char *nearest_waypoint_by_lineseg(int *arg0, int handle)
{
    int buf[4];
    char *result;
    char *node;
    float best;
    result = WayPointList_begin(handle);
    best = 100000.0f;
    node = result;
    if (result != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(node + 0x10), arg0);
            d = func_00168128((int)buf);
            if (d < best) {
                best = d;
                result = node;
            }
            node = WayPointList_next(node);
        } while (node != 0);
    }
    return result;
}
