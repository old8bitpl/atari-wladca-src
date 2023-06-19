#!/usr/bin/python3

from processor.core import BuildOutput, SrcFileProcessor


class WallBreachGraphProcessor(SrcFileProcessor):

    def __init__(self, filename, offset):
        super().__init__(filename, offset)

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # breach (27 chars (from 101) * 12 anim phases * 8 bytes/per phase)
        fr = 2048 + 5 + 21 * 12 * 8
        to = fr + 27 * 12 * 8
        data = input_data[fr: to]
        output.put(self.offset, data)
