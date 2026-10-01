# Progress

The share of each section of the PAL boot ELF that the rebuilt ELF holds identical to the base, and where those bytes come from: the tracked sources, or the data-only members generated at build time from the user's disc. The table between the markers is rewritten by `tools/check_elf.py --progress` (`tools/build.sh progress`); do not edit it by hand.

<!-- progress:begin -->
| Section | From source | From the disc | Total bytes | Source % | Identical % |
| --- | ---: | ---: | ---: | ---: | ---: |
| `.text` | 1612740 | 0 | 1612740 | 100.00 % | 100.00 % |
| `.vutext` | 20704 | 0 | 20704 | 100.00 % | 100.00 % |
| `.data` | 2086880 | 790080 | 2876960 | 72.54 % | 100.00 % |
| `.rodata` | 91547 | 872829 | 964376 | 9.49 % | 100.00 % |
| `.lit4` | 4436 | 0 | 4436 | 100.00 % | 100.00 % |
| `.sdata` | 9326 | 8 | 9334 | 99.91 % | 100.00 % |
| `.sbss` (owned) | 1240 | 4 | 1244 | 99.68 % | 100.00 % |
| `.bss` (owned) | 1022872 | 0 | 1022872 | 100.00 % | 100.00 % |

**From source** counts the bytes placed by an object compiled or assembled from a tracked source under `ico2/` or `sce/`. **From the disc** counts the bytes of the data-only archive members (`config/data_members.pal.txt`), which the build generates from the user's own base ELF: as C for the members `config/data_schema.pal.txt` lists (`tools/gen_data_c.py`) and as assembly for the rest (`tools/extract_data.py`); none of their content is in the repository. **Identical** is their sum, the share of the section equal to the base, which the gate requires to be 100 % for every section with file bytes.

`.sbss` and `.bss` are NOBITS: they hold no ROM bytes, so their figure is **ownership**, how much of the section an object defines and the link places at the base's addresses. A section the ELF sizes at zero (`.vudata` on this target) is omitted.
<!-- progress:end -->

Per-directory, per-TU and per-function breakdowns are on the progress dashboard
(`docs/index.html` reading `docs/progress.json`, which `tools/check_elf.py --progress`
writes); the link is at the top of `README.md`.
