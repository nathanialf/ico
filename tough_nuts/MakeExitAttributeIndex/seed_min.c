struct PackedLL { long long v; } __attribute__((packed));
extern struct PackedLL D_0062A6A0;
extern int GetEdgeOfFloor(void *a0);
void MakeExitAttributeIndex(void *a0) {
    *(int *)((char *)a0 + 0x94) = 0;
    *((struct PackedLL *)((char *)a0 + 0x8C)) = D_0062A6A0;
    *(int *)((char *)a0 + 0x94) = 0;
    GetEdgeOfFloor(a0);
}
