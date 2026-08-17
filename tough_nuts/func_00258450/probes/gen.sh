#!/bin/bash
cd /primary/dev/ico/scratchpad/n450b
for f in b/*.c; do
  n=$(basename $f .c)
  if ./cc.sh -o b/$n.s $f 2>b/$n.err; then
    body=$(awk '/\.ent/,/\.end/' b/$n.s | grep -P '^\t[a-z]' | grep -v '^\t\.' | sed 's/\t/ /g;s/  */ /g;s/#.*//' | paste -sd'|' -)
    printf '%-8s %s\n' "$n" "$body"
  else
    printf '%-8s ERR %s\n' "$n" "$(head -1 b/$n.err)"
  fi
done
