void func_00117C98(void) {
    __asm__ __volatile__(
        "vlqd.xyzw $vf7, (--$vi15)\n\tvlqd.xyzw $vf6, (--$vi15)\n\tvlqd.xyzw $vf5, (--$vi15)\n\tvlqd.xyzw $vf4, (--$vi15)\n\tnop"
        : : : "memory"
    );
}
