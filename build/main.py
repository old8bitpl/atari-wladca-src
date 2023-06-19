#!/usr/bin/python3

from processor.core import BuildOutput, BinOutput, GmSrcFileProcessor, DataSrcFileProcessor, BinSrcFileProcessor, \
    SrcFileProcessor
from processor.processors.mirage_graph_processor import MirageGraphProcessor
from processor.processors.gameover_win_graph_processor import GameOverWinGraphProcessor
from processor.processors.catapult_graph_processor import CatapultGraphProcessor
from processor.processors.wallbreach_graph_processor import WallBreachGraphProcessor
from processor.processors.scream_sound_processor import ScreamSoundProcessor
from processor.mem_map import MIRAGEPIC, CZOLOPIC, MAPAPIC, BITWAPIC, ZAMEK1PIC, ZAMEK2PIC, SPISEKPIC, \
    WINTURNIEJPIC, KONIECPIC, CHARGEN, KATANIMBUF, MURANIMBUF, KRZYKDAT


def main():

    ###### orig build
    orig_output = BuildOutput()

    # orig ROM
    orig_rom = (SrcFileProcessor('../archived/build/ROM.COM', None).process(None))[4:]
    orig_output.put(0xc000, orig_rom[0x0000: 0x1000])
    orig_output.put(0xd800, orig_rom[0x1000:])

    # orig RAM
    orig_ram = (SrcFileProcessor('../archived/build/RAM.COM', None).process(None))[4:]
    orig_output.put(0x4c40, orig_ram[0x0000:])

    # orig game code
    BinSrcFileProcessor('../archived/src/m65/MAIN.OBJ').process(orig_output)


    ###### main build

    output = BuildOutput()

    # mirage pic
    MirageGraphProcessor('../src/graph/mirage.pic', MIRAGEPIC).process(output)

    # start pic
    GmSrcFileProcessor('../src/graph/czolo.gm', CZOLOPIC).process(output)

    # map pic
    GmSrcFileProcessor('../src/graph/mapa.gm2', MAPAPIC).process(output)

    # battle pic
    GmSrcFileProcessor('../src/graph/bitwa.gm', BITWAPIC).process(output)

    # sojpic/manbuf
    # TODO

    # castle 1 pic
    GmSrcFileProcessor('../src/graph/zamek1.gm2', ZAMEK1PIC).process(output)

    # castle 2 pic
    GmSrcFileProcessor('../src/graph/zamek2.gm2', ZAMEK2PIC).process(output)

    # conspiracy pic
    GmSrcFileProcessor('../src/graph/spisek.gm', SPISEKPIC).process(output)

    # shield pic
    # TODO

    # win tournament pic
    GmSrcFileProcessor('../src/graph/tarczwin.gm', WINTURNIEJPIC).process(output)

    # music dat
    BinSrcFileProcessor('../src/music/wladca.cmc').process(output)

    # music player
    BinSrcFileProcessor('../src/music/wladca.rep').process(output)

    # game over death pic
    # TODO

    # game over win pic
    GameOverWinGraphProcessor('../src/graph/koniec.scr', KONIECPIC).process(output)

    # char generator
    DataSrcFileProcessor('../src/graph/chargen.dat', CHARGEN).process(output)

    # catapult anim
    CatapultGraphProcessor('../src/graph/zamek1.gm2', KATANIMBUF).process(output)

    # wall breach anim
    WallBreachGraphProcessor('../src/graph/zamek1.gm2', MURANIMBUF).process(output)

    # scream sound data
    ScreamSoundProcessor('../src/sound/krzyk.dat', KRZYKDAT).process(output)

    # game code
    BinSrcFileProcessor('../src/asm/main.obx').process(output)

    # moverom code
    moverom_code = (SrcFileProcessor('../src/asm/moverom.obx', None).process(None))[2:]

    # movepage6to9 code
    movepage6to9_code = (SrcFileProcessor('../src/asm/movepage6to9.obx', None).process(None))[2:]


    ##### orig generating artifacts
    orig_output.export("o_wladca.dat")

    bin_orig_output = BinOutput(orig_output, moverom_code, movepage6to9_code)
    bin_orig_output.export("o_wladca.com")



    ##### main generating artifacts
    output.export("wladca.dat")

    bin_output = BinOutput(orig_output, moverom_code, movepage6to9_code)
    bin_output.export("wladca.com")



    ##### generating orig/main diff
    with open("diff.log", 'w') as fh:
        for i in range(0x900, 0x10000):
            orig_byte = orig_output.get_byte(i).hex()
            new_byte = output.get_byte(i).hex()
            if orig_byte != new_byte:
                fh.write("{}\t{}\t{}\n".format(hex(i), orig_byte, new_byte))



if __name__ == "__main__":
    main()
