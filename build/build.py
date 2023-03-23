#!/usr/bin/python3

from processor.core import BuildOutput, GmSrcFileProcessor
from processor.processors.zamek1_graph_processor import Zamek1GraphProcessor
from processor.processors.mirage_graph_processor import MirageGraphProcessor
from processor.processors.koniec_graph_processor import KoniecGraphProcessor
from processor.mem_map import MIRAGEPIC, CZOLOPIC, BITWAPIC, ZAMEK1PIC, ZAMEK2PIC, SPISEKPIC, WINTURNIEJPIC, KONIECPIC


def main():
    output = BuildOutput()

    # mirage pic
    MirageGraphProcessor('../src/graph/mirage.pic', MIRAGEPIC).process(output)

    # czolo pic
    GmSrcFileProcessor('../src/graph/czolo.gm', CZOLOPIC).process(output)

    # mapa pic
    # TODO

    # bitwa pic
    GmSrcFileProcessor('../src/graph/bitwa.gm', BITWAPIC).process(output)

    # sojpic/manbuf
    # TODO

    # zamek 1 pic + katapulta + wyrwa w murze
    Zamek1GraphProcessor('../src/graph/zamek1.gm2', ZAMEK1PIC).process(output)

    # zamek 2 pic
    GmSrcFileProcessor('../src/graph/zamek2.gm2', ZAMEK2PIC).process(output)

    # spisek pic
    GmSrcFileProcessor('../src/graph/spisek.gm', SPISEKPIC).process(output)

    # tarcza pic
    # TODO

    # win turniej pic
    GmSrcFileProcessor('../src/graph/tarczwin.gm', WINTURNIEJPIC).process(output)

    # muzyka dat
    # TODO

    # trup pic
    # TODO

    # koniec pic
    KoniecGraphProcessor('../src/graph/koniec.scr', KONIECPIC).process(output)

    output.export()


if __name__ == "__main__":
    main()
