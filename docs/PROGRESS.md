# Progress

The share of each section of the PAL boot ELF that the build reproduces. The table between the markers is rewritten by `tools/check_elf.py --progress` (`tools/build.sh progress`); do not edit it by hand.

<!-- progress:begin -->
| Section | From C | Extracted tables | Total bytes | C % | Identical % |
| --- | ---: | ---: | ---: | ---: | ---: |
| `.text` | 1612740 | 0 | 1612740 | 100.00 % | 100.00 % |
| `.vutext` | 20704 | 0 | 20704 | 100.00 % | 100.00 % |
| `.data` | 2086880 | 790080 | 2876960 | 72.54 % | 100.00 % |
| `.rodata` | 91530 | 872846 | 964376 | 9.49 % | 100.00 % |
| `.lit4` | 4436 | 0 | 4436 | 100.00 % | 100.00 % |
| `.sdata` | 9326 | 8 | 9334 | 99.91 % | 100.00 % |
| `.sbss` (owned) | 1240 | 4 | 1244 | 99.68 % | 100.00 % |
| `.bss` (owned) | 1022872 | 0 | 1022872 | 100.00 % | 100.00 % |

**From C** counts the bytes placed by an object compiled or assembled from a source under `ico2/` or `sce/`. **Extracted tables** counts the bytes of the data-only archive members, which the build writes out of the user's own base ELF (`tools/extract_data.py`, rows in `config/data_members.pal.txt`) instead of from committed source. **Identical** is their sum: the share of the section equal to the base.

`.sbss` and `.bss` are NOBITS: they hold no ROM bytes, so their figure is **ownership**, how much of the section a compiled C object defines and the link seats at the ROM's VMAs, not reproduced bytes. A section the ELF sizes at zero (`.vudata` on this target) is omitted.
<!-- progress:end -->

Per-directory, per-TU and per-function breakdowns are on the progress dashboard
(`docs/index.html` reading `docs/progress.json`, which `tools/check_elf.py --progress`
writes); the link is at the top of `README.md`.
