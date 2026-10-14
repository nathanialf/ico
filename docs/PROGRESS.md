# Progress

The share of each section of the Japanese boot ELF that the rebuilt ELF holds identical to the base, and where those bytes come from: the tracked sources, or the data-only members and the campaign stubs generated at build time from the user's disc. The table between the markers is rewritten by `tools/check_elf.py --progress` (`tools/build.sh progress`); do not edit it by hand.

<!-- progress:begin -->
| Section | From source | From the disc | Total bytes | Source % | Identical % |
| --- | ---: | ---: | ---: | ---: | ---: |
| `.text` | 1536696 | 67612 | 1604308 | 95.79 % | 100.00 % |
| `.vutext` | 20704 | 0 | 20704 | 100.00 % | 100.00 % |
| `.data` | 2086912 | 778872 | 2865784 | 72.82 % | 100.00 % |
| `.rodata` | 89628 | 868780 | 958408 | 9.35 % | 100.00 % |
| `.lit4` | 4028 | 232 | 4260 | 94.55 % | 100.00 % |
| `.sdata` | 9089 | 141 | 9230 | 98.47 % | 100.00 % |
| `.sbss` (owned) | 1244 | 0 | 1244 | 100.00 % | 100.00 % |
| `.bss` (owned) | 1022360 | 0 | 1022360 | 100.00 % | 100.00 % |

**From source** counts the bytes placed by an object compiled or assembled from a tracked source under `ico2/` or `sce/`. **From the disc** counts the bytes of the data-only archive members (`config/data_members.jpn.txt`), which the build generates from the user's own base ELF as C from the record types and names in `config/data_schema.jpn.txt` (`tools/gen_data_c.py`), and the functions and data runs `config/stubs.jpn.txt` lists, which a translation unit still includes from the base ELF while its C is unfinished (`tools/gen_stub_s.py`); none of their content is in the repository. Linker fill counts with the object it follows. **Identical** is their sum, the share of the section equal to the base, which the gate requires to be 100 % for every section with file bytes.

`.sbss` and `.bss` are NOBITS: they hold no ROM bytes, so their figure is **ownership**, how much of the section an object defines and the link places at the base's addresses. A section the ELF sizes at zero (`.vudata` on this target) is omitted.
<!-- progress:end -->

Per-directory, per-TU and per-function breakdowns are on the progress dashboard
(`docs/index.html` reading `docs/progress.json`, which `tools/check_elf.py --progress`
writes); the link is at the top of `README.md`.
