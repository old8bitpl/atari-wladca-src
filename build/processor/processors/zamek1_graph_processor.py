#!/usr/bin/python3

from processor.core import BuildOutput, GmSrcFileProcessor
from processor.mem_map import KATANIMBUF, MURANIMBUF


class Zamek1GraphProcessor(GmSrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # catapult (15 chars (from 86) * 12 anim phases * 8 bytes/per phase)
        fr = 2048 + 5 + 6 * 12 * 8
        to = fr + 15 * 12 * 8
        data = input_data[fr: to]
        output.put(KATANIMBUF, data)

        # breach (27 chars (from 101) * 12 anim phases * 8 bytes/per phase)
        fr = 2048 + 5 + 21 * 12 * 8
        to = fr + 27 * 12 * 8
        data = input_data[fr: to]
        output.put(MURANIMBUF, data)
