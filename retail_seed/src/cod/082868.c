float func_00182868(void *a0, void *a1)
{
    if (*(void **)((char *)a0 + 4) == a1) {
        return *(float *)((char *)a1 + 4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 4);
}
