#!/usr/bin/python3

from processor.core import BuildOutput, GmSrcFileProcessor


class MapGraphProcessor(GmSrcFileProcessor):

    def __init__(self, filename, map_offset, map_anim_offset):
        super().__init__(filename, map_offset)
        self.map_anim_offset = map_anim_offset

    def process(self, output: BuildOutput):
        input_data = super().process(output)

        # extract animation (8 chars)
        for c in range(9):
            for i in range(32):
                sadr = 0x805 + (c + 2) * 96 + 4 * 8 + i
                dadr = self.map_anim_offset + 32 * c + i
                d = input_data[sadr]
                output.put_byte(dadr, d)
