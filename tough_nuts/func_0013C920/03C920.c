int *func_0013C920(int **head_ptr, int key)
{
    int *p;
    if (head_ptr == 0) return 0;
    p = *head_ptr;
    if (p == 0) return 0;
    do {
        if (p[0xA] == key) return p;
        p = (int *)p[0xD];
    } while (p != 0);
    return 0;
}
