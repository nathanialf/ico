void *PrintGObjID(char *a0, long long a1) {
    unsigned long long t = (unsigned int)a1;
    *(int *)(a0 + 8) = 0x53;
    *(int *)(a0 + 0) = (int)t;
    *(int *)(a0 + 4) = 0;
    *(int *)(a0 + 0xC) = 0;
    return a0 + 0x10;
}
