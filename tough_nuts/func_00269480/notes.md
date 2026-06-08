# func_00269480 — fdlibm isnan(double bits in a long long)

VRAM 0x00269480. `int isnan` bit-trick: lx=(int)x; hx=(int)(x>>32);
hx&=0x7fffffff; hx|=(unsigned)(lx|-lx)>>31; hx=0x7ff00000-hx; return (unsigned)hx>>31.
Residual rc4 = a single sched2 reorder: ROM extracts hx (`dsra32 a0,a0`) right
after lx (pos 3); gcc delays it to pos 5 (after the 0x7fffffff const-load + negu).
~30 source forms (extraction order, temps, uint, double-arg-via-cast) all rc4.
sched2 tie — permuter target.
## Fire 9: re-attack rc4 hx-extract sched2 tie; sub-split/neg/mask/decl ~30 forms all rc4+; 100s permuter no rc0. (b)
