#!/bin/bash
find /tmp -maxdepth 1 \( -name 'permuter*' -o -name 'cc*' -o -name 'tmp*' \) ! -name 'claude-*' -exec rm -rf {} + 2>/dev/null
