## Requirements

### build
- python3
- gitpython (pip install gitpython)


## Content (folders)

### src

Folder with sources files

#### src/asm

Mads sources (the actual code), converted and adapted from MAC/65 sources
main game file: main.asm (includes other inc files) (mads -lpt main (also moverom and movepage6to9) to compile)
Mads: https://github.com/tebe6502/Mad-Assembler and https://mads.atari8.info/

#### src/data

data in txt format

#### src/graph

graphs in GM and GM2 format (GM25.COM)

#### src/music

music in CMC format (Chaos Music Composer)

#### src/sound

digitalized sounds

### build

Build tools. Use: "python3 main.py" to build (requires compiling sources from src/asm).
Generates files:
- wladca.dat - data dump file generated from processed data files (graph, music, sound) and sources from src/asm
- wladca.com - game com file file generated from processed data files (graph, music, sound) and sources from src/asm

Running generated game file (example):
- download emulator (e.g. Atari 800XLWin Plus 4.1 from: https://emutopia.com/index.php/emulators/item/320-atari-400-800-xl-xe/1180-atari800win-plus)
- boot emulator with dos.atr 
- map D1 to build.atr
- map H1 to build folder
- copy (C) game file from H1 to D1 (e.g. Datei kopieren: H1:WLADCA.COM,WLADCA.COM)
- boot emulator with build.atr
- run game file


### dist

generated wladca.com and wladca.atr


### tool

util programs


## Contact
email: old8bitpl@gmail.com
