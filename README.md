# csixtyfour

Work in progress comodore64 emulator.

## Test

Deps: cc65 (for compiling test.asm)
Usage: 
```
ca65 -g test.s
ld65 -C none.cfg test.o -o test.bin
./csixtyfour test.bin
```

### Machine ROM Software
basic.bin and kernal.bin: https://github.com/mist64/c64rom
characters.bin: https://www.zimmers.net/anonftp/pub/cbm/firmware/characters/

### Documents
https://c64os.com/post/6502instructions
https://www.c64-wiki.com/wiki/Opcode
https://www.c64-wiki.com/wiki/Kernal#Functions
https://c64os.com/post/introducingthekernalrom
https://www.lemon64.com/forum/viewtopic.php?t=69297
