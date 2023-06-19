
## Content (folders)

### archived

Folder containing archived content (no longer need to work on)

#### archived/atr

Original content from atari disks (requires cleaning)

#### archived/atr.extracted

Extracted files from original atari disks

#### archived/src/m65

MAC/65 sources (the actual code)
main game file: MAIN.M65 (includes other INC files. Checkout should be on H1:)
(ASM,,#H1:MAIN.OBJ to compile)

#### archived/com
original WLADCA.COM game file


### src

Folder with categorized files

#### src/asm

Mads sources (the actual code), converted and adapted from MAC/65 sources
main game file: main.asm (includes other inc files) (mads -lpt main to compile)
Mads: https://github.com/tebe6502/Mad-Assembler and https://mads.atari8.info/

#### src/graph

graphs in GM and GM2 format (GM25.COM)

#### src/music

music in CMC format (Chaos Music Composer)

#### src/sound

digitalized sounds

#### src/build

built data (without code)

#### src/tool

util programs
as to MAC/65 - please download it from: https://atariwiki.org/wiki/Wiki.jsp?page=Mac65

#### src/tbd

others files to be processed


### build

Build tools. Use: "python3 main.py" to build (requires compiling sources from src/asm).
Generates files:
- o_wladca.dat - data dump file generated from original data files (RAM.COM, ROM.COM) and sources from src/asm
- o_wladca.com - game com file file generated from original data files (RAM.COM, ROM.COM) and sources from src/asm
- wladca.dat - data dump file generated from processed data files (graph, music, sound) and sources from src/asm
- wladca.com - game com file file generated from processed data files (graph, music, sound) and sources from src/asm


## Contact
email: old8bitpl@gmail.com

