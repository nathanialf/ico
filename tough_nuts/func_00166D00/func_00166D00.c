int _clipW(void *arg0, int arg1, int arg2) {
    int ret = 0;
    int i;

    for (i = 0; i < D_0062C01C; i++) {
        short *p = D_0062C020->unk18[D_006A4B40[i]];
        if (p != 0 && *p >= 0) {
            do {
                int e = D_0062C020->unk10 + (int) *p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (__ClipFloor(arg0, e, 0, 1) != 0) {
                            *(int *)((char *)arg0 + 0x88) = e;
                            ret = 1;
                            *(int *)((char *)arg0 + 0x80) = arg1;
                            *(int *)((char *)arg0 + 0x84) = arg2;
                        }
                    }
                }
                p++;
            } while (*(volatile short *)p >= 0);
        }
    }
    return ret;
}
