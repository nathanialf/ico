#!/usr/bin/env bash
# tools/extra_cflags.sh <src/cod/FILE_OFF.c>
#
# Print any per-file CFLAGS overrides recorded in config/extra_cflags.txt
# for the given source file. The lookup key is the uppercase hex basename
# (file offset) of the .c — e.g. src/cod/0F4C00.c → key 0F4C00.
#
# Empty stdout (and exit 0) when no override exists, so the caller can
# unconditionally splice the result into a CC command:
#   $(CC) $(CFLAGS) $$(tools/extra_cflags.sh $<) -o ...
#
# This script must remain quiet on the success path — anything it writes
# to stdout is shell-substituted into the compile command line.

set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIDECAR="${ROOT}/config/extra_cflags.txt"

[ $# -eq 1 ] || { echo "usage: $0 <src/cod/<FILE_OFF>.c>" >&2; exit 2; }
[ -r "${SIDECAR}" ] || exit 0

base="$(basename "$1" .c)"
# Lookup key: basename uppercased (the file actually stores them
# uppercase, but be defensive in case of mixed-case .c filenames).
key="$(printf '%s' "${base}" | tr 'a-z' 'A-Z')"

# Match the first column exactly. Strip the leading column and any
# trailing comment, but pass the flags themselves through verbatim.
awk -v k="${key}" '
    /^[[:space:]]*#/ { next }
    /^[[:space:]]*$/ { next }
    {
        col1=$1
        if (col1 == k) {
            $1=""
            # awk leaves a leading separator after $1=""; print rest.
            sub(/^[[:space:]]+/, "")
            print
            exit
        }
    }
' "${SIDECAR}"
