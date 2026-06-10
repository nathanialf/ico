#!/usr/bin/env bash
# tools/probe_compiler.sh <ee-gcc-dir>
#
# Two-probe compiler-fingerprint test for the arg-order cluster
# (project_arg_order_compiler_fingerprint) + the func_001F8848 fold.
#
# Probe A (reg_dispLine site): dpk_Init(2, D, 4) after a void call.
#   PASS = const a0=2 emitted LAST (lands in the jal delay slot):
#          lui a1 / li a2,4 / addiu a1,%lo / jal / [li a0,2]
# Probe B (func_001F8848): plain-int idx+1 indexed load.
#   PASS = plain `sll _,_,2` + `lw _,4(_)` disp-fold, NO sll/sra
#          sign-extend pair, AND no (idx+1)*4 pre-scale.
#
# A compiler that passes both is a candidate for the 121-site cluster;
# follow up with the full-ELF regression:
#   EEGCC_DIR=<dir> tools/build.sh clean-rebuild-compare (see notes).
set -eu
DIR="$(cd "$1" && pwd)"
LIB=$(ls -d "$DIR"/gcc-lib/ee/*/ 2>/dev/null | head -1)
[ -n "$LIB" ] || LIB=$(ls -d "$DIR"/lib/gcc-lib/ee/*/ 2>/dev/null | head -1)
CC="$DIR/ee-gcc"
[ -x "$CC" ] || CC="$DIR/bin/ee-gcc"
CFLAGS="-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc"

T=$(mktemp -d)
trap 'rm -rf "$T"' EXIT

cat > "$T/a.c" <<'EOF'
extern void dpk_SwapBuffer(void);
extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);
extern char D_0054FBE0[];
void reg_dispLine(void) {
    dpk_SwapBuffer();
    dpk_Init(2, D_0054FBE0, 4);
    dl_GetPri();
}
EOF
cat > "$T/b.c" <<'EOF'
extern int D_004C3850[];
void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    D_004C3850[0] = idx;
    D_004C3850[4] = D_004C3850[idx + 1];
    D_004C3850[5] = 0;
    D_004C3850[6] = 0;
    D_004C3850[7] = 0;
}
EOF

echo "== $DIR"
if ! "$CC" -B "$LIB" $CFLAGS "$T/a.c" -o "$T/a.s" 2>"$T/a.err"; then
    echo "probe A: COMPILE FAILED"; head -2 "$T/a.err"; exit 1
fi
# delay-slot occupant = insn on the line after `jal dpk_Init`
A_DELAY=$(awk '/jal\tdpk_Init/{getline; print; exit}' "$T/a.s" | tr -s '\t ' ' ')
case "$A_DELAY" in
    *'$4,2'*|*'li $4,0x2'*) echo "probe A: PASS  (delay = a0=2:$A_DELAY)";;
    *) echo "probe A: fail  (delay =$A_DELAY)";;
esac

if ! "$CC" -B "$LIB" $CFLAGS "$T/b.c" -o "$T/b.s" 2>"$T/b.err"; then
    echo "probe B: COMPILE FAILED"; head -2 "$T/b.err"; exit 1
fi
B_BODY=$(sed -n '/func_001F8848:/,/\.end/p' "$T/b.s")
HAS_SLL2=$(echo "$B_BODY" | grep -cE 'sll[[:space:]]+\$[0-9]+,\$[0-9]+,2$' || true)
HAS_SEXT=$(echo "$B_BODY" | grep -cE '(sll|sra)[[:space:]]+.*,(16|14)$' || true)
HAS_DISP4=$(echo "$B_BODY" | grep -cE 'lw[[:space:]]+\$[0-9]+,4\(' || true)
if [ "$HAS_SLL2" -ge 1 ] && [ "$HAS_DISP4" -ge 1 ] && [ "$HAS_SEXT" -eq 0 ]; then
    echo "probe B: PASS  (plain sll2 + disp-fold, no sext)"
else
    echo "probe B: fail  (sll2=$HAS_SLL2 disp4=$HAS_DISP4 sext=$HAS_SEXT)"
fi
