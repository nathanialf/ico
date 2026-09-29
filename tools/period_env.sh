#!/bin/sh
# Runs a period toolchain binary (ee-gcc 2.9-991111 and its cc1/cpp/ee-as,
# SCE's 2.10 assembler) with the obstack chunk size of the machine that built
# the game: see tools/period_obstack.c.  Builds the preload library once.
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SO="${ROOT}/build/period_obstack.so"
SRC="${ROOT}/tools/period_obstack.c"
if [ ! -f "${SO}" ] || [ "${SRC}" -nt "${SO}" ]; then
    mkdir -p "${ROOT}/build"
    TMP="${SO}.$$"
    gcc -m32 -shared -fPIC -nostdlib -o "${TMP}" "${SRC}" /lib/i386-linux-gnu/libc.so.6 && mv -f "${TMP}" "${SO}" || { rm -f "${TMP}"; echo "period_env.sh: cannot build ${SO}" >&2; exit 1; }
fi
LD_PRELOAD="${SO}${LD_PRELOAD:+:${LD_PRELOAD}}" exec "$@"
