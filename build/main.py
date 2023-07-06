#!/usr/bin/python3

from processor.core import BuildOutput, BinOutput, GmSrcFileProcessor, DataSrcFileProcessor, BinSrcFileProcessor, \
    SrcFileProcessor
from processor.processors.battle_graph_processor import BattleGraphProcessor
from processor.processors.catapult_ball_trajectories_processor import CatapultBallTrajectoriesProcessor
from processor.processors.country_names_processor import CountryNamesProcessor
from processor.processors.death_graph_processor import DeathGraphProcessor
from processor.processors.map_graph_processor import MapGraphProcessor
from processor.processors.mirage_graph_processor import MirageGraphProcessor
from processor.processors.gameover_win_graph_processor import GameOverWinGraphProcessor
from processor.processors.catapult_graph_processor import CatapultGraphProcessor
from processor.processors.player_names_processor import PlayerNamesProcessor
from processor.processors.tournament_graphs_processor import TournamentGraphsProcessor
from processor.processors.wallbreach_graph_processor import WallBreachGraphProcessor
from processor.processors.scream_sound_processor import ScreamSoundProcessor
from processor.mem_map import MIRAGEPIC, CZOLOPIC, MAPAPIC, BITWAPIC, ZAMEK1PIC, ZAMEK2PIC, SPISEKPIC, \
    WINTURNIEJPIC, KONIECPIC, CHARGEN, KATANIMBUF, MURANIMBUF, KRZYKDAT, SOJPIC, TARCZAPIC, TARCZAFAZATAB, FLAGAFAZATAB, \
    NAMPLDAT, NAMKSTAB, DOCHTAB, SHIELDTAB, FLAGTAB, NEARTAB, TERTAB, LOTDAT, MAPANIMDAT, TRUPPICDAT


def main():
    ###### main build

    output = BuildOutput()

    # mirage pic
    MirageGraphProcessor('../src/graph/mirage.pic', MIRAGEPIC).process(output)

    # start pic
    GmSrcFileProcessor('../src/graph/czolo.gm', CZOLOPIC).process(output)

    # map pic
    MapGraphProcessor('../src/graph/mapa.gm2', MAPAPIC, MAPANIMDAT).process(output)

    # battle pic
    BattleGraphProcessor('../src/graph/bitwa.gm', BITWAPIC).process(output)

    # sojpic/manbuf
    GmSrcFileProcessor('../src/graph/sojpic.gm', SOJPIC).process(output)

    # castle 1 pic
    GmSrcFileProcessor('../src/graph/zamek1.gm2', ZAMEK1PIC).process(output)

    # castle 2 pic
    GmSrcFileProcessor('../src/graph/zamek2.gm2', ZAMEK2PIC).process(output)

    # conspiracy pic
    GmSrcFileProcessor('../src/graph/spisek.gm', SPISEKPIC).process(output)

    # shield pic
    TournamentGraphsProcessor('../src/graph/tarcza1.gm2', '../src/graph/tarcza2.gm', '../src/graph/tarcza3.gm',
                              TARCZAPIC, TARCZAFAZATAB, FLAGAFAZATAB).process(output)

    # win tournament pic
    GmSrcFileProcessor('../src/graph/tarczwin.gm', WINTURNIEJPIC).process(output)

    # music dat
    BinSrcFileProcessor('../src/music/wladca.cmc').process(output)

    # music player
    BinSrcFileProcessor('../src/music/wladca.rep').process(output)

    # game over death pic
    DeathGraphProcessor('../src/graph/trup.gm', TRUPPICDAT).process(output)

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

    # player names
    PlayerNamesProcessor('../src/data/players.txt', NAMPLDAT).process(output)

    # country names
    CountryNamesProcessor(
        '../src/data/countries.txt', NAMKSTAB, DOCHTAB, SHIELDTAB, FLAGTAB, NEARTAB, TERTAB).process(output)

    # catapult ball trajectories
    CatapultBallTrajectoriesProcessor('../src/data/catapult_ball_trajectories.txt', LOTDAT).process(output)

    # game code
    BinSrcFileProcessor('../src/asm/main.obx').process(output)

    # moverom code
    moverom_code = (SrcFileProcessor('../src/asm/moverom.obx', None).process(None))[2:]

    # movepage6to9 code
    movepage6to9_code = (SrcFileProcessor('../src/asm/movepage6to9.obx', None).process(None))[2:]


    ##### main generating artifacts
    output.export("wladca.dat")

    bin_output = BinOutput(output, moverom_code, movepage6to9_code)
    bin_output.export("wladca.com")


if __name__ == "__main__":
    main()
