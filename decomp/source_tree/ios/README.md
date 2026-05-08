# `ios/` — recovered ICO source

I/O system — wrappers around SCE SDK libs (cdvd, pad, mc, sif).

**7 file(s)** recovered from `__FILE__` literals in `baserom/baseelf.elf` `.rodata`. Each placeholder records its anchor vma — the address of the literal that lets us tie a `.text` function back to this TU.

See `../source_tree.md` for the full recovery method.

## Files

- `cdvd.c` — anchor 0x00556818
- `inflate.c` — anchor 0x00556b00
- `mblock.c` — anchor 0x00556c08
- `memory.c` — anchor 0x005570e0
- `message.c` — anchor 0x00557540
- `pad.c` — anchor 0x005576b8
- `thread.c` — anchor 0x005578d0
